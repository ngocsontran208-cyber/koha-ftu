<option value="relevance">Mức độ liên quan</option>

<optgroup label="Độ phổ biến">
 [% IF ( sort_by == "popularity_dsc" ) %]
 <option value="popularity_dsc" selected="selected">Độ phổ biến (từ cao đến thấp)</option>
 [% ELSE %]
 <option value="popularity_dsc">Độ phổ biến (từ cao đến thấp)</option>
 [% END %]
 [% IF ( sort_by == "popularity_asc" ) %]
 <option value="popularity_asc" selected="selected">Độ phổ biến (từ thấp đến cao)</option>
 [% ELSE %]
 <option value="popularity_asc">Độ phổ biến (từ thấp đến cao)</option>
 [% END %]
</optgroup>

<optgroup label="Tác giả">
 [% IF ( sort_by == "author_az" || sort_by == "author_asc" ) %]
 <option value="author_az" selected="selected">Tác giả (A-Z)</option>
 [% ELSE %]
 <option value="author_az">Tác giả (A-Z)</option>
 [% END %]
 [% IF ( sort_by == "author_za" || sort_by == "author_dsc" ) %]
 <option value="author_za" selected="selected">Tác giả (Z-A)</option>
 [% ELSE %]
 <option value="author_za">Tác giả (Z-A)</option>
 [% END %]
</optgroup>

<optgroup label="Số phân loại">
 [% IF ( sort_by == "call_number_asc" ) %]
 <option value="call_number_asc" selected="selected">Số phân loại (0-9 tới A-Z)</option>
 [% ELSE %]
 <option value="call_number_asc">Số phân loại (0-9 tới A-Z)</option>
 [% END %]

 [% IF ( sort_by == "call_number_dsc" ) %]
 <option value="call_number_dsc" selected="selected">Ký hiệu phân loại (Z-A tới 9-0)</option>
 [% ELSE %]
 <option value="call_number_dsc">Ký hiệu phân loại (Z-A tới 9-0)</option>
 [% END %]
</optgroup>

<optgroup label="Ngày">
 [% IF ( sort_by == "pubdate_dsc" ) %]
 <option value="pubdate_dsc" selected="selected">Xuất bản/Phát hành: Mới - Cũ</option>
 [% ELSE %]
 <option value="pubdate_dsc">Xuất bản/Phát hành: Mới - Cũ</option>
 [% END %]

 [% IF ( sort_by == "pubdate_asc" ) %]
 <option value="pubdate_asc" selected="selected">Xuất bản/Phát hành: Cũ - Mới</option>
 [% ELSE %]
 <option value="pubdate_asc">Xuất bản/Phát hành: Cũ - Mới</option>
 [% END %]

 [% IF ( sort_by == "acqdate_dsc" ) %]
 <option value="acqdate_dsc" selected="selected">Ngày bổ sung: Mới đến cũ</option>
 [% ELSE %]
 <option value="acqdate_dsc">Ngày bổ sung: Mới đến cũ</option>
 [% END %]

 [% IF ( sort_by == "acqdate_asc" ) %]
 <option value="acqdate_asc" selected="selected">Ngày bổ sung: Cũ đến mới</option>
 [% ELSE %]
 <option value="acqdate_asc">Ngày bổ sung: Cũ đến mới</option>
 [% END %]
</optgroup>

<optgroup label="Nhan đề">
 [% IF ( sort_by == "title_az" || sort_by == "title_asc" ) %]
 <option value="title_az" selected="selected">Nhan đề (A-Z)</option>
 [% ELSE %]
 <option value="title_az">Nhan đề (A-Z)</option>
 [% END %]
 [% IF ( sort_by == "title_za" || sort_by == "title_dsc" ) %]
 <option value="title_za" selected="selected">Nhan đề (Z-A)</option>
 [% ELSE %]
 <option value="title_za">Nhan đề (Z-A)</option>
 [% END %]
</optgroup>
