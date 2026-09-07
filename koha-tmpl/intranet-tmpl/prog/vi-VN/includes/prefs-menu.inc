[% USE HtmlId %]
<div id="prefs-menu" class="sidebar_menu">
    <ul>
        [% IF ( accounting ) %]
            <li class="active">
                <a title="Accounting" href="/cgi-bin/koha/admin/preferences.pl?tab=accounting">Kế toán</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Accounting" href="/cgi-bin/koha/admin/preferences.pl?tab=accounting">Kế toán</a>
            </li>
        [% END %]
        [% IF ( acquisitions ) %]
            <li class="active">
                <a title="Acquisitions" href="/cgi-bin/koha/admin/preferences.pl?tab=acquisitions">Bổ sung tài liệu</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Acquisitions" href="/cgi-bin/koha/admin/preferences.pl?tab=acquisitions">Bổ sung tài liệu</a>
            </li>
        [% END %]

        [% IF ( admin ) %]
            <li class="active">
                <a title="Administration" href="/cgi-bin/koha/admin/preferences.pl?tab=admin">Quản trị</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Administration" href="/cgi-bin/koha/admin/preferences.pl?tab=admin">Quản trị</a>
            </li>
        [% END %]

        [% IF ( authorities ) %]
            <li class="active">
                <a title="Authority control" href="/cgi-bin/koha/admin/preferences.pl?tab=authorities">Tham chiếu thẩm quyền</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Authority control" href="/cgi-bin/koha/admin/preferences.pl?tab=authorities">Tham chiếu thẩm quyền</a>
            </li>
        [% END %]

        [% IF ( cataloguing ) %]
            <li class="active">
                <a title="Cataloging" href="/cgi-bin/koha/admin/preferences.pl?tab=cataloguing">Biên mục</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Cataloging" href="/cgi-bin/koha/admin/preferences.pl?tab=cataloguing">Biên mục</a>
            </li>
        [% END %]

        [% IF ( circulation ) %]
            <li class="active">
                <a title="Circulation" href="/cgi-bin/koha/admin/preferences.pl?tab=circulation">Mượn trả</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Circulation" href="/cgi-bin/koha/admin/preferences.pl?tab=circulation">Mượn trả</a>
            </li>
        [% END %]

        [% IF ( enhanced_content ) %]
            <li class="active">
                <a title="Enhanced content settings" href="/cgi-bin/koha/admin/preferences.pl?tab=enhanced_content">Nội dung bổ sung</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Enhanced content settings" href="/cgi-bin/koha/admin/preferences.pl?tab=enhanced_content">Nội dung bổ sung</a>
            </li>
        [% END %]

        [% IF ( erm ) %]
            <li class="active">
                <a title="E-resource management" href="/cgi-bin/koha/admin/preferences.pl?tab=erm">Quản lý tài nguyên điện tử</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="E-resource management" href="/cgi-bin/koha/admin/preferences.pl?tab=erm">Quản lý tài nguyên điện tử</a>
            </li>
        [% END %]

        [% IF ( i18n_l10n ) %]
            <li class="active">
                <a title="Internationalization and localization" href="/cgi-bin/koha/admin/preferences.pl?tab=i18n_l10n">I18N/L10N</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Internationalization and localization" href="/cgi-bin/koha/admin/preferences.pl?tab=i18n_l10n">I18N/L10N</a>
            </li>
        [% END %]

        [% IF ( interlibrary_loans ) %]
            <li class="active">
                <a title="Interlibrary loans" href="/cgi-bin/koha/admin/preferences.pl?tab=interlibrary_loans">Mượn liên thư viện</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Interlibrary loans" href="/cgi-bin/koha/admin/preferences.pl?tab=interlibrary_loans">Mượn liên thư viện</a>
            </li>
        [% END %]

        [% IF ( local_use ) %]
            <li class="active">
                <a href="/cgi-bin/koha/admin/systempreferences.pl">Sử dụng nội bộ</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a href="/cgi-bin/koha/admin/systempreferences.pl">Sử dụng nội bộ</a>
            </li>
        [% END %]

        [% IF ( logs ) %]
            <li class="active">
                <a title="Transaction logs" href="/cgi-bin/koha/admin/preferences.pl?tab=logs">Nhật ký</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Transaction logs" href="/cgi-bin/koha/admin/preferences.pl?tab=logs">Nhật ký</a>
            </li>
        [% END %]

        [% IF ( opac ) %]
            <li class="active">
                <a title="Online Public Access Catalog" href="/cgi-bin/koha/admin/preferences.pl?tab=opac">OPAC</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Online Public Access Catalog" href="/cgi-bin/koha/admin/preferences.pl?tab=opac">OPAC</a>
            </li>
        [% END %]

        [% IF ( patrons ) %]
            <li class="active">
                <a title="Patrons" href="/cgi-bin/koha/admin/preferences.pl?tab=patrons">Bạn đọc</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Patrons" href="/cgi-bin/koha/admin/preferences.pl?tab=patrons">Bạn đọc</a>
            </li>
        [% END %]

        [% IF ( preservation ) %]
            <li class="active">
                <a title="Preservation" href="/cgi-bin/koha/admin/preferences.pl?tab=preservation">Bảo tồn</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Preservation" href="/cgi-bin/koha/admin/preferences.pl?tab=preservation">Bảo tồn</a>
            </li>
        [% END %]

        [% IF ( reports ) %]
            <li class="active">
                <a title="Reports" href="/cgi-bin/koha/admin/preferences.pl?tab=reports">Báo cáo</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Reports" href="/cgi-bin/koha/admin/preferences.pl?tab=reports">Báo cáo</a>
            </li>
        [% END %]

        [% IF ( searching ) %]
            <li class="active">
                <a title="Searching" href="/cgi-bin/koha/admin/preferences.pl?tab=searching">Tìm kiếm</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Searching" href="/cgi-bin/koha/admin/preferences.pl?tab=searching">Tìm kiếm</a>
            </li>
        [% END %]

        [% IF ( serials ) %]
            <li class="active">
                <a title="Serials" href="/cgi-bin/koha/admin/preferences.pl?tab=serials">Báo tạp chí</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Serials" href="/cgi-bin/koha/admin/preferences.pl?tab=serials">Báo tạp chí</a>
            </li>
        [% END %]

        [% IF ( staff_interface ) %]
            <li class="active">
                <a title="Staff interface" href="/cgi-bin/koha/admin/preferences.pl?tab=staff_interface">Giao diện thủ thư</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Staff interface" href="/cgi-bin/koha/admin/preferences.pl?tab=staff_interface">Giao diện thủ thư</a>
            </li>
        [% END %]

        [% IF ( tools ) %]
            <li class="active">
                <a title="Tools" href="/cgi-bin/koha/admin/preferences.pl?tab=tools">Công cụ</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Tools" href="/cgi-bin/koha/admin/preferences.pl?tab=tools">Công cụ</a>
            </li>
        [% END %]

        [% IF ( web_services ) %]
            <li class="active">
                <a title="Web services" href="/cgi-bin/koha/admin/preferences.pl?tab=web_services">Dịch vụ web</a>
                [% PROCESS subtabs %]
            </li>
        [% ELSE %]
            <li>
                <a title="Web services" href="/cgi-bin/koha/admin/preferences.pl?tab=web_services">Dịch vụ web</a>
            </li>
        [% END %]
    </ul>
</div>
<!-- /.sidebar_menu -->

[% BLOCK subtabs %]
    [% UNLESS ( searchfield ) %]
        [% FOREACH TAB IN TABS %]
            <ul>
                [% FOREACH LINE IN TAB.LINES %]
                    [% IF ( LINE.is_group_title ) %]
                        <li><a class="pref_sublink" href="#[% TAB.tab_id | html %]_[% LINE.title | $HtmlId %]">[% LINE.title | html %]</a></li>
                    [% END %]
                [% END %]
            </ul>
        [% END %]
    [% END %]
[% END %]
