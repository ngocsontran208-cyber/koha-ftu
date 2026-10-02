<!-- acquisitions-toolbar.inc -->
[% INCLUDE 'modals/delete_vendor.inc' %]
<div id="toolbar" class="btn-toolbar">
    [% IF ( booksellerid ) %]
        <div class="btn-group">
            <a class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" href="#"><i class="fa fa-plus"></i> Tạo mới</a>
            <ul class="dropdown-menu">
                [% IF CAN_user_acquisition_order_manage && active %]
                    <li><a class="dropdown-item" href="/cgi-bin/koha/acqui/basketheader.pl?booksellerid=[% booksellerid | uri %]&amp;op=add_form"><i class="fa fa-basket-shopping text-primary"></i> Giỏ đơn hàng</a></li>
                [% END %]
                [% IF CAN_user_acquisition_contracts_manage && active %]
                    <li><a class="dropdown-item" href="/cgi-bin/koha/admin/aqcontract.pl?op=add_form&amp;booksellerid=[% booksellerid | uri %]"><i class="fa fa-file-contract text-info"></i> Hợp đồng</a></li>
                [% END %]
                [% IF ( CAN_user_acquisition_vendors_manage ) %]
                    <li><a class="dropdown-item" href="/cgi-bin/koha/acquisition/vendors/add"><i class="fa fa-building text-success"></i> Nhà cung cấp</a></li>
                [% END %]
            </ul>
        </div>
        [% IF ( CAN_user_acquisition_vendors_manage ) %]
            <div class="btn-group">
                <a class="btn btn-default" id="editsupplier" href="/cgi-bin/koha/acquisition/vendors/[% booksellerid | html %]"><i class="fa-solid fa-pencil" aria-hidden="true"></i> Chỉnh sửa nhà cung cấp</a>
            </div>
            [% UNLESS ( basketcount OR subscriptioncount ) %]
                <div class="btn-group">
                    <button type="button" data-bs-toggle="modal" data-bs-target="#deleteVendorModal" data-booksellerid="[% booksellerid | html %]" class="btn btn-default"><i class="fa fa-trash-can text-danger"></i> Xóa nhà cung cấp</button>
                </div>
            [% END %]
        [% END %]
        [% IF CAN_user_acquisition_order_receive && basketcount && active %]
            <div class="btn-group"
                ><a class="btn btn-default" id="receive" href="/cgi-bin/koha/acqui/parcels.pl?booksellerid=[% booksellerid | html %]"><i class="fa fa-inbox text-success"></i> Nhận lô hàng</a></div
            >
        [% END %]
    [% ELSIF ( CAN_user_acquisition_vendors_manage ) %]
        <div class="btn-group"
            ><a class="btn btn-primary ftu-btn-primary" href="/cgi-bin/koha/acquisition/vendors/add"><i class="fa fa-plus"></i> Thêm nhà cung cấp mới</a></div
        >
    [% END %]
</div>
<!-- / acquisitions-toolbar.inc -->
