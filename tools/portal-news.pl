#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;

my ($template, $borrowernumber, $cookie) = get_template_and_user(
    {
        template_name   => "tools/portal-news.tt",
        query           => $cgi,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => { tools => "edit_additional_contents" },
    }
);

my $op = $cgi->param("op") || "list";
my $msg = $cgi->param("msg") || "";

if (($op eq "upload_image" || $op eq "cud-upload_image")) {
    use JSON;
    use MIME::Base64;
    my $json = JSON->new->utf8;
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $target_dir = "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/images/portal_uploads";
    mkdir $target_dir unless -d $target_dir;

    my $base64_data = $cgi->param("base64_data") || "";
    if ($base64_data =~ /data:image\/(\w+);base64,(.+)$/s) {
        my $ext = lc($1);
        my $raw_b64 = $2;
        $raw_b64 =~ s/\s/+/g;
        $ext = "jpg" if $ext eq "jpeg";
        $ext = "jpg" unless $ext =~ /^(jpg|jpeg|png|gif|webp)$/;
        my $safe_name = "thumb_" . time() . "_" . int(rand(100000)) . ".$ext";
        my $target_path = "$target_dir/$safe_name";
        my $decoded = MIME::Base64::decode_base64($raw_b64);
        if ($decoded && open(my $out, '>', $target_path)) {
            binmode $out;
            print $out $decoded;
            close $out;
            print $json->encode({ success => 1, url => "/opac-tmpl/bootstrap/images/portal_uploads/$safe_name" });
            exit;
        }
    }

    my $upload_fh = $cgi->upload("image_file");
    if ($upload_fh) {
        my $filename = $cgi->param("image_file") || "upload.jpg";
        my ($ext) = $filename =~ /(\.[^.]+)$/;
        $ext = lc($ext || ".jpg");
        $ext = ".jpg" unless $ext =~ /^\.(jpg|jpeg|png|gif|webp)$/;
        my $safe_name = "thumb_" . time() . "_" . int(rand(100000)) . $ext;
        my $target_path = "$target_dir/$safe_name";

        if (open(my $out, '>', $target_path)) {
            binmode $out;
            binmode $upload_fh;
            my $buffer;
            while (my $bytes = read($upload_fh, $buffer, 4096)) {
                print $out $buffer;
            }
            close $out;
            print $json->encode({ success => 1, url => "/opac-tmpl/bootstrap/images/portal_uploads/$safe_name" });
            exit;
        }
    }

    print $json->encode({ success => 0, error => "Không thể lưu hình ảnh lên máy chủ." });
    exit;
}

if (($op eq "upload_pdf" || $op eq "cud-upload_pdf" || $op eq "upload_file" || $op eq "cud-upload_file")) {
    use JSON;
    use MIME::Base64;
    my $json = JSON->new->utf8;
    print $cgi->header( -type => "application/json", -charset => "utf-8" );

    my $target_dir = "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/images/portal_uploads";
    mkdir $target_dir unless -d $target_dir;

    my $upload_fh = $cgi->upload("pdf_file") || $cgi->upload("file");
    if ($upload_fh) {
        my $orig_name = $cgi->param("file_name") || $cgi->param("pdf_file") || $cgi->param("file") || "tailieu.pdf";
        $orig_name =~ s/.*[\/\\]//; # strip path
        my ($base_name) = $orig_name =~ /^(.*?)(?:\.[^.]+)?$/;
        $base_name ||= "Tài liệu PDF";

        my $safe_name = "doc_" . time() . "_" . int(rand(100000)) . ".pdf";
        my $target_path = "$target_dir/$safe_name";

        if (open(my $out, '>', $target_path)) {
            binmode $out;
            binmode $upload_fh;
            my $buffer;
            my $total_bytes = 0;
            while (my $bytes = read($upload_fh, $buffer, 8192)) {
                print $out $buffer;
                $total_bytes += $bytes;
            }
            close $out;

            my $size_str = sprintf("%.1f MB", $total_bytes / (1024 * 1024));
            if ($total_bytes < 1024 * 1024) {
                $size_str = sprintf("%.0f KB", $total_bytes / 1024);
            }

            print $json->encode({
                success       => 1,
                url           => "/opac-tmpl/bootstrap/images/portal_uploads/$safe_name",
                filename      => $safe_name,
                original_name => $orig_name,
                title         => $base_name,
                size_str      => $size_str,
                bytes         => $total_bytes
            });
            exit;
        }
    }

    my $base64_data = $cgi->param("base64_data") || "";
    if ($base64_data =~ /data:(?:application\/pdf|application\/octet-stream);base64,(.+)$/s || ($base64_data && $base64_data !~ /[^A-Za-z0-9+\/=\s]/)) {
        my $raw_b64 = $1 || $base64_data;
        $raw_b64 =~ s/\s/+/g;
        my $orig_name = $cgi->param("file_name") || "tailieu.pdf";
        $orig_name =~ s/.*[\/\\]//;
        my ($base_name) = $orig_name =~ /^(.*?)(?:\.[^.]+)?$/;
        $base_name ||= "Tài liệu PDF";

        my $safe_name = "doc_" . time() . "_" . int(rand(100000)) . ".pdf";
        my $target_path = "$target_dir/$safe_name";
        my $decoded = MIME::Base64::decode_base64($raw_b64);
        if ($decoded && open(my $out, '>', $target_path)) {
            binmode $out;
            print $out $decoded;
            close $out;

            my $total_bytes = length($decoded);
            my $size_str = sprintf("%.1f MB", $total_bytes / (1024 * 1024));
            if ($total_bytes < 1024 * 1024) {
                $size_str = sprintf("%.0f KB", $total_bytes / 1024);
            }

            print $json->encode({
                success       => 1,
                url           => "/opac-tmpl/bootstrap/images/portal_uploads/$safe_name",
                filename      => $safe_name,
                original_name => $orig_name,
                title         => $base_name,
                size_str      => $size_str,
                bytes         => $total_bytes
            });
            exit;
        }
    }

    print $json->encode({ success => 0, error => "Không thể tải lên file PDF. Vui lòng thử lại." });
    exit;
}

if ($op eq "get_db" || $op eq "get_banner") {
    use JSON;
    my $id = int($cgi->param("id") || 0);
    my $sth = $dbh->prepare("SELECT * FROM koha_portal_posts WHERE id = ?");
    $sth->execute($id);
    my $row = $sth->fetchrow_hashref;
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    print JSON::to_json($row || {});
    exit;
}

if (($op eq "delete" || $op eq "cud-delete")) {
    my $id = int($cgi->param("id") || 0);
    my $section = $cgi->param("section") || "";
    if ($id > 0) {
        my $sth = $dbh->prepare("SELECT post_type FROM koha_portal_posts WHERE id = ?");
        $sth->execute($id);
        my ($pt) = $sth->fetchrow_array;
        $section = "database" if ($pt && $pt eq "database");
        $section = "banner" if ($pt && $pt eq "banner");
        $dbh->do("DELETE FROM koha_portal_posts WHERE id = ?", undef, $id);
    }
    print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?op=list&msg=deleted" . ($section ? "&section=$section" : ""));
    exit;
}

if (($op eq "toggle_status" || $op eq "cud-toggle_status")) {
    my $id = int($cgi->param("id") || 0);
    my $section = $cgi->param("section") || "";
    if ($id > 0) {
        my $sth = $dbh->prepare("SELECT status, post_type FROM koha_portal_posts WHERE id = ?");
        $sth->execute($id);
        my ($curr, $pt) = $sth->fetchrow_array;
        $section = "database" if ($pt && $pt eq "database");
        $section = "banner" if ($pt && $pt eq "banner");
        my $new_status = ($curr eq "published") ? "draft" : "published";
        $dbh->do("UPDATE koha_portal_posts SET status = ? WHERE id = ?", undef, $new_status, $id);
    }
    print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?op=list&msg=status_updated" . ($section ? "&section=$section" : ""));
    exit;
}

if (($op eq "toggle_banner_text" || $op eq "cud-toggle_banner_text")) {
    my $id = int($cgi->param("id") || 0);
    if ($id > 0) {
        my $sth = $dbh->prepare("SELECT content FROM koha_portal_posts WHERE id = ?");
        $sth->execute($id);
        my ($curr) = $sth->fetchrow_array;
        my $new_content = ($curr && $curr eq "show_text") ? "" : "show_text";
        my $new_feat = ($new_content eq "show_text") ? 1 : 0;
        $dbh->do("UPDATE koha_portal_posts SET content = ?, is_featured = ? WHERE id = ?", undef, $new_content, $new_feat, $id);
    }
    print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?op=list&section=banner&msg=banner_text_updated");
    exit;
}

if (($op eq "save" || $op eq "cud-save" || $op eq "save_db" || $op eq "cud-save_db" || $op eq "save_banner" || $op eq "cud-save_banner")) {
    my $id                  = int($cgi->param("id") || 0);
    my $sort_order          = int($cgi->param("sort_order") || 1);
    my $post_type           = $cgi->param("post_type") || ($op =~ /_db/ ? "database" : ($op =~ /_banner/ ? "banner" : "news"));
    my $title               = $cgi->param("title");
    my $excerpt             = $cgi->param("excerpt") || "";
    my $classification      = $cgi->param("classification") || ($post_type eq 'database' ? "CSDL THƯƠNG MẠI" : ($post_type eq 'banner' ? "THƯ VIỆN FTU" : ""));
    my $access_instructions = $cgi->param("access_instructions") || "";
    my $db_user             = $cgi->param("db_user") || "";
    my $db_pass             = $cgi->param("db_pass") || "";
    my $support_link        = $cgi->param("support_link") || "";
    my $content             = "";
    my $is_featured         = 0;

    if ($post_type eq 'banner') {
        # Checkbox sends 'show_text' if checked; undef/empty if unchecked
        my $show_text = $cgi->param("show_text") // $cgi->param("content");
        $content = ($show_text && ($show_text eq 'show_text' || $show_text eq '1' || $show_text eq 'on')) ? 'show_text' : '';
        $is_featured = ($content eq 'show_text') ? 1 : 0;
        if (!defined $title || $title =~ /^\s*$/) {
            $title = "Banner " . ($sort_order || $id || "FTU");
        }
    } else {
        $title = "Chưa đặt tiêu đề" unless defined $title && $title =~ /\S/;
        $content = $cgi->param("content") || $excerpt || "";
        $is_featured = int($cgi->param("is_featured") || 0);
    }

    my $featured_image      = $cgi->param("featured_image") || "";
    my $author_name         = $cgi->param("author_name") || "Thư viện ĐH Ngoại thương";
    my $status              = $cgi->param("status") || "published";
    
    my $event_start  = $cgi->param("event_start");
    $event_start     = undef if defined $event_start && $event_start eq "";
    
    my $event_end    = $cgi->param("event_end");
    $event_end       = undef if defined $event_end && $event_end eq "";
    
    my $event_location = $cgi->param("event_location") || undef;
    my $event_reg_link = $cgi->param("event_reg_link") || $support_link || undef;
    $support_link    ||= $event_reg_link if $event_reg_link;
    my $event_tag      = $cgi->param("event_tag") || ($post_type eq 'database' ? "Nội bộ & Từ xa" : "Sắp diễn ra");
    my $views_count    = int($cgi->param("views_count") || 0);

    if ($id > 0) {
        my $sql = "UPDATE koha_portal_posts SET 
            sort_order = ?, post_type = ?, title = ?, excerpt = ?, classification = ?,
            access_instructions = ?, db_user = ?, db_pass = ?, support_link = ?,
            content = ?, featured_image = ?, author_name = ?, status = ?, is_featured = ?,
            event_start = ?, event_end = ?, event_location = ?, event_reg_link = ?,
            event_tag = ?, views_count = ?
            WHERE id = ?";
        $dbh->do($sql, undef, 
            $sort_order, $post_type, $title, $excerpt, $classification,
            $access_instructions, $db_user, $db_pass, $support_link,
            $content, $featured_image, $author_name, $status, $is_featured,
            $event_start, $event_end, $event_location, $event_reg_link,
            $event_tag, $views_count, $id
        );
    } else {
        my $sql = "INSERT INTO koha_portal_posts 
            (sort_order, post_type, title, excerpt, classification, access_instructions, db_user, db_pass, support_link, content, featured_image, author_name, status, is_featured, event_start, event_end, event_location, event_reg_link, event_tag, views_count)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        $dbh->do($sql, undef,
            $sort_order, $post_type, $title, $excerpt, $classification,
            $access_instructions, $db_user, $db_pass, $support_link,
            $content, $featured_image, $author_name, $status, $is_featured,
            $event_start, $event_end, $event_location, $event_reg_link,
            $event_tag, $views_count
        );
    }
    my $redirect_url = "/cgi-bin/koha/tools/portal-news.pl?op=list&msg=saved";
    $redirect_url .= "&section=database" if ($post_type eq "database");
    $redirect_url .= "&section=banner" if ($post_type eq "banner");
    print $cgi->redirect($redirect_url);
    exit;
}

if (($op eq "save_footer" || $op eq "cud-save_footer")) {
    my $cfg_file = "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/vi-VN/includes/ftu-brand-config.inc";
    my %new_vals = (
        # 1. Liên kết nhanh (5 liên kết theo yêu cầu)
        title_home             => $cgi->param("title_home") || "Trang chủ Thư viện",
        link_home              => $cgi->param("link_home") || "/cgi-bin/ftu/opac-main.pl",
        title_advsearch        => $cgi->param("title_advsearch") || "Tìm kiếm tài liệu nâng cao",
        link_advsearch         => $cgi->param("link_advsearch") || "/cgi-bin/ftu/opac-search.pl",
        title_databases        => $cgi->param("title_databases") || "Cơ sở dữ liệu điện tử",
        link_databases         => $cgi->param("link_databases") || "/cgi-bin/ftu/opac-databases.pl",
        title_renew            => $cgi->param("title_renew") || "Gia hạn sách trực tuyến",
        link_renew             => $cgi->param("link_renew") || "/cgi-bin/ftu/opac-user.pl#opac-user-checkouts",
        title_guide            => $cgi->param("title_guide") || "Hướng dẫn sử dụng OPAC",
        link_guide             => $cgi->param("link_guide") || "/cgi-bin/ftu/opac-news-detail.pl?id=1",

        # 2. Hotline & Giờ phục vụ
        hotline_hanoi          => $cgi->param("hotline_hanoi") || "(024) 3835 6800",
        hotline_hanoi_ext      => $cgi->param("hotline_hanoi_ext") || "Máy lẻ: 532 / 535",
        hotline_hcmc           => $cgi->param("hotline_hcmc") || "(028) 3512 7254",
        hotline_hcmc_sub       => $cgi->param("hotline_hcmc_sub") || "(028) 3512 7258",
        hotline_quangninh      => $cgi->param("hotline_quangninh") || "(0203) 3850 411",
        email_contact          => $cgi->param("email_contact") || 'tv.hcmc@ftu.edu.vn',
        hours_status           => $cgi->param("hours_status") || "Đang mở cửa",
        hours_summary          => $cgi->param("hours_summary") || "Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 16:00",

        # 3. Địa chỉ 3 cơ sở
        campus_hn_title        => $cgi->param("campus_hn_title") || "Trụ sở chính Hà Nội",
        campus_hn_addr         => $cgi->param("campus_hn_addr") || "91 Phố Chùa Láng, P. Láng Thượng, Q. Đống Đa, TP. Hà Nội",
        campus_hn_phone        => $cgi->param("campus_hn_phone") || "(024) 3835 6800 (Ext: 532, 535)",

        campus_hcm_title       => $cgi->param("campus_hcm_title") || "Phân hiệu Trường ĐH Ngoại thương tại TP. Hồ Chí Minh",
        campus_hcm_addr        => $cgi->param("campus_hcm_addr") || "Số 15, Đường D5, P. Thạnh Mỹ Tây, TP. HCM",
        campus_hcm_phone       => $cgi->param("campus_hcm_phone") || "(028) 3512 7254 - 3512 7258",

        campus_qn_title        => $cgi->param("campus_qn_title") || "Cơ sở Quảng Ninh",
        campus_qn_addr         => $cgi->param("campus_qn_addr") || "Số 260 Bạch Đằng, P. Nam Khê, TP. Uông Bí, Tỉnh Quảng Ninh",
        campus_qn_phone        => $cgi->param("campus_qn_phone") || "(0203) 3850 411",

        # 4. Kênh Mạng xã hội & Truyền thông
        link_facebook          => $cgi->param("link_facebook") || "https://www.facebook.com/thuvienftuhanoi",
        link_youtube           => $cgi->param("link_youtube") || 'https://www.youtube.com/@FTUChannel',
        link_portal            => $cgi->param("link_portal") || "http://ftu.edu.vn",
        link_dspace            => $cgi->param("link_dspace") || "http://dspace.ftu.edu.vn",

        # 5. Thông tin Thư viện & Bản quyền
        library_name_full      => $cgi->param("library_name_full") || "Thư viện Trường Đại học Ngoại thương",
        library_name_en        => $cgi->param("library_name_en") || "Foreign Trade University Library",
        library_description    => $cgi->param("library_description") || "Trung tâm Thông tin – Tri thức hiện đại, kết nối cộng đồng giảng viên và sinh viên FTU với nguồn học liệu số phong phú, sách in chuyên ngành chất lượng cao và dịch vụ hỗ trợ nghiên cứu chuẩn quốc tế.",
        copyright_text         => $cgi->param("copyright_text") || "© 2026 Thư viện Trường Đại học Ngoại thương (Foreign Trade University Library). Bảo lưu mọi quyền."
    );

    my @cfg_files = (
        "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/vi-VN/includes/ftu-brand-config.inc",
        "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/en/includes/ftu-brand-config.inc",
        "/kohadevbox/koha/koha-tmpl/intranet-tmpl/prog/vi-VN/includes/ftu-brand-config.inc",
        "/kohadevbox/koha/koha-tmpl/intranet-tmpl/prog/en/includes/ftu-brand-config.inc",
    );

    for my $f (@cfg_files) {
        if (open(my $fh, "<:encoding(UTF-8)", $f)) {
            my $content = do { local $/; <$fh> };
            close $fh;
            for my $k (keys %new_vals) {
                my $v = $new_vals{$k};
                $v =~ s/\\/\\\\/g;
                $v =~ s/\"/\\"/g;
                if ($content =~ /^\s*\Q$k\E\s*=>\s*"[^"\\]*(?:\\.[^"\\]*)*"/m) {
                    $content =~ s/^(\s*\Q$k\E\s*=>\s*)"[^"\\]*(?:\\.[^"\\]*)*"/$1"$v"/m;
                } else {
                    $content =~ s/(\}\s*\%\])/    $k => "$v",\n$1/;
                }
            }
            if (open(my $out, ">:encoding(UTF-8)", $f)) {
                print $out $content;
                close $out;
            }
        }
    }

    # Backup to systempreferences
    eval {
        use JSON;
        my $json_str = JSON::to_json(\%new_vals);
        C4::Context->set_preference('FTU_FooterConfig', $json_str);
    };

    # Flush template & system cache
    eval {
        require Koha::Caches;
        Koha::Caches->get_instance()->flush_all();
    };

    print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?section=footer&msg=footer_saved");
    exit;
}

if ($op eq "add_form") {
    my $id = int($cgi->param("id") || 0);
    my $section = $cgi->param("section") || "";
    my $default_type = $cgi->param("default_type") || "";
    my $post = {};
    if ($id > 0) {
        my $sth = $dbh->prepare("SELECT * FROM koha_portal_posts WHERE id = ?");
        $sth->execute($id);
        $post = $sth->fetchrow_hashref;
        if ($post) {
            $section = "database" if ($post->{post_type} && $post->{post_type} eq "database");
            $section = "banner" if ($post->{post_type} && $post->{post_type} eq "banner");
            if ($post->{event_start}) {
                $post->{event_start} =~ s/\s+/T/; # Convert for datetime-local input
                $post->{event_start} = substr($post->{event_start}, 0, 16);
            }
            if ($post->{event_end}) {
                $post->{event_end} =~ s/\s+/T/;
                $post->{event_end} = substr($post->{event_end}, 0, 16);
            }
        }
    } else {
        $post->{status} = "published";
        if ($default_type eq "database" || $section eq "database") {
            $post->{post_type} = "database";
            $post->{author_name} = "Thư viện ĐH Ngoại thương";
            $post->{event_tag} = "Nội bộ & Từ xa";
            $post->{classification} = "CSDL THƯƠNG MẠI";
            $post->{access_instructions} = "• Xác thực IP mạng trường hoặc đăng nhập tài khoản thư viện cấp";
            my ($max_ord) = $dbh->selectrow_array("SELECT MAX(sort_order) FROM koha_portal_posts WHERE post_type = 'database'");
            $post->{sort_order} = ($max_ord || 0) + 1;
            $section = "database";
        } elsif ($default_type eq "banner" || $section eq "banner") {
            $post->{post_type} = "banner";
            $post->{author_name} = "Thư viện ĐH Ngoại thương";
            $post->{event_tag} = "THƯ VIỆN FTU";
            $post->{classification} = "THƯ VIỆN FTU";
            my ($max_ord) = $dbh->selectrow_array("SELECT MAX(sort_order) FROM koha_portal_posts WHERE post_type = 'banner'");
            $post->{sort_order} = ($max_ord || 0) + 1;
            $section = "banner";
        } else {
            $post->{post_type} = $default_type || "news";
            $post->{author_name} = "Thư viện ĐH Ngoại thương";
            $post->{event_tag} = "Sắp diễn ra";
            $section = "news";
        }
    }

    $template->param(
        op      => "add_form",
        section => $section,
        post    => $post,
        msg     => $msg,
    );
    output_html_with_http_headers $cgi, $cookie, $template->output;
    exit;
}

# Default: op=list
my $section = $cgi->param("section") || "";
my $filter_type = $cgi->param("type") || "all";
my $filter_status = $cgi->param("status") || "all";
my $filter_class = $cgi->param("class") || "all";
my $search_q = $cgi->param("q") || "";

if ($filter_type eq "database") {
    $section = "database";
} elsif ($filter_type eq "banner") {
    $section = "banner";
} elsif ($filter_type eq "news" || $filter_type eq "event" || $filter_type eq "notice") {
    $section = "news";
}
$section = "news" unless ($section eq "database" || $section eq "banner" || $section eq "footer");

my $query = "SELECT * FROM koha_portal_posts WHERE 1=1";
my @params;

if ($section eq "database") {
    $query .= " AND post_type = 'database'";
    if ($filter_class ne "all") {
        $query .= " AND classification = ?";
        push @params, $filter_class;
    }
} elsif ($section eq "banner") {
    $query .= " AND post_type = 'banner'";
} else {
    $query .= " AND post_type NOT IN ('database', 'banner')";
    if ($filter_type ne "all") {
        $query .= " AND post_type = ?";
        push @params, $filter_type;
    }
}

if ($filter_status ne "all") {
    $query .= " AND status = ?";
    push @params, $filter_status;
}
if ($search_q ne "") {
    $query .= " AND (title LIKE ? OR excerpt LIKE ? OR event_tag LIKE ? OR classification LIKE ? OR access_instructions LIKE ? OR db_user LIKE ?)";
    push @params, "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%";
}

if ($section eq "database" || $section eq "banner") {
    $query .= " ORDER BY sort_order ASC, id ASC";
} else {
    $query .= " ORDER BY is_featured DESC, created_at DESC";
}

# Pagination (10 items per page)
use POSIX qw(ceil);
my $page = int($cgi->param("page") || 1);
$page = 1 if $page < 1;
my $limit = 10;

# Count total rows for pagination
my $count_query = "SELECT COUNT(*) FROM koha_portal_posts WHERE 1=1";
if ($section eq "database") {
    $count_query .= " AND post_type = 'database'";
    if ($filter_class ne "all") {
        $count_query .= " AND classification = ?";
    }
} elsif ($section eq "banner") {
    $count_query .= " AND post_type = 'banner'";
} else {
    $count_query .= " AND post_type NOT IN ('database', 'banner')";
    if ($filter_type ne "all") {
        $count_query .= " AND post_type = ?";
    }
}
if ($filter_status ne "all") {
    $count_query .= " AND status = ?";
}
if ($search_q ne "") {
    $count_query .= " AND (title LIKE ? OR excerpt LIKE ? OR event_tag LIKE ? OR classification LIKE ? OR access_instructions LIKE ? OR db_user LIKE ?)";
}

my $count_sth = $dbh->prepare($count_query);
$count_sth->execute(@params);
my ($total_rows) = $count_sth->fetchrow_array;
$total_rows ||= 0;

my $total_pages = ceil($total_rows / $limit) || 1;
$page = $total_pages if ($page > $total_pages && $total_pages > 0);
my $offset = ($page - 1) * $limit;

# Append LIMIT & OFFSET
$query .= " LIMIT ? OFFSET ?";
push @params, $limit, $offset;

my $sth = $dbh->prepare($query);
$sth->execute(@params);
my @posts;
while (my $row = $sth->fetchrow_hashref) {
    if ($row->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/) {
        $row->{formatted_date} = "$3/$2/$1";
    }
    if ($row->{event_start} && $row->{event_start} =~ /^(\d{4})-(\d{2})-(\d{2})\s+(\d{2}):(\d{2})/) {
        $row->{event_date} = "$3/$2";
        $row->{event_time} = "$4:$5";
        $row->{formatted_event} = "$3/$2 lúc $4:$5";
    }
    push @posts, $row;
}

# Calculate pagination bounds
my $page_start = $total_rows == 0 ? 0 : ($offset + 1);
my $page_end   = ($offset + $limit > $total_rows) ? $total_rows : ($offset + $limit);
my $has_prev   = $page > 1 ? 1 : 0;
my $prev_page  = $page - 1;
my $has_next   = $page < $total_pages ? 1 : 0;
my $next_page  = $page + 1;

my @pages_loop;
for (my $p = 1; $p <= $total_pages; $p++) {
    push @pages_loop, {
        page_num  => $p,
        is_active => ($p == $page ? 1 : 0),
    };
}

# Counts for quick tabs
my $count_news_group = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type NOT IN ('database', 'banner')");
my $count_news       = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'news'");
my $count_event      = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'event'");
my $count_news_draft = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type NOT IN ('database', 'banner') AND status = 'draft'");

my $count_database      = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database'");
my $count_db_active     = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database' AND status = 'published'");
my $count_db_draft      = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database' AND status = 'draft'");
my $count_db_commercial = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database' AND classification LIKE '%THƯƠNG MẠI%'");
my $count_db_opensource = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database' AND (classification LIKE '%NGUỒN MỞ%' OR classification LIKE '%OPEN%')");
my ($next_db_order)     = $dbh->selectrow_array("SELECT COALESCE(MAX(sort_order), 0) + 1 FROM koha_portal_posts WHERE post_type = 'database'");

my $count_banner        = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'banner'");
my $count_banner_active = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'banner' AND status = 'published'");
my $count_banner_draft  = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'banner' AND status = 'draft'");
my ($next_banner_order) = $dbh->selectrow_array("SELECT COALESCE(MAX(sort_order), 0) + 1 FROM koha_portal_posts WHERE post_type = 'banner'");

my $footer_cfg = {};
my $cfg_file = "/kohadevbox/koha/koha-tmpl/opac-tmpl/bootstrap/vi-VN/includes/ftu-brand-config.inc";
if (open(my $fh, "<:encoding(UTF-8)", $cfg_file)) {
    my $content = do { local $/; <$fh> };
    close $fh;
    while ($content =~ /^\s*([a-zA-Z0-9_]+)\s*=>\s*"([^"\\]*(?:\\.[^"\\]*)*)"/mg) {
        my ($k, $v) = ($1, $2);
        $v =~ s/\\"/\"/g;
        $v =~ s/\\\\/\\/g;
        $footer_cfg->{$k} = $v;
    }
}

$template->param(
    op                  => "list",
    section             => $section,
    footer_cfg          => $footer_cfg,
    posts               => \@posts,
    filter_type         => $filter_type,
    filter_status       => $filter_status,
    filter_class        => $filter_class,
    search_q            => $search_q,
    current_page        => $page,
    total_pages         => $total_pages,
    total_rows          => $total_rows,
    page_start          => $page_start,
    page_end            => $page_end,
    has_prev            => $has_prev,
    prev_page           => $prev_page,
    has_next            => $has_next,
    next_page           => $next_page,
    pages_loop          => \@pages_loop,
    count_news_group    => $count_news_group,
    count_news          => $count_news,
    count_event         => $count_event,
    count_news_draft    => $count_news_draft,
    count_database      => $count_database,
    count_db_active     => $count_db_active,
    count_db_draft      => $count_db_draft,
    count_db_commercial => $count_db_commercial,
    count_db_opensource => $count_db_opensource,
    next_db_order       => ($next_db_order || 1),
    count_banner        => $count_banner,
    count_banner_active => $count_banner_active,
    count_banner_draft  => $count_banner_draft,
    next_banner_order   => ($next_banner_order || 1),
    msg                 => $msg,
);

output_html_with_http_headers $cgi, $cookie, $template->output;
