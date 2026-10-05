[% USE Koha %]
[% USE KohaPlugins %]
[% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && loggedinusername ) %]
 <div id="menu">
 <ul>
 <li [% IF userview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-user.pl">Tóm tắt</a></li>

 [% IF Koha.Preference( 'OPACVirtualCard' ) %]
 <li [% IF virtualcardview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-virtual-card.pl">Library card</a></li>
 [% END %]

 [% IF ( OPACFinesTab ) %]
 <li [% IF accountview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-account.pl">Các khoản phí</a></li>
 [% END %]

 <li [% IF userupdateview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-memberentry.pl">Thông tin cá nhân</a></li>

 [% IF Koha.Preference('PrivacyPolicyConsent') || KohaPlugins.feature_enabled('patron_consent_type') %]
 <li [% IF consentview %]class="active"[% END %]>
 <a href="/cgi-bin/koha/opac-patron-consent.pl">Sự đồng ý</a>
 </li>
 [% END %]

 [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]
 <li [% IF tagsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-tags.pl?mine=1">Thẻ</a></li>
 [% END %]

 [% IF logged_in_user.category.effective_change_password %]
 <li [% IF passwdview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-passwd.pl">Đổi mật khẩu</a></li>
 [% END %]

 [% IF EnableOpacSearchHistory %]
 <li [% IF searchhistoryview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-search-history.pl">Lịch sử tìm kiếm</a></li>
 [% END %]

 [% IF ( opacreadinghistory ) %]
 <li [% IF readingrecview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-readingrecord.pl">Lịch sử mượn tài liệu</a></li>
 [% IF ( OPACPrivacy ) %]
 <li [% IF privacyview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-privacy.pl">Quyền riêng tư</a></li>
 [% END %]
 [% END # / opacreadinghistory %]

 [% IF Koha.Preference('OPACHoldsHistory') == 1 %]
 <li [% IF holdshistoryview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-holdshistory.pl">Lịch sử đặt trước</a></li>
 [% END %]

 [% IF Koha.Preference('UseRecalls') %]
 <li [% IF recallsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-recalls.pl">Lịch sử yêu cầu thu hồi</a> </li>
 [% END %]

 [% IF ( suggestion ) %]
 <li [% IF suggestionsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-suggestions.pl">Đề xuất mua tài liệu</a></li>
 [% END %]

 [% IF ( EnhancedMessagingPreferences ) %]
 [% IF Koha.Preference( 'EnhancedMessagingPreferencesOPAC' ) || Koha.Preference('TranslateNotices') %]
 <li [% IF messagingview %]class="active"[% END %]>
     <a href="/cgi-bin/koha/opac-messaging.pl">Tin nhắn & Thông báo
     [% SET unread_cnt = logged_in_user.messages.search({ message_type => 'B' }).filter_by_unread.count %]
     [% IF unread_cnt > 0 %]
         <span class="badge bg-danger rounded-pill" style="font-size: 0.75rem; margin-left: 4px;">[% unread_cnt | html %]</span>
     [% END %]
     </a>
 </li>
 [% END %]
 [% END %]

 [% IF Koha.Preference( 'virtualshelves' ) == 1 %]
 <li [% IF listsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-shelves.pl?op=list">Danh sách</a></li>
 [% END %]

 [% IF Koha.Preference( 'RoutingSerials' ) && logged_in_user && logged_in_user.get_routing_lists.count %]
 <li [% IF routinglistsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-routing-lists.pl">Danh sách luân chuyển</a></li>
 [% END %]

 [% IF Koha.Preference( 'useDischarge' ) == 1 %]
 <li [% IF dischargeview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-discharge.pl">Yêu cầu thanh lý hồ sơ thư viện</a></li>
 [% END %]

 [% IF Koha.Preference( 'ILLModule' ) == 1 %]
 <li [% IF illrequestsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-illrequests.pl">Yêu cầu mượn từ thư viện khác</a></li>
 [% END %]

 [% IF Koha.Preference( 'CurbsidePickup' ) %]
 <li [% IF curbside_pickups_view %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-curbside-pickups.pl">Nhận sách ngoài thư viện</a></li>
 [% END %]

 [% IF logged_in_user.alert_subscriptions.count %]
 <li [% IF alertsview %]class="active"[% END %]> <a href="/cgi-bin/koha/opac-alert-subscriptions.pl">Alert subscriptions ([% logged_in_user.alert_subscriptions.count | html %])</a></li>
 [% END %]
 </ul>
 </div>
[% END %]
