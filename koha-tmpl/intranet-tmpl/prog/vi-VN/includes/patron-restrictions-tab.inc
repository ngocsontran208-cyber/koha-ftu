[% USE raw %]
[% USE Koha %]
[% USE HtmlScrubber %]
[% PROCESS 'restriction-types.inc' %]

[% IF ( patron.restrictions.count == 0 ) %]
    <p>Bạn đọc hiện không bị hạn chế.</p>
[% ELSE %]
    <table>
        <thead>
            <tr>
                <th>Loại</th>
                <th>Ghi chú</th>
                <th>Ngày hết hạn</th>
                <th>Ngày tạo</th>
                [% IF CAN_user_borrowers_edit_borrowers && CAN_user_circulate_manage_restrictions %]
                    <th>&nbsp;</th>
                [% END %]
            </tr>
        </thead>
        <tbody>
            [% FOREACH restriction IN patron.restrictions %]
                <tr [% IF restriction.is_expired %]class="expired"[% END %]>
                    <td> [% PROCESS restriction_type_description restriction_type=restriction.type %] </td>
                    <td>
                        [% IF restriction.comment.search('OVERDUES_PROCESS') %]
                            <span>Hạn chế thêm bởi quy trình quá hạn [% restriction.comment.remove('OVERDUES_PROCESS ') | scrub_html type => 'comment' | $raw %]</span>
                        [% ELSE %]
                            [% restriction.comment | scrub_html type => 'comment' | $raw %]
                        [% END %]
                    </td>
                    <td>
                        [% IF restriction.expiration %]
                            [% restriction.expiration | $KohaDates %]
                            [% IF restriction.is_expired %](<span>Đã hết hạn</span>)[% END %]
                        [% ELSE %]
                            <em>Vô thời hạn</em>
                        [% END %]
                    </td>
                    <td>[% restriction.created | $KohaDates %]</td>
                    [% IF CAN_user_borrowers_edit_borrowers && CAN_user_circulate_manage_restrictions %]
                        <td>
                            <form method="post" action="/cgi-bin/koha/members/mod_debarment.pl">
                                [% INCLUDE 'csrf-token.inc' %]
                                <input type="hidden" name="op" value="cud-del" />
                                <input type="hidden" name="borrowernumber" value="[% patron.borrowernumber | uri %]" />
                                <input type="hidden" name="borrower_debarment_id" value="[% restriction.borrower_debarment_id | uri %]" />
                                <button type="submit" class="remove_restriction btn btn-default btn-xs"><i class="fa fa-trash-can"></i> Xóa</button>
                            </form>
                        </td>
                    [% END %]
                </tr>
            [% END %]
        </tbody>
    </table>
[% END %]
[% IF CAN_user_borrowers_edit_borrowers && CAN_user_circulate_manage_restrictions %]
    <p
        ><a href="#" id="add_manual_restriction"><i class="fa fa-plus"></i> Thêm hạn chế thủ công</a></p
    >
    <form method="post" action="/cgi-bin/koha/members/mod_debarment.pl" class="clearfix">
        [% INCLUDE 'csrf-token.inc' %]
        <input type="hidden" name="borrowernumber" value="[% patron.borrowernumber | html %]" />
        <input type="hidden" name="op" value="cud-add" />
        <fieldset class="rows" id="manual_restriction_form">
            <legend>Thêm hạn chế thủ công</legend>
            <ol>
                [% IF Koha.Preference('PatronRestrictionTypes') %]
                    <li>
                        <label for="debarred_type">Loại:</label>
                        <select name="debarred_type">
                            [% FOREACH restriction_type IN restriction_types %]
                                [% IF !restriction_type.is_system %]
                                    [% IF restriction_type.is_default %]
                                        <option value="[% restriction_type.code | html %]" selected>[% PROCESS restriction_type_description %]</option>
                                    [% ELSE %]
                                        <option value="[% restriction_type.code | html %]">[% PROCESS restriction_type_description %]</option>
                                    [% END %]
                                [% END %]
                            [% END %]
                        </select>
                    </li>
                [% END %]
                <li><label for="rcomment">Ghi chú:</label> <input type="text" id="rcomment" name="comment" /></li>
                <li>
                    <label for="rexpiration">Ngày hết hạn:</label>
                    <input name="expiration" id="rexpiration" size="20" value="" class="flatpickr" data-flatpickr-futuredate="true" type="text" />
                </li>
            </ol>
            <fieldset class="action"><input type="submit" value="Thêm hạn chế" /> <a href="#" class="cancel" id="cancel_manual_restriction">Hủy</a></fieldset>
        </fieldset>
    </form>
[% END %]
