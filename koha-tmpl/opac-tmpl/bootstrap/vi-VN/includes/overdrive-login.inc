<div id="overdrive-login" class="modal" tabindex="-1" role="dialog" aria-labelledby="overdrive-login-label" aria-hidden="true">
 <div class="modal-dialog">
 <div class="modal-content">
 <div class="modal-header">
 <h1 class="modal-title" id="overdrive-login-label">Đăng nhập</h1>
 <button aria-label="Thoát" class="btn-close" data-bs-dismiss="modal" type="button"></button>
 </div>
 <form action="#" id="overdrive-login-form">
 [% INCLUDE 'csrf-token.inc' %]
 <div class="modal-body">
 <fieldset class="brief">
 <label for="ODpassword">Mật khẩu:</label>
 <input type="password" name="ODpassword" id="ODpassword" value="" autocomplete="off" />
 </fieldset>
 </div>
 <div class="modal-footer">
 <input class="btn btn-primary overdrive-checkout-submit" type="submit" value="Đăng nhập" />
 <button type="button" data-bs-dismiss="modal" class="btn btn-default">Hủy bỏ</button>
 </div>
 </form>
 <!-- /#overdrive-login-form -->
 </div>
 <!-- /.modal-content -->
 </div>
 <!-- /.modal-dialog -->
</div>
<!-- /#overdrive-login -->
