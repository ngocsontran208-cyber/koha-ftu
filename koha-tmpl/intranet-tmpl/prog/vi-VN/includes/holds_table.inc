[% USE Koha %]
[% SET hold_cancellation = AuthorisedValues.GetAuthValueDropbox('HOLD_CANCELLATION') %]
[% USE AuthorisedValues %]

<table id="patron_holds_table_[% biblio_id | html %]_[% split_data | html %]" class="holds_table" data-total-holds="[% total_holds | html %]">
 <thead>
 <tr>
 <th id="checkbox" data-colname="checkbox"><input type="checkbox" class="select_hold_all" /></th>
 <th id="priority" data-colname="priority">Ưu tiên</th>
 <th id="change_priority" data-colname="change_priority">Change priority</th>
 <th id="patron" data-colname="patron">Bạn đọc</th>
 <th id="notes" data-colname="notes">Ghi chú</th>
 <th id="date" data-colname="date">Ngày</th>
 <th id="expiration" data-colname="expiration">Ngày hết hạn</th>
 <th id="pickup_library" data-colname="pickup_library">Thư viện nhận sách</th>
 <th id="details" data-colname="details">Chi tiết</th>
 <th id="set_lowest_priority" data-colname="set_lowest_priority"><span style="display:none;">Set lowest priority</span><i class="fa fa-lg fa-rotate-90 fa-fast-forward" title="Chuyển thành đặt mượn có mức ưu tiên thấp nhất"></i></th>
 <th id="delete" data-colname="delete">Xóa</th>
 <th id="suspend" data-colname="suspend">Tạm ngưng</th>
 <th id="print_slip" data-colname="print_slip">Print hold/transfer slip</th>
 </tr>
 </thead>
</table>
