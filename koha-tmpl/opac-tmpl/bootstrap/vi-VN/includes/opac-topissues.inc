[% USE Koha %]
[% USE Branches %]
[% PROCESS 'html_helpers.inc' %]
[% SET AllPublicBranches = Branches.all(  search_params => { public => 1 }, selected => branch, unfiltered => 1 ) %]

<div id="search-facets">
 <form method="get" action="/cgi-bin/koha/opac-topissues.pl">
 <h2><a href="#" class="menu-collapse-toggle" aria-expanded="false">Thu hẹp kết quả tìm kiếm</a></h2>
 <ul class="menu-collapse">
 <li
                ><label for="limit">Hiển thị hàng đầu </label>
 <select name="limit" id="limit">
 [% IF ( limit == 10 ) %]<option value="10" selected="selected">10 nhan đề</option>[% ELSE %]<option value="10">10 nhan đề</option>[% END %]
 [% IF ( limit == 15 ) %]<option value="15" selected="selected">15 nhan đề</option>[% ELSE %]<option value="15">15 nhan đề</option>[% END %]
 [% IF ( limit == 20 ) %]<option value="20" selected="selected">20 nhan đề</option>[% ELSE %]<option value="20">20 nhan đề</option>[% END %]
 [% IF ( limit == 30 ) %]<option value="30" selected="selected">30 nhan đề</option>[% ELSE %]<option value="30">30 nhan đề</option>[% END %]
 [% IF ( limit == 40 ) %]<option value="40" selected="selected">40 nhan đề</option>[% ELSE %]<option value="40">40 nhan đề</option>[% END %]
 [% IF ( limit == 50 ) %]<option value="50" selected="selected">50 nhan đề</option>[% ELSE %]<option value="50">50 nhan đề</option>[% END %]
 [% IF ( limit == 100 ) %]<option value="100" selected="selected">100 nhan đề</option>[% ELSE %]<option value="100">100 nhan đề</option>[% END %]
 </select></li
            >

 [% IF AllPublicBranches.size > 1 %]
 <li>
 <label for="branch">Từ: </label>
 <select name="branch" id="branch">
 <option value="">Tất cả thư viện</option>
 [% PROCESS options_for_libraries libraries => AllPublicBranches %]
 </select>
 </li>
 [% END %]

 [% OpacAdvancedSearchTypes = Koha.Preference('OpacAdvancedSearchTypes').split('\|') %]
 [% IF OpacAdvancedSearchTypes.grep('^itemtypes$').size %]
 <li>
 <label for="itemtype">Giới hạn ở: </label>
 <select name="itemtype" id="itemtype">
 <option value="">Tất cả loại tài liệu</option>
 [% FOREACH itemtype IN ItemTypes.Get() %]
 <option value="[% itemtype.itemtype | html %]" [% IF itemtype.itemtype == selected_itemtype %]selected="selected"[% END %]> [% itemtype.translated_description | html %] </option>
 [% END %]
 </select>
 </li>
 [% END %]

 [% IF OpacAdvancedSearchTypes.grep('^ccode$').size %]
 <li>
 <label for="ccode">Giới hạn ở:</label>
 <select name="ccode" id="ccode">
 <option value="">Tất cả bộ sưu tập</option>
 [% FOREACH ccode IN AuthorisedValues.Get('CCODE', 1) %]
 <option value="[% ccode.authorised_value | html %]" [% IF ccode.authorised_value == selected_ccode %]selected="selected"[% END %]> [% ccode.lib | html %] </option>
 [% END %]
 </select>
 </li>
 [% END %]

 <li
                ><label for="timeLimit">Nhập về trong khoảng:</label>
 <select name="timeLimit" id="timeLimit">
 <option value="3" [% IF timeLimit == 3 %]selected="selected"[% END %]>3 tháng</option>
 <option value="6" [% IF timeLimit == 6 %]selected="selected"[% END %]>6 tháng</option>
 <option value="12" [% IF timeLimit == 12 %]selected="selected"[% END %]>12 tháng</option>
 <option value="999" [% IF timeLimit == 999 %]selected="selected"[% END %]>Không giới hạn</option>
 </select></li
            >
 <li>
 <input type="hidden" name="do_it" value="1" />
 <input class="btn btn-primary" type="submit" value="Gửi" />
 </li>
 </ul>
 </form>
</div>
