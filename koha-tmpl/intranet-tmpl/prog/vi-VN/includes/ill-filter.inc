[% USE raw %]
[% USE Koha %]
[% PROCESS 'html_helpers.inc' %]
[% USE Branches %]

<form method="get" id="illfilter_form">
 <fieldset class="brief">
 <h3>Bộ lọc dữ liệu</h3>
 <ol>
 <li>
 <label for="illfilter_keyword">Từ khóa:</label>
 <input type="text" name="illfilter_keyword" id="illfilter_keyword" />
 </li>
 <li>
 <label for="illfilter_backend">Backend:</label>
 <select name="illfilter_backend" id="illfilter_backend">
 <option value="">All backends</option>
 </select>
 </li>
 <li>
 <label for="illfilter_status">Trạng thái:</label>
 <select name="illfilter_status" id="illfilter_status" multiple="multiple"> </select>
 </li>
 <li>
 <label for="illfilter_dateplaced_start">Date placed between:</label>
 <input type="text" name="illfilter_dateplaced_start" id="illfilter_dateplaced_start" class="flatpickr" data-date_to="illfilter_dateplaced_end" />
 </li>
 <li>
 <label for="illfilter_dateplaced_end">and:</label>
 <input type="text" name="illfilter_dateplaced_end" id="illfilter_dateplaced_end" class="flatpickr" />
 </li>
 <li>
 <label for="illfilter_datemodified_start">Updated between:</label>
 <input type="text" name="illfilter_datemodified_start" id="illfilter_datemodified_start" class="flatpickr" data-date_to="illfilter_datemodified_end" />
 </li>
 <li>
 <label for="illfilter_datemodified_end">and:</label>
 <input type="text" name="illfilter_datemodified_end" id="illfilter_datemodified_end" class="flatpickr" />
 </li>
 <li>
 <label for="illfilter_branchname">Thư viện:</label>
 <select name="illfilter_branchname" id="illfilter_branchname">
 <option value="">Tất cả thư viện</option>
 [% PROCESS options_for_libraries libraries => Branches.all( selected => userbranch, only_from_group => 1 ) %]
 </select>
 </li>
 <li>
 <label for="illfilter_patron">Bạn đọc đặt mượn:</label>
 <input type="text" name="illfilter_patron" id="illfilter_patron" />
 </li>
 <li>
 <label for="illfilter_managed_by">Người quản lý:</label>
 <input type="text" name="illfilter_managed_by" id="illfilter_managed_by" />
 </li>
 </ol>
 </fieldset>
 <fieldset class="action">
 <input class="btn btn-primary" type="submit" value="Tìm kiếm" />
 <input class="clear_search" type="button" value="Xóa" />
 </fieldset>
</form>
<!-- /#illfilter_form -->
