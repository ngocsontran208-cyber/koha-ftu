#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use JSON qw( to_json );
use C4::Context;

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;

my $id     = $cgi->param("id");
my $type   = $cgi->param("type") || "all";
my $limit  = int($cgi->param("limit") || 10);
$limit = 50 if $limit > 50 || $limit <= 0;

print $cgi->header(
    -type    => "application/json; charset=utf-8",
    -expires => "now",
    -Access_Control_Allow_Origin => "*",
);

if ($id) {
    my $sth = $dbh->prepare("SELECT * FROM koha_portal_posts WHERE id = ?");
    $sth->execute($id);
    my $post = $sth->fetchrow_hashref;
    if ($post) {
        # Increment views
        $dbh->do("UPDATE koha_portal_posts SET views_count = views_count + 1 WHERE id = ?", undef, $id);
        format_post($post);
        print to_json($post);
    } else {
        print to_json({ error => "Not found" });
    }
    exit;
}

if ($type eq "books") {
    # Tự động đảm bảo Report 1 trong saved_sql luôn tồn tại cho svc/report
    eval {
        my $chk = $dbh->selectrow_array("SELECT id FROM saved_sql WHERE id = 1");
        if (!$chk) {
            $dbh->do("INSERT INTO saved_sql (id, report_name, savedsql, public, date_created) VALUES (1, 'Sách mới cập nhật trang chủ', 'SELECT b.biblionumber, b.title, b.author, bi.publicationyear AS year, UNIX_TIMESTAMP(b.timestamp) AS cover_ts FROM biblio b LEFT JOIN biblioitems bi ON b.biblionumber = bi.biblionumber ORDER BY b.biblionumber DESC LIMIT 20', 1, NOW())");
        }
    };

    my $b_sth = $dbh->prepare("
        SELECT b.biblionumber, b.biblionumber AS id, b.title, b.author, bi.publicationyear AS year, bi.isbn, bi.itemtype, UNIX_TIMESTAMP(b.timestamp) AS cover_ts
        FROM biblio b
        LEFT JOIN biblioitems bi ON b.biblionumber = bi.biblionumber
        ORDER BY b.biblionumber DESC
        LIMIT $limit
    ");
    $b_sth->execute();
    my @books;
    while (my $row = $b_sth->fetchrow_hashref) {
        $row->{link} = "/cgi-bin/koha/opac-detail.pl?biblionumber=" . $row->{biblionumber};
        push @books, $row;
    }
    print to_json(\@books);
    exit;
}

my $query = "SELECT * FROM koha_portal_posts WHERE status = ?";
my @params = ("published");

if ($type eq "all") {
    $query .= " AND post_type NOT IN ('database', 'banner')";
} elsif ($type ne "all_with_db") {
    $query .= " AND post_type = ?";
    push @params, $type;
}

if ($type eq "database" || $type eq "banner") {
    $query .= " ORDER BY sort_order ASC, id ASC LIMIT $limit";
} else {
    $query .= " ORDER BY is_featured DESC, COALESCE(event_start, created_at) DESC LIMIT $limit";
}

my $sth = $dbh->prepare($query);
$sth->execute(@params);

my @posts;
while (my $row = $sth->fetchrow_hashref) {
    format_post($row);
    push @posts, $row;
}

print to_json(\@posts);

sub format_post {
    my ($p) = @_;
    return unless $p;
    
    # Format created_at date
    if ($p->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/) {
        $p->{created_year}  = $1;
        $p->{created_month} = "Th" . int($2);
        $p->{created_day}   = sprintf("%02d", int($3));
        $p->{formatted_date} = "$p->{created_day}/$2/$1";
    }

    # Format event date
    if ($p->{event_start} && $p->{event_start} =~ /^(\d{4})-(\d{2})-(\d{2})\s+(\d{2}):(\d{2})/) {
        $p->{event_year}  = $1;
        $p->{event_month} = "Th" . int($2);
        $p->{event_day}   = sprintf("%02d", int($3));
        $p->{event_time}  = "$4:$5";
        $p->{formatted_event_date} = "$p->{event_day}/$2/$1";
    }

    # Format banner text visibility
    if ($p->{post_type} && $p->{post_type} eq 'banner') {
        $p->{show_text} = ($p->{content} && $p->{content} eq 'show_text') ? 1 : 0;
    }
}
