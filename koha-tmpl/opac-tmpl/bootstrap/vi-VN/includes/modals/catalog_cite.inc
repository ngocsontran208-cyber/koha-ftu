[% USE raw %]
<!-- Add cite modal -->
<div class="modal" id="citeModal" tabindex="-1" role="dialog" aria-labelledby="citeLabel" aria-hidden="true">
 <div class="modal-dialog modal-lg">
 <div class="modal-content">
 <div class="modal-header">
 <h1 class="modal-title" id="citeModalLabel">[% biblio.title | html %]</h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <div class="modal-body">
 [% FOREACH system IN cites.keys.sort %]
 <h2>[% system | html %]</h2>
 <p>[% cites.$system | html %]</p>
 [% END %]
 </div>
 <div class="modal-footer">
 <button type="button" class="btn btn-default" data-bs-dismiss="modal">Thoát</button>
 </div>
 </div>
 </div>
</div>
