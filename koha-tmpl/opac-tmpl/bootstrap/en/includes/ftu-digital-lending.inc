[%# FTU Digital Lending (CDL) Engine & Modals %]
<!-- Modal Xác nhận Mượn Tài liệu số -->
<div class="modal fade" id="ftuDigitalLendingModal" tabindex="-1" aria-labelledby="ftuDigitalLendingModalLabel" aria-hidden="true" style="z-index: 10600;">
    <div class="modal-dialog modal-dialog-centered modal-lg">
        <div class="modal-content" style="border: none; border-radius: 16px; overflow: hidden; box-shadow: 0 20px 40px rgba(0,0,0,0.2);">
            <!-- Modal Header -->
            <div class="modal-header" style="background: linear-gradient(135deg, #A31A24 0%, #7F1019 100%); color: #ffffff; padding: 1.25rem 1.5rem; border: none;">
                <div class="d-flex align-items-center" style="gap: 12px;">
                    <div style="width: 40px; height: 40px; border-radius: 10px; background: rgba(255,255,255,0.15); display: flex; align-items: center; justify-content: center; font-size: 1.25rem;">
                        <i class="fa fa-book-reader" aria-hidden="true"></i>
                    </div>
                    <div>
                        <h5 class="modal-title fw-bold mb-0" id="ftuDigitalLendingModalLabel" style="font-size: 1.15rem; letter-spacing: -0.01em;">Xác nhận mượn tài liệu số</h5>
                        <small style="opacity: 0.85; font-size: 0.8rem;">Hệ thống Kiểm soát Lưu thông Số Bản quyền (FTU CDL &amp; DRM)</small>
                    </div>
                </div>
                <button type="button" class="btn-close btn-close-white" data-bs-dismiss="modal" aria-label="Đóng"></button>
            </div>

            <!-- Modal Body -->
            <div class="modal-body p-4" id="ftuDigitalLendingModalBody">
                <!-- Nội dung được cập nhật động bằng Javascript -->
                <div class="text-center py-4" id="ftuModalStateLoading">
                    <div class="spinner-border text-danger" role="status" style="width: 3rem; height: 3rem;">
                        <span class="visually-hidden">Đang tải...</span>
                    </div>
                    <p class="mt-3 text-muted fw-semibold" style="font-size: 0.95rem;">Đang kiểm tra chính sách bạn đọc và hạn mức mượn số...</p>
                </div>
            </div>
        </div>
    </div>
</div>

<!-- Modal Xác nhận Trả Tài liệu số -->
<div class="modal fade" id="ftuDigitalReturnModal" tabindex="-1" aria-labelledby="ftuDigitalReturnModalLabel" aria-hidden="true" style="z-index: 10605;">
    <div class="modal-dialog modal-dialog-centered">
        <div class="modal-content" style="border: none; border-radius: 16px; overflow: hidden; box-shadow: 0 20px 40px rgba(0,0,0,0.2);">
            <div class="modal-header bg-danger text-white p-3 border-0">
                <h5 class="modal-title fw-bold" id="ftuDigitalReturnModalLabel">
                    <i class="fa fa-undo me-2"></i> Xác nhận trả tài liệu số
                </h5>
                <button type="button" class="btn-close btn-close-white" data-bs-dismiss="modal" aria-label="Đóng"></button>
            </div>
            <div class="modal-body p-4">
                <div class="text-center mb-3">
                    <div style="width: 64px; height: 64px; margin: 0 auto; border-radius: 50%; background: #FEE2E2; display: flex; align-items: center; justify-content: center; color: #DC2626; font-size: 1.75rem;">
                        <i class="fa fa-book"></i>
                    </div>
                </div>
                <h6 class="text-center fw-bold text-dark mb-2" id="ftuReturnDocTitle">Nhan đề tài liệu</h6>
                <p class="text-center text-muted small mb-3">
                    Bạn có chắc chắn muốn trả tài liệu này không? Sau khi trả, phiên đọc bản quyền DRM sẽ được thu hồi và bạn sẽ được cộng thêm <strong>1 lượt mượn</strong> tài liệu mới.
                </p>
                <div class="d-flex justify-content-center gap-2">
                    <button type="button" class="btn btn-light px-4 fw-semibold" data-bs-dismiss="modal">Hủy bỏ</button>
                    <button type="button" class="btn btn-danger px-4 fw-semibold" id="ftuBtnConfirmReturn">
                        <i class="fa fa-check me-1"></i> Xác nhận trả ngay
                    </button>
                </div>
            </div>
        </div>
    </div>
</div>

<!-- Stylesheet & Script điều phối toàn cục -->
<style>
.ftu-quota-badge {
    display: inline-flex;
    align-items: center;
    gap: 6px;
    padding: 6px 12px;
    border-radius: 8px;
    font-size: 0.85rem;
    font-weight: 600;
}
.ftu-quota-badge.success { background: #ECFDF5; color: #065F46; border: 1px solid #A7F3D0; }
.ftu-quota-badge.warning { background: #FFFBEB; color: #92400E; border: 1px solid #FDE68A; }
.ftu-quota-badge.danger  { background: #FEF2F2; color: #991B1B; border: 1px solid #FECACA; }

.ftu-card-stat {
    border-radius: 12px;
    border: 1px solid #E2E8F0;
    padding: 1.15rem;
    background: #ffffff;
    box-shadow: 0 2px 6px rgba(0,0,0,0.03);
    transition: all 0.2s ease;
}
.ftu-card-stat:hover {
    box-shadow: 0 6px 16px rgba(0,0,0,0.07);
    border-color: #CBD5E1;
}

#digital-checkouts-table th {
    background-color: #F8FAFC;
    color: #475569;
    font-weight: 700;
    font-size: 0.85rem;
    text-transform: uppercase;
    letter-spacing: 0.03em;
    vertical-align: middle;
}
#digital-checkouts-table td {
    vertical-align: middle;
    font-size: 0.9rem;
}
</style>

<script nonce="[% Koha.CSPNonce | $raw %]">
(function() {
    'use strict';

    // 1. Phân giải endpoint DRM linh hoạt
    function getDrmApiBase() {
        var proto = window.location.protocol;
        var host = window.location.hostname || '10.2.0.226';
        var port = window.location.port;
        var isGateway = !port || port === '80' || port === '443';
        if (isGateway) {
            return proto + '//' + host + '/drm/api/v1/drm';
        }
        return proto + '//' + host + ':8095/api/v1/drm';
    }

    // 2. Lấy thông tin tài khoản bạn đọc Koha đang đăng nhập
    var tplPatronId = ('[% logged_in_user.userid || loggedinusername | html %]').trim();
    var tplPatronName = ('[% logged_in_user.firstname | html %] [% logged_in_user.surname | html %]').trim() || tplPatronId;
    var tplBorrowernumber = ('[% logged_in_user.borrowernumber | html %]').trim();
    var tplCategory = ('[% logged_in_user.categorycode | html %]').trim();
    var tplBranch = ('[% logged_in_user.branchcode | html %]').trim();

    function getLoggedInPatron() {
        if (tplPatronId && tplPatronId.length > 0) {
            return {
                patronId: tplPatronId,
                borrowernumber: tplBorrowernumber,
                categorycode: tplCategory,
                branchcode: tplBranch,
                name: tplPatronName || tplPatronId
            };
        }
        var el = document.querySelector('.loggedinusername');
        if (el) {
            var userid = el.getAttribute('data-userid');
            var borrowernumber = el.getAttribute('data-borrowernumber');
            var branchcode = el.getAttribute('data-branchcode');
            var categorycode = el.getAttribute('data-categorycode');
            var patronId = (userid && userid.trim()) ? userid.trim() : (borrowernumber ? borrowernumber.trim() : null);
            if (!patronId && el.textContent) patronId = el.textContent.trim();
            if (patronId) {
                return {
                    patronId: patronId,
                    borrowernumber: borrowernumber,
                    categorycode: categorycode,
                    branchcode: branchcode,
                    name: el.textContent ? el.textContent.trim() : patronId
                };
            }
        }
        // Kiểm tra thêm tham số user từ SSO hoặc URL nếu có
        var urlParams = new URLSearchParams(window.location.search);
        var qUser = urlParams.get('user');
        if (qUser && qUser.trim()) {
            return {
                patronId: qUser.trim(),
                name: qUser.trim()
            };
        }
        return null;
    }

    var activeCheckDoc = null;
    var returnTargetDoc = null;

    // 3. Hàm kích hoạt Modal mượn tài liệu số
    window.ftuOpenDigitalLendingModal = function(params) {
        params = params || {};
        var patron = getLoggedInPatron();
        var modalEl = document.getElementById('ftuDigitalLendingModal');
        if (!modalEl) return;
        var bsModal = bootstrap.Modal.getInstance(modalEl) || new bootstrap.Modal(modalEl);
        var bodyEl = document.getElementById('ftuDigitalLendingModalBody');

        bsModal.show();

        // Kiểm tra nếu chưa đăng nhập
        if (!patron || !patron.patronId) {
            bodyEl.innerHTML = `
                <div class="text-center py-4">
                    <div style="width: 64px; height: 64px; margin: 0 auto 1rem; border-radius: 50%; background: #FEF3C7; display: flex; align-items: center; justify-content: center; color: #D97706; font-size: 1.75rem;">
                        <i class="fa fa-lock"></i>
                    </div>
                    <h5 class="fw-bold text-dark mb-2">Yêu cầu đăng nhập tài khoản</h5>
                    <p class="text-muted" style="max-width: 480px; margin: 0 auto 1.5rem;">
                        Bạn cần đăng nhập tài khoản Thư viện FTU để hệ thống kiểm tra chính sách bạn đọc và cấp quyền mượn đọc tài liệu số.
                    </p>
                    <a href="/cgi-bin/koha/opac-user.pl" class="btn btn-danger px-4 py-2 fw-bold" style="background: #A31A24; border-color: #A31A24; border-radius: 8px;">
                        <i class="fa fa-sign-in-alt me-1"></i> Đăng nhập ngay
                    </a>
                </div>
            `;
            return;
        }

        // Trạng thái đang tải
        bodyEl.innerHTML = `
            <div class="text-center py-4">
                <div class="spinner-border text-danger" role="status" style="width: 3rem; height: 3rem;"></div>
                <p class="mt-3 text-muted fw-semibold">Đang kiểm tra chính sách bạn đọc và hạn mức mượn số...</p>
            </div>
        `;

        var drmBase = getDrmApiBase();
        var queryArgs = 'patronId=' + encodeURIComponent(patron.patronId);
        if (params.itemUuid) queryArgs += '&itemUuid=' + encodeURIComponent(params.itemUuid);
        if (params.bitstreamUuid) queryArgs += '&bitstreamUuid=' + encodeURIComponent(params.bitstreamUuid);
        if (params.biblionumber) queryArgs += '&biblionumber=' + encodeURIComponent(params.biblionumber);
        if (params.handle) queryArgs += '&handle=' + encodeURIComponent(params.handle);
        if (params.title) queryArgs += '&title=' + encodeURIComponent(params.title);
        if (params.author) queryArgs += '&author=' + encodeURIComponent(params.author);
        if (params.fallbackUrl) queryArgs += '&fallbackUrl=' + encodeURIComponent(params.fallbackUrl);

        fetch(drmBase + '/lending/precheck?' + queryArgs)
            .then(function(res) { return res.json(); })
            .then(function(data) {
                if (!data.success) {
                    throw new Error(data.error || 'Không thể kiểm tra chính sách mượn số');
                }
                activeCheckDoc = data;
                renderPrecheckModal(data, params);
            })
            .catch(function(err) {
                bodyEl.innerHTML = `
                    <div class="alert alert-warning d-flex align-items-center" role="alert">
                        <i class="fa fa-exclamation-triangle fa-2x me-3 text-warning"></i>
                        <div>
                            <h6 class="fw-bold mb-1">Không thể kết nối dịch vụ DRM</h6>
                            <p class="mb-0 small">${err.message}</p>
                        </div>
                    </div>
                    <div class="text-end">
                        <button type="button" class="btn btn-secondary btn-sm" data-bs-dismiss="modal">Đóng</button>
                    </div>
                `;
            });
    };

    function renderPrecheckModal(data, originalParams) {
        var bodyEl = document.getElementById('ftuDigitalLendingModalBody');
        var quota = data.quota || {};
        var doc = data.document || {};
        var maxLoans = quota.maxActiveLoans || 5;
        var activeLoans = quota.activeLoansCount || 0;
        var remainingLoans = quota.remainingLoans || 0;
        var groupName = quota.groupName || 'Bạn đọc FTU';

        // TRƯỜNG HỢP 1: ĐÃ MƯỢN TRƯỚC ĐÓ VÀ ĐANG CÒN HẠN
        if (data.alreadyBorrowed) {
            bodyEl.innerHTML = `
                <div class="p-3 bg-light rounded-3 mb-3 border">
                    <div class="d-flex align-items-start" style="gap: 15px;">
                        <div style="font-size: 2.2rem; color: #059669; line-height: 1;">
                            <i class="fa fa-check-circle"></i>
                        </div>
                        <div class="flex-grow-1">
                            <span class="badge bg-success mb-1">Đang trong hạn mượn</span>
                            <h5 class="fw-bold text-dark mb-1">${doc.title || 'Tài liệu số FTU'}</h5>
                            <p class="text-muted small mb-2"><i class="fa fa-user-edit me-1"></i> Tác giả: ${doc.author || 'Đại học Ngoại Thương'}</p>
                            <p class="mb-0 small text-secondary">
                                Tài liệu này đang nằm trong danh sách mượn của bạn. Bạn có thể mở đọc toàn văn ngay bây giờ mà không tốn thêm lượt mượn.
                            </p>
                        </div>
                    </div>
                </div>
                <div class="d-flex justify-content-between align-items-center pt-2">
                    <span class="small text-muted">
                        <i class="fa fa-id-card me-1"></i> ${groupName} &bull; Đang mượn: <strong>${activeLoans}/${maxLoans}</strong>
                    </span>
                    <div class="d-flex gap-2">
                        <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Đóng</button>
                        <button type="button" class="btn btn-success fw-bold px-4" id="ftuBtnReadNow">
                            <i class="fa fa-book-open me-1"></i> Mở đọc ngay
                        </button>
                    </div>
                </div>
            `;
            document.getElementById('ftuBtnReadNow').onclick = function() {
                var ssoPortalUrl = window.location.protocol + '//' + window.location.hostname + (window.location.port === '80' || !window.location.port ? '/sso' : ':8090');
                var readerTarget = '/bitstreams/' + encodeURIComponent(doc.bitstreamUuid);
                if (originalParams && originalParams.handle) {
                    readerTarget = '/elib/handle/' + encodeURIComponent(originalParams.handle.replace(/^handle\//i, ''));
                } else if (originalParams && originalParams.fallbackUrl) {
                    readerTarget = originalParams.fallbackUrl;
                } else if (doc.itemUuid) {
                    readerTarget = '/elib/items/' + encodeURIComponent(doc.itemUuid);
                }
                var readerUrl = ssoPortalUrl + '/sso/koha-to-dspace?user=' + encodeURIComponent(quota.patronId) + '&target=' + encodeURIComponent(readerTarget);
                window.open(readerUrl, '_blank');
                var modal = bootstrap.Modal.getInstance(document.getElementById('ftuDigitalLendingModal'));
                if (modal) modal.hide();
            };
            return;
        }

        // TRƯỜNG HỢP 2: VƯỢT QUÁ SỐ LƯỢNG CHO PHÉP (HẾT HẠN MỨC)
        if (!data.canBorrow) {
            bodyEl.innerHTML = `
                <div class="p-3 rounded-3 mb-3 border border-danger" style="background: #FEF2F2;">
                    <div class="d-flex align-items-start" style="gap: 15px;">
                        <div style="font-size: 2.2rem; color: #DC2626; line-height: 1;">
                            <i class="fa fa-exclamation-circle"></i>
                        </div>
                        <div class="flex-grow-1">
                            <span class="badge bg-danger mb-1">Đã đạt giới hạn tối đa</span>
                            <h5 class="fw-bold text-dark mb-1">${doc.title || 'Tài liệu số FTU'}</h5>
                            <p class="text-danger fw-semibold small mb-2">
                                <i class="fa fa-ban me-1"></i> Không thể mượn thêm tài liệu số mới
                            </p>
                            <p class="mb-2 small text-secondary">
                                Nhóm bạn đọc <strong>${groupName}</strong> có hạn mức mượn tối đa là <strong>${maxLoans} tài liệu số</strong> cùng lúc.
                                Hiện tại bạn đã mượn <strong>${activeLoans}/${maxLoans} cuốn</strong>.
                            </p>
                            <div class="p-2 rounded bg-white border border-danger-subtle small text-danger fw-semibold">
                                <i class="fa fa-info-circle me-1"></i> Quy định mượn trả: Bạn phải trả bớt tài liệu số đang mượn trước rồi mới được đọc hoặc mượn cuốn khác!
                            </div>
                        </div>
                    </div>
                </div>
                <div class="d-flex justify-content-between align-items-center pt-2">
                    <span class="small text-muted">
                        Hạn mức: <strong class="text-danger">${activeLoans}/${maxLoans}</strong> (Còn 0 lượt)
                    </span>
                    <div class="d-flex gap-2">
                        <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Đóng</button>
                        <a href="/cgi-bin/koha/opac-user.pl?tab=opac-user-digital-checkouts" class="btn btn-danger fw-bold px-3" style="background: #A31A24; border-color: #A31A24;">
                            <i class="fa fa-list-check me-1"></i> Đến trang Trả tài liệu số
                        </a>
                    </div>
                </div>
            `;
            return;
        }

        // TRƯỜNG HỢP 3: ĐỦ ĐIỀU KIỆN MƯỢN SỐ
        bodyEl.innerHTML = `
            <div class="p-3 bg-light rounded-3 mb-3 border">
                <div class="d-flex align-items-start" style="gap: 15px;">
                    <div style="width: 48px; height: 48px; border-radius: 10px; background: #FEE2E2; color: #A31A24; display: flex; align-items: center; justify-content: center; font-size: 1.5rem; flex-shrink: 0;">
                        <i class="fa fa-book"></i>
                    </div>
                    <div class="flex-grow-1">
                        <h5 class="fw-bold text-dark mb-1">${doc.title || 'Tài liệu số FTU'}</h5>
                        <p class="text-muted small mb-2"><i class="fa fa-user-edit me-1"></i> Tác giả: <strong>${doc.author || 'Trường Đại học Ngoại Thương'}</strong></p>
                        
                        <div class="row g-2 mt-1">
                            <div class="col-6">
                                <div class="p-2 bg-white rounded border small">
                                    <span class="text-muted d-block">Thời hạn mượn:</span>
                                    <strong class="text-danger"><i class="fa fa-calendar-alt me-1"></i> 14 ngày</strong> (đọc trực tuyến)
                                </div>
                            </div>
                            <div class="col-6">
                                <div class="p-2 bg-white rounded border small">
                                    <span class="text-muted d-block">Lượt mượn còn lại:</span>
                                    <strong class="text-success"><i class="fa fa-check me-1"></i> ${remainingLoans} / ${maxLoans} tài liệu</strong>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

            <div class="alert alert-info py-2 px-3 mb-3 small d-flex align-items-center" style="border-radius: 8px;">
                <i class="fa fa-shield-alt text-primary me-2 fa-lg"></i>
                <div>
                    Tài liệu được bảo vệ bản quyền số FTU DRM. Bạn đọc được đọc toàn văn trực tuyến kèm dấu bản quyền danh tính. Không sao chép hoặc phát tán trái phép.
                </div>
            </div>

            <div class="d-flex justify-content-between align-items-center pt-2">
                <span class="small text-muted">
                    <i class="fa fa-user-tag me-1"></i> ${groupName}
                </span>
                <div class="d-flex gap-2">
                    <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Hủy bỏ</button>
                    <button type="button" class="btn btn-danger fw-bold px-4" id="ftuBtnDoBorrow" style="background: #A31A24; border-color: #A31A24;">
                        <i class="fa fa-check me-1"></i> Đồng ý mượn &amp; Mở đọc
                    </button>
                </div>
            </div>
        `;

        document.getElementById('ftuBtnDoBorrow').onclick = function() {
            var btn = this;
            btn.disabled = true;
            btn.innerHTML = '<i class="fa fa-spinner fa-spin me-1"></i> Đang kích hoạt mượn...';

            var drmBase = getDrmApiBase();
            fetch(drmBase + '/lending/borrow', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    patronId: quota.patronId,
                    bitstreamUuid: doc.bitstreamUuid,
                    itemUuid: doc.itemUuid,
                    biblionumber: (originalParams && originalParams.biblionumber) ? originalParams.biblionumber : doc.biblionumber,
                    handle: originalParams ? originalParams.handle : undefined,
                    title: doc.title,
                    author: doc.author,
                    fallbackUrl: originalParams ? originalParams.fallbackUrl : undefined,
                    patronName: quota.patronName
                })
            })
            .then(function(res) { return res.json(); })
            .then(function(borrowRes) {
                if (!borrowRes.success) {
                    throw new Error(borrowRes.error || 'Mượn tài liệu số thất bại');
                }
                
                // Mở trình đọc tài liệu số trong tab mới
                if (borrowRes.readerUrl) {
                    window.open(borrowRes.readerUrl, '_blank');
                }

                // Cập nhật lại danh sách mượn nếu đang ở trang opac-user.pl
                if (typeof window.ftuReloadDigitalLoans === 'function') {
                    window.ftuReloadDigitalLoans();
                }

                var modal = bootstrap.Modal.getInstance(document.getElementById('ftuDigitalLendingModal'));
                if (modal) modal.hide();
            })
            .catch(function(err) {
                alert('Lỗi mượn tài liệu: ' + err.message);
                btn.disabled = false;
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Đồng ý mượn &amp; Mở đọc';
            });
        };
    }

    // 4. Bắt chặn toàn cục các liên kết "Truy cập toàn văn số" trên Koha OPAC
    document.addEventListener('click', function(e) {
        var a = e.target.closest('a');
        if (!a) return;

        // Bỏ qua các nút thao tác bên trong modal hoặc danh mục quản lý mượn
        if (
            a.closest('#ftuDigitalLendingModal') ||
            a.closest('#ftuDigitalReturnModal') ||
            a.closest('#opac-user-digital-checkouts_panel') ||
            a.closest('#opac-user-digital-checkouts-panel-container') ||
            a.classList.contains('btn-return-digital') ||
            a.id === 'ftuBtnReadNow' ||
            a.id === 'ftuBtnDoBorrow'
        ) {
            return;
        }

        var rawHref = a.getAttribute('href') || '';
        if (!rawHref || rawHref.startsWith('#') || rawHref.startsWith('javascript:')) {
            return;
        }

        var href = rawHref;
        try { href = decodeURIComponent(rawHref); } catch(_) {}
        var text = (a.textContent || '').trim().toLowerCase();

        var isFullTextLink = false;
        if (
            a.getAttribute('property') === 'url' ||
            a.closest('.online_resources') ||
            a.closest('.ftu-opac-digital-badge') ||
            a.classList.contains('ftu-dspace-link')
        ) {
            isFullTextLink = true;
        } else if (
            text.includes('truy cập toàn văn') ||
            text.includes('toàn văn số') ||
            text.includes('đọc trực tuyến') ||
            text.includes('xem toàn văn') ||
            text.includes('tài liệu số') ||
            text.includes('full text') ||
            text.includes('read online')
        ) {
            isFullTextLink = true;
        } else if (
            href.includes('/handle/') ||
            href.includes('/items/') ||
            href.includes('/bitstreams/') ||
            href.includes('/koha-to-dspace') ||
            href.includes('/elib/') ||
            rawHref.includes('/koha-to-dspace') ||
            rawHref.includes('handle%2F') ||
            rawHref.includes('items%2F')
        ) {
            isFullTextLink = true;
        }

        if (isFullTextLink) {
            e.preventDefault();
            e.stopPropagation();
            if (typeof e.stopImmediatePropagation === 'function') {
                e.stopImmediatePropagation();
            }

            var itemUuid = null;
            var bitstreamUuid = null;
            var handle = null;

            var itemMatch = href.match(/\/items\/([a-f0-9\-]{36})/i);
            if (itemMatch) itemUuid = itemMatch[1];

            var bsMatch = href.match(/\/bitstreams\/([a-f0-9\-]{36})/i);
            if (bsMatch) bitstreamUuid = bsMatch[1];

            var handleMatch = href.match(/handle\/([0-9]+\/[0-9]+)/i) || rawHref.match(/handle(?:%2F|\/)([0-9]+(?:%2F|\/)[0-9]+)/i);
            if (handleMatch) {
                handle = decodeURIComponent(handleMatch[1]).replace(/%2F/i, '/');
            }

            var biblionumber = null;
            var bibContainer = document.querySelector('#catalogue_detail_biblio[data-biblionumber]');
            if (bibContainer) biblionumber = bibContainer.getAttribute('data-biblionumber');
            if (!biblionumber) {
                var urlParams = new URLSearchParams(window.location.search);
                biblionumber = urlParams.get('biblionumber');
            }
            if (!biblionumber) {
                var bibInput = document.querySelector('input[name="biblionumber"], input#biblionumber');
                if (bibInput) biblionumber = bibInput.value;
            }
            if (!biblionumber && a.closest('[data-biblionumber]')) {
                biblionumber = a.closest('[data-biblionumber]').getAttribute('data-biblionumber');
            }

            var recordEl = a.closest('.record') || a.closest('.searchresults') || document.querySelector('.record');
            var titleEl = recordEl ? recordEl.querySelector('h1.title, .title') : document.querySelector('h1.title, .biblio-title');
            var authorEl = recordEl ? recordEl.querySelector('.author, .byauthor, .byAuthor') : document.querySelector('.author, .byauthor');

            var title = '';
            if (titleEl) {
                var clone = titleEl.cloneNode(true);
                var respStmt = clone.querySelector('.title_resp_stmt');
                if (respStmt) respStmt.remove();
                title = clone.textContent.trim().replace(/\s+/g, ' ');
            }
            var author = authorEl ? authorEl.textContent.trim().replace(/^Liệt kê theo:\s*/i, '').replace(/^Contributor\(s\):\s*/i, '').replace(/\s+/g, ' ') : '';

            window.ftuOpenDigitalLendingModal({
                itemUuid: itemUuid,
                bitstreamUuid: bitstreamUuid,
                biblionumber: biblionumber,
                handle: handle,
                title: title,
                author: author,
                fallbackUrl: rawHref
            });
            return false;
        }
    }, true);

    // 5. Quản lý Tab "Tài liệu số đang mượn" trên trang opac-user.pl
    window.ftuReloadDigitalLoans = function() {
        var patron = getLoggedInPatron();
        if (!patron || !patron.patronId) return;

        var panelEl = document.getElementById('opac-user-digital-checkouts-panel-container') || document.getElementById('opac-user-digital-checkouts_panel');
        var badgeEl = document.getElementById('digital-loans-count-badge');
        if (!panelEl && !badgeEl) return;

        var drmBase = getDrmApiBase();
        fetch(drmBase + '/lending/patron/' + encodeURIComponent(patron.patronId))
            .then(function(res) { return res.json(); })
            .then(function(data) {
                if (!data.success) return;
                var loans = data.loans || [];
                var quota = data.quota || {};

                // Cập nhật badge số lượng
                if (badgeEl) {
                    badgeEl.textContent = loans.length;
                }

                // Cập nhật giao diện bên trong tab panel
                if (panelEl) {
                    renderDigitalLoansPanel(panelEl, loans, quota);
                }
            })
            .catch(function(err) {
                console.warn('[FTU-DIGITAL-LENDING] Lỗi tải tài liệu số:', err);
            });
    };

    function renderDigitalLoansPanel(container, loans, quota) {
        var maxLoans = quota.maxActiveLoans || 5;
        var activeCount = loans.length;
        var remaining = Math.max(0, maxLoans - activeCount);
        var groupName = quota.groupName || 'Bạn đọc FTU';

        var html = `
            <!-- Dashboard Hạn mức Bạn đọc -->
            <div class="row g-3 mb-4 mt-1">
                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Nhóm Bạn đọc</span>
                            <span class="badge bg-danger-subtle text-danger border border-danger-subtle">${quota.groupCode || 'GRP_UG_STD'}</span>
                        </div>
                        <h6 class="fw-bold text-dark mb-1">${groupName}</h6>
                        <span class="small text-muted">Hạn mức mượn: <strong>${maxLoans} tài liệu số</strong></span>
                    </div>
                </div>

                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Tài liệu số đang mượn</span>
                            <span class="badge ${remaining > 0 ? 'bg-success-subtle text-success border border-success-subtle' : 'bg-danger-subtle text-danger border border-danger-subtle'}">
                                ${remaining > 0 ? 'Còn ' + remaining + ' lượt' : 'Đã hết lượt'}
                            </span>
                        </div>
                        <h3 class="fw-bold mb-0 text-dark">${activeCount} <small class="text-muted fs-6 fw-normal">/ ${maxLoans} cuốn</small></h3>
                        <div class="progress mt-2" style="height: 6px;">
                            <div class="progress-bar ${activeCount >= maxLoans ? 'bg-danger' : 'bg-success'}" style="width: ${(activeCount / maxLoans) * 100}%;"></div>
                        </div>
                    </div>
                </div>

                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Thời hạn mượn</span>
                            <span class="badge bg-primary-subtle text-primary border border-primary-subtle">DRM Bảo mật</span>
                        </div>
                        <h6 class="fw-bold text-dark mb-1">14 Ngày / Lần mượn</h6>
                        <span class="small text-muted">Tự động thu hồi phiên khi hết hạn hoặc trả sách</span>
                    </div>
                </div>
            </div>
        `;

        // Bảng danh sách hoặc Trạng thái trống
        if (loans.length === 0) {
            html += `
                <div class="text-center py-5 bg-light rounded-3 border">
                    <div style="width: 72px; height: 72px; margin: 0 auto 1rem; border-radius: 50%; background: #E2E8F0; display: flex; align-items: center; justify-content: center; color: #64748B; font-size: 2rem;">
                        <i class="fa fa-book-open"></i>
                    </div>
                    <h5 class="fw-bold text-dark mb-1">Hiện tại không có tài liệu số nào đang mượn</h5>
                    <p class="text-muted small mb-3" style="max-width: 450px; margin: 0 auto;">
                        Bạn có thể tra cứu các tài liệu học thuật số hóa trong kho Thư viện FTU để mượn và đọc trực tuyến mọi lúc mọi nơi.
                    </p>
                    <a href="/cgi-bin/koha/opac-search.pl" class="btn btn-outline-danger btn-sm px-3 fw-semibold">
                        <i class="fa fa-search me-1"></i> Khám phá kho tài liệu số
                    </a>
                </div>
            `;
        } else {
            html += `
                <div class="table-responsive">
                    <table class="table table-bordered table-hover align-middle" id="digital-checkouts-table">
                        <thead>
                            <tr>
                                <th style="width: 50px;" class="text-center">STT</th>
                                <th>Nhan đề tài liệu &amp; Tác giả</th>
                                <th style="width: 130px;" class="text-center">Ngày mượn</th>
                                <th style="width: 150px;" class="text-center">Ngày hết hạn</th>
                                <th style="width: 120px;" class="text-center">Thời hạn</th>
                                <th style="width: 180px;" class="text-center">Thao tác</th>
                            </tr>
                        </thead>
                        <tbody>
            `;

            loans.forEach(function(item, idx) {
                var checkoutDate = item.checkoutTime ? new Date(item.checkoutTime).toLocaleDateString('vi-VN') : '--';
                var dueDate = item.dueTime ? new Date(item.dueTime).toLocaleDateString('vi-VN') : '--';
                var daysLeft = item.daysRemaining || 0;
                var badgeClass = daysLeft > 3 ? 'bg-success' : (daysLeft > 0 ? 'bg-warning text-dark' : 'bg-danger');
                var badgeText = daysLeft > 0 ? ('Còn ' + daysLeft + ' ngày') : 'Đã hết hạn';

                html += `
                    <tr data-lending-id="${item.lendingId}" data-bitstream-uuid="${item.bitstreamUuid}">
                        <td class="text-center fw-bold text-muted">${idx + 1}</td>
                        <td>
                            <div class="fw-bold text-dark mb-1">${item.title}</div>
                            <small class="text-muted"><i class="fa fa-user me-1"></i> ${item.author}</small>
                        </td>
                        <td class="text-center small">${checkoutDate}</td>
                        <td class="text-center small fw-semibold">${dueDate}</td>
                        <td class="text-center">
                            <span class="badge ${badgeClass} rounded-pill">${badgeText}</span>
                        </td>
                        <td class="text-center">
                            <div class="btn-group btn-group-sm">
                                <a href="${item.readerUrl}" target="_blank" class="btn btn-outline-primary fw-semibold" title="Đọc trực tuyến">
                                    <i class="fa fa-book-reader me-1"></i> Đọc
                                </a>
                                <button type="button" class="btn btn-outline-danger fw-semibold btn-return-digital" data-title="${encodeURIComponent(item.title)}" data-lending-id="${item.lendingId}" data-bitstream-uuid="${item.bitstreamUuid}" title="Trả tài liệu số">
                                    <i class="fa fa-undo me-1"></i> Trả
                                </button>
                            </div>
                        </td>
                    </tr>
                `;
            });

            html += `
                        </tbody>
                    </table>
                </div>
            `;
        }

        container.innerHTML = html;

        // Gắn sự kiện nút "Trả tài liệu"
        var returnBtns = container.querySelectorAll('.btn-return-digital');
        returnBtns.forEach(function(btn) {
            btn.addEventListener('click', function() {
                var docTitle = decodeURIComponent(this.getAttribute('data-title') || 'Tài liệu số');
                var lendingId = this.getAttribute('data-lending-id');
                var bitstreamUuid = this.getAttribute('data-bitstream-uuid');

                returnTargetDoc = {
                    lendingId: lendingId,
                    bitstreamUuid: bitstreamUuid,
                    title: docTitle
                };

                document.getElementById('ftuReturnDocTitle').textContent = docTitle;
                var retModal = new bootstrap.Modal(document.getElementById('ftuDigitalReturnModal'));
                retModal.show();
            });
        });
    }

    // Xử lý xác nhận trả tài liệu số
    var btnConfirmReturn = document.getElementById('ftuBtnConfirmReturn');
    if (btnConfirmReturn) {
        btnConfirmReturn.addEventListener('click', function() {
            if (!returnTargetDoc) return;
            var patron = getLoggedInPatron();
            if (!patron || !patron.patronId) return;

            var btn = this;
            btn.disabled = true;
            btn.innerHTML = '<i class="fa fa-spinner fa-spin me-1"></i> Đang xử lý trả...';

            var drmBase = getDrmApiBase();
            fetch(drmBase + '/lending/return', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    patronId: patron.patronId,
                    bitstreamUuid: returnTargetDoc.bitstreamUuid,
                    lendingId: returnTargetDoc.lendingId
                })
            })
            .then(function(res) { return res.json(); })
            .then(function(retRes) {
                btn.disabled = false;
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Xác nhận trả ngay';

                var retModalEl = document.getElementById('ftuDigitalReturnModal');
                var modal = bootstrap.Modal.getInstance(retModalEl);
                if (modal) modal.hide();

                if (!retRes.success) {
                    alert('Lỗi trả tài liệu: ' + retRes.error);
                    return;
                }

                // Cập nhật lại danh sách mượn ngay lập tức
                window.ftuReloadDigitalLoans();
            })
            .catch(function(err) {
                alert('Lỗi kết nối khi trả tài liệu: ' + err.message);
                btn.disabled = false;
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Xác nhận trả ngay';
            });
        });
    }

    // Tự động tải danh sách và mở tab nếu có tham số ?tab=opac-user-digital-checkouts
    document.addEventListener('DOMContentLoaded', function() {
        var urlParams = new URLSearchParams(window.location.search);
        var activeTabParam = urlParams.get('tab');
        var hash = window.location.hash;

        if (activeTabParam === 'opac-user-digital-checkouts' || hash === '#opac-user-digital-checkouts' || hash === '#opac-user-digital-checkouts_panel') {
            setTimeout(function() {
                var tabEl = document.querySelector('#opac-user-views a[href="#opac-user-digital-checkouts_panel"], #opac-user-digital-checkouts-tab');
                if (tabEl) {
                    var tabObj = bootstrap.Tab.getInstance(tabEl) || new bootstrap.Tab(tabEl);
                    tabObj.show();
                }
            }, 200);
        }

        // Tải danh sách mượn số ban đầu và cập nhật badge
        if (document.getElementById('opac-user-digital-checkouts_panel') || document.getElementById('digital-loans-count-badge') || document.getElementById('opac-user-digital-checkouts-panel-container')) {
            window.ftuReloadDigitalLoans();
        }
    });

})();
</script>
