#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;
use Koha::Biblios;
use Koha::Items;
use Koha::CoverImages;
use Koha::CoverImage;
use Koha::ItemTypes;
use Koha::Libraries;
use C4::Biblio qw( AddBiblio ModBiblio DelBiblio );
use MARC::Record;
use MARC::Field;
use GD;
use JSON;
use MIME::Base64;

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;
my $json = JSON->new->utf8;

# Tự động đảm bảo bảng biblio_quantities luôn tồn tại
eval {
    $dbh->do("
        CREATE TABLE IF NOT EXISTS biblio_quantities (
            biblionumber INT(11) NOT NULL,
            quantity INT(11) NOT NULL DEFAULT 0,
            PRIMARY KEY (biblionumber)
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4
    ");
};

# Authentication and permissions
my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name   => "cataloguing/records.tt",
        query           => $cgi,
        type            => "intranet",
        authnotrequired => 0,
        flagsrequired   => { catalogue => 1 },
    }
);

my $op = $cgi->param("op") || "list";
$op =~ s/^cud-//;

sub format_date_dmy {
    my ($d) = @_;
    return '' unless defined $d;
    $d =~ s/^\s+|\s+$//g;
    return '' unless length($d);
    if ($d =~ /^(\d{4})-(\d{2})-(\d{2})/) {
        return "$3/$2/$1";
    }
    return $d;
}

# -------------------------------------------------------------
# 1. AJAX: Lấy mã vạch tự sinh tiếp theo (Auto Barcode)
# -------------------------------------------------------------
if ( $op eq "auto_barcode" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $prefix = $cgi->param("prefix") || "FTU";
    $prefix =~ s/[^A-Za-z0-9_-]//g;
    $prefix = "FTU" unless length($prefix);

    # Tìm mã vạch lớn nhất bắt đầu bằng prefix
    my $sth = $dbh->prepare("SELECT barcode FROM items WHERE barcode LIKE ? ORDER BY itemnumber DESC LIMIT 50");
    $sth->execute("$prefix%");
    my $max_num = 0;
    while (my ($bc) = $sth->fetchrow_array) {
        if ($bc =~ /^$prefix(\d+)$/) {
            my $num = int($1);
            $max_num = $num if $num > $max_num;
        }
    }
    
    my $next_num = $max_num > 0 ? $max_num + 1 : int(rand(900)) + 100;
    my $next_barcode = sprintf("%s%06d", $prefix, $next_num);

    # Đảm bảo mã vạch chưa từng tồn tại
    my $chk = $dbh->prepare("SELECT COUNT(*) FROM items WHERE barcode = ?");
    $chk->execute($next_barcode);
    my ($exists) = $chk->fetchrow_array;
    if ($exists) {
        $next_barcode = sprintf("%s%d%03d", $prefix, time() % 100000, int(rand(1000)));
    }

    print $json->encode({ success => 1, barcode => $next_barcode });
    exit;
}

# -------------------------------------------------------------
# 2. AJAX: Lấy thông tin chi tiết 1 biểu ghi để sửa nhanh (Get Record)
# -------------------------------------------------------------
if ( $op eq "get_record" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);

    my $sth = $dbh->prepare(q{
        SELECT 
            b.biblionumber,
            b.title,
            b.subtitle,
            b.author,
            b.abstract,
            b.seriestitle,
            b.copyrightdate,
            bi.isbn,
            bi.publishercode,
            bi.publicationyear,
            bi.cn_class,
            bi.cn_item,
            bi.cn_source,
            bi.pages,
            bi.itemtype
        FROM biblio b
        LEFT JOIN biblioitems bi ON b.biblionumber = bi.biblionumber
        WHERE b.biblionumber = ?
    });
    $sth->execute($biblionumber);
    my $rec = $sth->fetchrow_hashref;

    if ($rec) {
        my $biblio = Koha::Biblios->find($biblionumber);
        my $record = $biblio && $biblio->metadata ? $biblio->metadata->record : undef;
        
        my $ddc = $rec->{cn_class};
        my $cutter = $rec->{cn_item};
        
        # Nếu chưa có trong bi.cn_class / bi.cn_item, trích xuất từ MARC (082 / 092 / 084 / 942)
        if ($record) {
            for my $tag ('082', '092', '084') {
                my $f = $record->field($tag);
                if ($f) {
                    $ddc ||= $f->subfield('a');
                    $cutter ||= $f->subfield('b');
                    last if ($ddc && $cutter);
                }
            }
            if (!$ddc || !$cutter) {
                my $f942 = $record->field('942');
                if ($f942) {
                    $ddc ||= $f942->subfield('h');
                    $cutter ||= $f942->subfield('i');
                }
            }
        }
        
        # Nếu vẫn chưa có, lấy từ itemcallnumber
        if (!$ddc) {
            my ($item_cn) = $dbh->selectrow_array("SELECT itemcallnumber FROM items WHERE biblionumber = ? AND itemcallnumber IS NOT NULL AND itemcallnumber != '' LIMIT 1", undef, $biblionumber);
            $ddc = $item_cn if $item_cn;
        }
        
        $rec->{classification} = $ddc // "";
        $rec->{cutter}         = $cutter // "";
        if ($rec->{classification} && $rec->{cutter}) {
            if ($rec->{classification} =~ /\Q$rec->{cutter}\E/) {
                $rec->{callnumber} = $rec->{classification};
            } elsif ($rec->{classification} =~ m{/$}) {
                $rec->{callnumber} = "$rec->{classification}$rec->{cutter}";
            } else {
                $rec->{callnumber} = "$rec->{classification}/$rec->{cutter}";
            }
        } else {
            $rec->{callnumber} = $rec->{classification} || $rec->{cutter} || "";
        }

        my ($bq_qty) = $dbh->selectrow_array("SELECT quantity FROM biblio_quantities WHERE biblionumber = ?", undef, $biblionumber);
        $rec->{book_quantity} = defined $bq_qty ? int($bq_qty) : int($rec->{total_items} || 0);

        print $json->encode({ success => 1, biblio => $rec });
    } else {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
    }
    exit;
}

# -------------------------------------------------------------
# 3. AJAX: Lưu cập nhật biểu ghi nhanh (Save Record)
# -------------------------------------------------------------
if ( $op eq "save_record" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);
    my $title        = $cgi->param("title") // "";
    my $subtitle     = $cgi->param("subtitle") // "";
    my $author       = $cgi->param("author") // "";
    my $publisher    = $cgi->param("publishercode") // "";
    my $pubyear      = $cgi->param("publicationyear") // "";
    my $isbn         = $cgi->param("isbn") // "";
    my $pages        = $cgi->param("pages") // "";
    my $classif      = $cgi->param("classification") // "";
    my $cutter       = $cgi->param("cutter") // "";
    my $itemtype     = $cgi->param("itemtype") // "";
    my $abstract     = $cgi->param("abstract") // "";

    $title   =~ s/^\s+|\s+$//g;
    $classif =~ s/^\s+|\s+$//g;
    $cutter  =~ s/^\s+|\s+$//g;

    if ($title eq "") {
        print $json->encode({ success => 0, error => "Nhan đề tài liệu không được để trống" });
        exit;
    }

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    eval {
        # 1. Cập nhật bảng biblio
        $biblio->title($title);
        $biblio->subtitle($subtitle) if defined $subtitle;
        $biblio->author($author) if defined $author;
        $biblio->abstract($abstract) if defined $abstract;
        $biblio->copyrightdate(int($pubyear)) if ($pubyear =~ /^\d+$/);
        $biblio->store;

        # 2. Cập nhật bảng biblioitems
        my $biblioitem = $biblio->biblioitem;
        if ($biblioitem) {
            $biblioitem->isbn($isbn) if defined $isbn;
            $biblioitem->publishercode($publisher) if defined $publisher;
            $biblioitem->publicationyear($pubyear) if defined $pubyear;
            $biblioitem->cn_class($classif);
            $biblioitem->cn_item($cutter);
            $biblioitem->cn_source('ddc') unless $biblioitem->cn_source;
            $biblioitem->pages($pages) if defined $pages;
            $biblioitem->itemtype($itemtype) if defined $itemtype;
            $biblioitem->store;
        }

        # 3. Đồng bộ chuẩn vào MARC Record (245, 100, 260/264, 020, 082, 092, 942)
        eval {
            my $record = $biblio->metadata ? $biblio->metadata->record : undef;
            if ($record) {
                # 245
                my $f245 = $record->field('245');
                if ($f245) {
                    $f245->update('a' => $title);
                    $f245->update('b' => $subtitle) if length($subtitle);
                } else {
                    $record->add_fields(MARC::Field->new('245', '1', '0', 'a' => $title));
                }
                # 100
                if (length($author)) {
                    my $f100 = $record->field('100');
                    if ($f100) { $f100->update('a' => $author); }
                    else { $record->add_fields(MARC::Field->new('100', '1', ' ', 'a' => $author)); }
                }
                # 260 / 264
                my $f260 = $record->field('260') || $record->field('264');
                if ($f260) {
                    $f260->update('b' => $publisher) if length($publisher);
                    $f260->update('c' => $pubyear) if length($pubyear);
                } elsif (length($publisher) || length($pubyear)) {
                    $record->add_fields(MARC::Field->new('260', ' ', ' ', 'b' => $publisher, 'c' => $pubyear));
                }
                # 020
                if (length($isbn)) {
                    my $f020 = $record->field('020');
                    if ($f020) { $f020->update('a' => $isbn); }
                    else { $record->add_fields(MARC::Field->new('020', ' ', ' ', 'a' => $isbn)); }
                }

                # 082 (Dewey Decimal Classification: $a = DDC, $b = Cutter)
                my $f082 = $record->field('082');
                if (length($classif) || length($cutter)) {
                    if ($f082) {
                        $f082->delete_subfield(code => 'a');
                        $f082->delete_subfield(code => 'b');
                        $f082->add_subfields('a' => $classif) if length($classif);
                        $f082->add_subfields('b' => $cutter) if length($cutter);
                        $f082->add_subfields('2' => '23') unless $f082->subfield('2');
                    } else {
                        my @sfs;
                        push @sfs, ('a' => $classif) if length($classif);
                        push @sfs, ('b' => $cutter) if length($cutter);
                        push @sfs, ('2' => '23');
                        $record->add_fields(MARC::Field->new('082', '0', '4', @sfs));
                    }
                } elsif ($f082) {
                    $record->delete_field($f082);
                }

                # 092 (Local DDC)
                my $f092 = $record->field('092');
                if ($f092) {
                    $f092->delete_subfield(code => 'a');
                    $f092->delete_subfield(code => 'b');
                    $f092->add_subfields('a' => $classif) if length($classif);
                    $f092->add_subfields('b' => $cutter) if length($cutter);
                }

                # 942 (Koha MARC mapping: 942$h = cn_class, 942$i = cn_item, 942$2 = cn_source)
                my $f942 = $record->field('942');
                if ($f942) {
                    $f942->delete_subfield(code => 'h');
                    $f942->delete_subfield(code => 'i');
                    $f942->add_subfields('h' => $classif) if length($classif);
                    $f942->add_subfields('i' => $cutter) if length($cutter);
                    $f942->update('2' => 'ddc') unless $f942->subfield('2');
                    $f942->update('c' => $itemtype) if length($itemtype);
                } else {
                    my @sfs = ('2' => 'ddc');
                    push @sfs, ('c' => $itemtype) if length($itemtype);
                    push @sfs, ('h' => $classif) if length($classif);
                    push @sfs, ('i' => $cutter) if length($cutter);
                    $record->add_fields(MARC::Field->new('942', ' ', ' ', @sfs));
                }

                ModBiblio($record, $biblionumber, $biblio->frameworkcode);
            }
        };
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi lưu biểu ghi: $@" });
    } else {
        my $full_cn;
        if ($classif && $cutter) {
            if ($classif =~ /\Q$cutter\E/) {
                $full_cn = $classif;
            } elsif ($classif =~ m{/$}) {
                $full_cn = "$classif$cutter";
            } else {
                $full_cn = "$classif/$cutter";
            }
        } else {
            $full_cn = $classif || $cutter || "";
        }
        print $json->encode({ 
            success => 1, 
            message => "Đã lưu cập nhật biểu ghi và chuẩn hóa MARC thành công",
            biblio  => {
                biblionumber    => $biblionumber,
                title           => $title,
                subtitle        => $subtitle,
                author          => $author,
                publishercode   => $publisher,
                publicationyear => $pubyear,
                isbn            => $isbn,
                classification  => $classif,
                cutter          => $cutter,
                callnumber      => $full_cn,
                itemtype        => $itemtype
            }
        });
    }
    exit;
}

# -------------------------------------------------------------
# 4. AJAX: Tải lên ảnh bìa biểu ghi (Upload Cover Image)
# -------------------------------------------------------------
if ( $op eq "upload_cover" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    my $raw_data;
    my $upload_fh = $cgi->upload("cover_file");
    if ($upload_fh) {
        $raw_data = do { local $/; <$upload_fh> };
    }
    if (!$raw_data) {
        my $base64 = $cgi->param("base64_data") || "";
        if ($base64 =~ /data:image\/(?:jpeg|jpg|png|gif|webp);base64,(.+)$/s) {
            my $clean_b64 = $1;
            $clean_b64 =~ s/[\r\n\t]//g;
            $clean_b64 =~ s/ /+/g;
            $raw_data = MIME::Base64::decode_base64($clean_b64);
        }
    }

    if (!$raw_data) {
        print $json->encode({ success => 0, error => "Không nhận được dữ liệu file ảnh hợp lệ" });
        exit;
    }

    eval {
        GD::Image->trueColor(1);
        my $srcimage = eval { GD::Image->new($raw_data) }
                    || eval { GD::Image->newFromPngData($raw_data) }
                    || eval { GD::Image->newFromJpegData($raw_data) }
                    || eval { GD::Image->newFromGifData($raw_data) }
                    || eval { GD::Image->newFromWebpData($raw_data) };
        if (!$srcimage) {
            die "Không thể nhận diện định dạng hình ảnh (chỉ hỗ trợ JPG, PNG, WebP, GIF)";
        }

        # Xóa các ảnh bìa cũ của biểu ghi nếu có
        eval { $biblio->cover_images->delete; };

        # Tạo và lưu ảnh mới
        my $cover = Koha::CoverImage->new({
            biblionumber => $biblionumber,
            src_image    => $srcimage,
            mimetype     => 'image/png'
        })->store;

        print $json->encode({ 
            success     => 1, 
            message     => "Đã cập nhật ảnh bìa thành công",
            thumb_url   => "/cgi-bin/koha/catalogue/image.pl?biblionumber=$biblionumber&thumbnail=1&t=" . time(),
            imagenumber => $cover->imagenumber
        });
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi xử lý ảnh: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 5. AJAX: Xóa ảnh bìa (Delete Cover)
# -------------------------------------------------------------
if ( $op eq "delete_cover" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    eval {
        $biblio->cover_images->delete;
        print $json->encode({ success => 1, message => "Đã xóa ảnh bìa thành công" });
    };
    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi xóa ảnh: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 6. AJAX: Thêm bản sách ĐKCB mới (Add Item)
# -------------------------------------------------------------
if ( $op eq "add_item" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber   = int($cgi->param("biblionumber") || 0);
    my $barcode        = $cgi->param("barcode") // "";
    my $itemcallnumber = $cgi->param("itemcallnumber") // "";
    my $homebranch     = $cgi->param("homebranch") || "CPL";
    my $location       = $cgi->param("location") || "GEN";
    my $itype          = $cgi->param("itype") || "BK";

    $barcode =~ s/^\s+|\s+$//g;

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    # Kiểm tra giới hạn số lượng sách của biểu ghi (số lượng ĐKCB không được vượt số lượng sách)
    my ($allowed_qty) = $dbh->selectrow_array(
        "SELECT quantity FROM biblio_quantities WHERE biblionumber = ?",
        undef, $biblionumber
    );
    my $current_count = Koha::Items->search({ biblionumber => $biblionumber })->count;

    if (defined $allowed_qty && $allowed_qty == 0) {
        print $json->encode({
            success => 0,
            error   => "Biểu ghi chưa được thiết lập số lượng sách (hiện là 0 bản). Vui lòng bấm vào ô số lượng bản để cập nhật số lượng sách trước khi tạo ĐKCB!"
        });
        exit;
    } elsif (defined $allowed_qty && $current_count >= $allowed_qty) {
        print $json->encode({
            success => 0,
            error   => "Số lượng đăng ký cá biệt ($current_count bản) đã đạt tối đa số lượng sách của biểu ghi ($allowed_qty cuốn). Không thể tạo thêm ĐKCB mới!"
        });
        exit;
    }

    # Nếu chưa có mã vạch, tự sinh
    if ($barcode eq "") {
        my $sth = $dbh->prepare("SELECT barcode FROM items WHERE barcode LIKE 'FTU%' ORDER BY itemnumber DESC LIMIT 30");
        $sth->execute();
        my $max_num = 0;
        while (my ($bc) = $sth->fetchrow_array) {
            if ($bc =~ /^FTU(\d+)$/) {
                my $num = int($1);
                $max_num = $num if $num > $max_num;
            }
        }
        $barcode = sprintf("FTU%06d", $max_num > 0 ? $max_num + 1 : 100001);
    }

    # Kiểm tra mã vạch trùng
    my $chk = $dbh->prepare("SELECT itemnumber FROM items WHERE barcode = ?");
    $chk->execute($barcode);
    if (my ($dup_id) = $chk->fetchrow_array) {
        print $json->encode({ success => 0, error => "Mã đăng ký cá biệt (Mã vạch) '$barcode' đã được sử dụng bởi cuốn sách khác (#$dup_id)!" });
        exit;
    }

    eval {
        my $biblioitem = $biblio->biblioitem;
        my $bin = $biblioitem ? $biblioitem->biblioitemnumber : $biblionumber;

        my $item = Koha::Item->new({
            biblionumber     => $biblionumber,
            biblioitemnumber => $bin,
            barcode          => $barcode,
            itemcallnumber   => $itemcallnumber,
            homebranch       => $homebranch,
            holdingbranch    => $homebranch,
            location         => $location,
            itype            => $itype,
            dateaccessioned  => sprintf("%04d-%02d-%02d", (localtime)[5]+1900, (localtime)[4]+1, (localtime)[3]),
            notforloan       => 0,
            itemlost         => 0,
            damaged          => 0,
            withdrawn        => 0
        })->store;

        # Lấy tên chi nhánh để hiển thị
        my $br_sth = $dbh->prepare("SELECT branchname FROM branches WHERE branchcode = ?");
        $br_sth->execute($homebranch);
        my ($branchname) = $br_sth->fetchrow_array;
        $branchname ||= $homebranch;

        print $json->encode({
            success     => 1,
            message     => "Đã thêm bản sách ĐKCB thành công",
            total_items => $current_count + 1,
            quantity    => defined $allowed_qty ? $allowed_qty : ($current_count + 1),
            item        => {
                itemnumber      => $item->itemnumber,
                barcode         => $barcode,
                itemcallnumber  => $itemcallnumber,
                homebranch      => $homebranch,
                branchname      => $branchname,
                location        => $location,
                dateaccessioned => format_date_dmy($item->dateaccessioned),
                status_label    => "Sẵn sàng"
            }
        });
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi tạo bản sách: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 7. AJAX: Cập nhật thông tin bản sách ĐKCB (Edit Item / Barcode)
# -------------------------------------------------------------
if ( $op eq "edit_item" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $itemnumber     = int($cgi->param("itemnumber") || 0);
    my $new_barcode    = $cgi->param("barcode") // "";
    my $itemcallnumber = $cgi->param("itemcallnumber") // "";
    my $homebranch     = $cgi->param("homebranch") // "";
    my $location       = $cgi->param("location") // "";

    $new_barcode    =~ s/^\s+|\s+$//g;
    $itemcallnumber =~ s/^\s+|\s+$//g;

    if ($new_barcode eq "") {
        print $json->encode({ success => 0, error => "Mã ĐKCB (Barcode) không được để trống" });
        exit;
    }

    my $item = eval { Koha::Items->find($itemnumber) };
    if (!$item) {
        print $json->encode({ success => 0, error => "Không tìm thấy bản sách #$itemnumber" });
        exit;
    }

    # Kiểm tra trùng lặp barcode nếu barcode thay đổi
    if ($new_barcode ne ($item->barcode // "")) {
        my $existing = eval { Koha::Items->find({ barcode => $new_barcode }) };
        if ($existing && $existing->itemnumber != $itemnumber) {
            print $json->encode({ 
                success => 0, 
                error   => "Mã ĐKCB '$new_barcode' đã tồn tại trên bản sách khác (Biểu ghi #" . $existing->biblionumber . "). Vui lòng chọn mã khác!" 
            });
            exit;
        }
    }

    eval {
        $item->barcode($new_barcode);
        $item->itemcallnumber($itemcallnumber) if defined $itemcallnumber;
        $item->homebranch($homebranch) if length($homebranch);
        $item->holdingbranch($homebranch) if length($homebranch);
        $item->location($location) if length($location);
        $item->store;
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi cập nhật bản sách: $@" });
    } else {
        # Lấy tên chi nhánh và mô tả vị trí kho để hiển thị
        my $br_sth = $dbh->prepare("SELECT branchname FROM branches WHERE branchcode = ?");
        $br_sth->execute($item->homebranch);
        my ($branchname) = $br_sth->fetchrow_array;
        $branchname ||= $item->homebranch;

        my $loc_desc = "";
        if ($item->location) {
            my ($av_desc) = $dbh->selectrow_array("SELECT lib FROM authorised_values WHERE category = 'LOC' AND authorised_value = ?", undef, $item->location);
            $loc_desc = $av_desc || $item->location;
        }

        print $json->encode({
            success => 1,
            message => "Đã cập nhật mã ĐKCB '$new_barcode' và thông tin bản sách thành công",
            item    => {
                itemnumber      => $item->itemnumber,
                biblionumber    => $item->biblionumber,
                barcode         => $item->barcode,
                itemcallnumber  => $item->itemcallnumber,
                homebranch      => $item->homebranch,
                branchname      => $branchname,
                location        => $item->location,
                location_desc   => $loc_desc
            }
        });
    }
    exit;
}

# -------------------------------------------------------------
# 8. AJAX: Xóa 1 bản sách (Delete Item)
# -------------------------------------------------------------
if ( $op eq "delete_item" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $itemnumber = int($cgi->param("itemnumber") || 0);

    my $item = eval { Koha::Items->find($itemnumber) };
    if (!$item) {
        print $json->encode({ success => 0, error => "Không tìm thấy bản sách #$itemnumber" });
        exit;
    }

    if ($item->onloan) {
        print $json->encode({ success => 0, error => "Bản sách đang được bạn đọc mượn, không thể xóa!" });
        exit;
    }

    eval {
        my $biblionumber = $item->biblionumber;
        $item->delete;
        print $json->encode({ 
            success      => 1, 
            message      => "Đã xóa bản sách thành công",
            itemnumber   => $itemnumber,
            biblionumber => $biblionumber
        });
    };
    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi xóa bản sách: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 8. AJAX: Cập nhật số lượng sách (Update Book Quantity)
# -------------------------------------------------------------
if ( $op eq "update_quantity" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);
    my $quantity     = int($cgi->param("quantity") // -1);

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    if ($quantity < 0) {
        print $json->encode({ success => 0, error => "Số lượng sách phải là số nguyên không âm (>= 0)" });
        exit;
    }

    my $current_items = Koha::Items->search({ biblionumber => $biblionumber })->count;
    if ($quantity < $current_items) {
        print $json->encode({
            success => 0,
            error   => "Số lượng sách ($quantity) không được nhỏ hơn số lượng bản ĐKCB hiện có ($current_items bản)!"
        });
        exit;
    }

    eval {
        $dbh->do(
            "INSERT INTO biblio_quantities (biblionumber, quantity) VALUES (?, ?) ON DUPLICATE KEY UPDATE quantity = VALUES(quantity)",
            undef, $biblionumber, $quantity
        );
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi lưu số lượng sách: $@" });
    } else {
        print $json->encode({
            success      => 1,
            message      => "Đã cập nhật số lượng sách thành công ($quantity cuốn)",
            biblionumber => $biblionumber,
            quantity     => $quantity,
            total_items  => $current_items
        });
    }
    exit;
}

# -------------------------------------------------------------
# 9. AJAX: Xóa toàn bộ biểu ghi & bản sách (Delete Biblio)
# -------------------------------------------------------------
if ( $op eq "delete_biblio" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $biblionumber = int($cgi->param("biblionumber") || 0);

    my $biblio = eval { Koha::Biblios->find($biblionumber) };
    if (!$biblio) {
        print $json->encode({ success => 0, error => "Không tìm thấy biểu ghi #$biblionumber" });
        exit;
    }

    # Kiểm tra xem có bản sách nào đang mượn không
    my $items = $biblio->items;
    my $onloan_count = 0;
    while (my $it = $items->next) {
        if ($it->onloan) {
            $onloan_count++;
        }
    }

    if ($onloan_count > 0) {
        print $json->encode({ 
            success => 0, 
            error   => "Không thể xóa: Biểu ghi đang có $onloan_count cuốn sách đang được mượn bởi bạn đọc!" 
        });
        exit;
    }

    eval {
        # 1. Xóa toàn bộ bản sách
        my $all_items = $biblio->items;
        while (my $it = $all_items->next) {
            $it->delete;
        }

        # 2. Xóa ảnh bìa
        eval { $biblio->cover_images->delete; };

        # 3. Xóa biểu ghi thư mục
        my $del_err = DelBiblio($biblionumber);
        if ($del_err) {
            die $del_err;
        }

        print $json->encode({ 
            success      => 1, 
            message      => "Đã xóa biểu ghi và toàn bộ bản sách liên quan thành công",
            biblionumber => $biblionumber
        });
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi xóa biểu ghi: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 9. AJAX: Tạo nhanh biểu ghi mới + ĐKCB (Quick Create)
# -------------------------------------------------------------
if ( $op eq "quick_create" ) {
    print $cgi->header( -type => "application/json", -charset => "utf-8" );
    my $title        = $cgi->param("title") // "";
    my $author       = $cgi->param("author") // "";
    my $isbn         = $cgi->param("isbn") // "";
    my $publisher    = $cgi->param("publishercode") // "";
    my $pubyear      = $cgi->param("publicationyear") // "";
    my $classif      = $cgi->param("classification") // "";
    my $cutter       = $cgi->param("cutter") // "";
    my $itemtype     = $cgi->param("itemtype") || "BK";
    my $homebranch   = $cgi->param("homebranch") || "CPL";
    my $num_items    = int($cgi->param("num_items") || 1);
    my $barcode_pfx  = $cgi->param("barcode_prefix") || "FTU";

    $title   =~ s/^\s+|\s+$//g;
    $classif =~ s/^\s+|\s+$//g;
    $cutter  =~ s/^\s+|\s+$//g;

    if ($title eq "") {
        print $json->encode({ success => 0, error => "Nhan đề tài liệu không được để trống" });
        exit;
    }

    $num_items = 1 if $num_items < 1;
    $num_items = 20 if $num_items > 20;

    eval {
        # 1. Tạo MARC21 Record
        my $record = MARC::Record->new();
        $record->leader("00000nam a2200000   4500");
        $record->add_fields(
            MARC::Field->new("008", sprintf("%02d%02d%02ds%4s    xx            000 0 eng d", 
                (localtime)[5] % 100, (localtime)[4]+1, (localtime)[3], 
                $pubyear =~ /^\d{4}$/ ? $pubyear : (localtime)[5]+1900)),
            MARC::Field->new("245", "1", "0", "a" => $title)
        );
        $record->add_fields(MARC::Field->new("100", "1", " ", "a" => $author)) if length($author);
        $record->add_fields(MARC::Field->new("020", " ", " ", "a" => $isbn)) if length($isbn);
        $record->add_fields(MARC::Field->new("260", " ", " ", "b" => $publisher, "c" => $pubyear)) if (length($publisher) || length($pubyear));

        # 082 DDC & Cutter
        my @sfs_082;
        push @sfs_082, ('a' => $classif) if length($classif);
        push @sfs_082, ('b' => $cutter) if length($cutter);
        push @sfs_082, ('2' => '23');
        $record->add_fields(MARC::Field->new("082", "0", "4", @sfs_082)) if @sfs_082 > 1;

        # 942 Koha Mapping
        my @sfs_942 = ('2' => 'ddc');
        push @sfs_942, ('c' => $itemtype) if length($itemtype);
        push @sfs_942, ('h' => $classif) if length($classif);
        push @sfs_942, ('i' => $cutter) if length($cutter);
        $record->add_fields(MARC::Field->new("942", " ", " ", @sfs_942));

        # 2. Thêm vào Koha
        my ($biblionumber, $biblioitemnumber) = AddBiblio($record, "");
        if (!$biblionumber) {
            die "Không thể khởi tạo biểu ghi thư mục";
        }

        # Cập nhật thêm thông tin vào biblio / biblioitems nếu cần
        my $biblio = Koha::Biblios->find($biblionumber);
        if ($biblio) {
            $biblio->copyrightdate(int($pubyear)) if ($pubyear =~ /^\d+$/);
            $biblio->store;
            my $bi = $biblio->biblioitem;
            if ($bi) {
                $bi->itemtype($itemtype);
                $bi->cn_class($classif) if length($classif);
                $bi->cn_item($cutter) if length($cutter);
                $bi->cn_source('ddc');
                $bi->store;
            }
        }

        # 3. Tạo các bản sách ĐKCB
        my @created_barcodes;
        my $sth = $dbh->prepare("SELECT barcode FROM items WHERE barcode LIKE ? ORDER BY itemnumber DESC LIMIT 30");
        $sth->execute("$barcode_pfx%");
        my $curr_num = 0;
        while (my ($bc) = $sth->fetchrow_array) {
            if ($bc =~ /^$barcode_pfx(\d+)$/) {
                my $num = int($1);
                $curr_num = $num if $num > $curr_num;
            }
        }
        $curr_num = 100000 if $curr_num == 0;

        my $item_callno;
        if ($classif && $cutter) {
            if ($classif =~ /\Q$cutter\E/) {
                $item_callno = $classif;
            } elsif ($classif =~ m{/$}) {
                $item_callno = "$classif$cutter";
            } else {
                $item_callno = "$classif/$cutter";
            }
        } else {
            $item_callno = $classif || $cutter || "";
        }

        for (my $i = 1; $i <= $num_items; $i++) {
            $curr_num++;
            my $new_bc = sprintf("%s%06d", $barcode_pfx, $curr_num);
            my $item = Koha::Item->new({
                biblionumber     => $biblionumber,
                biblioitemnumber => $biblioitemnumber,
                barcode          => $new_bc,
                itemcallnumber   => $item_callno,
                homebranch       => $homebranch,
                holdingbranch    => $homebranch,
                location         => "GEN",
                itype            => $itemtype,
                dateaccessioned  => sprintf("%04d-%02d-%02d", (localtime)[5]+1900, (localtime)[4]+1, (localtime)[3]),
                notforloan       => 0,
                itemlost         => 0,
                damaged          => 0,
                withdrawn        => 0
            })->store;
            push @created_barcodes, $new_bc;
        }

        $dbh->do(
            "INSERT INTO biblio_quantities (biblionumber, quantity) VALUES (?, ?) ON DUPLICATE KEY UPDATE quantity = VALUES(quantity)",
            undef, $biblionumber, $num_items
        );

        print $json->encode({
            success      => 1,
            message      => "Đã tạo biểu ghi và $num_items bản sách ĐKCB thành công",
            biblionumber => $biblionumber,
            barcodes     => \@created_barcodes
        });
    };

    if ($@) {
        print $json->encode({ success => 0, error => "Lỗi tạo biểu ghi nhanh: $@" });
    }
    exit;
}

# -------------------------------------------------------------
# 10. Mặc định: Hiển thị danh sách biểu ghi & ĐKCB (List View)
# -------------------------------------------------------------
my $q          = $cgi->param("q") // "";
my $itemtype   = $cgi->param("itemtype") // "";
my $branch     = $cgi->param("branch") // "";
my $has_cover  = $cgi->param("has_cover") // "";
my $has_items  = $cgi->param("has_items") // "";
my $page       = int($cgi->param("page") || 1);
my $limit      = int($cgi->param("limit") || 15);
my $sort       = $cgi->param("sort") || "newest";

$page = 1 if $page < 1;
$limit = 15 if ($limit != 10 && $limit != 15 && $limit != 25 && $limit != 50 && $limit != 100);
my $offset = ($page - 1) * $limit;

# Xây dựng câu truy vấn điều kiện
my @where = ("1=1");
my @params;

if ($q ne "") {
    push @where, "(b.title LIKE ? OR b.author LIKE ? OR bi.isbn LIKE ? OR b.biblionumber = ? OR EXISTS (SELECT 1 FROM items i_search WHERE i_search.biblionumber = b.biblionumber AND i_search.barcode LIKE ?))";
    my $like_q = "%$q%";
    my $bib_id = ($q =~ /^\d+$/) ? int($q) : -1;
    push @params, ($like_q, $like_q, $like_q, $bib_id, $like_q);
}

if ($itemtype ne "") {
    push @where, "bi.itemtype = ?";
    push @params, $itemtype;
}

if ($branch ne "") {
    push @where, "EXISTS (SELECT 1 FROM items i_br WHERE i_br.biblionumber = b.biblionumber AND i_br.homebranch = ?)";
    push @params, $branch;
}

if ($has_cover eq "1") {
    push @where, "EXISTS (SELECT 1 FROM cover_images ci WHERE ci.biblionumber = b.biblionumber)";
} elsif ($has_cover eq "0") {
    push @where, "NOT EXISTS (SELECT 1 FROM cover_images ci WHERE ci.biblionumber = b.biblionumber)";
}

if ($has_items eq "1") {
    push @where, "EXISTS (SELECT 1 FROM items i_has WHERE i_has.biblionumber = b.biblionumber)";
} elsif ($has_items eq "0") {
    push @where, "NOT EXISTS (SELECT 1 FROM items i_has WHERE i_has.biblionumber = b.biblionumber)";
}

my $where_clause = join(" AND ", @where);

# Đếm tổng số biểu ghi thỏa điều kiện
my $count_sql = qq{
    SELECT COUNT(*)
    FROM biblio b
    LEFT JOIN biblioitems bi ON b.biblionumber = bi.biblionumber
    WHERE $where_clause
};
my $sth_count = $dbh->prepare($count_sql);
$sth_count->execute(@params);
my ($total_rows) = $sth_count->fetchrow_array;
$total_rows ||= 0;

my $total_pages = int(($total_rows + $limit - 1) / $limit);
$total_pages = 1 if $total_pages < 1;

# Sắp xếp
my $order_by = "b.biblionumber DESC";
if ($sort eq "title_asc") {
    $order_by = "b.title ASC, b.biblionumber DESC";
} elsif ($sort eq "author_asc") {
    $order_by = "b.author ASC, b.biblionumber DESC";
}

# Lấy danh sách biểu ghi của trang hiện tại (tương thích mọi sql_mode ONLY_FULL_GROUP_BY)
my $list_sql = qq{
    SELECT 
        b.biblionumber,
        b.title,
        b.subtitle,
        b.author,
        b.copyrightdate,
        b.datecreated,
        bi.isbn,
        bi.publishercode,
        bi.publicationyear,
        bi.cn_class,
        bi.cn_item,
        bi.cn_source,
        COALESCE(NULLIF(bi.cn_class, ''), (SELECT itemcallnumber FROM items WHERE biblionumber = b.biblionumber AND itemcallnumber IS NOT NULL AND itemcallnumber != '' LIMIT 1)) AS classification,
        bi.pages,
        bi.itemtype,
        it.description AS itemtype_desc,
        (SELECT imagenumber FROM cover_images ci WHERE ci.biblionumber = b.biblionumber LIMIT 1) AS cover_image_id,
        (SELECT COUNT(*) FROM items i WHERE i.biblionumber = b.biblionumber) AS total_items,
        (SELECT COUNT(*) FROM items i WHERE i.biblionumber = b.biblionumber AND i.onloan IS NULL AND (i.notforloan = 0 OR i.notforloan IS NULL) AND (i.itemlost = 0 OR i.itemlost IS NULL) AND (i.withdrawn = 0 OR i.withdrawn IS NULL) AND (i.damaged = 0 OR i.damaged IS NULL)) AS available_items,
        (SELECT COUNT(*) FROM items i WHERE i.biblionumber = b.biblionumber AND i.onloan IS NOT NULL) AS onloan_items,
        COALESCE(bq.quantity, (SELECT COUNT(*) FROM items i WHERE i.biblionumber = b.biblionumber), 0) AS book_quantity
    FROM biblio b
    LEFT JOIN biblioitems bi ON b.biblionumber = bi.biblionumber
    LEFT JOIN itemtypes it ON bi.itemtype = it.itemtype
    LEFT JOIN biblio_quantities bq ON b.biblionumber = bq.biblionumber
    WHERE $where_clause
    ORDER BY $order_by
    LIMIT ? OFFSET ?
};

my $sth_list = $dbh->prepare($list_sql);
$sth_list->execute(@params, $limit, $offset);
my @records;
my @page_biblionumbers;

while (my $row = $sth_list->fetchrow_hashref) {
    $row->{items} = [];
    $row->{total_items} ||= 0;
    $row->{available_items} ||= 0;
    $row->{onloan_items} ||= 0;
    push @records, $row;
    push @page_biblionumbers, $row->{biblionumber};
}

# Lấy danh sách items (ĐKCB) của các biểu ghi trên trang này
my %items_by_biblio;
if (@page_biblionumbers) {
    my $placeholders = join(",", map { "?" } @page_biblionumbers);
    my $items_sql = qq{
        SELECT 
            i.itemnumber,
            i.biblionumber,
            i.barcode,
            i.itemcallnumber,
            i.homebranch,
            br.branchname,
            i.location,
            av_loc.lib AS location_desc,
            i.itype,
            i.notforloan,
            i.itemlost,
            i.damaged,
            i.withdrawn,
            i.onloan,
            i.dateaccessioned
        FROM items i
        LEFT JOIN branches br ON i.homebranch = br.branchcode
        LEFT JOIN authorised_values av_loc ON (av_loc.category = 'LOC' AND av_loc.authorised_value = i.location)
        WHERE i.biblionumber IN ($placeholders)
        ORDER BY i.itemnumber ASC
    };
    my $sth_items = $dbh->prepare($items_sql);
    $sth_items->execute(@page_biblionumbers);

    while (my $it = $sth_items->fetchrow_hashref) {
        $it->{dateaccessioned} = format_date_dmy($it->{dateaccessioned});
        # Xác định nhãn trạng thái lưu thông
        if ($it->{onloan}) {
            $it->{status_code} = "onloan";
            $it->{status_label} = "Đang mượn (đến " . format_date_dmy($it->{onloan}) . ")";
        } elsif ($it->{itemlost}) {
            $it->{status_code} = "lost";
            $it->{status_label} = "Mất sách";
        } elsif ($it->{damaged}) {
            $it->{status_code} = "damaged";
            $it->{status_label} = "Hư hỏng";
        } elsif ($it->{withdrawn}) {
            $it->{status_code} = "withdrawn";
            $it->{status_label} = "Đã thanh lý";
        } elsif ($it->{notforloan}) {
            $it->{status_code} = "notforloan";
            $it->{status_label} = "Không cho mượn";
        } else {
            $it->{status_code} = "available";
            $it->{status_label} = "Sẵn sàng";
        }
        push @{ $items_by_biblio{$it->{biblionumber}} }, $it;
    }
}

# Bổ sung items và làm giàu thông tin phân loại DDC & Cutter từ MARC
foreach my $rec (@records) {
    $rec->{datecreated} = format_date_dmy($rec->{datecreated});
    if ($items_by_biblio{$rec->{biblionumber}}) {
        $rec->{items} = $items_by_biblio{$rec->{biblionumber}};
    }
    if (!$rec->{classification} || !$rec->{cn_item}) {
        my $bib = Koha::Biblios->find($rec->{biblionumber});
        if ($bib && $bib->metadata && $bib->metadata->record) {
            my $mrec = $bib->metadata->record;
            my $f082 = $mrec->field('082') || $mrec->field('092') || $mrec->field('084');
            if ($f082) {
                $rec->{classification} ||= $f082->subfield('a');
                $rec->{cn_item} ||= $f082->subfield('b');
            }
            if (!$rec->{classification} || !$rec->{cn_item}) {
                my $f942 = $mrec->field('942');
                if ($f942) {
                    $rec->{classification} ||= $f942->subfield('h');
                    $rec->{cn_item} ||= $f942->subfield('i');
                }
            }
        }
    }
    $rec->{cutter} = $rec->{cn_item} // "";
    if ($rec->{classification} && $rec->{cutter}) {
        if ($rec->{classification} =~ /\Q$rec->{cutter}\E/) {
            $rec->{callnumber} = $rec->{classification};
        } elsif ($rec->{classification} =~ m{/$}) {
            $rec->{callnumber} = "$rec->{classification}$rec->{cutter}";
        } else {
            $rec->{callnumber} = "$rec->{classification}/$rec->{cutter}";
        }
    } else {
        $rec->{callnumber} = $rec->{classification} || $rec->{cutter} || "";
    }
    $rec->{book_quantity} = int($rec->{book_quantity} || 0);
}

# Tạo danh sách phân trang (pages_loop)
my @pages_loop;
my $start_p = $page - 3 > 1 ? $page - 3 : 1;
my $end_p   = $page + 3 < $total_pages ? $page + 3 : $total_pages;

for (my $p = $start_p; $p <= $end_p; $p++) {
    push @pages_loop, {
        page_num => $p,
        is_current => ($p == $page) ? 1 : 0
    };
}

# Lấy danh mục Item Types, Branches và Locations cho bộ lọc & modal
my $itemtypes = Koha::ItemTypes->search( {}, { order_by => 'description' } );
my $branches  = Koha::Libraries->search( {}, { order_by => 'branchname' } );
my $locations = Koha::AuthorisedValues->search( { category => 'LOC' }, { order_by => 'lib' } );

$template->param(
    records        => \@records,
    total_records  => $total_rows,
    current_page   => $page,
    total_pages    => $total_pages,
    limit          => $limit,
    pages_loop     => \@pages_loop,
    prev_page      => ($page > 1 ? $page - 1 : undef),
    next_page      => ($page < $total_pages ? $page + 1 : undef),
    q              => $q,
    selected_type  => $itemtype,
    selected_br    => $branch,
    has_cover      => $has_cover,
    has_items      => $has_items,
    sort           => $sort,
    itemtypes      => $itemtypes,
    branches       => $branches,
    locations      => $locations,
);

output_html_with_http_headers $cgi, $cookie, $template->output;