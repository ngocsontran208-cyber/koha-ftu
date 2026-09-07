[% USE raw %]
[% USE Koha %]
[% PROCESS 'html_helpers.inc' %]
[% WRAPPER tabs id="header_search" %]
 [% WRAPPER tab_panels %]
 [% WRAPPER tab_panel tabname="suggestions_search" bt_active= 1 %]
 <form action="/cgi-bin/koha/acqui/newordersuggestion.pl" method="get">
 <input type="hidden" name="booksellerid" value="[% booksellerid | html %]" />

 <div class="form-title">
 <label class="control-label" for="searchtitle"><span class="control-text">Tìm đề xuất mua</span> <i class="fa-solid fa-fw fa-comment" aria-hidden="true"></i></label>
 </div>

 <div class="form-content">
 <input class="head-searchbox form-control" id="searchtitle" name="title" placeholder="Nhan đề" size="10" type="text" value="[% title | html %]" />
 <input class="head-searchbox form-control" id="searchauthor" name="author" placeholder="Tác giả" size="10" type="text" value="[% author | html %]" />
 <input class="head-searchbox form-control" id="searchpublishercode" name="publishercode" placeholder="Nhà xuất bản" size="10" type="text" value="[% publishercode | html %]" />
 </div>

 <button aria-label="Tìm kiếm" type="submit"><i class="fa fa-arrow-right"></i></button>
 </form>
 [% END # /tab_panel %]

 [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
 [% INCLUDE 'patron-search-box.inc' %]
 [% END %]

 [% IF ( CAN_user_catalogue ) %]
 [% INCLUDE 'catalogue-search-box.inc' %]
 [% END %]
 [% END # /tab_panels %]
 [% WRAPPER tabs_nav %]
 [% WRAPPER tab_item tabname= "suggestions_search" bt_active= 1 %]
 <i class="fa-solid fa-comment" aria-hidden="true"></i> <span class="tab-title">Tìm đề xuất mua</span>
 [% END %]
 [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
 [% WRAPPER tab_item tabname= "circ_search" %]
 <i class="fa fa-upload" aria-hidden="true"></i> <span class="tab-title">Ghi mượn</span>
 [% END %]
 [% END %]
 [% IF ( CAN_user_catalogue ) %]
 [% WRAPPER tab_item tabname= "catalog_search" %]
 <i class="fa fa-fw fa-search" aria-hidden="true"></i> <span class="tab-title">Search catalog</span>
 [% END %]
 [% END %]
 [% END # /tabs_nav %]
[% END # /WRAPPER tabs %]
<!-- /suggestions-add-search.inc -->
