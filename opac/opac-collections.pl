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

my $query = CGI->new;
my $dbh   = C4::Context->dbh;

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

my @collections;
while ( my $row = $sth->fetchrow_hashref ) {
    push @collections, $row;
}

# Count totals for filter tabs
my ($count_all) = $dbh->selectrow_array("SELECT COUNT(*) FROM authorised_values WHERE category = 'CCODE'");
my ($count_feat) = $dbh->selectrow_array("
    SELECT COUNT(*) FROM authorised_values av 
    JOIN koha_collection_meta m ON av.authorised_value = m.ccode 
    WHERE av.category = 'CCODE' AND m.is_featured = 1
");

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
    count_all         => $count_all || scalar(@collections),
    count_featured    => $count_feat || 0,
    public_shelves    => \@public_shelves,
    shelves_count     => scalar(@public_shelves),
    filter_type       => $filter_type,
    search_q          => $search_q,
);

output_html_with_http_headers $query, $cookie, $template->output;
