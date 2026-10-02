[% USE Koha %]
[% USE Asset %]
[% USE raw %]
[% USE To %]

<div id="acquisitions-menu" class="sidebar_menu ftu-sidebar-menu">
    <h5><i class="fa fa-cart-shopping text-danger"></i> Bổ sung tài liệu</h5>
    <ul>
        <li>
            <a href="/cgi-bin/koha/acqui/acqui-home.pl"><i class="fa fa-house fa-fw"></i> Trang chủ bổ sung</a>
        </li>
        <li>
            <a href="/cgi-bin/koha/acqui/histsearch.pl"><i class="fa fa-magnifying-glass fa-fw"></i> Tìm kiếm nâng cao</a>
        </li>
        [% IF ( CAN_user_acquisition_order_receive ) %]
            <li>
                <a href="/cgi-bin/koha/acqui/lateorders.pl"><i class="fa fa-clock-rotate-left fa-fw"></i> Đơn hàng trễ hạn</a>
            </li>
        [% END %]
        [% IF ( CAN_user_suggestions_suggestions_create || CAN_user_suggestions_suggestions_manage || CAN_user_suggestions_suggestions_delete ) %]
            <li>
                <a href="/cgi-bin/koha/suggestion/suggestion.pl"><i class="fa fa-lightbulb fa-fw"></i> Đề xuất mua sắm</a>
            </li>
        [% END %]
        <li>
            <a href="/cgi-bin/koha/acqui/invoices.pl"><i class="fa fa-file-invoice-dollar fa-fw"></i> Quản lý hóa đơn</a>
        </li>
        [% IF Koha.Preference('EDIFACT') && CAN_user_acquisition_edi_manage %]
            <li>
                <a href="/cgi-bin/koha/acqui/edifactmsgs.pl"><i class="fa fa-network-wired fa-fw"></i> Thông điệp EDIFACT</a>
            </li>
        [% END %]
    </ul>

    [% IF CAN_user_reports || CAN_user_circulate_circulate_remaining_permissions %]
        <h5><i class="fa fa-chart-column text-danger"></i> Báo cáo &amp; Thống kê</h5>
        <ul>
            [% IF CAN_user_reports %]
                <li>
                    <a href="/cgi-bin/koha/reports/acquisitions_stats.pl"><i class="fa fa-chart-line fa-fw"></i> Báo cáo thống kê bổ sung</a>
                </li>
                <li>
                    <a href="/cgi-bin/koha/reports/orders_by_fund.pl"><i class="fa fa-chart-pie fa-fw"></i> Đơn hàng theo nguồn quỹ</a>
                </li>
            [% END %]
            [% IF CAN_user_circulate_circulate_remaining_permissions %]
                <li>
                    <a href="/cgi-bin/koha/circ/reserveratios.pl"><i class="fa fa-scale-balanced fa-fw"></i> Tỷ lệ đặt trước</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF CAN_user_acquisition_period_manage || CAN_user_acquisition_budget_manage || CAN_user_acquisition_currencies_manage || CAN_user_parameters_manage_additional_fields %]
        <h5><i class="fa fa-sliders text-danger"></i> Quản trị ngân sách</h5>
        <ul>
            [% IF CAN_user_acquisition_period_manage %]
                <li>
                    <a href="/cgi-bin/koha/admin/aqbudgetperiods.pl"><i class="fa fa-calendar-days fa-fw"></i> Niên khóa ngân sách</a>
                </li>
            [% END %]
            [% IF CAN_user_acquisition_budget_manage %]
                <li>
                    <a href="/cgi-bin/koha/admin/aqbudgets.pl"><i class="fa fa-piggy-bank fa-fw"></i> Danh mục quỹ</a>
                </li>
            [% END %]
            [% IF CAN_user_acquisition_currencies_manage %]
                <li>
                    <a href="/cgi-bin/koha/admin/currency.pl"><i class="fa fa-coins fa-fw"></i> Đơn vị tiền tệ</a>
                </li>
            [% END %]
            [% IF CAN_user_parameters_manage_additional_fields %]
                <li>
                    <a href="/cgi-bin/koha/admin/additional-fields.pl?tablename=aqinvoices"><i class="fa fa-table-list fa-fw"></i> Quản lý trường hóa đơn</a>
                </li>
                <li>
                    <a href="/cgi-bin/koha/admin/additional-fields.pl?tablename=aqbasket"><i class="fa fa-basket-shopping fa-fw"></i> Quản lý trường giỏ đơn hàng</a>
                </li>
                <li>
                    <a href="/cgi-bin/koha/admin/additional-fields.pl?tablename=aqorders"><i class="fa fa-list-check fa-fw"></i> Quản lý trường đặt mua</a>
                </li>
            [% END %]
        </ul>
    [% END %]
</div>
