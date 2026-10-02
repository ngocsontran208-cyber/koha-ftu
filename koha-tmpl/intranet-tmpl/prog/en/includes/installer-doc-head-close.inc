[% USE raw %]
[% USE Asset %]
<meta http-equiv="Content-Type" content="text/html; charset=utf-8" />
<link rel="icon" type="image/svg+xml" href="[% interface | html %]/[% theme | html %]/img/favicon.svg?v=ftu" />
<link rel="icon" type="image/png" sizes="32x32" href="[% interface | html %]/[% theme | html %]/img/favicon-32x32.png?v=ftu" />
<link rel="icon" type="image/png" sizes="16x16" href="[% interface | html %]/[% theme | html %]/img/favicon-16x16.png?v=ftu" />
<link rel="shortcut icon" href="[% IF ( IntranetFavicon ) %][% IntranetFavicon | html %][% ELSE %][% interface | html %]/[% theme | html %]/img/favicon.ico?v=ftu[% END %]" type="image/x-icon" />
[% IF ( bidi ) %]
    [% Asset.css("css/installer-rtl.css") | $raw %]
[% ELSE %]
    [% Asset.css("css/installer.css") | $raw %]
[% END %]
<script nonce="[% Koha.CSPNonce | $raw %]">
    var Koha = {};
</script>
[% IF lang && lang != 'en' %]
    [% Asset.js(lang _ '/js/locale_data.js') | $raw %]
[% END %]
[% Asset.js('js/Gettext.js') | $raw %]
[% Asset.js('js/i18n.js') | $raw %]
[% Asset.js('js/stores.js') | $raw %]
<style nonce="[% Koha.CSPNonce | $raw %]" id="antiClickjack">
    body {
        display: none !important;
    }
</style>
