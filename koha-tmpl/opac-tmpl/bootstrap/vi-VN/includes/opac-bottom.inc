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
                <!-- Cột 1: Thương hiệu Thư viện FTU & Liên hệ (5/12) -->
                <div class="col-12 col-lg-5 mb-3 mb-lg-0 ftu-footer-brand-col">
                    <div class="d-flex align-items-center mb-3 ftu-footer-brand-wrap" style="gap: 12px;">
                        <img src="/opac-tmpl/bootstrap/images/ftu-logo.svg" alt="[% FTU_BRAND.logo_alt %]" style="height: 38px; width: auto;"
                            onerror="this.onerror=null; this.src='[% FTU_BRAND.logo_url %]'" />
                        <div>
                            <div class="ftu-footer-title" style="font-weight: 800; color: #0F172A; font-size: 0.98rem; line-height: 1.3; text-transform: uppercase;">
                                [% FTU_BRAND.library_name %]
                            </div>
                            <div class="ftu-footer-sub" style="font-size: 0.78rem; color: #64748B; font-weight: 500; margin-top: 2px;">
                                [% FTU_BRAND.campus_current %]
                            </div>
                        </div>
                    </div>

                    <div class="d-flex flex-column ftu-footer-contacts" style="gap: 8px; font-size: 0.84rem; color: #475569;">
                        <!-- Địa chỉ -->
                        <div class="d-flex align-items-start ftu-contact-item" style="gap: 10px;">
                            <i class="fa fa-location-dot" style="color: #b91c1c; font-size: 15px; margin-top: 3px; flex-shrink: 0;" aria-hidden="true"></i>
                            <div>
                                <strong style="color: #1E293B;">Địa chỉ:</strong>
                                <span> [% FTU_BRAND.campus_hcm_addr || 'Số 15, Đường D5, Phường 25, Quận Bình Thạnh, TP. Hồ Chí Minh' %]</span>
                            </div>
                        </div>

                        <!-- Điện thoại & Email nhanh trên Mobile -->
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

                        <!-- Giờ phục vụ -->
                        <div class="d-flex align-items-center ftu-contact-item" style="gap: 10px;">
                            <i class="fa fa-clock" style="color: #b91c1c; font-size: 14px; flex-shrink: 0;" aria-hidden="true"></i>
                            <div>
                                <strong style="color: #1E293B;">Giờ phục vụ:</strong>
                                <span> [% FTU_BRAND.hours_summary || 'Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 16:00' %]</span>
                            </div>
                        </div>

                        <!-- Mạng xã hội & Kênh kết nối: FB, YouTube, Web -->
                        <div class="ftu-social-connect-wrap mt-2 pt-2" style="border-top: 1px dashed #cbd5e1;">
                            <div class="d-flex flex-wrap align-items-center" style="gap: 8px;">
                                <span class="ftu-social-heading" style="font-size: 0.78rem; font-weight: 700; color: #64748b; text-transform: uppercase; letter-spacing: 0.5px; margin-right: 2px;">
                                    <i class="fa fa-share-alt" style="color: #b91c1c; font-size: 11px; margin-right: 3px;" aria-hidden="true"></i> Kết nối:
                                </span>
                                <a href="[% FTU_BRAND.link_facebook || 'https://www.facebook.com/ftu2.hcmc' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-pill ftu-pill-fb" title="Fanpage Facebook Thư viện Phân hiệu Trường ĐH Ngoại thương tại TP.HCM" aria-label="Facebook">
                                    <span class="ftu-social-icon-box"><i class="fa-brands fa-facebook-f fa fa-facebook-f" style="color: #ffffff !important;" aria-hidden="true"></i></span>
                                    <span class="ftu-social-text">Facebook</span>
                                </a>
                                <a href="[% FTU_BRAND.link_youtube || 'https://www.youtube.com/@FTUChannel' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-pill ftu-pill-yt" title="Kênh YouTube FTU Official" aria-label="YouTube">
                                    <span class="ftu-social-icon-box"><i class="fa-brands fa-youtube fa fa-youtube-play" style="color: #ffffff !important;" aria-hidden="true"></i></span>
                                    <span class="ftu-social-text">YouTube</span>
                                </a>
                                <a href="[% FTU_BRAND.link_portal || 'https://hcmc.ftu.edu.vn' %]" target="_blank" rel="noopener noreferrer" class="ftu-social-pill ftu-pill-web" title="Cổng thông tin điện tử Phân hiệu Trường ĐH Ngoại thương tại TP.HCM" aria-label="Website">
                                    <span class="ftu-social-icon-box"><i class="fa-solid fa-globe fa fa-globe" style="color: #ffffff !important;" aria-hidden="true"></i></span>
                                    <span class="ftu-social-text">Website</span>
                                </a>
                            </div>
                        </div>
                    </div>
                </div>

                <!-- Cột 2: Khám phá tài nguyên (3/12) - Mở sẵn trên máy tính, Accordion trên Mobile -->
                <div class="col-12 col-md-6 col-lg-3 mb-2 mb-lg-0">
                    <details class="ftu-footer-accordion" open>
                        <summary class="ftu-footer-summary">
                            <h4 class="ftu-footer-heading">
                                <span class="ftu-footer-heading-bar"></span>
                                Khám phá tài nguyên
                            </h4>
                            <i class="fa fa-chevron-down ftu-footer-chevron d-lg-none" aria-hidden="true"></i>
                        </summary>
                        <ul class="ftu-footer-list">
                            <li><a href="/cgi-bin/koha/opac-collections.pl" class="ftu-footer-link">Bộ sưu tập tài liệu số</a></li>
                            <li><a href="/cgi-bin/koha/opac-search.pl?idx=au" class="ftu-footer-link">Tìm kiếm theo Tác giả</a></li>
                            <li><a href="/cgi-bin/koha/opac-search.pl?idx=su" class="ftu-footer-link">Tìm kiếm theo Chủ đề</a></li>
                            <li><a href="/cgi-bin/koha/opac-course-reserves.pl" class="ftu-footer-link">Giáo trình &amp; Học phần</a></li>
                            <li><a href="[% FTU_BRAND.link_dspace %]" target="_blank" rel="noopener noreferrer" class="ftu-footer-link ftu-dspace-link">Kho tài liệu số DSpace <i class="fa fa-external-link-alt" style="font-size: 0.72rem; margin-left: 3px;"></i></a></li>
                        </ul>
                    </details>
                </div>

                <!-- Cột 3: Hỗ trợ & Dịch vụ (4/12) - Mở sẵn trên máy tính, Accordion trên Mobile -->
                <div class="col-12 col-md-6 col-lg-4 mb-2 mb-lg-0">
                    <details class="ftu-footer-accordion" open>
                        <summary class="ftu-footer-summary">
                            <h4 class="ftu-footer-heading">
                                <span class="ftu-footer-heading-bar"></span>
                                Hỗ trợ &amp; Dịch vụ
                            </h4>
                            <i class="fa fa-chevron-down ftu-footer-chevron d-lg-none" aria-hidden="true"></i>
                        </summary>
                        <ul class="ftu-footer-list">
                            <li><a href="/cgi-bin/koha/opac-user.pl" class="ftu-footer-link">Tài khoản &amp; Gia hạn sách</a></li>
                            <li><a href="[% FTU_BRAND.link_dspace %]/info/end-user-agreement" target="_blank" rel="noopener noreferrer" class="ftu-footer-link">Quy định bản quyền học thuật</a></li>
                            <li><a href="/cgi-bin/koha/opac-news-detail.pl?id=5" class="ftu-footer-link">Thông báo &amp; Lịch phục vụ</a></li>
                            <li><a href="/cgi-bin/koha/opac-reportproblem.pl" class="ftu-footer-link">Liên hệ Ban quản trị Thư viện</a></li>
                        </ul>
                    </details>
                </div>
            </div>

            <!-- Dòng bản quyền cuối cùng -->
            <div class="pt-3 border-top d-flex flex-column flex-md-row justify-content-between align-items-center ftu-footer-bottom-bar"
                style="border-top: 1px solid #E2E8F0 !important; font-size: 12px; color: #64748B; gap: 0.5rem;">
                <p style="margin: 0; color: #64748B; text-align: center;">[% FTU_BRAND.copyright_text %]</p>
                <div class="d-flex align-items-center" style="gap: 12px;">
                    <a href="/cgi-bin/koha/opac-oai.pl" target="_blank" style="color: #64748B; text-decoration: none; font-weight: 500;">OAI-PMH</a>
                    <span style="display: inline-block; width: 4px; height: 4px; background: #CBD5E1; border-radius: 50%;"></span>
                    <span>Vận hành trên nền tảng <a href="https://koha-community.org" target="_blank"
                        style="color: #b91c1c; font-weight: 600; text-decoration: none;">Koha &amp; DSpace</a></span>
                </div>
            </div>
        </div>

        <style>
            /* Kênh kết nối & Mạng xã hội chân trang - Thiết kế Pill Badge cao cấp */
            .ftu-social-pill {
                display: inline-flex !important;
                align-items: center !important;
                gap: 6px !important;
                padding: 4px 11px 4px 5px !important;
                border-radius: 20px !important;
                text-decoration: none !important;
                font-size: 0.78rem !important;
                font-weight: 600 !important;
                transition: all 0.22s ease-in-out !important;
                box-shadow: 0 1px 2px rgba(0, 0, 0, 0.05) !important;
                line-height: 1 !important;
            }
            .ftu-social-icon-box {
                display: inline-flex !important;
                align-items: center !important;
                justify-content: center !important;
                width: 24px !important;
                height: 24px !important;
                border-radius: 50% !important;
                flex-shrink: 0 !important;
            }
            .ftu-social-icon-box i,
            .ftu-social-icon-box .fa,
            .ftu-social-icon-box .fa-brands,
            .ftu-social-icon-box .fa-solid {
                color: #ffffff !important;
                font-size: 12px !important;
                line-height: 1 !important;
            }
            /* Facebook Pill */
            .ftu-pill-fb {
                background: #eff6ff !important;
                border: 1px solid #bfdbfe !important;
                color: #1d4ed8 !important;
            }
            .ftu-pill-fb .ftu-social-icon-box {
                background: #1877f2 !important;
            }
            .ftu-pill-fb:hover {
                background: #1877f2 !important;
                border-color: #1877f2 !important;
                color: #ffffff !important;
                transform: translateY(-2px) !important;
                box-shadow: 0 4px 10px rgba(24, 119, 242, 0.35) !important;
            }
            .ftu-pill-fb:hover .ftu-social-icon-box {
                background: rgba(255, 255, 255, 0.25) !important;
            }
            .ftu-pill-fb:hover .ftu-social-text {
                color: #ffffff !important;
            }
            /* YouTube Pill */
            .ftu-pill-yt {
                background: #fef2f2 !important;
                border: 1px solid #fecaca !important;
                color: #b91c1c !important;
            }
            .ftu-pill-yt .ftu-social-icon-box {
                background: #ef4444 !important;
            }
            .ftu-pill-yt:hover {
                background: #ef4444 !important;
                border-color: #ef4444 !important;
                color: #ffffff !important;
                transform: translateY(-2px) !important;
                box-shadow: 0 4px 10px rgba(239, 68, 68, 0.35) !important;
            }
            .ftu-pill-yt:hover .ftu-social-icon-box {
                background: rgba(255, 255, 255, 0.25) !important;
            }
            .ftu-pill-yt:hover .ftu-social-text {
                color: #ffffff !important;
            }
            /* Website Pill */
            .ftu-pill-web {
                background: #f0f9ff !important;
                border: 1px solid #bae6fd !important;
                color: #0369a1 !important;
            }
            .ftu-pill-web .ftu-social-icon-box {
                background: #0284c7 !important;
            }
            .ftu-pill-web:hover {
                background: #0284c7 !important;
                border-color: #0284c7 !important;
                color: #ffffff !important;
                transform: translateY(-2px) !important;
                box-shadow: 0 4px 10px rgba(2, 132, 199, 0.35) !important;
            }
            .ftu-pill-web:hover .ftu-social-icon-box {
                background: rgba(255, 255, 255, 0.25) !important;
            }
            .ftu-pill-web:hover .ftu-social-text {
                color: #ffffff !important;
            }

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
        if (href && !href.includes('/koha-to-dspace')) {
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
