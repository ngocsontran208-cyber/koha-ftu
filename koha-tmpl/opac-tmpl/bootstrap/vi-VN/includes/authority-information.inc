[% FOREACH info IN information %]
 [% SWITCH info_type %]
 [% CASE 'identifiers' %]
 [% SWITCH info.source.lower %]
 [% CASE 'orcid' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>ORCID: </span>
 <a href="https://orcid.org/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'scopus' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>Scopus ID: </span>
 <a href="https://www.scopus.com/authid/detail.uri?authorId=[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'loop' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>Loop ID: </span>
 <a href="https://loop.frontiersin.org/people/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'rid' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>Tài liệu xuất bản: </span>
 <a href="https://publons.com/researcher/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'viaf' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>VIAF ID: </span>
 <a href="https://viaf.org/viaf/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'isni' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>ISNI ID: </span>
 <a href="https://isni.org/isni/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'wikidata' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>Wikidata ID: </span>
 <a href="https://www.wikidata.org/entity/[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% CASE 'uri' %]
 <li class="identifier_[% info.source.lower | html %]">
 <span>URI: </span>
 <a href="[% info.number | url %]">[% info.number | html %]</a>
 </li>
 [% END %]
 [% CASE 'activity' %]
 [% IF info.field_of_activity %]
 <li>
 <span>
 Lĩnh vực hoạt động: [% info.field_of_activity | html %] [% IF info.start_period || info.end_period %] ([%~ IF info.start_period %] từ: [% info.start_period | html %][% END %][% IF info.end_period %] đến: [% info.end_period | html %][% END ~%] ) [% END %] </span>
 </li>
 [% END %]
 [% CASE 'address' %]
 [% IF info.address %]
 <li>
 <span>Địa chỉ: [% info.address | html %] [% info.postal_code | html %] [% info.city | html %] [% info.country | html %]</span>
 </li>
 [% END %]
 [% CASE 'associated_group' %]
 [% IF info.associated_group %]
 <li>
 <span>
 Nhóm liên kết: [% info.associated_group | html %] [% IF info.start_period || info.end_period %] ( [%~ IF info.start_period %] từ: [% info.start_period | html %][% END %] [% IF info.end_period %] đến: [% info.end_period | html %][% END ~%] ) [% END %] [% IF info.uri %]<p style="margin-bottom: 0;">URL: [% info.uri | html %]</p>[% END %]
 [% IF info.source_of_information %]<p style="margin-bottom: 0;">Nguồn tham khảo: [% info.source_of_information | html %]</p>[% END %]
 [% IF info.authority_record_number %]<p style="margin-bottom: 0;">Số kiểm soát bản ghi chủ quyền hoặc số tiêu chuẩn: [% info.authority_record_number | html %]</p>[% END %]
 </span>
 </li>
 [% END %]
 [% CASE 'email_address' %]
 [% IF info.email_address %]
 <li>
 <span> Địa chỉ Email: [% info.email_address | html %] </span>
 </li>
 [% END %]
 [% CASE 'occupation' %]
 [% IF info.occupation %]
 <li>
 <span>
 Nghề nghiệp: [% info.occupation | html %][% IF info.start_period || info.end_period %] ( [%~ IF info.start_period %]từ: [% info.start_period | html %][% END %][% IF info.end_period %]đến:[% info.end_period | html %][% END ~%] ) [% END %][% IF info.uri %]<p style="margin-bottom: 0;">URL: [% info.uri | html %]</p>[% END %]
 [% IF info.source_of_information %]<p style="margin-bottom: 0;">Nguồn tham khảo: [% info.source_of_information | html %]</p>[% END %]
 [% IF info.authority_record_number %]<p style="margin-bottom: 0;">Số kiểm soát bản ghi chủ quyền hoặc số tiêu chuẩn: [% info.authority_record_number | html %]</p>[% END %]
 </span>
 </li>
 [% END %]
 [% CASE 'place_of_birth' %]
 [% IF info.place_of_birth %]
 <li>
 <span> Nơi sinh: [% info.place_of_birth | html %] </span>
 </li>
 [% END %]
 [% CASE 'place_of_death' %]
 [% IF info.place_of_death %]
 <li>
 <span> Nơi mất: [% info.place_of_death | html %] </span>
 </li>
 [% END %]
 [% CASE 'uri' %]
 [% IF info.uri %]
 <li>
 <span> URI: [% info.uri | $raw | html %] </span>
 </li>
 [% END %]
 [% END %]
[% END %]
