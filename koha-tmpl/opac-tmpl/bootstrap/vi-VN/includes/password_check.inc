[% USE Koha %]
[% USE raw %]
<script nonce="[% Koha.CSPNonce | $raw %]" data-tt-allowed="true">
    var pwd_title = "";
    var pattern_title = "";
    var new_password_node_name = "[% new_password | html %]";
    var category_selector = "[% category_selector | html %]";
    var STRONG_MSG = _("Mật khẩu phải chứa ít nhất %s ký tự, bao gồm CHỮ IN HOA, chữ thường và số");
    var WEAK_MSG = _("Mật khẩu phải chứa ít nhất %s ký tự");

    if(category_selector && $('select'+category_selector).length) {
        jQuery.validator.addMethod("password_strong", function(value, element){
            var require_strong = $('select'+category_selector+' option:selected').data('pwdStrong');
            var min_lenght = $('select'+category_selector+' option:selected').data('pwdLength');
            var regex_text = require_strong?"(?=.*\\d)(?=.*[a-z])(?=.*[A-Z]).{"+min_lenght+",}":".{"+min_lenght+",}";
            var pattern_regex = new RegExp(regex_text);
            return this.optional(element) || pattern_regex.test(value);
        }, function(unused, element) {
            var require_strong = $('select'+category_selector+' option:selected').data('pwdStrong');
            var min_lenght = $('select'+category_selector+' option:selected').data('pwdLength');
            return (require_strong?STRONG_MSG:WEAK_MSG).format(min_lenght)
        });
    } else {
        [% IF RequireStrongPassword %]
            pwd_title = STRONG_MSG.format([% minPasswordLength | html %]);
            pattern_regex = /(?=.*\d)(?=.*[a-z])(?=.*[A-Z]).{[% minPasswordLength | html %],}/;
        [% ELSIF minPasswordLength %]
            pwd_title = WEAK_MSG.format([% minPasswordLength | html %]);
            pattern_regex = /.{[% minPasswordLength | html %],}/;
        [% END %]
        jQuery.validator.addMethod("password_strong", function(value, element){
            return this.optional(element) || value == '****' || pattern_regex.test(value);
        }, pwd_title);
    }
    jQuery.validator.addMethod("password_no_spaces", function(value, element){
        return ( this.optional(element) || !value.match(/^\s/) && !value.match(/\s$/) );
    }, _("Mật khẩu chứa khoảng trắng ở đầu và/hoặc cuối"));
    jQuery.validator.addMethod("password_match", function(value, element){
        var new_password_node = $("input[name='" + new_password_node_name + "']:first");
        return value == $(new_password_node).val();
    }, _("Vui lòng nhập lại mật khẩu giống với mật khẩu đã nhập ở trên"));
</script>
