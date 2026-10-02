[% USE Koha %]
[% USE Branches %]
[% PROCESS 'html_helpers.inc' %]
[% IF context == "main" %]
    <div class="row">
        <div class="col-sm-6">
            <ol>
                [% PROCESS 'search-orders-1' %]
            </ol>
        </div>
        <div class="col-sm-6">
            <ol>
                [% PROCESS 'search-orders-2' %]
            </ol>
        </div>
    </div>
[% ELSE %]
    <ol>
        [% PROCESS 'search-orders-1' %]
        [% PROCESS 'search-orders-2' %]
    </ol>
[% END %]

[% BLOCK 'search-orders-1' %]
    <li><label for="title">Nhan đề tài liệu: </label> <input type="text" name="title" id="title" value="[% filters.title | html %]" placeholder="Nhập nhan đề sách, tài liệu..." /></li>
    <li><label for="author">Tác giả: </label> <input type="text" name="author" id="author" value="[% filters.author | html %]" placeholder="Tên tác giả, dịch giả..." /></li>
    <li><label for="isbn">Mã chuẩn ISBN: </label> <input type="text" name="isbn" id="isbn" value="[% filters.isbn | html %]" placeholder="ISBN..." /></li>
    <li><label for="issn">Mã chuẩn ISSN: </label> <input type="text" name="issn" id="issn" value="[% filters.issn | html %]" placeholder="ISSN..." /></li>
    [% IF Koha.Preference('marcflavour') == 'UNIMARC' %]
        <li><label for="ean">Mã vạch EAN: </label> <input type="text" name="ean" id="ean" value="[% filters.ean | html %]" /></li>
    [% END %]
    <li><label for="name">Nhà cung cấp / Đối tác: </label> <input type="text" name="name" id="name" value="[% filters.name | html %]" placeholder="Tên nhà cung cấp..." /></li>
    <li><label for="basket">Giỏ đặt hàng: </label> <input type="text" name="basket" id="basket" value="[% filters.basket | html %]" placeholder="Tên hoặc mã giỏ..." /></li>
    <li><label for="internalnote">Ghi chú nội bộ: </label> <input type="text" name="internalnote" id="internalnote" value="[% filters.internalnote | html %]" /></li>
    <li><label for="vendornote">Ghi chú đối tác: </label> <input type="text" name="vendornote" id="vendornote" value="[% filters.vendornote | html %]" /></li>
    <li>
        <label for="find_patron">Cán bộ tạo giỏ: </label>
        <input autocomplete="off" id="find_patron" type="text" class="noEnterSubmit" placeholder="Tìm kiếm cán bộ thư viện..." />
        <div>
            <div id="basket_creators" style="float:left;"></div>
        </div>
    </li>
    <li>
        <label for="managing_library">Cơ sở thư viện: </label>
        <select name="managing_library" id="managing_library">
            <option value="">Tất cả các cơ sở</option>
            [% PROCESS options_for_libraries libraries => Branches.all(selected => '') %]
        </select>
    </li>
[% END %]
[% BLOCK 'search-orders-2' %]
    <li><label for="booksellerinvoicenumber">Số hóa đơn đối tác: </label> <input type="text" name="booksellerinvoicenumber" id="booksellerinvoicenumber" value="[% filters.booksellerinvoicenumber | html %]" /></li>
    <li>
        <label for="basketgroupname">Nhóm giỏ đơn hàng:</label>
        <input type="text" name="basketgroupname" id="basketgroupname" value="[% filters.basketgroupname | html %]" />
    </li>
    [% INCLUDE 'additional-fields-entry.inc' available=available_additional_fields values=additional_field_filters wrap_fieldset=0 search_form=1 %]
    <li>
        <label for="ordernumber">Mã dòng đơn hàng:</label>
        <input type="text" name="ordernumber" id="ordernumber" value="[% filters.ordernumber | html %]" />
    </li>
    <li class="radio">
        <label for="search_children_too">
            [% IF filters.search_children_too %]
                <input type="checkbox" name="search_children_too" id="search_children_too" value="1" checked="checked" />
            [% ELSE %]
                <input type="checkbox" name="search_children_too" id="search_children_too" value="1" />
            [% END %]
            Hiển thị cả các mục con phụ thuộc
        </label>
    </li>

    <li>
        <label for="orderstatus">Trạng thái đơn hàng: </label>
        <select name="orderstatus" id="orderstatus">
            [% IF filters.orderstatus == "" %]
                <option value="">Tất cả trạng thái (trừ đã hủy)</option>
            [% ELSE %]
                <option value="" selected="selected">Tất cả trạng thái (trừ đã hủy)</option>
            [% END %]
            [% IF filters.orderstatus == "any" %]
                <option value="any" selected="selected">Tất cả mọi trạng thái</option>
            [% ELSE %]
                <option value="any">Tất cả mọi trạng thái</option>
            [% END %]
            [% IF filters.orderstatus == "new" %]
                <option value="new" selected="selected">Mới tạo</option>
            [% ELSE %]
                <option value="new">Mới tạo</option>
            [% END %]
            [% IF filters.orderstatus == "ordered" %]
                <option value="ordered" selected="selected">Đã đặt hàng</option>
            [% ELSE %]
                <option value="ordered">Đã đặt hàng</option>
            [% END %]
            [% IF filters.orderstatus == "partial" %]
                <option value="partial" selected="selected">Đã tiếp nhận một phần</option>
            [% ELSE %]
                <option value="partial">Đã tiếp nhận một phần</option>
            [% END %]
            [% IF filters.orderstatus == "complete" %]
                <option value="complete" selected="selected">Đã tiếp nhận toàn bộ</option>
            [% ELSE %]
                <option value="complete">Đã tiếp nhận toàn bộ</option>
            [% END %]
            [% IF filters.orderstatus == "cancelled" %]
                <option value="cancelled" selected="selected">Đã hủy đơn</option>
            [% ELSE %]
                <option value="cancelled">Đã hủy đơn</option>
            [% END %]
        </select>
    </li>
    <li class="radio">
        <label class="yesno" for="is_standing">
            [% IF filters.is_standing %]
                <input type="checkbox" name="is_standing" id="is_standing" value="1" checked="checked" />
            [% ELSE %]
                <input type="checkbox" name="is_standing" id="is_standing" value="1" />
            [% END %]
            Đơn hàng định kỳ (Standing order)
        </label>
    </li>
    <li>
        <label for="fund">Nguồn quỹ bổ sung: </label>
        <select name="budget" id="fund">
            <option value="">Tất cả các quỹ</option>
            [% FOREACH bp_loo IN bp_loop %]
                <optgroup label="[% bp_loo.budget_period_description | html %]">
                    [% FOREACH h_loo IN bp_loo.hierarchy %]
                        <option type="text" value="[% h_loo.budget_id | html %]" branchcode="[% h_loo.budget_branchcode | html %]" [% IF h_loo.budget_id == filters.budget %]selected="selected"[% END %]>
                            [% h_loo.budget_display_name | html %]
                        </option>
                    [% END %]
                </optgroup>
            [% END %]
        </select>
    </li>

    <li>
        <label for="from">Đặt từ ngày: </label>
        <input type="text" size="10" id="from" name="from" value="[% filters.from_placed_on | html %]" class="flatpickr" data-date_to="to" placeholder="dd/mm/yyyy" />
        <div class="hint">[% INCLUDE 'date-format.inc' %]</div>
    </li>
    <li>
        <label for="to">Đến ngày: </label>
        <input type="text" size="10" id="to" name="to" value="[% filters.to_placed_on | html %]" class="flatpickr" placeholder="dd/mm/yyyy" />
        <div class="hint">[% INCLUDE 'date-format.inc' %]</div>
    </li>
[% END %]
