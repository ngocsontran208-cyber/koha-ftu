#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use C4::Auth qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use C4::Context;
use POSIX qw( ceil );

my $cgi = CGI->new;
my $dbh = C4::Context->dbh;

my $page  = int($cgi->param("page") || 1);
$page = 1 if $page < 1;
my $limit = 10;

my $q = $cgi->param("q") || "";
$q =~ s/^\s+|\s+$//g;

my $filter_type = $cgi->param("type") || "all";

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name   => "opac-news.tt",
        type            => "opac",
        query           => $cgi,
        authnotrequired => 1,
    }
);

# Điều kiện lọc bài viết công khai
my $where = "status = 'published' AND post_type NOT IN ('database', 'banner')";
my @bind;

if ($filter_type ne "all") {
    $where .= " AND post_type = ?";
    push @bind, $filter_type;
}

if ($q ne "") {
    $where .= " AND (title LIKE ? OR excerpt LIKE ? OR content LIKE ?)";
    push @bind, "%$q%", "%$q%", "%$q%";
}

# Đếm tổng số bài viết
my $count_sth = $dbh->prepare("SELECT COUNT(*) FROM koha_portal_posts WHERE $where");
$count_sth->execute(@bind);
my ($total_rows) = $count_sth->fetchrow_array;
$total_rows ||= 0;

my $total_pages = ceil($total_rows / $limit) || 1;
$page = $total_pages if $page > $total_pages && $total_pages > 0;
my $offset = ($page - 1) * $limit;
$offset = 0 if $offset < 0;

# Lấy danh sách bài viết
my $sth = $dbh->prepare("
    SELECT id, slug, post_type, title, excerpt, featured_image, author_name, views_count, created_at, event_start, event_end, event_location, event_tag, classification
    FROM koha_portal_posts
    WHERE $where
    ORDER BY is_featured DESC, COALESCE(event_start, created_at) DESC, id DESC
    LIMIT $limit OFFSET $offset
");
$sth->execute(@bind);

my @posts;
while (my $row = $sth->fetchrow_hashref) {
    if ($row->{created_at} =~ /^(\d{4})-(\d{2})-(\d{2})/) {
        $row->{created_day}   = sprintf("%02d", int($3));
        $row->{created_month} = "Th" . int($2);
        $row->{created_year}  = $1;
        $row->{formatted_date} = "$row->{created_day}/$2/$1";
    }
    if ($row->{event_start} && $row->{event_start} =~ /^(\d{4})-(\d{2})-(\d{2})\s+(\d{2}):(\d{2})/) {
        $row->{event_day}   = sprintf("%02d", int($3));
        $row->{event_month} = "Th" . int($2);
        $row->{event_year}  = $1;
        $row->{event_time}  = "$4:$5";
        $row->{formatted_event_date} = "$row->{event_day}/$2/$1";
    }
    push @posts, $row;
}

# Danh sách phân trang
my @pages;
for my $i (1 .. $total_pages) {
    push @pages, {
        number => $i,
        active => ($i == $page) ? 1 : 0
    };
}

$template->param(
    posts        => \@posts,
    total_rows   => $total_rows,
    total_pages  => $total_pages,
    current_page => $page,
    pages        => \@pages,
    has_prev     => ($page > 1) ? 1 : 0,
    prev_page    => $page - 1,
    has_next     => ($page < $total_pages) ? 1 : 0,
    next_page    => $page + 1,
    filter_type  => $filter_type,
    search_query => $q,
);

output_html_with_http_headers $cgi, $cookie, $template->output;
