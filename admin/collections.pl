#!/usr/bin/perl

# Copyright 2026 Koha FTU Team
# Dedicated Collection Management Module for Koha (CCODE & OPAC Portal)

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );

use C4::Context;
use C4::Auth   qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use Try::Tiny  qw( try catch );

my $input = CGI->new;
my $op    = $input->param('op') // 'list';

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name => "admin/collections.tt",
        query         => $input,
        type          => "intranet",
        flagsrequired => { parameters => 'manage_auth_values' },
    }
);

my $dbh = C4::Context->dbh;

# Đảm bảo bảng koha_collection_meta luôn tồn tại trên mọi môi trường DB
eval {
    $dbh->do("
        CREATE TABLE IF NOT EXISTS koha_collection_meta (
            ccode VARCHAR(80) NOT NULL PRIMARY KEY,
            description TEXT NULL,
            image_url VARCHAR(500) NULL,
            is_featured TINYINT(1) DEFAULT 1,
            sort_order INT(11) DEFAULT 99,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
    ");
};

my @messages;

# Preset image list for quick selection
my @preset_images = (
    {
        name => 'Khoa học Máy tính & Lập trình',
        url  => '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg',
    },
    {
        name => 'Cơ sở Dữ liệu & Mạng máy tính',
        url  => '/opac-tmpl/bootstrap/images/collections/bst_csdl_mang.jpg',
    },
    {
        name => 'Trí tuệ Nhân tạo & Khoa học Dữ liệu',
        url  => '/opac-tmpl/bootstrap/images/collections/bst_ai_data.jpg',
    },
    {
        name => 'Kinh tế học & Quản trị Kinh doanh',
        url  => '/opac-tmpl/bootstrap/images/collections/bst_kinh_te.jpg',
    },
    {
        name => 'Tài liệu Tra cứu & Chuyên khảo FTU',
        url  => '/opac-tmpl/bootstrap/images/collections/bst_ref.jpg',
    },
);

if ( $op eq 'cud-save' ) {
    my $is_new      = $input->param('is_new') // 0;
    my $ccode       = $input->param('ccode') // '';
    my $lib         = $input->param('lib') // '';
    my $description = $input->param('description') // '';
    my $image_url   = $input->param('image_url') // '';
    my $is_featured = $input->param('is_featured') ? 1 : 0;
    my $sort_order  = $input->param('sort_order') // 1;

    $ccode =~ s/^\s+|\s+$//g;
    $ccode = uc($ccode);
    $lib =~ s/^\s+|\s+$//g;
    $image_url =~ s/^\s+|\s+$//g;
    $sort_order = int($sort_order) || 1;

    # Handle image upload from computer if provided
    my $upload_fh   = $input->upload('upload_image');
    my $upload_name = $input->param('upload_image') || '';

    if ( $upload_fh && $upload_name ) {
        my ($ext) = ( $upload_name =~ /(\.[a-zA-Z0-9]+)$/ );
        $ext = lc($ext || '.jpg');
        if ( $ext !~ /^\.(jpg|jpeg|png|webp|gif)$/i ) {
            push @messages, { type => 'danger', code => 'error_invalid_image_type' };
        } else {
            my $dest_dir = C4::Context->config('intranetdir') . '/koha-tmpl/opac-tmpl/bootstrap/images/collections';
            my $safe_code = lc($ccode || 'collection');
            $safe_code =~ s/[^a-z0-9_]/_/g;
            my $new_filename = "bst_" . $safe_code . "_" . time() . $ext;
            my $dest_file = "$dest_dir/$new_filename";

            if ( open(my $out, '>', $dest_file) ) {
                binmode $out;
                binmode $upload_fh;
                my $buffer;
                while (my $bytes = read($upload_fh, $buffer, 4096)) {
                    print $out $buffer;
                }
                close $out;
                $image_url = "/opac-tmpl/bootstrap/images/collections/$new_filename";
            } else {
                warn "Failed to write uploaded image to $dest_file: $!";
            }
        }
    }

    $image_url ||= '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg';

    if ( !$ccode ) {
        push @messages, { type => 'danger', code => 'error_missing_ccode' };
        $op = $is_new ? 'add_form' : 'edit_form';
    } elsif ( !$lib ) {
        push @messages, { type => 'danger', code => 'error_missing_lib' };
        $op = $is_new ? 'add_form' : 'edit_form';
    } else {
        try {
            if ($is_new) {
                # Check if already exists in authorised_values
                my $sth_check = $dbh->prepare("SELECT COUNT(*) FROM authorised_values WHERE category = 'CCODE' AND authorised_value = ?");
                $sth_check->execute($ccode);
                my ($exists) = $sth_check->fetchrow_array;
                if ($exists) {
                    push @messages, { type => 'danger', code => 'error_duplicate_ccode', ccode => $ccode };
                    $op = 'add_form';
                } else {
                    my $sth_av = $dbh->prepare("INSERT INTO authorised_values (category, authorised_value, lib, lib_opac) VALUES ('CCODE', ?, ?, ?)");
                    $sth_av->execute($ccode, $lib, $lib);

                    my $sth_meta = $dbh->prepare("INSERT INTO koha_collection_meta (ccode, description, image_url, is_featured, sort_order) VALUES (?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE description=VALUES(description), image_url=VALUES(image_url), is_featured=VALUES(is_featured), sort_order=VALUES(sort_order)");
                    $sth_meta->execute($ccode, $description, $image_url, $is_featured, $sort_order);

                    push @messages, { type => 'success', code => 'success_add', ccode => $ccode, lib => $lib };
                    $op = 'list';
                }
            } else {
                # Update existing
                my $sth_av = $dbh->prepare("UPDATE authorised_values SET lib = ?, lib_opac = ? WHERE category = 'CCODE' AND authorised_value = ?");
                $sth_av->execute($lib, $lib, $ccode);

                my $sth_meta = $dbh->prepare("INSERT INTO koha_collection_meta (ccode, description, image_url, is_featured, sort_order) VALUES (?, ?, ?, ?, ?) ON DUPLICATE KEY UPDATE description=VALUES(description), image_url=VALUES(image_url), is_featured=VALUES(is_featured), sort_order=VALUES(sort_order)");
                $sth_meta->execute($ccode, $description, $image_url, $is_featured, $sort_order);

                push @messages, { type => 'success', code => 'success_update', ccode => $ccode, lib => $lib };
                $op = 'list';
            }
        } catch {
            push @messages, { type => 'danger', code => 'error_sql', text => "$_" };
            $op = 'list';
        };
    }
} elsif ( $op eq 'cud-toggle_featured' ) {
    my $ccode = $input->param('ccode');
    if ($ccode) {
        try {
            $dbh->do("INSERT INTO koha_collection_meta (ccode, is_featured) VALUES (?, 1) ON DUPLICATE KEY UPDATE is_featured = NOT is_featured", undef, $ccode);
            push @messages, { type => 'success', code => 'success_toggle', ccode => $ccode };
        } catch {
            push @messages, { type => 'danger', code => 'error_sql', text => "$_" };
        };
    }
    $op = 'list';
} elsif ( $op eq 'cud-delete' ) {
    my $ccode = $input->param('ccode');
    if ($ccode) {
        # Check items count
        my $sth_cnt = $dbh->prepare("SELECT COUNT(*) FROM items WHERE ccode = ?");
        $sth_cnt->execute($ccode);
        my ($cnt) = $sth_cnt->fetchrow_array;
        if ($cnt > 0) {
            push @messages, { type => 'danger', code => 'error_has_items', ccode => $ccode, items_count => $cnt };
        } else {
            try {
                $dbh->do("DELETE FROM koha_collection_meta WHERE ccode = ?", undef, $ccode);
                $dbh->do("DELETE FROM authorised_values WHERE category = 'CCODE' AND authorised_value = ?", undef, $ccode);
                push @messages, { type => 'success', code => 'success_delete', ccode => $ccode };
            } catch {
                push @messages, { type => 'danger', code => 'error_sql', text => "$_" };
            };
        }
    }
    $op = 'list';
}

if ( $op eq 'add_form' || $op eq 'edit_form' ) {
    my $col = {};
    if ( $op eq 'edit_form' ) {
        my $ccode = $input->param('ccode');
        my $sth = $dbh->prepare("
            SELECT 
                av.authorised_value as ccode,
                av.lib,
                av.lib_opac,
                COALESCE(m.description, '') as description,
                COALESCE(m.image_url, '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg') as image_url,
                COALESCE(m.is_featured, 0) as is_featured,
                COALESCE(m.sort_order, 1) as sort_order,
                COALESCE(ic.items_count, 0) as items_count
            FROM authorised_values av
            LEFT JOIN koha_collection_meta m ON av.authorised_value = m.ccode
            LEFT JOIN (
                SELECT ccode, COUNT(*) as items_count 
                FROM items 
                WHERE ccode IS NOT NULL AND ccode != '' 
                GROUP BY ccode
            ) ic ON av.authorised_value = ic.ccode
            WHERE av.category = 'CCODE' AND av.authorised_value = ?
        ");
        $sth->execute($ccode);
        $col = $sth->fetchrow_hashref();
    } else {
        $col = {
            ccode       => '',
            lib         => '',
            description => '',
            image_url   => '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg',
            is_featured => 1,
            sort_order  => 1,
            items_count => 0,
        };
    }

    $template->param(
        collection    => $col,
        is_add        => ( $op eq 'add_form' ? 1 : 0 ),
        preset_images => \@preset_images,
    );
} else {
    # List collections
    my $sth = $dbh->prepare("
        SELECT 
            av.id as av_id,
            av.authorised_value as ccode,
            av.lib,
            av.lib_opac,
            COALESCE(m.description, '') as description,
            COALESCE(m.image_url, '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg') as image_url,
            COALESCE(m.is_featured, 0) as is_featured,
            COALESCE(m.sort_order, 99) as sort_order,
            COALESCE(ic.items_count, 0) as items_count
        FROM authorised_values av
        LEFT JOIN koha_collection_meta m ON av.authorised_value = m.ccode
        LEFT JOIN (
            SELECT ccode, COUNT(*) as items_count 
            FROM items 
            WHERE ccode IS NOT NULL AND ccode != '' 
            GROUP BY ccode
        ) ic ON av.authorised_value = ic.ccode
        WHERE av.category = 'CCODE'
        ORDER BY m.is_featured DESC, m.sort_order ASC, av.lib ASC
    ");
    $sth->execute();
    my @collections;
    my $total_items = 0;
    my $featured_count = 0;

    while ( my $row = $sth->fetchrow_hashref() ) {
        $total_items += $row->{items_count} || 0;
        $featured_count++ if $row->{is_featured};
        push @collections, $row;
    }

    $template->param(
        collections    => \@collections,
        total_count    => scalar(@collections),
        total_items    => $total_items,
        featured_count => $featured_count,
    );
}

$template->param(
    op       => $op,
    messages => \@messages,
);

output_html_with_http_headers $input, $cookie, $template->output;
