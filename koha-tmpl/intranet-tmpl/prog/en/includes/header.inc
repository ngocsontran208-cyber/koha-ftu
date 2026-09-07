[% USE raw %]
[% USE Branches %]
[% USE Desks %]
[% USE Registers %]
[% USE Koha %]
[% PROCESS 'i18n.inc' %]
[% IF Koha.Preference( 'CookieConsent' ) %]
    [% USE JSConsents %]
[% END %]
[% IF ( loggedinusername ) %]
<!-- ══ FTU Unified Header – Global ══ -->
<div id="ftu-header-unified">
    <div id="ftu-hd-brand">
        <a href="/cgi-bin/koha/mainpage.pl" id="ftu-hd-logo-link">
            <img src="/intranet-tmpl/prog/img/ftu-logo.png" alt="FTU" id="ftu-hd-logo" />
        </a>
        <div id="ftu-hd-titles">
            <span id="ftu-hd-title">Hệ thống Quản lý Thư viện</span>
            <span id="ftu-hd-sub">Phân hiệu Trường Đại học Ngoại thương</span>
        </div>
    </div>

    <nav id="ftu-hd-nav" aria-label="Điều hướng chính">
        [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
        <a class="ftu-nav-link" href="/cgi-bin/koha/circ/circulation-home.pl">
            <i class="fa fa-exchange"></i> Lưu thông
        </a>
        [% END %]
        [% IF CAN_user_borrowers_edit_borrowers || CAN_user_borrowers_list_borrowers %]
        <a class="ftu-nav-link" href="/cgi-bin/koha/members/members-home.pl">
            <i class="fa fa-id-card"></i> Bạn đọc
        </a>
        [% END %]
        [% IF ( CAN_user_catalogue ) %]
        <a class="ftu-nav-link" href="/cgi-bin/koha/catalogue/search.pl">
            <i class="fa fa-search"></i> Tìm kiếm
        </a>
        [% END %]
        [% IF ( CAN_user_editcatalogue_edit_catalogue || CAN_user_editcatalogue_edit_items || can_see_cataloguing_module ) %]
        <a class="ftu-nav-link" href="/cgi-bin/koha/cataloguing/cataloging-home.pl">
            <i class="fa fa-tag"></i> Biên mục
        </a>
        [% END %]
        [% IF ( CAN_user_reports ) %]
        <a class="ftu-nav-link" href="/cgi-bin/koha/reports/reports-home.pl">
            <i class="fa fa-pie-chart"></i> Báo cáo
        </a>
        [% END %]
        <div class="ftu-nav-dropdown" id="ftu-more-wrap">
            <button class="ftu-nav-link ftu-nav-more" id="ftu-more-btn" type="button">
                <i class="fa fa-bars"></i> Thêm <i class="fa fa-caret-down ftu-caret"></i>
            </button>
            <div class="ftu-dropdown-menu" id="ftu-more-menu">
                [% IF ( CAN_user_acquisition ) %]
                <a href="/cgi-bin/koha/acqui/acqui-home.pl"><i class="fa fa-shopping-cart"></i> Bổ sung</a>
                [% END %]
                [% IF ( CAN_user_serials ) %]
                <a href="/cgi-bin/koha/serials/serials-home.pl"><i class="fa fa-newspaper-o"></i> Báo – Tạp chí</a>
                [% END %]
                [% IF ( CAN_user_lists ) %]
                <a href="/cgi-bin/koha/virtualshelves/shelves.pl"><i class="fa fa-list-alt"></i> Danh sách</a>
                [% END %]
                <a href="/cgi-bin/koha/authorities/authorities-home.pl"><i class="fa fa-link"></i> Từ điển</a>
                [% IF ( CAN_user_tools || CAN_user_clubs ) %]
                <a href="/cgi-bin/koha/tools/tools-home.pl"><i class="fa fa-wrench"></i> Công cụ</a>
                [% END %]
                [% IF ( CAN_user_parameters || CAN_user_plugins_admin ) %]
                <a href="/cgi-bin/koha/admin/admin-home.pl"><i class="fa fa-gears"></i> Quản trị</a>
                [% END %]
                [% IF Koha.Preference('ILLModule') && CAN_user_ill %]
                <a href="/cgi-bin/koha/ill/ill.pl"><i class="fa fa-exchange"></i> Mượn liên thư viện</a>
                [% END %]
                <hr class="ftu-menu-divider" />
                <a href="/cgi-bin/koha/about.pl"><i class="fa fa-info-circle"></i> Giới thiệu Koha</a>
            </div>
        </div>
    </nav>

    <div id="ftu-hd-right">
        <div id="ftu-hd-clock">
            <span id="ftu-hd-date"></span>
            <span id="ftu-hd-status"><span class="ftu-live-dot"></span> Trực tuyến</span>
        </div>
        <div class="ftu-nav-dropdown" id="ftu-user-wrap">
            <button class="ftu-user-btn" id="ftu-user-btn" type="button">
                <span class="ftu-user-avatar"><i class="fa fa-user"></i></span>
                <span class="ftu-user-name">[% logged_in_user.userid | html %]</span>
                <i class="fa fa-caret-down ftu-caret"></i>
            </button>
            <div class="ftu-dropdown-menu ftu-dropdown-right" id="ftu-user-menu">
                <div class="ftu-user-info">
                    <strong>[% logged_in_user.firstname | html %] [% logged_in_user.surname | html %]</strong>
                    <small>[% Branches.GetLoggedInBranchname | html %]</small>
                </div>
                <hr class="ftu-menu-divider" />
                [% IF loggedinusernumber %]
                <a href="/cgi-bin/koha/members/moremember.pl?borrowernumber=[% loggedinusernumber | html %]">
                    <i class="fa fa-user-circle"></i> Tài khoản của tôi
                </a>
                [% END %]
                <a href="/cgi-bin/koha/circ/set-library.pl">
                    <i class="fa fa-building"></i> Đổi thư viện
                </a>
                [% IF EnableSearchHistory %]
                <a href="/cgi-bin/koha/catalogue/search-history.pl">
                    <i class="fa fa-history"></i> Lịch sử tìm kiếm
                </a>
                [% END %]
                <hr class="ftu-menu-divider" />
                <a href="/cgi-bin/koha/mainpage.pl?logout.x=1" class="ftu-logout">
                    <i class="fa fa-sign-out"></i> Đăng xuất
                </a>
            </div>
        </div>
    </div>
</div>
<script>
$(document).ready(function() {
    function updateClock() {
        var now = new Date();
        var t = now.toLocaleTimeString('vi-VN', {hour:'2-digit', minute:'2-digit'});
        var d = now.toLocaleDateString('vi-VN', {weekday:'short', day:'numeric', month:'long', year:'numeric'});
        var el = document.getElementById('ftu-hd-date');
        if (el) el.textContent = t + ' \u2013 ' + d;
    }
    updateClock();
    setInterval(updateClock, 30000);

    $('#ftu-more-btn').on('click', function(e) {
        e.preventDefault();
        e.stopPropagation();
        $('#ftu-user-menu').removeClass('open');
        $('#ftu-more-menu').toggleClass('open');
    });

    $('#ftu-user-btn').on('click', function(e) {
        e.preventDefault();
        e.stopPropagation();
        $('#ftu-more-menu').removeClass('open');
        $('#ftu-user-menu').toggleClass('open');
    });

    $(document).on('click', function() {
        $('.ftu-dropdown-menu').removeClass('open');
    });
});
</script>
[% END %]
<nav class="navbar navbar-expand navbar-dark bg-dark" aria-label="Main">
    <div class="container-fluid">
        <a id="logo" class="navbar-brand" href="/cgi-bin/koha/mainpage.pl"><img src="[% interface | html %]/[% theme | html %]/img/picto-koha.svg" alt="Koha" /></a>

        <div class="collapse navbar-collapse" id="header">
            <ul id="toplevelmenu" class="navbar-nav me-auto">
                [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
                    <li class="nav-item"
                        ><a class="nav-link" href="/cgi-bin/koha/circ/circulation-home.pl"
                            ><span class="nav-link-icon"><i class="fa fa-fw fa-exchange" title="Circulation"></i></span> <span class="nav-link-text">Circulation</span></a
                        ></li
                    >
                [% END %]
                [% IF CAN_user_borrowers_edit_borrowers || CAN_user_borrowers_list_borrowers %]
                    <li class="nav-item"
                        ><a class="nav-link" href="/cgi-bin/koha/members/members-home.pl"
                            ><span class="nav-link-icon"><i class="fa fa-fw fa-id-card" title="Patrons"></i></span> <span class="nav-link-text">Patrons</span></a
                        ></li
                    >
                [% END %]
                <li class="nav-item" id="catalog-search-link">
                    <a class="nav-link" href="/cgi-bin/koha/catalogue/search.pl"
                        ><span class="nav-link-icon"><i class="fa fa-fw fa-search" title="Search"></i></span> <span class="nav-link-text">Search</span></a
                    >
                </li>
                [% IF ( CAN_user_catalogue ) %]
                    <li class="nav-item dropdown" id="catalog-search-dropdown">
                        <a href="/cgi-bin/koha/catalogue/search.pl" class="nav-link dropdown-toggle" role="button" data-bs-toggle="dropdown" aria-expanded="false"></a>
                        <ul class="dropdown-menu dropdown-menu-dark dropdown-menu-end">
                            <li><a class="dropdown-item" href="/cgi-bin/koha/catalogue/search.pl">Advanced search</a></li>
                            <li><a class="dropdown-item" href="/cgi-bin/koha/catalogue/itemsearch.pl">Item search</a></li>
                        </ul>
                    </li>
                [% END %]
                [% Koha.Preference('IntranetNav') | $raw %]
                <li class="nav-item dropdown">
                    <a href="/cgi-bin/koha/mainpage.pl" class="nav-link dropdown-toggle" role="button" data-bs-toggle="dropdown" aria-expanded="false"
                        ><span class="nav-link-icon"><i class="fa fa-fw fa-bars" title="[% tp('More menu options', 'More') | html %]"></i></span> <span class="nav-link-text">[% tp("More menu options", "More") | html %]</span></a
                    >
                    <ul class="dropdown-menu dropdown-menu-dark dropdown-menu-end">
                        <li><a class="dropdown-item" href="/cgi-bin/koha/virtualshelves/shelves.pl">Lists</a></li>
                        [% IF ( CAN_user_editcatalogue_edit_catalogue || CAN_user_editcatalogue_edit_items || can_see_cataloguing_module  ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/cataloguing/cataloging-home.pl">Cataloging</a></li>
                        [% END %]
                        [% IF ( CAN_user_acquisition ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/acqui/acqui-home.pl">Acquisitions</a></li>
                        [% END %]
                        <li><a class="dropdown-item" href="/cgi-bin/koha/authorities/authorities-home.pl">Authorities</a></li>
                        [% IF Koha.Preference('ILLModule') && CAN_user_ill %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/ill/ill.pl">Interlibrary loans</a></li>
                        [% END %]
                        [% IF ( CAN_user_serials ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/serials/serials-home.pl">Serials</a></li>
                        [% END %]
                        [% IF Koha.Preference('ERMModule') && CAN_user_erm %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/erm/erm.pl">E-resource management</a></li>
                        [% END %]
                        [% IF ( Koha.Preference('UseCourseReserves') ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/course_reserves/course-reserves.pl">Course reserves</a></li>
                        [% END %]
                        [% IF Koha.Preference('PreservationModule') && CAN_user_preservation %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/preservation/home.pl">Preservation</a></li>
                        [% END %]
                        [% IF ( CAN_user_reports ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/reports/reports-home.pl">Reports</a></li>
                        [% END %]
                        [% IF ( CAN_user_suggestions_suggestions_manage ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/suggestion/suggestion.pl">Suggestions</a></li>
                        [% END %]
                        [% IF ( CAN_user_tools || CAN_user_clubs ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/tools/tools-home.pl">Tools</a></li>
                        [% END %]
                        [% IF ( Koha.Preference('EnablePointOfSale') && Koha.Preference('UseCashRegisters') && CAN_user_cash_management_takepayment ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/pos/pay.pl">Point of sale</a></li>
                        [% END %]
                        [% IF ( CAN_user_parameters ) %]
                            <li><a class="dropdown-item" href="/cgi-bin/koha/admin/admin-home.pl">Administration</a></li>
                        [% END %]
                        <li><a class="dropdown-item" href="/cgi-bin/koha/about.pl">About Koha</a></li>
                    </ul>
                </li>
                [% IF ( Koha.Preference('intranetbookbag') ) %]
                    <li class="nav-item">
                        <a class="nav-link" href="#" id="cartmenulink"><i class="fa fa-shopping-cart" title="Cart"></i><span id="basketcount"></span></a>
                    </li>
                [% END %]
            </ul>

            <ul id="user-menu" class="nav navbar-nav">
                [% IF ( loggedinusername ) %]
                    <li class="nav-item dropdown" id="logged-in-dropdown">
                        <a id="logged-in-menu" href="/cgi-bin/koha/mainpage.pl" class="nav-link dropdown-toggle" role="button" data-bs-toggle="dropdown" aria-expanded="false">
                            <span id="logged-in-info-brief">
                                <i class="fa fa-user"></i>
                            </span>
                            <span id="logged-in-info-full">
                                [% SET is_superlibrarian = CAN_user_superlibrarian ? 'is_superlibrarian' : '' %]
                                <span class="loggedinusername [% is_superlibrarian | html %]" data-loggedinusername="[% logged_in_user.userid | html %]" data-is-superlibrarian="[% is_superlibrarian | html %]"
                                    >[% logged_in_user.userid | html %]</span
                                >
                                <span class="loggedincategorycode content_hidden" data-loggedincategorycode="[% logged_in_user.categorycode | html %]">[% logged_in_user.categorycode | html %]</span>
                                [% IF ( StaffLoginRestrictLibraryByIP ) %]
                                    <brand> [% Branches.GetLoggedInBranchname | html %] </brand>
                                [% ELSE %]
                                    <strong>
                                        <span class="logged-in-branch-name" data-logged-in-branch-name="[% Branches.GetLoggedInBranchname | html %]">[% Branches.GetLoggedInBranchname | html %]</span>
                                        <span class="logged-in-branch-code content_hidden" data-logged-in-branch-code="[% Branches.GetLoggedInBranchcode | html %]">[% Branches.GetLoggedInBranchcode | html %]</span>
                                    </strong>
                                [% END %]
                                [% IF Koha.Preference('UseCirculationDesks') && Desks.ListForLibrary.count %]
                                    <span class="separator">|</span>
                                    <strong>
                                        [% IF ( Desks.GetLoggedInDeskName == '' ) %]
                                            <span class="logged-in-desk-name">NO DESK SET</span>
                                        [% ELSE %]
                                            <span class="logged-in-desk-name" data-logged-in-desk-name="[% Desks.GetLoggedInDeskName | html %]">[% Desks.GetLoggedInDeskName | html %]</span>
                                            <span class="logged-in-desk-id content_hidden" data-logged-in-desk-id="[% Desks.GetLoggedInDeskId | html %]">[% Desks.GetLoggedInDeskId | html %]</span>
                                        [% END %]
                                    </strong>
                                [% END %]
                                [% IF Koha.Preference('UseCashRegisters') && !(Registers.session_register_name == '') %]
                                    <span class="separator">|</span>
                                    <strong>
                                        <span class="logged-in-register-name" data-logged-in-register-name="[% Registers.session_register_name | html %]">[% Registers.session_register_name | html %]</span>
                                        <span class="logged-in-register-id content_hidden" data-logged-in-register-id="[% Registers.session_register_id | html %]">[% Registers.session_register_id | html %]</span>
                                    </strong>
                                [% END %]
                            </span>
                            <b class="caret"></b>
                        </a>

                        <ul class="dropdown-menu dropdown-menu-dark dropdown-menu-end" role="menu" aria-labelledby="logged-in-menu">
                            <li class="loggedin-menu-label">
                                Logged in as:<br />
                                <span class="loggedinusername">[% logged_in_user.userid | html %]</span>
                            </li>
                            <li class="loggedin-menu-label">
                                [% IF ( StaffLoginRestrictLibraryByIP ) %]
                                    <brand> [% Branches.GetLoggedInBranchname | html %] </brand>
                                [% ELSE %]
                                    Location: <br />
                                    <span class="logged-in-branch-name">[% Branches.GetLoggedInBranchname | html %]</span>
                                    <span class="logged-in-branch-code content_hidden">[% Branches.GetLoggedInBranchcode | html %]</span>
                                [% END %]
                            </li>

                            [% IF Koha.Preference('UseCirculationDesks') && Desks.ListForLibrary.count %]
                                <li class="loggedin-menu-label">
                                    Desk: <br />
                                    [% IF ( Desks.GetLoggedInDeskName == '' ) %]
                                        <span class="logged-in-desk-name">NO DESK SET</span>
                                    [% ELSE %]
                                        <span class="logged-in-desk-name">[% Desks.GetLoggedInDeskName | html %]</span>
                                        <span class="logged-in-desk-id content_hidden">[% Desks.GetLoggedInDeskId | html %]</span>
                                    [% END %]
                                </li>
                            [% END %]

                            [% IF Koha.Preference('UseCashRegisters') && !(Registers.session_register_name == '') %]
                                <li class="loggedin-menu-label">
                                    Register: <br />
                                    <span class="logged-in-register-name">[% Registers.session_register_name | html %]</span>
                                    <span class="logged-in-register-id content_hidden">[% Registers.session_register_id | html %]</span>
                                </li>
                            [% END %]

                            [% IF ( CAN_user_superlibrarian || CAN_user_loggedinlibrary || Koha.Preference('UseCirculationDesks') || Koha.Preference('UseCashRegisters') ) %]
                                <li><hr class="dropdown-divider" /></li>
                                <li>
                                    <div id="set_library_controls">
                                        <div>
                                            <a class="dropdown-item" href="/cgi-bin/koha/circ/set-library.pl">
                                                [% IF ( CAN_user_superlibrarian || CAN_user_loggedinlibrary ) %]
                                                    [% IF ( Koha.Preference('UseCirculationDesks') && Koha.Preference('UseCashRegisters') ) %]
                                                        [% t("Set library, desk, and register") | html %]
                                                    [% ELSIF ( Koha.Preference('UseCirculationDesks') ) %]
                                                        [% t("Set library and desk") | html %]
                                                    [% ELSIF ( Koha.Preference('UseCashRegisters') ) %]
                                                        [% t("Set library and cash register") | html %]
                                                    [% ELSE %]
                                                        [% t("Set library") | html %]
                                                    [% END %]
                                                [% ELSIF ( Koha.Preference('UseCirculationDesks') && Koha.Preference('UseCashRegisters') ) %]
                                                    [% t("Set desk and cash register") | html %]
                                                [% ELSIF ( Koha.Preference('UseCashRegisters') ) %]
                                                    [% t("Set cash register") | html %]
                                                [% ELSIF ( Koha.Preference('UseCirculationDesks') ) %]
                                                    [% t("Set desk") | html %]
                                                [% END %]
                                            </a>
                                        </div>
                                        [% IF ( CAN_user_superlibrarian || CAN_user_loggedinlibrary || Koha.Preference('UseCirculationDesks') || Koha.Preference('UseCashRegisters') ) %]
                                            <div>
                                                <a id="branch_select_cog" class="dropdown-item" href="#" role="button" aria-label="Toggle panel for login settings" aria-expanded="false">
                                                    <i class="fa fa-cog" aria-hidden="true"></i>
                                                </a>
                                            </div>
                                        [% END %]
                                    </div>
                                </li>

                                <li id="setlibrary_panel" style="display:none"></li>
                            [% ELSIF Koha.Preference('UseCirculationDesks') && Koha.Preference('UseCashRegisters') %]
                                <li><hr class="dropdown-divider" /></li>
                                <li>
                                    <a class="dropdown-item" href="/cgi-bin/koha/circ/set-library.pl">Set desk and cash register</a>
                                </li>
                            [% ELSIF Koha.Preference('UseCirculationDesks') %]
                                <li><hr class="dropdown-divider" /></li>
                                <li>
                                    <a class="dropdown-item" href="/cgi-bin/koha/circ/set-library.pl">Set desk</a>
                                </li>
                            [% ELSIF Koha.Preference('UseCashRegisters') %]
                                <li><hr class="dropdown-divider" /></li>
                                <li>
                                    <a class="dropdown-item" href="/cgi-bin/koha/circ/set-library.pl">Set cash register</a>
                                </li>
                            [% END %]
                            [% IF EnableSearchHistory %]
                                <li>
                                    <a class="dropdown-item" href="/cgi-bin/koha/catalogue/search-history.pl">Search history</a>
                                </li>
                            [% END %]

                            [% IF loggedinusernumber %]
                                <li class="nav-item toplinks-myaccount">
                                    <a class="dropdown-item" href="/cgi-bin/koha/members/moremember.pl?borrowernumber=[% loggedinusernumber | html %]">My account</a>
                                </li>
                                <li class="nav-item toplinks-mycheckouts">
                                    <a class="dropdown-item" href="/cgi-bin/koha/circ/circulation.pl?borrowernumber=[% loggedinusernumber | html %]">My checkouts</a>
                                </li>
                            [% END %]

                            [% IF Koha.Preference( 'CookieConsent' ) && JSConsents.all('staffConsent').size %]
                                <li class="nav-item toplinks-myconsents">
                                    <a id="viewCookieConsents" href="#" class="toplinks dropdown-item">My consents</a>
                                </li>
                            [% END %]
                            <li class="nav-item">
                                <a id="logout" class="toplinks dropdown-item" href="/cgi-bin/koha/mainpage.pl?logout.x=1">Log out</a>
                            </li>
                        </ul>
                    </li>
                    [% IF Koha.debug_flag %]
                        <li class="nav-item dropdown" id="debug-controls-dropdown">
                            <a id="debug-controls-menu" href="#" class="nav-link dropdown-toggle" role="button" data-bs-toggle="dropdown" aria-expanded="false" title="Debug controls">
                                <i id="debug-icon" class="fa fa-bug"></i>
                            </a>
                            <ul class="dropdown-menu dropdown-menu-dark dropdown-menu-end" role="menu" aria-labelledby="debug-controls-menu">
                                <li>
                                    <a id="toggleUserCSS" class="dropdown-item" href="#"> <i class="fa fa-fw fa-brands fa-css3"></i> <span class="toggle-text">Toggle User CSS</span> </a>
                                </li>
                                <li>
                                    <a id="toggleUserJS" class="dropdown-item" href="#"> <i class="fa fa-fw fa-brands fa-square-js"></i> <span class="toggle-text">Toggle User JS</span> </a>
                                </li>
                                <li>
                                    <a id="toggleStylesheets" class="dropdown-item" href="#"> <i class="fa fa-fw fa-file-code"></i> <span class="toggle-text">Toggle Custom Stylesheets</span> </a>
                                </li>
                            </ul>
                        </li>
                    [% END %]
                    [% INCLUDE 'langmenu-staff-top.inc' %]
                [% ELSE %]
                    <li class="nav-item loggedout">
                        <a href="/cgi-bin/koha/mainpage.pl" id="login">Log in</a>
                    </li>
                [% END %]
            </ul>
        </div>
    </div>

    [% IF ( Koha.Preference('intranetbookbag') ) %]<div id="cartDetails">Your cart is empty.</div>[% END %]
</nav>

[% content | $raw %]
