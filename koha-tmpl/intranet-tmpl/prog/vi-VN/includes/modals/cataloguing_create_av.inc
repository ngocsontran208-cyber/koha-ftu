<div id="avCreate" class="modal" tabindex="-1" role="dialog" aria-labelledby="avCreateLabel" aria-hidden="true">
 <div class="modal-dialog">
 <div class="modal-content">
 <div class="modal-header">
 <h1 class="modal-title" id="avCreateLabel">Create a new authorized value</h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <form id="add_new_av" method="get">
 <div class="modal-body">
 <fieldset class="rows">
 <ol>
 <li>
 <span class="label">Danh mục:</span>
 <input type="hidden" name="category" value="" />
 <span id="new_av_category"></span>
 </li>
 <li>
 <label for="value" class="required">Giá trị nhất quán:</label>
 <input class="required" required="required" type="text" id="value" name="value" />
 <span class="required">Bắt buộc</span>
 </li>
 <li>
 <label for="description" class="required">Thông tin mô tả:</label>
 <input class="required" required="required" type="text" id="description" name="description" />
 <span class="required">Bắt buộc</span>
 </li>
 <li>
 <label for="opac_description">Description (OPAC):</label>
 <input type="text" id="opac_description" name="opac_description" />
 </li>
 </ol>
 </fieldset>
 <div class="avCreate_error alert alert-warning" style="display:none;"></div>
 </div>
 <div class="modal-footer">
 <input type="hidden" name="select2" value="" />
 <button type="submit" class="btn btn-default">Lưu</button>
 <button type="button" class="btn btn-default" data-bs-dismiss="modal">Hủy bỏ</button>
 </div>
 </form>
 </div>
 <!-- /.modal-content -->
 </div>
 <!-- /.modal-dialog -->
</div>
<!-- /#avCreate -->
