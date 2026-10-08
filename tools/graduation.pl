#!/usr/bin/perl

# ==============================================================================
# PHÂN HỆ XÉT TỐT NGHIỆP - THƯ VIỆN ĐẠI HỌC NGOẠI THƯƠNG (FTU LIBRARY)
# ==============================================================================
# Chức năng:
# 1. Quản lý theo Đợt xét tốt nghiệp (Lưu trữ đợt, tái đối soát không cần re-upload).
# 2. Tiếp nhận danh sách mã sinh viên từ Excel / CSV hoặc paste text.
# 3. Đối soát tự động nợ sách (issues), hạn trả (date_due), tiền phạt (accountlines).
# 4. Gửi email nhắc nhở hoàn tất trả sách trước khi xét tốt nghiệp.
# 5. Khóa thẻ hàng loạt khi sinh viên tốt nghiệp (Koha + đồng bộ OpenLDAP/SSO).
# ==============================================================================

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use JSON;
use HTTP::Tiny;
use POSIX qw( strftime );
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;
use Encode qw( decode_utf8 );

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;
my $json = JSON->new->utf8;

# Tự động bảo đảm bảng dữ liệu đợt xét tốt nghiệp tồn tại
ensure_graduation_tables($dbh);

my ($template, $borrowernumber, $cookie) = get_template_and_user(
    {
        template_name   => "tools/graduation.tt",
        query           => $cgi,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => { tools => "moderate_comments" }, # Yêu cầu quyền thủ thư tools
    }
);

my $op = $cgi->param("op") || "list";
$op =~ s/^cud-//;

# ==============================================================================
# SUBROUTINE: ĐỐI SOÁT CHI TIẾT DANH SÁCH BẠN ĐỌC
# ==============================================================================
sub perform_patron_clearance_check {
    my ($dbh, $cardnumbers_ref, $batch_id) = @_;
    my @cardnumbers = @$cardnumbers_ref;

    if (!@cardnumbers) {
        return {
            success         => 0,
            error           => "Danh sách mã người dùng trống",
            total_input     => 0,
            count_cleared   => 0,
            count_has_debt  => 0,
            count_not_found => 0,
            count_debarred  => 0,
            results         => []
        };
    }

    # Giới hạn tối đa 5000 mã/lần kiểm tra để bảo đảm hiệu năng
    if (@cardnumbers > 5000) {
        @cardnumbers = @cardnumbers[0..4999];
    }

    my $placeholders = join(",", map { "?" } @cardnumbers);

    # 1. Truy vấn thông tin bạn đọc & tổng số sách mượn, tiền phạt
    my $query_patrons = qq{
        SELECT 
            b.borrowernumber,
            b.cardnumber,
            b.surname,
            b.firstname,
            CONCAT(COALESCE(b.surname,''), ' ', COALESCE(b.firstname,'')) AS full_name,
            b.email,
            b.phone,
            b.branchcode,
            b.categorycode,
            b.sort1,
            b.sort2,
            b.debarred,
            b.debarredcomment,
            b.borrowernotes,
            (SELECT COUNT(*) FROM issues i WHERE i.borrowernumber = b.borrowernumber) AS total_borrowed,
            (SELECT COUNT(*) FROM issues i WHERE i.borrowernumber = b.borrowernumber AND i.date_due < NOW()) AS total_overdue,
            (SELECT COALESCE(SUM(a.amountoutstanding), 0) FROM accountlines a WHERE a.borrowernumber = b.borrowernumber AND a.amountoutstanding > 0) AS total_fine
        FROM borrowers b
        WHERE b.cardnumber IN ($placeholders) OR b.userid IN ($placeholders)
    };

    my $sth_patrons = $dbh->prepare($query_patrons);
    $sth_patrons->execute(@cardnumbers, @cardnumbers);

    my %found_patrons;
    my @found_borrowernumbers;

    while (my $row = $sth_patrons->fetchrow_hashref) {
        my $cnum = $row->{cardnumber} || "";
        $row->{total_borrowed} = int($row->{total_borrowed} || 0);
        $row->{total_overdue}  = int($row->{total_overdue} || 0);
        $row->{total_fine}     = 0 + ($row->{total_fine} || 0);
        $row->{is_debarred}    = ($row->{debarred} && $row->{debarred} ge strftime("%Y-%m-%d", localtime)) ? 1 : 0;
        $row->{issues_list}    = [];

        $found_patrons{$cnum} = $row;
        push @found_borrowernumbers, $row->{borrowernumber};
    }

    # 2. Truy vấn chi tiết các đầu sách đang mượn nếu có bạn đọc nợ sách
    if (@found_borrowernumbers) {
        my $b_placeholders = join(",", map { "?" } @found_borrowernumbers);
        my $query_issues = qq{
            SELECT 
                i.borrowernumber,
                b.cardnumber,
                it.barcode,
                it.itemcallnumber,
                bi.title,
                bi.author,
                COALESCE(bi_items.publishercode, '') AS publishercode,
                COALESCE(bi_items.publicationyear, '') AS publicationyear,
                DATE_FORMAT(i.issuedate, '%d/%m/%Y') AS issuedate_formatted,
                DATE_FORMAT(i.date_due, '%d/%m/%Y') AS date_due_formatted,
                i.date_due,
                (i.date_due < NOW()) AS is_overdue,
                IF(i.date_due < NOW(), DATEDIFF(NOW(), i.date_due), 0) AS days_overdue
            FROM issues i
            JOIN items it ON i.itemnumber = it.itemnumber
            JOIN biblio bi ON it.biblionumber = bi.biblionumber
            LEFT JOIN biblioitems bi_items ON it.biblionumber = bi_items.biblionumber
            JOIN borrowers b ON i.borrowernumber = b.borrowernumber
            WHERE i.borrowernumber IN ($b_placeholders)
            ORDER BY i.date_due ASC
        };
        my $sth_issues = $dbh->prepare($query_issues);
        $sth_issues->execute(@found_borrowernumbers);

        while (my $issue = $sth_issues->fetchrow_hashref) {
            my $cnum = $issue->{cardnumber};
            my $pub = $issue->{publishercode} || "";
            if ($pub && $issue->{publicationyear}) {
                $pub .= " (" . $issue->{publicationyear} . ")";
            } elsif (!$pub && $issue->{publicationyear}) {
                $pub = $issue->{publicationyear};
            }
            $issue->{publisher} = $pub || "-";

            if ($found_patrons{$cnum}) {
                push @{$found_patrons{$cnum}->{issues_list}}, $issue;
            }
        }
    }

    # 3. Lấy thêm thông tin từ LDAP/SSO nếu có
    my %sso_meta;
    eval {
        my $http = HTTP::Tiny->new(timeout => 3);
        my $res = $http->get("http://10.2.0.227:8090/api/v1/users");
        if ($res->{success}) {
            my $sso_json = $json->decode($res->{content});
            if ($sso_json->{success} && ref($sso_json->{users}) eq "ARRAY") {
                for my $u (@{$sso_json->{users}}) {
                    my $uid = $u->{uid} || $u->{cardNumber};
                    $sso_meta{$uid} = {
                        studentClass => $u->{studentClass} || "",
                        department   => $u->{department} || "",
                        cohort       => $u->{cohort} || "",
                        ssoNotes     => $u->{notes} || "",
                        ssoStatus    => $u->{status} || ""
                    };
                }
            }
        }
    };

    # 4. Gom kết quả phân loại chuẩn
    my @results;
    my $count_cleared = 0;
    my $count_has_debt = 0;
    my $count_not_found = 0;
    my $count_debarred = 0;

    for my $cnum (@cardnumbers) {
        if ($found_patrons{$cnum}) {
            my $p = $found_patrons{$cnum};
            my $has_debt = ($p->{total_borrowed} > 0 || $p->{total_fine} > 0) ? 1 : 0;
            my $is_cleared = !$has_debt ? 1 : 0;

            if ($has_debt) {
                $count_has_debt++;
            } else {
                $count_cleared++;
            }
            if ($p->{is_debarred}) {
                $count_debarred++;
            }

            my $sso_info = $sso_meta{$cnum} || {};
            my $class_name = $sso_info->{studentClass} || $p->{sort1} || "Chưa cập nhật";
            my $dept_name  = $sso_info->{department}   || $p->{sort2} || "Trường ĐH Ngoại Thương";
            my $clean_note = "";
            if ($p->{is_debarred}) {
                $clean_note = $p->{debarredcomment} || "Người học đã tốt nghiệp";
                $clean_note =~ s/\[\d{2}\/\d{2}\/\d{4}\]\s*//g;
                $clean_note =~ s/\[\d{4}-\d{2}-\d{2}\]\s*//g;
                $clean_note =~ s/Người học đã tốt nghiệp\s*Người học đã tốt nghiệp/Người học đã tốt nghiệp/g;
                $clean_note =~ s/\s+/ /g;
                $clean_note =~ s/^\s+|\s+$//g;
            }

            push @results, {
                cardnumber       => $cnum,
                borrowernumber   => $p->{borrowernumber},
                full_name        => $p->{full_name},
                email            => $p->{email} || "",
                phone            => $p->{phone} || "",
                student_class    => $class_name,
                department       => $dept_name,
                total_borrowed   => $p->{total_borrowed},
                total_overdue    => $p->{total_overdue},
                total_fine       => $p->{total_fine},
                has_debt         => $has_debt,
                is_cleared       => $is_cleared,
                is_debarred      => $p->{is_debarred},
                debarred_comment => $p->{debarredcomment} || "",
                notes            => $clean_note,
                issues           => $p->{issues_list}
            };
        } else {
            $count_not_found++;
            push @results, {
                cardnumber     => $cnum,
                borrowernumber => undef,
                full_name      => "Không tìm thấy trong Koha",
                email          => "",
                phone          => "",
                student_class  => "-",
                department     => "-",
                total_borrowed => 0,
                total_overdue  => 0,
                total_fine     => 0,
                has_debt       => 0,
                is_cleared     => 0,
                is_not_found   => 1,
                is_debarred    => 0,
                notes          => "",
                issues         => []
            };
        }
    }

    # 5. Nếu đối soát theo đợt ($batch_id), cập nhật thống kê và chi tiết vào CSDL
    if ($batch_id) {
        eval {
            my $sth_up_batch = $dbh->prepare(qq{
                UPDATE ftu_graduation_batches
                SET total_patrons = ?,
                    cleared_count = ?,
                    debt_count    = ?,
                    updated_at    = NOW()
                WHERE id = ?
            });
            $sth_up_batch->execute(scalar(@cardnumbers), $count_cleared, $count_has_debt, $batch_id);

            my $sth_up_item = $dbh->prepare(qq{
                UPDATE ftu_graduation_batch_items
                SET full_name = ?,
                    student_class = ?,
                    department = ?,
                    last_status = ?,
                    last_checked_at = NOW()
                WHERE batch_id = ? AND cardnumber = ?
            });

            for my $r (@results) {
                my $st = 'CLEARED';
                if ($r->{is_not_found}) {
                    $st = 'NOT_FOUND';
                } elsif ($r->{is_debarred}) {
                    $st = 'LOCKED';
                } elsif ($r->{has_debt}) {
                    $st = 'DEBT';
                }
                $sth_up_item->execute(
                    $r->{full_name} || '',
                    $r->{student_class} || '',
                    $r->{department} || '',
                    $st,
                    $batch_id,
                    $r->{cardnumber}
                );
            }
        };
    }

    return {
        success         => 1,
        total_input     => scalar(@cardnumbers),
        count_cleared   => $count_cleared,
        count_has_debt  => $count_has_debt,
        count_not_found => $count_not_found,
        count_debarred  => $count_debarred,
        results         => \@results
    };
}

# ------------------------------------------------------------------------------
# API 0.1: DANH SÁCH CÁC ĐỢT XÉT TỐT NGHIỆP ĐÃ LƯU (OP = BATCHES_LIST)
# ------------------------------------------------------------------------------
if ($op eq "batches_list") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $sth = $dbh->prepare(qq{
        SELECT 
            b.id,
            b.batch_name,
            b.academic_year,
            b.cohort,
            b.description,
            b.total_patrons,
            b.cleared_count,
            b.debt_count,
            b.created_by,
            DATE_FORMAT(b.created_at, '%d/%m/%Y %H:%i') AS created_at_formatted,
            DATE_FORMAT(b.updated_at, '%d/%m/%Y %H:%i') AS updated_at_formatted
        FROM ftu_graduation_batches b
        ORDER BY b.id DESC
    });
    $sth->execute();
    my @batches = @{$sth->fetchall_arrayref({})};
    print $json->encode({ success => 1, batches => \@batches });
    exit;
}

# ------------------------------------------------------------------------------
# API 0.2: TẠO ĐỢT XÉT TỐT NGHIỆP MỚI VÀ LƯU LẠI (OP = BATCH_CREATE)
# ------------------------------------------------------------------------------
if ($op eq "batch_create") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $post_body = $cgi->param("POSTDATA") || "";
    my $parsed_body = {};
    if ($post_body) {
        eval { $parsed_body = $json->decode($post_body); };
    }

    my $batch_name    = $cgi->param("batch_name") || $parsed_body->{batch_name} || "";
    my $academic_year = $cgi->param("academic_year") || $parsed_body->{academic_year} || "";
    my $cohort        = $cgi->param("cohort") || $parsed_body->{cohort} || "";
    my $description   = $cgi->param("description") || $parsed_body->{description} || "";
    my $raw_uids      = $cgi->param("uids") || $parsed_body->{uids} || "";

    $batch_name =~ s/^\s+|\s+$//g;
    if (!$batch_name) {
        print $json->encode({ success => 0, error => "Vui lòng nhập tên đợt xét tốt nghiệp" });
        exit;
    }

    my @cardnumbers = ();
    if (ref($raw_uids) eq "ARRAY") {
        @cardnumbers = @$raw_uids;
    } else {
        for my $line (split(/[\r\n,;\t]+/, $raw_uids)) {
            $line =~ s/^\s+|\s+$//g;
            push @cardnumbers, $line if length($line) > 0;
        }
    }
    my %seen;
    @cardnumbers = grep { !$seen{$_}++ } @cardnumbers;

    # 1. Thêm vào bảng ftu_graduation_batches
    my $sth_insert_b = $dbh->prepare(qq{
        INSERT INTO ftu_graduation_batches (batch_name, academic_year, cohort, description, total_patrons, created_by, created_at, updated_at)
        VALUES (?, ?, ?, ?, ?, 'Thủ thư', NOW(), NOW())
    });
    $sth_insert_b->execute($batch_name, $academic_year, $cohort, $description, scalar(@cardnumbers));
    my $batch_id = $dbh->{mysql_insertid} || $dbh->last_insert_id(undef, undef, 'ftu_graduation_batches', 'id');

    if (!@cardnumbers) {
        print $json->encode({
            success         => 1,
            batch_id        => $batch_id,
            batch_name      => $batch_name,
            academic_year   => $academic_year,
            cohort          => $cohort,
            description     => $description,
            total_input     => 0,
            count_cleared   => 0,
            count_has_debt  => 0,
            count_not_found => 0,
            count_debarred  => 0,
            results         => [],
            message         => "Đã tạo đợt [$batch_name] thành công. Bạn có thể nạp danh sách sinh viên ngay bây giờ!"
        });
        exit;
    }

    # 2. Thêm các sinh viên vào ftu_graduation_batch_items
    my $sth_insert_i = $dbh->prepare(qq{
        INSERT INTO ftu_graduation_batch_items (batch_id, cardnumber, last_status)
        VALUES (?, ?, 'PENDING')
    });
    for my $cnum (@cardnumbers) {
        $sth_insert_i->execute($batch_id, $cnum);
    }

    # 3. Chạy đối soát ngay và cập nhật thống kê
    my $check_result = perform_patron_clearance_check($dbh, \@cardnumbers, $batch_id);
    $check_result->{batch_id} = $batch_id;
    $check_result->{batch_name} = $batch_name;
    $check_result->{academic_year} = $academic_year;
    $check_result->{cohort} = $cohort;
    $check_result->{message} = "Đã tạo đợt [$batch_name] và lưu danh sách " . scalar(@cardnumbers) . " sinh viên thành công!";

    print $json->encode($check_result);
    exit;
}

# ------------------------------------------------------------------------------
# API 0.3: TẢI & ĐỐI SOÁT LẠI ĐỢT XÉT TỐT NGHIỆP (OP = BATCH_LOAD / BATCH_RECHECK)
# ------------------------------------------------------------------------------
if ($op eq "batch_load" || $op eq "batch_recheck") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $batch_id = int($cgi->param("batch_id") || 0);

    if (!$batch_id) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $batch_id = int($parsed->{batch_id} || 0);
            };
        }
    }

    if (!$batch_id) {
        print $json->encode({ success => 0, error => "Mã đợt xét tốt nghiệp không hợp lệ" });
        exit;
    }

    my $sth_b = $dbh->prepare("SELECT * FROM ftu_graduation_batches WHERE id = ?");
    $sth_b->execute($batch_id);
    my $batch_row = $sth_b->fetchrow_hashref;
    if (!$batch_row) {
        print $json->encode({ success => 0, error => "Không tìm thấy đợt xét tốt nghiệp có ID $batch_id" });
        exit;
    }

    my $sth_items = $dbh->prepare("SELECT cardnumber FROM ftu_graduation_batch_items WHERE batch_id = ? ORDER BY id ASC");
    $sth_items->execute($batch_id);
    my @cardnumbers;
    while (my ($cnum) = $sth_items->fetchrow_array) {
        push @cardnumbers, $cnum if $cnum;
    }

    if (!@cardnumbers) {
        print $json->encode({
            success         => 1,
            batch_id        => $batch_id,
            batch_name      => $batch_row->{batch_name},
            academic_year   => $batch_row->{academic_year} || "",
            cohort          => $batch_row->{cohort} || "",
            description     => $batch_row->{description} || "",
            is_locked       => int($batch_row->{is_locked} || 0),
            total_input     => 0,
            count_cleared   => 0,
            count_has_debt  => 0,
            count_not_found => 0,
            count_debarred  => 0,
            results         => [],
            message         => "Đợt xét chưa có sinh viên nào. Vui lòng nạp file Excel hoặc nhập mã sinh viên."
        });
        exit;
    }

    # Chạy đối soát thời gian thực để làm mới dữ liệu
    my $check_result = perform_patron_clearance_check($dbh, \@cardnumbers, $batch_id);
    $check_result->{batch_id} = $batch_id;
    $check_result->{batch_name} = $batch_row->{batch_name};
    $check_result->{academic_year} = $batch_row->{academic_year} || "";
    $check_result->{cohort} = $batch_row->{cohort} || "";
    $check_result->{description} = $batch_row->{description} || "";
    $check_result->{message} = "Đã đối soát lại thành công dữ liệu đợt: " . $batch_row->{batch_name};

    print $json->encode($check_result);
    exit;
}

# ------------------------------------------------------------------------------
# API 0.4: NẠP / THÊM SINH VIÊN VÀO ĐỢT (OP = BATCH_IMPORT_STUDENTS)
# ------------------------------------------------------------------------------
if ($op eq "batch_import_students") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $post_body = $cgi->param("POSTDATA") || "";
    my $parsed_body = {};
    if ($post_body) {
        eval { $parsed_body = $json->decode($post_body); };
    }

    my $batch_id    = int($cgi->param("batch_id") || $parsed_body->{batch_id} || 0);
    my $raw_uids    = $cgi->param("uids") || $parsed_body->{uids} || "";
    my $import_mode = $cgi->param("import_mode") || $parsed_body->{import_mode} || "append";

    if (!$batch_id) {
        print $json->encode({ success => 0, error => "Mã đợt xét tốt nghiệp không hợp lệ" });
        exit;
    }

    my $sth_b = $dbh->prepare("SELECT * FROM ftu_graduation_batches WHERE id = ?");
    $sth_b->execute($batch_id);
    my $batch_row = $sth_b->fetchrow_hashref;
    if (!$batch_row) {
        print $json->encode({ success => 0, error => "Không tìm thấy đợt xét tốt nghiệp có ID $batch_id" });
        exit;
    }

    my @new_cardnumbers = ();
    if (ref($raw_uids) eq "ARRAY") {
        @new_cardnumbers = @$raw_uids;
    } else {
        for my $line (split(/[\r\n,;\t]+/, $raw_uids)) {
            $line =~ s/^\s+|\s+$//g;
            push @new_cardnumbers, $line if length($line) > 0;
        }
    }
    my %seen_new;
    @new_cardnumbers = grep { !$seen_new{$_}++ } @new_cardnumbers;

    if (!@new_cardnumbers) {
        print $json->encode({ success => 0, error => "Danh sách sinh viên trống. Vui lòng nạp file hoặc dán MSSV." });
        exit;
    }

    if ($import_mode eq "replace") {
        $dbh->do("DELETE FROM ftu_graduation_batch_items WHERE batch_id = ?", undef, $batch_id);
    }

    # Đọc danh sách hiện có để tránh trùng lặp khi append
    my %existing;
    my $sth_exist = $dbh->prepare("SELECT cardnumber FROM ftu_graduation_batch_items WHERE batch_id = ?");
    $sth_exist->execute($batch_id);
    while (my ($c) = $sth_exist->fetchrow_array) {
        $existing{$c} = 1;
    }

    my $sth_insert_i = $dbh->prepare(qq{
        INSERT INTO ftu_graduation_batch_items (batch_id, cardnumber, last_status)
        VALUES (?, ?, 'PENDING')
    });
    my $inserted_count = 0;
    for my $cnum (@new_cardnumbers) {
        next if $existing{$cnum};
        $sth_insert_i->execute($batch_id, $cnum);
        $existing{$cnum} = 1;
        $inserted_count++;
    }

    # Lấy toàn bộ cardnumbers của đợt này để đối soát
    my $sth_items = $dbh->prepare("SELECT DISTINCT cardnumber FROM ftu_graduation_batch_items WHERE batch_id = ?");
    $sth_items->execute($batch_id);
    my @all_cardnumbers;
    while (my ($cnum) = $sth_items->fetchrow_array) {
        push @all_cardnumbers, $cnum if $cnum;
    }

    $dbh->do("UPDATE ftu_graduation_batches SET total_patrons = ?, updated_at = NOW() WHERE id = ?", undef, scalar(@all_cardnumbers), $batch_id);

    my $check_result = perform_patron_clearance_check($dbh, \@all_cardnumbers, $batch_id);
    $check_result->{batch_id}      = $batch_id;
    $check_result->{batch_name}    = $batch_row->{batch_name};
    $check_result->{academic_year} = $batch_row->{academic_year} || "";
    $check_result->{cohort}        = $batch_row->{cohort} || "";
    $check_result->{description}   = $batch_row->{description} || "";
    $check_result->{message}       = "Đã nạp thành công $inserted_count sinh viên mới vào đợt [" . $batch_row->{batch_name} . "] (Tổng cộng: " . scalar(@all_cardnumbers) . " SV).";

    print $json->encode($check_result);
    exit;
}

# ------------------------------------------------------------------------------
# API 0.5: XÓA ĐỢT XÉT TỐT NGHIỆP (OP = BATCH_DELETE)
# ------------------------------------------------------------------------------
if ($op eq "batch_delete") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $batch_id = int($cgi->param("batch_id") || 0);

    if (!$batch_id) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $batch_id = int($parsed->{batch_id} || 0);
            };
        }
    }

    if (!$batch_id) {
        print $json->encode({ success => 0, error => "Mã đợt không hợp lệ" });
        exit;
    }

    my $sth_del = $dbh->prepare("DELETE FROM ftu_graduation_batches WHERE id = ?");
    $sth_del->execute($batch_id);

    print $json->encode({ success => 1, message => "Đã xóa đợt xét tốt nghiệp thành công!" });
    exit;
}

# ------------------------------------------------------------------------------
# API 1: ĐỐI SOÁT NHANH KHÔNG LƯU ĐỢT (OP = CHECK)
# ------------------------------------------------------------------------------
if ($op eq "check") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $raw_data = $cgi->param("uids") || "";
    if (!$raw_data) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $raw_data = $parsed->{uids} if ref($parsed) eq "HASH";
            };
        }
    }

    my @cardnumbers = ();
    if (ref($raw_data) eq "ARRAY") {
        @cardnumbers = @$raw_data;
    } else {
        for my $line (split(/[\r\n,;\t]+/, $raw_data)) {
            $line =~ s/^\s+|\s+$//g;
            push @cardnumbers, $line if length($line) > 0;
        }
    }

    my %seen;
    @cardnumbers = grep { !$seen{$_}++ } @cardnumbers;

    if (!@cardnumbers) {
        print $json->encode({ success => 0, error => "Danh sách mã người dùng trống" });
        exit;
    }

    my $result = perform_patron_clearance_check($dbh, \@cardnumbers, undef);
    print $json->encode($result);
    exit;
}

# ------------------------------------------------------------------------------
# API 2: GỬI EMAIL NHẮC NHỞ TRẢ SÁCH (OP = SEND_REMINDERS)
# ------------------------------------------------------------------------------
if ($op eq "send_reminders") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $raw_data = $cgi->param("uids") || "";
    if (!$raw_data) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $raw_data = $parsed->{uids} if ref($parsed) eq "HASH";
            };
        }
    }

    my @target_uids = ref($raw_data) eq "ARRAY" ? @$raw_data : split(/[\r\n,;\t]+/, $raw_data);
    @target_uids = grep { s/^\s+|\s+$//g; length($_) > 0 } @target_uids;

    if (!@target_uids) {
        print $json->encode({ success => 0, error => "Chưa chọn người nhận thông báo" });
        exit;
    }

    my $placeholders = join(",", map { "?" } @target_uids);

    # Truy vấn danh sách sách nợ của các sinh viên được chọn
    my $query = qq{
        SELECT 
            b.borrowernumber,
            b.cardnumber,
            CONCAT(COALESCE(b.surname,''), ' ', COALESCE(b.firstname,'')) AS full_name,
            b.email,
            it.barcode,
            bi.title,
            DATE_FORMAT(i.date_due, '%d/%m/%Y') AS date_due_formatted,
            IF(i.date_due < NOW(), DATEDIFF(NOW(), i.date_due), 0) AS days_overdue
        FROM borrowers b
        JOIN issues i ON b.borrowernumber = i.borrowernumber
        JOIN items it ON i.itemnumber = it.itemnumber
        JOIN biblio bi ON it.biblionumber = bi.biblionumber
        WHERE b.cardnumber IN ($placeholders)
        ORDER BY b.cardnumber, i.date_due ASC
    };

    my $sth = $dbh->prepare($query);
    $sth->execute(@target_uids);

    my %patron_debts;
    while (my $row = $sth->fetchrow_hashref) {
        my $cnum = $row->{cardnumber};
        $patron_debts{$cnum} ||= {
            borrowernumber => $row->{borrowernumber},
            cardnumber     => $cnum,
            full_name      => $row->{full_name},
            email          => $row->{email},
            books          => []
        };
        push @{$patron_debts{$cnum}->{books}}, $row;
    }

    my $sent_count = 0;
    my $failed_count = 0;
    my @sent_details;

    my $sth_queue = $dbh->prepare(qq{
        INSERT INTO message_queue 
        (borrowernumber, subject, content, metadata, letter_code, message_transport_type, status, time_queued, to_address, from_address, content_type)
        VALUES (?, ?, ?, ?, 'GRAD_REMIND', 'email', 'pending', NOW(), ?, 'thuvien\@ftu.edu.vn', 'text/html; charset="UTF-8"')
    });

    for my $cnum (keys %patron_debts) {
        my $p = $patron_debts{$cnum};
        my $to_email = $p->{email} || "$cnum\@ftu.edu.vn";

        my $books_html = "<table border='1' cellpadding='6' cellspacing='0' style='border-collapse:collapse; width:100%; border-color:#cbd5e1; font-size:13px;'>";
        $books_html .= "<tr style='background:#f1f5f9; text-align:left;'><th>STT</th><th>Mã vạch</th><th>Tựa sách</th><th>Hạn trả</th><th>Tình trạng</th></tr>";
        my $idx = 1;
        for my $b (@{$p->{books}}) {
            my $status_text = $b->{days_overdue} > 0 ? "<span style='color:#dc2626; font-weight:600;'>Quá hạn $b->{days_overdue} ngày</span>" : "<span style='color:#16a34a;'>Trong hạn</span>";
            $books_html .= "<tr><td>$idx</td><td>$b->{barcode}</td><td><strong>$b->{title}</strong></td><td>$b->{date_due_formatted}</td><td>$status_text</td></tr>";
            $idx++;
        }
        $books_html .= "</table>";

        my $subject = "[FTU Library] Thông báo hoàn tất trả tài liệu phục vụ xét tốt nghiệp - Mã SV: $cnum";
        my $body = qq{
            <div style="font-family: Arial, sans-serif; font-size: 14px; line-height: 1.6; color: #1e293b; max-width: 680px; margin: 0 auto; border: 1px solid #e2e8f0; border-radius: 6px; padding: 24px;">
                <div style="border-bottom: 2px solid #b91c1c; padding-bottom: 12px; margin-bottom: 16px;">
                    <h3 style="color: #b91c1c; margin: 0;">PHÂN HIỆU TRƯỜNG ĐẠI HỌC NGOẠI THƯƠNG</h3>
                    <p style="margin: 4px 0 0 0; color: #475569; font-size: 13px;">Thư viện Phân hiệu - Phân hệ Xét tốt nghiệp</p>
                </div>
                <p>Kính gửi sinh viên: <strong>$p->{full_name}</strong> (Mã SV: <strong>$cnum</strong>),</p>
                <p>Căn cứ dữ liệu mượn trả tại Thư viện, hiện tại bạn vẫn còn giữ <strong>} . scalar(@{$p->{books}}) . qq{ cuốn sách</strong> chưa hoàn trả:</p>
                $books_html
                <p style="margin-top: 16px;">Để đủ điều kiện xác nhận hoàn thành nghĩa vụ thư viện phục vụ Hội đồng xét tốt nghiệp, đề nghị bạn khẩn trương mang toàn bộ tài liệu trên đến Thư viện để làm thủ tục hoàn trả.</p>
                <div style="background: #fef2f2; border-left: 4px solid #ef4444; padding: 10px 14px; margin: 16px 0; font-size: 13px; color: #991b1b;">
                    <strong>Lưu ý:</strong> Mọi thắc mắc xin vui lòng liên hệ trực tiếp Bộ phận Mượn trả Thư viện hoặc gửi email về thuvien\@ftu.edu.vn.
                </div>
                <p style="color: #64748b; font-size: 12px; margin-top: 24px; border-top: 1px solid #e2e8f0; padding-top: 12px;">
                    Thông báo này được gửi tự động từ Hệ thống Thư viện Phân hiệu Trường Đại học Ngoại thương (FTULIB SYSTEM).
                </p>
            </div>
        };

        eval {
            $sth_queue->execute($p->{borrowernumber}, $subject, $body, $json->encode({ cardnumber => $cnum }), $to_email);
            $sent_count++;
            push @sent_details, { cardnumber => $cnum, name => $p->{full_name}, email => $to_email, status => "QUEUED" };
        };
        if ($@) {
            $failed_count++;
        }
    }

    eval {
        system("nohup /kohadevbox/koha/misc/cronjobs/process_message_queue.pl >/dev/null 2>&1 &");
    };

    print $json->encode({
        success      => 1,
        message      => "Đã tạo $sent_count thông báo email nhắc nhở thành công!",
        sent_count   => $sent_count,
        failed_count => $failed_count,
        details      => \@sent_details
    });
    exit;
}

# ------------------------------------------------------------------------------
# API 3: KHÓA THẺ HÀNG LOẠT VÀ ĐỒNG BỘ GHI CHÚ TỐT NGHIỆP (OP = BATCH_LOCK)
# ------------------------------------------------------------------------------
if ($op eq "batch_lock") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $raw_data = $cgi->param("uids") || "";
    if (!$raw_data) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $raw_data = $parsed->{uids} if ref($parsed) eq "HASH";
            };
        }
    }

    my @target_uids = ref($raw_data) eq "ARRAY" ? @$raw_data : split(/[\r\n,;\t]+/, $raw_data);
    @target_uids = grep { s/^\s+|\s+$//g; length($_) > 0 } @target_uids;

    if (!@target_uids) {
        print $json->encode({ success => 0, error => "Chưa chọn tài khoản cần khóa thẻ" });
        exit;
    }

    my $placeholders = join(",", map { "?" } @target_uids);

    # 1. Cập nhật Koha borrowers: debarred='9999-12-31', debarredcomment='Người học đã tốt nghiệp'
    my $today_str = strftime("%d/%m/%Y", localtime);
    my $update_query = qq{
        UPDATE borrowers
        SET debarred = '9999-12-31',
            debarredcomment = 'Người học đã tốt nghiệp',
            login_attempts = -1,
            borrowernotes = CONCAT(COALESCE(borrowernotes,''), IF(borrowernotes IS NULL OR borrowernotes = '', '', '\n'), '[$today_str] Người học đã tốt nghiệp')
        WHERE cardnumber IN ($placeholders) AND categorycode != 'S'
    };

    my $sth_update = $dbh->prepare($update_query);
    $sth_update->execute(@target_uids);
    my $rows_affected = $sth_update->rows;

    # 1.1 Tạo bản ghi debarment trong borrower_debarments
    eval {
        my $sth_debar = $dbh->prepare(qq{
            INSERT INTO borrower_debarments (borrowernumber, type, comment, expiration, created)
            SELECT borrowernumber, 'MANUAL', 'Người học đã tốt nghiệp', '9999-12-31', NOW()
            FROM borrowers
            WHERE cardnumber IN ($placeholders)
              AND borrowernumber NOT IN (SELECT borrowernumber FROM borrower_debarments WHERE comment LIKE '%tốt nghiệp%')
        });
        $sth_debar->execute(@target_uids);
    };

    # 2. Đồng bộ sang OpenLDAP & SSO Portal
    my $sso_synced = 0;
    eval {
        my $http = HTTP::Tiny->new(timeout => 5);
        my $payload = $json->encode({
            uids   => \@target_uids,
            status => "LOCKED",
            reason => "Người học đã tốt nghiệp",
            notes  => "Người học đã tốt nghiệp"
        });
        my @sso_endpoints = (
            "http://ftulib-sso-portal:8090/api/v1/sso/users/batch-status",
            "http://10.2.0.226/api/v1/sso/users/batch-status",
            "http://127.0.0.1:8090/api/v1/sso/users/batch-status"
        );
        for my $endpoint (@sso_endpoints) {
            my $res = $http->post($endpoint, {
                headers => {
                    "Content-Type"    => "application/json",
                    "x-koha-staff"    => "1",
                    "x-koha-internal" => "1"
                },
                content => $payload
            });
            if ($res->{success}) {
                my $res_json = eval { $json->decode($res->{content}) };
                if ($res_json && $res_json->{success}) {
                    $sso_synced = $res_json->{count} || scalar(@target_uids);
                    last;
                }
            }
        }
    };

    print $json->encode({
        success       => 1,
        message       => "Đã khóa thẻ thành công $rows_affected sinh viên trên Koha và đồng bộ trạng thái tốt nghiệp sang SSO Portal!",
        rows_affected => $rows_affected,
        sso_synced    => $sso_synced,
        uids          => \@target_uids
    });
    exit;
}

# ------------------------------------------------------------------------------
# API 4: MỞ KHÓA THẺ HÀNG LOẠT (OP = BATCH_UNLOCK)
# ------------------------------------------------------------------------------
if ($op eq "batch_unlock") {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $raw_data = $cgi->param("uids") || "";
    if (!$raw_data) {
        my $post_body = $cgi->param("POSTDATA") || "";
        if ($post_body) {
            eval {
                my $parsed = $json->decode($post_body);
                $raw_data = $parsed->{uids} if ref($parsed) eq "HASH";
            };
        }
    }

    my @target_uids = ref($raw_data) eq "ARRAY" ? @$raw_data : split(/[\r\n,;\t]+/, $raw_data);
    @target_uids = grep { s/^\s+|\s+$//g; length($_) > 0 } @target_uids;

    if (!@target_uids) {
        print $json->encode({ success => 0, error => "Chưa chọn tài khoản cần mở khóa thẻ" });
        exit;
    }

    my $placeholders = join(",", map { "?" } @target_uids);

    # 1. Cập nhật Koha borrowers: debarred = NULL, debarredcomment = ''
    my $today_str = strftime("%d/%m/%Y", localtime);
    my $update_query = qq{
        UPDATE borrowers
        SET debarred = NULL,
            debarredcomment = '',
            borrowernotes = CONCAT(COALESCE(borrowernotes,''), IF(borrowernotes IS NULL OR borrowernotes = '', '', '\n'), '[$today_str] Đã mở khóa thẻ')
        WHERE cardnumber IN ($placeholders)
    };

    my $sth_update = $dbh->prepare($update_query);
    $sth_update->execute(@target_uids);
    my $rows_affected = $sth_update->rows;

    # 2. Đồng bộ sang OpenLDAP & SSO Portal
    my $sso_synced = 0;
    eval {
        my $http = HTTP::Tiny->new(timeout => 5);
        my $payload = $json->encode({
            uids   => \@target_uids,
            status => "ACTIVE",
            reason => "Mở khóa thẻ thư viện",
            notes  => "Mở khóa thẻ thư viện"
        });
        my @sso_endpoints = (
            "http://ftulib-sso-portal:8090/api/v1/sso/users/batch-status",
            "http://10.2.0.226/api/v1/sso/users/batch-status",
            "http://127.0.0.1:8090/api/v1/sso/users/batch-status"
        );
        for my $endpoint (@sso_endpoints) {
            my $res = $http->post($endpoint, {
                headers => {
                    "Content-Type"    => "application/json",
                    "x-koha-staff"    => "1",
                    "x-koha-internal" => "1"
                },
                content => $payload
            });
            if ($res->{success}) {
                my $res_json = eval { $json->decode($res->{content}) };
                if ($res_json && $res_json->{success}) {
                    $sso_synced = $res_json->{count} || scalar(@target_uids);
                    last;
                }
            }
        }
    };

    print $json->encode({
        success       => 1,
        message       => "Đã mở khóa thẻ thành công $rows_affected sinh viên trên Koha và đồng bộ trạng thái hoạt động sang SSO Portal!",
        rows_affected => $rows_affected,
        sso_synced    => $sso_synced,
        uids          => \@target_uids
    });
    exit;
}

# ------------------------------------------------------------------------------
# GIAO DIỆN CHÍNH (OP = LIST): XUẤT TEMPLATE TT
# ------------------------------------------------------------------------------
my $sth_initial_batches = $dbh->prepare(qq{
    SELECT 
        id, batch_name, academic_year, cohort, description, total_patrons, cleared_count, debt_count,
        DATE_FORMAT(created_at, '%d/%m/%Y %H:%i') AS created_at_formatted
    FROM ftu_graduation_batches
    ORDER BY id DESC
});
$sth_initial_batches->execute();
my @initial_batches = @{$sth_initial_batches->fetchall_arrayref({})};

$template->param(
    page_title         => "Phân hệ Xét tốt nghiệp - Thư viện FTU",
    saved_batches         => \@initial_batches,
    saved_batches_json    => decode_utf8($json->encode(\@initial_batches)),
);

output_html_with_http_headers $cgi, $cookie, $template->output;

# ==============================================================================
# SUBROUTINE: BẢO ĐẢM CẤU TRÚC BẢNG ĐỢT TỐT NGHIỆP TRONG CSDL
# ==============================================================================
sub ensure_graduation_tables {
    my ($dbh) = @_;
    eval {
        $dbh->do(qq{
            CREATE TABLE IF NOT EXISTS ftu_graduation_batches (
                id INT AUTO_INCREMENT PRIMARY KEY,
                batch_name VARCHAR(255) NOT NULL,
                academic_year VARCHAR(50) DEFAULT '',
                cohort VARCHAR(50) DEFAULT '',
                description TEXT NULL,
                total_patrons INT DEFAULT 0,
                cleared_count INT DEFAULT 0,
                debt_count INT DEFAULT 0,
                created_by VARCHAR(100) DEFAULT 'Thủ thư',
                created_at DATETIME DEFAULT CURRENT_TIMESTAMP,
                updated_at DATETIME DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
        });
        $dbh->do(qq{
            CREATE TABLE IF NOT EXISTS ftu_graduation_batch_items (
                id INT AUTO_INCREMENT PRIMARY KEY,
                batch_id INT NOT NULL,
                cardnumber VARCHAR(64) NOT NULL,
                full_name VARCHAR(255) DEFAULT '',
                student_class VARCHAR(100) DEFAULT '',
                department VARCHAR(255) DEFAULT '',
                last_status VARCHAR(30) DEFAULT 'PENDING',
                last_checked_at DATETIME NULL,
                INDEX idx_batch_id (batch_id),
                INDEX idx_cardnumber (cardnumber),
                CONSTRAINT fk_ftu_grad_batch FOREIGN KEY (batch_id) REFERENCES ftu_graduation_batches (id) ON DELETE CASCADE
            ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci;
        });
    };
}
