[% USE Koha %]
<div id="cat-menu" class="sidebar_menu">
    [% IF ( CAN_user_tools_stage_marc_import || CAN_user_tools_manage_staged_marc ) %]
        <h5><i class="fa fa-file-import"></i> Nhập dữ liệu</h5>
        <ul>
            [% IF ( CAN_user_tools_stage_marc_import ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/stage-marc-import.pl">Tải lên biểu ghi nhập khẩu</a>
                </li>
            [% END %]
            [% IF ( CAN_user_tools_manage_staged_marc ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/manage-marc-import.pl">Quản lý lô biểu ghi đã tải lên</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_tools_export_catalog ) %]
        <h5><i class="fa fa-file-export"></i> Xuất dữ liệu</h5>
        <ul>
            [% IF ( CAN_user_tools_export_catalog ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/export.pl">Xuất dữ liệu biên mục</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_tools_inventory || ( ( Koha.Preference('OpacCatalogConcerns') || Koha.Preference('CatalogConcerns') ) && CAN_user_editcatalogue_edit_catalogue ) ) %]
        <h5><i class="fa fa-clipboard-check"></i> Báo cáo &amp; Kiểm kê</h5>
        <ul>
            [% IF ( CAN_user_tools_inventory ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/inventory.pl">Kiểm kê kho tài liệu</a>
                </li>
            [% END %]
            [% IF ( Koha.Preference('OpacCatalogConcerns') || Koha.Preference('CatalogConcerns') ) && CAN_user_editcatalogue_edit_catalogue %]
                <li>
                    <a href="/cgi-bin/koha/cataloguing/concerns.pl">Ý kiến bạn đọc về biên mục</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_tools_items_batchmod || CAN_user_tools_items_batchdel || CAN_user_tools_records_batchmod || CAN_user_tools_records_batchdel || CAN_user_editcatalogue_records_restore || CAN_user_tools_marc_modification_templates ) %]
        <h5><i class="fa fa-layer-group"></i> Xử lý hàng loạt</h5>
        <ul>
            [% IF ( CAN_user_tools_items_batchmod ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/batchMod.pl">Chỉnh sửa bản tài liệu hàng loạt</a>
                </li>
            [% END %]
            [% IF ( CAN_user_tools_items_batchdel ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/batchMod.pl?del=1">Xóa bản tài liệu hàng loạt</a>
                </li>
            [% END %]
            [% IF CAN_user_tools_records_batchmod %]
                <li>
                    <a href="/cgi-bin/koha/tools/batch_record_modification.pl">Chỉnh sửa biểu ghi hàng loạt</a>
                </li>
            [% END %]
            [% IF CAN_user_tools_records_batchdel %]
                <li>
                    <a href="/cgi-bin/koha/tools/batch_delete_records.pl">Xóa biểu ghi hàng loạt</a>
                </li>
            [% END %]
            [% IF ( CAN_user_tools_marc_modification_templates ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/marc_modification_templates.pl">Mẫu quy tắc chỉnh sửa MARC</a>
                </li>
            [% END %]
            [% IF ( CAN_user_editcatalogue_records_restore ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/restore-records.pl">Khôi phục biểu ghi đã xóa</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_tools_items_batchmod || ( CAN_user_stockrotation_manage_rotas && Koha.Preference('StockRotation') ) ) %]
        <h5><i class="fa fa-sync"></i> Tự động hóa</h5>
        <ul>
            [% IF ( CAN_user_tools_items_batchmod ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/automatic_item_modification_by_age.pl">Thay đổi bản tài liệu theo thời gian</a>
                </li>
            [% END %]
            [% IF ( CAN_user_stockrotation_manage_rotas && Koha.Preference('StockRotation') ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/stockrotation.pl">Luân chuyển kho tài liệu</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_tools_label_creator || CAN_user_tools_upload_local_cover_images ) %]
        <h5><i class="fa fa-tools"></i> Công cụ nghiệp vụ</h5>
        <ul>
            [% IF ( CAN_user_tools_label_creator ) %]
                <li>
                    <a href="/cgi-bin/koha/labels/label-home.pl">In nhãn gáy &amp; Mã vạch</a>
                </li>
                <li>
                    <a href="/cgi-bin/koha/labels/barcode-print.pl">Tạo hình ảnh mã vạch</a>
                </li>
                <li>
                    <a href="/cgi-bin/koha/labels/spinelabel-home.pl">In nhanh nhãn gáy sách</a>
                </li>
            [% END %]

            [% IF ( CAN_user_tools_upload_local_cover_images ) %]
                <li>
                    <a href="/cgi-bin/koha/tools/upload-cover-image.pl">Tải lên ảnh bìa sách</a>
                </li>
            [% END %]
        </ul>
    [% END %]

    [% IF ( CAN_user_parameters ) %]
        <h5><i class="fa fa-cog"></i> Quản trị hệ thống</h5>
        <ul>
            [% IF ( CAN_user_parameters_manage_sysprefs ) %]
                <li>
                    <a class="circ-button" href="/cgi-bin/koha/admin/preferences.pl?tab=cataloguing">Thiết lập tham số biên mục</a>
                </li>
            [% END %]
            <li>
                <a class="circ-button" href="/cgi-bin/koha/admin/admin-home.pl">Cấu hình hệ thống</a>
            </li>
        </ul>
    [% END %]
</div>
<!-- /.sidebar_menu -->
