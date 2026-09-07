<!-- Bundle contents modal -->
<div class="modal printable" id="bundleContentsModal" tabindex="-1" role="dialog" aria-labelledby="bundleContentsLabel">
 <div class="modal-dialog">
 <div class="modal-content">
 <div class="modal-header">
 <h1 class="modal-title" id="bundleContentsLabel">Bundle contents for [% item.barcode | html %]</h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <div class="modal-body">
 <table style="width:100%">
 <thead>
 <tr>
 <th>Mã vạch</th>
 <th>Nhan đề</th>
 </tr>
 </thead>
 <tbody>
 [% FOREACH bundle_item IN bundle_items %]
 <tr>
 <td>[% bundle_item.barcode | html %]</td>
 <td>[% INCLUDE 'biblio-title.inc' biblio=bundle_item.biblio %]</td>
 </tr>
 [% END %]
 </tbody>
 <tfoot> </tfoot>
 </table>
 </div>
 <!-- /.modal-body -->
 <div class="modal-footer">
 <button type="button" class="printModal btn btn-primary"><i class="fa fa-print"></i> In</button>
 <button type="button" class="btn btn-default" data-bs-dismiss="modal">Thoát</button>
 </div>
 <!-- /.modal-footer -->
 </div>
 <!-- /.modal-content -->
 </div>
 <!-- /.modal-dialog -->
</div>
<!-- /#bundleContentsModal -->
