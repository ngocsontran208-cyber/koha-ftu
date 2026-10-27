#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use C4::Auth qw( get_template_and_user haspermission );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;
use C4::Log qw( logaction );
use Koha::Patrons;

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;

my ($template, $borrowernumber, $cookie) = get_template_and_user(
    {
        template_name   => "tools/portal-news.tt",
        query           => $cgi,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => [
            { tools => "portal_news" },
            { tools => "portal_database" },
            { tools => "portal_banner" },
            { tools => "portal_footer" },
            { tools => "edit_additional_contents" },
            { tools => "portal_review" },
        ],
    }
);

# ---- Phân quyền theo mục ----
# portal_review: chỉ được thao tác Lời giới thiệu (intro_*). Các quyền portal_* còn lại: thao tác các mục khác.
# Dùng sub ẩn danh (không dùng sub có tên) để tránh lỗi giữ biến cũ giữa các request khi chạy dưới Plack.
my %INTRO_TYPES = ( intro_librarian => 1, intro_reader => 1 );
my $ftu_userid  = C4::Context->userenv ? C4::Context->userenv->{id} : undef;
my $can_review  = ( $ftu_userid && haspermission( $ftu_userid, { tools => 'portal_review' } ) ) ? 1 : 0;
my $can_other   = 0;
for my $perm (qw( portal_news portal_database portal_banner portal_footer edit_additional_contents )) {
    if ( $ftu_userid && haspermission( $ftu_userid, { tools => $perm } ) ) { $can_other = 1; last; }
}
$template->param( can_portal_review => $can_review, can_portal_other => $can_other );
my $ftu_can_touch = sub {
    my ($pt) = @_;
    return $INTRO_TYPES{ $pt // '' } ? $can_review : $can_other;
};
my $ftu_deny = sub {
    my ($sec) = @_;
    print $cgi->redirect( "/cgi-bin/koha/tools/portal-news.pl?op=list&msg=forbidden" . ( $sec ? "&section=$sec" : "" ) );
    exit;
};

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
        $ftu_deny->( $INTRO_TYPES{ $pt // '' } ? 'intro' : $section ) unless $ftu_can_touch->($pt);
        $section = "database" if ($pt && $pt eq "database");
        $section = "banner" if ($pt && $pt eq "banner");
        $section = "intro" if ($pt && $INTRO_TYPES{$pt});
        $dbh->do("DELETE FROM koha_portal_posts WHERE id = ?", undef, $id);
        logaction( 'PORTAL_NEWS', 'DELETE', $id, "Xóa mục #" . $id . " (loại: " . ($pt || 'news') . ")" );
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
        $ftu_deny->( $INTRO_TYPES{ $pt // '' } ? 'intro' : $section ) unless $ftu_can_touch->($pt);
        $section = "database" if ($pt && $pt eq "database");
        $section = "banner" if ($pt && $pt eq "banner");
        $section = "intro" if ($pt && $INTRO_TYPES{$pt});
        my $new_status = ($curr eq "published") ? "draft" : "published";
        $dbh->do("UPDATE koha_portal_posts SET status = ? WHERE id = ?", undef, $new_status, $id);
        logaction( 'PORTAL_NEWS', 'STATUS_CHANGE', $id, "Đổi trạng thái mục #$id sang $new_status (loại: " . ($pt || 'news') . ")" );
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
    if ($id > 0) {
        my ($old_pt) = $dbh->selectrow_array("SELECT post_type FROM koha_portal_posts WHERE id = ?", undef, $id);
        $ftu_deny->() if defined $old_pt && !$ftu_can_touch->($old_pt);
    }
    $ftu_deny->( $INTRO_TYPES{$post_type} ? 'intro' : '' ) unless $ftu_can_touch->($post_type);
    my $title               = $cgi->param("title");
    my $excerpt             = $cgi->param("excerpt") || "";
    my $classification      = $cgi->param("classification") || ($post_type eq 'database' ? "CSDL THƯƠNG MẠI" : ($post_type eq 'banner' ? "THƯ VIỆN FTU" : ""));
    my $access_instructions = $cgi->param("access_instructions") || "";
    my $db_user             = $cgi->param("db_user") || "";
    my $db_pass             = $cgi->param("db_pass") || "";
    my $db_url              = $cgi->param("db_url") || "";
    my $support_link        = $cgi->param("support_link") || "";
    $db_url ||= $support_link if ($post_type eq 'database' && !$db_url);
    $support_link ||= $db_url if ($post_type eq 'database' && !$support_link);
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
        my $raw_html = $cgi->param("content_raw");
        if ( ( $cgi->param("content_mode") // '' ) eq 'text' && defined $raw_html && $raw_html =~ /\S/ ) {
            $content = $raw_html;    # chế độ Mã nguồn HTML: giữ nguyên văn
        } else {
            $content = $cgi->param("content") || $excerpt || "";
        }
        $is_featured = int($cgi->param("is_featured") || 0);
    }

    my $featured_image      = $cgi->param("featured_image") || "";
    my $author_name         = $cgi->param("author_name") || "Thư viện Phân hiệu";
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

    my $saved_id = $id;
    if ($id > 0) {
        my $sql = "UPDATE koha_portal_posts SET 
            sort_order = ?, post_type = ?, title = ?, excerpt = ?, classification = ?,
            access_instructions = ?, db_user = ?, db_pass = ?, db_url = ?, support_link = ?,
            content = ?, featured_image = ?, author_name = ?, status = ?, is_featured = ?,
            event_start = ?, event_end = ?, event_location = ?, event_reg_link = ?,
            event_tag = ?, views_count = ?
            WHERE id = ?";
        $dbh->do($sql, undef, 
            $sort_order, $post_type, $title, $excerpt, $classification,
            $access_instructions, $db_user, $db_pass, $db_url, $support_link,
            $content, $featured_image, $author_name, $status, $is_featured,
            $event_start, $event_end, $event_location, $event_reg_link,
            $event_tag, $views_count, $id
        );
        logaction( 'PORTAL_NEWS', 'MODIFY', $id, "$post_type: $title" );
    } else {
        my $sql = "INSERT INTO koha_portal_posts 
            (sort_order, post_type, title, excerpt, classification, access_instructions, db_user, db_pass, db_url, support_link, content, featured_image, author_name, status, is_featured, event_start, event_end, event_location, event_reg_link, event_tag, views_count)
            VALUES (?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?, ?)";
        $dbh->do($sql, undef,
            $sort_order, $post_type, $title, $excerpt, $classification,
            $access_instructions, $db_user, $db_pass, $db_url, $support_link,
            $content, $featured_image, $author_name, $status, $is_featured,
            $event_start, $event_end, $event_location, $event_reg_link,
            $event_tag, $views_count
        );
        my $new_id = $dbh->{mysql_insertid} || $dbh->last_insert_id(undef, undef, 'koha_portal_posts', 'id');
        $saved_id = $new_id;
        logaction( 'PORTAL_NEWS', 'ADD', $new_id, "$post_type: $title" );
    }

    # Gắn Lời giới thiệu với các biểu ghi (biblio) được giới thiệu
    if ($saved_id) {
        $dbh->do("DELETE FROM koha_portal_post_biblios WHERE post_id = ?", undef, $saved_id);
        if ($INTRO_TYPES{$post_type}) {
            my %seen;
            my @bibs = grep { $_ > 0 && !$seen{$_}++ } map { int($_) } split /[^0-9]+/, ( $cgi->param("biblionumbers") // '' );
            @bibs = @bibs[0 .. 0] if @bibs > 1;    # mỗi Lời giới thiệu gắn với đúng 1 cuốn sách
            for my $bn (@bibs) {
                $dbh->do("INSERT IGNORE INTO koha_portal_post_biblios (post_id, biblionumber) SELECT ?, biblionumber FROM biblio WHERE biblionumber = ?", undef, $saved_id, $bn);
            }
        }
    }

    my $redirect_url = "/cgi-bin/koha/tools/portal-news.pl?op=list&msg=saved";
    $redirect_url .= "&section=database" if ($post_type eq "database");
    $redirect_url .= "&section=banner" if ($post_type eq "banner");
    $redirect_url .= "&section=intro" if ($INTRO_TYPES{$post_type});
    print $cgi->redirect($redirect_url);
    exit;
}

if (($op eq "save_footer" || $op eq "cud-save_footer")) {
    my $p_library_name      = $cgi->param("library_name") || "Thư viện Phân hiệu Trường Đại học Ngoại thương";
    my $p_campus_current    = $cgi->param("campus_current") || "Foreign Trade University - Ho Chi Minh City Branch";
    my $p_campus_hcm_addr   = $cgi->param("campus_hcm_addr") || "Số 15, Đường D5, Phường Thạnh Mỹ Tây, TP. Hồ Chí Minh";
    my $p_hotline_hcmc      = $cgi->param("hotline_hcmc") || "(028) 3512 7254";
    my $p_email_contact     = $cgi->param("email_contact") || 'tv.hcmc@ftu.edu.vn';
    my $p_hours_summary     = $cgi->param("hours_summary") || "Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 16:00";
    my $p_link_facebook     = $cgi->param("link_facebook") || "https://www.facebook.com/ftu2.hcmc";
    my $p_link_youtube      = $cgi->param("link_youtube") || 'https://www.youtube.com/@FTUChannel';
    my $p_link_portal       = $cgi->param("link_portal") || "https://hcmc.ftu.edu.vn";

    my $p_footer_res_title1 = $cgi->param("footer_res_title1") || "Bộ sưu tập tài liệu số";
    my $p_footer_res_link1  = $cgi->param("footer_res_link1") || "/cgi-bin/koha/opac-collections.pl";
    my $p_footer_res_title2 = $cgi->param("footer_res_title2") || "Tìm kiếm theo Tác giả";
    my $p_footer_res_link2  = $cgi->param("footer_res_link2") || "/cgi-bin/koha/opac-search.pl?idx=au";
    my $p_footer_res_title3 = $cgi->param("footer_res_title3") || "Tìm kiếm theo Chủ đề";
    my $p_footer_res_link3  = $cgi->param("footer_res_link3") || "/cgi-bin/koha/opac-search.pl?idx=su";
    my $p_footer_res_title4 = $cgi->param("footer_res_title4") || "Giáo trình & Học phần";
    my $p_footer_res_link4  = $cgi->param("footer_res_link4") || "/cgi-bin/koha/opac-course-reserves.pl";
    my $p_footer_res_title5 = $cgi->param("footer_res_title5") || "Kho tài liệu số DSpace";
    my $p_footer_res_link5  = $cgi->param("footer_res_link5") || "/elib";

    my $p_footer_srv_title1 = $cgi->param("footer_srv_title1") || "Tài khoản & Gia hạn sách";
    my $p_footer_srv_link1  = $cgi->param("footer_srv_link1") || "/cgi-bin/koha/opac-user.pl";
    my $p_footer_srv_title2 = $cgi->param("footer_srv_title2") || "Quy định bản quyền học thuật";
    my $p_footer_srv_link2  = $cgi->param("footer_srv_link2") || "/elib/info/end-user-agreement";
    my $p_footer_srv_title3 = $cgi->param("footer_srv_title3") || "Thông báo & Lịch phục vụ";
    my $p_footer_srv_link3  = $cgi->param("footer_srv_link3") || "/cgi-bin/koha/opac-news-detail.pl?id=5";
    my $p_footer_srv_title4 = $cgi->param("footer_srv_title4") || "Liên hệ Ban quản trị Thư viện";
    my $p_footer_srv_link4  = $cgi->param("footer_srv_link4") || "/cgi-bin/koha/opac-reportproblem.pl";

    my $p_copyright_text    = $cgi->param("copyright_text") || "© 2026 Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh. Bảo lưu mọi quyền.";

    # 1. Lưu vào từng System Preference trong DB
    C4::Context->set_preference('FTU_Footer_LibraryName',   $p_library_name);
    C4::Context->set_preference('FTU_Footer_CampusCurrent', $p_campus_current);
    C4::Context->set_preference('FTU_Footer_Addr',          $p_campus_hcm_addr);
    C4::Context->set_preference('FTU_Footer_Hotline',       $p_hotline_hcmc);
    C4::Context->set_preference('FTU_Footer_Email',         $p_email_contact);
    C4::Context->set_preference('FTU_Footer_Hours',         $p_hours_summary);
    C4::Context->set_preference('FTU_Footer_Facebook',      $p_link_facebook);
    C4::Context->set_preference('FTU_Footer_Youtube',       $p_link_youtube);
    C4::Context->set_preference('FTU_Footer_Portal',        $p_link_portal);

    C4::Context->set_preference('FTU_Footer_ResTitle1',     $p_footer_res_title1);
    C4::Context->set_preference('FTU_Footer_ResLink1',      $p_footer_res_link1);
    C4::Context->set_preference('FTU_Footer_ResTitle2',     $p_footer_res_title2);
    C4::Context->set_preference('FTU_Footer_ResLink2',      $p_footer_res_link2);
    C4::Context->set_preference('FTU_Footer_ResTitle3',     $p_footer_res_title3);
    C4::Context->set_preference('FTU_Footer_ResLink3',      $p_footer_res_link3);
    C4::Context->set_preference('FTU_Footer_ResTitle4',     $p_footer_res_title4);
    C4::Context->set_preference('FTU_Footer_ResLink4',      $p_footer_res_link4);
    C4::Context->set_preference('FTU_Footer_ResTitle5',     $p_footer_res_title5);
    C4::Context->set_preference('FTU_Footer_ResLink5',      $p_footer_res_link5);

    C4::Context->set_preference('FTU_Footer_SrvTitle1',     $p_footer_srv_title1);
    C4::Context->set_preference('FTU_Footer_SrvLink1',      $p_footer_srv_link1);
    C4::Context->set_preference('FTU_Footer_SrvTitle2',     $p_footer_srv_title2);
    C4::Context->set_preference('FTU_Footer_SrvLink2',      $p_footer_srv_link2);
    C4::Context->set_preference('FTU_Footer_SrvTitle3',     $p_footer_srv_title3);
    C4::Context->set_preference('FTU_Footer_SrvLink3',      $p_footer_srv_link3);
    C4::Context->set_preference('FTU_Footer_SrvTitle4',     $p_footer_srv_title4);
    C4::Context->set_preference('FTU_Footer_SrvLink4',      $p_footer_srv_link4);

    C4::Context->set_preference('FTU_Footer_Copyright',     $p_copyright_text);

    my %new_vals = (
        library_name           => $p_library_name,
        campus_current         => $p_campus_current,
        campus_hcm_addr        => $p_campus_hcm_addr,
        hotline_hcmc           => $p_hotline_hcmc,
        email_contact          => $p_email_contact,
        hours_summary          => $p_hours_summary,
        link_facebook          => $p_link_facebook,
        link_youtube           => $p_link_youtube,
        link_portal            => $p_link_portal,

        footer_res_title1      => $p_footer_res_title1,
        footer_res_link1       => $p_footer_res_link1,
        footer_res_title2      => $p_footer_res_title2,
        footer_res_link2       => $p_footer_res_link2,
        footer_res_title3      => $p_footer_res_title3,
        footer_res_link3       => $p_footer_res_link3,
        footer_res_title4      => $p_footer_res_title4,
        footer_res_link4       => $p_footer_res_link4,
        footer_res_title5      => $p_footer_res_title5,
        footer_res_link5       => $p_footer_res_link5,

        footer_srv_title1      => $p_footer_srv_title1,
        footer_srv_link1       => $p_footer_srv_link1,
        footer_srv_title2      => $p_footer_srv_title2,
        footer_srv_link2       => $p_footer_srv_link2,
        footer_srv_title3      => $p_footer_srv_title3,
        footer_srv_link3       => $p_footer_srv_link3,
        footer_srv_title4      => $p_footer_srv_title4,
        copyright_text         => $p_copyright_text,

        # Đồng bộ luôn các biến _en để giao diện tiếng Anh cũng hiển thị đúng nội dung người dùng cấu hình
        library_name_en        => $p_library_name,
        campus_current_en      => $p_campus_current,
        campus_hcm_addr_en     => $p_campus_hcm_addr,
        hours_summary_en       => $p_hours_summary,
        copyright_text_en      => $p_copyright_text
    );

    # 2. Ghi chuỗi JSON dự phòng vào FTU_FooterConfig
    eval {
        use JSON;
        my $json_str = JSON::to_json(\%new_vals);
        C4::Context->set_preference('FTU_FooterConfig', $json_str);
    };

    # 3. Ghi trực tiếp vào các file include cấu hình thương hiệu
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
                if ($content =~ /^\s*\Q$k\E\s*=>\s*.*?,?$/m) {
                    $content =~ s/^\s*\Q$k\E\s*=>.*$/    $k => "$v",/m;
                }
            }
            if (open(my $out, ">:encoding(UTF-8)", $f)) {
                print $out $content;
                close $out;
            }
        }
    }

    eval {
        require Koha::Caches;
        Koha::Caches->get_instance()->flush_all();
    };

    # Xóa compiled template cache và khởi động lại Plack để thay đổi có hiệu lực tức thì
    system("rm -rf /var/cache/koha/kohadev/templates/* 2>/dev/null; koha-plack --restart kohadev 2>/dev/null || true");

    logaction( 'PORTAL_NEWS', 'MODIFY', 0, "Cập nhật cấu hình thông tin chân trang (Footer)" );

    print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?section=footer&msg=footer_saved");
    exit;
}

if ($op eq "search_biblio") {
    my $q = $cgi->param("q") // "";
    my $field = $cgi->param("field") || "all";
    $q =~ s/^\s+|\s+$//g;
    my @rows;
    if (length $q) {
        my $like  = "%$q%";
        my $isbnq = $q; $isbnq =~ s/[\s-]//g;
        my $isbnl = "%$isbnq%";
        my (@w, @bind);
        my $bc_exists = "EXISTS (SELECT 1 FROM items ix WHERE ix.biblionumber = b.biblionumber AND ix.barcode %s ?)";
        my $cn_exists = "EXISTS (SELECT 1 FROM items ix WHERE ix.biblionumber = b.biblionumber AND ix.itemcallnumber LIKE ?)";
        if ($field eq "title") {
            push @w, "(b.title LIKE ? OR b.subtitle LIKE ?)"; push @bind, $like, $like;
        } elsif ($field eq "author") {
            push @w, "b.author LIKE ?"; push @bind, $like;
        } elsif ($field eq "isbn") {
            push @w, "(REPLACE(bi.isbn, '-', '') LIKE ? OR REPLACE(bi.issn, '-', '') LIKE ?)"; push @bind, $isbnl, $isbnl;
        } elsif ($field eq "barcode") {
            push @w, sprintf($bc_exists, "LIKE"); push @bind, "$q%";
        } elsif ($field eq "callnumber") {
            push @w, $cn_exists; push @bind, "$q%";
        } elsif ($field eq "biblionumber") {
            push @w, "b.biblionumber = ?"; push @bind, ($q =~ /^\d+$/ ? $q : 0);
        } else {
            push @w, "b.biblionumber = ?";              push @bind, ($q =~ /^\d+$/ ? $q : 0);
            push @w, sprintf($bc_exists, "=");          push @bind, $q;
            push @w, "(b.title LIKE ? OR b.subtitle LIKE ?)"; push @bind, $like, $like;
            push @w, "b.author LIKE ?";                 push @bind, $like;
            push @w, "REPLACE(bi.isbn, '-', '') LIKE ?"; push @bind, $isbnl;
        }
        my $sql = "SELECT b.biblionumber, b.title, b.subtitle, b.author, bi.publicationyear, bi.publishercode, bi.isbn,
                          (SELECT COUNT(*) FROM items i2 WHERE i2.biblionumber = b.biblionumber) AS items_count,
                          (SELECT i3.itemcallnumber FROM items i3 WHERE i3.biblionumber = b.biblionumber AND i3.itemcallnumber <> '' LIMIT 1) AS callnumber,
                          (SELECT i4.barcode FROM items i4 WHERE i4.biblionumber = b.biblionumber AND i4.barcode LIKE ? LIMIT 1) AS matched_barcode
                   FROM biblio b LEFT JOIN biblioitems bi ON bi.biblionumber = b.biblionumber
                   WHERE " . join(" OR ", @w) . "
                   ORDER BY (b.biblionumber = ?) DESC, b.biblionumber DESC LIMIT 20";
        my $sth = $dbh->prepare($sql);
        $sth->execute( ($field eq 'barcode' ? "$q%" : $q), @bind, ($q =~ /^\d+$/ ? $q : 0) );
        while (my $r = $sth->fetchrow_hashref) {
            $r->{isbn} = (split /\s*\|\s*/, ($r->{isbn} // ''))[0];
            push @rows, $r;
        }
    }
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    print JSON->new->utf8->encode(\@rows);
    exit;
}

if ($op eq "add_form") {
    my $id = int($cgi->param("id") || 0);
    my $section = $cgi->param("section") || "";
    my $default_type = $cgi->param("default_type") || "";
    my $post = {};
    my @linked_biblios;
    # Người chỉ có quyền portal_review luôn được đưa về form Lời giới thiệu
    if (!$can_other && !$id) { $section = "intro"; $default_type = "intro_librarian" unless $INTRO_TYPES{$default_type}; }
    if ($id > 0) {
        my $sth = $dbh->prepare("SELECT * FROM koha_portal_posts WHERE id = ?");
        $sth->execute($id);
        $post = $sth->fetchrow_hashref;
        if ($post) {
            $ftu_deny->() unless $ftu_can_touch->($post->{post_type});
            $section = "database" if ($post->{post_type} && $post->{post_type} eq "database");
            $section = "banner" if ($post->{post_type} && $post->{post_type} eq "banner");
            $section = "intro" if ($post->{post_type} && $INTRO_TYPES{ $post->{post_type} });
            my $lb = $dbh->prepare("SELECT b.biblionumber, b.title, b.subtitle, b.author, bi.publicationyear, bi.publishercode, bi.isbn, (SELECT COUNT(*) FROM items i2 WHERE i2.biblionumber = b.biblionumber) AS items_count, (SELECT i3.itemcallnumber FROM items i3 WHERE i3.biblionumber = b.biblionumber AND i3.itemcallnumber <> '' LIMIT 1) AS callnumber FROM koha_portal_post_biblios pb JOIN biblio b ON b.biblionumber = pb.biblionumber LEFT JOIN biblioitems bi ON bi.biblionumber = b.biblionumber WHERE pb.post_id = ? ORDER BY b.title LIMIT 1");
            $lb->execute($id);
            while (my $r = $lb->fetchrow_hashref) { push @linked_biblios, $r; }
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
        if ($INTRO_TYPES{$default_type} || $section eq "intro") {
            $ftu_deny->() unless $can_review;
            $post->{post_type} = $INTRO_TYPES{$default_type} ? $default_type : "intro_librarian";
            my $me = Koha::Patrons->find($borrowernumber);
            my $me_name = $me ? join(' ', grep { defined && length } ($me->surname, $me->firstname)) : '';
            $post->{author_name} = $post->{post_type} eq 'intro_reader' ? '' : ($me_name || "Thư viện Phân hiệu");
            $post->{event_tag} = "";
            $section = "intro";
            # Cho phép mở form từ trang sách: ?biblionumber=123
            if (my $pre = int($cgi->param("biblionumber") || 0)) {
                my $r = $dbh->selectrow_hashref("SELECT b.biblionumber, b.title, b.subtitle, b.author, bi.publicationyear, bi.publishercode, bi.isbn, (SELECT COUNT(*) FROM items i2 WHERE i2.biblionumber = b.biblionumber) AS items_count, (SELECT i3.itemcallnumber FROM items i3 WHERE i3.biblionumber = b.biblionumber AND i3.itemcallnumber <> '' LIMIT 1) AS callnumber FROM biblio b LEFT JOIN biblioitems bi ON bi.biblionumber = b.biblionumber WHERE b.biblionumber = ?", undef, $pre);
                push @linked_biblios, $r if $r;
            }
        } elsif ($default_type eq "database" || $section eq "database") {
            $post->{post_type} = "database";
            $post->{author_name} = "Thư viện Phân hiệu";
            $post->{event_tag} = "Nội bộ & Từ xa";
            $post->{classification} = "CSDL THƯƠNG MẠI";
            $post->{access_instructions} = "• Xác thực IP mạng trường hoặc đăng nhập tài khoản thư viện cấp";
            my ($max_ord) = $dbh->selectrow_array("SELECT MAX(sort_order) FROM koha_portal_posts WHERE post_type = 'database'");
            $post->{sort_order} = ($max_ord || 0) + 1;
            $section = "database";
        } elsif ($default_type eq "banner" || $section eq "banner") {
            $post->{post_type} = "banner";
            $post->{author_name} = "Thư viện Phân hiệu";
            $post->{event_tag} = "THƯ VIỆN FTU";
            $post->{classification} = "THƯ VIỆN FTU";
            my ($max_ord) = $dbh->selectrow_array("SELECT MAX(sort_order) FROM koha_portal_posts WHERE post_type = 'banner'");
            $post->{sort_order} = ($max_ord || 0) + 1;
            $section = "banner";
        } else {
            $post->{post_type} = $default_type || "news";
            $post->{author_name} = "Thư viện Phân hiệu";
            $post->{event_tag} = "Sắp diễn ra";
            $section = "news";
        }
    }

    $template->param(
        op      => "add_form",
        section => $section,
        post    => $post,
        linked_biblios => \@linked_biblios,
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
} elsif ($INTRO_TYPES{$filter_type}) {
    $section = "intro";
}
$section = "news" unless ($section eq "database" || $section eq "banner" || $section eq "footer" || $section eq "intro");
$section = "intro" if !$can_other && $can_review;
$section = "news"  if $section eq "intro" && !$can_review;

my $INTRO_SQL = "('intro_librarian', 'intro_reader')";
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
} elsif ($section eq "intro") {
    $query .= " AND post_type IN $INTRO_SQL";
    if ($INTRO_TYPES{$filter_type}) {
        $query .= " AND post_type = ?";
        push @params, $filter_type;
    }
} else {
    $query .= " AND post_type NOT IN ('database', 'banner', 'intro_librarian', 'intro_reader')";
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
    $query .= " AND (title LIKE ? OR excerpt LIKE ? OR event_tag LIKE ? OR classification LIKE ? OR access_instructions LIKE ? OR db_user LIKE ? OR author_name LIKE ?)";
    push @params, "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%", "%$search_q%";
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
} elsif ($section eq "intro") {
    $count_query .= " AND post_type IN $INTRO_SQL";
    if ($INTRO_TYPES{$filter_type}) {
        $count_query .= " AND post_type = ?";
    }
} else {
    $count_query .= " AND post_type NOT IN ('database', 'banner', 'intro_librarian', 'intro_reader')";
    if ($filter_type ne "all") {
        $count_query .= " AND post_type = ?";
    }
}
if ($filter_status ne "all") {
    $count_query .= " AND status = ?";
}
if ($search_q ne "") {
    $count_query .= " AND (title LIKE ? OR excerpt LIKE ? OR event_tag LIKE ? OR classification LIKE ? OR access_instructions LIKE ? OR db_user LIKE ? OR author_name LIKE ?)";
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
    if ($section eq "intro") {
        my $bt = $dbh->prepare("SELECT b.biblionumber, b.title FROM koha_portal_post_biblios pb JOIN biblio b ON b.biblionumber = pb.biblionumber WHERE pb.post_id = ? ORDER BY b.title");
        $bt->execute($row->{id});
        my @books;
        while (my $bk = $bt->fetchrow_hashref) { $bk->{title} =~ s/[\s\/:;,.]+$//; push @books, $bk; }
        $row->{books} = \@books;
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
my $count_news_group = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type NOT IN ('database', 'banner', 'intro_librarian', 'intro_reader')");
my $count_news       = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'news'");
my $count_event      = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'event'");
my $count_news_draft = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type NOT IN ('database', 'banner', 'intro_librarian', 'intro_reader') AND status = 'draft'");

my $count_intro           = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type IN $INTRO_SQL");
my $count_intro_librarian = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'intro_librarian'");
my $count_intro_reader    = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'intro_reader'");
my $count_intro_draft     = $dbh->selectrow_array("SELECT COUNT(*) FROM koha_portal_posts WHERE post_type IN $INTRO_SQL AND status = 'draft'");

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

my $footer_cfg = {
    library_name           => C4::Context->preference('FTU_Footer_LibraryName') || "Thư viện Phân hiệu Trường Đại học Ngoại thương",
    campus_current         => C4::Context->preference('FTU_Footer_CampusCurrent') || "Foreign Trade University - Ho Chi Minh City Branch",
    campus_hcm_addr        => C4::Context->preference('FTU_Footer_Addr') || "Số 15, Đường D5, Phường Thạnh Mỹ Tây, TP. Hồ Chí Minh",
    hotline_hcmc           => C4::Context->preference('FTU_Footer_Hotline') || "(028) 3512 7254",
    email_contact          => C4::Context->preference('FTU_Footer_Email') || 'tv.hcmc@ftu.edu.vn',
    hours_summary          => C4::Context->preference('FTU_Footer_Hours') || "Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 16:00",
    link_facebook          => C4::Context->preference('FTU_Footer_Facebook') || "https://www.facebook.com/ftu2.hcmc",
    link_youtube           => C4::Context->preference('FTU_Footer_Youtube') || 'https://www.youtube.com/@FTUChannel',
    link_portal            => C4::Context->preference('FTU_Footer_Portal') || "https://hcmc.ftu.edu.vn",

    footer_res_title1      => C4::Context->preference('FTU_Footer_ResTitle1') || "Bộ sưu tập tài liệu số",
    footer_res_link1       => C4::Context->preference('FTU_Footer_ResLink1') || "/cgi-bin/koha/opac-collections.pl",
    footer_res_title2      => C4::Context->preference('FTU_Footer_ResTitle2') || "Tìm kiếm theo Tác giả",
    footer_res_link2       => C4::Context->preference('FTU_Footer_ResLink2') || "/cgi-bin/koha/opac-search.pl?idx=au",
    footer_res_title3      => C4::Context->preference('FTU_Footer_ResTitle3') || "Tìm kiếm theo Chủ đề",
    footer_res_link3       => C4::Context->preference('FTU_Footer_ResLink3') || "/cgi-bin/koha/opac-search.pl?idx=su",
    footer_res_title4      => C4::Context->preference('FTU_Footer_ResTitle4') || "Giáo trình & Học phần",
    footer_res_link4       => C4::Context->preference('FTU_Footer_ResLink4') || "/cgi-bin/koha/opac-course-reserves.pl",
    footer_res_title5      => C4::Context->preference('FTU_Footer_ResTitle5') || "Kho tài liệu số DSpace",
    footer_res_link5       => C4::Context->preference('FTU_Footer_ResLink5') || (C4::Context->preference('FTU_DSpaceBaseURL') || "/elib"),

    footer_srv_title1      => C4::Context->preference('FTU_Footer_SrvTitle1') || "Tài khoản & Gia hạn sách",
    footer_srv_link1       => C4::Context->preference('FTU_Footer_SrvLink1') || "/cgi-bin/koha/opac-user.pl",
    footer_srv_title2      => C4::Context->preference('FTU_Footer_SrvTitle2') || "Quy định bản quyền học thuật",
    footer_srv_link2       => C4::Context->preference('FTU_Footer_SrvLink2') || ((C4::Context->preference('FTU_DSpaceBaseURL') || "/elib") . "/info/end-user-agreement"),
    footer_srv_title3      => C4::Context->preference('FTU_Footer_SrvTitle3') || "Thông báo & Lịch phục vụ",
    footer_srv_link3       => C4::Context->preference('FTU_Footer_SrvLink3') || "/cgi-bin/koha/opac-news-detail.pl?id=5",
    footer_srv_title4      => C4::Context->preference('FTU_Footer_SrvTitle4') || "Liên hệ Ban quản trị Thư viện",
    footer_srv_link4       => C4::Context->preference('FTU_Footer_SrvLink4') || "/cgi-bin/koha/opac-reportproblem.pl",

    copyright_text         => C4::Context->preference('FTU_Footer_Copyright') || "© 2026 Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh. Bảo lưu mọi quyền."
};

# Bổ sung từ JSON FTU_FooterConfig hoặc file ftu-brand-config.inc nếu thiếu
eval {
    use JSON;
    my $pref = C4::Context->preference('FTU_FooterConfig');
    if ($pref) {
        my $decoded = JSON::from_json($pref);
        if (ref($decoded) eq 'HASH') {
            for my $k (keys %$decoded) {
                $footer_cfg->{$k} = $decoded->{$k} if (!defined $footer_cfg->{$k} || $footer_cfg->{$k} eq '');
            }
        }
    }
};

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
    count_intro           => $count_intro,
    count_intro_librarian => $count_intro_librarian,
    count_intro_reader    => $count_intro_reader,
    count_intro_draft     => $count_intro_draft,
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
