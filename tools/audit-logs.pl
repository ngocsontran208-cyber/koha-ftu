#!/usr/bin/perl

# ==============================================================================
# PHÂN HỆ NHẬT KÝ HỆ THỐNG & KIỂM TOÁN AN NINH (SYSTEM AUDIT & ACTION LOGS)
# THƯ VIỆN PHÂN HIỆU TRƯỜNG ĐẠI HỌC NGOẠI THƯƠNG (FTU LIBRARY)
# ==============================================================================
# Chức năng:
# 1. Giám sát toàn diện: Ai làm gì, thực thi khi nào, qua giao diện nào (Intranet, OPAC, API, Cron).
# 2. Báo cáo thống kê: Thao tác hôm nay, đăng nhập thành công/thất bại, chỉnh sửa/xóa biểu ghi.
# 3. Tra cứu nâng cao: Đa tiêu chí (người thực hiện, phân hệ, hành động, ngày giờ, từ khóa).
# 4. Chi tiết thay đổi (Diff Viewer): So sánh giá trị trước và sau khi chỉnh sửa.
# 5. Xuất báo cáo kiểm toán: Excel / CSV chuẩn UTF-8 BOM hiển thị chuẩn tiếng Việt.
# 6. Tích hợp mở rộng: Hỗ trợ ghi nhận log từ DRM Service và SSO qua API nội bộ.
# ==============================================================================

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use JSON qw( to_json );
use POSIX qw( strftime );
use Text::CSV::Encoded;
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;
use C4::Log qw( logaction );
use Encode qw( decode_utf8 encode_utf8 is_utf8 );

sub _utf8_str {
    my ($val) = @_;
    return "" unless defined $val;
    return $val if utf8::is_utf8($val);
    return eval { decode_utf8($val) } // $val;
}

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;

my ($template, $borrowernumber, $cookie) = get_template_and_user(
    {
        template_name   => "tools/audit-logs.tt",
        query           => $cgi,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => [
            { tools => "audit_logs" },
            { tools => "audit_export" },
            { tools => "view_system_logs" },
        ],
    }
);

my $op = $cgi->param("op") || "view";
$op =~ s/^cud-//;

# ==============================================================================
# 1. API: THỐNG KÊ TỔNG QUAN (LIVE DASHBOARD STATS)
# ==============================================================================
if ($op eq "stats") {
    print $cgi->header(
        -type    => "application/json; charset=utf-8",
        -expires => "now",
    );

    # Thống kê hôm nay
    my ($total_today) = $dbh->selectrow_array(
        "SELECT COUNT(*) FROM action_logs WHERE timestamp >= CURDATE()"
    );
    $total_today //= 0;

    my ($logins_today) = $dbh->selectrow_array(
        "SELECT COUNT(*) FROM action_logs WHERE timestamp >= CURDATE() AND (action LIKE '%LOGIN%' OR action LIKE '%AUTH%')"
    );
    $logins_today //= 0;

    my ($mods_deletes_today) = $dbh->selectrow_array(
        "SELECT COUNT(*) FROM action_logs WHERE timestamp >= CURDATE() AND action IN ('MODIFY', 'DELETE', 'CHANGE PASS', 'RESET PASS')"
    );
    $mods_deletes_today //= 0;

    my ($circ_today) = $dbh->selectrow_array(
        "SELECT COUNT(*) FROM action_logs WHERE timestamp >= CURDATE() AND (module = 'CIRCULATION' OR action IN ('ISSUE', 'RETURN', 'RENEW'))"
    );
    $circ_today //= 0;

    # Phân bổ theo phân hệ hôm nay
    my $sth_mod = $dbh->prepare(
        "SELECT module, COUNT(*) as cnt FROM action_logs WHERE timestamp >= CURDATE() GROUP BY module ORDER BY cnt DESC LIMIT 8"
    );
    $sth_mod->execute();
    my @by_module;
    while (my $r = $sth_mod->fetchrow_hashref) {
        push @by_module, {
            module => $r->{module} || 'KHAC',
            count  => int($r->{cnt} || 0)
        };
    }

    # Top 5 người dùng thao tác nhiều nhất trong 7 ngày
    my $sth_users = $dbh->prepare(
        "SELECT al.user, " .
        "COALESCE(CONCAT(COALESCE(u.surname,''), ' ', COALESCE(u.firstname,'')), CONCAT('User #', al.user)) as name, " .
        "COALESCE(u.cardnumber, '') as cardnumber, " .
        "COUNT(*) as cnt " .
        "FROM action_logs al " .
        "LEFT JOIN borrowers u ON al.user = u.borrowernumber " .
        "WHERE al.timestamp >= DATE_SUB(NOW(), INTERVAL 7 DAY) AND al.user > 0 " .
        "GROUP BY al.user, name, cardnumber " .
        "ORDER BY cnt DESC LIMIT 5"
    );
    $sth_users->execute();
    my @top_users;
    while (my $r = $sth_users->fetchrow_hashref) {
        push @top_users, {
            user_id    => int($r->{user}),
            name       => $r->{name},
            cardnumber => $r->{cardnumber},
            count      => int($r->{cnt})
        };
    }

    print to_json({
        success            => 1,
        total_today        => int($total_today),
        logins_today       => int($logins_today),
        mods_deletes_today => int($mods_deletes_today),
        circ_today         => int($circ_today),
        by_module          => \@by_module,
        top_users          => \@top_users,
    });
    exit;
}

# ==============================================================================
# 2. API: LẤY DANH SÁCH NHẬT KÝ SERVER-SIDE (DATATABLES PAGINATION & FILTER)
# ==============================================================================
if ($op eq "list") {
    print $cgi->header(
        -type    => "application/json; charset=utf-8",
        -expires => "now",
    );

    my $draw   = int($cgi->param("draw") || 1);
    my $start  = int($cgi->param("start") || 0);
    my $length = int($cgi->param("length") || 25);
    $length = 100 if $length > 100;
    $length = 10  if $length < 1;

    my $filter_module    = $cgi->param("module") || "";
    my $filter_action    = $cgi->param("action") || "";
    my $filter_interface = $cgi->param("interface") || "";
    my $filter_user      = $cgi->param("user_search") || "";
    my $filter_from      = $cgi->param("date_from") || "";
    my $filter_to        = $cgi->param("date_to") || "";
    my $filter_keyword   = $cgi->param("keyword") || "";
    my $filter_object    = $cgi->param("object_id") || "";

    my @where_clauses;
    my @params;

    if ($filter_module ne "" && $filter_module ne "ALL") {
        push @where_clauses, "al.module = ?";
        push @params, $filter_module;
    }

    if ($filter_action ne "" && $filter_action ne "ALL") {
        push @where_clauses, "al.action = ?";
        push @params, $filter_action;
    }

    if ($filter_interface ne "" && $filter_interface ne "ALL") {
        push @where_clauses, "al.interface = ?";
        push @params, $filter_interface;
    }

    if ($filter_object ne "") {
        push @where_clauses, "al.object = ?";
        push @params, int($filter_object);
    }

    if ($filter_user ne "") {
        push @where_clauses, "(al.user = ? OR u.cardnumber LIKE ? OR u.surname LIKE ? OR u.firstname LIKE ? OR CONCAT(COALESCE(u.surname,''), ' ', COALESCE(u.firstname,'')) LIKE ?)";
        my $user_num = int($filter_user);
        my $wild = "%$filter_user%";
        push @params, ($user_num, $wild, $wild, $wild, $wild);
    }

    if ($filter_from ne "") {
        if ($filter_from =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
            push @where_clauses, "al.timestamp >= ?";
            push @params, "$filter_from 00:00:00";
        } elsif ($filter_from =~ /^(\d{1,2})\/(\d{1,2})\/(\d{4})$/) {
            my ($d, $m, $y) = ($1, $2, $3);
            push @where_clauses, "al.timestamp >= ?";
            push @params, sprintf("%04d-%02d-%02d 00:00:00", $y, $m, $d);
        }
    }

    if ($filter_to ne "") {
        if ($filter_to =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
            push @where_clauses, "al.timestamp <= ?";
            push @params, "$filter_to 23:59:59";
        } elsif ($filter_to =~ /^(\d{1,2})\/(\d{1,2})\/(\d{4})$/) {
            my ($d, $m, $y) = ($1, $2, $3);
            push @where_clauses, "al.timestamp <= ?";
            push @params, sprintf("%04d-%02d-%02d 23:59:59", $y, $m, $d);
        }
    }

    if ($filter_keyword ne "") {
        push @where_clauses, "(al.info LIKE ? OR al.diff LIKE ?)";
        my $kw_wild = "%$filter_keyword%";
        push @params, ($kw_wild, $kw_wild);
    }

    my $where_sql = @where_clauses ? "WHERE " . join(" AND ", @where_clauses) : "";

    # 1. Tổng số dòng không lọc
    my ($records_total) = $dbh->selectrow_array("SELECT COUNT(*) FROM action_logs");

    # 2. Tổng số dòng sau khi lọc
    my $count_sql = "SELECT COUNT(*) FROM action_logs al " .
                    "LEFT JOIN borrowers u ON al.user = u.borrowernumber " .
                    $where_sql;
    my $sth_c = $dbh->prepare($count_sql);
    $sth_c->execute(@params);
    my ($records_filtered) = $sth_c->fetchrow_array;
    $records_filtered //= 0;

    # 3. Lấy dữ liệu trang hiện tại
    my $data_sql = qq{
        SELECT 
            al.action_id,
            al.timestamp,
            al.user AS user_id,
            CONCAT(COALESCE(u.surname,''), ' ', COALESCE(u.firstname,'')) AS user_name,
            u.cardnumber AS user_cardnumber,
            u.categorycode AS user_category,
            al.module,
            al.action,
            al.object,
            al.info,
            al.interface,
            al.diff,
            -- Đối tượng bạn đọc nếu có
            CONCAT(COALESCE(p.surname,''), ' ', COALESCE(p.firstname,'')) AS target_patron_name,
            p.cardnumber AS target_patron_cardnumber,
            -- Đối tượng sách nếu có
            b.title AS target_biblio_title
        FROM action_logs al
        LEFT JOIN borrowers u ON al.user = u.borrowernumber
        LEFT JOIN borrowers p ON (al.module IN ('MEMBERS', 'CIRCULATION', 'HOLDS', 'FINES') AND al.object = p.borrowernumber)
        LEFT JOIN biblio b ON (al.module IN ('CATALOGUING', 'CIRCULATION', 'HOLDS') AND al.object = b.biblionumber)
        $where_sql
        ORDER BY al.action_id DESC
        LIMIT ?, ?
    };

    my $sth_d = $dbh->prepare($data_sql);
    $sth_d->execute(@params, $start, $length);

    my @rows;
    while (my $r = $sth_d->fetchrow_hashref) {
        my $user_display = "";
        my $user_sub     = "";
        my $user_link    = "";
        my $is_system    = 0;

        my $user_name           = _utf8_str($r->{user_name});
        my $target_patron_name  = _utf8_str($r->{target_patron_name});
        my $target_biblio_title = _utf8_str($r->{target_biblio_title});
        my $info                = _utf8_str($r->{info});
        my $diff                = _utf8_str($r->{diff});

        if ($r->{user_id} && $r->{user_id} > 0) {
            $user_display = $user_name || ("Thủ thư #" . $r->{user_id});
            $user_sub     = $r->{user_cardnumber} ? "Mã thẻ: " . $r->{user_cardnumber} : "ID: #" . $r->{user_id};
            $user_link    = "/cgi-bin/koha/members/moremember.pl?borrowernumber=" . $r->{user_id};
        } else {
            if ($r->{interface} eq 'opac' && $target_patron_name && $target_patron_name =~ /\S/) {
                $user_display = $target_patron_name . " (Bạn đọc)";
                $user_sub     = $r->{target_patron_cardnumber} ? "Mã thẻ: " . $r->{target_patron_cardnumber} : "OPAC";
                $user_link    = "/cgi-bin/koha/members/moremember.pl?borrowernumber=" . ($r->{object} || 0);
            } else {
                $user_display = "Hệ thống tự động";
                $user_sub     = $r->{interface} ? uc($r->{interface}) : "Cron/Script";
                $is_system    = 1;
            }
        }

        # Đối tượng tác động (Target Object)
        my $target_label = "";
        my $target_link  = "";
        if ($target_patron_name && $target_patron_name =~ /\S/) {
            $target_label = "Bạn đọc: " . $target_patron_name;
            if ($r->{target_patron_cardnumber}) {
                $target_label .= " (" . $r->{target_patron_cardnumber} . ")";
            }
            $target_link  = "/cgi-bin/koha/members/moremember.pl?borrowernumber=" . $r->{object};
        } elsif ($target_biblio_title && $target_biblio_title =~ /\S/) {
            $target_label = "Tài liệu: " . $target_biblio_title;
            $target_link  = "/cgi-bin/koha/catalogue/detail.pl?biblionumber=" . $r->{object};
        } elsif ($r->{object}) {
            if ($r->{module} eq 'SYSTEMPREFERENCE') {
                $target_label = "Cấu hình: " . $info;
                $target_link  = "/cgi-bin/koha/admin/preferences.pl?op=search&searchfield=" . $info;
            } elsif ($r->{module} eq 'GRADUATION') {
                $target_label = "Đợt xét TN #" . $r->{object};
                $target_link  = "/cgi-bin/koha/tools/graduation.pl?batch_id=" . $r->{object};
            } elsif ($r->{module} eq 'PORTAL_NEWS') {
                $target_label = "Trang/Bài viết #" . $r->{object};
                $target_link  = "/cgi-bin/koha/tools/portal-news.pl?op=add_form&id=" . $r->{object};
            } else {
                $target_label = "ID Đối tượng #" . $r->{object};
            }
        }

        # Định dạng thời gian
        my $ts = $r->{timestamp} || "";
        my ($date_part, $time_part) = split(/ /, $ts);
        my $formatted_time = $ts;
        if ($date_part =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
            $formatted_time = "$3/$2/$1 " . ($time_part || "");
        }

        # Nhãn tiếng Việt cho module
        my %mod_map = (
            'GRADUATION'       => { name => 'Xét tốt nghiệp', class => 'mod-grad', icon => 'fa-graduation-cap' },
            'PORTAL_NEWS'      => { name => 'Trang công khai', class => 'mod-portal', icon => 'fa-newspaper-o' },
            'PUBLIC_PORTAL'    => { name => 'Trang công khai', class => 'mod-portal', icon => 'fa-globe' },
            'MEMBERS'          => { name => 'Bạn đọc', class => 'mod-patrons', icon => 'fa-id-card' },
            'CIRCULATION'      => { name => 'Lưu thông', class => 'mod-circ', icon => 'fa-exchange' },
            'CATALOGUING'      => { name => 'Biên mục', class => 'mod-cat', icon => 'fa-book' },
            'SYSTEMPREFERENCE' => { name => 'Cấu hình HT', class => 'mod-sys', icon => 'fa-gears' },
            'AUTH'             => { name => 'Xác thực & SSO', class => 'mod-auth', icon => 'fa-key' },
            'DRM'              => { name => 'Thư viện số DRM', class => 'mod-drm', icon => 'fa-shield' },
            'REPORTS'          => { name => 'Báo cáo', class => 'mod-rep', icon => 'fa-pie-chart' },
            'AUTHORITIES'      => { name => 'Từ điển', class => 'mod-authval', icon => 'fa-link' },
            'FINES'            => { name => 'Tiền phạt', class => 'mod-fines', icon => 'fa-money' },
            'NOTICES'          => { name => 'Thông báo', class => 'mod-notices', icon => 'fa-envelope' },
            'CRONJOBS'         => { name => 'Tác vụ ngầm', class => 'mod-cron', icon => 'fa-clock-o' },
            'SCRIPTS'          => { name => 'Tập lệnh', class => 'mod-script', icon => 'fa-code' },
            'ACQUISITIONS'     => { name => 'Bổ sung', class => 'mod-acq', icon => 'fa-shopping-cart' },
            'SUGGESTIONS'      => { name => 'Đề xuất', class => 'mod-sug', icon => 'fa-lightbulb-o' },
            'NEWS'             => { name => 'Tin tức/Trang', class => 'mod-news', icon => 'fa-globe' },
        );

        my $m_meta = $mod_map{$r->{module}} || { name => $r->{module} || 'Khác', class => 'mod-default', icon => 'fa-cube' };

        # Nhãn tiếng Việt cho action
        my %act_map = (
            'ADD'              => { name => 'Thêm mới', badge => 'badge-success' },
            'CREATE'           => { name => 'Tạo mới', badge => 'badge-success' },
            'MODIFY'           => { name => 'Chỉnh sửa', badge => 'badge-primary' },
            'DELETE'           => { name => 'Xóa bỏ', badge => 'badge-danger' },
            'ISSUE'            => { name => 'Cho mượn', badge => 'badge-info' },
            'RETURN'           => { name => 'Nhận trả', badge => 'badge-success' },
            'RENEW'            => { name => 'Gia hạn', badge => 'badge-info' },
            'RENEWAL'          => { name => 'Gia hạn', badge => 'badge-info' },
            'CHANGE PASS'      => { name => 'Đổi mật khẩu', badge => 'badge-warning' },
            'RESET PASS'       => { name => 'Đặt lại MK', badge => 'badge-warning' },
            'LOGIN'            => { name => 'Đăng nhập', badge => 'badge-success' },
            'LOGIN_FAILED'     => { name => 'Đăng nhập lỗi', badge => 'badge-danger' },
            'LOGOUT'           => { name => 'Đăng xuất', badge => 'badge-secondary' },
            'STATUS_CHANGE'    => { name => 'Đổi trạng thái', badge => 'badge-info' },
            'BATCH_CREATE'     => { name => 'Tạo đợt', badge => 'badge-success' },
            'BATCH_IMPORT'     => { name => 'Nạp sinh viên', badge => 'badge-info' },
            'BATCH_DELETE'     => { name => 'Xóa đợt', badge => 'badge-danger' },
            'BATCH_LOCK'       => { name => 'Khóa thẻ TN', badge => 'badge-danger' },
            'BATCH_UNLOCK'     => { name => 'Mở khóa thẻ', badge => 'badge-success' },
            'SEND_REMINDER'    => { name => 'Gửi nhắc nợ', badge => 'badge-warning' },
        );

        my $a_meta = $act_map{$r->{action}} || { name => $r->{action} || 'Thao tác', badge => 'badge-secondary' };

        # Interface
        my %if_map = (
            'intranet'    => { name => 'Cán bộ (Intranet)', badge => 'badge-intranet' },
            'opac'        => { name => 'Bạn đọc (OPAC)', badge => 'badge-opac' },
            'api'         => { name => 'API Kết nối', badge => 'badge-api' },
            'cron'        => { name => 'Tiến trình ngầm', badge => 'badge-cron' },
            'commandline' => { name => 'Terminal', badge => 'badge-cmd' },
            'sip'         => { name => 'Máy trạm SIP', badge => 'badge-sip' },
        );

        my $if_meta = $if_map{lc($r->{interface} || '')} || { name => uc($r->{interface} || 'HT'), badge => 'badge-default' };

        push @rows, {
            action_id        => int($r->{action_id}),
            timestamp        => $formatted_time,
            timestamp_raw    => $r->{timestamp},
            user_display     => $user_display,
            user_sub         => $user_sub,
            user_link        => $user_link,
            is_system        => $is_system,
            module           => $r->{module} || "",
            module_name      => $m_meta->{name},
            module_class     => $m_meta->{class},
            module_icon      => $m_meta->{icon},
            action           => $r->{action} || "",
            action_name      => $a_meta->{name},
            action_badge     => $a_meta->{badge},
            interface        => $r->{interface} || "",
            interface_name   => $if_meta->{name},
            interface_badge  => $if_meta->{badge},
            target_label     => $target_label,
            target_link      => $target_link,
            info             => $info,
            has_diff         => ($diff && length($diff) > 2) ? 1 : 0,
            diff             => $diff,
        };
    }

    print to_json({
        draw            => $draw,
        recordsTotal    => int($records_total || 0),
        recordsFiltered => int($records_filtered || 0),
        data            => \@rows,
    });
    exit;
}

# ==============================================================================
# 3. API: XUẤT BÁO CÁO EXCEL / CSV CHUẨN UTF-8 BOM
# ==============================================================================
if ($op eq "export_csv") {
    my $filter_module    = $cgi->param("module") || "";
    my $filter_action    = $cgi->param("action") || "";
    my $filter_interface = $cgi->param("interface") || "";
    my $filter_user      = $cgi->param("user_search") || "";
    my $filter_from      = $cgi->param("date_from") || "";
    my $filter_to        = $cgi->param("date_to") || "";
    my $filter_keyword   = $cgi->param("keyword") || "";
    my $filter_object    = $cgi->param("object_id") || "";

    my @where_clauses;
    my @params;

    if ($filter_module ne "" && $filter_module ne "ALL") {
        push @where_clauses, "al.module = ?";
        push @params, $filter_module;
    }
    if ($filter_action ne "" && $filter_action ne "ALL") {
        push @where_clauses, "al.action = ?";
        push @params, $filter_action;
    }
    if ($filter_interface ne "" && $filter_interface ne "ALL") {
        push @where_clauses, "al.interface = ?";
        push @params, $filter_interface;
    }
    if ($filter_object ne "") {
        push @where_clauses, "al.object = ?";
        push @params, int($filter_object);
    }
    if ($filter_user ne "") {
        push @where_clauses, "(al.user = ? OR u.cardnumber LIKE ? OR u.surname LIKE ? OR u.firstname LIKE ? OR CONCAT(COALESCE(u.surname,''), ' ', COALESCE(u.firstname,'')) LIKE ?)";
        my $user_num = int($filter_user);
        my $wild = "%$filter_user%";
        push @params, ($user_num, $wild, $wild, $wild, $wild);
    }
    if ($filter_from ne "") {
        if ($filter_from =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
            push @where_clauses, "al.timestamp >= ?";
            push @params, "$filter_from 00:00:00";
        } elsif ($filter_from =~ /^(\d{1,2})\/(\d{1,2})\/(\d{4})$/) {
            push @where_clauses, "al.timestamp >= ?";
            push @params, sprintf("%04d-%02d-%02d 00:00:00", $3, $2, $1);
        }
    }
    if ($filter_to ne "") {
        if ($filter_to =~ /^(\d{4})-(\d{2})-(\d{2})$/) {
            push @where_clauses, "al.timestamp <= ?";
            push @params, "$filter_to 23:59:59";
        } elsif ($filter_to =~ /^(\d{1,2})\/(\d{1,2})\/(\d{4})$/) {
            push @where_clauses, "al.timestamp <= ?";
            push @params, sprintf("%04d-%02d-%02d 23:59:59", $3, $2, $1);
        }
    }
    if ($filter_keyword ne "") {
        push @where_clauses, "(al.info LIKE ? OR al.diff LIKE ?)";
        my $kw_wild = "%$filter_keyword%";
        push @params, ($kw_wild, $kw_wild);
    }

    my $where_sql = @where_clauses ? "WHERE " . join(" AND ", @where_clauses) : "";

    my $query = qq{
        SELECT 
            al.action_id,
            al.timestamp,
            al.user AS user_id,
            CONCAT(COALESCE(u.surname,''), ' ', COALESCE(u.firstname,'')) AS user_name,
            u.cardnumber AS user_cardnumber,
            al.module,
            al.action,
            al.object,
            al.info,
            al.interface,
            CONCAT(COALESCE(p.surname,''), ' ', COALESCE(p.firstname,'')) AS target_patron_name,
            p.cardnumber AS target_patron_cardnumber,
            b.title AS target_biblio_title
        FROM action_logs al
        LEFT JOIN borrowers u ON al.user = u.borrowernumber
        LEFT JOIN borrowers p ON (al.module IN ('MEMBERS', 'CIRCULATION', 'HOLDS', 'FINES') AND al.object = p.borrowernumber)
        LEFT JOIN biblio b ON (al.module IN ('CATALOGUING', 'CIRCULATION', 'HOLDS') AND al.object = b.biblionumber)
        $where_sql
        ORDER BY al.action_id DESC
        LIMIT 5000
    };

    my $sth = $dbh->prepare($query);
    $sth->execute(@params);

    my $timestamp_str = strftime("%Y%m%d_%H%M%S", localtime);
    my $filename = "nhat_ky_he_thong_FTULIB_" . $timestamp_str . ".csv";

    print $cgi->header(
        -type       => "text/csv; charset=utf-8",
        -attachment => $filename,
        -expires    => "now",
    );

    # Ghi UTF-8 BOM để Excel hiển thị tiếng Việt chính xác 100%
    print "\xEF\xBB\xBF";

    my $csv = Text::CSV::Encoded->new({
        encoding_out => 'utf8',
        sep_char     => ',',
        eol          => "\n",
        binary       => 1
    });

    # Tiêu đề cột tiếng Việt
    $csv->combine(
        "Mã nhật ký",
        "Thời gian",
        "Người thực hiện",
        "Mã thẻ thủ thư/bạn đọc",
        "Phân hệ",
        "Hành động",
        "Mã đối tượng",
        "Đối tượng tác động",
        "Giao diện",
        "Thông tin chi tiết"
    );
    print $csv->string();

    while (my $r = $sth->fetchrow_hashref) {
        my $user_disp = $r->{user_name} || ($r->{user_id} ? "Thủ thư #" . $r->{user_id} : "Hệ thống");
        my $target_disp = "";
        if ($r->{target_patron_name} && $r->{target_patron_name} =~ /\S/) {
            $target_disp = "Bạn đọc: " . $r->{target_patron_name} . ($r->{target_patron_cardnumber} ? " (" . $r->{target_patron_cardnumber} . ")" : "");
        } elsif ($r->{target_biblio_title} && $r->{target_biblio_title} =~ /\S/) {
            $target_disp = "Sách: " . $r->{target_biblio_title};
        } elsif ($r->{object}) {
            $target_disp = "ID #" . $r->{object};
        }

        $csv->combine(
            $r->{action_id},
            $r->{timestamp},
            $user_disp,
            $r->{user_cardnumber} || "",
            $r->{module} || "",
            $r->{action} || "",
            $r->{object} || "",
            $target_disp,
            uc($r->{interface} || ""),
            $r->{info} || ""
        );
        print $csv->string();
    }
    exit;
}

# ==============================================================================
# 4. GIAO DIỆN CHÍNH (HTML VIEW)
# ==============================================================================
# Lấy danh sách module và action hiện có trong DB để sinh dropdown bộ lọc
my $modules_ref = $dbh->selectcol_arrayref(
    "SELECT DISTINCT module FROM action_logs WHERE module IS NOT NULL AND module != '' ORDER BY module"
);

my $actions_ref = $dbh->selectcol_arrayref(
    "SELECT DISTINCT action FROM action_logs WHERE action IS NOT NULL AND action != '' ORDER BY action"
);

$template->param(
    available_modules => $modules_ref || [],
    available_actions => $actions_ref || [],
    page_title        => "Nhật ký Hệ thống & Giám sát An ninh",
);

output_html_with_http_headers $cgi, $cookie, $template->output;
