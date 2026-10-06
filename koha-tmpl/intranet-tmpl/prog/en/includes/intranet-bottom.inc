[% USE raw %]
[% USE Koha %]
[% USE KohaPlugins %]
[% USE Asset %]
[% USE AdditionalContents %]
[% IF Koha.Preference( 'CookieConsent' ) %]
    [% SET CookieConsentBar = AdditionalContents.get( location => "CookieConsentBar", lang => lang, library => branchcode || default_branch ) %]
    [% SET CookieConsentPopup = AdditionalContents.get( location => "CookieConsentPopup", lang => lang, library => branchcode || default_branch ) %]
    [% USE JSConsents %]
[% END %]



<span id="audio-alert"></span>

<!-- Cookie consent -->
[% IF Koha.Preference( 'CookieConsent' ) %]
    <!-- Cookie consent bar -->
    <div id="cookieConsentBar" aria-hidden="true">
        [% IF ( CookieConsentBar && CookieConsentBar.content && CookieConsentBar.content.count >0 ) %]
            <div id="cookieConsentBar_content">
                [%- FOREACH item IN CookieConsentBar.content -%]
                    [%- item.content | $raw -%]
                [%- END -%]
            </div>
        [% END %]
        <div class="consentButtons">
            [% IF ( JSConsents.all('staffConsent').size ) %]
                <button type="button" class="btn btn-primary consentAcceptAll">Accept all cookies</button>
            [% END %]
            <button type="button" class="btn btn-primary consentAcceptEssential">Accept essential cookies</button>
            <button type="button" class="btn btn-default" id="consentMoreInfo">More information</button>
        </div>
    </div>
    <!-- /#cookieConsentBar -->

    <!-- Cookie consent modal -->
    <div id="cookieConsentModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="cookieConsentModalLabel" aria-hidden="true">
        <div class="modal-dialog modal-lg">
            <div class="modal-content">
                <div class="modal-header">
                    <h1 class="modal-title" id="cookieConsentModalLabel">Cookies policy</h1>
                </div>
                <div class="modal-body">
                    [% IF ( CookieConsentPopup && CookieConsentPopup.content && CookieConsentPopup.content.count >0 ) %]
                        <div id="cookieConsentPopupText">
                            [%- FOREACH item IN CookieConsentPopup.content -%]
                                [%- item.content | $raw -%]
                            [%- END -%]
                        </div>
                    [% END %]
                    <div id="consentCookieList">
                        [% consents = JSConsents.all('staffConsent') %]
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
                    <div id="consentButtons">
                        <button type="button" class="btn btn-primary consentAcceptEssential">Accept essential cookies</button>
                        [% IF ( JSConsents.all('staffConsent').size ) %]
                            <button type="button" class="btn btn-primary consentAcceptAll">Accept all cookies</button>
                            <button type="button" class="btn btn-success" id="consentAcceptSelected">Accept selected non-essential cookies</button>
                        [% END %]
                        <button type="button" class="btn btn-secondary consentCloseModal">Cancel</button>
                    </div>
                </div>
            </div>
            <!-- /.modal-content -->
        </div>
        <!-- /.modal-dialog -->
    </div>
    <!-- /#cookieConsentModal  -->
[% END %]
<!-- CookieConsentedJS code that may run -->
[% IF Koha.Preference( 'CookieConsent' ) && JSConsents.all('staffConsent').size %]
    [% consents = JSConsents.all('staffConsent') %]
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
            data-requires-consent="[% consent.staffConsent ? 'true' : 'false' | html %]"
        ></div>
    [% END %]
[% END %]

[% IF ( footerjs ) %]
    [% INCLUDE js_includes.inc %]
    [% jsinclude | $raw # Parse the page template's JavaScript block if necessary %]
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
</body>
<!-- prettier-ignore-start -->
</html>
<!-- prettier-ignore-end -->
