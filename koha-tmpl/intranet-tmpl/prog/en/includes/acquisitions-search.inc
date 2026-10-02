[% USE raw %]
[% PROCESS 'html_helpers.inc' %]
<!-- acquisitions-search.inc -->
[% FILTER collapse %]
    [% WRAPPER tabs id="header_search" %]

        [% WRAPPER tab_panels %]
            [% WRAPPER tab_panel tabname="supplier_search" bt_active= 1 %]
                <form name="findsupplier" action="/cgi-bin/koha/acquisition/vendors" method="get">
                    <div class="form-title">
                        <label class="control-label" for="supplier"><span class="control-text">Tìm nhà cung cấp</span> <i class="fa fa-fw fa-truck-field" aria-hidden="true"></i></label>
                    </div>

                    <div class="form-content">
                        <input type="text" name="supplier" id="supplier" class="head-searchbox form-control" placeholder="Tìm kiếm nhà cung cấp, đối tác..." />
                    </div>
                    <button type="submit" aria-label="Tìm kiếm"><i class="fa fa-magnifying-glass"></i></button>
                </form>
            [% END # /tab_panel# %]
            [% WRAPPER tab_panel tabname="orders_search" %]
                <form action="/cgi-bin/koha/acqui/histsearch.pl" method="get">
                    <div class="form-title">
                        <label class="control-label" for="order_title"><span class="control-text">Tìm đơn hàng</span> <i class="fa fa-fw fa-basket-shopping" aria-hidden="true"></i></label>
                    </div>

                    <div class="form-content">
                        <input type="text" id="order_title" class="form-control" placeholder="Nhan đề tài liệu..." name="title" size="13" value="[% title | html %]" />
                        <input type="text" id="searchsupplier" class="form-control" placeholder="Nhà cung cấp..." name="name" size="13" value="[% name | html %]" />
                        <button type="button" class="form-extra-content-toggle" title="Tùy chọn mở rộng"><i class="form-extra-content-icon fa-solid fa-sliders" aria-hidden="true"></i></button>
                        <input type="hidden" id="do_search" name="do_search" value="do" />
                    </div>
                    <button type="submit" aria-label="Tìm kiếm"><i class="fa fa-magnifying-glass"></i></button>

                    <div class="form-extra-content">
                        <div>
                            <label for="basket" class="control-label">Giỏ đặt hàng</label>
                            <input type="text" class="form-control" placeholder="Tên hoặc mã giỏ..." name="basket" id="basket" />
                        </div>
                        <div>
                            <label for="booksellerinvoicenumber" class="control-label">Số hóa đơn</label>
                            <input type="text" class="form-control" placeholder="Số hóa đơn đối tác..." name="booksellerinvoicenumber" id="booksellerinvoicenumber" />
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
                <i class="fa fa-truck-field" aria-hidden="true"></i> <span class="tab-title">Tìm nhà cung cấp</span>
            [% END %]
            [% WRAPPER tab_item tabname= "orders_search" %]
                <i class="fa fa-basket-shopping" aria-hidden="true"></i> <span class="tab-title">Tìm đơn hàng</span>
            [% END %]
        [% END # /WRAPPER tabs_nav %]
    [% END # /WRAPPER tabs %]
[% END %]

<!-- /acquisitions-search.inc -->
