[% USE I18N %]
[% USE raw %]

[% MACRO t(msgid) BLOCK %]
    [%- IF msgid == 'Koha' -%]
        FTU - HCM LIB
    [%- ELSIF msgid == 'About Koha' -%]
        Giới thiệu FTU - HCM LIB
    [%- ELSIF msgid == 'Koha administration' -%]
        Quản trị FTU - HCM LIB
    [%- ELSE -%]
        [%- I18N.t(msgid) | $raw -%]
    [%- END -%]
[% END %]

[% MACRO tx(msgid, vars) BLOCK %]
    [%- IF msgid == 'Koha' -%]
        FTU - HCM LIB
    [%- ELSE -%]
        [%- I18N.tx(msgid, vars) | $raw -%]
    [%- END -%]
[% END %]

[% MACRO tn(msgid, msgid_plural, count) BLOCK %]
 [%- I18N.tn(msgid, msgid_plural, count) | $raw -%]
[% END %]

[% MACRO tnx(msgid, msgid_plural, count, vars) BLOCK %]
 [%- I18N.tnx(msgid, msgid_plural, count, vars) | $raw -%]
[% END %]

[% MACRO txn(msgid, msgid_plural, count, vars) BLOCK %]
 [%- I18N.txn(msgid, msgid_plural, count, vars) | $raw -%]
[% END %]

[% MACRO tp(msgctxt, msgid) BLOCK %]
 [%- I18N.tp(msgctxt, msgid) | $raw -%]
[% END %]

[% MACRO tpx(msgctxt, msgid, vars) BLOCK %]
 [%- I18N.tpx(msgctxt, msgid, vars) | $raw -%]
[% END %]

[% MACRO tnp(msgctxt, msgid, msgid_plural, count) BLOCK %]
 [%- I18N.tnp(msgctxt, msgid, msgid_plural, count) | $raw -%]
[% END %]

[% MACRO tnpx(msgctxt, msgid, msgid_plural, count, vars) BLOCK %]
 [%- I18N.tnpx(msgctxt, msgid, msgid_plural, count, vars) | $raw -%]
[% END %]
