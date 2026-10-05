#!/usr/bin/perl

# Copyright 2023 Aleisha Amohia <aleisha@catalyst.net.nz>
#
# This file is part of Koha.
#
# Koha is free software; you can redistribute it and/or modify it
# under the terms of the GNU General Public License as published by
# the Free Software Foundation; either version 3 of the License, or
# (at your option) any later version.
#
# Koha is distributed in the hope that it will be useful, but
# WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with Koha; if not, see <https://www.gnu.org/licenses>.

use Modern::Perl;
use CGI qw ( -utf8 );
use C4::Context;
use C4::Output      qw( output_html_with_http_headers );
use C4::Auth        qw( get_template_and_user );
use Koha::DateUtils qw( dt_from_string );
use Koha::Patrons;

my $query = CGI->new;
my $op    = $query->param('op') // q{};

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name => "opac-user.tt",
        query         => $query,
        type          => "opac",
    }
);

my $logged_in_user = Koha::Patrons->find($borrowernumber);
my $message_id     = $query->param('message_id') // q{};
my $referer        = $query->param('referer') || $ENV{HTTP_REFERER} || '/cgi-bin/koha/opac-user.pl';

my $cgi_prefix = '/cgi-bin/koha/';
if ( $referer =~ m{^(/cgi-bin/[^/]+/)} ) {
    $cgi_prefix = $1;
} elsif ( $ENV{SCRIPT_NAME} && $ENV{SCRIPT_NAME} =~ m{^(/cgi-bin/[^/]+/)} ) {
    $cgi_prefix = $1;
}

my $target_url = ( $referer =~ /opac-messaging\.pl/ )
    ? "${cgi_prefix}opac-messaging.pl?tab=history"
    : "${cgi_prefix}opac-user.pl";

if ( $op =~ /^cud-/ ) {
    if ( $message_id eq 'all' ) {
        my $unread = $logged_in_user->messages->filter_by_unread;
        while ( my $m = $unread->next ) {
            $m->update( { patron_read_date => dt_from_string } );
        }
        print $query->redirect($target_url);
        exit;
    }

    my $message = $logged_in_user->messages->find($message_id);
    if ($message) {
        $message->update( { patron_read_date => dt_from_string } );
        print $query->redirect($target_url);
        exit;
    }
}

print $query->redirect($target_url);
exit;
