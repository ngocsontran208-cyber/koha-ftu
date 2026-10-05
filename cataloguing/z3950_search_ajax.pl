#!/usr/bin/perl

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );
use JSON qw( to_json from_json );
use Encode qw( encode_utf8 decode_utf8 );
use C4::Auth qw( check_cookie_auth );
use C4::Context;
use C4::Breeding qw( Z3950Search );
use C4::ImportBatch qw( GetZ3950BatchId AddBiblioToBatch );
use C4::Biblio qw( TransformMarcToKoha );
use Koha::Z3950Servers;
use LWP::UserAgent;
use MARC::Record;
use MARC::Field;

my $input = CGI->new;

binmode STDOUT, ':encoding(UTF-8)';
print $input->header(
    -type    => 'application/json',
    -charset => 'UTF-8'
);

# Check the user's permissions
my ($auth_status) = C4::Auth::check_cookie_auth(
    $input->cookie('CGISESSID'),
    {
        editcatalogue => 'edit_catalogue'
    }
);
if ( $auth_status ne "ok" ) {
    print to_json( { ok => 0, error => 'Unauthorized', message => 'Phiên làm việc hết hạn hoặc chưa đăng nhập' } );
    exit 0;
}

my $raw_isbn      = $input->param('isbn')          // '';
my $title         = $input->param('title')         // '';
my $author        = $input->param('author')        // '';
my $frameworkcode = $input->param('frameworkcode') // '';
my $biblionumber  = $input->param('biblionumber')  // 0;

my $clean_isbn = $raw_isbn;
$clean_isbn =~ s/^[iI][sS][bB][nN][: \t]*//;
$clean_isbn =~ s/\s*\([^)]*\)//g;
$clean_isbn =~ s/^\s+|\s+$//g;

$title  =~ s/^\s+|\s+$//g;
$author =~ s/^\s+|\s+$//g;

unless ( $clean_isbn || $title || $author ) {
    print to_json( {
        ok      => 0,
        count   => 0,
        results => [],
        message => 'Vui lòng nhập ISBN, Nhan đề hoặc Tác giả để tra cứu'
    } );
    exit 0;
}

# 1. Search Thư viện Quốc gia Việt Nam (NLV) directly via their live OPAC system
my @nlv_results = eval { search_nlv_opac($raw_isbn, $clean_isbn, $title, $author) };
warn "NLV OPAC Search Error: $@" if $@;

# 2. Determine Z39.50 servers to search
my @id = $input->multi_param('id');
if ( !@id ) {
    my $server_ids_str = $input->param('server_ids') // '';
    @id = grep { /^\d+$/ } split( /,/, $server_ids_str );
}
if ( !@id ) {
    my $default_servers = Koha::Z3950Servers->search(
        {
            recordtype => 'biblio',
            servertype => [ 'zed', 'sru' ],
            checked    => 1,
        },
        {
            order_by => [ 'rank', 'servername' ],
        }
    );
    @id = map { $_->id } $default_servers->as_list;
}

# Mock template object to capture Z3950Search results
{
    package MockTemplate;
    sub new { bless {}, shift }
    sub param {
        my $self = shift;
        if ( @_ == 1 ) { return $self->{ $_[0] }; }
        my %args = @_;
        while ( my ( $k, $v ) = each %args ) {
            $self->{$k} = $v;
        }
        return $self;
    }
}

my $mock_tmpl = MockTemplate->new();

# If we already got good results from NLV for a Vietnamese ISBN (978-604...), skip waiting for foreign Z39.50
my $is_vn_isbn = ( $clean_isbn =~ /^978[-]?604/ );
if ( @id && !( @nlv_results && $is_vn_isbn ) ) {
    my $pars = {
        biblionumber => $biblionumber,
        page         => 1,
        id           => \@id,
        isbn         => $clean_isbn,
        title        => $title,
        author       => $author,
    };

    eval {
        Z3950Search( $pars, $mock_tmpl );
    };
}

my $breeding_loop = $mock_tmpl->param('breeding_loop') // [];
my $errconn       = $mock_tmpl->param('errconn')       // [];

my @results = @nlv_results;
my %seen_title_isbn;
for my $r (@results) {
    my $key = lc( ($r->{title} // '') . '|' . ($r->{editionstatement} // '') . '|' . ($r->{date} // '') );
    $seen_title_isbn{$key} = 1;
}

foreach my $row ( @$breeding_loop ) {
    next unless $row->{breedingid} && $row->{breedingid} > 0;
    my $key = lc( ($row->{title} // '') . '|' . ($row->{editionstatement} // '') . '|' . ($row->{date} // '') );
    next if $seen_title_isbn{$key}++;
    push @results, {
        breedingid       => $row->{breedingid},
        title            => $row->{title} // '',
        author           => $row->{author} // '',
        isbn             => $row->{isbn} // '',
        date             => $row->{date} // '',
        editionstatement => $row->{editionstatement} // '',
        server           => $row->{server} // '',
    };
}

# Sort results: newest year and highest edition first
@results = sort_records(\@results, $title);

my @errors;
unless ( @results ) {
    foreach my $err ( @$errconn ) {
        my $srv = $err->{server} // 'Máy chủ Z39.50';
        push @errors, {
            server  => $srv,
            errcode => $err->{errcode},
            message => "Mất kết nối tới máy chủ $srv"
        };
    }
}

print to_json( {
    ok            => 1,
    count         => scalar( @results ),
    results       => \@results,
    errors        => \@errors,
    frameworkcode => $frameworkcode,
    biblionumber  => $biblionumber,
} );

exit 0;

# -------------------------------------------------------------
# Function: sort_records
# Sorts records intelligently by title match, year desc, edition desc
# -------------------------------------------------------------
sub sort_records {
    my ($recs, $query_title) = @_;
    return () unless $recs && @$recs;

    my $sub_extract_ed = sub {
        my ($ed) = @_;
        return 0 unless $ed;
        return int($1) if $ed =~ /(\d+)/;
        return 0;
    };

    my @sorted = sort {
        if ($query_title) {
            my $match_a = (index(lc($a->{title} // ''), lc($query_title)) != -1) ? 1 : 0;
            my $match_b = (index(lc($b->{title} // ''), lc($query_title)) != -1) ? 1 : 0;
            return $match_b <=> $match_a if $match_a != $match_b;
        }

        # Year descending
        my ($ya) = ($a->{date} // '') =~ /(\d{4})/;
        my ($yb) = ($b->{date} // '') =~ /(\d{4})/;
        $ya //= 0;
        $yb //= 0;
        return $yb <=> $ya if $ya != $yb;

        # Edition number descending
        my $eda = $sub_extract_ed->($a->{editionstatement});
        my $edb = $sub_extract_ed->($b->{editionstatement});
        return $edb <=> $eda if $eda != $edb;

        return ($a->{title} // '') cmp ($b->{title} // '');
    } @$recs;

    return @sorted;
}

# -------------------------------------------------------------
# Function: get_isbn_variants
# Generates all possible permutations of Vietnamese ISBNs
# -------------------------------------------------------------
sub get_isbn_variants {
    my ($isbn) = @_;
    my %seen;
    my @variants;

    $isbn =~ s/^[iI][sS][bB][nN][: \t]*//;
    $isbn =~ s/\s*\([^)]*\)//g;
    $isbn =~ s/^\s+|\s+$//g;
    return () unless $isbn;

    push @variants, $isbn unless $seen{$isbn}++;

    my $digits = $isbn;
    $digits =~ s/[^0-9Xx]//g;
    push @variants, $digits unless $seen{$digits}++;

    if (length($digits) == 13) {
        my $p = substr($digits, 0, 3);
        my $g = substr($digits, 3, 3);
        my $rest = substr($digits, 6, 6);
        my $chk = substr($digits, 12, 1);

        # 3-3 split: e.g. 978-604-486-220-0, 978-604-962-708-8
        my $v1 = "$p-$g-" . substr($rest, 0, 3) . "-" . substr($rest, 3, 3) . "-$chk";
        push @variants, $v1 unless $seen{$v1}++;

        # 2-4 split: e.g. 978-604-96-2708-8
        my $v2 = "$p-$g-" . substr($rest, 0, 2) . "-" . substr($rest, 2, 4) . "-$chk";
        push @variants, $v2 unless $seen{$v2}++;

        # 4-2 split: e.g. 978-604-9627-08-8
        my $v3 = "$p-$g-" . substr($rest, 0, 4) . "-" . substr($rest, 4, 2) . "-$chk";
        push @variants, $v3 unless $seen{$v3}++;
    }

    return @variants;
}

# -------------------------------------------------------------
# Function: search_nlv_opac
# Connects to opac.nlv.gov.vn, queries books, parses full MARC21
# -------------------------------------------------------------
sub search_nlv_opac {
    my ($raw_isbn, $clean_isbn, $title, $author) = @_;

    my %term_seen;
    my @terms;

    if ($raw_isbn || $clean_isbn) {
        my @vars = get_isbn_variants($raw_isbn || $clean_isbn);
        for my $v (@vars) {
            push @terms, $v unless $term_seen{$v}++;
        }
    }
    if ($title && $title =~ /\S/) {
        push @terms, $title unless $term_seen{$title}++;
    }
    if ($author && $author =~ /\S/ && !@terms) {
        push @terms, $author unless $term_seen{$author}++;
    }

    return () unless @terms;

    my $ua = LWP::UserAgent->new(
        cookie_jar => {},
        ssl_opts   => { verify_hostname => 0 },
        timeout    => 8,
        agent      => "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36",
    );

    my $res = eval { $ua->get("https://opac.nlv.gov.vn/tim-kiem") };
    return () unless $res && $res->is_success;

    my ($token) = $res->decoded_content =~ /id=requestVerificationToken\s+value=([^\s>]+)/;
    return () unless $token;

    my %seen_links;
    my @detail_links;

    for my $term (@terms) {
        my $payload = {
            type     => "quick",
            page     => 1,
            pageSize => 8,
            request  => {
                searchBy => [ ["option", "qs"], ["keyword", $term] ],
                sortBy   => [ ["year_pub", "desc"] ],
                filterBy => [],
            }
        };

        my $post_res = eval {
            $ua->post(
                "https://opac.nlv.gov.vn/Search",
                "Content-Type"             => "application/json",
                "RequestVerificationToken" => $token,
                "X-Requested-With"         => "XMLHttpRequest",
                Content                    => encode_utf8(to_json($payload)),
            );
        };
        next unless $post_res && $post_res->is_success;

        my $search_html = $post_res->decoded_content;
        my @links = $search_html =~ /href=[\x27\x22](\/chi-tiet-tai-lieu\/[^\x27\x22]+)[\x27\x22]/g;
        for my $l (@links) {
            $l =~ s/\?.*$//; # Remove query parameters like ?focusRegCir=true to avoid duplicate links
            push @detail_links, $l unless $seen_links{$l}++;
        }
        last if @detail_links >= 1;
    }

    return () unless @detail_links;

    my $batch_id = GetZ3950BatchId("Thư viện Quốc gia Việt Nam (NLV)");
    my @records;
    my %seen_records;
    my $seq = 0;

    for my $link (@detail_links[0 .. ($#detail_links > 5 ? 5 : $#detail_links)]) {
        my $d_res = eval { $ua->get("https://opac.nlv.gov.vn" . $link) };
        next unless $d_res && $d_res->is_success;

        my ($table_html) = $d_res->decoded_content =~ /<table[^>]*class=[\x27\x22][^\x27\x22]*marc21[^\x27\x22]*[\x27\x22][^>]*>(.*?)<\/table>/s;
        next unless $table_html;

        my $record = MARC::Record->new();
        $record->leader("00000nam a2200000 a 4500");
        $record->encoding("UTF-8");

        my @rows = split /<tr>/i, $table_html;
        shift @rows;

        my ($current_tag, $current_ind1, $current_ind2, @current_subfields);
        my $flush = sub {
            return unless defined $current_tag && length($current_tag) == 3 && @current_subfields;
            eval {
                my $field = MARC::Field->new($current_tag, $current_ind1, $current_ind2, @current_subfields);
                $record->append_fields($field) if $field;
            };
            @current_subfields = ();
        };

        for my $r (@rows) {
            my @cells = split /<td[^>]*>/i, $r;
            shift @cells;
            @cells = map { my $c = $_; $c =~ s/<\/?[^>]+>//g; $c =~ s/^\s+|\s+$//g; $c } @cells;
            next unless @cells;
            my ($tag, $ind1, $ind2, $subfield, $value) = @cells;
            $tag //= ""; $ind1 //= "#"; $ind2 //= "#"; $subfield //= ""; $value //= "";
            $ind1 = ($ind1 eq "#" || $ind1 eq "") ? " " : substr($ind1, 0, 1);
            $ind2 = ($ind2 eq "#" || $ind2 eq "") ? " " : substr($ind2, 0, 1);

            if ($tag =~ /^\d{3}$/) {
                $flush->();
                $current_tag = $tag;
                $current_ind1 = $ind1;
                $current_ind2 = $ind2;
                push @current_subfields, ($subfield, $value) if $subfield ne "" && $value ne "";
            } elsif ($current_tag && $subfield ne "" && $value ne "") {
                push @current_subfields, ($subfield, $value);
            }
        }
        $flush->();

        # Ensure author 100 is set if 700 exists
        if (!$record->field("100") && $record->field("700")) {
            my $f700 = $record->field("700");
            my @sf;
            for my $sc ("a", "b", "c", "d", "e") {
                my $val = $f700->subfield($sc);
                push @sf, ($sc, $val) if defined $val;
            }
            $record->insert_fields_ordered(MARC::Field->new("100", $f700->indicator(1), $f700->indicator(2), @sf)) if @sf;
        }

        my @kohafields = ( "biblio.title", "biblio.author", "biblioitems.isbn", "biblioitems.editionstatement", "biblio.copyrightdate", "biblioitems.publicationyear" );
        my $koha_row = TransformMarcToKoha({ record => $record, kohafields => \@kohafields, limit_table => "no_items" });

        my $rec_title   = $koha_row->{title} || $record->title || "";
        my $rec_author  = $koha_row->{author} || $record->author || "";
        my $rec_isbn    = $koha_row->{isbn} || ($record->subfield("020", "a") // "");
        my $rec_date    = $koha_row->{copyrightdate} || $koha_row->{publicationyear} || "";
        my $rec_edition = $koha_row->{editionstatement} || "";

        # Deduplicate identical editions
        my $rec_fingerprint = lc("$rec_title|$rec_author|$rec_edition|$rec_date");
        next if $seen_records{$rec_fingerprint}++;

        my $breedingid = AddBiblioToBatch($batch_id, ++$seq, $record, "UTF-8", 0);
        next unless $breedingid;

        push @records, {
            breedingid       => $breedingid,
            title            => $rec_title,
            author           => $rec_author,
            isbn             => $rec_isbn,
            date             => $rec_date,
            editionstatement => $rec_edition,
            server           => "Thư viện Quốc gia Việt Nam (NLV)",
        };
    }

    # If user provided a specific title filter, prioritize matching titles
    if ($title && $title =~ /\S/) {
        my @matching = grep { index(lc($_->{title}), lc($title)) != -1 } @records;
        @records = @matching if @matching;
    }

    return @records;
}
