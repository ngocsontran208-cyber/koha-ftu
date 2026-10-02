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
    <!-- FTU MASTER LIBRARY FOOTER (DSpace Elegant White Edition)                  -->
    <!-- ========================================================================= -->
    <footer class="ftu-footer-master noprint">
        <div class="ftu-footer-container">
            <div class="row mb-5" style="row-gap: 2rem;">
                <!-- Cột 1: Thương hiệu Thư viện FTU & Liên hệ -->
                <div class="col-12 col-lg-6 mb-4 mb-lg-0">
                    <div class="d-flex align-items-center mb-4" style="gap: 12px;">
                        <img src="/opac-tmpl/bootstrap/images/ftu-logo.svg" alt="[% FTU_BRAND.logo_alt %]" style="height: 38px; width: auto;"
                            onerror="this.onerror=null; this.src='[% FTU_BRAND.logo_url %]'" />
                        <span class="font-bold tracking-tight text-lg uppercase"
                            style="font-weight: 700; color: #0F172A; font-size: 1.1rem; letter-spacing: -0.02em;">THƯ VIỆN PHÂN HIỆU TRƯỜNG ĐH NGOẠI THƯƠNG</span>
                    </div>

                    <div class="d-flex flex-column" style="gap: 14px; font-size: 0.875rem; color: #4B5563;">
                        <!-- Trụ sở chính -->
                        <div class="d-flex align-items-start" style="gap: 12px;">
                            <svg style="width: 20px; height: 20px; color: #9CA3AF; flex-shrink: 0; margin-top: 2px;" fill="none"
                                stroke="currentColor" viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M17.657 16.657L13.414 20.9a1.998 1.998 0 01-2.827 0l-4.244-4.243a8 8 0 1111.314 0z"></path>
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M15 11a3 3 0 11-6 0 3 3 0 016 0z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1F2937;">Trụ sở chính:</span>
                                <p style="margin-top: 2px; margin-bottom: 0;">Số 91 Phố Chùa Láng, Phường Láng Thượng, Quận Đống Đa, Hà Nội</p>
                            </div>
                        </div>

                        <!-- Phân hiệu TP.HCM -->
                        <div class="d-flex align-items-start" style="gap: 12px;">
                            <svg style="width: 20px; height: 20px; color: #9CA3AF; flex-shrink: 0; margin-top: 2px;" fill="none"
                                stroke="currentColor" viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M17.657 16.657L13.414 20.9a1.998 1.998 0 01-2.827 0l-4.244-4.243a8 8 0 1111.314 0z"></path>
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M15 11a3 3 0 11-6 0 3 3 0 016 0z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1F2937;">Phân hiệu tại TP. Hồ Chí Minh:</span>
                                <p style="margin-top: 2px; margin-bottom: 0;">Số 15 Đường D5, Phường 25, Quận Bình Thạnh, TP. Hồ Chí Minh</p>
                            </div>
                        </div>

                        <!-- Cơ sở Quảng Ninh -->
                        <div class="d-flex align-items-start" style="gap: 12px;">
                            <svg style="width: 20px; height: 20px; color: #9CA3AF; flex-shrink: 0; margin-top: 2px;" fill="none"
                                stroke="currentColor" viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M17.657 16.657L13.414 20.9a1.998 1.998 0 01-2.827 0l-4.244-4.243a8 8 0 1111.314 0z"></path>
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M15 11a3 3 0 11-6 0 3 3 0 016 0z"></path>
                            </svg>
                            <div>
                                <span style="font-weight: 600; color: #1F2937;">Cơ sở Quảng Ninh:</span>
                                <p style="margin-top: 2px; margin-bottom: 0;">Số 260 Đường Bạch Đằng, Phường Nam Khê, TP. Uông Bí, Tỉnh Quảng Ninh</p>
                            </div>
                        </div>

                        <!-- Email -->
                        <div class="d-flex align-items-center pt-2" style="gap: 12px;">
                            <svg style="width: 20px; height: 20px; color: #9CA3AF; flex-shrink: 0;" fill="none" stroke="currentColor"
                                viewBox="0 0 24 24">
                                <path stroke-linecap="round" stroke-linejoin="round" stroke-width="1.5"
                                    d="M3 8l7.89 5.26a2 2 0 002.22 0L21 8M5 19h14a2 2 0 002-2V7a2 2 0 00-2-2H5a2 2 0 00-2 2v10a2 2 0 002 2z">
                                </path>
                            </svg>
                            <a href="mailto:hoclieuso.hcmc@ftu.edu.vn"
                                style="color: #4B5563; font-weight: 500; text-decoration: none;">hoclieuso.hcmc@ftu.edu.vn</a>
                        </div>
                    </div>
                </div>

                <!-- Cột 2: Khám phá tài nguyên -->
                <div class="col-12 col-md-6 col-lg-3 mb-4 mb-lg-0">
                    <h4 class="font-bold mb-4 uppercase tracking-wider text-xs"
                        style="font-weight: 700; color: #111827; text-transform: uppercase; letter-spacing: 0.05em; font-size: 0.75rem;">
                        Khám phá tài nguyên</h4>
                    <ul class="list-unstyled" style="padding-left: 0; margin-bottom: 0; list-style: none;">
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-collections.pl" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Bộ sưu tập</a></li>
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-search.pl?idx=au" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Tìm kiếm theo Tác giả</a></li>
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-search.pl?idx=su" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Tìm kiếm theo Chủ đề</a></li>
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-course-reserves.pl" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Giáo trình &amp; Học phần</a></li>
                        <li class="mb-2"><a href="[% FTU_BRAND.link_dspace %]" target="_blank" rel="noopener noreferrer" class="text-decoration-none ftu-dspace-link"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Kho tài liệu số DSpace</a></li>
                    </ul>
                </div>

                <!-- Cột 3: Hỗ trợ & Hướng dẫn -->
                <div class="col-12 col-md-6 col-lg-3">
                    <h4 class="font-bold mb-4 uppercase tracking-wider text-xs"
                        style="font-weight: 700; color: #111827; text-transform: uppercase; letter-spacing: 0.05em; font-size: 0.75rem;">
                        Hỗ trợ &amp; Hướng dẫn</h4>
                    <ul class="list-unstyled" style="padding-left: 0; margin-bottom: 0; list-style: none;">
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-user.pl" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Tài khoản &amp; Gia hạn sách</a></li>
                        <li class="mb-2"><a href="[% FTU_BRAND.link_dspace %]/info/end-user-agreement" target="_blank" rel="noopener noreferrer" class="text-decoration-none ftu-dspace-link"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Quy định bản quyền học thuật</a></li>
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-news-detail.pl?id=1" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Câu hỏi thường gặp (FAQ)</a></li>
                        <li class="mb-2"><a href="/cgi-bin/koha/opac-reportproblem.pl" class="text-decoration-none"
                            style="color: #6B7280; font-weight: 500; font-size: 0.875rem;">Liên hệ Ban quản trị</a></li>
                    </ul>
                </div>
            </div>

            <!-- Dòng bản quyền cuối cùng -->
            <div class="pt-4 border-top d-flex flex-column flex-md-row justify-content-between align-items-center"
                style="border-top: 1px solid #F1F5F9; font-size: 13px; color: #94A3B8; gap: 1rem;">
                <p style="margin: 0;">© 2026 Trường Đại học Ngoại thương. Bảo lưu mọi quyền.</p>
                <div class="d-flex align-items-center" style="gap: 16px;">
                    <a href="/cgi-bin/koha/opac-oai.pl" target="_blank" style="color: #94A3B8; text-decoration: none;">OAI-PMH</a>
                    <span style="display: inline-block; width: 4px; height: 4px; background: #CBD5E1; border-radius: 50%;"></span>
                    <span>Vận hành trên nền tảng <a href="https://koha-community.org" target="_blank"
                        style="color: #64748B; text-decoration: none;">Koha &amp; DSpace</a></span>
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
 <span class="report_a_problem_text">Báo sự cố</span>
 </a>
 [% END %]

 [% IF Koha.Preference( 'CookieConsent' ) %]
 <a id="cookieConsentFooter" class="nav-link" href="#">
 <i class="fa fa-cookie fa-fw fa-icon-footer" aria-hidden="true"></i>
 <span class="cookieConsentFooter_text">Bộ nhớ đệm</span>
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
 <span class="koha_url_text">Vận hành bởi Koha</span>
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
[% KohaPlugins.get_plugins_opac_js | $raw %]

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
        if (href && !href.includes('/sso/koha-to-dspace')) {
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
