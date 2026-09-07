<div id="toolbar" class="btn-toolbar">
 [% IF ( budget_period_id ) %]
 <div class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false"><i class="fa fa-plus"></i> Mới</button>
 <ul class="dropdown-menu">
 <li><a class="dropdown-item" href="/cgi-bin/koha/admin/aqbudgetperiods.pl?op=add_form">Ngân sách</a></li>
 [% IF ( budget_period_locked || !CAN_user_acquisition_budget_add_del ) %]
 <li data-bs-toggle="tooltip" data-bs-placement="left" title="The budget is locked">
 <a class="dropdown-item disabled" aria-disabled="true" href="#">Quỹ cho [% budget_period_description | html %]</a>
 </li>
 [% ELSE %]
 <li>
 <a class="dropdown-item" href="/cgi-bin/koha/admin/aqbudgets.pl?op=add_form&amp;budget_period_id=[% budget_period_id | uri %]">Quỹ cho [% budget_period_description | html %]</a>
 </li>
 [% END %]
 </ul>
 </div>

 <div class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false"><i class="fa-solid fa-pencil" aria-hidden="true"></i> Sửa</button>
 <ul class="dropdown-menu">
 <li><a class="dropdown-item" href="/cgi-bin/koha/admin/aqbudgetperiods.pl?op=add_form&amp;budget_period_id=[% budget_period_id | uri %]">Chỉnh sửa [% budget_period_description | html %]</a></li>
 <li><a class="dropdown-item" href="/cgi-bin/koha/admin/aqbudgetperiods.pl?op=duplicate_form&amp;budget_period_id=[% budget_period_id | uri %]">Sao chép [% budget_period_description | html %]</a></li>
 </ul>
 </div>

 <div class="btn-group">
 <button class="btn btn-default dropdown-toggle" data-bs-toggle="dropdown" aria-expanded="false"><i class="fa-solid fa-pencil" aria-hidden="true"></i> Lịch phát hành</button>
 <ul class="dropdown-menu">
 <li>
 [% IF ( CAN_user_acquisition_planning_manage ) %]
 <a class="dropdown-item" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=MONTHS">Phân bổ theo tháng</a>
 [% ELSE %]
 <a class="dropdown-item disabled" aria-disabled="true" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=MONTHS">Phân bổ theo tháng</a>
 [% END %]
 </li>
 <li>
 [% IF ( CAN_user_acquisition_planning_manage ) %]
 <a class="dropdown-item" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=BRANCHES">Phân bổ theo thư viện</a>
 [% ELSE %]
 <a class="dropdown-item disabled" aria-disabled="true" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=BRANCHES">Phân bổ theo thư viện</a>
 [% END %]
 </li>
 <li>
 [% IF ( CAN_user_acquisition_planning_manage ) %]
 <a class="dropdown-item" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=ITEMTYPES">Phân bổ theo kiểu tài liệu</a>
 [% ELSE %]
 <a class="dropdown-item disabled" aria-disabled="true" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=ITEMTYPES">Phân bổ theo kiểu tài liệu</a>
 [% END %]
 </li>
 [% FOREACH auth_cats_loo IN auth_cats_loop %]
 <li>
 [% IF ( CAN_user_acquisition_planning_manage ) %]
 <a class="dropdown-item" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=[% auth_cats_loo | uri %]">Phân bổ theo [% auth_cats_loo | html %]</a>
 [% ELSE %]
 <a class="dropdown-item disabled" aria-disabled="true" href="/cgi-bin/koha/admin/aqplan.pl?budget_period_id=[% budget_period_id | uri %]&amp;authcat=[% auth_cats_loo | uri %]"
                                >Phân bổ theo [% auth_cats_loo | html %]</a
                            >
 [% END %]
 </li>
 [% END %]
 </ul>
 </div>
 [% ELSE %]
 <div class="btn-group"
            ><a class="btn btn-default" id="newrootbudget" href="/cgi-bin/koha/admin/aqbudgetperiods.pl?op=add_form"><i class="fa fa-plus"></i> Ngân sách</a></div
        >
 [% END %]
</div>
