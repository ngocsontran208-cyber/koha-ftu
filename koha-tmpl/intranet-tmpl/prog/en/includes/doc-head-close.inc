[% USE raw %]
[% USE Asset %]
[% USE Koha %]
[% USE KohaPlugins %]
[% USE String %]
[% PROCESS 'html_helpers.inc' %]
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<meta name="viewport" content="width=device-width, initial-scale=1" />
<meta name="csrf-token" content="[% Koha.GenerateCSRF | $raw %]" />
[% IF logged_in_user %]<meta name="generator" content="Koha [% Koha.Version.maintenance | html %]" />[% END %]
<script nonce="[% Koha.CSPNonce | $raw %]">
    window.__CSP_NONCE__ = "[% Koha.CSPNonce | $raw %]";
</script>
[%# Prevent XFS attacks -%]
[% UNLESS popup %]
    <style nonce="[% Koha.CSPNonce | $raw %]" id="antiClickjack">
        body {
            display: none !important;
        }
    </style>
[% END %]

<link rel="icon" type="image/svg+xml" href="[% interface | html %]/[% theme | html %]/img/favicon.svg?v=ftu" />
<link rel="icon" type="image/png" sizes="32x32" href="[% interface | html %]/[% theme | html %]/img/favicon-32x32.png?v=ftu" />
<link rel="icon" type="image/png" sizes="16x16" href="[% interface | html %]/[% theme | html %]/img/favicon-16x16.png?v=ftu" />
<link rel="apple-touch-icon" sizes="180x180" href="[% interface | html %]/[% theme | html %]/img/apple-touch-icon.png?v=ftu" />
<link rel="shortcut icon" href="[% IF ( IntranetFavicon ) %][% IntranetFavicon | html %][% ELSE %][% interface | html %]/[% theme | html %]/img/favicon.ico?v=ftu[% END %]" type="image/x-icon" />

[% IF ( bidi ) %]
    [% Asset.css("lib/jquery/jquery-ui-rtl-1.13.2.min.css") | $raw %]
[% ELSE %]
    [% Asset.css("lib/jquery/jquery-ui-1.13.2.min.css") | $raw %]
[% END %]
[% Asset.css("lib/datatables/datatables.min.css") | $raw %]
[% Asset.css("css/print.css", { media = "print" }) | $raw %]
[% INCLUDE intranetstylesheet.inc %]
<script nonce="[% Koha.CSPNonce | $raw %]" type="module">
    import { APIClient } from "/intranet-tmpl/prog/js/fetch/api-client.js";
    window.APIClient = APIClient;
</script>
<script nonce="[% Koha.CSPNonce | $raw %]">
    var Koha = {};
    [% IF CAN_user_parameters_manage_column_config %]
        var CAN_user_parameters_manage_column_config = 1;
    [% ELSE %]
        var CAN_user_parameters_manage_column_config = 0;
    [% END %]
</script>
[% IF lang && lang != 'en' %]
    [% Asset.js(lang _ '/js/locale_data.js') | $raw %]
[% END %]
[% Asset.js('js/Gettext.js') | $raw %]
[% Asset.js('js/i18n.js') | $raw %]
[% Asset.js('js/stores.js') | $raw %]

[% IF ( login ) %]
    [% Asset.css("css/login.css") | $raw %]
[% END %]

[% IF ( IntranetUserCSS ) %]
    <!-- prettier-ignore-start -->
    <style nonce="[% Koha.CSPNonce | $raw %]">[% IntranetUserCSS | $raw %]</style>
    <!-- prettier-ignore-end -->
[% END %]

<!-- FTU Global Branding CSS -->
[% Asset.css("css/ftu-global.css") | $raw %]

[% KohaPlugins.get_plugins_intranet_head | $raw %]

[% UNLESS ( footerjs ) %]
    [% INCLUDE js_includes.inc %]
[% END %]

<!-- FTU Enforce Brand Title & UI Script -->
<script nonce="[% Koha.CSPNonce | $raw %]">
(function() {
    function enforceFtuBrand() {
        try {
            if (document.title && /koha/i.test(document.title)) {
                document.title = document.title
                    .replace(/(?:\s*[›&rsaquo;>»]+\s*|\s+)Koha\b/gi, ' › FTU - HCM LIB')
                    .replace(/\bKoha\b/gi, 'FTU - HCM LIB');
            }
            var titleEl = document.querySelector('title');
            if (titleEl && /koha/i.test(titleEl.textContent)) {
                titleEl.textContent = titleEl.textContent
                    .replace(/(?:\s*[›&rsaquo;>»]+\s*|\s+)Koha\b/gi, ' › FTU - HCM LIB')
                    .replace(/\bKoha\b/gi, 'FTU - HCM LIB');
            }
        } catch(e) {}
    }
    enforceFtuBrand();
    if (document.readyState === 'loading') {
        document.addEventListener('DOMContentLoaded', enforceFtuBrand);
    }
    window.addEventListener('load', enforceFtuBrand);
    if (window.MutationObserver) {
        new MutationObserver(enforceFtuBrand).observe(document.head || document.documentElement, {
            subtree: true,
            childList: true,
            characterData: true
        });
    }
})();
</script>
