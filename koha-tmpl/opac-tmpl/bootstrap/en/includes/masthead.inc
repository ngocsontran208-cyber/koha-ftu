[% USE raw %]
[% USE Koha %]
[% USE Branches %]
[% USE Categories %]
[% USE AuthClient %]
[% USE AdditionalContents %]
[% PROCESS 'i18n.inc' %]
[% PROCESS 'ftu-brand-config.inc' %]
[% PROCESS 'html_helpers.inc' %]
[% IF Koha.Preference( 'CookieConsent' ) %]
    [% USE JSConsents %]
[% END %]
[% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
[% SET OpacHeader = AdditionalContents.get( location => "opacheader", lang => lang, library => logged_in_user.branchcode || default_branch, blocktitle => 0 ) %]
[% SET OpacCustomSearch = AdditionalContents.get( location => "OpacCustomSearch", lang => lang, library => logged_in_user.branchcode || default_branch, blocktitle => 0 ) %]
[% SET OpacLoginInstructions = AdditionalContents.get( location => "OpacLoginInstructions", lang => lang, library => branchcode || default_branch ) %]
[% SET OpacMoreSearches = AdditionalContents.get( location => "OpacMoreSearches", lang => lang, library => branchcode || default_branch ) %]
[% SET CookieConsentBar = AdditionalContents.get( location => "CookieConsentBar", lang => lang, library => branchcode || default_branch ) %]
[% SET CookieConsentPopup = AdditionalContents.get( location => "CookieConsentPopup", lang => lang, library => branchcode || default_branch ) %]
[% SET AllPublicBranches = Branches.all(  search_params => { public => 1 }, selected => opac_name, unfiltered => 1 ) %]

<button id="scrolltocontent">Skip to main content</button>
<!-- prettier-ignore-start -->
<!-- closed in opac-bottom.inc -->
<div id="wrapper">
<!-- prettier-ignore-end -->
<header id="header-region" class="noprint">
    <nav class="navbar navbar-expand">
        <div id="logo">
            <a class="navbar-brand" href="/opac/" title="[% FTU_BRAND.library_name %]">
                <img class="ftu-logo-img" src="[% FTU_BRAND.logo_url %]" alt="[% FTU_BRAND.logo_alt %]" />
                <span class="ftu-brand-title-wrap">
                    <span class="ftu-brand-main-title">
                        <span class="brand-title-desktop">[% FTU_BRAND.library_name %]</span>
                        <span class="brand-title-mobile">THƯ VIỆN FTU HCMC</span>
                    </span>
                    <span class="ftu-brand-sub-title">[% FTU_BRAND.library_sub_title %]</span>
                </span>
            </a>
        </div>
        <!-- Right Header Actions Container -->
        <div class="ftu-header-actions-wrap">
        [% IF ( OpacPublic ) %]
            [% IF ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
                <div id="cartDetails" class="cart-message">Your cart is empty.</div>
            [% END %]
            <ul id="cart-list-nav" class="navbar-nav">
                [% IF ( Koha.Preference( 'opacbookbag' ) == 1 ) %]
                    <li class="nav-item js-show">
                        <a href="#" class="nav-link" title="Collect items you are interested in" id="cartmenulink" role="button" aria-label="Cart">
                            <i id="carticon" class="fa fa-shopping-cart fa-fw fa-icon-black" aria-hidden="true"></i> <span class="cartlabel">Cart</span> <span id="basketcount"></span>
                        </a>
                    </li>
                [% END %]
                <li role="presentation" class="divider-vertical"></li>
                [% IF ( Koha.Preference( 'virtualshelves' ) == 1 ) %]
                    [% IF Koha.Preference( 'opacuserlogin' ) == 1 || some_public_shelves.count > 0 %]
                        <li class="nav-item dropdown">
                            <a
                                href="/cgi-bin/koha/opac-shelves.pl"
                                title="Show lists"
                                class="nav-link dropdown-toggle"
                                id="listsmenu"
                                data-bs-toggle="dropdown"
                                role="button"
                                aria-label="Show dropdown with detailed list information"
                                aria-haspopup="true"
                                aria-expanded="false"
                                ><i class="fa fa-list fa-fw fa-icon-black" aria-hidden="true"></i> <span class="listslabel">Lists</span>
                            </a>
                            <div aria-labelledby="listsmenu" role="menu" class="dropdown-menu">
                                [% IF some_public_shelves.count %]
                                    <a class="dropdown-item" href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;public=1" tabindex="0" role="menuitem"><strong>Public lists</strong></a>
                                    [% SET number_of_public_shelves = 0 %]
                                    [% FOREACH s IN some_public_shelves %]
                                        <a class="dropdown-item" href="/cgi-bin/koha/opac-shelves.pl?op=view&amp;shelfnumber=[% s.shelfnumber | uri %]&amp;sortfield=[% s.sortfield | uri %]" tabindex="0" role="menuitem"
                                            >[% s.shelfname | html %]</a
                                        >
                                        [% SET number_of_public_shelves = number_of_public_shelves + 1 %]
                                        [% IF number_of_public_shelves >= 10 %][% LAST %][% END %]
                                    [% END %]
                                    [% IF some_public_shelves.count > 10 %]
                                        <a class="dropdown-item listmenulink" href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;public=1" tabindex="0" role="menuitem">View all</a>
                                    [% END %]
                                [% END %]
                                [% IF Koha.Preference( 'opacuserlogin' ) == 1 && some_public_shelves.count > 0 %]
                                    <div class="dropdown-divider"></div>
                                [% END %]
                                [% IF Koha.Preference( 'opacuserlogin' ) == 1 %]
                                    <a class="dropdown-item" href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;public=0" tabindex="0" role="menuitem"><strong>Your lists</strong></a>
                                    [% IF loggedinusername %]
                                        [% IF some_private_shelves.count %]
                                            [% SET number_of_private_shelves = 0 %]
                                            [% FOREACH s IN some_private_shelves %]
                                                <a class="dropdown-item" href="/cgi-bin/koha/opac-shelves.pl?op=view&amp;shelfnumber=[% s.shelfnumber | uri %]&amp;sortfield=[% s.sortfield | uri %]" tabindex="0" role="menuitem"
                                                    >[% s.shelfname | html %]</a
                                                >
                                                [% SET number_of_private_shelves = number_of_private_shelves + 1 %]
                                                [% IF number_of_private_shelves >= 10 %][% LAST %][% END %]
                                            [% END %]
                                            [% IF some_private_shelves.count > 10 %]
                                                <a class="dropdown-item listmenulink" href="/cgi-bin/koha/opac-shelves.pl?op=list&amp;public=0" tabindex="0" role="menuitem">View all</a>
                                            [% END %]
                                        [% ELSE %]
                                            <a class="dropdown-item disabled" aria-disabled="true" href="#" tabindex="0" role="menuitem">No private lists</a>
                                        [% END %]
                                        <a class="dropdown-item listmenulink" href="/cgi-bin/koha/opac-shelves.pl?op=add_form" tabindex="0" role="menuitem">New list</a>
                                    [% ELSE %]
                                        <a class="dropdown-item" href="/cgi-bin/koha/opac-shelves.pl?op=add_form" tabindex="0" role="menuitem">Log in to create your own lists</a>
                                    [% END # / IF loggedinusername %]
                                [% END # / IF opacuserlogin %]
                            </div>
                            <!-- / .dropdown-menu -->
                        </li>
                        <!-- / .nav-item.dropdown -->
                    [% END # / IF opacuserlogin || some_public_shelves < 1 %]
                [% END # / IF virtualshelves %]
                <li role="presentation" class="divider-vertical"></li>
                <li class="nav-item" id="csdl-nav-item">
                    <a href="/cgi-bin/koha/opac-databases.pl" class="nav-link" title="Databases" id="csdlmenulink" role="button">
                        <i id="csdlicon" class="fa fa-database fa-fw fa-icon-black" aria-hidden="true"></i> <span class="csdllabel">Databases</span>
                    </a>
                </li>
                <li role="presentation" class="divider-vertical"></li>
                <li class="nav-item" id="bst-nav-item">
                    <a href="/cgi-bin/koha/opac-collections.pl" class="nav-link" title="Collections" id="bstmenulink" role="button">
                        <i id="bsticon" class="fa fa-cubes fa-fw fa-icon-black" aria-hidden="true"></i> <span class="bstlabel">Collections</span>
                    </a>
                </li>
                [% IF Koha.Preference( 'OpacTrustedCheckout' ) %]
                    <li class="nav-item">
                        <a href="#" class="nav-link" title="Self check out" id="comenulink" role="button" data-bs-toggle="modal" data-bs-target="#checkoutModal">
                            <i id="checkout-icon" class="fa fa-barcode fa-icon-black" aria-hidden="true"></i> <span class="checkout-label">Self-checkout</span>
                        </a>
                    </li>
                [% END %]
            </ul>
            <!-- / .navbar-nav -->
        [% END # /IF OpacPublic %]
        [% IF Koha.Preference( 'opacuserlogin' ) == 1 ||  Koha.Preference( 'EnableOpacSearchHistory') || Koha.Preference( 'opaclanguagesdisplay' ) %]
            [%# Following on one line for translatability %]
            [% IF ( ( opaclanguagesdisplay ) && ( ! one_language_enabled ) && ( languages_loop ) && ( OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'top') ) %]
                [% context = "header" %]
                [% INCLUDE 'langmenu.inc' %]
            [% ELSE %]
                <!-- Fallback FTU Language Selector (đảm bảo luôn hiển thị trên thanh điều hướng) -->
                <div id="header_langmenu" class="langmenu">
                    <ul class="navbar-nav">
                        <li class="nav-item dropdown">
                            <a href="#" title="Switch languages" class="nav-link dropdown-toggle" id="langmenu_fb" data-bs-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
                                <i class="fa fa-flag fa-fw fa-icon-header" aria-hidden="true"></i> <span class="langlabel">Languages</span> <b class="caret"></b>
                            </a>
                            <div aria-labelledby="langmenu_fb" role="menu" class="dropdown-menu dropdown-menu-end">
                                <a class="dropdown-item" href="/cgi-bin/koha/opac-changelanguage.pl?language=vi-VN" tabindex="-1" role="menuitem">
                                    Tiếng Việt
                                </a>
                                <a class="dropdown-item" href="/cgi-bin/koha/opac-changelanguage.pl?language=en" tabindex="-1" role="menuitem">
                                    English <i class="fa fa-check" aria-hidden="true"></i>
                                </a>
                            </div>
                        </li>
                        <li class="divider-vertical" aria-hidden="false" role="presentation"></li>
                    </ul>
                </div>
            [% END %]
            <ul id="members" class="navbar-nav">
                <li class="nav-item dropdown dropdown-menu-end">
                    [% IF ( Koha.Preference( 'opacuserlogin' ) == 1 ) %]
                        [% IF ( loggedinusername ) %]
                            <a href="/cgi-bin/koha/opac-user.pl" class="nav-link dropdown-toggle" id="user-menu" data-bs-toggle="dropdown" role="button" aria-haspopup="true" aria-expanded="false">
                                <i class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i>
                                <span class="userlabel">Welcome, [% INCLUDE 'patron-title.inc' patron = logged_in_user no_html = 1 %]</span>
                                [% IF logged_in_user && logged_in_user.checkouts.count > 0 %]
                                    <span class="badge rounded-pill bg-danger ms-1" style="font-size: 11px; padding: 2px 6px;" title="[% logged_in_user.checkouts.count %] active loans">[% logged_in_user.checkouts.count %]</span>
                                [% END %]
                            </a>
                            <a tabindex="0" role="menuitem" class="logout js-hide" href="/opac/logout"><i class="fa fa-fw fa-sign-out" aria-hidden="true"></i> Log out</a>
                        [% ELSE %]
                            [% IF Koha.Preference('casAuthentication') %]
                                [%# CAS authentication is too complicated for modal window %]
                                <a class="nav-link login-link" href="/cgi-bin/koha/opac-user.pl" aria-label="Log in to your account"
                                    ><i class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i> <span class="userlabel">Log in to your account</span></a
                                >
                            [% ELSIF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
                                <a href="/cgi-bin/koha/svc/auth/googleopenidconnect" class="nav-link login-link loginModal-trigger" data-return="true" aria-label="Log in to your account"
                                    ><i class="fa fa-user fa-icon-black fa-fw" aria-hidden="true"></i> <span class="userlabel">Log in to your account</span></a
                                >
                            [% ELSE %]
                                <a href="/cgi-bin/koha/opac-user.pl" class="nav-link login-link loginModal-trigger" data-return="true" aria-label="Log in to your account"
                                    ><i class="fa fa-user fa-fw fa-icon-black fa-fw" aria-hidden="true"></i> <span class="userlabel">Log in to your account</span></a
                                >
                            [% END %]
                        [% END %]
                    [% END %]

                    [% IF ( Koha.Preference( 'opacuserlogin' ) == 1 && loggedinusername ) %]
                        <div aria-labelledby="user-menu" role="menu" class="dropdown-menu dropdown-menu-end">
                            <div id="loggedinuser-menu">
                                <p>
                                    <a class="login-link" href="/cgi-bin/koha/opac-user.pl"
                                        ><span
                                            class="loggedinusername"
                                            data-borrowernumber="[% logged_in_user.borrowernumber | html %]"
                                            data-branchcode="[% logged_in_user.branchcode | html %]"
                                            data-categorycode="[% logged_in_user.categorycode | html %]"
                                            data-userid="[% logged_in_user.userid || loggedinusername | html %]"
                                            >Your account</span
                                        ></a
                                    >
                                </p>
                                [% IF logged_in_user && logged_in_user.checkouts.count > 0 %]
                                <p>
                                    <a class="login-link" href="/cgi-bin/koha/opac-user.pl?tab=opac-user-checkouts">
                                        <i class="fa fa-book" aria-hidden="true"></i> Current checkouts: <strong>[% logged_in_user.checkouts.count %]</strong>
                                    </a>
                                </p>
                                [% END %]
                                [% IF Koha.Preference( 'EnableOpacSearchHistory' ) %]
                                    <p>
                                        <a tabindex="0" role="menuitem" class="login-link" href="/cgi-bin/koha/opac-search-history.pl" title="View your search history">Search history</a>
                                        <span role="presentation" class="divider-vertical"></span>
                                        <a
                                            class="clearsh submit-form-link"
                                            href="#"
                                            data-method="post"
                                            data-action="/cgi-bin/koha/opac-search-history.pl"
                                            data-op="cud-delete"
                                            data-confirmation-msg="[% t('Are you sure you want to delete your search history?') | html %]"
                                            title="Delete your search history"
                                            ><i class="fa fa-trash-can" aria-hidden="true"></i> Clear</a
                                        >
                                    </p>
                                [% END %]
                                <a tabindex="0" role="menuitem" class="logout" id="logout" href="/opac/logout">Log out</a>
                            </div>
                        </div>
                    [% END %]
                </li>
                <!-- Cookie consent button for non logged-in users -->
                [% IF !loggedinusername %]
                    <li role="presentation" style="display:none" id="cookieConsentDivider" class="divider-vertical" aria-hidden="true"></li>
                    <li style="display:none" id="cookieConsentLi" class="nav-item" aria-hidden="true">
                        <a id="cookieConsentButton" href="#" name="Your cookies" class="nav-link" title="View and amend cookies you have consented to" role="button">
                            <i class="fa fa-cookie-bite fa-fw fa-icon-black" aria-hidden="true"></i>
                            <span class="cookieconsentlabel">Your cookies</span>
                        </a>
                    </li>
                [% END %]
                [% IF OpacPublic && ( !Koha.Preference( 'opacuserlogin') || !loggedinusername ) %]
                    [% IF Koha.Preference( 'EnableOpacSearchHistory' ) %]
                        <li role="presentation" class="divider-vertical"></li>
                        <li class="nav-item search_history">
                            <a class="nav-link" href="/cgi-bin/koha/opac-search-history.pl" title="View your search history">
                                <i class="fa fa-calendar-days fa-fw fa-icon-black" aria-hidden="true"></i>
                                <span class="search_history_label">Search history</span>
                            </a>
                        </li>
                    [% END %]
                [% END %]
            </ul>
        [% END # IF opacuserlogin || EnableOpacSearchHistory || opaclanguagesdisplay %]
        </div> <!-- /.ftu-header-actions-wrap -->
    </nav>
    <!-- /navbar -->

    [% IF ( OpacHeader ) %]
        <div class="container-fluid">
            <div class="row">
                <div class="col"> [% PROCESS koha_news_block news => OpacHeader %] </div>
            </div>
        </div>
    [% END %]
</header>
<!-- / header-region -->

[% IF ( OpacPublic ) %]
    <div class="container-fluid">
        [% UNLESS ( advsearch ) %]
            <div class="row">
                <div class="col">
                    <div id="opac-main-search" class="mastheadsearch">
                        [% IF ( OpacCustomSearch ) %]
                            [% PROCESS koha_news_block news => OpacCustomSearch %]
                        [% ELSE %]
                            <form name="searchform" method="get" action="/cgi-bin/koha/opac-search.pl" id="searchform" role="search">
                                <div class="row gx-2">
                                    <div class="col-sm-auto order-2 order-sm-2">
                                        <label for="masthead_search" class="visually-hidden">Search the catalog by:</label>
                                        <select name="idx" id="masthead_search" class="form-select">
                                            [% IF ( ms_kw ) %]
                                                <option selected="selected" value="" data-placeholder="[% t("Search the catalog") | html %]">Library catalog</option>
                                            [% ELSE %]
                                                <option value="" data-placeholder="[% t("Search the catalog") | html %]">Library catalog</option>
                                            [% END # /ms_kw %]
                                            [% IF ( ms_ti ) %]
                                                <option selected="selected" value="ti" data-placeholder="[% t("Search the catalog by title") | html %]">Title</option>
                                            [% ELSE %]
                                                <option value="ti" data-placeholder="[% t("Search the catalog by title") | html %]">Title</option>
                                            [% END # /ms_ti %]
                                            [% IF ( ms_au ) %]
                                                <option selected="selected" value="au" data-placeholder="[% t("Search the catalog by author") | html %]">Author</option>
                                            [% ELSE %]
                                                <option value="au" data-placeholder="[% t("Search the catalog by author") | html %]">Author</option>
                                            [% END # /ms_au %]
                                            [% IF ( ms_su ) %]
                                                <option selected="selected" value="su" data-placeholder="[% t("Search the catalog by subject") | html %]">Subject</option>
                                            [% ELSE %]
                                                <option value="su" data-placeholder="[% t("Search the catalog by subject") | html %]">Subject</option>
                                            [% END # /ms_su %]
                                            [% IF ( ms_nb ) %]
                                                <option selected="selected" value="nb" data-placeholder="[% t("Search the catalog by ISBN") | html %]">ISBN</option>
                                            [% ELSE %]
                                                <option value="nb" data-placeholder="[% t("Search the catalog by ISBN") | html %]">ISBN</option>
                                            [% END # /ms_nb %]
                                            [% IF ( ms_ns ) %]
                                                <option selected="selected" value="ns" data-placeholder="[% t("Search the catalog by ISSN") | html %]">ISSN</option>
                                            [% ELSE %]
                                                <option value="ns" data-placeholder="[% t("Search the catalog by ISSN") | html %]">ISSN</option>
                                            [% END # /ms_ns %]
                                            [% IF ( ms_se ) %]
                                                <option selected="selected" value="se" data-placeholder="[% t("Search the catalog by series") | html %]">Series</option>
                                            [% ELSE %]
                                                <option value="se" data-placeholder="[% t("Search the catalog by series") | html %]">Series</option>
                                            [% END # /ms_se %]
                                            [% IF ( Koha.Preference('OPACNumbersPreferPhrase') ) %]
                                                [% IF ( ms_callnumcommaphr ) %]
                                                    <option selected="selected" value="callnum,phr" data-placeholder="[% t("Search the catalog by call number") | html %]">Call number</option>
                                                [% ELSE %]
                                                    <option value="callnum,phr" data-placeholder="[% t("Search the catalog by call number") | html %]">Call number</option>
                                                [% END #/ms_callnumcommaphr %]
                                            [% ELSE %]
                                                [% IF ( ms_callnum ) %]
                                                    <option selected="selected" value="callnum" data-placeholder="[% t("Search the catalog by call number") | html %]">Call number</option>
                                                [% ELSE %]
                                                    <option value="callnum" data-placeholder="[% t("Search the catalog by call number") | html %]">Call number</option>
                                                [% END # /ms_callnum %]
                                            [% END # /IF OPACNumbersPreferPhrase %]
                                        </select>
                                    </div>
                                    <!-- /.col-sm-auto -->

                                    <div class="col order-4 order-sm-3">
                                        [% IF ( !Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 && mylibraryfirst ) %]
                                            <label for="translControl1" class="visually-hidden">Search the catalog in [% Branches.GetName( mylibraryfirst ) | html %]</label>
                                            <input
                                                type="text"
                                                class="transl1 form-control form-control-filtered"
                                                id="translControl1"
                                                name="q"
                                                value="[% ms_value | html %]"
                                                data-bs-toggle="tooltip"
                                                data-bs-placement="top"
                                                title="Searching in [% Branches.GetName( mylibraryfirst ) | html %] only"
                                                placeholder="Search the catalog"
                                            /><span id="translControl"></span>
                                        [% ELSE %]
                                            <label for="translControl1" class="visually-hidden">Search the catalog</label>
                                            <input type="text" class="transl1 form-control" id="translControl1" name="q" value="[% ms_value | html %]" placeholder="Search the catalog" /><span id="translControl"></span>
                                        [% END # /ms_value %]
                                    </div>
                                    <!-- /.col -->

                                    [% IF ( Koha.Preference( 'OpacAddMastheadLibraryPulldown' ) == 1 && AllPublicBranches.size > 1 ) %]
                                        <div class="col-sm col-md-3 col-lg-2 order-3 order-sm-4">
                                            <label for="select_library" class="visually-hidden">Search the catalog in:</label>
                                            <select name="limit" id="select_library" class="form-select">
                                                <option value="">All libraries</option>

                                                [% IF LibrarySearchGroups %]
                                                    <optgroup label="Libraries">
                                                        [% FOREACH library IN AllPublicBranches %]
                                                            [% IF library.selected %]
                                                                <option selected="selected" value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
                                                            [% ELSE %]
                                                                <option value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
                                                            [% END %]
                                                        [% END %]
                                                    </optgroup>
                                                    <optgroup label="Groups">
                                                        [% FOREACH lsg IN LibrarySearchGroups %]
                                                            [% IF 'multibranchlimit-' _ lsg.id == opac_name || lsg.id == opac_name %]
                                                                <option selected="selected" value="multibranchlimit:[% lsg.id | html %]">[% lsg.title | html %]</option>
                                                            [% ELSE %]
                                                                <option value="multibranchlimit:[% lsg.id | html %]">[% lsg.title | html %]</option>
                                                            [% END # / bc.selected %]
                                                        [% END %]
                                                    </optgroup>
                                                [% ELSE %]
                                                    [% FOREACH library IN AllPublicBranches %]
                                                        [% IF library.selected %]
                                                            <option selected="selected" value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
                                                        [% ELSE %]
                                                            <option value="branch:[% library.branchcode | html %]">[% library.branchname | html %]</option>
                                                        [% END %]
                                                    [% END %]
                                                [% END %]
                                            </select>
                                            <!-- /#select_library -->
                                        </div>
                                        <!-- /.col-sm-auto -->
                                    [% ELSE %]
                                        [% IF ( opac_limit_override ) %]
                                            [% IF ( opac_search_limit ) %]
                                                [% IF ( multibranchlimit = opac_search_limit.match( 'branch:multibranchlimit-(\d+)' ) ) %]
                                                    <input name="limit" value="multibranchlimit:[% multibranchlimit.0 | html %]" type="hidden" />
                                                [% ELSE %]
                                                    <input name="limit" value="[% opac_search_limit | html %]" type="hidden" />
                                                [% END %]
                                            [% END %]
                                        [% ELSE %]
                                            [% IF ( mylibraryfirst ) %]
                                                <input name="limit" value="branch:[% mylibraryfirst | html %]" type="hidden" />
                                            [% END %]
                                        [% END # / opac_limit_override %]
                                    [% END # / OpacAddMastheadLibraryPulldown %]

                                    <div class="order-5 col-sm-auto">
                                        <button type="submit" id="searchsubmit" class="btn btn-primary" title="Search" aria-label="Search">
                                            <i class="fa fa-search" aria-hidden="true"></i>
                                        </button>
                                    </div>
                                </div>
                                <!-- /.form-row -->
                                <input type="hidden" name="weight_search" value="1" />
                            </form>
                        [% END # / ( OpacCustomSearch ) %] </div
                    ><!-- /#opac-main-search -->
                </div>
                <!-- /.col -->
            </div>
            <!-- /.row -->
        [% END # / UNLESS advsearch %]

        <div class="row">
            <details class="ftu-moresearches-details col-12">
            <summary class="ftu-moresearches-summary d-md-none">
                <span class="d-inline-flex align-items-center gap-1">
                    <i class="fa fa-sliders text-danger" aria-hidden="true"></i>
                    <strong style="color: #334155; font-size: 0.8rem;">Extended Search Tools</strong>
                </span>
                <span class="badge bg-light text-muted border" style="font-size: 0.72rem; font-weight: normal;">Collapse / Expand <i class="fa fa-chevron-down ms-1" style="font-size: 0.65rem;"></i></span>
            </summary>
            <ul class="nav" id="moresearches">
                <li class="nav-item">
                    <a href="/cgi-bin/koha/opac-search.pl"><i class="fa-solid fa-sliders fa-fw" aria-hidden="true"></i> <span>Advanced search</span></a>
                </li>
                <li class="nav-item">
                    <a href="/cgi-bin/koha/opac-collections.pl"><i class="fa-solid fa-layer-group fa-fw" aria-hidden="true"></i> <span>Collections</span></a>
                </li>
                [% IF ( Koha.Preference( 'UseCourseReserves' ) == 1 ) %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-course-reserves.pl"><i class="fa-solid fa-graduation-cap fa-fw" aria-hidden="true"></i> <span>Course reserves</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference( 'OpacBrowser' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-browser.pl"><i class="fa-solid fa-sitemap fa-fw" aria-hidden="true"></i> <span>Browse by hierarchy</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference( 'OpacAuthorities' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-authorities-home.pl"><i class="fa-solid fa-id-card-clip fa-fw" aria-hidden="true"></i> <span>Authority search</span></a>
                    </li>
                [% END %]
                [% IF ( ( Koha.Preference( 'opacuserlogin' ) == 1 ) && ( Koha.Preference( 'OPACComments' ) == 1 ) && ( Koha.Preference( 'OpacShowRecentComments' ) == 1 ) ) %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-showreviews.pl"><i class="fa-solid fa-comments fa-fw" aria-hidden="true"></i> <span>Recent comments</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference( 'TagsEnabled' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-tags.pl"><i class="fa-solid fa-tags fa-fw" aria-hidden="true"></i> <span>Tag cloud</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference( 'OpacCloud' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-tags_subject.pl"><i class="fa-solid fa-tag fa-fw" aria-hidden="true"></i> <span>Subject cloud</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference( 'OpacTopissue' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-topissues.pl"><i class="fa-solid fa-fire fa-fw" aria-hidden="true"></i> <span>Most popular</span></a>
                    </li>
                [% END %]
                [% IF Koha.Preference('SearchEngine') == 'Elasticsearch' && Koha.Preference( 'OpacBrowseSearch' ) == 1 %]
                    <li class="nav-item">
                        <a href="/cgi-bin/koha/opac-browse.pl"><i class="fa-solid fa-compass fa-fw" aria-hidden="true"></i> <span>Browse search</span></a>
                    </li>
                [% END %]
                [% IF suggestion %]
                    [% IF Koha.Preference( 'AnonSuggestions' ) == 1 || Koha.Preference( 'OPACViewOthersSuggestions' ) == 1 %]
                        <li class="nav-item">
                            <a href="/cgi-bin/koha/opac-suggestions.pl?suggested_by_anyone=1"><i class="fa-solid fa-lightbulb fa-fw" aria-hidden="true"></i> <span>Purchase suggestions</span></a>
                        </li>
                    [% END %]
                [% END %]
                [% IF ( Koha.Preference('OPACShowLibraries') && AllPublicBranches.size > 0 ) %]
                    <li class="nav-item">
                        <a id="library_page" href="/cgi-bin/koha/opac-library.pl">
                            [% IF ( singleBranchMode || AllPublicBranches.size == 1 ) %]
                                <i class="fa-solid fa-phone fa-fw" aria-hidden="true"></i> <span>Contact</span>
                            [% ELSE %]
                                <i class="fa-solid fa-building-columns fa-fw" aria-hidden="true"></i> <span>Libraries</span>
                            [% END %]
                        </a>
                    </li>
                [% END %]
                [% PROCESS koha_news_block news => OpacMoreSearches %]
            </ul>
            <!-- /.nav#moresearches -->
            </details>
        </div>
        <!-- /.row -->
    </div>
    <!-- /.container-fluid -->
[% END # / OpacPublic %]

[% IF ( Koha.Preference( 'opacuserlogin' ) == 1 ) %]
    <!-- Login form hidden by default, used for modal window -->
    <div id="loginModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="modalLoginLabel" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h1 class="modal-title" id="modalLoginLabel">Log in to your account</h1>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Close"></button>
                </div>
                <form action="/cgi-bin/koha/opac-user.pl" method="post" name="auth" id="modalAuth">
                    [% INCLUDE 'csrf-token.inc' %]
                    <input type="hidden" name="has-search-query" id="has-search-query" value="" />
                    <input type="hidden" name="return" id="modal-return-url" value="" />
                    <div class="modal-body">
                        [% IF ( Koha.Preference('GoogleOpenIDConnect') == 1 ) %]
                            <a href="/cgi-bin/koha/svc/auth/googleopenidconnect" class="btn btn-light" id="openid_connect"><i class="fa-brands fa-google" aria-hidden="true"></i> Log in with Google</a>
                            <p>If you do not have a Google account, but do have a local account, you can still log in: </p>
                        [% END # /IF GoogleOpenIDConnect %]
                        [% IF ( shibbolethAuthentication ) %]
                            [% IF ( invalidShibLogin ) %]
                                <!-- This is what is displayed if shibboleth login has failed to match a koha user -->
                                <div class="alert alert-info">
                                    <p>Sorry, your Shibboleth identity does not match a valid library identity. If you have a local login, you may use that below.</p>
                                </div>
                            [% ELSE %]
                                <h3 class="shib_title">Shibboleth login</h3>
                                <p><a id="shib_url" class="shib_url" href="[% shibbolethLoginUrl | $raw %]">Log in using a Shibboleth account</a>.</p>
                                [% UNLESS Koha.Preference('opacShibOnly') %]
                                    <h3 class="shib_local_title">Local login</h3>
                                [% END %]
                            [% END %]
                        [% END %]
                        [% UNLESS Koha.Preference('opacShibOnly') %]
                            [% SET identity_providers = AuthClient.get_providers('opac') %]
                            [% IF ( ! identity_providers.empty ) %]
                                [% FOREACH provider IN identity_providers %]
                                    <p class="clearfix">
                                        <a href="[% provider.url | url %]" class="btn btn-light col-md-12" id="provider_[% provider.code | html %]">
                                            [% IF provider.icon_url %]
                                                <img src="[% provider.icon_url | url %]" />
                                            [% ELSE %]
                                                <i class="fa fa-user" aria-hidden="true"></i>
                                            [% END %]
                                            [% tx("Log in with {identity_provider}", { identity_provider = provider.description } ) | html %]
                                        </a>
                                    </p>
                                [% END %]
                                <hr />
                                <p>If you do not have an external account, but do have a local account, you can still log in: </p>
                            [% END # /IF  identity_providers.size %]
                            <input type="hidden" name="koha_login_context" value="opac" />
                            <fieldset class="brief">
                                <div class="local-login">
                                    [% PROCESS login_label for="muserid" %]<input type="text" id="muserid" name="login_userid" autocomplete="off" /> <label for="mpassword">Password:</label
                                    ><input type="password" id="mpassword" name="login_password" autocomplete="off" />
                                    <fieldset class="action">
                                        <input type="hidden" name="login_op" value="cud-login" />
                                        <input type="submit" class="btn btn-primary" value="Log in" />
                                    </fieldset>
                                </div>
                                [% IF OpacLoginInstructions %]
                                    <div id="nologininstructions-modal" class="nologininstructions"> [% PROCESS koha_news_block news => OpacLoginInstructions %] </div>
                                [% END %]
                                [% IF Koha.Preference('OpacResetPassword') && Categories.can_any_reset_password %]
                                    <div id="forgotpassword-modal" class="forgotpassword">
                                        <p><a href="/cgi-bin/koha/opac-password-recovery.pl">Forgot your password?</a></p>
                                    </div>
                                [% END %]
                                [% IF Koha.Preference('PatronSelfRegistration') && Categories.all( categorycode => Koha.Preference('PatronSelfRegistrationDefaultCategory') ).count %]
                                    <div id="patronregistration-modal" class="patronregistration">
                                        <p><a href="/cgi-bin/koha/opac-memberentry.pl">Create an account</a></p>
                                    </div>
                                [% END %]
                            </fieldset>
                        [% END %]
                    </div>
                </form>
                <!-- /#auth -->
            </div>
            <!-- /.modal-content -->
        </div>
        <!-- /.modal-dialog -->
    </div>
    <!-- /#modalAuth  -->
[% END # / IF opacuserlogin %]

[% IF Koha.Preference( 'CookieConsent' ) %]
    <!-- Cookie consent bar -->
    <div id="cookieConsentBar" aria-hidden="true">
        [% IF ( CookieConsentBar ) %]
            <div id="cookieConsentBar_content"> [% PROCESS koha_news_block news => CookieConsentBar %] </div>
        [% END %]
        <div class="consentButtons">
            [% IF ( JSConsents.all('opacConsent').size ) %]
                <button type="button" class="btn btn-primary consentAcceptAll">Accept all cookies</button>
            [% END %]
            <button type="button" class="btn btn-primary consentAcceptEssential">Accept essential cookies</button>
            <button type="button" class="btn btn-info" id="consentMoreInfo" aria-label="Click to view more information about your cookie consents">More information</button>
        </div>
    </div>
    <!-- /#cookieConsentBar -->
    <!-- Cookie consent modal -->
    <div id="cookieConsentModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="cookieConsentModalLabel" aria-hidden="true">
        <div class="modal-dialog">
            <div class="modal-content">
                <div class="modal-header">
                    <h1 class="modal-title" id="cookieConsentModalLabel">Cookies policy</h1>
                </div>
                <div class="modal-body">
                    [% IF ( CookieConsentPopup ) %]
                        <div id="cookieConsentPopupText"> [% PROCESS koha_news_block news => CookieConsentPopup %] </div>
                    [% END %]
                    <div id="consentCookieList">
                        [% consents = JSConsents.all('opacConsent') %]
                        [% FOREACH consent IN consents %]
                            <div class="consentModalItem">
                                <div class="consentItemCheckbox">
                                    <input class="consentCheckbox" type="checkbox" name="consentCheckbox" value="[% consent.id | html %]" aria-label="Consent to cookie" />
                                </div>
                                <div class="consentItemMeta">
                                    <div class="consentItemName">[% consent.name | html %]</div>
                                    <div class="consentItemDescription">[% consent.description | html %]</div>
                                </div>
                            </div>
                        [% END %]
                    </div>
                </div>
                <div class="modal-footer">
                    <div class="consentButtons">
                        <button type="button" class="btn btn-primary consentAcceptEssential">Accept essential cookies</button>
                        [% IF ( JSConsents.all('opacConsent').size ) %]
                            <button type="button" class="btn btn-primary consentAcceptAll">Accept all cookies</button>
                            <button type="button" class="btn btn-warning" id="consentAcceptSelected">Accept selected non-essential cookies</button>
                        [% END %]
                        <a href="#" class="btn btn-secondary consentCloseModal">Cancel</a>
                    </div>
                </div>
            </div>
            <!-- /.modal-content -->
        </div>
        <!-- /.modal-dialog -->
    </div>
[% END %]

<!-- ========================================================================= -->
<!-- FTU ADAPTIVE MOBILE BOTTOM DOCK                                          -->
<!-- ========================================================================= -->
<nav class="ftu-mobile-bottom-dock noprint" id="ftuMobileBottomDock" aria-label="Mobile quick navigation">
    <a href="/opac/" class="ftu-dock-item" id="ftuDockHome" aria-label="Home">
        <div class="ftu-dock-icon"><i class="fa fa-home" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Home</span>
    </a>
    <a href="/cgi-bin/koha/opac-search.pl" class="ftu-dock-item" id="ftuDockSearch" aria-label="Search">
        <div class="ftu-dock-icon"><i class="fa fa-search" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Search</span>
    </a>
    <a href="/cgi-bin/koha/opac-databases.pl" class="ftu-dock-item" id="ftuDockDatabases" aria-label="Databases">
        <div class="ftu-dock-icon"><i class="fa fa-database" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Databases</span>
    </a>
    <a href="/cgi-bin/koha/opac-collections.pl" class="ftu-dock-item" id="ftuDockCollections" aria-label="Collections">
        <div class="ftu-dock-icon"><i class="fa fa-cubes" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Collections</span>
    </a>
    [% IF loggedinusername %]
    <a href="/cgi-bin/koha/opac-user.pl" class="ftu-dock-item" id="ftuDockUser" aria-label="Account">
        <div class="ftu-dock-icon"><i class="fa fa-user-circle" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Account</span>
    </a>
    [% ELSE %]
    <a href="/cgi-bin/koha/opac-user.pl" class="ftu-dock-item" id="ftuDockUser" data-bs-toggle="modal" data-bs-target="#modalAuth" aria-label="Log in">
        <div class="ftu-dock-icon"><i class="fa fa-user" aria-hidden="true"></i></div>
        <span class="ftu-dock-label">Log in</span>
    </a>
    [% END %]
</nav>
