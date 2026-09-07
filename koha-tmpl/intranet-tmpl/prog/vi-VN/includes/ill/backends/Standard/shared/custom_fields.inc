[% USE Koha %]
[% USE raw %]
<fieldset class="rows">
 <legend>Custom fields</legend>
 <ol id="standard-fields">
 [% keys = whole.value.other.custom_key.split('\0') %]
 [% values = whole.value.other.custom_value.split('\0') %]
 [% i = 0 %]
 [% FOREACH key IN keys %]
 <li class="form-horizontal">
 [% IF opac %]
 <input type="text" placeholder="key" class="form-control input-fluid custom-field-input custom-name" name="custom_key" value="[% key | html %]" />
 <input class="form-control input-fluid custom-field-input" id="custom-value" name="custom_value" placeholder="Giá trị" type="text" value="[% values.$i | html %]" />
 [% ELSE %]
 <input type="text" placeholder="key" class="custom-name" name="custom_key" value="[% key | html %]" />
 <input id="custom-value" name="custom_value" placeholder="Giá trị" type="text" value="[% values.$i | html %]" />
 [% END %]
 <button value="[% i | html %]" name="custom_delete" type="submit" class="btn btn-danger btn-sm delete-new-field"> <span class="fa fa-trash"></span> Xóa </button>
 </li>
 [% i = i + 1 %]
 [% END %]
 </ol>
 <div id="custom-warning" style="display:none;margin:1em;" class="error required"></div>
 <button type="button" id="add-new-fields" class="btn btn-default">
 <span class="fa fa-plus"></span>
 Thêm trường tìm kiếm </button>
</fieldset>

<style nonce="[% Koha.CSPNonce | $raw %]">
    .custom-field-input {
        width: 25%;
        display: inline-block;
        margin-left: 0.5em;
    }
</style>
