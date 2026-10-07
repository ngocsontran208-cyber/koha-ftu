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
            <div class="row ftu-footer-row">
                <!-- Col 1: FTU Library Brand & Contact (5/12) -->
                <div class="col-12 col-lg-5 mb-3 mb-lg-0 ftu-footer-brand-col">
                    <div class="d-flex align-items-center mb-3 ftu-footer-brand-wrap" style="gap: 12px;">
                        <img src="/opac-tmpl/bootstrap/images/ftu-logo.svg" alt="[% FTU_BRAND.logo_alt %]" style="height: 38px; width: auto;"
                            onerror="this.onerror=null; this.src='[% FTU_BRAND.logo_url %]'" />
                        <div>
                            <div class="ftu-footer-title" style="font-weight: 800; color: #0F172A; font-size: 0.98rem; line-height: 1.3; text-transform: uppercase;">
                                [% FTU_BRAND.library_name_en %]
                            </div>
                            <div class="ftu-footer-sub" style="font-size: 0.78rem; color: #64748B; font-weight: 500; margin-top: 2px;">
                                [% FTU_BRAND.campus_current_en %]
                            </div>
                        </div>
                    </div>

                    <div class="d-flex flex-column ftu-footer-contacts" style="gap: 8px; font-size: 0.84rem; color: #475569;">
                        <!-- Address -->
                        <div class="d-flex align-items-start ftu-contact-item" style="gap: 10px;">
                            <i class="fa fa-location-dot" style="color: #b91c1c; font-size: 15px; margin-top: 3px; flex-shrink: 0;" aria-hidden="true"></i>
                            <div>
                                <strong style="color: #1E293B;">Address:</strong>
                                <span> [% FTU_BRAND.campus_hcm_addr_en || 'No. 15, D5 St., Ward 25, Binh Thanh District, Ho Chi Minh City' %]</span>
                            </div>
                        </div>

                        <!-- Phone & Email quick links on Mobile -->
                        <div class="d-flex flex-wrap align-items-center ftu-quick-contact-row" style="gap: 12px;">
                            <div class="d-flex align-items-center" style="gap: 8px;">
                                <i class="fa fa-phone" style="color: #b91c1c; font-size: 14px; flex-shrink: 0;" aria-hidden="true"></i>
                                <div>
                                    <strong style="color: #1E293B;">Hotline:</strong>
                                    <a href="tel:02835127254" style="color: #475569; font-weight: 600; text-decoration: none;">[% FTU_BRAND.hotline_hcmc || '(028) 3512 7254' %]</a>
                                </div>
                            </div>

                            <div class="d-flex align-items-center" style="gap: 8px;">
                                <i class="fa fa-envelope" style="color: #b91c1c; font-size: 14px; flex-shrink: 0;" aria-hidden="true"></i>
                                <div>
                                    <strong style="color: #1E293B;">Email:</strong>
                                    <a href="mailto:[% FTU_BRAND.email_contact || 'tv.hcmc@ftu.edu.vn' %]" style="color: #b91c1c; font-weight: 600; text-decoration: none;">[% FTU_BRAND.email_contact || 'tv.hcmc@ftu.edu.vn' %]</a>
                                </div>
                            </div>
                        </div>

                        <!-- Service Hours -->
                        <div class="d-flex align-items-center ftu-contact-item" style="gap: 10px;">
                            <i class="fa fa-clock" style="color: #b91c1c; font-size: 14px; flex-shrink: 0;" aria-hidden="true"></i>
                            <div>
                                <strong style="color: #1E293B;">Hours:</strong>
                                <span> [% FTU_BRAND.hours_summary_en || 'Mon – Fri: 07:30 – 19:30 | Sat: 08:00 – 16:00' %]</span>
                            </div>
                        </div>

                        <!-- Social & Web Channels: FB, YouTube, Web -->
                        <div class="d-flex align-items-center ftu-social-row mt-2 pt-1" style="gap: 10px;">
                            <span style="font-size: 0.82rem; font-weight: 700; color: #1e293b; margin-right: 4px;">Connect:</span>
                            <a href="[% FTU_BRAND.link_facebook || 'https://www.facebook.com/ftu2.hcmc' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-btn ftu-social-fb" title="Facebook FTU Library" aria-label="Facebook">
                                <i class="fa-brands fa-facebook-f fa fa-facebook-f" aria-hidden="true"></i>
                            </a>
                            <a href="[% FTU_BRAND.link_youtube || 'https://www.youtube.com/@FTUChannel' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-btn ftu-social-yt" title="YouTube FTU Channel" aria-label="YouTube">
                                <i class="fa-brands fa-youtube fa fa-youtube-play" aria-hidden="true"></i>
                            </a>
                            <a href="[% FTU_BRAND.link_portal || 'https://hcmc.ftu.edu.vn' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-btn ftu-social-web" title="FTU Portal Website" aria-label="Website">
                                <i class="fa-solid fa-globe fa fa-globe" aria-hidden="true"></i>
                            </a>
                        </div>
                    </div>
                </div>

                <!-- Col 2: Discover Resources (3/12) - Open on Desktop, Accordion on Mobile -->
                <div class="col-12 col-md-6 col-lg-3 mb-2 mb-lg-0">
                    <details class="ftu-footer-accordion" open>
                        <summary class="ftu-footer-summary">
                            <h4 class="ftu-footer-heading">
                                <span class="ftu-footer-heading-bar"></span>
                                Discover Resources
                            </h4>
                            <i class="fa fa-chevron-down ftu-footer-chevron d-lg-none" aria-hidden="true"></i>
                        </summary>
                        <ul class="ftu-footer-list">
                            <li><a href="/cgi-bin/koha/opac-collections.pl" class="ftu-footer-link">Digital Collections</a></li>
                            <li><a href="/cgi-bin/koha/opac-search.pl?idx=au" class="ftu-footer-link">Search by Author</a></li>
                            <li><a href="/cgi-bin/koha/opac-search.pl?idx=su" class="ftu-footer-link">Search by Subject</a></li>
                            <li><a href="/cgi-bin/koha/opac-course-reserves.pl" class="ftu-footer-link">Course Reserves</a></li>
                            <li><a href="[% FTU_BRAND.link_dspace %]" target="_blank" rel="noopener noreferrer" class="ftu-footer-link ftu-dspace-link">DSpace Digital Repository <i class="fa fa-external-link-alt" style="font-size: 0.72rem; margin-left: 3px;"></i></a></li>
                        </ul>
                    </details>
                </div>

                <!-- Col 3: Help & Support (4/12) - Open on Desktop, Accordion on Mobile -->
                <div class="col-12 col-md-6 col-lg-4 mb-2 mb-lg-0">
                    <details class="ftu-footer-accordion" open>
                        <summary class="ftu-footer-summary">
                            <h4 class="ftu-footer-heading">
                                <span class="ftu-footer-heading-bar"></span>
                                Help &amp; Services
                            </h4>
                            <i class="fa fa-chevron-down ftu-footer-chevron d-lg-none" aria-hidden="true"></i>
                        </summary>
                        <ul class="ftu-footer-list">
                            <li><a href="/cgi-bin/koha/opac-user.pl" class="ftu-footer-link">Account &amp; Renewals</a></li>
                            <li><a href="[% FTU_BRAND.link_dspace %]/info/end-user-agreement" target="_blank" rel="noopener noreferrer" class="ftu-footer-link">Academic Copyright Policy</a></li>
                            <li><a href="/cgi-bin/koha/opac-news-detail.pl?id=5" class="ftu-footer-link">News &amp; Service Notices</a></li>
                            <li><a href="/cgi-bin/koha/opac-reportproblem.pl" class="ftu-footer-link">Contact Library Admin</a></li>
                        </ul>
                    </details>
                </div>
            </div>

            <!-- Bottom Copyright Bar -->
            <div class="pt-3 border-top d-flex flex-column flex-md-row justify-content-between align-items-center ftu-footer-bottom-bar"
                style="border-top: 1px solid #E2E8F0 !important; font-size: 12px; color: #64748B; gap: 0.5rem;">
                <p style="margin: 0; color: #64748B; text-align: center;">[% FTU_BRAND.copyright_text %]</p>
                <div class="d-flex align-items-center" style="gap: 12px;">
                    <a href="/cgi-bin/koha/opac-oai.pl" target="_blank" style="color: #64748B; text-decoration: none; font-weight: 500;">OAI-PMH</a>
                    <span style="display: inline-block; width: 4px; height: 4px; background: #CBD5E1; border-radius: 50%;"></span>
                    <span>Powered by <a href="https://koha-community.org" target="_blank"
                        style="color: #b91c1c; font-weight: 600; text-decoration: none;">Koha &amp; DSpace</a></span>
                </div>
            </div>
        </div>

        <style>
            /* Social & Web buttons in footer */
            .ftu-social-btn {
                display: inline-flex !important;
                align-items: center !important;
                justify-content: center !important;
                width: 32px !important;
                height: 32px !important;
                border-radius: 50% !important;
                color: #ffffff !important;
                text-decoration: none !important;
                transition: all 0.2s ease-in-out !important;
                box-shadow: 0 1px 3px rgba(0, 0, 0, 0.12) !important;
                font-size: 14px !important;
            }
            .ftu-social-btn:hover {
                transform: translateY(-2px) scale(1.08) !important;
                box-shadow: 0 4px 8px rgba(0, 0, 0, 0.22) !important;
                color: #ffffff !important;
                filter: brightness(1.1) !important;
            }
            .ftu-social-fb { background: #1877f2 !important; }
            .ftu-social-yt { background: #ef4444 !important; }
            .ftu-social-web { background: #0284c7 !important; }

            .ftu-footer-accordion summary,
            .ftu-footer-summary {
                list-style: none !important;
                list-style-type: none !important;
            }
            .ftu-footer-accordion summary::-webkit-details-marker,
            .ftu-footer-summary::-webkit-details-marker {
                display: none !important;
            }
            .ftu-footer-accordion summary::marker,
            .ftu-footer-summary::marker {
                display: none !important;
                content: "" !important;
            }
            @media (min-width: 992px) {
                .ftu-footer-accordion {
                    display: block !important;
                }
                .ftu-footer-accordion summary {
                    pointer-events: none !important;
                    cursor: default !important;
                    list-style: none !important;
                    list-style-type: none !important;
                    margin-bottom: 1.25rem !important;
                }
                .ftu-footer-chevron {
                    display: none !important;
                }
                .ftu-footer-list {
                    display: block !important;
                }
            }
        </style>
        <script>
            (function() {
                function syncFtuFooter() {
                    var isDesktop = window.innerWidth >= 992;
                    var accordions = document.querySelectorAll('.ftu-footer-accordion');
                    accordions.forEach(function(acc) {
                        if (isDesktop) {
                            acc.setAttribute('open', '');
                        } else {
                            if (!acc.dataset.userInteracted) {
                                acc.removeAttribute('open');
                            }
                        }
                    });
                }
                if (document.readyState === 'loading') {
                    document.addEventListener('DOMContentLoaded', syncFtuFooter);
                } else {
                    syncFtuFooter();
                }
                window.addEventListener('resize', syncFtuFooter);

                document.addEventListener('DOMContentLoaded', function() {
                    var summaries = document.querySelectorAll('.ftu-footer-summary');
                    summaries.forEach(function(s) {
                        s.addEventListener('click', function(e) {
                            if (window.innerWidth >= 992) {
                                e.preventDefault();
                                return false;
                            }
                            var parentAcc = this.closest('.ftu-footer-accordion');
                            if (parentAcc) {
                                parentAcc.dataset.userInteracted = 'true';
                            }
                        });
                    });
                });
            })();
        </script>
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

    var ssoHost = '[% FTU_BRAND.link_sso %]' || '/sso';
    ssoHost = ssoHost.replace(/\/+$/, '');
    var ssoEndpoint = ssoHost.endsWith('/sso') ? (ssoHost + '/koha-to-dspace') : (ssoHost + '/sso/koha-to-dspace');

    // 1. Tự động đồng bộ trước phiên SSO DSpace chạy ngầm (Silent pre-auth)
    try {
        if (window.fetch) {
            fetch(ssoEndpoint + '?user=' + encodeURIComponent(kohaUser) + '&mode=json', {
                method: 'GET',
                credentials: 'include'
            }).catch(function() {});
        }
    } catch(e) {}

    // 2. Chuyển đổi toàn bộ link trỏ đến DSpace sang Cổng chuyển giao phiên Seamless SSO
    function patchDspaceLinks() {
        $('a[href*=":4000/"], a[href*="/handle/"], a[href*="/items/"], .ftu-dspace-link').each(function() {
            var href = $(this).attr('href');
            if (href && !href.includes('/koha-to-dspace') && !href.startsWith('javascript:')) {
                var ssoBridge = ssoEndpoint + '?user=' + encodeURIComponent(kohaUser) + '&target=' + encodeURIComponent(href);
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
        if (href && !href.includes('/koha-to-dspace') && !href.startsWith('javascript:')) {
            e.preventDefault();
            var ssoBridge = ssoEndpoint + '?user=' + encodeURIComponent(kohaUser) + '&target=' + encodeURIComponent(href);
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
    var curPort = window.location.port;
    var isGateway = !curPort || curPort === '80' || curPort === '443';
    if (curHost && curHost !== 'localhost' && curHost !== '127.0.0.1') {
        $('a[href*="localhost"], a[href*="127.0.0.1"]').each(function() {
            var href = $(this).attr('href');
            if (!href) return;
            if (isGateway) {
                href = href.replace(/https?:\/\/(localhost|127\.0\.0\.1):4000(\/elib)?/g, '/elib')
                           .replace(/https?:\/\/(localhost|127\.0\.0\.1):8090/g, '/sso')
                           .replace(/https?:\/\/(localhost|127\.0\.0\.1):8095\/reader/g, '/reader')
                           .replace(/https?:\/\/(localhost|127\.0\.0\.1):8095/g, '/drm')
                           .replace(/https?:\/\/(localhost|127\.0\.0\.1):8082/g, '')
                           .replace(/(localhost|127\.0\.0\.1)/g, curHost);
            } else {
                href = href.replace(/(localhost|127\.0\.0\.1)/g, curHost);
            }
            $(this).attr('href', href);
        });
    }
})();
</script>
<script nonce="[% Koha.CSPNonce | $raw %]">
(function() {
    if (window.history && window.history.replaceState && window.location.search && /[?&]logout(?:\.x|\.y)?=/.test(window.location.search)) {
        var cleanSearch = window.location.search.replace(/([?&])logout(?:\.x|\.y)?=[^&]*(&|$)/g, '$1').replace(/[?&]$/, '');
        var newUrl = window.location.pathname + cleanSearch + window.location.hash;
        window.history.replaceState(null, document.title, newUrl);
    }
})();
</script>

<!-- FTU Controlled Digital Lending & DRM Engine -->
[% INCLUDE 'ftu-digital-lending.inc' %]

<!-- FTU Adaptive Viewport & Mobile Controller Engine -->
<script src="/opac-tmpl/bootstrap/js/ftu-adaptive-viewport.js?v=20261006_mobile_engine" nonce="[% Koha.CSPNonce | $raw %]"></script>
</body>
<!-- prettier-ignore-start -->
</html>
<!-- prettier-ignore-end -->
