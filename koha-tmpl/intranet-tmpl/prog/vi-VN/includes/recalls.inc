[% USE Branches %]
<div id="recalls">
 [% IF recalls.count %]
 <table id="recalls-table">
 <thead>
 <tr>
 [% IF checkboxes %]<th class="recall-checkbox no-sort">&nbsp;</th>[% END %]
 <th class="recall-title anti-the">Nhan đề</th>
 [% UNLESS specific_patron %]<th class="recall-patron">Requested by</th>[% END %]
 <th class="recall-date">Ngày đặt hàng</th>
 <th class="recall-expiry">Ngày hết hạn</th>
 <th class="recall-branch">Địa điểm nhận sách</th>
 <th class="recall-status">Trạng thái</th>
 [% UNLESS viewing_old %]<th class="recall-duedate">Hạn trả</th>[% END %]
 [% UNLESS viewing_old %]<th class="recall-actions no-sort">&nbsp;</th>[% END %]
 </tr>
 </thead>

 <tbody>
 [% FOREACH recall IN recalls %]
 [% SET tr_class = recall.completed ? 'old' : '' %]
 <tr class="[% tr_class | html %]">
 [% IF checkboxes %]
 <td class="recall-checkbox">
 [% IF recall.completed %]
 &nbsp;
 [% ELSE %]
 <input type="checkbox" value="[% recall.id | html %]" name="recall_ids" />
 [% END %]
 </td>
 [% END %]

 <td class="recall-title">
 [% INCLUDE 'biblio-title.inc' biblio=recall.biblio link=1 %]
 [% IF recall.biblio.author %]by [% recall.biblio.author | html %][% END %]
 [% recall.item.enumchron | html %]
 [% IF ( recall.item ) %]<br /><em>Đăng ký cá biệt: [% recall.item.barcode | html %]</em>[% END %]
 </td>

 [% UNLESS specific_patron %]
 <td class="recall-patron"> [% INCLUDE 'patron-title.inc' patron=recall.patron hide_patron_infos_if_needed=1 link_to="circulation_recalls" %] </td>
 [% END %]

 <td class="recall-date" data-order="[% recall.created_date | html %]"> [% recall.created_date | $KohaDates %] </td>

 <td class="recall-expiry" data-order="[% recall.expiration_date | html %]">
 [% IF ( recall.expiration_date ) %]
 [% recall.expiration_date | $KohaDates %]
 [% ELSIF ( !recall.completed ) %]
 <span>Không bao giờ hết hạn</span>
 [% ELSE %]
 -
 [% END %]
 </td>

 <td class="recall-branch"> [% recall.library.branchname | html %] </td>

 <td class="recall-status">
 [% IF ( recall.in_transit ) %]
 <span>Đang chuyển đến [% recall.library.branchname | html %]</span>
 [% ELSIF ( recall.waiting ) %]
 <span>Sẵn sàng để nhận</span>
 [% ELSIF ( recall.expired ) %]
 <span>Đã hết hạn vào [% recall.expiration_date | $KohaDates %]</span>
 [% ELSIF ( recall.cancelled ) %]
 <span>Đã hủy vào [% recall.completed_date | $KohaDates %]</span>
 [% ELSIF ( recall.overdue ) %]
 <span>Đã quá hạn trả</span>
 [% ELSIF ( recall.fulfilled ) %]
 <span>Đã hoàn thành</span>
 [% ELSE %]
 <span>Đã yêu cầu</span>
 [% END %]
 </td>

 [% UNLESS viewing_old %]
 <td class="recall-duedate" data-order="[% recall.checkout.date_due | html %]">
 [% IF recall.requested and recall.checkout %]
 <span>Hạn phải trả vào ngày [% recall.checkout.date_due | $KohaDates %]</span>
 [% ELSIF recall.waiting and RECALL.expiration_date %]
 <span>Đến lấy trước ngày [% RECALL.expiration_date | $KohaDates %]</span>
 [% ELSE %]
 -
 [% END %]
 </td>
 [% END %]

 [% UNLESS viewing_old %]
 <td class="recall-cancel actions">
 [% IF recall.completed %]
 &nbsp;
 [% ELSE %]
 <div class="btn-group">
 <button type="button" class="btn btn-sm btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-haspopup="true" aria-expanded="false"> Thao tác </button>
 <ul class="dropdown-menu dropdown-menu-end">
 [% IF ( recall.requested or recall.overdue ) %]
 <li>
 <a class="cancel_recall dropdown-item" data-id="[% recall.id | html %]"><i class="fa fa-times"></i> Hủy bỏ</a>
 </li>
 [% IF ( recall.should_be_overdue ) %]
 <li
                                                        ><a class="overdue_recall dropdown-item" data-id="[% recall.id | html %]"><i class="fa fa-hourglass-end"></i> Mark as overdue</a>
 </li>
 [% END %]
 [% ELSIF ( recall.waiting ) %]
 <li>
 <a class="revert_recall dropdown-item" data-id="[% recall.id | html %]"><i class="fa fa-undo"></i> Revert waiting</a>
 </li>
 <li>
 <a class="expire_recall dropdown-item" data-id="[% recall.id | html %]"><i class="fa fa-times"></i> Expire</a>
 </li>
 [% ELSIF ( recall.in_transit ) %]
 <li>
 <a class="transit_recall dropdown-item" data-id="[% recall.id | html %]"><i class="fa fa-times"></i> Cancel recall and return to: [% Branches.GetName(recall.item.homebranch) | html %]</a>
 </li>
 [% END %]
 </ul>
 </div>
 [% END %]
 </td>
 [% END %]
 </tr>
 [% END %]
 </tbody>
 </table>
 [% ELSE %]
 [% IF patron.borrowernumber %]
 <div class="alert alert-info">Patron has no recalls.</div>
 [% ELSE %]
 <div class="alert alert-info">There are no recalls to show.</div>
 [% END %]
 [% END %]
</div>
