[% USE Koha %]
[% USE Branches %]
[% USE Categories %]
[% USE Notices %]
[% USE AuthorisedValues %]
[% USE NoticeTemplates %]
[% USE scalar %]
<div id="toolbar" class="btn-toolbar">
 [% IF CAN_user_borrowers_edit_borrowers %]
 <a id="editpatron" class="btn btn-default" href="/cgi-bin/koha/members/memberentry.pl?op=edit_form&amp;destination=circ&amp;borrowernumber=[% patron.borrowernumber | html %]"
            ><i class="fa-solid fa-pencil" aria-hidden="true"></i> Sửa</a
        >
 [% END %]
 [% SET guarantee_categories = Categories.limited( can_be_guarantee => 1 ).unblessed %]
 [% IF CAN_user_borrowers_edit_borrowers %]
 [% IF patron.is_adult AND Koha.Preference("borrowerRelationship") %]
 [% IF guarantee_categories.size > 1 %]
 <div id="addchild" class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false"><i class="fa fa-plus"></i> Thêm người được bảo lãnh</button>
 <ul class="dropdown-menu">
 [% FOREACH cat IN guarantee_categories %]
 <li
                                ><a class="dropdown-item" href="/cgi-bin/koha/members/memberentry.pl?op=add_form&amp;guarantor_id=[% patron.borrowernumber | html %]&categorycode=[% cat.categorycode | html %]"
                                    >[% cat.description | html %]</a
                                ></li
                            >
 [% END %]
 </ul>
 </div>
 [% ELSE %]
 <a id="addchild" class="btn btn-default" href="/cgi-bin/koha/members/memberentry.pl?op=add_form&amp;guarantor_id=[% patron.borrowernumber | html %]"><i class="fa fa-plus"></i> Thêm người được bảo lãnh</a>
 [% END %]
 [% END %]
 <a id="changepassword" class="btn btn-default" href="/cgi-bin/koha/members/member-password.pl?member=[% patron.borrowernumber | html %]"><i class="fa fa-lock"></i> Đổi mật khẩu</a>
 <a id="duplicate" class="btn btn-default" href="/cgi-bin/koha/members/memberentry.pl?op=duplicate&amp;borrowernumber=[% patron.borrowernumber | html %]"><i class="fa fa-copy"></i> Sao chép</a>
 [% END %]

 [% IF CAN_user_circulate_circulate_remaining_permissions %]
 <div class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false"><i class="fa fa-print"></i> In</button>
 <ul class="dropdown-menu">
 <li><a class="dropdown-item printslip" data-code="printsummary" href="#">Thông tin tài khoản</a></li>
 <li><a class="dropdown-item printslip" data-code="issueslip" href="#">Thông tin ghi mượn</a></li>
 <li><a class="dropdown-item printslip" data-code="issueqslip" href="#">Ghi mượn trong ngày</a></li>
 [% IF patron.account_balance != 0 %]
 <li><a class="dropdown-item printslip" data-code="accounts_summary" id="printfineslip" href="#">In số dư tài khoản</a></li>
 [% END %]
 [% IF patron.has_overdues %]
 <li><a class="dropdown-item" id="print_overdues" href="#">In thông báo quá hạn</a></li>
 [% END %]
 [% IF patron.privacy < 2 %]
 [%# 2 is the privacy rule "Never" (Delete my history immediately) %]
 <li><a class="dropdown-item printslip" data-code="checkinslip" href="#">In phiếu ghi trả</a></li>
 [% END %]
 [% FOREACH notice IN Notices.GetTemplates( 'patron_slip' ) %]
 <li><a class="dropdown-item printslip" data-code="[% notice.code | html %]" href="#">In [% notice.name | html %]</a></li>
 [% END %]
 </ul>
 </div>
 [% END %]

 [% IF ( CAN_user_reserveforothers ) %]
 <a id="searchtohold" class="btn btn-default" href="#"><i class="fa fa-search"></i> Tìm kiếm</a>
 [% END %]

 [% IF CAN_user_borrowers_edit_borrowers %]
 <a id="toolbar_addnewmessageLabel" href="#add_message_form" data-bs-toggle="modal" class="btn btn-default"><i class="fa-solid fa-comment"></i> Thêm tin nhắn</a>
 [% END %]

 [% IF Koha.Preference('CurbsidePickup') %]
 <a id="curbsidePickupLabel" href="/cgi-bin/koha/circ/curbside_pickups.pl?op=find-patron&borrowernumber=[% patron.borrowernumber | html %]" class="btn btn-default"><i class="fa-solid fa-rotate"></i> Đặt lịch hẹn nhận sách</a>
 [% END %]

 [% IF CAN_user_borrowers_edit_borrowers %]
 <div class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown">Thêm <span class="caret"></span></button>
 <ul class="dropdown-menu dropdown-menu-end">
 [% IF CAN_user_borrowers_edit_borrowers %]
 <li>
 <a class="dropdown-item" id="renewpatron" href="/cgi-bin/koha/members/setstatus.pl?borrowernumber=[% patron.borrowernumber | html %]&amp;destination=[% destination | html %]&amp;reregistration=y">Gia hạn tài khoản</a>
 </li>
 [% ELSE %]
 <li data-bs-placement="left" data-bs-toggle="tooltip" title="Bạn không được phân quyền để gia hạn tài khoản bạn đọc">
 <a class="dropdown-item disabled" aria-disabled="true" id="renewpatron" href="#">Gia hạn tài khoản</a>
 </li>
 [% END %]
 [% IF ( CAN_user_permissions ) %]
 <li>
 <a class="dropdown-item" id="patronflags" href="/cgi-bin/koha/members/member-flags.pl?member=[% patron.borrowernumber | html %]">Phân quyền người dùng</a>
 </li>
 [% ELSE %]
 <li data-bs-placement="left" data-bs-toggle="tooltip" title="Bạn không được phân quyền để phân quyền chức năng cho bạn đọc">
 <a class="dropdown-item disabled" aria-disabled="true" id="patronflags" href="#">Phân quyền người dùng</a>
 </li>
 [% END %]
 [% IF ( Koha.Preference('TwoFactorAuthentication') == 'enforced' || Koha.Preference('TwoFactorAuthentication') == 'enabled' ) && ( logged_in_user.borrowernumber == patron.borrowernumber || logged_in_user.is_superlibrarian ) %]
 <li><a class="dropdown-item" id="twofa" href="/cgi-bin/koha/members/two_factor_auth.pl?borrowernumber=[% patron.borrowernumber | uri %]">Quản lý xác thực hai yếu tố</a></li>
 [% END %]

 [% IF CAN_user_borrowers_edit_borrowers && useDischarge %]
 <li><a class="dropdown-item" href="/cgi-bin/koha/members/discharge.pl?borrowernumber=[% patron.borrowernumber | uri %]">Xác nhận thanh toán mượn trả</a></li>
 [% END %]

 [% IF Koha.Preference('RESTOAuth2ClientCredentials') %]
 [% IF CAN_user_superlibrarian OR loggedinusernumber == patron.borrowernumber %]
 <li>
 <a class="dropdown-item" id="apikeys" href="/cgi-bin/koha/members/apikeys.pl?patron_id=[% patron.borrowernumber | html %]">Quản lý khóa API</a>
 </li>
 [% ELSE %]
 <li data-bs-toggle="tooltip" data-bs-placement="left" title="Bạn không được phân quyền để quản lý khóa API">
 <a class="dropdown-item disabled" aria-disabled="true" id="apikeys" href="#">Quản lý khóa API</a>
 </li>
 [% END %]
 [% END %]

 [% IF CAN_user_borrowers_edit_borrowers %]
 <li>
 <a class="dropdown-item" id="sendwelcome" href="/cgi-bin/koha/members/notices.pl?borrowernumber=[% patron.borrowernumber | uri %]&op=send_welcome">Gửi thông báo chào mừng</a>
 </li>
 [% END %]

 [% IF CAN_user_borrowers_edit_borrowers && patron.category.effective_reset_password %]
 <li><a class="dropdown-item" id="resetpassword" href="/cgi-bin/koha/members/notices.pl?borrowernumber=[% patron.borrowernumber | uri %]&op=send_password_reset">Gửi thông báo đặt lại mật khẩu</a></li>
 [% END %]

 [% IF CAN_user_borrowers_delete_borrowers %]
 [% IF ( patron.protected == 1 ) %]
 <li data-bs-toggle="tooltip" data-bs-placement="left" title="Bạn đọc được bảo vệ">
 <a class="dropdown-item disabled" aria-disabled="true" id="deletepatron" href="#">Xóa</a>
 </li>
 [% ELSE %]
 <li>
 <a class="dropdown-item" id="deletepatron" href="#">Xóa</a>
 </li>
 [% END %]
 [% ELSE %]
 <li aria-disabled="true" data-bs-placement="left" data-bs-toggle="tooltip" title="Bạn không được phân quyền để xóa tài khoản bạn đọc">
 <a class="dropdown-item disabled" id="deletepatron" href="#">Xóa</a>
 </li>
 [% END %]

 [% SET adult_categories = Categories.scalar.all(category_type => 'A') %]
 [% IF adult_categories.count > 0 %]
 [% IF patron.is_child %]
 <li>
 <a class="dropdown-item" id="updatechild" href="#">Cập nhật Trẻ em - Người lớn</a>
 </li>
 [% ELSE %]
 <li data-bs-placement="left" data-bs-toggle="tooltip" title="Bạn đọc là người lớn">
 <a href="#" class="dropdown-item disabled" aria-disabled="true" id="updatechild">Cập nhật Trẻ em - Người lớn</a>
 </li>
 [% END %]
 [% END %]
 [% IF CAN_user_borrowers_view_checkout_history && Koha.Preference('intranetreadinghistory') %]
 [% IF ( patron.privacy == 2 ) %]
 <li data-bs-toggle="tooltip" data-bs-placement="left" title="Không được phép theo cài đặt bảo mật của bạn đọc">
 <a class="dropdown-item disabled" aria-disabled="true" id="exportbarcodes" href="#">Xuất dữ liệu ghi mượn trong ngày</a>
 </li>
 [% ELSE %]
 <li>
 <a class="dropdown-item" id="exportcheckins" href="#">Xuất dữ liệu ghi mượn trong ngày</a>
 </li>
 [% END %]
 [% END %]
 </ul>
 </div>
 [% END %]
</div>

<!-- Modal -->
<div id="add_message_form" class="modal" tabindex="-1" role="dialog" aria-labelledby="addnewmessageLabel toolbar_addnewmessageLabel" aria-hidden="true">
 <div class="modal-dialog modal-lg">
 <div class="modal-content modal-lg">
 <form method="post" action="/cgi-bin/koha/circ/add_message.pl" id="message_form" name="message_f">
 [% INCLUDE 'csrf-token.inc' %]
 <input type="hidden" name="op" value="cud-add_message" />
 <div class="modal-header">
 <h1 class="modal-title">Tạo tin nhắn</h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <div class="modal-body">
 <fieldset id="message_fieldset">
 <ol>
 <li class="form-group form-row">
 <label for="message_type" class="col-form-label">Gửi tin nhắn cho:</label>
 <select name="message_type" id="message_type" class="form-select">
 <option value="L">Nhân viên - Ghi chú nội bộ</option>
 <option value="B">OPAC - [% patron.firstname | html %] [% patron.surname | html %]</option>
 [% IF CAN_user_borrowers_send_messages_to_borrowers_email %]
 <option value="E">Email - địa chỉ email của bạn đọc</option>
 [% END %]
 [% IF Koha.Preference("SMSSendDriver") && CAN_user_borrowers_send_messages_to_borrowers_sms %]
 <option value="SMS">SMS - số sms của bạn đọc</option>
 [% END %]
 </select>
 </li>

 [% bor_notes = AuthorisedValues.Get( 'BOR_NOTES' ) %]
 [% IF bor_notes %]
 <li class="form-group form-row">
 <label for="select_patron_messages" class="col-form-label">Chọn tin nhắn mẫu có sẵn (tùy chọn): </label>
 <select name="type" id="select_patron_messages" class="form-select">
 <option value="">-- Chọn tin nhắn mẫu hoặc tự nhập nội dung bên dưới --</option>
 [% FOREACH bor_note IN bor_notes %]
 <option value="[% bor_note.lib | html %]">[% bor_note.lib | html %]</option>
 [% END %]
 </select>
 </li>
 [% END %]

 [% patron_letters = NoticeTemplates.GetByModuleForLibrary( 'add_message' ) %]
 [% IF patron_letters %]
 <li class="form-group form-row">
 <label for="select_patron_notice" class="col-form-label" style="display:none;">Thông báo bạn đọc: </label>
 <select name="select_patron_notice" id="select_patron_notice" class="form-select" style="display:none;">
 <option value="">Chọn thông báo</option>
 [% FOREACH letter IN patron_letters %]
 <option value="[% letter.code | html %]">[% letter.name | html %]</option>
 [% END %]
 </select>
 </li>
 [% END %]

 <li class="form-group form-row" id="subject_form" style="display: none;">
 <label for="borrower_subject" class="col-form-label">Chủ đề:</label>
 <input type="text" size="60" name="borrower_subject" class="form-control" id="borrower_subject" />
 </li>
 <li class="form-group form-row">
 <label for="borrower_message" class="col-form-label" style="font-weight: 600;">Nội dung tin nhắn (*):</label>
 <textarea cols="65" rows="4" name="borrower_message" class="form-control" id="borrower_message" required placeholder="Nhập nội dung tin nhắn gửi tới bạn đọc tại đây..."></textarea>
 </li>
 </ol>
 </fieldset>
 <input type="hidden" name="borrowernumber" value="[% patron.borrowernumber | html %]" />
 <input type="hidden" name="batch" value="[% batch | html %]" />
 <input type="hidden" name="branchcode" value="[% Branches.GetLoggedInBranchcode | html %]" />
 </div>
 <div class="modal-footer">
 <button class="btn btn-default approve" type="submit"><i class="fa fa-check"></i> Lưu</button>
 <button class="btn btn-default deny cancel" type="button" data-bs-dismiss="modal"><i class="fa fa-times"></i> Hủy bỏ</button>
 </div>
 </form>
 </div>
 </div>
</div>
