#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;
my $id  = int($cgi->param("id") || 0);

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name   => "opac-news-detail.tt",
        type            => "opac",
        query           => $cgi,
        authnotrequired => 1,
    }
);

my $post;
if ($id > 0) {
    my $sth = $dbh->prepare("SELECT * FROM koha_portal_posts WHERE id = ?");
    $sth->execute($id);
    $post = $sth->fetchrow_hashref;
    if ($post) {
        if ($post->{post_type} eq 'database') {
            print $cgi->redirect("/cgi-bin/koha/opac-databases.pl");
            exit;
        }
        if ($post->{post_type} eq 'banner') {
            my $target = $post->{support_link} || "/";
            print $cgi->redirect($target);
            exit;
        }

        $dbh->do("UPDATE koha_portal_posts SET views_count = views_count + 1 WHERE id = ?", undef, $id);
        
        if ($post->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/) {
            $post->{created_day}   = sprintf("%02d", int($3));
            $post->{created_month} = "Th" . int($2);
            $post->{created_year}  = $1;
            $post->{formatted_date} = "$post->{created_day}/$2/$1";
        }
        if ($post->{event_start} && $post->{event_start} =~ /^(\d{4})-(\d{2})-(\d{2})\s+(\d{2}):(\d{2})/) {
            $post->{event_day}   = sprintf("%02d", int($3));
            $post->{event_month} = "Th" . int($2);
            $post->{event_year}  = $1;
            $post->{event_time}  = "$4:$5";
            $post->{formatted_event_date} = "$post->{event_day}/$2/$1";
        }
    }
}

# Fetch related recent posts (chỉ lấy bài viết/tin tức/sự kiện, loại trừ CSDL và Banner)
my $recent_sth = $dbh->prepare("SELECT id, title, post_type, created_at, featured_image, views_count FROM koha_portal_posts WHERE status = ? AND id != ? AND post_type NOT IN ('database', 'banner') ORDER BY created_at DESC LIMIT 5");
$recent_sth->execute("published", $id);
my @recent_posts;
while (my $row = $recent_sth->fetchrow_hashref) {
    if ($row->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/) {
        $row->{formatted_date} = "$3/$2/$1";
    }
    push @recent_posts, $row;
}

# Fetch previous and next posts for bottom navigation (loại trừ CSDL và Banner)
my $prev_sth = $dbh->prepare("SELECT id, title FROM koha_portal_posts WHERE status = ? AND id < ? AND post_type NOT IN ('database', 'banner') ORDER BY id DESC LIMIT 1");
$prev_sth->execute("published", $id);
my $prev_post = $prev_sth->fetchrow_hashref;

my $next_sth = $dbh->prepare("SELECT id, title FROM koha_portal_posts WHERE status = ? AND id > ? AND post_type != 'database' ORDER BY id ASC LIMIT 1");
$next_sth->execute("published", $id);
my $next_post = $next_sth->fetchrow_hashref;

$template->param(
    post         => $post,
    recent_posts => \@recent_posts,
    prev_post    => $prev_post,
    next_post    => $next_post,
);

output_html_with_http_headers $cgi, $cookie, $template->output;
