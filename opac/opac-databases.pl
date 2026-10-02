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
        template_name   => "opac-databases.tt",
        query           => $query,
        type            => "opac",
        authnotrequired => ( C4::Context->preference("OpacPublic") ? 1 : 0 ),
    }
);

my $filter_class = $query->param('class') // 'all';
my $search_q     = $query->param('q') // '';
$search_q =~ s/^\s+|\s+$//g;

# Count total published databases
my ( $total_count ) = $dbh->selectrow_array(
    "SELECT COUNT(*) FROM koha_portal_posts WHERE post_type = 'database' AND status = 'published'"
);

# Count per classification
my $sth_counts = $dbh->prepare(
    "SELECT classification, COUNT(*) as cnt FROM koha_portal_posts WHERE post_type = 'database' AND status = 'published' GROUP BY classification ORDER BY classification"
);
$sth_counts->execute();
my @class_counts;
while ( my $r = $sth_counts->fetchrow_hashref ) {
    push @class_counts, $r;
}

# Fetch databases
my $sql = "SELECT id, title, slug, excerpt, content, classification,
                  access_instructions, db_user, db_pass, support_link,
                  sort_order, views_count, created_at
           FROM koha_portal_posts
           WHERE post_type = 'database' AND status = 'published'";
my @params;

if ( $filter_class ne 'all' && $filter_class ne '' ) {
    $sql .= " AND classification = ?";
    push @params, $filter_class;
}

if ( length($search_q) > 0 ) {
    $sql .= " AND (title LIKE ? OR excerpt LIKE ? OR access_instructions LIKE ?)";
    my $like = "%$search_q%";
    push @params, ( $like, $like, $like );
}

$sql .= " ORDER BY sort_order ASC, id ASC";

my $sth = $dbh->prepare($sql);
$sth->execute(@params);
my @databases;
while ( my $row = $sth->fetchrow_hashref ) {
    push @databases, $row;
}

my $is_logged_in = $borrowernumber ? 1 : 0;

foreach my $row (@databases) {
    my $has_pass = ( defined $row->{db_pass} && length($row->{db_pass}) > 0 ) ? 1 : 0;
    $row->{has_pass} = $has_pass;
    if ( !$is_logged_in ) {
        delete $row->{db_pass};
    }
}

$template->param(
    databases       => \@databases,
    databases_count => scalar(@databases),
    total_count     => $total_count || 0,
    class_counts    => \@class_counts,
    current_class   => $filter_class,
    search_query    => $search_q,
    is_logged_in    => $is_logged_in,
);

output_html_with_http_headers $query, $cookie, $template->output;
