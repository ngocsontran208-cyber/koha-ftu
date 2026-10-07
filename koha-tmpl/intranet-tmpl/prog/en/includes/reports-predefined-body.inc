<style nonce="[% Koha.CSPNonce | $raw %]">
/* ------------------------------------------------------------- */
/* STYLES CHO CÂY DANH MỤC BÁO CÁO CÓ SẴN (THEO HÌNH 1)         */
/* ------------------------------------------------------------- */
.ftu-report-tree-card {
    background: #ffffff;
    border: 1px solid #dcdfe6;
    border-radius: 4px;
    padding: 12px 14px;
    min-height: 520px;
    box-shadow: 0 1px 3px rgba(0,0,0,0.05);
}

.ftu-tree-root {
    font-size: 15px;
    font-weight: 700;
    color: #1a73e8;
    margin-bottom: 10px;
    display: flex;
    align-items: center;
    gap: 8px;
    cursor: default;
}

.ftu-tree-root i.fa-star {
    color: #1a73e8;
    font-size: 16px;
}

.ftu-tree-list {
    list-style: none;
    padding-left: 12px;
    margin: 0;
    position: relative;
    border-left: 1px dotted #8fa3b5;
    margin-left: 8px;
}

.ftu-tree-item {
    position: relative;
    padding: 9px 0 9px 18px;
    line-height: 1.35;
}

.ftu-tree-item::before {
    content: "";
    position: absolute;
    top: 19px;
    left: -1px;
    width: 14px;
    border-top: 1px dotted #8fa3b5;
}

.ftu-tree-link {
    color: #2c3e50;
    text-decoration: none;
    font-size: 14px;
    display: block;
    transition: all 0.15s ease;
    border-radius: 3px;
    padding: 4px 6px;
}

.ftu-tree-link:hover {
    color: #1a73e8;
    background: #f1f6fd;
    text-decoration: none;
}

.ftu-tree-item.active .ftu-tree-link {
    color: #0b57d0;
    font-weight: 700;
    background: #e8f0fe;
    border-left: 3px solid #1a73e8;
    padding-left: 8px;
}

/* ------------------------------------------------------------- */
/* STYLES CHO DROPDOWN TÌM KIẾM CHỌN BÁO CÁO (THEO HÌNH 2)       */
/* ------------------------------------------------------------- */
.ftu-dropdown-container {
    position: relative;
    width: 100%;
    margin-bottom: 16px;
}

.ftu-custom-select-trigger {
    background: #ffffff;
    border: 1px solid #1a73e8;
    border-radius: 4px;
    padding: 7px 12px;
    font-size: 14px;
    font-weight: 500;
    color: #2c3e50;
    cursor: pointer;
    display: flex;
    justify-content: space-between;
    align-items: center;
    box-shadow: 0 1px 2px rgba(26,115,232,0.15);
}

.ftu-custom-select-trigger:focus,
.ftu-custom-select-trigger:hover {
    border-color: #0b57d0;
    box-shadow: 0 0 0 2px rgba(26,115,232,0.25);
}

.ftu-dropdown-menu {
    position: absolute;
    top: calc(100% + 2px);
    left: 0;
    right: 0;
    background: #ffffff;
    border: 1px solid #1a73e8;
    border-radius: 4px;
    box-shadow: 0 4px 12px rgba(0,0,0,0.15);
    z-index: 1050;
    display: none;
    padding: 6px 0;
}

.ftu-dropdown-search-wrap {
    padding: 6px 10px 8px 10px;
    border-bottom: 1px solid #e2e8f0;
    position: relative;
}

.ftu-dropdown-search-input {
    width: 100%;
    padding: 6px 28px 6px 10px;
    font-size: 13px;
    border: 1px solid #cbd5e1;
    border-radius: 3px;
    outline: none;
}

.ftu-dropdown-search-input:focus {
    border-color: #1a73e8;
}

.ftu-search-icon {
    position: absolute;
    right: 18px;
    top: 14px;
    color: #64748b;
    pointer-events: none;
    font-size: 13px;
}

.ftu-dropdown-options-list {
    max-height: 280px;
    overflow-y: auto;
    margin: 0;
    padding: 0;
    list-style: none;
}

.ftu-dropdown-option {
    padding: 7px 14px;
    font-size: 13.5px;
    color: #1e293b;
    cursor: pointer;
    transition: background 0.12s;
}

.ftu-dropdown-option:hover {
    background: #f1f5f9;
}

.ftu-dropdown-option.selected {
    background: #1a73e8;
    color: #ffffff !important;
    font-weight: 600;
}

/* ------------------------------------------------------------- */
/* STYLES CHO BỘ LỌC, SUMMARY CARDS & BẢNG KẾT QUẢ              */
/* ------------------------------------------------------------- */
.ftu-filter-panel {
    background: #f8fafc;
    border: 1px solid #e2e8f0;
    border-radius: 5px;
    padding: 12px 16px;
}

.table-ftu-report {
    background: #ffffff;
    border: 1px solid #dcdfe6;
    font-size: 13.5px;
}

.table-ftu-report thead th {
    background: #f1f5f9;
    color: #334155;
    font-weight: 700;
    border-bottom: 2px solid #cbd5e1;
    padding: 9px 10px;
    vertical-align: middle;
}

.table-ftu-report tbody td {
    padding: 8px 10px;
    vertical-align: middle;
    border-top: 1px solid #f1f5f9;
}

.table-ftu-report tbody tr:hover {
    background-color: #f8fafc;
}

.table-ftu-report tfoot tr td {
    background: #f8fafc;
    font-weight: 700;
    border-top: 2px solid #cbd5e1;
}

.badge-active { background-color: #10b981; color: #fff; padding: 3px 8px; border-radius: 3px; font-size: 11px; }
.badge-expired { background-color: #f59e0b; color: #fff; padding: 3px 8px; border-radius: 3px; font-size: 11px; }
.badge-revoked { background-color: #ef4444; color: #fff; padding: 3px 8px; border-radius: 3px; font-size: 11px; }

/* In ấn */
@media print {
    body * { visibility: hidden; }
    #printable-report-area, #printable-report-area * { visibility: visible; }
    #printable-report-area { position: absolute; left: 0; top: 0; width: 100%; }
    .no-print { display: none !important; }
}
</style>

<!-- KHUNG CHÍNH GỒM 2 CỘT: CÂY DANH MỤC (HÌNH 1) & KHUNG BÁO CÁO (HÌNH 2) -->
<div class="row pt-2">
    
    <!-- CỘT BÊN TRÁI: CÂY DANH MỤC BÁO CÁO (HÌNH 1) -->
    <div class="col-md-3 col-lg-3 mb-3">
        <div class="ftu-report-tree-card">
            <div class="ftu-tree-root">
                <i class="fa fa-star"></i> Báo cáo
            </div>
            <ul class="ftu-tree-list">
                <li class="ftu-tree-item active">
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('digital_access')">
                        Báo cáo thống kê truy cập tài liệu số
                    </a>
                </li>
                <li class="ftu-tree-item">
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('circ')">
                        Báo cáo lưu thông
                    </a>
                </li>
                <li class="ftu-tree-item">
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('digital_docs')">
                        Báo cáo tài liệu số
                    </a>
                </li>
                <li class="ftu-tree-item">
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('inventory')">
                        Báo cáo kho
                    </a>
                </li>
                <li class="ftu-tree-item">
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('serials')">
                        Báo cáo báo tạp chí
                    </a>
                </li>
            </ul>
        </div>
    </div>

    <!-- CỘT BÊN PHẢI: KHUNG CHỌN BÁO CÁO & XUẤT SỐ LIỆU (HÌNH 2) -->
    <div class="col-md-9 col-lg-9 mb-3">
        <div class="card shadow-sm p-3 bg-white" style="border: 1px solid #dcdfe6; min-height: 520px;">
            
            <!-- TIÊU ĐỀ KHU VỰC BÁO CÁO -->
            <div class="d-flex justify-content-between align-items-center pb-2 mb-3 border-bottom">
                <h4 id="category_title" class="mb-0" style="color: #0d6efd; font-weight: 700; font-size: 17px; text-transform: uppercase;">
                    Báo cáo thống kê truy cập tài liệu số
                </h4>
                <span class="badge bg-light text-dark border">
                    <i class="fa fa-calendar-alt text-muted"></i> Ngày: [% today | html %]
                </span>
            </div>

            <!-- DROPDOWN CHỌN BÁO CÁO (THEO CHUẨN HÌNH 2) -->
            <div class="ftu-dropdown-container no-print">
                <div class="ftu-custom-select-trigger" id="select_trigger" onclick="toggleDropdown()">
                    <span id="selected_label">--- Chọn ---</span>
                    <i class="fa fa-caret-down text-primary"></i>
                </div>
                
                <div class="ftu-dropdown-menu" id="dropdown_menu">
                    <div class="ftu-dropdown-search-wrap">
                        <input type="text" id="report_search_input" class="ftu-dropdown-search-input" placeholder="" onkeyup="filterReports(this.value)" />
                        <i class="fa fa-search ftu-search-icon"></i>
                    </div>
                    <ul class="ftu-dropdown-options-list" id="options_list">
                        <li class="ftu-dropdown-option" data-id="" onclick="selectReport('', '--- Chọn ---')">
                            --- Chọn ---
                        </li>
                        <li class="ftu-dropdown-option" data-id="online_users" onclick="selectReport('online_users', 'Thống kê truy cập chi tiết các user đang đăng nhập')">
                            Thống kê truy cập chi tiết các user đang đăng nhập
                        </li>
                        <li class="ftu-dropdown-option" data-id="access_over_time" onclick="selectReport('access_over_time', 'Báo cáo tổng lượt truy cập tài liệu số theo thời gian')">
                            Báo cáo tổng lượt truy cập tài liệu số theo thời gian
                        </li>
                        <li class="ftu-dropdown-option" data-id="top_used_docs" onclick="selectReport('top_used_docs', 'THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT')">
                            THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT
                        </li>
                        <li class="ftu-dropdown-option" data-id="top_interactive_docs" onclick="selectReport('top_interactive_docs', 'THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT')">
                            THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT
                        </li>
                        <li class="ftu-dropdown-option selected" data-id="opac_visits_ftu2" onclick="selectReport('opac_visits_ftu2', 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2')">
                            TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2
                        </li>
                        <li class="ftu-dropdown-option" data-id="top_patrons" onclick="selectReport('top_patrons', 'THỐNG KÊ BẠN ĐỌC SỬ DỤNG TÀI LIỆU SỐ NHIỀU NHẤT')">
                            THỐNG KÊ BẠN ĐỌC SỬ DỤNG TÀI LIỆU SỐ NHIỀU NHẤT
                        </li>
                        <li class="ftu-dropdown-option" data-id="collection_usage" onclick="selectReport('collection_usage', 'THỐNG KÊ LƯỢT SỬ DỤNG CÁC BỘ SƯU TẬP')">
                            THỐNG KÊ LƯỢT SỬ DỤNG CÁC BỘ SƯU TẬP
                        </li>
                    </ul>
                </div>
            </div>

            <!-- BỘ LỌC THỜI GIAN -->
            <div class="ftu-filter-panel no-print">
                <div class="row align-items-end g-2">
                    <div class="col-md-3">
                        <label class="form-label mb-1" style="font-size: 13px; font-weight: 600;">Từ ngày:</label>
                        <input type="date" id="filter_from_date" class="form-control form-control-sm" value="[% from_date || '2026-09-01' | html %]" />
                    </div>
                    <div class="col-md-3">
                        <label class="form-label mb-1" style="font-size: 13px; font-weight: 600;">Đến ngày:</label>
                        <input type="date" id="filter_to_date" class="form-control form-control-sm" value="[% to_date || '2026-10-07' | html %]" />
                    </div>
                    <input type="hidden" id="filter_branch" value="CPL" />
                    <div class="col-md-6 text-end">
                        <button type="button" class="btn btn-primary btn-sm" onclick="loadReportData()">
                            <i class="fa fa-search"></i> Xem báo cáo
                        </button>
                        <button type="button" class="btn btn-success btn-sm ms-1" onclick="exportExcel()">
                            <i class="fa fa-file-excel"></i> Xuất Excel
                        </button>
                        <button type="button" class="btn btn-outline-secondary btn-sm ms-1" onclick="printReport()">
                            <i class="fa fa-print"></i> In
                        </button>
                    </div>
                </div>
            </div>

            <!-- KHU VỰC IN & HIỂN THỊ KẾT QUẢ BÁO CÁO -->
            <div id="printable-report-area">
                
                <!-- TIÊU ĐỀ IN BÁO CÁO CHUẨN A4 -->
                <div class="d-none d-print-block mb-4 text-center">
                    <h3 style="font-size: 16px; margin: 0; font-weight: bold;">TRƯỜNG ĐẠI HỌC NGOẠI THƯƠNG</h3>
                    <h4 style="font-size: 14px; margin: 3px 0 12px 0;">THƯ VIỆN - TRUNG TÂM THÔNG TIN</h4>
                    <h2 id="print_report_title" style="font-size: 18px; margin: 15px 0 5px 0; font-weight: bold; text-transform: uppercase;">
                        BÁO CÁO THỐNG KÊ
                    </h2>
                    <p id="print_report_subtitle" style="font-size: 13px; font-style: italic; margin-bottom: 15px;">
                        Từ ngày: ... Đến ngày: ...
                    </p>
                </div>

                <!-- BẢNG DỮ LIỆU BÁO CÁO -->
                <div class="table-responsive">
                    <div id="loading_indicator" class="text-center py-4 d-none">
                        <i class="fa fa-spinner fa-spin fa-2x text-primary mb-2"></i>
                        <div class="text-muted" style="font-size: 13.5px;">Đang tổng hợp dữ liệu báo cáo từ DRM Service & Koha ILS...</div>
                    </div>
                    <table class="table table-bordered table-hover table-ftu-report" id="report_table">
                        <thead id="report_table_head">
                            <!-- Header động theo loại báo cáo -->
                        </thead>
                        <tbody id="report_table_body">
                            <!-- Dữ liệu động -->
                        </tbody>
                        <tfoot id="report_table_foot">
                            <!-- Footer tổng kết -->
                        </tfoot>
                    </table>
                </div>

                <!-- CHÂN TRANG IN -->
                <div class="d-none d-print-block mt-5 pt-4">
                    <div class="row text-center">
                        <div class="col-6">
                            <p><strong>NGƯỜI LẬP BIỂU</strong></p>
                            <p style="margin-top: 60px;">(Ký và ghi rõ họ tên)</p>
                        </div>
                        <div class="col-6">
                            <p><em>Ngày ..... tháng ..... năm 2026</em></p>
                            <p><strong>PHỤ TRÁCH THƯ VIỆN</strong></p>
                            <p style="margin-top: 60px;">(Ký và ghi rõ họ tên)</p>
                        </div>
                    </div>
                </div>

            </div>
            <!-- /#printable-report-area -->

        </div>
    </div>
</div>

<script nonce="[% Koha.CSPNonce | $raw %]">
var reportCategories = {
    digital_access: {
        title: 'BÁO CÁO THỐNG KÊ TRUY CẬP TÀI LIỆU SỐ',
        defaultReport: 'opac_visits_ftu2',
        defaultTitle: 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2',
        reports: [
            { id: 'online_users', title: 'Thống kê truy cập chi tiết các user đang đăng nhập' },
            { id: 'access_over_time', title: 'Báo cáo tổng lượt truy cập tài liệu số theo thời gian' },
            { id: 'top_used_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT' },
            { id: 'top_interactive_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT' },
            { id: 'opac_visits_ftu2', title: 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2' },
            { id: 'top_patrons', title: 'THỐNG KÊ BẠN ĐỌC SỬ DỤNG TÀI LIỆU SỐ NHIỀU NHẤT' },
            { id: 'collection_usage', title: 'THỐNG KÊ LƯỢT SỬ DỤNG CÁC BỘ SƯU TẬP' }
        ]
    },
    circ: {
        title: 'BÁO CÁO LƯU THÔNG',
        defaultReport: 'circ_by_class',
        defaultTitle: 'Thống kê tài liệu đang mượn theo môn loại',
        reports: [
            { id: 'circ_by_class', title: 'Thống kê tài liệu đang mượn theo môn loại' },
            { id: 'circ_flow_by_class', title: 'Thống kê tài liệu mượn trả theo môn loại' },
            { id: 'circ_unused_docs', title: 'Thống kê tài liệu không có người mượn' },
            { id: 'circ_total_docs', title: 'Thống kê tổng số tài liệu' },
            { id: 'circ_overdue_docs', title: 'Thống kê tài liệu đang mượn quá hạn' },
            { id: 'circ_popular_docs', title: 'Thống kê tài liệu được yêu thích' },
            { id: 'circ_popular_authors', title: 'Thống kê tác giả được yêu thích' },
            { id: 'circ_shelving_cart', title: 'Thống kê tài liệu mượn, trả vào kho' },
            { id: 'circ_patron_loans', title: 'Thống kê mượn tài liệu của bạn đọc' },
            { id: 'circ_doc_history', title: 'Thống kê lịch sử mượn - trả của tài liệu' }
        ]
    },
    digital_docs: {
        title: 'BÁO CÁO TÀI LIỆU SỐ',
        defaultReport: 'top_used_docs',
        defaultTitle: 'THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT',
        reports: [
            { id: 'top_used_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT' },
            { id: 'top_interactive_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT' },
            { id: 'collection_usage', title: 'THỐNG KÊ LƯỢT SỬ DỤNG CÁC BỘ SƯU TẬP' }
        ]
    }
};

var currentCategory = 'digital_access';
var currentReportId = 'opac_visits_ftu2';
var currentReportTitle = 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2';

document.addEventListener('DOMContentLoaded', function() {
    renderDropdownOptions(currentCategory);
    selectReport(currentReportId, currentReportTitle);

    document.addEventListener('click', function(e) {
        var container = document.querySelector('.ftu-dropdown-container');
        if (container && !container.contains(e.target)) {
            closeDropdown();
        }
    });
});

function renderDropdownOptions(catKey) {
    var cat = reportCategories[catKey];
    if (!cat) return;

    var list = document.getElementById('options_list');
    list.innerHTML = '<li class="ftu-dropdown-option" data-id="" onclick="selectReport(\'\', \'--- Chọn ---\')">--- Chọn ---</li>';

    cat.reports.forEach(function(r) {
        var isSel = (r.id === currentReportId) ? ' selected' : '';
        var li = document.createElement('li');
        li.className = 'ftu-dropdown-option' + isSel;
        li.setAttribute('data-id', r.id);
        li.textContent = r.title;
        li.onclick = function() { selectReport(r.id, r.title); };
        list.appendChild(li);
    });
}

function toggleDropdown() {
    var menu = document.getElementById('dropdown_menu');
    if (menu.style.display === 'block') {
        closeDropdown();
    } else {
        openDropdown();
    }
}

function openDropdown() {
    var menu = document.getElementById('dropdown_menu');
    menu.style.display = 'block';
    var inp = document.getElementById('report_search_input');
    inp.value = '';
    filterReports('');
    setTimeout(function() { inp.focus(); }, 50);
}

function closeDropdown() {
    var menu = document.getElementById('dropdown_menu');
    if (menu) menu.style.display = 'none';
}

function filterReports(keyword) {
    var term = (keyword || '').toLowerCase().trim();
    var items = document.querySelectorAll('.ftu-dropdown-option');
    items.forEach(function(item) {
        var txt = item.textContent.toLowerCase();
        if (!term || txt.indexOf(term) !== -1) {
            item.style.display = 'block';
        } else {
            item.style.display = 'none';
        }
    });
}

function selectReport(reportId, reportTitle) {
    currentReportId = reportId;
    currentReportTitle = reportTitle;
    document.getElementById('selected_label').textContent = reportTitle;

    var items = document.querySelectorAll('.ftu-dropdown-option');
    items.forEach(function(item) {
        if (item.getAttribute('data-id') === reportId) {
            item.classList.add('selected');
        } else {
            item.classList.remove('selected');
        }
    });

    closeDropdown();

    if (!reportId) {
        document.getElementById('report_table_head').innerHTML = '';
        document.getElementById('report_table_body').innerHTML = '<tr><td class="text-center py-4 text-muted">Vui lòng chọn một loại báo cáo từ danh sách trên để xem số liệu.</td></tr>';
        document.getElementById('report_table_foot').innerHTML = '';
        return;
    }

    loadReportData();
}

function switchCategory(cat) {
    var items = document.querySelectorAll('.ftu-tree-item');
    items.forEach(function(i) { i.classList.remove('active'); });

    if (reportCategories[cat]) {
        if (event && event.currentTarget) {
            event.currentTarget.closest('.ftu-tree-item').classList.add('active');
        }
        currentCategory = cat;
        var catData = reportCategories[cat];
        document.getElementById('category_title').textContent = catData.title;
        renderDropdownOptions(cat);
        selectReport(catData.defaultReport, catData.defaultTitle);
    } else {
        if (event && event.currentTarget) {
            event.currentTarget.closest('.ftu-tree-item').classList.add('active');
        }
        var catName = (event && event.currentTarget) ? event.currentTarget.textContent.trim() : cat;
        document.getElementById('category_title').textContent = catName;
        document.getElementById('selected_label').textContent = '--- Chọn ---';
        document.getElementById('options_list').innerHTML = '<li class="ftu-dropdown-option" data-id="" onclick="selectReport(\'\', \'--- Chọn ---\')">--- Chọn ---</li>';
        document.getElementById('report_table_head').innerHTML = '';
        document.getElementById('report_table_body').innerHTML = '<tr><td class="text-center py-4 text-muted"><i class="fa fa-info-circle text-primary"></i> Danh mục <strong>' + catName + '</strong> đang được kết nối dữ liệu. Vui lòng chuyển sang <strong>Báo cáo lưu thông</strong> hoặc <strong>Báo cáo thống kê truy cập tài liệu số</strong>.</td></tr>';
        document.getElementById('report_table_foot').innerHTML = '';
    }
}

function loadReportData() {
    if (!currentReportId) return;

    var fromDate = document.getElementById('filter_from_date').value;
    var toDate = document.getElementById('filter_to_date').value;
    var branch = document.getElementById('filter_branch').value;

    document.getElementById('loading_indicator').classList.remove('d-none');
    document.getElementById('report_table').classList.add('opacity-50');

    var apiUrl = '/cgi-bin/koha/reports/digital-reports.pl?op=api_data'
        + '&report_id=' + encodeURIComponent(currentReportId)
        + '&from_date=' + encodeURIComponent(fromDate)
        + '&to_date=' + encodeURIComponent(toDate)
        + '&branch=' + encodeURIComponent(branch);

    fetch(apiUrl)
        .then(function(res) { return res.json(); })
        .then(function(data) {
            document.getElementById('loading_indicator').classList.add('d-none');
            document.getElementById('report_table').classList.remove('opacity-50');
            renderTable(data);
        })
        .catch(function(err) {
            document.getElementById('loading_indicator').classList.add('d-none');
            document.getElementById('report_table').classList.remove('opacity-50');
            console.error('Error fetching report:', err);
            document.getElementById('report_table_body').innerHTML = '<tr><td colspan="10" class="text-center text-danger py-4"><i class="fa fa-exclamation-triangle"></i> Lỗi nạp số liệu: ' + err.message + '</td></tr>';
        });
}

function renderTable(res) {
    var rows = res.rows || [];
    var summary = res.summary || {};

    document.getElementById('print_report_title').textContent = currentReportTitle;
    document.getElementById('print_report_subtitle').textContent = 'Từ ngày: ' + document.getElementById('filter_from_date').value + ' - Đến ngày: ' + document.getElementById('filter_to_date').value;

    var thead = document.getElementById('report_table_head');
    var tbody = document.getElementById('report_table_body');
    var tfoot = document.getElementById('report_table_foot');
    thead.innerHTML = '';
    tbody.innerHTML = '';
    tfoot.innerHTML = '';

    if (rows.length === 0) {
        tbody.innerHTML = '<tr><td colspan="10" class="text-center py-4 text-muted"><i class="fa fa-info-circle"></i> Không tìm thấy bản ghi nào phù hợp với bộ lọc trong khoảng thời gian đã chọn.</td></tr>';
        return;
    }

    // =========================================================================
    // 1. NHÓM BÁO CÁO TRUY CẬP TÀI LIỆU SỐ
    // =========================================================================

    // 1.1 Thống kê truy cập chi tiết các user đang đăng nhập
    if (currentReportId === 'online_users') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã bạn đọc</th>'
            + '<th>Họ và tên</th>'
            + '<th>Đối tượng</th>'
            + '<th>Tài liệu đang đọc</th>'
            + '<th>Địa chỉ IP</th>'
            + '<th>Thời gian cấp phiên</th>'
            + '<th>Tương tác cuối</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var statusBadge = r.status_text === 'Đang hoạt động' ? '<span class="badge-active"><i class="fa fa-check-circle"></i> Đang hoạt động</span>' :
                              r.status_text === 'Đã hết phiên' ? '<span class="badge-expired"><i class="fa fa-clock"></i> Hết hạn</span>' :
                              '<span class="badge-revoked"><i class="fa fa-ban"></i> Thu hồi</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.patron_id || '') + '</code></td>'
                + '<td><strong>' + (r.patron_name || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role_label || '') + '</span></td>'
                + '<td><i class="fa fa-book text-muted me-1"></i> ' + (r.document_title || '') + '</td>'
                + '<td><small class="text-muted">' + (r.client_ip || '') + '</small></td>'
                + '<td>' + (r.issued_at || '') + '</td>'
                + '<td>' + (r.last_heartbeat || '') + '</td>'
                + '<td class="text-center">' + statusBadge + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="8" class="text-end"><strong>TỔNG SỐ BẢN GHI:</strong></td>'
            + '<td class="text-center text-success"><strong>' + rows.length + '</strong></td>'
            + '</tr>';
    }

    // 1.2 Báo cáo tổng lượt truy cập tài liệu số theo thời gian
    else if (currentReportId === 'access_over_time') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Thời gian (Ngày)</th>'
            + '<th class="text-end">Tổng số phiên truy cập</th>'
            + '<th class="text-end">Lượt mượn tài liệu số</th>'
            + '<th class="text-end">Số bạn đọc tiếp cận</th>'
            + '<th class="text-end">Số tài liệu số được đọc</th>'
            + '<th class="text-end">Lượt xem trang (ước tính)</th>'
            + '</tr>';

        var sumSessions = 0, sumLoans = 0, sumViews = 0;
        rows.forEach(function(r) {
            sumSessions += (r.total_sessions || 0);
            sumLoans += (r.total_loans || 0);
            sumViews += (r.pageviews_est || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-calendar-day text-primary me-1"></i> ' + (r.access_date || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.total_sessions || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary">' + (r.total_loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end">' + (r.unique_users || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end">' + (r.unique_docs || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-muted">' + (r.pageviews_est || 0).toLocaleString('vi-VN') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumSessions.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumLoans.toLocaleString('vi-VN') + '</strong></td>'
            + '<td colspan="2"></td>'
            + '<td class="text-end text-muted"><strong>' + sumViews.toLocaleString('vi-VN') + '</strong></td>'
            + '</tr>';
    }

    // 1.3 THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT
    else if (currentReportId === 'top_used_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Nhan đề tài liệu số</th>'
            + '<th>Tác giả / NXB</th>'
            + '<th>Bộ sưu tập số</th>'
            + '<th class="text-end">Lượt mượn số</th>'
            + '<th class="text-end">Lượt đọc trực tuyến</th>'
            + '<th class="text-end">Bạn đọc tiếp cận</th>'
            + '<th>Lần sử dụng gần nhất</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-secondary">' + r.stt + '</span></td>'
                + '<td><strong class="text-primary"><i class="fa fa-file-pdf text-danger me-1"></i> ' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.collection_name || '') + '</span></td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.loan_count || 0) + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.read_count || 0) + '</td>'
                + '<td class="text-end">' + (r.patron_count || 0) + '</td>'
                + '<td><small class="text-muted">' + (r.last_used || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 1.4 THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT
    else if (currentReportId === 'top_interactive_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Nhan đề tài liệu số</th>'
            + '<th>Tác giả</th>'
            + '<th class="text-end">Tổng phiên tương tác</th>'
            + '<th class="text-end">Số bạn đọc</th>'
            + '<th class="text-end">Thời lượng đọc TB</th>'
            + '<th class="text-end">Lượt xem trang</th>'
            + '<th>Tương tác cuối</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-primary">' + r.stt + '</span></td>'
                + '<td><strong><i class="fa fa-book-reader text-primary me-1"></i> ' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.session_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end">' + (r.reader_count || 0) + '</td>'
                + '<td class="text-end text-success">' + (r.avg_duration || 0) + ' phút</td>'
                + '<td class="text-end text-muted">' + (r.pageviews || 0).toLocaleString('vi-VN') + '</td>'
                + '<td><small class="text-muted">' + (r.last_interaction || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 1.5 TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY FTU2
    else if (currentReportId === 'opac_visits_ftu2') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Ngày ghi nhận</th>'
            + '<th class="text-end">Lượt đăng nhập OPAC</th>'
            + '<th class="text-end">Lượt tra cứu (Search)</th>'
            + '<th class="text-end">Xem chi tiết biểu ghi</th>'
            + '<th class="text-end">Lượt mượn/đọc số tại FTU2</th>'
            + '<th class="text-end">Tổng lượt tương tác</th>'
            + '</tr>';

        var sumLogins = 0, sumSearches = 0, sumViews = 0, sumReads = 0, sumTotal = 0;
        rows.forEach(function(r) {
            sumLogins += (r.login_count || 0);
            sumSearches += (r.search_count || 0);
            sumViews += (r.detail_views || 0);
            sumReads += (r.digital_reads || 0);
            sumTotal += (r.total_interactions || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-calendar-alt text-primary me-1"></i> ' + (r.visit_date || '') + '</strong></td>'
                + '<td class="text-end text-success">' + (r.login_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info">' + (r.search_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-secondary">' + (r.detail_views || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-warning font-weight-bold">' + (r.digital_reads || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.total_interactions || 0).toLocaleString('vi-VN') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumLogins.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-info"><strong>' + sumSearches.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-secondary"><strong>' + sumViews.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-warning"><strong>' + sumReads.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumTotal.toLocaleString('vi-VN') + '</strong></td>'
            + '</tr>';
    }

    // 1.6 THỐNG KÊ BẠN ĐỌC SỬ DỤNG TÀI LIỆU SỐ NHIỀU NHẤT
    else if (currentReportId === 'top_patrons') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Mã bạn đọc / Số thẻ</th>'
            + '<th>Họ và tên bạn đọc</th>'
            + '<th>Đối tượng / Nhóm</th>'
            + '<th class="text-end">Lượt mượn tài liệu số</th>'
            + '<th class="text-end">Số phiên đọc trực tuyến</th>'
            + '<th class="text-end">Tổng lượt sử dụng</th>'
            + '<th>Lần hoạt động gần nhất</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-secondary">' + r.stt + '</span></td>'
                + '<td><code>' + (r.patron_id || '') + '</code></td>'
                + '<td><strong><i class="fa fa-user-graduate text-muted me-1"></i> ' + (r.patron_name || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role_label || '') + '</span></td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.loan_count || 0) + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.session_count || 0) + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.total_usage || 0) + '</td>'
                + '<td><small class="text-muted">' + (r.last_active || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 1.7 THỐNG KÊ LƯỢT SỬ DỤNG CÁC BỘ SƯU TẬP
    else if (currentReportId === 'collection_usage') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Tên Bộ sưu tập số (DSpace 7)</th>'
            + '<th class="text-end">Tổng số tài liệu trong BST</th>'
            + '<th class="text-end">Lượt mượn tài liệu số</th>'
            + '<th class="text-end">Lượt đọc trực tuyến</th>'
            + '<th class="text-end">Số bạn đọc tiếp cận</th>'
            + '<th class="text-end">Tỷ lệ khai thác</th>'
            + '</tr>';

        var sumItems = 0, sumLoans = 0, sumReads = 0, sumReaders = 0;
        rows.forEach(function(r) {
            sumItems += (r.total_items || 0);
            sumLoans += (r.loans || 0);
            sumReads += (r.reads || 0);
            sumReaders += (r.readers || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-folder-open text-warning me-1"></i> ' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.total_items || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.reads || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end font-weight-bold">' + (r.readers || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.usage_ratio || '0%') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG CÁC BỘ SƯU TẬP DSPACE:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumItems.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumLoans.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-info"><strong>' + sumReads.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end"><strong>' + sumReaders.toLocaleString('vi-VN') + '</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // =========================================================================
    // 2. NHÓM BÁO CÁO LƯU THÔNG (CIRCULATION REPORTS - 10 LOẠI BÁO CÁO)
    // =========================================================================

    // 2.1 Thống kê tài liệu đang mượn theo môn loại
    else if (currentReportId === 'circ_by_class') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã môn loại (DDC)</th>'
            + '<th>Tên môn loại chuyên ngành</th>'
            + '<th class="text-end">Số đầu sách đang mượn</th>'
            + '<th class="text-end">Số bản sách đang mượn</th>'
            + '<th class="text-end">Tỷ lệ (%)</th>'
            + '</tr>';

        var totalTitles = 0, totalItems = 0;
        rows.forEach(function(r) {
            totalTitles += (r.title_count || 0);
            totalItems += (r.item_count || 0);
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong><i class="fa fa-bookmark text-primary me-1"></i> ' + (r.name || '') + '</strong></td>'
                + '<td class="text-end">' + (r.title_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.item_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.ratio || '') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end text-primary"><strong>' + totalTitles.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-success"><strong>' + totalItems.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 2.2 Thống kê tài liệu mượn trả theo môn loại
    else if (currentReportId === 'circ_flow_by_class') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã môn loại (DDC)</th>'
            + '<th>Tên môn loại chuyên ngành</th>'
            + '<th class="text-end">Lượt mượn ra</th>'
            + '<th class="text-end">Lượt trả về</th>'
            + '<th class="text-end">Tổng lượt lưu thông</th>'
            + '<th class="text-end">Tỷ lệ hoàn trả</th>'
            + '</tr>';

        var sumLoans = 0, sumReturns = 0, sumTotal = 0;
        rows.forEach(function(r) {
            sumLoans += (r.loans || 0);
            sumReturns += (r.returns || 0);
            sumTotal += (r.total || 0);
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong>' + (r.name || '') + '</strong></td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.returns || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.total || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-muted">' + (r.ratio || '') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumLoans.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-info"><strong>' + sumReturns.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumTotal.toLocaleString('vi-VN') + '</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 2.3 Thống kê tài liệu không có người mượn
    else if (currentReportId === 'circ_unused_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã vạch (Barcode)</th>'
            + '<th>Ký hiệu phân loại</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Tác giả</th>'
            + '<th>Năm XB</th>'
            + '<th>Vị trí kho xếp giá</th>'
            + '<th class="text-center">Thời gian chưa lưu thông</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td><strong class="text-primary"><i class="fa fa-book me-1"></i> ' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td class="text-center">' + (r.year || '') + '</td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-center"><span class="badge bg-warning text-dark"><i class="fa fa-clock me-1"></i> ' + (r.unused_days || 0) + ' ngày</span></td>'
                + '</tr>';
        });
    }

    // 2.4 Thống kê tổng số tài liệu
    else if (currentReportId === 'circ_total_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Kho lưu trữ tài liệu Phân hiệu FTU2</th>'
            + '<th class="text-end">Tổng số đầu sách (Nhan đề)</th>'
            + '<th class="text-end">Tổng số bản sách (Bản in)</th>'
            + '<th class="text-end">Đang cho mượn</th>'
            + '<th class="text-end">Sẵn sàng phục vụ</th>'
            + '<th class="text-end">Tỷ lệ khả dụng</th>'
            + '</tr>';

        var sumTitles = 0, sumItems = 0, sumLoaned = 0, sumAvail = 0;
        rows.forEach(function(r) {
            sumTitles += (r.titles || 0);
            sumItems += (r.items || 0);
            sumLoaned += (r.loaned || 0);
            sumAvail += (r.available || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-archive text-primary me-1"></i> ' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.titles || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end font-weight-bold text-primary">' + (r.items || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-warning font-weight-bold">' + (r.loaned || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.available || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.ratio || '') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG TOÀN PHÂN HIỆU:</strong></td>'
            + '<td class="text-end font-weight-bold text-primary"><strong>' + sumTitles.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end font-weight-bold text-primary"><strong>' + sumItems.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-warning"><strong>' + sumLoaned.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumAvail.toLocaleString('vi-VN') + '</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 2.5 Thống kê tài liệu đang mượn quá hạn
    else if (currentReportId === 'circ_overdue_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Số thẻ bạn đọc</th>'
            + '<th>Họ và tên</th>'
            + '<th>Đối tượng</th>'
            + '<th>Mã vạch sách</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Ngày mượn</th>'
            + '<th>Hạn trả</th>'
            + '<th class="text-center">Số ngày quá hạn</th>'
            + '<th class="text-end">Tiền phạt ước tính (VNĐ)</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.cardnumber || '') + '</code></td>'
                + '<td><strong><i class="fa fa-user-graduate text-danger me-1"></i> ' + (r.patron_name || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role || '') + '</span></td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong>' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.issue_date || '') + '</td>'
                + '<td><span class="text-danger font-weight-bold">' + (r.due_date || '') + '</span></td>'
                + '<td class="text-center"><span class="badge bg-danger"><i class="fa fa-exclamation-circle me-1"></i> ' + (r.overdue_days || 0) + ' ngày</span></td>'
                + '<td class="text-end font-weight-bold text-danger">' + (r.fine || '0') + ' đ</td>'
                + '</tr>';
        });
    }

    // 2.6 Thống kê tài liệu được yêu thích
    else if (currentReportId === 'circ_popular_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Mã vạch</th>'
            + '<th>Nhan đề sách in</th>'
            + '<th>Tác giả</th>'
            + '<th>Nhà xuất bản</th>'
            + '<th>Môn loại DDC</th>'
            + '<th class="text-end">Tổng lượt mượn</th>'
            + '<th>Lần mượn gần nhất</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-primary">' + r.stt + '</span></td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong class="text-primary"><i class="fa fa-heart text-danger me-1"></i> ' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td>' + (r.publisher || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.class || '') + '</span></td>'
                + '<td class="text-end font-weight-bold text-success" style="font-size: 14.5px;">' + (r.loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td><small class="text-muted">' + (r.last_issue || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 2.7 Thống kê tác giả được yêu thích
    else if (currentReportId === 'circ_popular_authors') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Tên tác giả</th>'
            + '<th>Khoa / Đơn vị công tác</th>'
            + '<th class="text-end">Số đầu sách tại thư viện</th>'
            + '<th class="text-end">Tổng lượt mượn</th>'
            + '<th class="text-end">Số bạn đọc tiếp cận</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-info text-dark">' + r.stt + '</span></td>'
                + '<td><strong><i class="fa fa-user-edit text-primary me-1"></i> ' + (r.author || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.dept || '') + '</span></td>'
                + '<td class="text-end font-weight-bold">' + (r.title_count || 0) + '</td>'
                + '<td class="text-end text-success font-weight-bold" style="font-size: 14.5px;">' + (r.loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.reader_count || 0).toLocaleString('vi-VN') + '</td>'
                + '</tr>';
        });
    }

    // 2.8 Thống kê tài liệu mượn, trả vào kho
    else if (currentReportId === 'circ_shelving_cart') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Ngày ghi nhận</th>'
            + '<th>Kho xếp giá lưu trữ</th>'
            + '<th class="text-end">Lượt mượn ra</th>'
            + '<th class="text-end">Lượt trả về kho</th>'
            + '<th class="text-end">Chờ xếp giá</th>'
            + '<th class="text-end">Tồn kho khả dụng</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-calendar-day text-muted me-1"></i> ' + (r.date || '') + '</strong></td>'
                + '<td><strong><i class="fa fa-warehouse text-warning me-1"></i> ' + (r.location || '') + '</strong></td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.checkouts || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.checkins || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-warning font-weight-bold">' + (r.shelving || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.stock || 0).toLocaleString('vi-VN') + '</td>'
                + '</tr>';
        });
    }

    // 2.9 Thống kê mượn tài liệu của bạn đọc
    else if (currentReportId === 'circ_patron_loans') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">Top</th>'
            + '<th>Mã bạn đọc / MSSV</th>'
            + '<th>Họ và tên bạn đọc</th>'
            + '<th>Đối tượng</th>'
            + '<th>Khoa / Khóa học</th>'
            + '<th class="text-end">Tổng lượt mượn</th>'
            + '<th class="text-end">Sách đang mượn</th>'
            + '<th class="text-end">Sách đã trả</th>'
            + '<th>Lần mượn gần nhất</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-secondary">' + r.stt + '</span></td>'
                + '<td><code>' + (r.patron_id || '') + '</code></td>'
                + '<td><strong><i class="fa fa-user-graduate text-primary me-1"></i> ' + (r.patron_name || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role || '') + '</span></td>'
                + '<td>' + (r.faculty || '') + '</td>'
                + '<td class="text-end font-weight-bold text-primary" style="font-size: 14.5px;">' + (r.total_loans || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-warning font-weight-bold">' + (r.active_loans || 0) + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.return_count || 0) + '</td>'
                + '<td><small class="text-muted">' + (r.last_loan || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 2.10 Thống kê lịch sử mượn - trả của tài liệu
    else if (currentReportId === 'circ_doc_history') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã vạch sách</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Bạn đọc mượn</th>'
            + '<th>Ngày mượn</th>'
            + '<th>Hạn trả</th>'
            + '<th>Ngày trả thực tế</th>'
            + '<th>Thủ thư thực hiện</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var stBadge = r.status === 'Đã trả đúng hạn' ? '<span class="badge bg-success"><i class="fa fa-check-circle"></i> Đã trả</span>' :
                          r.status === 'Quá hạn' ? '<span class="badge bg-danger"><i class="fa fa-exclamation-triangle"></i> Quá hạn</span>' :
                          '<span class="badge bg-primary"><i class="fa fa-book-reader"></i> Đang mượn</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong>' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.patron || '') + '</td>'
                + '<td>' + (r.issue_date || '') + '</td>'
                + '<td>' + (r.due_date || '') + '</td>'
                + '<td>' + (r.ret_date || '') + '</td>'
                + '<td><small class="text-muted">' + (r.staff || '') + '</small></td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '</tr>';
        });
    }
}

function exportExcel() {
    if (!currentReportId) {
        alert('Vui lòng chọn một loại báo cáo trước khi xuất file!');
        return;
    }
    var fromDate = document.getElementById('filter_from_date').value;
    var toDate = document.getElementById('filter_to_date').value;
    var branch = document.getElementById('filter_branch').value;

    var exportUrl = '/cgi-bin/koha/reports/digital-reports.pl?op=export_csv'
        + '&report_id=' + encodeURIComponent(currentReportId)
        + '&from_date=' + encodeURIComponent(fromDate)
        + '&to_date=' + encodeURIComponent(toDate)
        + '&branch=' + encodeURIComponent(branch);

    window.location.href = exportUrl;
}

function printReport() {
    window.print();
}
</script>
