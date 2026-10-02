#!/usr/bin/perl

use Modern::Perl;
use CGI qw( -utf8 );

my $cgi = CGI->new;
my %params = $cgi->Vars;
$params{section} = "database";
my $query_str = join("&", map { "$_=" . $cgi->escape($params{$_}) } keys %params);

print $cgi->redirect("/cgi-bin/koha/tools/portal-news.pl?$query_str");
