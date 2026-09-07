[% USE raw %]
[% IF ( PAGE_NUMBERS ) %]
 <nav aria-label="Phân trang kết quả tìm kiếm" class="noprint">
 [% IF hits_to_paginate < total %]
 <span class="h6">Đã tải [% hits_to_paginate | html %] trong tổng số [% total | html %] kết quả, vui lòng thu hẹp tìm kiếm để xem các biểu ghi khác</span>
 [% END %]
 <ul class="pagination pagination-sm">
 [% IF ( previous_page_offset.defined ) %]
 <li class="page-item">
 <a aria-label="Đến trang đầu" class="page-link" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]"><i class="fa fa-fw fa-angle-double-left" aria-hidden="true"></i> Đầu tiên</a
                    >
 </li>
 <li class="page-item">
 <a aria-label="Đến trang trước" class="page-link" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% previous_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">
 <i class="fa fa-fw fa-angle-left" aria-hidden="true"></i> Trước</a
                    >
 </li>
 [% END %]
 [% FOREACH PAGE_NUMBER IN PAGE_NUMBERS %]
 [% IF ( PAGE_NUMBER.highlight ) %]
 <li class="page-item active">
 <a aria-current="page" aria-label="Trang hiện tại: Trang [% PAGE_NUMBER.pg | html %]" class="page-link" href="#">[% PAGE_NUMBER.pg | html %]</a>
 </li>
 [% ELSE %]
 <li class="page-item">
 <a aria-label="Đến trang [% PAGE_NUMBER.pg | html %]" class="page-link" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% PAGE_NUMBER.offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">[% PAGE_NUMBER.pg | html %]</a
                        >
 </li>
 [% END %]
 [% END %]
 [% IF ( next_page_offset ) %]
 <li class="page-item">
 <a aria-label="Đến trang kế tiếp" class="page-link" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% next_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">Tiếp <i class="fa fa-fw fa-angle-right" aria-hidden="true"></i
                    ></a>
 </li>
 <li class="page-item">
 <a aria-label="Đến trang cuối cùng" class="page-link" href="/cgi-bin/koha/opac-search.pl?[% query_cgi | $raw %][% limit_cgi | $raw %]&offset=[% last_page_offset | uri %][% IF ( sort_by ) %]&sort_by=[% sort_by | uri %][% END %][% IF results_per_page %]&count=[% results_per_page | uri %][% END %]">Cuối <i class="fa fa-fw fa-angle-double-right" aria-hidden="true"></i
                    ></a>
 </li>
 [% END %]
 </ul>
 </nav>
[% END %]
