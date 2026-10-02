[% USE raw %]
<!-- str/cataloging_additem.inc -->
<script nonce="[% Koha.CSPNonce | $raw %]">
    var searchid = '[% searchid | html %]';
    var biblionumber = '[% biblionumber | html %]';
    var frameworkcode = '[% frameworkcode | html %]';
    [% IF popup %]
      var popup = true;
    [% ELSE %]
      var popup = false;
    [% END %]
    var op = '[% op | html %]';
    var LABEL_EDIT_ITEM = _("Sửa bản tài liệu");
    var LABEL_DELETE_ITEM = _("Xóa bản tài liệu");
    var MSG_FORM_NOT_SUBMITTED = _("Phát hiện các lỗi sau đây, bạn vui lòng kiểm tra và chỉnh sửa lại:");
    var MSG_MANDATORY_FIELDS_EMPTY = _("%s Các trường bắt buộc chưa khai báo thông tin (được đánh dấu)");
    var MSG_IMPORTANT_FIELDS_EMPTY = _("%s trường thông tin quan trọng chưa nhập (được đánh dấu)");
    var MSG_ADD_MULTIPLE_ITEMS = _("Bạn sắp thêm %s bản tài liệu mới. Tiếp tục?");
    var MSG_ENTER_NUM_ITEMS = _("Vui lòng nhập số bản tài liệu được tạo mới.");
    var MSG_CONFIRM_DELETE_ITEM = _("Bạn chắc chắn muốn xóa bản tài liệu này?");
    var MSG_CONFIRM_ADD_ITEM = _("Bạn có chắc chắn muốn thêm bản tài liệu mới? Mọi thay đổi chưa lưu trên trang này sẽ bị mất.");
    var MSG_CONFIRM_SAVE = _("Bạn có chắc chắn muốn lưu?");
    var table_settings = [% TablesSettings.GetTableSettings( 'cataloguing', 'additem', 'itemst', 'json' ) | $raw %];
</script>
<!-- / str/cataloging_additem.inc -->
