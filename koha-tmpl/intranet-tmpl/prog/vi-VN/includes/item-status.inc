[% USE AuthorisedValues %]
[% USE Branches %]
[% USE Koha %]
[% USE KohaDates %]

[% SET itemavailable = 1 %]

[% IF ( item.itemlost ) %]
 [% SET itemavailable = 0 %]
 [% itemlost_description = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.itemlost', authorised_value => item.itemlost ) %]
 [% IF ( itemlost_description ) %]
 <span class="item-status lost">[% itemlost_description | html %]</span>
 [% ELSE %]
 <span class="item-status lost">Bị mất thẻ</span>
 [% END %]
[% END %]

[% checkout = item.checkout %]
[% IF ( checkout ) %]
 [% SET itemavailable = 0 %]
 [% IF checkout.onsite_checkout %]
 <span class="item-status checkedout">Currently in local use by [% INCLUDE 'patron-title.inc' patron=checkout.patron hide_patron_infos_if_needed=1 %]</span>
 [% ELSE %]
 <span class="item-status checkedout">Checked out to [% INCLUDE 'patron-title.inc' patron=checkout.patron hide_patron_infos_if_needed=1 %]</span>
 [% END %]
 <span class="item-status due">Due: [% checkout.date_due | $KohaDates %]</span>
[% END %]

[% transfer = item.get_transfer %]
[% IF ( transfer.in_transit ) %]
 [% SET itemavailable = 0 %]
 <span class="item-status intransit">Đang chuyển từ [% Branches.GetName( transfer.frombranch ) | html %] sang [% Branches.GetName( transfer.tobranch ) | html %] từ ngày [% transfer.datesent | $KohaDates %]</span>
[% END %]

[% IF ( item.withdrawn ) %]
 [% SET itemavailable = 0 %]
 [% withdrawn_description = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.withdrawn', authorised_value => item.withdrawn ) %]
 [% IF withdrawn_description %]
 <span class="item-status withdrawn">[% withdrawn_description | html %]</span>
 [% ELSE %]
 <span class="item-status withdrawn">Loại khỏi lưu thông</span>
 [% END %]
[% END %]

[% IF ( item.effective_not_for_loan_status ) %]
 [% SET itemavailable = 0 %]
 [% notforloan_description = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.notforloan', authorised_value => item.effective_not_for_loan_status ) %]
 [% IF notforloan_description %]
 <span class="item-status notforloan">[% notforloan_description | html %]</span>
 [% ELSE %]
 <span class="item-status notforloan">Không cho mượn</span>
 [% END %]
[% END %]

[% IF ( item.damaged ) %]
 [% SET itemavailable = 0 %]
 [% damaged_description = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.damaged', authorised_value => item.damaged ) %]
 [% IF damaged_description %]
 <span class="item-status damaged">[% damaged_description | html %]</span>
 [% ELSE %]
 <span class="item-status damaged">Bị hư hỏng</span>
 [% END %]
[% END %]

[% IF item.has_pending_hold %]
 [% SET itemavailable = 0 %]
 <span class="item-status pendinghold">Đang chờ đặt trước</span>
[% END %]

[% hold = item.holds.next %]
[% IF hold %]
 [% IF hold.waitingdate %]
 [% SET itemavailable = 0 %]
 <span class="item-status holdwaiting">Waiting at [% Branches.GetName(hold.get_column('branchcode')) | html %] since [% hold.waitingdate | $KohaDates %].</span>
 [% ELSE %]
 <span class="item-status itemhold">Item-level hold (placed [% hold.reservedate | $KohaDates %]) for delivery at [% Branches.GetName(hold.get_column('branchcode')) | html %].</span>
 [% END %]
 [% IF Koha.Preference('canreservefromotherbranches') %]
 <span class="item-status holdfor">Hold for: [% INCLUDE 'patron-title.inc' patron=hold.borrower hide_patron_infos_if_needed=1 %]</span>
 [% END %]
[% END %]

[% IF ( itemavailable ) %]
 <span class="item-status available">Available</span>
[% END %]

[% IF ( item.restricted ) %]
 [% restricted_description = AuthorisedValues.GetDescriptionByKohaField( kohafield => 'items.restricted', authorised_value => item.restricted ) %]
 [% IF restricted_description %]
 <span class="item-status restricted">[% restricted_description | html %]</span>
 [% ELSE %]
 <span class="item-status restricted">Bị khóa tài khoản</span>
 [% END %]
[% END %]
