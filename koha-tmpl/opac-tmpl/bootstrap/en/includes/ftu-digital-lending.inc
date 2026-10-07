[%# FTU Digital Lending (CDL) Engine & Modals - English Version %]
<!-- Digital Lending Confirmation Modal -->
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
                        <h5 class="modal-title fw-bold mb-0" id="ftuDigitalLendingModalLabel" style="font-size: 1.15rem; letter-spacing: -0.01em;">Confirm Digital Document Loan</h5>
                        <small style="opacity: 0.85; font-size: 0.8rem;">FTU Controlled Digital Lending &amp; DRM Protection Engine</small>
                    </div>
                </div>
                <button type="button" class="btn-close btn-close-white" data-bs-dismiss="modal" aria-label="Close"></button>
            </div>

            <!-- Modal Body -->
            <div class="modal-body p-4" id="ftuDigitalLendingModalBody">
                <div class="text-center py-4" id="ftuModalStateLoading">
                    <div class="spinner-border text-danger" role="status" style="width: 3rem; height: 3rem;">
                        <span class="visually-hidden">Loading...</span>
                    </div>
                    <p class="mt-3 text-muted fw-semibold" style="font-size: 0.95rem;">Checking reader policy and digital lending quota...</p>
                </div>
            </div>
        </div>
    </div>
</div>

<!-- Digital Return Confirmation Modal -->
<div class="modal fade" id="ftuDigitalReturnModal" tabindex="-1" aria-labelledby="ftuDigitalReturnModalLabel" aria-hidden="true" style="z-index: 10605;">
    <div class="modal-dialog modal-dialog-centered">
        <div class="modal-content" style="border: none; border-radius: 16px; overflow: hidden; box-shadow: 0 20px 40px rgba(0,0,0,0.2);">
            <div class="modal-header bg-danger text-white p-3 border-0">
                <h5 class="modal-title fw-bold" id="ftuDigitalReturnModalLabel">
                    <i class="fa fa-undo me-2"></i> Confirm Return of Digital Document
                </h5>
                <button type="button" class="btn-close btn-close-white" data-bs-dismiss="modal" aria-label="Close"></button>
            </div>
            <div class="modal-body p-4">
                <div class="text-center mb-3">
                    <div style="width: 64px; height: 64px; margin: 0 auto; border-radius: 50%; background: #FEE2E2; display: flex; align-items: center; justify-content: center; color: #DC2626; font-size: 1.75rem;">
                        <i class="fa fa-book"></i>
                    </div>
                </div>
                <h6 class="text-center fw-bold text-dark mb-2" id="ftuReturnDocTitle">Document Title</h6>
                <p class="text-center text-muted small mb-3">
                    Are you sure you want to return this digital document? Returning will revoke the active DRM reading session and release <strong>1 loan slot</strong> for you.
                </p>
                <div class="d-flex justify-content-center gap-2">
                    <button type="button" class="btn btn-light px-4 fw-semibold" data-bs-dismiss="modal">Cancel</button>
                    <button type="button" class="btn btn-danger px-4 fw-semibold" id="ftuBtnConfirmReturn">
                        <i class="fa fa-check me-1"></i> Return Document Now
                    </button>
                </div>
            </div>
        </div>
    </div>
</div>

<!-- Stylesheet & Script -->
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

    function getLoggedInPatron() {
        var el = document.querySelector('.loggedinusername');
        if (!el) return null;
        var userid = el.getAttribute('data-userid');
        var borrowernumber = el.getAttribute('data-borrowernumber');
        var branchcode = el.getAttribute('data-branchcode');
        var categorycode = el.getAttribute('data-categorycode');
        var patronId = (userid && userid.trim()) ? userid.trim() : (borrowernumber ? borrowernumber.trim() : null);
        return {
            patronId: patronId,
            borrowernumber: borrowernumber,
            categorycode: categorycode,
            branchcode: branchcode,
            name: el.textContent ? el.textContent.trim() : patronId
        };
    }

    var activeCheckDoc = null;
    var returnTargetDoc = null;

    window.ftuOpenDigitalLendingModal = function(params) {
        var patron = getLoggedInPatron();
        var modalEl = document.getElementById('ftuDigitalLendingModal');
        if (!modalEl) return;
        var bsModal = bootstrap.Modal.getInstance(modalEl) || new bootstrap.Modal(modalEl);
        var bodyEl = document.getElementById('ftuDigitalLendingModalBody');

        bsModal.show();

        if (!patron || !patron.patronId) {
            bodyEl.innerHTML = `
                <div class="text-center py-4">
                    <div style="width: 64px; height: 64px; margin: 0 auto 1rem; border-radius: 50%; background: #FEF3C7; display: flex; align-items: center; justify-content: center; color: #D97706; font-size: 1.75rem;">
                        <i class="fa fa-lock"></i>
                    </div>
                    <h5 class="fw-bold text-dark mb-2">Login Required</h5>
                    <p class="text-muted" style="max-width: 480px; margin: 0 auto 1.5rem;">
                        You must log in to your FTU Library account to check borrowing policies and borrow digital documents.
                    </p>
                    <a href="/cgi-bin/koha/opac-user.pl" class="btn btn-danger px-4 py-2 fw-bold" style="background: #A31A24; border-color: #A31A24; border-radius: 8px;">
                        <i class="fa fa-sign-in-alt me-1"></i> Log In Now
                    </a>
                </div>
            `;
            return;
        }

        bodyEl.innerHTML = `
            <div class="text-center py-4">
                <div class="spinner-border text-danger" role="status" style="width: 3rem; height: 3rem;"></div>
                <p class="mt-3 text-muted fw-semibold">Checking reader policy and digital lending quota...</p>
            </div>
        `;

        var drmBase = getDrmApiBase();
        var queryArgs = 'patronId=' + encodeURIComponent(patron.patronId);
        if (params.itemUuid) queryArgs += '&itemUuid=' + encodeURIComponent(params.itemUuid);
        if (params.bitstreamUuid) queryArgs += '&bitstreamUuid=' + encodeURIComponent(params.bitstreamUuid);
        if (params.biblionumber) queryArgs += '&biblionumber=' + encodeURIComponent(params.biblionumber);

        fetch(drmBase + '/lending/precheck?' + queryArgs)
            .then(function(res) { return res.json(); })
            .then(function(data) {
                if (!data.success) {
                    throw new Error(data.error || 'Failed to check digital lending policy');
                }
                activeCheckDoc = data;
                renderPrecheckModal(data, params);
            })
            .catch(function(err) {
                bodyEl.innerHTML = `
                    <div class="alert alert-warning d-flex align-items-center" role="alert">
                        <i class="fa fa-exclamation-triangle fa-2x me-3 text-warning"></i>
                        <div>
                            <h6 class="fw-bold mb-1">Cannot connect to DRM Service</h6>
                            <p class="mb-0 small">${err.message}</p>
                        </div>
                    </div>
                    <div class="text-end">
                        <button type="button" class="btn btn-secondary btn-sm" data-bs-dismiss="modal">Close</button>
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
        var groupName = quota.groupName || 'FTU Patron';

        if (data.alreadyBorrowed) {
            bodyEl.innerHTML = `
                <div class="p-3 bg-light rounded-3 mb-3 border">
                    <div class="d-flex align-items-start" style="gap: 15px;">
                        <div style="font-size: 2.2rem; color: #059669; line-height: 1;">
                            <i class="fa fa-check-circle"></i>
                        </div>
                        <div class="flex-grow-1">
                            <span class="badge bg-success mb-1">Currently Borrowed</span>
                            <h5 class="fw-bold text-dark mb-1">${doc.title || 'FTU Digital Document'}</h5>
                            <p class="text-muted small mb-2"><i class="fa fa-user-edit me-1"></i> Author: ${doc.author || 'Foreign Trade University'}</p>
                            <p class="mb-0 small text-secondary">
                                You currently have an active loan for this digital book. You can read it online immediately without consuming an extra loan slot.
                            </p>
                        </div>
                    </div>
                </div>
                <div class="d-flex justify-content-between align-items-center pt-2">
                    <span class="small text-muted">
                        <i class="fa fa-id-card me-1"></i> ${groupName} &bull; Active: <strong>${activeLoans}/${maxLoans}</strong>
                    </span>
                    <div class="d-flex gap-2">
                        <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Close</button>
                        <button type="button" class="btn btn-success fw-bold px-4" id="ftuBtnReadNow">
                            <i class="fa fa-book-open me-1"></i> Open &amp; Read Now
                        </button>
                    </div>
                </div>
            `;
            document.getElementById('ftuBtnReadNow').onclick = function() {
                var ssoPortalUrl = window.location.protocol + '//' + window.location.hostname + (window.location.port === '80' || !window.location.port ? '/sso' : ':8090');
                var readerUrl = ssoPortalUrl + '/sso/koha-to-dspace?user=' + encodeURIComponent(quota.patronId) + '&target=/bitstreams/' + encodeURIComponent(doc.bitstreamUuid);
                window.open(readerUrl, '_blank');
                var modal = bootstrap.Modal.getInstance(document.getElementById('ftuDigitalLendingModal'));
                if (modal) modal.hide();
            };
            return;
        }

        if (!data.canBorrow) {
            bodyEl.innerHTML = `
                <div class="p-3 rounded-3 mb-3 border border-danger" style="background: #FEF2F2;">
                    <div class="d-flex align-items-start" style="gap: 15px;">
                        <div style="font-size: 2.2rem; color: #DC2626; line-height: 1;">
                            <i class="fa fa-exclamation-circle"></i>
                        </div>
                        <div class="flex-grow-1">
                            <span class="badge bg-danger mb-1">Loan Limit Reached</span>
                            <h5 class="fw-bold text-dark mb-1">${doc.title || 'FTU Digital Document'}</h5>
                            <p class="text-danger fw-semibold small mb-2">
                                <i class="fa fa-ban me-1"></i> Cannot borrow additional digital documents
                            </p>
                            <p class="mb-2 small text-secondary">
                                Patron group <strong>${groupName}</strong> has a maximum limit of <strong>${maxLoans} concurrent digital loans</strong>.
                                You currently have <strong>${activeLoans}/${maxLoans} items</strong> checked out.
                            </p>
                            <div class="p-2 rounded bg-white border border-danger-subtle small text-danger fw-semibold">
                                <i class="fa fa-info-circle me-1"></i> Policy Requirement: You must return at least one digital document before you can borrow or read a new one!
                            </div>
                        </div>
                    </div>
                </div>
                <div class="d-flex justify-content-between align-items-center pt-2">
                    <span class="small text-muted">
                        Limit: <strong class="text-danger">${activeLoans}/${maxLoans}</strong> (0 remaining)
                    </span>
                    <div class="d-flex gap-2">
                        <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Close</button>
                        <a href="/cgi-bin/koha/opac-user.pl?tab=opac-user-digital-checkouts" class="btn btn-danger fw-bold px-3" style="background: #A31A24; border-color: #A31A24;">
                            <i class="fa fa-list-check me-1"></i> Manage &amp; Return Digital Loans
                        </a>
                    </div>
                </div>
            `;
            return;
        }

        bodyEl.innerHTML = `
            <div class="p-3 bg-light rounded-3 mb-3 border">
                <div class="d-flex align-items-start" style="gap: 15px;">
                    <div style="width: 48px; height: 48px; border-radius: 10px; background: #FEE2E2; color: #A31A24; display: flex; align-items: center; justify-content: center; font-size: 1.5rem; flex-shrink: 0;">
                        <i class="fa fa-book"></i>
                    </div>
                    <div class="flex-grow-1">
                        <h5 class="fw-bold text-dark mb-1">${doc.title || 'FTU Digital Document'}</h5>
                        <p class="text-muted small mb-2"><i class="fa fa-user-edit me-1"></i> Author: <strong>${doc.author || 'Foreign Trade University'}</strong></p>
                        
                        <div class="row g-2 mt-1">
                            <div class="col-6">
                                <div class="p-2 bg-white rounded border small">
                                    <span class="text-muted d-block">Lending Duration:</span>
                                    <strong class="text-danger"><i class="fa fa-calendar-alt me-1"></i> 14 days</strong> (online reading)
                                </div>
                            </div>
                            <div class="col-6">
                                <div class="p-2 bg-white rounded border small">
                                    <span class="text-muted d-block">Remaining Loans:</span>
                                    <strong class="text-success"><i class="fa fa-check me-1"></i> ${remainingLoans} / ${maxLoans} slots</strong>
                                </div>
                            </div>
                        </div>
                    </div>
                </div>
            </div>

            <div class="alert alert-info py-2 px-3 mb-3 small d-flex align-items-center" style="border-radius: 8px;">
                <i class="fa fa-shield-alt text-primary me-2 fa-lg"></i>
                <div>
                    Protected by FTU Digital Rights Management (DRM). Full text is available online with forensic identity watermarking. Unauthorized copying or distribution is prohibited.
                </div>
            </div>

            <div class="d-flex justify-content-between align-items-center pt-2">
                <span class="small text-muted">
                    <i class="fa fa-user-tag me-1"></i> ${groupName}
                </span>
                <div class="d-flex gap-2">
                    <button type="button" class="btn btn-light fw-semibold" data-bs-dismiss="modal">Cancel</button>
                    <button type="button" class="btn btn-danger fw-bold px-4" id="ftuBtnDoBorrow" style="background: #A31A24; border-color: #A31A24;">
                        <i class="fa fa-check me-1"></i> Confirm Loan &amp; Read Now
                    </button>
                </div>
            </div>
        `;

        document.getElementById('ftuBtnDoBorrow').onclick = function() {
            var btn = this;
            btn.disabled = true;
            btn.innerHTML = '<i class="fa fa-spinner fa-spin me-1"></i> Activating digital loan...';

            var drmBase = getDrmApiBase();
            fetch(drmBase + '/lending/borrow', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({
                    patronId: quota.patronId,
                    bitstreamUuid: doc.bitstreamUuid,
                    itemUuid: doc.itemUuid,
                    patronName: quota.patronName
                })
            })
            .then(function(res) { return res.json(); })
            .then(function(borrowRes) {
                if (!borrowRes.success) {
                    throw new Error(borrowRes.error || 'Failed to borrow digital document');
                }
                if (borrowRes.readerUrl) {
                    window.open(borrowRes.readerUrl, '_blank');
                }
                if (typeof window.ftuReloadDigitalLoans === 'function') {
                    window.ftuReloadDigitalLoans();
                }
                var modal = bootstrap.Modal.getInstance(document.getElementById('ftuDigitalLendingModal'));
                if (modal) modal.hide();
            })
            .catch(function(err) {
                alert('Borrowing error: ' + err.message);
                btn.disabled = false;
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Confirm Loan &amp; Read Now';
            });
        };
    }

    document.addEventListener('click', function(e) {
        var a = e.target.closest('a');
        if (!a) return;
        var href = a.getAttribute('href') || '';
        var text = (a.textContent || '').trim().toLowerCase();

        var isFullTextLink = false;
        var itemUuid = null;
        var bitstreamUuid = null;

        if (text.includes('truy cập toàn văn') || text.includes('toàn văn số') || text.includes('online access') || text.includes('full text') || a.getAttribute('property') === 'url') {
            if (href.includes('/items/') || href.includes('/bitstreams/') || href.includes('/handle/') || href.includes('/elib/')) {
                isFullTextLink = true;
            }
        } else if (href.includes('/items/') || href.includes('/bitstreams/')) {
            isFullTextLink = true;
        }

        if (isFullTextLink) {
            e.preventDefault();
            e.stopPropagation();

            var itemMatch = href.match(/\/items\/([a-f0-9\-]{36})/i);
            if (itemMatch) itemUuid = itemMatch[1];

            var bsMatch = href.match(/\/bitstreams\/([a-f0-9\-]{36})/i);
            if (bsMatch) bitstreamUuid = bsMatch[1];

            var biblionumber = null;
            var bibInput = document.querySelector('input[name="biblionumber"], input#biblionumber');
            if (bibInput) biblionumber = bibInput.value;

            window.ftuOpenDigitalLendingModal({
                itemUuid: itemUuid,
                bitstreamUuid: bitstreamUuid,
                biblionumber: biblionumber,
                fallbackUrl: href
            });
            return false;
        }
    }, true);

    window.ftuReloadDigitalLoans = function() {
        var patron = getLoggedInPatron();
        if (!patron || !patron.patronId) return;

        var panelEl = document.getElementById('opac-user-digital-checkouts_panel');
        var badgeEl = document.getElementById('digital-loans-count-badge');
        if (!panelEl) return;

        var drmBase = getDrmApiBase();
        fetch(drmBase + '/lending/patron/' + encodeURIComponent(patron.patronId))
            .then(function(res) { return res.json(); })
            .then(function(data) {
                if (!data.success) return;
                var loans = data.loans || [];
                var quota = data.quota || {};

                if (badgeEl) {
                    badgeEl.textContent = loans.length;
                }
                renderDigitalLoansPanel(panelEl, loans, quota);
            })
            .catch(function(err) {
                console.warn('[FTU-DIGITAL-LENDING] Error loading loans:', err);
            });
    };

    function renderDigitalLoansPanel(container, loans, quota) {
        var maxLoans = quota.maxActiveLoans || 5;
        var activeCount = loans.length;
        var remaining = Math.max(0, maxLoans - activeCount);
        var groupName = quota.groupName || 'FTU Patron';

        var html = `
            <div class="row g-3 mb-4 mt-1">
                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Patron Group</span>
                            <span class="badge bg-danger-subtle text-danger border border-danger-subtle">${quota.groupCode || 'GRP_UG_STD'}</span>
                        </div>
                        <h6 class="fw-bold text-dark mb-1">${groupName}</h6>
                        <span class="small text-muted">Loan Limit: <strong>${maxLoans} digital documents</strong></span>
                    </div>
                </div>

                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Active Digital Loans</span>
                            <span class="badge ${remaining > 0 ? 'bg-success-subtle text-success border border-success-subtle' : 'bg-danger-subtle text-danger border border-danger-subtle'}">
                                ${remaining > 0 ? remaining + ' slots left' : 'Limit reached'}
                            </span>
                        </div>
                        <h3 class="fw-bold mb-0 text-dark">${activeCount} <small class="text-muted fs-6 fw-normal">/ ${maxLoans} books</small></h3>
                        <div class="progress mt-2" style="height: 6px;">
                            <div class="progress-bar ${activeCount >= maxLoans ? 'bg-danger' : 'bg-success'}" style="width: ${(activeCount / maxLoans) * 100}%;"></div>
                        </div>
                    </div>
                </div>

                <div class="col-12 col-md-4">
                    <div class="ftu-card-stat">
                        <div class="d-flex align-items-center justify-content-between mb-2">
                            <span class="text-muted small fw-bold text-uppercase">Loan Period</span>
                            <span class="badge bg-primary-subtle text-primary border border-primary-subtle">DRM Security</span>
                        </div>
                        <h6 class="fw-bold text-dark mb-1">14 Days / Loan</h6>
                        <span class="small text-muted">Automatic revocation upon expiration or early return</span>
                    </div>
                </div>
            </div>
        `;

        if (loans.length === 0) {
            html += `
                <div class="text-center py-5 bg-light rounded-3 border">
                    <div style="width: 72px; height: 72px; margin: 0 auto 1rem; border-radius: 50%; background: #E2E8F0; display: flex; align-items: center; justify-content: center; color: #64748B; font-size: 2rem;">
                        <i class="fa fa-book-open"></i>
                    </div>
                    <h5 class="fw-bold text-dark mb-1">No Active Digital Loans</h5>
                    <p class="text-muted small mb-3" style="max-width: 450px; margin: 0 auto;">
                        Search our digital repository to borrow and read academic literature anywhere, anytime.
                    </p>
                    <a href="/cgi-bin/koha/opac-search.pl" class="btn btn-outline-danger btn-sm px-3 fw-semibold">
                        <i class="fa fa-search me-1"></i> Browse Digital Documents
                    </a>
                </div>
            `;
        } else {
            html += `
                <div class="table-responsive">
                    <table class="table table-bordered table-hover align-middle" id="digital-checkouts-table">
                        <thead>
                            <tr>
                                <th style="width: 50px;" class="text-center">#</th>
                                <th>Title &amp; Author</th>
                                <th style="width: 130px;" class="text-center">Checkout Date</th>
                                <th style="width: 150px;" class="text-center">Due Date</th>
                                <th style="width: 120px;" class="text-center">Status</th>
                                <th style="width: 180px;" class="text-center">Action</th>
                            </tr>
                        </thead>
                        <tbody>
            `;

            loans.forEach(function(item, idx) {
                var checkoutDate = item.checkoutTime ? new Date(item.checkoutTime).toLocaleDateString('en-US') : '--';
                var dueDate = item.dueTime ? new Date(item.dueTime).toLocaleDateString('en-US') : '--';
                var daysLeft = item.daysRemaining || 0;
                var badgeClass = daysLeft > 3 ? 'bg-success' : (daysLeft > 0 ? 'bg-warning text-dark' : 'bg-danger');
                var badgeText = daysLeft > 0 ? (daysLeft + ' days left') : 'Expired';

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
                                <a href="${item.readerUrl}" target="_blank" class="btn btn-outline-primary fw-semibold" title="Read Online">
                                    <i class="fa fa-book-reader me-1"></i> Read
                                </a>
                                <button type="button" class="btn btn-outline-danger fw-semibold btn-return-digital" data-title="${encodeURIComponent(item.title)}" data-lending-id="${item.lendingId}" data-bitstream-uuid="${item.bitstreamUuid}" title="Return Document">
                                    <i class="fa fa-undo me-1"></i> Return
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

        var returnBtns = container.querySelectorAll('.btn-return-digital');
        returnBtns.forEach(function(btn) {
            btn.addEventListener('click', function() {
                var docTitle = decodeURIComponent(this.getAttribute('data-title') || 'Digital Document');
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

    var btnConfirmReturn = document.getElementById('ftuBtnConfirmReturn');
    if (btnConfirmReturn) {
        btnConfirmReturn.addEventListener('click', function() {
            if (!returnTargetDoc) return;
            var patron = getLoggedInPatron();
            if (!patron || !patron.patronId) return;

            var btn = this;
            btn.disabled = true;
            btn.innerHTML = '<i class="fa fa-spinner fa-spin me-1"></i> Processing return...';

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
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Return Document Now';

                var retModalEl = document.getElementById('ftuDigitalReturnModal');
                var modal = bootstrap.Modal.getInstance(retModalEl);
                if (modal) modal.hide();

                if (!retRes.success) {
                    alert('Return error: ' + retRes.error);
                    return;
                }

                window.ftuReloadDigitalLoans();
            })
            .catch(function(err) {
                alert('Connection error: ' + err.message);
                btn.disabled = false;
                btn.innerHTML = '<i class="fa fa-check me-1"></i> Return Document Now';
            });
        });
    }

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

        if (document.getElementById('opac-user-digital-checkouts_panel')) {
            window.ftuReloadDigitalLoans();
        }
    });

})();
</script>
