[% USE ItemTypes %]
<!-- Place booking modal -->
<div class="modal" id="placeBookingModal" tabindex="-1" role="dialog" aria-labelledby="placeBookingLabel">
 <form method="get" id="placeBookingForm">
 <div class="modal-dialog modal-lg">
 <div class="modal-content">
 <div class="modal-header">
 <h1 class="modal-title" id="placeBookingLabel"></h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <div class="modal-body">
 <div id="booking_result"></div>
 <fieldset class="brief">
 <input type="hidden" name="biblio_id" id="booking_id" />
 <input type="hidden" name="biblio_id" id="booking_biblio_id" />
 <input type="hidden" name="start_date" id="booking_start_date" />
 <input type="hidden" name="end_date" id="booking_end_date" />
 <ol>
 <li>
 <label class="required" for="booking_patron_id">Bạn đọc: </label>
 <select name="booking_patron_id" id="booking_patron_id" required="required">
 <option></option>
 [% IF patron %]
 <option value="[% borrowernumber | uri %]" selected="selected">[% patron.firstname | html %] [% patron.surname | html %] ([% patron.cardnumber | html %] )</option>
 [% END %]
 </select>
 <div class="hint">Enter patron card number or partial name</div>
 </li>
 <li>
 <label class="required" for="pickup_library_id">Nơi nhận tài liệu:</label>
 <select name="booking_pickup" id="pickup_library_id" required="required" disabled="disabled"></select>
 <span class="required">Bắt buộc</span>
 </li>
 <li>
 <label for="booking_itemtype">Itemtype: </label>
 <select id="booking_itemtype" name="booking_itemtype" disabled="disabled"> </select> </li
                            ><li>
 <label for="booking_item_id">Item: </label>
 <select name="booking_item_id" id="booking_item_id" disabled="disabled">
 <option value="0">Any item</option>
 </select>
 </li>
 <li>
 <div id="period_fields">
 <label class="required" for="period">Booking dates: </label>
 <input type="text" id="period" name="period" class="flatpickr" data-flatpickr-futuredate="true" data-flatpickr-disable-shortcuts="true" required="required" disabled="disabled" autocomplete="off" />
 <span class="required">Bắt buộc</span>
 </div>
 <div class="hint">Select the booking start and end date</div>
 </li>
 </ol>
 </fieldset>
 </div>
 <!-- /.modal-body -->
 <div class="modal-footer">
 <button type="submit" class="btn btn-primary">Gửi</button>
 <button type="button" class="btn btn-default" data-bs-dismiss="modal">Hủy bỏ</button>
 </div>
 <!-- /.modal-footer -->
 </div>
 <!-- /.modal-content -->
 </div>
 <!-- /.modal-dialog -->
 </form>
</div>
<!-- /#placeBookingModal -->
