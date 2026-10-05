[% USE KohaDates %]
[% USE Branches %]
[% IF patron_messages.filter_by_unread.count OR opacnote %]
 <div class="alert alert-info patron-message-box" style="background: #f0f7ff; border: 1px solid #b8daff; border-left: 5px solid #0056b3; border-radius: 8px; padding: 16px 20px; margin-bottom: 24px; box-shadow: 0 2px 8px rgba(0,0,0,0.04);">
 <h3 style="color: #004085; font-size: 1.15rem; margin-top: 0; margin-bottom: 12px; display: flex; align-items: center; gap: 8px;">
     <i class="fa fa-bell" style="color: #0056b3;"></i> 
     <span>Thông báo & Tin nhắn từ FTU - HCMC ([% patron_messages.filter_by_unread.count | html %])</span>
 </h3>
 <ul style="list-style: none; padding-left: 0; margin-bottom: 0;">
 [% FOREACH message IN patron_messages.filter_by_unread %]
 <li style="background: #ffffff; border: 1px solid #e2e8f0; border-radius: 6px; padding: 12px 16px; margin-bottom: 10px; display: flex; justify-content: space-between; align-items: center; flex-wrap: wrap; gap: 10px;">
   <div style="flex: 1; min-width: 250px;">
     <div style="font-size: 1rem; color: #1e293b; font-weight: 500; line-height: 1.5;">[% message.message | html | html_line_break %]</div>
     <div style="font-size: 0.82rem; color: #64748b; margin-top: 4px;">
       <i class="fa fa-clock-o"></i> [% message.message_date | $KohaDates %] &bull; <span class="badge border border-primary text-primary bg-white px-2 py-0.5" style="font-weight: 500;">[% Branches.GetName(message.branchcode) | html %]</span>
     </div>
   </div>
 [% IF sco != "true" %]
 <form id="dismiss-message-form-[% message.message_id | html %]" class="d-print-none" action="/cgi-bin/koha/opac-dismiss-message.pl" method="post" style="margin: 0;">
 [% INCLUDE 'csrf-token.inc' %]
 <input type="hidden" name="message_id" value="[% message.message_id | html %]" />
 <input type="hidden" name="op" value="cud-update" />
 <button type="submit" class="dismiss-message-button btn btn-outline-secondary btn-sm" style="font-size: 0.82rem; white-space: nowrap;"><i class="fa fa-check" aria-hidden="true"></i> Đã đọc / Đóng</button>
 </form>
 [% END %]
 </li>
 [% END %]

 [% IF ( opacnote ) %]
 <li style="background: #ffffff; border: 1px solid #e2e8f0; border-radius: 6px; padding: 12px 16px; margin-bottom: 10px; color: #1e293b;">
   [% opacnote | html | html_line_break %]
 </li>
 [% END %]
 </ul>
 </div>
[% END %]
