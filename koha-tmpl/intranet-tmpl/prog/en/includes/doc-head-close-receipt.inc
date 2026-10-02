[% USE raw %]
[% USE Asset %]
<link rel="icon" type="image/svg+xml" href="[% interface | html %]/[% theme | html %]/img/favicon.svg?v=ftu" />
<link rel="icon" type="image/png" sizes="32x32" href="[% interface | html %]/[% theme | html %]/img/favicon-32x32.png?v=ftu" />
<link rel="icon" type="image/png" sizes="16x16" href="[% interface | html %]/[% theme | html %]/img/favicon-16x16.png?v=ftu" />
<link rel="shortcut icon" href="[% IF ( IntranetFavicon ) %][% IntranetFavicon | html %][% ELSE %][% interface | html %]/[% theme | html %]/img/favicon.ico?v=ftu[% END %]" type="image/x-icon" />
[% Asset.css("css/print.css", { media = "print" }) | $raw %]
