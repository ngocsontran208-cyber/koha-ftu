<!-- circ-nav.inc – Việt hoá -->
[% USE Koha %]
[% USE Branches %]
<div class="circ-nav-menu sidebar_menu">
    <h5>Lưu thông</h5>
    <ul>
        <li>
            <a href="/cgi-bin/koha/circ/circulation.pl">Mượn sách</a>
        </li>
        <li>
            <a href="/cgi-bin/koha/circ/returns.pl">Trả sách</a>
        </li>
        <li>
            <a href="/cgi-bin/koha/circ/renew.pl">Gia hạn</a>
        </li>
        [% IF ( CAN_user_superlibrarian || CAN_user_loggedinlibrary ) %]
            <li>
                [% IF Koha.Preference('UseCirculationDesks') %]
                    <a href="/cgi-bin/koha/circ/set-library.pl">Đặt thư viện & quầy</a>
                [% ELSE %]
                    <a href="/cgi-bin/koha/circ/set-library.pl">Đặt thư viện</a>
                [% END %]
            </li>
        [% ELSIF Koha.Preference('UseCirculationDesks') %]
            <li>
                <a href="/cgi-bin/koha/circ/set-library.pl">Đặt quầy</a>
            </li>
        [% END %]
        [% IF ( fast_cataloging && CAN_user_editcatalogue_fast_cataloging ) %]
            <li>
                <a href="/cgi-bin/koha/cataloguing/addbiblio.pl?frameworkcode=FA"> Biên mục nhanh</a>
            </li>
        [% END %]
        [% IF ( Koha.Preference('AllowCheckoutNotes') && CAN_user_circulate_manage_checkout_notes ) %]
            <li>
                <a href="/cgi-bin/koha/circ/checkout-notes.pl">Ghi chú mượn</a>
            </li>
        [% END %]
        [% IF Koha.Preference('OnSiteCheckouts') %]
            <li>
                <a href="/cgi-bin/koha/circ/on-site_checkouts.pl">Mượn tại chỗ đang chờ</a>
            </li>
        [% END %]
    </ul>

    <h5>Đặt giữ</h5>
    <ul>
        <li>
            [% IF Koha.Preference('UseHoldsQueueFilterOptions') %]
                <a href="/cgi-bin/koha/circ/view_holdsqueue.pl?branchlimit=[% Branches.GetLoggedInBranchcode | uri %]">Hàng đợi đặt giữ</a>
            [% ELSE %]
                <a href="/cgi-bin/koha/circ/view_holdsqueue.pl?branchlimit=[% Branches.GetLoggedInBranchcode | uri %]&run_report=1">Hàng đợi đặt giữ</a>
            [% END %]
        </li>
        <li>
            <a href="/cgi-bin/koha/circ/pendingreserves.pl">Đặt giữ cần lấy</a>
        </li>
        <li>
            <a href="/cgi-bin/koha/circ/waitingreserves.pl">Đặt giữ chờ nhận</a>
        </li>
        [% IF ( Koha.Preference('CurbsidePickup') && CAN_user_circulate_manage_curbside_pickups ) %]
            <li>
                <a href="/cgi-bin/koha/circ/curbside_pickups.pl">Nhận tại quầy</a>
            </li>
        [% END %]
        <li>
            <a href="/cgi-bin/koha/circ/reserveratios.pl">Tỷ lệ đặt giữ</a>
        </li>
        [% IF Koha.Preference('EnableBooking') %]
            <li>
                <a href="/cgi-bin/koha/circ/bookings.pl">Đặt chỗ cần lấy</a>
            </li>
        [% END %]
    </ul>

    [% IF Koha.Preference('UseRecalls') and CAN_user_recalls %]
        <h5>Thu hồi</h5>
        <ul>
            <li>
                <a href="/cgi-bin/koha/recalls/recalls_queue.pl" title="Tất cả thu hồi đang hoạt động">Hàng đợi thu hồi</a>
            </li>
            <li>
                <a href="/cgi-bin/koha/recalls/recalls_to_pull.pl" title="Thu hồi có thể hoàn thành nhưng chưa đặt chờ">Thu hồi cần lấy</a>
            </li>
            <li>
                <a href="/cgi-bin/koha/recalls/recalls_overdue.pl" title="Tài liệu thu hồi quá hạn">Thu hồi quá hạn</a>
            </li>
            <li>
                <a href="/cgi-bin/koha/recalls/recalls_waiting.pl" title="Tài liệu thu hồi chờ nhận">Thu hồi chờ nhận</a>
            </li>
            <li>
                <a href="/cgi-bin/koha/recalls/recalls_old_queue.pl" title="Thu hồi không hoạt động">Thu hồi cũ</a>
            </li>
        </ul>
    [% END %]

    [% IF Koha.Preference('ArticleRequests') %]
        <h5>Yêu cầu bạn đọc</h5>
        <ul>
            <li>
                <a href="/cgi-bin/koha/circ/article-requests.pl">Yêu cầu bài báo</a>
            </li>
        </ul>
    [% END %]

    <h5>Chuyển kho</h5>
    <ul>
        [% IF !Koha.Preference('IndependentBranchesTransfers') || CAN_user_superlibrarian %]
            <li>
                <a href="/cgi-bin/koha/circ/branchtransfers.pl">Chuyển kho</a>
            </li>
        [% END %]
        [% IF Koha.Preference('StockRotation') %]
            <li>
                <a href="/cgi-bin/koha/circ/transfers_to_send.pl">Chuyển đi</a>
            </li>
        [% END %]
        <li>
            <a href="/cgi-bin/koha/circ/transferstoreceive.pl">Nhận về</a>
        </li>
    </ul>

    [% IF ( CAN_user_circulate_overdues_report ) %]
        <h5>Quá hạn</h5>
        <ul>
            <li>
                <a href="/cgi-bin/koha/circ/overdue.pl" title="Cảnh báo: Báo cáo này tốn nhiều tài nguyên khi có nhiều tài liệu quá hạn.">Quá hạn</a>
            </li>
            <li>
                <a href="/cgi-bin/koha/circ/branchoverdues.pl" title="Giới hạn trong thư viện của bạn.">Quá hạn có phạt</a>
            </li>
        </ul>
    [% END %]
</div>
<!-- /.sidebar_menu -->
