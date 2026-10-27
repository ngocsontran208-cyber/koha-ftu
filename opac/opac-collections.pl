#!/usr/bin/perl

# Copyright 2026 Koha Development Team
#
# This file is part of Koha.
#
# Koha is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

use Modern::Perl;
use utf8;
use CGI        qw( -utf8 );
use C4::Auth   qw( get_template_and_user );
use C4::Context;
use C4::Output qw( output_html_with_http_headers );

use URI::Escape qw( uri_escape_utf8 );

my $query = CGI->new;
my $dbh   = C4::Context->dbh;

# Đảm bảo bảng koha_collection_meta luôn tồn tại trên mọi môi trường DB
eval {
    $dbh->do("
        CREATE TABLE IF NOT EXISTS koha_collection_meta (
            ccode VARCHAR(80) NOT NULL PRIMARY KEY,
            description TEXT NULL,
            image_url VARCHAR(500) NULL,
            is_featured TINYINT(1) DEFAULT 1,
            sort_order INT(11) DEFAULT 99,
            parent_ccode VARCHAR(80) DEFAULT NULL,
            created_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP,
            updated_at TIMESTAMP DEFAULT CURRENT_TIMESTAMP ON UPDATE CURRENT_TIMESTAMP,
            INDEX idx_parent_ccode (parent_ccode)
        ) ENGINE=InnoDB DEFAULT CHARSET=utf8mb4 COLLATE=utf8mb4_unicode_ci
    ");
    $dbh->do("ALTER TABLE koha_collection_meta ADD COLUMN IF NOT EXISTS parent_ccode VARCHAR(80) DEFAULT NULL AFTER sort_order");
};

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name   => "opac-collections.tt",
        query           => $query,
        type            => "opac",
        authnotrequired => ( C4::Context->preference("OpacPublic") ? 1 : 0 ),
    }
);

my $filter_type = $query->param('filter') // 'all'; # 'all' or 'featured'
my $search_q    = $query->param('q') // '';
$search_q =~ s/^\s+|\s+$//g;

# 1. Fetch collections from authorised_values (category='CCODE') joined with koha_collection_meta and items count
my $sql = "
    SELECT 
        av.authorised_value AS code,
        COALESCE(av.lib_opac, av.lib, av.authorised_value) AS title,
        COALESCE(m.description, 'Tuyển tập các tài liệu, giáo trình và tài nguyên chuyên khảo phục vụ học tập và nghiên cứu.') AS description,
        COALESCE(m.image_url, av.imageurl, '/opac-tmpl/bootstrap/images/collections/bst_lap_trinh.jpg') AS image_url,
        COALESCE(m.is_featured, 1) AS is_featured,
        COALESCE(m.sort_order, 99) AS sort_order,
        COALESCE(m.parent_ccode, '') AS parent_ccode,
        COALESCE(item_stats.item_count, 0) AS item_count,
        COALESCE(item_stats.biblio_count, 0) AS biblio_count
    FROM authorised_values av
    LEFT JOIN koha_collection_meta m ON av.authorised_value = m.ccode
    LEFT JOIN (
        SELECT ccode, COUNT(*) AS item_count, COUNT(DISTINCT biblionumber) AS biblio_count 
        FROM items 
        WHERE ccode IS NOT NULL AND ccode != '' 
        GROUP BY ccode
    ) item_stats ON av.authorised_value = item_stats.ccode
    WHERE av.category = 'CCODE'
";

my @params;
if ( length($search_q) > 0 ) {
    $sql .= " AND (av.authorised_value LIKE ? OR av.lib LIKE ? OR av.lib_opac LIKE ? OR m.description LIKE ?)";
    my $like = "%$search_q%";
    push @params, ( $like, $like, $like, $like );
}

if ( $filter_type eq 'featured' ) {
    $sql .= " AND COALESCE(m.is_featured, 0) = 1";
}

$sql .= " ORDER BY COALESCE(m.sort_order, 99) ASC, av.lib ASC";

my $sth = $dbh->prepare($sql);
$sth->execute(@params);

my @all_collections;
my %by_code;
while ( my $row = $sth->fetchrow_hashref ) {
    $row->{children} = [];
    $by_code{$row->{code}} = $row;
    push @all_collections, $row;
}

# Attach children collections to their parent
for my $col (@all_collections) {
    if ( $col->{parent_ccode} && exists $by_code{$col->{parent_ccode}} ) {
        push @{ $by_code{$col->{parent_ccode}}->{children} }, $col;
        $col->{is_child} = 1;
    } else {
        $col->{is_child} = 0;
    }
}

# Build top-level collections array
my @collections;
for my $col (@all_collections) {
    # Skip child collections at top-level grid unless user is searching explicitly
    if ( $col->{is_child} && length($search_q) == 0 ) {
        next;
    }

    my $children = $col->{children} || [];
    if ( @$children ) {
        $col->{has_children} = 1;
        $col->{children_count} = scalar(@$children);
        
        my $total_items = $col->{item_count} || 0;
        my @child_titles;
        for my $child (@$children) {
            $total_items += ($child->{item_count} || 0);
            push @child_titles, $child->{title};
        }
        $col->{total_item_count} = $total_items;
        $col->{children_search_terms} = join(' ', @child_titles);

        # Build combined search URL
        my @all_codes = ( $col->{code}, map { $_->{code} } @$children );
        $col->{combined_search_url} = join('&amp;', map { "limit=mc-ccode:" . uri_escape_utf8($_) } @all_codes);
    } else {
        $col->{has_children} = 0;
        $col->{children_count} = 0;
        $col->{total_item_count} = $col->{item_count} || 0;
        $col->{children_search_terms} = '';
        $col->{combined_search_url} = "limit=mc-ccode:" . uri_escape_utf8($col->{code});
    }

    push @collections, $col;
}

# Count totals for filter tabs (based on top-level collections)
my $count_all = scalar(@collections);
my $count_feat = 0;
for my $c (@collections) {
    $count_feat++ if $c->{is_featured};
}

# Check if public virtual shelves exist
my $sth_shelves = $dbh->prepare("
    SELECT vs.shelfnumber, vs.shelfname, COUNT(vsc.biblionumber) AS count
    FROM virtualshelves vs
    LEFT JOIN virtualshelfcontents vsc ON vs.shelfnumber = vsc.shelfnumber
    WHERE vs.public = 1
    GROUP BY vs.shelfnumber, vs.shelfname
    ORDER BY vs.shelfname
");
$sth_shelves->execute();
my @public_shelves;
while ( my $sh = $sth_shelves->fetchrow_hashref ) {
    push @public_shelves, $sh;
}

$template->param(
    collections       => \@collections,
    collections_count => scalar(@collections),
    count_all         => $count_all,
    count_featured    => $count_feat,
    public_shelves    => \@public_shelves,
    shelves_count     => scalar(@public_shelves),
    filter_type       => $filter_type,
    search_q          => $search_q,
);

output_html_with_http_headers $query, $cookie, $template->output;
