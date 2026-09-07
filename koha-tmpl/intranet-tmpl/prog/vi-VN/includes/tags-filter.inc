<form method="get" action="/cgi-bin/koha/tags/review.pl">
 <fieldset class="brief">
 <h4>Bộ lọc dữ liệu</h4>
 <ol>
 <li> <label for="tag">Thuật ngữ:</label> <input type="text" name="tag" id="tag" value="[% filter_tag | html %]" /> </li>
 <li>
 <label for="approved">Trạng thái:</label>
 <select name="approved" id="approved">
 [% IF ( filter_approved_all ) %]
 <option selected="selected" value="all">Tất cả</option>
 [% ELSE %]
 <option value="all">Tất cả</option>
 [% END %]
 [% IF ( filter_approved_ok ) %]
 <option selected="selected" value="1">Chấp nhận</option>
 [% ELSE %]
 <option value="1">Chấp nhận</option>
 [% END %]
 [% IF ( filter_approved_pending ) %]
 <option selected="selected" value="0">Đang xử lý</option>
 [% ELSE %]
 <option value="0">Chờ duyệt</option>
 [% END %]
 [% IF ( filter_approved_rej ) %]
 <option selected="selected" value="-1">Bị từ chối</option>
 [% ELSE %]
 <option value="-1">Bị từ chối</option>
 [% END %]
 </select>
 </li>
 <li> <label for="approver">Reviewer:</label> <input type="text" name="approver" id="approver" value="[% filter_approver | html %]" /> </li>
 <li>
 <label for="from">Từ ngày: </label>
 <input type="text" size="10" id="from" name="from" value="[% filter_date_approved_from | html %]" class="flatpickr" data-date_to="to" />
 <div class="hint">[% INCLUDE 'date-format.inc' %]</div>

 <label for="to">Đến ngày: </label>
 <input type="text" size="10" id="to" name="to" value="[% filter_date_approved_to | html %]" class="flatpickr" />
 <div class="hint">[% INCLUDE 'date-format.inc' %]</div>
 </li>
 </ol>
 </fieldset>
 <fieldset class="action">
 <button type="submit" class="btn btn-primary"><i class="fa fa-filter" aria-hidden="true"></i> Tìm kiếm</button>
 </fieldset>
</form>
