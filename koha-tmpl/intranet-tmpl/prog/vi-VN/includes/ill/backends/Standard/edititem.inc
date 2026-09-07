[% USE raw %]
[% PROCESS "ill/backends/Standard/shared/form_input_helpers.inc" %]
[% IF whole.error %]
 [% IF whole.status == 'missing_type' %]
 <p><em>Please note:</em> Mandatory field 'type' is missing.</p>
 [% ELSE %]
 <p>Lỗi chưa được xử lý</p>
 [% END %]
[% END %]

[% IF whole.stage == "form" %]
 <h2>Edit ILL request item metadata</h2>
 <form id="standard_edit_form" method="POST" action="">
 [% INCLUDE 'csrf-token.inc' %]
 <fieldset class="rows">
 <legend>Thông tin chung</legend>
 <ol id="general-standard-fields">
 <li>
 <label class="required" for="type">Loại:</label>
 <select name="type" id="type">
 <option value="" />
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
 <option value="other" selected="selected">Báo cáo khác</option>
 [% ELSE %]
 <option value="other">Báo cáo khác</option>
 [% END %]
 [% IF whole.value.other.type.lower == "resource" %]
 <option value="resource" selected="selected">Tài nguyên chung</option>
 [% ELSE %]
 <option value="resource">Tài nguyên chung</option>
 [% END %]
 </select>
 </li>
 </ol>
 </fieldset>
 [% type = whole.value.other.type %]
 [% IF type %]
 [% INCLUDE "ill/backends/Standard/shared/forms/${type}.inc" %]
 [% END %]
 [% INCLUDE "ill/backends/Standard/shared/custom_fields.inc" %]
 <fieldset class="action">
 <input class="btn btn-primary" id="ill-submit" type="submit" value="Cập nhật" />
 <a class="cancel" href="/cgi-bin/koha/ill/ill-requests.pl?op=illview&amp;illrequest_id=[% whole.value.other.illrequest_id | html %]">Hủy bỏ</a>
 </fieldset>
 <input type="hidden" name="illrequest_id" value="[% whole.value.other.illrequest_id | html %]" />
 <input type="hidden" name="op" value="cud-edititem" />
 <input type="hidden" name="stage" value="form" />
 <input type="hidden" name="backend" value="Standard" />
 </form>
 [% BLOCK backend_jsinclude %]
 <script nonce="[% Koha.CSPNonce | $raw %]">
            var core = [ [% whole.core | $raw %] ];
            // <![CDATA[]
            [% INCLUDE "ill/backends/Standard/shared/shared.js" %]
            // ]]>
        </script>
 [% END %]
[% ELSE %]
 <p>Unknown stage. This should not have happened. </p>
[% END %]
