[% USE Koha %]
[% PROCESS 'i18n.inc' %]
[% PROCESS "ill/backends/Standard/shared/form_input_helpers.inc" %]
[% IF whole.error %]
 [% IF whole.status == 'missing_identifier' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Trường định danh bắt buộc không được để trống. </div>
 [% ELSIF whole.status == 'missing_type' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Vui lòng không để trống trường Loại. </div>
 [% ELSIF whole.status == 'missing_unauth_data' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Dữ liệu bạn đọc (tên, họ và email) là các trường bắt buộc. </div>
 [% ELSIF whole.status == 'missing_branch' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Vui lòng không để trống trường Thư viện. </div>
 [% ELSIF whole.status == 'invalid_borrower' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Thông tin chi tiết bạn đọc bạn nhập không hợp lệ. </div>
 [% ELSIF whole.status == 'invalid_branch' %]
 <div class="alert alert-warning"> <strong>Chú ý:</strong> Thư viện bạn chọn không hợp lệ. </div>
 [% ELSIF whole.status == 'failed_captcha' %]
 <div class="alert alert-warning">Bạn đã nhập sai các ký tự trong ô trước khi gửi. Vui lòng thử lại.</div>
 [% ELSE %]
 <p>Lỗi chưa được xử lý</p>
 [% END %]
[% END %]
[% SET opac = whole.value.other.opac %]

[% IF whole.stage == "form" %]
 <h2>Tạo yêu cầu mượn liên thư viện</h2>
 <form id="create_form" method="POST" action="">
 [% INCLUDE 'csrf-token.inc' %]
 <fieldset class="rows">
 <legend>Tùy chọn bạn đọc</legend>
 <ol>
 [% IF unauthenticated_ill && !logged_in_user %]
 [% PROCESS ill_text_input_field required = 1 id = 'unauthenticated_first_name' label = t('First name') value = whole.value.other.unauthenticated_first_name %]
 [% PROCESS ill_text_input_field required = 1 id = 'unauthenticated_last_name' label = t('Last name') value = whole.value.other.unauthenticated_last_name %]
 [% PROCESS ill_text_input_field required = 1 id = 'unauthenticated_email' label = t('E-mail address') value = whole.value.other.unauthenticated_email %]
 [% END %]
 [% WRAPPER ill_select_field required = 1 id = 'branchcode' label = t('Destination library') %]
 <option value=""></option>
 [% FOREACH branch IN branches %]
 [% IF whole.value.other.branchcode && branch.branchcode == whole.value.other.branchcode %]
 <option value="[% branch.branchcode | html %]" selected="selected"> [% branch.branchname | html %] </option>
 [% ELSE %]
 <option value="[% branch.branchcode | html %]"> [% branch.branchname | html %] </option>
 [% END %]
 [% END %]
 [% END #ill_select_field %]
 </ol>
 </fieldset>
 <fieldset class="rows">
 <legend>Thông tin chung</legend>
 <ol id="general-standard-fields">
 [% WRAPPER ill_select_field required = 1 id = 'type' label = t('Type') %]
 <option value=""></option>
 [% IF whole.value.other.type.lower == "book" %]
 <option value="book" selected="selected">Sách</option>
 [% ELSE %]
 <option value="book">Sách</option>
 [% END %]
 [% IF whole.value.other.type.lower == "chapter" %]
 <option value="chapter" selected="selected">Ký tự</option>
 [% ELSE %]
 <option value="chapter">Ký tự</option>
 [% END %]
 [% IF whole.value.other.type.lower == "journal" %]
 <option value="journal" selected="selected">Tạp chí</option>
 [% ELSE %]
 <option value="journal">Tạp chí</option>
 [% END %]
 [% IF whole.value.other.type.lower == "article" %]
 <option value="article" selected="selected">Bài báo tạp chí</option>
 [% ELSE %]
 <option value="article">Bài báo tạp chí</option>
 [% END %]
 [% IF whole.value.other.type.lower == "thesis" %]
 <option value="thesis" selected="selected">Thesis</option>
 [% ELSE %]
 <option value="thesis">Thesis</option>
 [% END %]
 [% IF whole.value.other.type.lower == "conference" %]
 <option value="conference" selected="selected">Conference</option>
 [% ELSE %]
 <option value="conference">Conference</option>
 [% END %]
 [% IF whole.value.other.type.lower == "dvd" %]
 <option value="dvd" selected="selected">DVD</option>
 [% ELSE %]
 <option value="dvd">DVD</option>
 [% END %]
 [% IF whole.value.other.type.lower == "other" %]
 <option value="other" selected="selected">Other</option>
 [% ELSE %]
 <option value="other">Other</option>
 [% END %]
 [% IF whole.value.other.type.lower == "resource" %]
 <option value="resource" selected="selected">Tài nguyên chung</option>
 [% ELSE %]
 <option value="resource">Tài nguyên chung</option>
 [% END %]
 [% END #ill_select_field %]
 </ol>
 </fieldset>
 [% type = whole.value.other.type %]
 [% IF type %]
 [% INCLUDE "ill/backends/Standard/shared/forms/${type}.inc" %]
 [% END %]
 <legend>Thông tin bổ sung</legend>
 <fieldset class="rows">
 [% INCLUDE "ill/backends/Standard/shared/notes.inc" %]
 [% INCLUDE "ill/backends/Standard/shared/custom_fields.inc" %]
 </fieldset>
 [% IF whole.value.other.type && unauthenticated_ill && !logged_in_user %]
 <fieldset class="rows" id="illrequest_captcha">
 <legend>Xác minh</legend>
 <ol>
 <li>
 <label for="captcha" class="required">Xác minh:</label>

 <input required type="text" name="captcha" id="captcha" class="form-control input-fluid" style="text-transform: uppercase;" />
 <div class="required_label required">Bắt buộc</div>
 <input type="hidden" name="captcha_digest" value="[% captcha_digest | html %]" />

 <span class="hint">Vui lòng nhập các ký tự sau vào ô phía trên: <strong>[% captcha | html %]</strong></span>
 </li>
 </ol>
 </fieldset>
 [% END %]
 <fieldset class="action">
 <input id="ill-submit" class="btn btn-primary" type="submit" value="Create" />
 <a class="cancel" href="/cgi-bin/koha/opac-illrequests.pl">Hủy bỏ</a>
 </fieldset>
 [% IF (whole.value.other.copyrightclearance_confirmed) %]
 <input type="hidden" name="copyrightclearance_confirmed" value="1" />
 [% END %]
 <input type="hidden" name="op" value="cud-create" />
 <input type="hidden" name="stage" value="form" />
 <input type="hidden" name="backend" value="Standard" />
 </form>
[% ELSE %]
 <p>Unknown stage. This should not have happened. </p>
[% END %]
[% BLOCK backend_jsinclude %]
 <script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
        var core = [ [% whole.core | $raw %] ];
        // <![CDATA[]
        [% INCLUDE "ill/backends/Standard/shared/shared.js" %]
        // ]]>
    </script>
[% END %]
