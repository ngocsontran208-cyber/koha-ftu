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
                Báo cáo
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
                    <a href="javascript:void(0)" class="ftu-tree-link" onclick="switchCategory('public_pages')">
                        Báo cáo các trang công khai
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
                    Ngày: [% today | html %]
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
                        <li class="ftu-dropdown-option selected" data-id="opac_visits_ftu2" onclick="selectReport('opac_visits_ftu2', 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU')">
                            TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU
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
                            Xem báo cáo
                        </button>
                        <button type="button" class="btn btn-success btn-sm ms-1" onclick="exportExcel()">
                            Xuất Excel
                        </button>
                        <button type="button" class="btn btn-outline-secondary btn-sm ms-1" onclick="printReport()">
                            In
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
                        <div class="text-muted" style="font-size: 13.5px;">Đang tổng hợp dữ liệu báo cáo từ DRM Service & FTU - HCM LIB...</div>
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
        defaultTitle: 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU',
        reports: [
            { id: 'online_users', title: 'Thống kê truy cập chi tiết các user đang đăng nhập' },
            { id: 'access_over_time', title: 'Báo cáo tổng lượt truy cập tài liệu số theo thời gian' },
            { id: 'top_used_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ ĐƯỢC SỬ DỤNG NHIỀU NHẤT' },
            { id: 'top_interactive_docs', title: 'THỐNG KÊ TÀI LIỆU SỐ CÓ LƯỢT TƯƠNG TÁC CAO NHẤT' },
            { id: 'opac_visits_ftu2', title: 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU' },
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
        defaultReport: 'digital_page_count',
        defaultTitle: 'Thống kê số trang tài liệu',
        reports: [
            { id: 'digital_page_count', title: 'Thống kê số trang tài liệu' },
            { id: 'digital_docs_by_collection', title: 'Danh mục tài liệu theo bộ sưu tập' },
            { id: 'digital_cataloging_stats', title: 'Thống kê biên mục tài liệu số' }
        ]
    },
    inventory: {
        title: 'BÁO CÁO KHO',
        defaultReport: 'inv_dkcb',
        defaultTitle: 'Sổ ĐKCB',
        reports: [
            { id: 'inv_dkcb', title: 'Sổ ĐKCB' },
            { id: 'inv_by_location', title: 'Báo cáo thống kê tài liệu theo kho' },
            { id: 'inv_detail_items', title: 'Danh mục chi tiết tài liệu' },
            { id: 'inv_by_language', title: 'Danh mục tài liệu theo nhóm ngôn ngữ' },
            { id: 'inv_by_itemtype', title: 'Danh mục tài liệu theo nhóm loại tài liệu' },
            { id: 'inv_by_status_group', title: 'Danh mục tài liệu theo nhóm trạng thái' },
            { id: 'inv_status_list', title: 'Danh mục trạng thái tài liệu' },
            { id: 'inv_withdrawn', title: 'Danh mục tài liệu thanh lý' },
            { id: 'inv_lost', title: 'Danh mục tài liệu mất' }
        ]
    },
    public_pages: {
        title: 'BÁO CÁO CÁC TRANG CÔNG KHAI',
        defaultReport: 'pub_article_views',
        defaultTitle: 'Thống kê lượt xem bài viết & tin tức',
        reports: [
            { id: 'pub_article_views', title: 'Thống kê lượt xem bài viết & tin tức' },
            { id: 'pub_page_traffic', title: 'Thống kê lưu lượng truy cập theo từng trang công khai' },
            { id: 'pub_top_searches', title: 'Thống kê từ khóa tìm kiếm phổ biến' },
            { id: 'pub_zero_hit_searches', title: 'Báo cáo tìm kiếm không có kết quả (Nhu cầu bổ sung)' },
            { id: 'pub_interactions', title: 'Báo cáo tương tác & dịch vụ trực tuyến công khai' },
            { id: 'pub_device_stats', title: 'Thống kê thiết bị & nền tảng truy cập' },
            { id: 'pub_hourly_traffic', title: 'Thống kê lưu lượng truy cập theo khung giờ & ngày trong tuần' },
            { id: 'pub_open_resources', title: 'Thống kê khám phá tài nguyên số công khai & bộ sưu tập mở' }
        ]
    },
    serials: {
        title: 'BÁO CÁO BÁO - TẠP CHÍ',
        defaultReport: 'serials_summary',
        defaultTitle: 'Thống kê tổng hợp báo - tạp chí',
        reports: [
            { id: 'serials_summary', title: 'Thống kê tổng hợp báo - tạp chí' },
            { id: 'serials_issues', title: 'Thống kê các số báo - tạp chí đã nhận' },
            { id: 'serials_by_vendor', title: 'Thống kê báo tạp chí theo nhà cung cấp' }
        ]
    }
};

var currentCategory = 'digital_access';
var currentReportId = 'opac_visits_ftu2';
var currentReportTitle = 'TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU';

document.addEventListener('DOMContentLoaded', function() {
    var urlParams = new URLSearchParams(window.location.search);
    var urlCat = urlParams.get('cat');
    var urlRep = urlParams.get('report_id');
    if (urlCat && reportCategories[urlCat]) {
        currentCategory = urlCat;
        currentReportId = reportCategories[urlCat].defaultReport;
        currentReportTitle = reportCategories[urlCat].defaultTitle;
        var items = document.querySelectorAll('.ftu-tree-item');
        items.forEach(function(i) { i.classList.remove('active'); });
        var targetLink = document.querySelector('.ftu-tree-link[onclick*="' + urlCat + '"]');
        if (targetLink) targetLink.closest('.ftu-tree-item').classList.add('active');
        document.getElementById('category_title').textContent = reportCategories[urlCat].title;
    }
    if (urlRep) {
        for (var c in reportCategories) {
            var found = reportCategories[c].reports.find(function(r) { return r.id === urlRep; });
            if (found) {
                currentCategory = c;
                currentReportId = found.id;
                currentReportTitle = found.title;
                var items = document.querySelectorAll('.ftu-tree-item');
                items.forEach(function(i) { i.classList.remove('active'); });
                var targetLink = document.querySelector('.ftu-tree-link[onclick*="' + c + '"]');
                if (targetLink) targetLink.closest('.ftu-tree-item').classList.add('active');
                document.getElementById('category_title').textContent = reportCategories[c].title;
                break;
            }
        }
    }
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
        document.getElementById('report_table_body').innerHTML = '<tr><td class="text-center py-4 text-muted">Danh mục <strong>' + catName + '</strong> đang được kết nối dữ liệu. Vui lòng chuyển sang <strong>Báo cáo lưu thông</strong> hoặc <strong>Báo cáo thống kê truy cập tài liệu số</strong>.</td></tr>';
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

    var baseReportsUrl = (window.location.pathname.substring(0, window.location.pathname.lastIndexOf('/') + 1) || '/cgi-bin/koha/reports/');
    var apiUrl = baseReportsUrl + 'digital-reports.pl?op=api_data'
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
            document.getElementById('report_table_body').innerHTML = '<tr><td colspan="10" class="text-center text-danger py-4">Lỗi nạp số liệu: ' + err.message + '</td></tr>';
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
        tbody.innerHTML = '<tr><td colspan="10" class="text-center py-4 text-muted">Không tìm thấy bản ghi nào phù hợp với bộ lọc trong khoảng thời gian đã chọn.</td></tr>';
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
            var statusBadge = r.status_text === 'Đang hoạt động' ? '<span class="badge-active">Đang hoạt động</span>' :
                              r.status_text === 'Đã hết phiên' ? '<span class="badge-expired">Hết hạn</span>' :
                              '<span class="badge-revoked">Thu hồi</span>';

            var pCode = r.patron_id || '';
            var pName = (r.patron_name || '') + (pCode ? ' <span class="text-muted small">(' + pCode + ')</span>' : '');

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + pCode + '</code></td>'
                + '<td><strong>' + pName + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role_label || '') + '</span></td>'
                + '<td>' + (r.document_title || '') + '</td>'
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
                + '<td><strong>' + (r.access_date || '') + '</strong></td>'
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
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
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
                + '<td><strong>' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.session_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end">' + (r.reader_count || 0) + '</td>'
                + '<td class="text-end text-success">' + (r.avg_duration || 0) + ' phút</td>'
                + '<td class="text-end text-muted">' + (r.pageviews || 0).toLocaleString('vi-VN') + '</td>'
                + '<td><small class="text-muted">' + (r.last_interaction || '') + '</small></td>'
                + '</tr>';
        });
    }

    // 1.5 TỔNG LƯỢT TRUY CẬP TRANG OPAC TỪ NGÀY ĐẾN NGÀY TẠI PHÂN HIỆU
    else if (currentReportId === 'opac_visits_ftu2') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Ngày ghi nhận</th>'
            + '<th class="text-end">Lượt đăng nhập OPAC</th>'
            + '<th class="text-end">Lượt tra cứu (Search)</th>'
            + '<th class="text-end">Xem chi tiết biểu ghi</th>'
            + '<th class="text-end">Lượt mượn/đọc số tại Phân hiệu</th>'
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
                + '<td><strong>' + (r.visit_date || '') + '</strong></td>'
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
            var pCode = r.patron_id || '';
            var pName = (r.patron_name || '') + (pCode ? ' <span class="text-muted small">(' + pCode + ')</span>' : '');

            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-secondary">' + r.stt + '</span></td>'
                + '<td><code>' + pCode + '</code></td>'
                + '<td><strong>' + pName + '</strong></td>'
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
                + '<td><strong>' + (r.name || '') + '</strong></td>'
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
    // 2. NHÓM BÁO CÁO TÀI LIỆU SỐ (3 LOẠI BÁO CÁO CHUẨN DSPACE & DRM)
    // =========================================================================

    // 2.1 Thống kê số trang tài liệu
    else if (currentReportId === 'digital_page_count') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Nhan đề tài liệu số</th>'
            + '<th>Tác giả</th>'
            + '<th>Bộ sưu tập số</th>'
            + '<th class="text-center">Định dạng</th>'
            + '<th class="text-end">Dung lượng (MB)</th>'
            + '<th class="text-end">Số trang</th>'
            + '<th>Chính sách bảo mật DRM</th>'
            + '<th class="text-center">Biểu ghi FTU - HCM LIB</th>'
            + '<th class="text-center">Ngày cập nhật</th>'
            + '</tr>';

        var sumPages = 0, sumSize = 0;
        rows.forEach(function(r) {
            sumPages += (r.page_count || 0);
            sumSize += parseFloat(r.size_mb || 0);

            var kohaLink = r.koha_biblionumber 
                ? '<a href="/cgi-bin/koha/catalogue/detail.pl?biblionumber=' + r.koha_biblionumber + '" target="_blank" class="badge bg-light text-primary border">#' + r.koha_biblionumber + '</a>'
                : '<span class="text-muted">Chưa gán</span>';

            var drmBadge = r.security_level_code === 'SEC-3' 
                ? '<span class="badge bg-danger text-white">Mức 3 - DRM Chống tải &amp; In ấn</span>'
                : '<span class="badge bg-primary text-white">Mức 2 - Watermark động FTU</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.collection_name || '') + '</span></td>'
                + '<td class="text-center"><span class="badge bg-secondary text-white">PDF</span></td>'
                + '<td class="text-end font-weight-bold">' + (r.size_mb || '0') + ' MB</td>'
                + '<td class="text-end text-success font-weight-bold" style="font-size: 14.5px;">' + (r.page_count || 0).toLocaleString('vi-VN') + ' trang</td>'
                + '<td>' + drmBadge + '</td>'
                + '<td class="text-center">' + kohaLink + '</td>'
                + '<td class="text-center text-muted"><small>' + (r.created_date || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="4" class="text-end"><strong>TỔNG CỘNG: ' + rows.length + ' TÀI LIỆU SỐ</strong></td>'
            + '<td></td>'
            + '<td class="text-end text-primary"><strong>' + sumSize.toFixed(2) + ' MB</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumPages.toLocaleString('vi-VN') + ' trang</strong></td>'
            + '<td colspan="3"></td>'
            + '</tr>';
    }

    // 2.2 Danh mục tài liệu theo bộ sưu tập
    else if (currentReportId === 'digital_docs_by_collection') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Bộ sưu tập</th>'
            + '<th>Nhan đề tài liệu số</th>'
            + '<th>Tác giả</th>'
            + '<th class="text-center">Năm XB</th>'
            + '<th class="text-end">Số trang</th>'
            + '<th class="text-end">Dung lượng</th>'
            + '<th>Tập tin số (Bitstream)</th>'
            + '<th class="text-center">Biểu ghi FTU - HCM LIB</th>'
            + '<th class="text-center">Ngày nhập</th>'
            + '</tr>';

        var sumPages = 0, sumSize = 0;
        rows.forEach(function(r) {
            sumPages += (r.page_count || 0);
            sumSize += parseFloat(r.size_mb || 0);

            var kohaLink = r.koha_biblionumber 
                ? '<a href="/cgi-bin/koha/catalogue/detail.pl?biblionumber=' + r.koha_biblionumber + '" target="_blank" class="badge bg-light text-primary border">#' + r.koha_biblionumber + '</a>'
                : '<span class="text-muted">Chưa gán</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><span class="badge bg-light text-dark border font-weight-bold">' + (r.collection_name || '') + '</span></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td class="text-center">' + (r.year || '') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.page_count || 0).toLocaleString('vi-VN') + ' trang</td>'
                + '<td class="text-end">' + (r.size_mb || '0') + ' MB</td>'
                + '<td><small class="text-muted font-monospace">' + (r.file_name || '') + '</small></td>'
                + '<td class="text-center">' + kohaLink + '</td>'
                + '<td class="text-center text-muted"><small>' + (r.modified_date || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="5" class="text-end"><strong>TỔNG CỘNG: ' + rows.length + ' TÀI LIỆU SỐ</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumPages.toLocaleString('vi-VN') + ' trang</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumSize.toFixed(2) + ' MB</strong></td>'
            + '<td colspan="3"></td>'
            + '</tr>';
    }

    // 2.3 Thống kê biên mục tài liệu số
    else if (currentReportId === 'digital_cataloging_stats') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Tên Bộ sưu tập số (DSpace 7)</th>'
            + '<th class="text-end">Số đầu mục (Titles)</th>'
            + '<th class="text-end">Số tập tin số (Bitstreams)</th>'
            + '<th class="text-end">Tổng số trang</th>'
            + '<th class="text-end">Tổng dung lượng</th>'
            + '<th class="text-center">Đã liên kết FTU - HCM LIB</th>'
            + '<th class="text-center">Hoàn thiện siêu dữ liệu DC</th>'
            + '<th class="text-center">Cập nhật mới nhất</th>'
            + '</tr>';

        var sumItems = 0, sumBits = 0, sumPages = 0, sumSize = 0;
        rows.forEach(function(r) {
            sumItems += (r.item_count || 0);
            sumBits += (r.bitstream_count || 0);
            sumPages += (r.page_count || 0);
            sumSize += parseFloat(r.total_size_mb || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary">' + (r.collection_name || '') + '</strong></td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.item_count || 0).toLocaleString('vi-VN') + ' đầu mục</td>'
                + '<td class="text-end font-weight-bold">' + (r.bitstream_count || 0).toLocaleString('vi-VN') + ' tệp</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.page_count || 0).toLocaleString('vi-VN') + ' trang</td>'
                + '<td class="text-end">' + (r.total_size_mb || '0') + ' MB</td>'
                + '<td class="text-center"><span class="badge bg-success text-white">' + (r.item_count || 0) + '/' + (r.item_count || 0) + ' (100%)</span></td>'
                + '<td class="text-center"><span class="badge bg-info text-white">100% Hoàn tất</span></td>'
                + '<td class="text-center text-muted"><small>' + (r.latest_update || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG: ' + rows.length + ' BỘ SƯU TẬP</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumItems.toLocaleString('vi-VN') + ' đầu mục</strong></td>'
            + '<td class="text-end"><strong>' + sumBits.toLocaleString('vi-VN') + ' tệp</strong></td>'
            + '<td class="text-end text-success"><strong>' + sumPages.toLocaleString('vi-VN') + ' trang</strong></td>'
            + '<td class="text-end text-primary"><strong>' + sumSize.toFixed(2) + ' MB</strong></td>'
            + '<td class="text-center text-success"><strong>100%</strong></td>'
            + '<td class="text-center text-info"><strong>100%</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // =========================================================================
    // 3. NHÓM BÁO CÁO LƯU THÔNG (CIRCULATION REPORTS - 10 LOẠI BÁO CÁO)
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
                + '<td><strong>' + (r.name || '') + '</strong></td>'
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
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td class="text-center">' + (r.year || '') + '</td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-center"><span class="badge bg-warning text-dark">' + (r.unused_days || 0) + ' ngày</span></td>'
                + '</tr>';
        });
    }

    // 2.4 Thống kê tổng số tài liệu
    else if (currentReportId === 'circ_total_docs') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Kho lưu trữ tài liệu Phân hiệu TP.HCM</th>'
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
                + '<td><strong>' + (r.name || '') + '</strong></td>'
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
            var pCode = r.cardnumber || r.patron_id || '';
            var pName = (r.patron_name || '') + (pCode ? ' <span class="text-muted small">(' + pCode + ')</span>' : '');

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + pCode + '</code></td>'
                + '<td><strong>' + pName + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.role || '') + '</span></td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong>' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.issue_date || '') + '</td>'
                + '<td><span class="text-danger font-weight-bold">' + (r.due_date || '') + '</span></td>'
                + '<td class="text-center"><span class="badge bg-danger">' + (r.overdue_days || 0) + ' ngày</span></td>'
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
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
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
                + '<td><strong>' + (r.author || '') + '</strong></td>'
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
                + '<td><strong>' + (r.date || '') + '</strong></td>'
                + '<td><strong>' + (r.location || '') + '</strong></td>'
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
            var pCode = r.patron_id || r.cardnumber || '';
            var pName = (r.patron_name || '') + (pCode ? ' <span class="text-muted small">(' + pCode + ')</span>' : '');

            tbody.innerHTML += '<tr>'
                + '<td class="text-center"><span class="badge bg-secondary">' + r.stt + '</span></td>'
                + '<td><code>' + pCode + '</code></td>'
                + '<td><strong>' + pName + '</strong></td>'
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
            + '<th>Bạn đọc mượn (Kèm mã thẻ)</th>'
            + '<th>Ngày mượn</th>'
            + '<th>Hạn trả</th>'
            + '<th>Ngày trả thực tế</th>'
            + '<th>Thủ thư thực hiện</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var stBadge = r.status === 'Đã trả đúng hạn' ? '<span class="badge bg-success">Đã trả</span>' :
                          r.status === 'Quá hạn' ? '<span class="badge bg-danger">Quá hạn</span>' :
                          '<span class="badge bg-primary">Đang mượn</span>';

            var pText = r.patron || '';
            var pCode = r.patron_id || '';
            if (!pText && r.patron_name) {
                pText = r.patron_name + (pCode ? ' <span class="text-muted small">(' + pCode + ')</span>' : '');
            } else if (pCode && !pText.includes(pCode)) {
                pText = pText + ' <span class="text-muted small">(' + pCode + ')</span>';
            }

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong>' + (r.title || '') + '</strong></td>'
                + '<td><strong>' + pText + '</strong></td>'
                + '<td>' + (r.issue_date || '') + '</td>'
                + '<td>' + (r.due_date || '') + '</td>'
                + '<td>' + (r.ret_date || '') + '</td>'
                + '<td><small class="text-muted">' + (r.staff || '') + '</small></td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '</tr>';
        });
    }

    // =========================================================================
    // 4. NHÓM BÁO CÁO KHO (INVENTORY REPORTS - 9 LOẠI BÁO CÁO CHUẨN THƯ VIỆN FTU)
    // =========================================================================

    // 4.1 Sổ ĐKCB
    else if (currentReportId === 'inv_dkcb') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Số ĐKCB (Mã vạch)</th>'
            + '<th class="text-center">Ngày vào sổ</th>'
            + '<th>Tác giả</th>'
            + '<th>Nhan đề sách</th>'
            + '<th>Nơi XB / Nhà xuất bản</th>'
            + '<th class="text-center">Năm XB</th>'
            + '<th>Ký hiệu xếp giá</th>'
            + '<th>Kho tài liệu</th>'
            + '<th class="text-end">Đơn giá (VNĐ)</th>'
            + '<th>Ghi chú</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td class="text-center">' + (r.date_accessioned || '') + '</td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.publisher || '') + '</td>'
                + '<td class="text-center">' + (r.pub_year || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.price_formatted || '0 đ') + '</td>'
                + '<td><small class="text-muted">' + (r.notes || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="9" class="text-end"><strong>TỔNG SỐ ' + rows.length + ' BẢN SÁCH VÀO SỔ ĐKCB:</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 4.2 Báo cáo thống kê tài liệu theo kho
    else if (currentReportId === 'inv_by_location') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã kho</th>'
            + '<th>Tên kho tài liệu (Phân hiệu TP.HCM)</th>'
            + '<th class="text-end">Số đầu sách (Nhan đề)</th>'
            + '<th class="text-end">Số bản sách (Item)</th>'
            + '<th class="text-end">Tổng giá trị (VNĐ)</th>'
            + '<th class="text-end">Đang cho mượn</th>'
            + '<th class="text-end">Sẵn sàng phục vụ</th>'
            + '<th class="text-end">Tỷ lệ cơ cấu</th>'
            + '</tr>';

        var sumTitles = 0, sumItems = 0, sumLoaned = 0, sumAvail = 0;
        rows.forEach(function(r) {
            sumTitles += (r.titles || 0);
            sumItems += (r.items || 0);
            sumLoaned += (r.loaned || 0);
            sumAvail += (r.available || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.titles || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.items || 0).toLocaleString('vi-VN') + ' bản</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.total_val_formatted || '0 đ') + '</td>'
                + '<td class="text-end text-warning font-weight-bold">' + (r.loaned || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.available || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end font-weight-bold">' + (r.ratio || '0%') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG TOÀN HỆ THỐNG KHO:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumTitles.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumItems.toLocaleString('vi-VN') + ' bản</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td class="text-end text-warning font-weight-bold"><strong>' + sumLoaned.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-info font-weight-bold">' + sumAvail.toLocaleString('vi-VN') + '</td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 4.3 Danh mục chi tiết tài liệu
    else if (currentReportId === 'inv_detail_items') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Số ĐKCB (Barcode)</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Tác giả</th>'
            + '<th>Ký hiệu xếp giá</th>'
            + '<th>Loại tài liệu</th>'
            + '<th>Kho quản lý</th>'
            + '<th class="text-center">Năm XB</th>'
            + '<th class="text-end">Đơn giá (VNĐ)</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var stBadge = r.status_text === 'Sẵn sàng phục vụ' ? '<span class="badge bg-success">Sẵn sàng phục vụ</span>' :
                          r.status_text === 'Đang cho mượn' ? '<span class="badge bg-warning text-dark">Đang cho mượn</span>' :
                          r.status_text === 'Đã thanh lý' ? '<span class="badge bg-secondary">Đã thanh lý</span>' :
                          '<span class="badge bg-danger">' + r.status_text + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td><span class="badge bg-info text-white">' + (r.itemtype_name || 'Sách in') + '</span></td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-center">' + (r.pub_year || '') + '</td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.price_formatted || '0 đ') + '</td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="8" class="text-end"><strong>TỔNG SỐ ' + rows.length + ' TÀI LIỆU CHI TIẾT:</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 4.4 Danh mục tài liệu theo nhóm ngôn ngữ
    else if (currentReportId === 'inv_by_language') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã ngôn ngữ</th>'
            + '<th>Nhóm ngôn ngữ</th>'
            + '<th class="text-end">Số đầu sách (Nhan đề)</th>'
            + '<th class="text-end">Số bản sách (Item)</th>'
            + '<th class="text-end">Tổng giá trị (VNĐ)</th>'
            + '<th class="text-end">Tỷ lệ cơ cấu (%)</th>'
            + '</tr>';

        var sumT = 0, sumI = 0;
        rows.forEach(function(r) {
            sumT += (r.titles || 0);
            sumI += (r.items || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.titles || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.items || 0).toLocaleString('vi-VN') + ' bản</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.val_formatted || '0 đ') + '</td>'
                + '<td class="text-end font-weight-bold">' + (r.ratio || '0%') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumT.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumI.toLocaleString('vi-VN') + ' bản</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 4.5 Danh mục tài liệu theo nhóm loại tài liệu
    else if (currentReportId === 'inv_by_itemtype') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã loại hình</th>'
            + '<th>Tên loại tài liệu</th>'
            + '<th class="text-end">Số đầu sách (Nhan đề)</th>'
            + '<th class="text-end">Số bản sách (Item)</th>'
            + '<th class="text-end">Tổng giá trị (VNĐ)</th>'
            + '<th class="text-end">Tỷ lệ cơ cấu (%)</th>'
            + '</tr>';

        var sumT = 0, sumI = 0;
        rows.forEach(function(r) {
            sumT += (r.titles || 0);
            sumI += (r.items || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.titles || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.items || 0).toLocaleString('vi-VN') + ' bản</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.total_val_formatted || '0 đ') + '</td>'
                + '<td class="text-end font-weight-bold">' + (r.ratio || '0%') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG CÁC LOẠI HÌNH:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumT.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumI.toLocaleString('vi-VN') + ' bản</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 4.6 Danh mục tài liệu theo nhóm trạng thái
    else if (currentReportId === 'inv_by_status_group') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã nhóm</th>'
            + '<th>Nhóm trạng thái tài liệu</th>'
            + '<th>Mô tả phạm vi phục vụ</th>'
            + '<th class="text-end">Số đầu sách</th>'
            + '<th class="text-end">Số bản sách</th>'
            + '<th class="text-end">Tỷ lệ cơ cấu (%)</th>'
            + '</tr>';

        var sumT = 0, sumI = 0;
        rows.forEach(function(r) {
            sumT += (r.titles || 0);
            sumI += (r.items || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.code || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.name || '') + '</strong></td>'
                + '<td><small class="text-muted">' + (r.desc || '') + '</small></td>'
                + '<td class="text-end font-weight-bold">' + (r.titles || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold" style="font-size: 14.5px;">' + (r.items || 0).toLocaleString('vi-VN') + ' bản</td>'
                + '<td class="text-end font-weight-bold">' + (r.ratio || '0%') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="4" class="text-end"><strong>TỔNG CỘNG:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumT.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumI.toLocaleString('vi-VN') + ' bản</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 4.7 Danh mục trạng thái tài liệu
    else if (currentReportId === 'inv_status_list') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Mã vạch (Barcode)</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Ký hiệu xếp giá</th>'
            + '<th>Kho hiện tại</th>'
            + '<th class="text-center">Trạng thái chi tiết</th>'
            + '<th class="text-center">Ngày cập nhật</th>'
            + '<th>Ghi chú nghiệp vụ</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var badgeCls = r.status_badge || 'badge-secondary';
            var stBadge = '<span class="badge ' + (badgeCls === 'badge-success' ? 'bg-success' : badgeCls === 'badge-warning' ? 'bg-warning text-dark' : 'bg-secondary') + '">' + r.status_label + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '<td class="text-center text-muted"><small>' + (r.last_update || '') + '</small></td>'
                + '<td><small class="text-muted">' + (r.note || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="8" class="text-end"><strong>TỔNG SỐ ' + rows.length + ' BẢN GHI TRẠNG THÁI TÀI LIỆU</strong></td>'
            + '</tr>';
    }

    // 4.8 Danh mục tài liệu thanh lý
    else if (currentReportId === 'inv_withdrawn') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Số ĐKCB (Barcode)</th>'
            + '<th>Nhan đề sách thanh lý</th>'
            + '<th>Tác giả</th>'
            + '<th>Ký hiệu xếp giá</th>'
            + '<th>Kho xuất thanh lý</th>'
            + '<th class="text-end">Đơn giá (VNĐ)</th>'
            + '<th class="text-center">Ngày thanh lý</th>'
            + '<th>Lý do xét duyệt</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong class="text-danger">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-end font-weight-bold text-muted">' + (r.price_formatted || '0 đ') + '</td>'
                + '<td class="text-center font-weight-bold text-danger">' + (r.withdrawn_date || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.reason || '') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="6" class="text-end"><strong>TỔNG CỘNG ' + rows.length + ' BẢN SÁCH ĐÃ THANH LÝ:</strong></td>'
            + '<td class="text-end text-danger font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td colspan="2"></td>'
            + '</tr>';
    }

    // 4.9 Danh mục tài liệu mất
    else if (currentReportId === 'inv_lost') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Số ĐKCB (Barcode)</th>'
            + '<th>Nhan đề tài liệu</th>'
            + '<th>Tác giả</th>'
            + '<th>Ký hiệu xếp giá</th>'
            + '<th>Kho quản lý</th>'
            + '<th class="text-end">Đơn giá đền bù (VNĐ)</th>'
            + '<th class="text-center">Ngày báo mất</th>'
            + '<th>Lý do ghi nhận</th>'
            + '<th class="text-center">Tình trạng bồi hoàn</th>'
            + '</tr>';

        rows.forEach(function(r) {
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><code>' + (r.barcode || '') + '</code></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.callnumber || '') + '</span></td>'
                + '<td>' + (r.location || '') + '</td>'
                + '<td class="text-end font-weight-bold text-danger">' + (r.price_formatted || '0 đ') + '</td>'
                + '<td class="text-center text-muted">' + (r.lost_date || '') + '</td>'
                + '<td>' + (r.note || '') + '</td>'
                + '<td class="text-center"><span class="badge bg-info text-white">' + (r.resolution || 'Chờ xử lý') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="6" class="text-end"><strong>TỔNG CỘNG ' + rows.length + ' TÀI LIỆU BÁO MẤT:</strong></td>'
            + '<td class="text-end text-danger font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td colspan="3"></td>'
            + '</tr>';
    }

    // =========================================================================
    // 5. NHÓM BÁO CÁO CÁC TRANG CÔNG KHAI (PUBLIC OPAC & PORTAL REPORTS)
    // =========================================================================

    // 5.1 Thống kê lượt xem bài viết & tin tức
    else if (currentReportId === 'pub_article_views') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th style="width: 80px;" class="text-center">Mã tin</th>'
            + '<th>Tiêu đề bài viết / Thông báo</th>'
            + '<th>Chuyên mục</th>'
            + '<th>Vị trí hiển thị</th>'
            + '<th class="text-center">Ngày đăng</th>'
            + '<th class="text-end">Lượt xem (Views)</th>'
            + '<th class="text-end">Bạn đọc duy nhất</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        var totalViews = 0;
        var totalUnique = 0;

        rows.forEach(function(r) {
            totalViews += (r.views || 0);
            totalUnique += (r.unique_readers || 0);
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td class="text-center"><span class="badge bg-light text-dark border">#' + r.id + '</span></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td><span class="badge bg-info text-white">' + (r.cat_name || '') + '</span></td>'
                + '<td><small class="text-muted">' + (r.location || '') + '</small></td>'
                + '<td class="text-center text-muted"><small>' + (r.pub_date || '') + '</small></td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.views || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary">' + (r.unique_readers || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-center"><span class="badge bg-success">' + (r.status || 'Đang hiển thị') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="6" class="text-end"><strong>TỔNG CỘNG ' + rows.length + ' BÀI VIẾT / THÔNG BÁO CÔNG KHAI:</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + totalViews.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + totalUnique.toLocaleString('vi-VN') + ' bạn đọc</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 5.2 Thống kê lưu lượng truy cập theo từng trang công khai
    else if (currentReportId === 'pub_page_traffic') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Tên trang công khai</th>'
            + '<th>Đường dẫn (URL / Tuyến đường)</th>'
            + '<th class="text-end">Lượt xem trang (Pageviews)</th>'
            + '<th class="text-end">Số phiên truy cập</th>'
            + '<th class="text-center">Thời gian dừng TB</th>'
            + '<th class="text-center">Tỷ lệ thoát (Bounce)</th>'
            + '<th class="text-end">Tỷ trọng lưu lượng</th>'
            + '</tr>';

        var sumPv = 0;
        var sumSess = 0;

        rows.forEach(function(r) {
            sumPv += (r.pageviews || 0);
            sumSess += (r.sessions || 0);
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary">' + (r.name || '') + '</strong></td>'
                + '<td><code>' + (r.route || '') + '</code></td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.pageviews || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.sessions || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-center">' + (r.avg_time || '') + '</td>'
                + '<td class="text-center text-muted">' + (r.bounce || '') + '</td>'
                + '<td class="text-end"><span class="badge bg-light text-dark border">' + (r.ratio || '') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG CỘNG LƯU LƯỢNG TRUY CẬP:</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + sumPv.toLocaleString('vi-VN') + ' lượt xem</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumSess.toLocaleString('vi-VN') + ' phiên</strong></td>'
            + '<td colspan="2"></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // 5.3 Thống kê từ khóa tìm kiếm phổ biến
    else if (currentReportId === 'pub_top_searches') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 50px;" class="text-center">Top</th>'
            + '<th>Từ khóa tìm kiếm phổ biến</th>'
            + '<th>Lĩnh vực / Chuyên ngành FTU</th>'
            + '<th class="text-end">Số lượt tìm kiếm</th>'
            + '<th class="text-center">Kết quả TB / lượt</th>'
            + '<th class="text-center">Tỷ lệ tương tác (CTR)</th>'
            + '<th class="text-center">Xu hướng quan tâm</th>'
            + '</tr>';

        var sumSearches = 0;

        rows.forEach(function(r) {
            sumSearches += (r.count || 0);
            var trendBadge = r.trend.indexOf('Tăng') !== -1
                ? '<span class="badge bg-success">' + r.trend + '</span>'
                : r.trend.indexOf('Mới') !== -1
                ? '<span class="badge bg-warning text-dark">' + r.trend + '</span>'
                : '<span class="badge bg-secondary">' + r.trend + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center font-weight-bold"><span class="badge bg-primary rounded-pill">' + r.stt + '</span></td>'
                + '<td><strong class="text-dark"><i class="fa fa-search text-muted me-1"></i> "' + (r.query || '') + '"</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.domain || '') + '</span></td>'
                + '<td class="text-end font-weight-bold text-primary">' + (r.count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-center text-muted">' + (r.avg_results || 0) + ' tài liệu</td>'
                + '<td class="text-center text-success font-weight-bold">' + (r.ctr || '') + '</td>'
                + '<td class="text-center">' + trendBadge + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG LƯỢT TÌM KIẾM TRONG TOP:</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumSearches.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td colspan="3"></td>'
            + '</tr>';
    }

    // 5.4 Báo cáo tìm kiếm không có kết quả (Nhu cầu bổ sung)
    else if (currentReportId === 'pub_zero_hit_searches') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Từ khóa tìm kiếm không có kết quả</th>'
            + '<th>Nhóm bạn đọc quan tâm</th>'
            + '<th class="text-end">Lượt tra cứu thất bại</th>'
            + '<th class="text-center">Lần tra cứu gần nhất</th>'
            + '<th>Hành động đề xuất (Bổ sung tài liệu)</th>'
            + '<th class="text-center">Tình trạng xử lý</th>'
            + '</tr>';

        var sumZeroHits = 0;

        rows.forEach(function(r) {
            sumZeroHits += (r.count || 0);
            var stBadge = r.status.indexOf('Đã') !== -1
                ? '<span class="badge bg-success">' + r.status + '</span>'
                : '<span class="badge bg-warning text-dark">' + r.status + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-danger"><i class="fa fa-exclamation-circle text-danger me-1"></i> "' + (r.query || '') + '"</strong></td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.audience || '') + '</span></td>'
                + '<td class="text-end font-weight-bold text-danger">' + (r.count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-center text-muted"><small>' + (r.last_time || '') + '</small></td>'
                + '<td><strong class="text-primary">' + (r.rec_action || '') + '</strong></td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="3" class="text-end"><strong>TỔNG SỐ LƯỢT TÌM KIẾM THẤT BẠI CẦN BỔ SUNG:</strong></td>'
            + '<td class="text-end text-danger font-weight-bold"><strong>' + sumZeroHits.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td colspan="3"></td>'
            + '</tr>';
    }

    // 5.5 Báo cáo tương tác & dịch vụ trực tuyến công khai
    else if (currentReportId === 'pub_interactions') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Loại hình tương tác & Dịch vụ trực tuyến</th>'
            + '<th class="text-end">Số yêu cầu tiếp nhận</th>'
            + '<th class="text-end">Đã xử lý & Phê duyệt</th>'
            + '<th class="text-end">Đang xử lý / Chờ</th>'
            + '<th class="text-center">Thời gian phản hồi TB</th>'
            + '<th class="text-center">Mức độ hài lòng</th>'
            + '</tr>';

        var sumRec = 0;
        var sumApp = 0;
        var sumPend = 0;

        rows.forEach(function(r) {
            sumRec += (r.received || 0);
            sumApp += (r.approved || 0);
            sumPend += (r.pending || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary">' + (r.service || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.received || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.approved || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-danger font-weight-bold">' + (r.pending || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-center text-muted">' + (r.avg_res || '') + '</td>'
                + '<td class="text-center"><span class="badge bg-success">' + (r.satisfaction || '') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG TOÀN BỘ CÁC DỊCH VỤ TRỰC TUYẾN:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumRec.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + sumApp.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-danger font-weight-bold"><strong>' + sumPend.toLocaleString('vi-VN') + '</strong></td>'
            + '<td colspan="2"></td>'
            + '</tr>';
    }

    // 5.6 Thống kê thiết bị & nền tảng truy cập
    else if (currentReportId === 'pub_device_stats') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Loại thiết bị truy cập</th>'
            + '<th>Hệ điều hành phổ biến</th>'
            + '<th>Trình duyệt Web chủ yếu</th>'
            + '<th class="text-end">Lượt truy cập (Visits)</th>'
            + '<th class="text-end">Tỷ lệ cơ cấu (%)</th>'
            + '<th class="text-center">Thời gian lưu lại TB</th>'
            + '</tr>';

        var sumVis = 0;

        rows.forEach(function(r) {
            sumVis += (r.visits || 0);
            var icon = r.type.indexOf('Máy tính') !== -1 ? 'fa-laptop' : r.type.indexOf('Điện thoại') !== -1 ? 'fa-mobile-alt' : 'fa-tablet-alt';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary"><i class="fa ' + icon + ' me-1"></i> ' + (r.type || '') + '</strong></td>'
                + '<td>' + (r.os || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.browser || '') + '</span></td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.visits || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end"><span class="badge bg-primary">' + (r.ratio || '') + '</span></td>'
                + '<td class="text-center text-muted">' + (r.avg_time || '') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="4" class="text-end"><strong>TỔNG LƯỢT TRUY CẬP THEO THIẾT BỊ:</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + sumVis.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '<td></td>'
            + '</tr>';
    }

    // 5.7 Thống kê lưu lượng truy cập theo khung giờ & ngày trong tuần
    else if (currentReportId === 'pub_hourly_traffic') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Khung giờ trong ngày</th>'
            + '<th class="text-center">Mức độ tải hệ thống</th>'
            + '<th class="text-end">Lượt xem trang / Giờ</th>'
            + '<th class="text-end">Bạn đọc trực tuyến TB</th>'
            + '<th>Hành vi tra cứu chủ yếu</th>'
            + '<th>Đề xuất phân công thủ thư trực</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var levelBadge = r.level.indexOf('Cao điểm') !== -1
                ? '<span class="badge bg-danger">' + r.level + '</span>'
                : r.level.indexOf('Bình thường') !== -1
                ? '<span class="badge bg-info text-white">' + r.level + '</span>'
                : '<span class="badge bg-secondary">' + r.level + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong><i class="fa fa-clock-o text-muted me-1"></i> ' + (r.period || '') + '</strong></td>'
                + '<td class="text-center">' + levelBadge + '</td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.pv_hour || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.online_users || 0).toLocaleString('vi-VN') + '</td>'
                + '<td>' + (r.top_action || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.staff_rec || '') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="7" class="text-end"><strong>BÁO CÁO PHÂN BỔ TẢI 24/7 PHỤC VỤ ĐIỀU PHỐI NHÂN LỰC THƯ VIỆN</strong></td>'
            + '</tr>';
    }

    // 5.8 Thống kê khám phá tài nguyên số công khai & bộ sưu tập mở
    else if (currentReportId === 'pub_open_resources') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Bộ sưu tập số & Khám phá mở FTU</th>'
            + '<th class="text-end">Số tài liệu</th>'
            + '<th class="text-end">Lượt tra cứu trên OPAC</th>'
            + '<th class="text-end">Lượt đọc toàn văn trực tuyến</th>'
            + '<th class="text-end">Lượt tải về / Xuất trích dẫn</th>'
            + '<th class="text-end">Tỷ lệ quan tâm (%)</th>'
            + '</tr>';

        var sumItems = 0;
        var sumOpac = 0;
        var sumFulltext = 0;
        var sumDl = 0;

        rows.forEach(function(r) {
            sumItems += (r.items || 0);
            sumOpac += (r.opac_views || 0);
            sumFulltext += (r.fulltext_reads || 0);
            sumDl += (r.downloads || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary"><i class="fa fa-folder-open text-warning me-1"></i> ' + (r.name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold">' + (r.items || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary font-weight-bold">' + (r.opac_views || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-success font-weight-bold">' + (r.fulltext_reads || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-info font-weight-bold">' + (r.downloads || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end"><span class="badge bg-light text-dark border">' + (r.ratio || '') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG TOÀN BỘ BỘ SƯU TẬP:</strong></td>'
            + '<td class="text-end font-weight-bold"><strong>' + sumItems.toLocaleString('vi-VN') + ' tài liệu</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumOpac.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + sumFulltext.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td class="text-end text-info font-weight-bold"><strong>' + sumDl.toLocaleString('vi-VN') + ' lượt</strong></td>'
            + '<td class="text-end"><strong>100%</strong></td>'
            + '</tr>';
    }

    // =========================================================================
    // 6. NHÓM BÁO CÁO BÁO - TẠP CHÍ (SERIALS REPORTS)
    // =========================================================================

    // 6.1 Thống kê tổng hợp báo - tạp chí
    else if (currentReportId === 'serials_summary') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th style="width: 80px;" class="text-center">Mã đặt</th>'
            + '<th>Nhan đề báo - tạp chí</th>'
            + '<th>Tác giả / Cơ quan chủ quản</th>'
            + '<th>Nhà cung cấp / Đại lý</th>'
            + '<th class="text-center">Tần suất</th>'
            + '<th class="text-center">Kỳ đã nhận</th>'
            + '<th class="text-center">Thời gian đặt</th>'
            + '<th class="text-center">Trạng thái</th>'
            + '</tr>';

        var totalRec = 0;
        rows.forEach(function(r) {
            totalRec += (r.received_count || 0);
            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td class="text-center"><span class="badge bg-light text-dark border">#' + (r.subscriptionid || '') + '</span></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td>' + (r.author || '') + '</td>'
                + '<td><span class="badge bg-light text-dark border">' + (r.vendor_name || '') + '</span></td>'
                + '<td class="text-center">' + (r.periodicity || 1) + ' kỳ/năm</td>'
                + '<td class="text-center font-weight-bold text-success">' + (r.received_count || 0) + '</td>'
                + '<td class="text-center text-muted"><small>' + (r.start_date || '') + ' - ' + (r.end_date || '') + '</small></td>'
                + '<td class="text-center"><span class="badge bg-success">' + (r.status_label || 'Đang đặt mua') + '</span></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="6" class="text-end"><strong>TỔNG SỐ ' + rows.length + ' ĐẦU BÁO - TẠP CHÍ ĐÃ THIẾT LẬP:</strong></td>'
            + '<td class="text-center text-success font-weight-bold"><strong>' + totalRec + ' kỳ</strong></td>'
            + '<td colspan="2"></td>'
            + '</tr>';
    }

    // 6.2 Thống kê các số báo - tạp chí đã nhận
    else if (currentReportId === 'serials_issues') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th style="width: 80px;" class="text-center">Mã số kỳ</th>'
            + '<th>Nhan đề ấn phẩm định kỳ</th>'
            + '<th>Ký hiệu số / kỳ phát hành</th>'
            + '<th class="text-center">Ngày dự kiến</th>'
            + '<th class="text-center">Ngày phát hành</th>'
            + '<th class="text-center">Trạng thái tiếp nhận</th>'
            + '<th>Ghi chú</th>'
            + '</tr>';

        rows.forEach(function(r) {
            var stBadge = r.status_label === 'Đã nhận' ? '<span class="badge bg-success">Đã nhận</span>' :
                          r.status_label === 'Trễ kỳ' ? '<span class="badge bg-warning">Trễ kỳ</span>' :
                          '<span class="badge bg-secondary">' + (r.status_label || 'Chờ nhận') + '</span>';

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td class="text-center"><span class="badge bg-light text-dark border">#' + (r.serialid || '') + '</span></td>'
                + '<td><strong class="text-primary">' + (r.title || '') + '</strong></td>'
                + '<td><span class="badge bg-info text-white">' + (r.serialseq || '') + '</span></td>'
                + '<td class="text-center text-muted"><small>' + (r.planned_date || '') + '</small></td>'
                + '<td class="text-center text-muted"><small>' + (r.published_date || '') + '</small></td>'
                + '<td class="text-center">' + stBadge + '</td>'
                + '<td><small class="text-muted">' + (r.notes || '') + '</small></td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="8" class="text-end"><strong>TỔNG SỐ ' + rows.length + ' KỲ PHÁT HÀNH ĐÃ ĐƯỢC TIẾP NHẬN</strong></td>'
            + '</tr>';
    }

    // 6.3 Thống kê báo tạp chí theo nhà cung cấp
    else if (currentReportId === 'serials_by_vendor') {
        thead.innerHTML = '<tr>'
            + '<th style="width: 45px;" class="text-center">STT</th>'
            + '<th>Tên nhà cung cấp / Đối tác phát hành</th>'
            + '<th class="text-end">Số gói đặt mua</th>'
            + '<th class="text-end">Số đầu ấn phẩm (Titles)</th>'
            + '<th class="text-end">Tổng kinh phí (VNĐ)</th>'
            + '<th class="text-end">Số kỳ phát hành đã nhận</th>'
            + '</tr>';

        var sumSubs = 0;
        var sumTitles = 0;
        var sumIssues = 0;

        rows.forEach(function(r) {
            sumSubs += (r.sub_count || 0);
            sumTitles += (r.title_count || 0);
            sumIssues += (r.issues_received || 0);

            tbody.innerHTML += '<tr>'
                + '<td class="text-center">' + r.stt + '</td>'
                + '<td><strong class="text-primary"><i class="fa fa-building-o me-1"></i> ' + (r.vendor_name || '') + '</strong></td>'
                + '<td class="text-end font-weight-bold text-info">' + (r.sub_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end text-primary">' + (r.title_count || 0).toLocaleString('vi-VN') + '</td>'
                + '<td class="text-end font-weight-bold text-success">' + (r.total_cost_formatted || '0 đ') + '</td>'
                + '<td class="text-end text-muted">' + (r.issues_received || 0).toLocaleString('vi-VN') + '</td>'
                + '</tr>';
        });

        tfoot.innerHTML = '<tr>'
            + '<td colspan="2" class="text-end"><strong>TỔNG CỘNG THEO TẤT CẢ ĐỐI TÁC:</strong></td>'
            + '<td class="text-end text-info font-weight-bold"><strong>' + sumSubs.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-primary font-weight-bold"><strong>' + sumTitles.toLocaleString('vi-VN') + '</strong></td>'
            + '<td class="text-end text-success font-weight-bold"><strong>' + (summary.total_value_formatted || '0 đ') + '</strong></td>'
            + '<td class="text-end text-muted font-weight-bold"><strong>' + sumIssues.toLocaleString('vi-VN') + '</strong></td>'
            + '</tr>';
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

    var baseReportsUrl = (window.location.pathname.substring(0, window.location.pathname.lastIndexOf('/') + 1) || '/cgi-bin/koha/reports/');
    var exportUrl = baseReportsUrl + 'digital-reports.pl?op=export_csv'
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
