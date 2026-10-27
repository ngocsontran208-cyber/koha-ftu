#!/usr/bin/perl

# FTU Library - "Lời giới thiệu" view for a biblio
# Lists published introductions (librarian / reader) linked to the record
# via koha_portal_post_biblios. Managed in Tools > Portal news (portal_review).
#
# This file is part of Koha.
#
# Koha is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.

use Modern::Perl;
use utf8;

use C4::Auth   qw( get_template_and_user );
use C4::Context;
use C4::Output qw( output_html_with_http_headers redirect_if_opac_suppressed );
use CGI        qw ( -utf8 );
use C4::Reserves qw( IsAvailableForItemLevelRequest );
use C4::Koha     qw( GetNormalizedISBN );
use C4::Record   qw( marc2cites );
use Koha::ItemTypes;
use Koha::Patrons;
use Koha::Biblios;

my $query        = CGI->new();
my $biblionumber = $query->param('biblionumber');
my $biblio;
$biblio = Koha::Biblios->find( $biblionumber, { prefetch => [ 'metadata', 'items' ] } ) if $biblionumber;
if ( !$biblio ) {
    print $query->redirect('/cgi-bin/koha/errors/404.pl');
    exit;
}

redirect_if_opac_suppressed( $query, $biblio );

my ( $template, $loggedinuser, $cookie ) = get_template_and_user(
    {
        template_name   => "opac-intro.tt",
        query           => $query,
        type            => "opac",
        authnotrequired => ( C4::Context->preference("OpacPublic") ? 1 : 0 ),
    }
);

my $patron = Koha::Patrons->find($loggedinuser);

my $opachiddenitems_rules = C4::Context->yaml_preference('OpacHiddenItems');
unless ( $patron and $patron->category->override_hidden_items ) {
    if ( $biblio->hidden_in_opac( { rules => $opachiddenitems_rules } ) ) {
        print $query->redirect('/cgi-bin/koha/errors/404.pl');
        exit;
    }
}

my $record = $biblio->metadata->record;

if ( my $cart_list = $query->cookie("bib_list") ) {
    my @cart_list = split( /\//, $cart_list );
    $template->param( incart => 1 ) if grep { $_ eq $biblionumber } @cart_list;
}

my $marcflavour = C4::Context->preference("marcflavour");
my $isbn        = GetNormalizedISBN( undef, $record, $marcflavour );
$template->param(
    normalized_isbn           => $isbn,
    content_identifier_exists => ( $isbn ? 1 : 0 ),
);

# Holdability (needed by the detail sidebar)
my $holdable_items      = $biblio->items->filter_by_for_hold->count;
my $can_holds_be_placed = $patron ? 0 : $holdable_items;
if ($patron) {
    my $items = $biblio->items;
    while ( my $item = $items->next ) {
        $can_holds_be_placed = $can_holds_be_placed || IsAvailableForItemLevelRequest( $item, $patron, undef );
    }
}

if ( C4::Context->preference('ArticleRequests') ) {
    my $itemtype = Koha::ItemTypes->find( $biblio->itemtype );
    my $artreqpossible =
          $patron   ? $biblio->can_article_request($patron)
        : $itemtype ? $itemtype->may_article_request
        :             q{};
    $template->param( artreqpossible => $artreqpossible );
}

# Lời giới thiệu đã xuất bản cho biểu ghi này (thủ thư trước, bạn đọc sau)
my @intro_posts;
my $dbh = C4::Context->dbh;
my $sth = $dbh->prepare(q{
    SELECT p.id, p.title, p.post_type, p.author_name, p.classification,
           p.excerpt, p.featured_image, p.created_at, p.views_count,
           LEFT(p.content, 4000) AS content_head
    FROM koha_portal_posts p
    JOIN koha_portal_post_biblios pb ON pb.post_id = p.id
    WHERE pb.biblionumber = ?
      AND p.status = 'published'
      AND p.post_type IN ('intro_librarian', 'intro_reader')
    ORDER BY (p.post_type = 'intro_librarian') DESC, p.created_at DESC
});
$sth->execute( $biblio->biblionumber );
while ( my $row = $sth->fetchrow_hashref ) {
    my $ex = $row->{excerpt};
    if ( !defined $ex || $ex !~ /\S/ ) {
        $ex = $row->{content_head} // '';
        $ex =~ s/<[^>]*>/ /g;
        $ex =~ s/&nbsp;/ /g;
        $ex =~ s/\s+/ /g;
        $ex =~ s/^\s+|\s+$//g;
        $ex = substr( $ex, 0, 260 ) . '…' if length($ex) > 260;
    }
    $row->{excerpt_text} = $ex;
    delete $row->{content_head};
    if ( $row->{created_at} && $row->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/ ) {
        $row->{formatted_date} = "$3/$2/$1";
    }
    push @intro_posts, $row;
}

$template->param(
    ReservableItems => $can_holds_be_placed,
    biblio          => $biblio,
    borrowernumber  => $loggedinuser,
    intro_posts     => \@intro_posts,
    ftu_intro_count => scalar(@intro_posts),
    cites           => C4::Record::marc2cites($record),
);

output_html_with_http_headers $query, $cookie, $template->output;
