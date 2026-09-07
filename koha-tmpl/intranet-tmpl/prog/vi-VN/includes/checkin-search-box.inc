[% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
 <!-- checkin-search-box.inc -->
 [% WRAPPER tab_panel tabname="checkin_search" bt_active= bs_tab_active %]
 <form method="post" action="/cgi-bin/koha/circ/returns.pl" autocomplete="off">
 [% INCLUDE 'csrf-token.inc' %]
 <div class="form-title">
 <label class="control-label" for="ret_barcode"><span class="control-text">Ghi Trả</span> <i class="fa fa-fw fa-download" aria-hidden="true"></i></label>
 </div>

 <div class="form-content">
 <input name="barcode" id="ret_barcode" class="head-searchbox form-control" accesskey="r" type="text" placeholder="Scan a barcode to check in" size="40" />
 <input type="hidden" name="op" value="cud-checkin" />
 </div>
 <button aria-label="Tìm kiếm" type="submit"><i class="fa fa-arrow-right"></i></button>
 </form>
 [% END # /tab_panel %]
 <!-- /checkin-search-box.inc -->
[% END %]
