[% USE raw %]
[% USE Koha %]
[% USE Branches %]
[% USE AdditionalContents %]
[%- USE KohaPlugins -%]
[% USE Asset %]
[% SET opaccredits = AdditionalContents.get( location => "opaccredits", lang => lang, library => logged_in_user.branchcode || default_branch ) %]
[% PROCESS 'ftu-brand-config.inc' %]
[% PROCESS 'html_helpers.inc' %]
[% IF Koha.Preference( 'CookieConsent' ) %]
    [% USE JSConsents %]
[% END %]
[% UNLESS ( is_popup ) %]
    [% SET OpacLangSelectorMode = Koha.Preference('OpacLangSelectorMode') %]
    [% IF ( opaccredits ) %]
        <div class="container-fluid">
            <div class="row">
                <div class="col"> [% PROCESS koha_news_block news => opaccredits %] </div>
            </div>
        </div>
    [% END #/ opaccredits %]
    <!-- prettier-ignore-start -->
    </div> <!-- / #wrapper in masthead.inc -->
    <!-- prettier-ignore-end -->

    <!-- ========================================================================= -->
    <!-- FTU MASTER LIBRARY FOOTER (Modern Academic Edition)                       -->
    <!-- ========================================================================= -->
    <footer class="ftu-footer-master noprint">
        <div class="ftu-footer-container">
            <div class="row mb-5" style="row-gap: 2.5rem;">
                <!-- Col 1: FTU Library Brand & Contact (5/12) -->
                <div class="col-12 col-lg-5 mb-4 mb-lg-0">
                    <div class="d-flex align-items-center mb-4" style="gap: 14px;">
                        <img src="/opac-tmpl/bootstrap/images/ftu-logo.svg" alt="[% FTU_BRAND.logo_alt %]" style="height: 42px; width: auto;"
                            onerror="this.onerror=null; this.src='[% FTU_BRAND.logo_url %]'" />
                        <div>
                            <div style="font-weight: 800; color: #0F172A; font-size: 1.05rem; line-height: 1.3; letter-spacing: -0.01em; text-transform: uppercase;">
                                [% FTU_BRAND.library_name_en %]
                            </div>
                            <div style="font-size: 0.8rem; color: #64748B; font-weight: 500; margin-top: 2px;">
                                [% FTU_BRAND.campus_current_en %]
                            </div>
                        </div>
                    </div>

                    <div class="d-flex flex-column" style="gap: 12px; font-size: 0.875rem; color: #475569;">
                        <!-- Address -->
                        <div class="d-flex align-items-start" style="gap: 12px;">
                            <svg style="width: 18px; height: 18px; color: #b91c1c; flex-shrink: 0; margin-top: 2px;" fill="none"
                                stroke="currentColor" viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                    d="M17.657 16.657L13.414 20.9a1.998 1.998 0 01-2.827 0l-4.244-4.243a8 8 0 1111.314 0z"></path>
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                    d="M15 11a3 3 0 11-6 0 3 3 0 016 0z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1E293B;">Address:</span>
                                <span style="color: #475569;"> No. 15, D5 St., Thanh My Tay Ward, Ho Chi Minh City</span>
                            </div>
                        </div>

                        <!-- Phone -->
                        <div class="d-flex align-items-center" style="gap: 12px;">
                            <svg style="width: 18px; height: 18px; color: #b91c1c; flex-shrink: 0;" fill="none" stroke="currentColor"
                                viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                    d="M3 5a2 2 0 012-2h3.28a1 1 0 01.948.684l1.498 4.493a1 1 0 01-.502 1.21l-2.257 1.13a11.042 11.042 0 005.516 5.516l1.13-2.257a1 1 0 011.21-.502l4.493 1.498a1 1 0 01.684.949V19a2 2 0 01-2 2h-1C9.716 21 3 14.284 3 6V5z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1E293B;">Phone:</span>
                                <span style="color: #475569; font-weight: 500;"> (028) 3512 7254 - 3512 7258</span>
                            </div>
                        </div>

                        <!-- Email -->
                        <div class="d-flex align-items-center" style="gap: 12px;">
                            <svg style="width: 18px; height: 18px; color: #b91c1c; flex-shrink: 0;" fill="none" stroke="currentColor"
                                viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                    d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1E293B;">Email:</span>
                                <a href="mailto:[% FTU_BRAND.email_contact %]"
                                    style="color: #b91c1c; font-weight: 500; text-decoration: none;"> [% FTU_BRAND.email_contact %]</a>
                            </div>
                        </div>

                        <!-- Service Hours -->
                        <div class="d-flex align-items-center" style="gap: 12px;">
                            <svg style="width: 18px; height: 18px; color: #b91c1c; flex-shrink: 0;" fill="none" stroke="currentColor"
                                viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="2"
                                    d="M12 8v4l3 3m6-3a9 9 0 11-18 0 9 9 0 0118 0z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1E293B;">Service Hours:</span>
                                <span style="color: #475569;"> [% FTU_BRAND.hours_summary_en %]</span>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- Col 2: Discover Resources (3/12) -->
                <div class="col-12 col-md-6 col-lg-3 mb-4 mb-lg-0">
                    <h4 style="font-weight: 700; color: #111827; text-transform: uppercase; letter-spacing: 0.05em; font-size: 0.8rem; margin-bottom: 1.25rem; display: flex; align-items: center; gap: 8px;">
                        <span style="width: 3px; height: 14px; background: #b91c1c; border-radius: 2px; display: inline-block;"></span>
                        Discover Resources
                    </h4>
                    <ul class="list-unstyled" style="padding-left: 0; margin-bottom: 0; list-style: none;">
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-collections.pl" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Digital Collections</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-search.pl?idx=au" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Search by Author</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-search.pl?idx=su" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Search by Subject</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-course-reserves.pl" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Course Reserves</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="[% FTU_BRAND.link_dspace %]" target="_blank" rel="noopener noreferrer" class="ftu-footer-link ftu-dspace-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">DSpace Digital Repository <i class="fa fa-external-link-alt" style="font-size: 0.75rem; margin-left: 3px;"></i></a></li>
                    </ul>
                </div>

                <!-- Col 3: Help & Support (4/12) -->
                <div class="col-12 col-md-6 col-lg-4">
                    <h4 style="font-weight: 700; color: #111827; text-transform: uppercase; letter-spacing: 0.05em; font-size: 0.8rem; margin-bottom: 1.25rem; display: flex; align-items: center; gap: 8px;">
                        <span style="width: 3px; height: 14px; background: #b91c1c; border-radius: 2px; display: inline-block;"></span>
                        Help &amp; Services
                    </h4>
                    <ul class="list-unstyled" style="padding-left: 0; margin-bottom: 0; list-style: none;">
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-user.pl" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Account &amp; Renewals</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="[% FTU_BRAND.link_dspace %]/info/end-user-agreement" target="_blank" rel="noopener noreferrer" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Academic Copyright Policy</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-news-detail.pl?id=5" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">News &amp; Service Notices</a></li>
                        <li style="margin-bottom: 0.65rem;"><a href="/cgi-bin/koha/opac-reportproblem.pl" class="ftu-footer-link"
                            style="color: #64748B; font-weight: 500; font-size: 0.875rem; text-decoration: none;">Contact Library Admin</a></li>
                    </ul>
                </div>
            </div>

            <!-- Bottom Copyright Bar -->
            <div class="pt-4 border-top d-flex flex-column flex-md-row justify-content-between align-items-center"
                style="border-top: 1px solid #E2E8F0 !important; font-size: 13px; color: #64748B; gap: 1rem;">
                <p style="margin: 0; color: #64748B;">[% FTU_BRAND.copyright_text %]</p>
                <div class="d-flex align-items-center" style="gap: 16px;">
                    <a href="/cgi-bin/koha/opac-oai.pl" target="_blank" style="color: #64748B; text-decoration: none; font-weight: 500;">OAI-PMH</a>
                    <span style="display: inline-block; width: 4px; height: 4px; background: #CBD5E1; border-radius: 50%;"></span>
                    <span>Powered by <a href="https://koha-community.org" target="_blank"
                        style="color: #b91c1c; font-weight: 600; text-decoration: none;">Koha &amp; DSpace</a></span>
                </div>
            </div>
        </div>
    </footer>

    [% IF ( Koha.Preference('OPACReportProblem') && Koha.Preference('KohaAdminEmailAddress') ) || Koha.Preference( 'CookieConsent' ) || OpacKohaUrl || ( ( opaclanguagesdisplay ) && ( ! one_language_enabled ) && ( languages_loop ) && ( OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer') ) %]
        <footer id="changelanguage" class="navbar navbar-expand navbar-light bg-light noprint">
            <div class="container-fluid">
                <div class="collapse navbar-collapse">
                    [%# Following on one line for translatability %]
                    [% IF ( ( opaclanguagesdisplay ) && ( ! one_language_enabled ) && ( languages_loop ) && ( OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer') ) %]
                        [% context = "footer" %]
                        [% INCLUDE 'langmenu.inc' %]
                    [% END # / IF opaclanguagedisplay %]

                    <div class="navbar-nav flex-grow-1">
                        [% IF Koha.Preference('OPACReportProblem') && Koha.Preference('KohaAdminEmailAddress') %]
                            <a id="report_a_problem" class="nav-link" href="/cgi-bin/koha/opac-reportproblem.pl">
                                <i class="fa fa-warning fa-fw fa-icon-footer" aria-hidden="true"></i>
                                <span class="report_a_problem_text">Report a problem</span>
                            </a>
                        [% END %]

                        [% IF Koha.Preference( 'CookieConsent' ) %]
                            <a id="cookieConsentFooter" class="nav-link" href="#">
                                <i class="fa fa-cookie fa-fw fa-icon-footer" aria-hidden="true"></i>
                                <span class="cookieConsentFooter_text">Cookies</span>
                            </a>
                        [% END %]
                    </div>
                    [% IF OpacKohaUrl %]
                        <div class="navbar-nav">
                            <a id="koha_url" class="nav-link koha_url" href="https://koha-community.org">
                                <svg xmlns="http://www.w3.org/2000/svg" viewBox="0 0 16 16">
                                    <path
                                        fill="currentColor"
                                        d="M7.394.75c.82-.45 1.75-.72 2.69-.75.5.015.99.1 1.45.27.92.35 1.68 1.05 2.15 1.9.53.865.76 1.875.87 2.875.25 3.315-.98 6.635-3.07 9.18-.825.82-1.835 1.52-3 1.735-.96.135-2-.07-2.775-.675-.48-.365-.67-1-.63-1.575.425.6 1.12 1.015 1.86 1.035.675.03 1.35-.275 1.8-.765.75-.825.835-2.21.12-3.08-.325-.375-.7-.715-1.15-.95-.44-.265-.95-.38-1.46-.45-.93-.06-1.9.11-2.72.57a3.22 3.22 0 0 0-1.565 2.15c-.2.7-.125 1.43-.05 2.14-.31-.81-.43-1.67-.5-2.53v-.64c.12-3.13 1.43-6.2 3.53-8.515.725-.75 1.53-1.43 2.45-1.92Zm0 0"
                                        style="stroke-width:.500008"
                                    />
                                </svg>
                                <span class="koha_url_text">Powered by Koha</span>
                            </a>
                        </div>
                    [% END # /IF OpacKohaUrl %]
                </div>
                <!-- /.collapse.navbar-collapse -->
            </div>
            <!-- /.container-fluid -->
        </footer>
        <!-- / #changelanguage -->
    [% END # /IF OpacLangSelectorMode == 'both' || OpacLangSelectorMode == 'footer' %]
[% END # / UNLESS is_popup %]

[% IF Koha.Preference( 'OpacTrustedCheckout' ) %]
    [% INCLUDE 'modals/checkout.inc' %]
[% END %]

<!-- CookieConsentedJS code that may run -->
[% IF Koha.Preference( 'CookieConsent' ) && JSConsents.all('opacConsent').size %]
    [% consents = JSConsents.all('opacConsent') %]
    [% FOREACH consent IN consents %]
        <div
            class="consentCode"
            style="display:none"
            aria-hidden="true"
            data-consent-id="[% consent.id | html %]"
            data-consent-code="[% consent.code | html %]"
            data-consent-match-pattern="[% consent.matchPattern | html %]"
            data-consent-cookie-domain="[% consent.cookieDomain | html %]"
            data-consent-cookie-path="[% consent.cookiePath | html %]"
            data-requires-consent="[% consent.opacConsent ? 'true' : 'false' | html %]"
        ></div>
    [% END %]
[% END %]

<!-- JavaScript includes -->
[% Asset.js("lib/jquery/jquery-3.6.0.min.js") | $raw %]
[% Asset.js("lib/jquery/jquery-migrate-3.3.2.min.js") | $raw %]
[% Asset.js("lib/bootstrap/js/bootstrap.bundle.min.js") | $raw %]
[% Asset.js("lib/fontfaceobserver/fontfaceobserver.min.js") | $raw %]
[% Asset.js("lib/enquire/enquire.min.js") | $raw %]
<script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
    let logged_in_user_id = "[% logged_in_user.borrowernumber | html %]";
</script>
[% Asset.js("js/global.js") | $raw %]
[% Asset.js("js/form-submit.js",{'type' => 'module'}) | $raw %]
[% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
    [% Asset.js("js/amazonimages.js") | $raw %]
[% END %]
<script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
    var query_desc = "[% query_desc | html %]";
    var querystring = "[% querystring | html %]";
    var query_cgi = "[% query_cgi | html %]";

    [% IF ( OPACAmazonCoverImages || SyndeticsCoverImages ) %]
        $(window).load(function() {
            verify_images();
         });
    [% END %]
    $(".print-large").on("click",function(){
        window.print();
        return false;
    });
    $(".addtoshelf").on("click",function(e){
        e.preventDefault();
        Dopop( this.href );
    });
    $("body").on("click", ".addtocart", function(e){
        e.preventDefault();
        var biblionumber = $(this).data("biblionumber");
        addRecord( biblionumber );
    });
    $("body").on("click", ".cartRemove", function(e){
        e.preventDefault();
        var biblionumber = $(this).data("biblionumber");
        delSingleRecord( biblionumber );
    });
</script>
[% IF Koha.Preference( 'opacbookbag' ) == 1 %]
    [% Asset.js("js/basket.js") | $raw %]
[% ELSIF ( Koha.Preference( 'virtualshelves' ) == 1 ) %]
    [% Asset.js("js/basket.js") | $raw %]
[% ELSE %]
    <script nonce="[% Koha.CSPNonce | $raw %]">
        var readCookie;
    </script>
[% END %]

[% IF Koha.Preference( 'opacuserlogin' ) == 1 %][% IF Koha.Preference( 'TagsEnabled' ) == 1 %][% Asset.js("js/tags.js") | $raw %][% END %][% END %]
[% IF ( GoogleJackets ) %]
    [% Asset.js("js/google-jackets.js") | $raw %]
[% END %]
[% IF ( Koha.Preference('OpacCoce') && Koha.Preference('CoceProviders') ) %]
    [% Asset.js("js/coce.js") | $raw %]
[% END %]

[% IF OPACLocalCoverImages %]
    [% Asset.js("js/localcovers.js") | $raw %]
[% END %]

[% IF Koha.Preference( 'OpacNewsLibrarySelect' ) %]
    <script nonce="[% Koha.CSPNonce | $raw %]">
        $("#news-branch-select").change(function () {
            $("#news-branch-select").submit();
        });
    </script>
[% END %]

[% Asset.js("lib/js-cookie/js.cookie-3.0.1.min.js") | $raw %]
[% Asset.js("js/show-password-toggle.js") | $raw %]
<script nonce="[% Koha.CSPNonce | $raw %]">
    $(document).ready(function () {
        if ($("#searchsubmit").length) {
            $(document).on("click", "#searchsubmit", function (e) {
                Cookies.remove("form_serialized", { path: "/" });
                Cookies.remove("form_serialized_limits", { path: "/" });
                Cookies.remove("search_path_code", { path: "/" });
            });
        }
    });
</script>
[% INCLUDE 'js-date-format.inc' %]
[% INCLUDE 'js-biblio-format.inc' %]
[% PROCESS jsinclude %]
[% IF ( Koha.Preference('OPACUserJS') ) %]
    <script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
        [% Koha.Preference('OPACUserJS') | $raw %]
    </script>
[% END %]
[% IF Branches.GetBranchSpecificJS( Branches.GetLoggedInBranchcode() || default_branch) %]
    <script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
        [% Branches.GetBranchSpecificJS( Branches.GetLoggedInBranchcode() || default_branch) | $raw %]
    </script>
[% END %]
[% IF SCO_login %]
    [% SET SCOUserJS = Koha.Preference('SCOUserJS') %]
    [% IF ( SCOUserJS ) %]
        <script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
            [% SCOUserJS | $raw %]
        </script>
    [% END %]
[% END %]
[% IF Koha.Preference( 'OpacTrustedCheckout' ) %]
    [% Asset.js("js/modals/checkout.js") | $raw %]
[% END %]
[% IF Koha.Preference( 'CookieConsent' ) %]
    [% Asset.js("js/cookieconsent.js") | $raw %]
[% END %]
[% IF ( loggedinusername ) %]
<script nonce="[% Koha.CSPNonce | $raw %]">
(function() {
    var kohaUser = '[% loggedinusername | html %]';
    if (!kohaUser) return;

    var ssoHost = '[% FTU_BRAND.link_sso %]' || (window.location.protocol + '//' + (window.location.hostname || 'localhost') + ':8090');
    ssoHost = ssoHost.replace(/\/+$/, '');

    // 1. Tự động đồng bộ trước phiên SSO DSpace chạy ngầm (Silent pre-auth)
    try {
        var ssoPreload = document.createElement('script');
        ssoPreload.src = ssoHost + '/sso/koha-to-dspace?user=' + encodeURIComponent(kohaUser) + '&mode=json';
        document.head.appendChild(ssoPreload);
    } catch(e) {}

    // 2. Chuyển đổi toàn bộ link trỏ đến DSpace sang Cổng chuyển giao phiên Seamless SSO
    function patchDspaceLinks() {
        $('a[href*=":4000/"], a[href*="/handle/"], a[href*="/items/"], .ftu-dspace-link').each(function() {
            var href = $(this).attr('href');
            if (href && !href.includes('/sso/koha-to-dspace') && !href.startsWith('javascript:')) {
                var ssoBridge = ssoHost + '/sso/koha-to-dspace?user=' + encodeURIComponent(kohaUser) + '&target=' + encodeURIComponent(href);
                $(this).attr('href', ssoBridge);
                $(this).attr('data-sso-bridged', 'true');
                if (!$(this).attr('title')) {
                    $(this).attr('title', 'Truy cập liên thông FTU SSO (Tự động đăng nhập DSpace)');
                }
            }
        });
    }

    $(document).ready(function() {
        patchDspaceLinks();
        setTimeout(patchDspaceLinks, 500);
        setTimeout(patchDspaceLinks, 1500);
    });

    // Bắt sự kiện click để đảm bảo an toàn tuyệt đối
    $(document).on('click', 'a[href*=":4000/"], a[href*="/handle/"], a[href*="/items/"], .ftu-dspace-link', function(e) {
        var href = $(this).attr('href');
        if (href && !href.includes('/sso/koha-to-dspace') && !href.startsWith('javascript:')) {
            e.preventDefault();
            var ssoBridge = ssoHost + '/sso/koha-to-dspace?user=' + encodeURIComponent(kohaUser) + '&target=' + encodeURIComponent(href);
            var target = $(this).attr('target');
            if (target === '_blank') {
                window.open(ssoBridge, '_blank');
            } else {
                window.location.href = ssoBridge;
            }
        }
    });
})();
</script>
[% END %]

<script nonce="[% Koha.CSPNonce | $raw %]">
(function() {
    var curHost = window.location.hostname;
    if (curHost && curHost !== 'localhost' && curHost !== '127.0.0.1') {
        $('a[href*="localhost:"], a[href*="127.0.0.1:"]').each(function() {
            var href = $(this).attr('href');
            if (href) {
                $(this).attr('href', href.replace(/(localhost|127\.0\.0\.1)/g, curHost));
            }
        });
    }
})();
</script>
</body>
<!-- prettier-ignore-start -->
</html>
<!-- prettier-ignore-end -->
