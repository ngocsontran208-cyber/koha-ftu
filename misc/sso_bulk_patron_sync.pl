#!/usr/bin/perl
use Modern::Perl;
use utf8;
binmode( STDIN );
binmode( STDOUT, ':encoding(UTF-8)' );
binmode( STDERR, ':encoding(UTF-8)' );

use JSON qw(decode_json encode_json);
use C4::Context;
use Koha::AuthUtils qw(hash_password);

local $/;
my $raw_input = <STDIN>;
unless ($raw_input) {
    print encode_json({ success => 0, error => 'Empty input' });
    exit 0;
}

my $users = eval { decode_json($raw_input) };
if ($@ || !ref($users) || ref($users) ne 'ARRAY') {
    print encode_json({ success => 0, error => 'Invalid JSON input: ' . ($@ || 'Not an array') });
    exit 0;
}

my $dbh = C4::Context->dbh;
unless ($dbh) {
    print encode_json({ success => 0, error => 'Could not connect to Koha database' });
    exit 0;
}

my $sql = q{
INSERT INTO borrowers (
    cardnumber, userid, surname, firstname, dateofbirth, sex, 
    categorycode, branchcode, dateenrolled, dateexpiry, debarred, debarredcomment,
    flags, phone, email, address, borrowernotes, sort1, sort2, password
) VALUES (
    ?, ?, ?, ?, ?, ?,
    ?, 'CPL', ?, ?, ?, ?,
    ?, ?, ?, ?, ?, ?, ?, ?
) ON DUPLICATE KEY UPDATE 
    surname=VALUES(surname), firstname=VALUES(firstname), 
    dateofbirth=VALUES(dateofbirth),
    sex=VALUES(sex),
    categorycode=VALUES(categorycode), dateenrolled=VALUES(dateenrolled), 
    dateexpiry=IF(categorycode='S' OR VALUES(categorycode)='S', '2099-12-31', VALUES(dateexpiry)),
    debarred=IF(categorycode='S' OR VALUES(categorycode)='S', NULL, VALUES(debarred)),
    debarredcomment=IF(categorycode='S' OR VALUES(categorycode)='S', NULL, VALUES(debarredcomment)),
    flags=IF(categorycode='S' OR VALUES(categorycode)='S', 1, flags),
    phone=VALUES(phone),
    email=VALUES(email),
    address=VALUES(address),
    borrowernotes=VALUES(borrowernotes),
    sort1=IF(categorycode='S' OR VALUES(categorycode)='S', NULL, VALUES(sort1)),
    sort2=VALUES(sort2),
    password=IF(VALUES(password) IS NOT NULL AND VALUES(password) != '', VALUES(password), password)
};

my $sth = $dbh->prepare($sql);
unless ($sth) {
    print encode_json({ success => 0, error => 'Prepare failed: ' . $dbh->errstr });
    exit 0;
}

my %pass_cache;
sub get_hash {
    my ($p) = @_;
    return '' unless defined $p && $p ne '';
    return $pass_cache{$p} if exists $pass_cache{$p};
    my $h = eval { hash_password($p) } || '';
    $pass_cache{$p} = $h;
    return $h;
}

sub parse_date_to_sql {
    my ($d, $default) = @_;
    return $default unless defined $d && $d =~ /\S/;
    $d =~ s/^\s+|\s+$//g;
    # YYYY-MM-DD
    if ($d =~ /^(\d{4})-(\d{1,2})-(\d{1,2})$/) {
        return sprintf("%04d-%02d-%02d", $1, $2, $3);
    }
    # DD/MM/YYYY
    if ($d =~ /^(\d{1,2})[\/\-\.](\d{1,2})[\/\-\.](\d{4})$/) {
        return sprintf("%04d-%02d-%02d", $3, $2, $1);
    }
    return $default;
}

my ($sec,$min,$hour,$mday,$mon,$year) = localtime();
my $today_sql = sprintf("%04d-%02d-%02d", $year + 1900, $mon + 1, $mday);

my $synced = 0;
my $failed = 0;
my @errors;

$dbh->begin_work;

for my $u (@$users) {
    my $uid = $u->{uid};
    next unless defined $uid && $uid =~ /\S/;
    $uid =~ s/^\s+|\s+$//g;

    my $role = $u->{role} || 'STUDENT';
    my $categorycode = ($role eq 'STUDENT') ? 'ST' : ($role eq 'POSTGRAD' ? 'SC' : ($role eq 'FACULTY' ? 'T' : 'S'));
    my $is_staff = ($categorycode eq 'S' || $role eq 'ADMIN');

    my $full_name = $u->{fullName} || $uid;
    my @parts = split(/\s+/, $full_name);
    my $surname = $parts[0] || 'FTU';
    my $firstname = @parts > 1 ? join(' ', @parts[1..$#parts]) : $uid;

    my $email = (defined $u->{email} && $u->{email} =~ /\S/) ? $u->{email} : undef;
    my $phone = (defined $u->{phone} && $u->{phone} =~ /\S/) ? $u->{phone} : undef;
    my $address = (defined $u->{address} && $u->{address} =~ /\S/) ? $u->{address} : undef;
    my $gender = $u->{gender} || '';
    my $sex = ($gender =~ /^(Nữ|F)/i) ? 'F' : (($gender =~ /^(Nam|M)/i) ? 'M' : undef);

    my $dob = parse_date_to_sql($u->{dateOfBirth}, undef);
    my $dateenrolled = parse_date_to_sql($u->{issueDate}, undef);
    my $dateexpiry = parse_date_to_sql($u->{expiryDate}, undef);

    my $debarred = undef;
    my $debarredcomment = undef;
    if (!$is_staff) {
        if (($u->{status} && $u->{status} eq 'LOCKED')) {
            $debarred = '2099-12-31';
            $debarredcomment = 'Khóa thẻ tài khoản SSO';
        } elsif (($u->{status} && $u->{status} eq 'EXPIRED') || ($dateexpiry && $dateexpiry lt $today_sql)) {
            $debarred = '2099-12-31';
            $debarredcomment = 'Thẻ bạn đọc đã hết hạn sử dụng';
        }
    }

    my $flags = $is_staff ? 1 : undef;

    my $cohort_class = '';
    if ($u->{cohort} || $u->{studentClass}) {
        my @cc;
        push @cc, "Khóa: " . $u->{cohort} if $u->{cohort};
        push @cc, "Lớp: " . $u->{studentClass} if $u->{studentClass};
        $cohort_class = join(' - ', @cc);
    }
    my $sort1 = $is_staff ? undef : ($cohort_class || undef);
    my $sort2 = $u->{cccd} || undef;

    my @notes_parts;
    push @notes_parts, "Khoa: " . $u->{department} if $u->{department};
    push @notes_parts, "CCCD: " . $u->{cccd} if $u->{cccd};
    push @notes_parts, "Trình độ: " . $u->{educationLevel} if $u->{educationLevel};
    push @notes_parts, "Nghề nghiệp: " . $u->{occupation} if $u->{occupation};
    push @notes_parts, "Dân tộc: " . $u->{ethnicity} if $u->{ethnicity};
    push @notes_parts, "Nơi làm việc: " . $u->{workplace} if $u->{workplace};
    push @notes_parts, $u->{notes} if $u->{notes};
    my $borrowernotes = @notes_parts ? join(' | ', @notes_parts) : undef;

    my $raw_pass = $u->{password};
    my $hashed_pass = (defined $raw_pass && $raw_pass ne '') ? get_hash($raw_pass) : undef;

    my $res = eval {
        $sth->execute(
            $uid, $uid, $surname, $firstname, $dob, $sex,
            $categorycode, $dateenrolled, $dateexpiry, $debarred, $debarredcomment,
            $flags, $phone, $email, $address, $borrowernotes, $sort1, $sort2, $hashed_pass
        );
    };
    if ($@ || !$res) {
        $failed++;
        push @errors, "$uid: " . ($@ || $sth->errstr);
    } else {
        $synced++;
    }
}

$dbh->commit;

print encode_json({
    success => 1,
    synced => $synced,
    failed => $failed,
    errors => \@errors
});
