[% USE raw %]
[% PROCESS 'html_helpers.inc' %]
<!-- acquisitions-search.inc -->
[% FILTER collapse %]
 [% WRAPPER tabs id="header_search" %]

 [% WRAPPER tab_panels %]
 [% WRAPPER tab_panel tabname="supplier_search" bt_active= 1 %]
 <form name="findsupplier" action="/cgi-bin/koha/acquisition/vendors" method="get">
 <div class="form-title">
 <label class="control-label" for="supplier"><span class="control-text">Tìm kiếm nhà cung cấp</span> <i class="fa fa-fw fa-upload" aria-hidden="true"></i></label>
 </div>

 <div class="form-content">
 <input type="text" name="supplier" id="supplier" class="head-searchbox form-control" placeholder="Search vendors" />
 </div>
 <button aria-label="Tìm kiếm" type="submit"><i class="fa fa-arrow-right"></i></button>
 </form>
 [% END # /tab_panel# %]
 [% WRAPPER tab_panel tabname="orders_search" %]
 <form action="/cgi-bin/koha/acqui/histsearch.pl" method="get">
 <div class="form-title">
 <label class="control-label" for="order_title"><span class="control-text">Tìm kiếm đơn hàng</span> <i class="fa fa-fw fa-download" aria-hidden="true"></i></label>
 </div>

 <div class="form-content">
 <input class="form-control" id="order_title" name="title" placeholder="Nhan đề" size="13" type="text" value="[% title | html %]" />
 <input class="form-control" id="searchsupplier" name="name" placeholder="Nhà cung cấp" size="13" type="text" value="[% name | html %]" />
 <button class="form-extra-content-toggle" title="Thêm tùy chọn" type="button"><i class="form-extra-content-icon fa-solid fa-sliders" aria-hidden="true"></i></button>
 <input type="hidden" id="do_search" name="do_search" value="do" />
 </div>
 <button aria-label="Tìm kiếm" type="submit"><i class="fa fa-arrow-right"></i></button>

 <div class="form-extra-content">
 <div>
 <label for="basket" class="control-label">Giỏ đặt hàng</label>
 <input class="form-control" id="basket" name="basket" placeholder="Giỏ đặt hàng" type="text" />
 </div>
 <div>
 <label for="booksellerinvoicenumber" class="control-label">Số hóa đơn</label>
 <input class="form-control" id="booksellerinvoicenumber" name="booksellerinvoicenumber" placeholder="Số hóa đơn" type="text" />
 </div>
 <div>
 <a href="/cgi-bin/koha/acqui/histsearch.pl">Tìm kiếm nâng cao</a>
 </div>
 </div>
 </form>
 [% END # /tab_panel# %]
 [% END # /WRAPPER tab_panels %]

 [% WRAPPER tabs_nav %]
 [% WRAPPER tab_item tabname= "supplier_search" bt_active= 1 %]
 <i class="fa fa-upload" aria-hidden="true"></i> <span class="tab-title">Tìm kiếm nhà cung cấp</span>
 [% END %]
 [% WRAPPER tab_item tabname= "orders_search" %]
 <i class="fa fa-download" aria-hidden="true"></i> <span class="tab-title">Tìm kiếm đơn hàng</span>
 [% END %]
 [% END # /WRAPPER tabs_nav %]
 [% END # /WRAPPER tabs %]
[% END %]

<!-- /acquisitions-search.inc -->
