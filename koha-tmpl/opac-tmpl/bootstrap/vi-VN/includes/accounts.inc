[%- BLOCK account_type_description -%]
 <span>
 [%- IF account.credit_type_code -%]
 [%- PROCESS credit_type_description account=account -%]
 [%- ELSIF account.debit_type_code -%]
 [%- PROCESS debit_type_description account=account -%]
 [%- END -%]
 [%- PROCESS account_status_description account=account -%]
 </span>
[%- END -%]

[%- BLOCK debit_type_description -%]
 [%- SWITCH account.debit_type_code -%]

 [%- CASE 'ACCOUNT' -%]
 <span>Phí tạo tài khoản</span>
 [%- CASE 'ACCOUNT_RENEW' -%]
 <span>Phí gia hạn tài khoản</span>
 [%- CASE 'ARTICLE_REQUEST' -%]
 <span>Phí yêu cầu đặt bài báo</span>
 [%- CASE 'LOST' -%]
 <span>Mất tài liệu</span>
 [%- CASE 'MANUAL' -%]
 <span>Phí thủ công</span>
 [%- CASE 'NEW_CARD' -%]
 <span>Tạo thẻ thư viện mới</span>
 [%- CASE 'OVERDUE' -%]
 <span>Tiền phạt</span>
 [%- CASE 'PROCESSING' -%]
 <span>Phí xử lý vật phẩm bị mất</span>
 [%- CASE 'RENT' -%]
 <span>Phí mượn tài liệu</span>
 [%- CASE 'RENT_DAILY' -%]
 <span>Phí thuê theo ngày</span>
 [%- CASE 'RENT_RENEW' -%]
 <span>Gia hạn mục thuê</span>
 [%- CASE 'RENT_DAILY_RENEW' -%]
 <span>Gia hạn tài liệu thuê theo ngày</span>
 [%- CASE 'RESERVE' -%]
 <span>Phí đặt mượn</span>
 [%- CASE 'RESERVE_EXPIRED' -%]
 <span>Yêu cầu đặt đã chờ quá hạn</span>
 [%- CASE 'PAYOUT' -%]
 <span>Khoản thanh toán từ thư viện cho người dùng</span>
 [%- CASE 'VOID' -%]
 <span>Khoản tín dụng đã bị hủy</span>
 [%- CASE -%]
 <span
            >[%- IF account && account.debit_type && account.debit_type.description -%]
 [% account.debit_type.description | html %]
 [%- ELSE -%]
 [% account.debit_type_code | html %]
 [%- END -%]
 </span>
 [%- END -%]
[%- END -%]

[%- BLOCK credit_type_description -%]
 [%- SWITCH account.credit_type_code -%]

 [%- CASE 'CANCELLATION' -%]
 <span>Khoản phí đã hủy</span>
 [%- CASE 'CREDIT' -%]
 <span>Hạn mức sử dụng</span>
 [%- CASE 'DISCOUNT' -%]
 <span>Giảm phí</span>
 [%- CASE 'FORGIVEN' -%]
 <span>Miễn</span>
 [%- CASE 'LOST_FOUND' -%]
 <span>Hoàn phí tài liệu mất</span>
 [%- CASE 'OVERPAYMENT' -%]
 <span>Hoàn trả khoản thanh toán thừa</span>
 [%- CASE 'PAYMENT' -%]
 <span>Thanh toán</span>
 [%- CASE 'PROCESSING_FOUND' -%]
 <span>Hoàn phí xử lý tài liệu bị mất</span>
 [%- CASE 'PURCHASE' -%]
 <span>Mua</span>
 [%- CASE 'REFUND' -%]
 <span>Hoàn tiền</span>
 [%- CASE 'WRITEOFF' -%]
 <span>Xóa khoản phải thu</span>
 [%- CASE -%]
 <span
            >[%- IF account && account.credit_type && account.credit_type.description -%]
 [% account.credit_type.description | html %]
 [%- ELSE -%]
 [% account.credit_type_code | html %]
 [%- END -%]
 </span>
 [%- END -%]
[%- END -%]

[%- BLOCK account_status_description -%]
 [%- SWITCH account.status -%]

 [%- CASE 'UNRETURNED' -%]
 <span> (Tích lũy)</span>
 [%- CASE 'RETURNED' -%]
 <span> (Đã trả)</span>
 [%- CASE 'REPLACED' -%]
 <span> (Đã thay thế)</span>
 [%- CASE 'REFUNDED' -%]
 <span> (Đã hoàn tiền)</span>
 [%- CASE 'FORGIVEN' -%]
 <span> (Đã miễn khoản phí)</span>
 [%- CASE 'VOID' -%]
 <span> (Vô hiệu)</span>
 [%- CASE 'LOST' -%]
 <span> (Bị mất)</span>
 [%- CASE 'CANCELLED' -%]
 <span> (Hủy bỏ)</span>
 [%- CASE -%]

 [%- END -%]
[%- END -%]
