#!/usr/bin/perl

# Copyright 2026 Koha FTU Team
# Dedicated Warehouse (Shelving Location) & Circulation Rules Hub for Koha ILS
# Inherits 100% Koha native data structures (Koha::AuthorisedValues & Koha::CirculationRules)

use Modern::Perl;
use utf8;
use CGI qw( -utf8 );

use C4::Context;
use C4::Auth   qw( get_template_and_user );
use C4::Output qw( output_html_with_http_headers );
use Try::Tiny  qw( try catch );

use Koha::AuthorisedValues;
use Koha::AuthorisedValue;
use Koha::CirculationRules;
use Koha::Libraries;
use Koha::Patron::Categories;
use Koha::ItemTypes;

my $input = CGI->new;
my $op    = $input->param('op') // 'list';

my ( $template, $borrowernumber, $cookie ) = get_template_and_user(
    {
        template_name => "admin/warehouses.tt",
        query         => $input,
        type          => "intranet",
        flagsrequired => { parameters => 1 },
    }
);

my $dbh = C4::Context->dbh;
my @messages;

# =========================================================================
# 1. ACTION: Lưu / Cập nhật Kho lưu trữ (Shelving Location - LOC)
# =========================================================================
if ( $op eq 'cud-save_warehouse' ) {
    my $id               = $input->param('id');
    my $authorised_value = $input->param('authorised_value') // '';
    my $lib              = $input->param('lib') // '';
    my $lib_opac         = $input->param('lib_opac') // '';
    my @branches         = $input->multi_param('branches');

    $authorised_value =~ s/^\s+|\s+$//g;
    $authorised_value = uc($authorised_value);
    $authorised_value =~ s/[^A-Z0-9_]/_/g;
    $lib =~ s/^\s+|\s+$//g;
    $lib_opac =~ s/^\s+|\s+$//g;
    $lib_opac = $lib if $lib_opac eq '';

    if ( $authorised_value eq '' || $lib eq '' ) {
        push @messages, { type => 'danger', text => "Mã kho và Tên kho không được để trống!" };
        $op = $id ? 'edit_warehouse_form' : 'add_warehouse_form';
    } else {
        try {
            if ($id) {
                my $av = Koha::AuthorisedValues->find($id);
                if ($av) {
                    $av->set(
                        {
                            authorised_value => $authorised_value,
                            lib              => $lib,
                            lib_opac         => $lib_opac,
                        }
                    )->store;
                    $av->replace_library_limits(\@branches);
                    push @messages, { type => 'success', text => "Đã cập nhật kho tài liệu '$lib' ($authorised_value) thành công!" };
                }
            } else {
                my $existing = Koha::AuthorisedValues->search(
                    { category => 'LOC', authorised_value => $authorised_value }
                )->count;
                if ($existing) {
                    die "Mã kho '$authorised_value' đã tồn tại trong hệ thống. Vui lòng chọn mã khác!\n";
                }
                my $av = Koha::AuthorisedValue->new(
                    {
                        category         => 'LOC',
                        authorised_value => $authorised_value,
                        lib              => $lib,
                        lib_opac         => $lib_opac,
                    }
                )->store;
                $av->replace_library_limits(\@branches) if @branches;
                push @messages, { type => 'success', text => "Đã tạo mới kho tài liệu '$lib' ($authorised_value) thành công!" };
            }
            $op = 'list';
        } catch {
            my $err = $_;
            push @messages, { type => 'danger', text => "Lỗi lưu kho: $err" };
            $op = $id ? 'edit_warehouse_form' : 'add_warehouse_form';
        };
    }
}

# =========================================================================
# 2. ACTION: Xóa Kho lưu trữ (Shelving Location - LOC)
# =========================================================================
elsif ( $op eq 'cud-delete_warehouse' ) {
    my $id = $input->param('id');
    my $av = Koha::AuthorisedValues->find($id);
    if ($av) {
        my ($items_count) = $dbh->selectrow_array(
            "SELECT COUNT(*) FROM items WHERE location = ?",
            undef, $av->authorised_value
        );
        $items_count = int($items_count || 0);

        if ($items_count > 0) {
            push @messages, {
                type => 'danger',
                text => "Không thể xóa kho '" . $av->lib . "' (" . $av->authorised_value . ") vì hiện có $items_count tài liệu đang lưu trữ tại đây!"
            };
        } else {
            try {
                my $name = $av->lib;
                my $code = $av->authorised_value;
                $av->delete;
                push @messages, { type => 'success', text => "Đã xóa kho tài liệu '$name' ($code) thành công!" };
            } catch {
                push @messages, { type => 'danger', text => "Lỗi xóa kho: $_" };
            };
        }
    }
    $op = 'list';
}

# =========================================================================
# 3. ACTION: Lưu / Cập nhật Quy tắc mượn trả (Koha::CirculationRules)
# =========================================================================
elsif ( $op eq 'cud-save_rule' ) {
    my $branchcode        = $input->param('branchcode');
    my $categorycode      = $input->param('categorycode');
    my $itemtype          = $input->param('itemtype');
    my $maxissueqty       = $input->param('maxissueqty');
    my $issuelength       = $input->param('issuelength');
    my $lengthunit        = $input->param('lengthunit') || 'days';
    my $renewalsallowed   = $input->param('renewalsallowed');
    my $renewalperiod     = $input->param('renewalperiod');
    my $maxonsiteissueqty = $input->param('maxonsiteissueqty');
    my $fine              = $input->param('fine');
    my $reservesallowed   = $input->param('reservesallowed');
    my $note              = $input->param('note');

    $branchcode   = undef if ( !defined $branchcode   || $branchcode eq ''   || $branchcode eq '*' );
    $categorycode = undef if ( !defined $categorycode || $categorycode eq '' || $categorycode eq '*' );
    $itemtype     = undef if ( !defined $itemtype     || $itemtype eq ''     || $itemtype eq '*' );

    try {
        Koha::CirculationRules->set_rules(
            {
                branchcode   => $branchcode,
                categorycode => $categorycode,
                itemtype     => $itemtype,
                rules        => {
                    maxissueqty       => $maxissueqty ne '' ? int($maxissueqty) : undef,
                    issuelength       => $issuelength ne '' ? int($issuelength) : undef,
                    lengthunit        => $lengthunit,
                    renewalsallowed   => $renewalsallowed ne '' ? int($renewalsallowed) : undef,
                    renewalperiod     => $renewalperiod ne '' ? int($renewalperiod) : undef,
                    maxonsiteissueqty => $maxonsiteissueqty ne '' ? int($maxonsiteissueqty) : undef,
                    fine              => $fine ne '' ? $fine : undef,
                    reservesallowed   => $reservesallowed ne '' ? int($reservesallowed) : undef,
                    note              => $note,
                    onshelfholds      => 1,
                    holds_per_record  => 2,
                    auto_renew        => 0,
                }
            }
        );
        push @messages, { type => 'success', text => "Đã lưu quy tắc lưu thông thành công!" };
        $op = 'list';
        $input->param( 'tab', 'rules' );
    } catch {
        push @messages, { type => 'danger', text => "Lỗi lưu quy tắc mượn trả: $_" };
        $op = 'add_rule_form';
    };
}

# =========================================================================
# 4. ACTION: Xóa Quy tắc mượn trả (Koha::CirculationRules)
# =========================================================================
elsif ( $op eq 'cud-delete_rule' ) {
    my $branchcode   = $input->param('branchcode');
    my $categorycode = $input->param('categorycode');
    my $itemtype     = $input->param('itemtype');

    $branchcode   = undef if ( !defined $branchcode   || $branchcode eq ''   || $branchcode eq '*' );
    $categorycode = undef if ( !defined $categorycode || $categorycode eq '' || $categorycode eq '*' );
    $itemtype     = undef if ( !defined $itemtype     || $itemtype eq ''     || $itemtype eq '*' );

    if ( !defined $branchcode && !defined $categorycode && !defined $itemtype ) {
        push @messages, { type => 'danger', text => "Không thể xóa quy tắc mặc định chung toàn hệ thống!" };
    } else {
        try {
            my $rules = Koha::CirculationRules->search(
                {
                    branchcode   => $branchcode,
                    categorycode => $categorycode,
                    itemtype     => $itemtype,
                }
            );
            $rules->delete;
            push @messages, { type => 'success', text => "Đã xóa quy tắc lưu thông thành công!" };
        } catch {
            push @messages, { type => 'danger', text => "Lỗi xóa quy tắc: $_" };
        };
    }
    $op = 'list';
    $input->param( 'tab', 'rules' );
}

# =========================================================================
# 5. VIEW: FORM THÊM / SỬA KHO LƯU TRỮ (add_warehouse_form / edit_warehouse_form)
# =========================================================================
if ( $op eq 'add_warehouse_form' || $op eq 'edit_warehouse_form' ) {
    my $id = $input->param('id');
    my $warehouse;
    my @selected_branches;

    if ($id) {
        $warehouse = Koha::AuthorisedValues->find($id);
        if ($warehouse) {
            @selected_branches = $warehouse->library_limits ? $warehouse->library_limits->as_list : ();
        }
    }

    $template->param(
        op                => $op,
        warehouse         => $warehouse,
        selected_branches => \@selected_branches,
        is_add            => ( $op eq 'add_warehouse_form' ? 1 : 0 ),
        messages          => \@messages,
    );
    output_html_with_http_headers $input, $cookie, $template->output;
    exit;
}

# =========================================================================
# 6. VIEW: FORM THÊM / SỬA QUY TẮC MƯỢN TRẢ (add_rule_form / edit_rule_form)
# =========================================================================
if ( $op eq 'add_rule_form' || $op eq 'edit_rule_form' ) {
    my $branchcode   = $input->param('branchcode');
    my $categorycode = $input->param('categorycode');
    my $itemtype     = $input->param('itemtype');

    $branchcode   = undef if ( defined $branchcode   && ( $branchcode eq ''   || $branchcode eq '*' ) );
    $categorycode = undef if ( defined $categorycode && ( $categorycode eq '' || $categorycode eq '*' ) );
    $itemtype     = undef if ( defined $itemtype     && ( $itemtype eq ''     || $itemtype eq '*' ) );

    my $rule;
    if ( $op eq 'edit_rule_form' ) {
        my $sth_r = $dbh->prepare("
            SELECT 
                cr.branchcode,
                cr.categorycode,
                cr.itemtype,
                MAX(CASE WHEN cr.rule_name = 'maxissueqty' THEN cr.rule_value END) AS maxissueqty,
                MAX(CASE WHEN cr.rule_name = 'issuelength' THEN cr.rule_value END) AS issuelength,
                MAX(CASE WHEN cr.rule_name = 'lengthunit' THEN cr.rule_value END) AS lengthunit,
                MAX(CASE WHEN cr.rule_name = 'renewalsallowed' THEN cr.rule_value END) AS renewalsallowed,
                MAX(CASE WHEN cr.rule_name = 'renewalperiod' THEN cr.rule_value END) AS renewalperiod,
                MAX(CASE WHEN cr.rule_name = 'maxonsiteissueqty' THEN cr.rule_value END) AS maxonsiteissueqty,
                MAX(CASE WHEN cr.rule_name = 'fine' THEN cr.rule_value END) AS fine,
                MAX(CASE WHEN cr.rule_name = 'reservesallowed' THEN cr.rule_value END) AS reservesallowed,
                MAX(CASE WHEN cr.rule_name = 'note' THEN cr.rule_value END) AS note
            FROM circulation_rules cr
            WHERE cr.branchcode <=> ? AND cr.categorycode <=> ? AND cr.itemtype <=> ?
            GROUP BY cr.branchcode, cr.categorycode, cr.itemtype
            LIMIT 1
        ");
        $sth_r->execute( $branchcode, $categorycode, $itemtype );
        $rule = $sth_r->fetchrow_hashref;
    }

    $template->param(
        op                => $op,
        rule              => $rule,
        categorycode      => ( defined $categorycode ? $categorycode : '*' ),
        itemtype          => ( defined $itemtype ? $itemtype : '*' ),
        branchcode        => ( defined $branchcode ? $branchcode : '*' ),
        patron_categories => Koha::Patron::Categories->search( {}, { order_by => ['description'] } ),
        itemtypes         => Koha::ItemTypes->search_with_localization,
        libraries         => Koha::Libraries->search( {}, { order_by => ['branchname'] } ),
        messages          => \@messages,
    );
    output_html_with_http_headers $input, $cookie, $template->output;
    exit;
}

# =========================================================================
# 7. DEFAULT VIEW: BẢNG DANH MỤC KHO & QUY TẮC MƯỢN TRẢ (LIST)
# =========================================================================
my $active_tab = $input->param('tab') // 'warehouses';
my $branch     = $input->param('branch') // '*';

# Danh sách Kho lưu trữ (Shelving Locations - category 'LOC')
my $warehouses_rs = Koha::AuthorisedValues->search(
    { category => 'LOC' },
    { order_by => ['lib'] }
);

my @warehouses;
my $total_items_in_warehouses = 0;

while ( my $w = $warehouses_rs->next ) {
    my ($cnt) = $dbh->selectrow_array(
        "SELECT COUNT(*) FROM items WHERE location = ?",
        undef, $w->authorised_value
    );
    $cnt = int($cnt || 0);
    $total_items_in_warehouses += $cnt;

    my @limit_branches = $w->library_limits ? $w->library_limits->as_list : ();
    my $branches_display = @limit_branches
      ? join( ', ', map { $_->branchname } @limit_branches )
      : 'Tất cả thư viện';

    push @warehouses, {
        id               => $w->id,
        authorised_value => $w->authorised_value,
        lib              => $w->lib,
        lib_opac         => $w->lib_opac,
        branches_display => $branches_display,
        items_count      => $cnt,
    };
}

my $where = "";
my @bind_params;
if ( $branch ne '*' ) {
    $where = "WHERE (cr.branchcode = ? OR cr.branchcode IS NULL)";
    push @bind_params, $branch;
}

my $sth_rules = $dbh->prepare("
    SELECT 
        cr.branchcode,
        cr.categorycode,
        cr.itemtype,
        MAX(b.branchname) AS branchname,
        MAX(c.description) AS category_desc,
        MAX(it.description) AS itemtype_desc,
        MAX(CASE WHEN cr.rule_name = 'maxissueqty' THEN cr.rule_value END) AS maxissueqty,
        MAX(CASE WHEN cr.rule_name = 'issuelength' THEN cr.rule_value END) AS issuelength,
        MAX(CASE WHEN cr.rule_name = 'lengthunit' THEN cr.rule_value END) AS lengthunit,
        MAX(CASE WHEN cr.rule_name = 'renewalsallowed' THEN cr.rule_value END) AS renewalsallowed,
        MAX(CASE WHEN cr.rule_name = 'renewalperiod' THEN cr.rule_value END) AS renewalperiod,
        MAX(CASE WHEN cr.rule_name = 'maxonsiteissueqty' THEN cr.rule_value END) AS maxonsiteissueqty,
        MAX(CASE WHEN cr.rule_name = 'fine' THEN cr.rule_value END) AS fine,
        MAX(CASE WHEN cr.rule_name = 'reservesallowed' THEN cr.rule_value END) AS reservesallowed,
        MAX(CASE WHEN cr.rule_name = 'note' THEN cr.rule_value END) AS note
    FROM circulation_rules cr
    LEFT JOIN branches b ON cr.branchcode = b.branchcode
    LEFT JOIN categories c ON cr.categorycode = c.categorycode
    LEFT JOIN itemtypes it ON cr.itemtype = it.itemtype
    $where
    GROUP BY cr.branchcode, cr.categorycode, cr.itemtype
    ORDER BY (cr.categorycode IS NOT NULL) DESC, (cr.itemtype IS NOT NULL) DESC, category_desc ASC
");
$sth_rules->execute(@bind_params);
my @rules;
while ( my $r = $sth_rules->fetchrow_hashref ) {
    $r->{lengthunit} ||= 'days';
    push @rules, $r;
}

$template->param(
    op                         => 'list',
    active_tab                 => $active_tab,
    current_branch             => $branch,
    warehouses                 => \@warehouses,
    circulation_rules          => \@rules,
    total_warehouses           => scalar(@warehouses),
    total_rules                => scalar(@rules),
    total_items_in_warehouses  => $total_items_in_warehouses,
    messages                   => \@messages,
);

output_html_with_http_headers $input, $cookie, $template->output;
