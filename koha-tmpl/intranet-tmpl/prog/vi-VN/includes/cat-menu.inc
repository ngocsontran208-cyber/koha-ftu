[% USE Koha %]
<div id="cat-menu" class="sidebar_menu">
 [% IF ( CAN_user_tools_stage_marc_import || CAN_user_tools_manage_staged_marc ) %]
 <h5>Nhập dữ liệu</h5>
 <ul>
 [% IF ( CAN_user_tools_stage_marc_import ) %]
 <li>
 <a href="/cgi-bin/koha/tools/stage-marc-import.pl">Stage records for import</a>
 </li>
 [% END %]
 [% IF ( CAN_user_tools_manage_staged_marc ) %]
 <li>
 <a href="/cgi-bin/koha/tools/manage-marc-import.pl">Quản lý biểu ghi MARC được duyệt</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_tools_export_catalog ) %]
 <h5>Xuất dữ liệu</h5>
 <ul>
 [% IF ( CAN_user_tools_export_catalog ) %]
 <li>
 <a href="/cgi-bin/koha/tools/export.pl">Export catalog data</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_tools_inventory || ( ( Koha.Preference('OpacCatalogConcerns') || Koha.Preference('CatalogConcerns') ) && CAN_user_editcatalogue_edit_catalogue ) ) %]
 <h5>Báo cáo</h5>
 <ul>
 [% IF ( CAN_user_tools_inventory ) %]
 <li>
 <a href="/cgi-bin/koha/tools/inventory.pl">Kiểm kê kho</a>
 </li>
 [% END %]
 [% IF ( Koha.Preference('OpacCatalogConcerns') || Koha.Preference('CatalogConcerns') ) && CAN_user_editcatalogue_edit_catalogue %]
 <li>
 <a href="/cgi-bin/koha/cataloguing/concerns.pl">Catalog concerns</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_tools_items_batchmod || CAN_user_tools_items_batchdel || CAN_user_tools_records_batchmod || CAN_user_tools_records_batchdel || CAN_user_editcatalogue_records_restore || CAN_user_tools_marc_modification_templates ) %]
 <h5>Batch editing</h5>
 <ul>
 [% IF ( CAN_user_tools_items_batchmod ) %]
 <li>
 <a href="/cgi-bin/koha/tools/batchMod.pl">Chỉnh sửa bản tài liệu theo lô</a>
 </li>
 [% END %]
 [% IF ( CAN_user_tools_items_batchdel ) %]
 <li>
 <a href="/cgi-bin/koha/tools/batchMod.pl?del=1">Xóa bản tài liệu theo lô</a>
 </li>
 [% END %]
 [% IF CAN_user_tools_records_batchmod %]
 <li>
 <a href="/cgi-bin/koha/tools/batch_record_modification.pl">Batch record modification</a>
 </li>
 [% END %]
 [% IF CAN_user_tools_records_batchdel %]
 <li>
 <a href="/cgi-bin/koha/tools/batch_delete_records.pl">Batch record deletion</a>
 </li>
 [% END %]
 [% IF ( CAN_user_tools_marc_modification_templates ) %]
 <li>
 <a href="/cgi-bin/koha/tools/marc_modification_templates.pl">Mẫu chỉnh sửa biểu ghi MARC</a>
 </li>
 [% END %]
 [% IF ( CAN_user_editcatalogue_records_restore ) %]
 <li>
 <a href="/cgi-bin/koha/tools/restore-records.pl">Restore deleted records</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_tools_items_batchmod || ( CAN_user_stockrotation_manage_rotas && Koha.Preference('StockRotation') ) ) %]
 <h5>Automation</h5>
 <ul>
 [% IF ( CAN_user_tools_items_batchmod ) %]
 <li>
 <a href="/cgi-bin/koha/tools/automatic_item_modification_by_age.pl">Item modifications by age</a>
 </li>
 [% END %]
 [% IF ( CAN_user_stockrotation_manage_rotas && Koha.Preference('StockRotation') ) %]
 <li>
 <a href="/cgi-bin/koha/tools/stockrotation.pl">Stock rotation</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_tools_label_creator || CAN_user_tools_upload_local_cover_images ) %]
 <h5>Công cụ bổ trợ</h5>
 <ul>
 [% IF ( CAN_user_tools_label_creator ) %]
 <li>
 <a href="/cgi-bin/koha/labels/label-home.pl">Tạo nhãn gáy</a>
 </li>
 <li>
 <a href="/cgi-bin/koha/labels/barcode-print.pl">Barcode image generator</a>
 </li>
 <li>
 <a href="/cgi-bin/koha/labels/spinelabel-home.pl">Tạo nhanh nhãn gáy</a>
 </li>
 [% END %]

 [% IF ( CAN_user_tools_upload_local_cover_images ) %]
 <li>
 <a href="/cgi-bin/koha/tools/upload-cover-image.pl">Thêm ảnh bìa cho biểu ghi</a>
 </li>
 [% END %]
 </ul>
 [% END %]

 [% IF ( CAN_user_parameters ) %]
 <h5>Quản trị hệ thống</h5>
 <ul>
 [% IF ( CAN_user_parameters_manage_sysprefs ) %]
 <li>
 <a class="circ-button" href="/cgi-bin/koha/admin/preferences.pl?tab=cataloguing">Preferences</a>
 </li>
 [% END %]
 <li>
 <a class="circ-button" href="/cgi-bin/koha/admin/admin-home.pl">Configuration</a>
 </li>
 </ul>
 [% END %]
</div>
<!-- /.sidebar_menu -->
