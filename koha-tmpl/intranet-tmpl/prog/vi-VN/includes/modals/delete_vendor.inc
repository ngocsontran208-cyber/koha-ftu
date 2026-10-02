<!-- Delete Vendor modal form -->
<div id="deleteVendorModal" class="modal" tabindex="-1" role="dialog" aria-labelledby="deleteVendorModalLabel">
    <form id="deleteVendorForm">
        <input type="hidden" name="booksellerid" id="booksellerid" value="" />
        <div class="modal-dialog" role="document">
            <div class="modal-content">
                <div class="modal-header">
                    <h4 class="modal-title" id="deleteVendorModalLabel"><i class="fa fa-trash-can text-danger"></i> Xóa nhà cung cấp</h4>
                    <button type="button" class="btn-close" data-bs-dismiss="modal" aria-label="Đóng"></button>
                </div>
                <div class="modal-body">
                    <p>Bạn có chắc chắn muốn xóa thông tin nhà cung cấp này khỏi hệ thống không?</p>
                </div>
                <div class="modal-footer">
                    <button type="submit" id="deleteVendorModaConfirmBtn" class="btn btn-danger approve"><i class="fa fa-check" aria-hidden="true"></i> Đồng ý xóa</button>
                    <button type="button" id="deleteVendorModaCancelBtn" data-bs-dismiss="modal" class="btn btn-default deny"><i class="fa fa-times" aria-hidden="true"></i> Hủy bỏ</button>
                </div>
            </div>
        </div>
    </form>
</div>
