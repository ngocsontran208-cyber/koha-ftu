[% USE Koha %]
<div id="guided-reports-view-menu" class="sidebar_menu">
 <h5>View reports</h5>
 <ul>
 [% IF ( CAN_user_reports_execute_reports || CAN_user_reports_create_reports || CAN_user_reports_delete_own_reports || CAN_user_reports_delete_all_reports ) %]
 <li><a href="/cgi-bin/koha/reports/guided_reports.pl?op=list">Báo cáo được lưu lại</a></li>
 [% END %]
 </ul>
 <h5>Từ điển báo cáo</h5>
 <ul>
 <li><a href="/cgi-bin/koha/reports/dictionary.pl">Xem từ điển</a></li>
 </ul>
 <h5>Nguồn tham khảo</h5>
 <ul>
 <li><a href="https://wiki.koha-community.org/wiki/SQL_Reports_Library" target="blank">Báo cáo mẫu Koha</a></li>
 [% SET koha_version = Koha.Version %]
 [% IF koha_version.development %]
 <li><a href="https://schema.koha-community.org/main" target="blank">Sơ đồ dữ liệu Koha</a></li>
 [% ELSE %]
 <li><a href="https://schema.koha-community.org/[% koha_version.major | uri %]_[% koha_version.minor | uri %]" target="blank">Sơ đồ dữ liệu Koha</a></li>
 [% END %]
 </ul>
</div>
<!-- /.sidebar_menu -->
