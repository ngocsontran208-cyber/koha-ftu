[% USE raw %]
[% USE Koha %]

[%# ═══════════════════════════════════════════════════════════════════════════
    FTU LIBRARY BRAND CONFIGURATION (THÔNG TIN THƯƠNG HIỆU & HỆ THỐNG FTULIB)
    Cơ sở: Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh
    Được cập nhật tự động từ trang: Quản trị > Công cụ > Cấu hình Chân trang (portal-news.pl?section=footer)
    ═══════════════════════════════════════════════════════════════════════════ %]

[% SET FTU_BRAND = {
    # ── 1. TÊN ĐƠN VỊ & PHÂN HIỆU ──────────────────────────────────────────
    university_name        => "Trường Đại học Ngoại thương",
    university_name_en     => "Foreign Trade University",
    university_short       => "FTU",
    campus_current         => "Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    campus_current_short   => "Phân hiệu tại TP. Hồ Chí Minh",
    campus_current_en      => "Foreign Trade University - Ho Chi Minh City Branch",

    # ── 2. TÊN THƯ VIỆN & KHẨU HIỆU ─────────────────────────────────────────
    library_name           => "Thư viện Phân hiệu Trường Đại học Ngoại thương",
    library_name_short     => "Thư viện FTU",
    library_name_full      => "Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    library_name_en        => "Foreign Trade University Library",
    library_sub_title      => "Foreign Trade University Library - Ho Chi Minh City Branch",
    library_slogan         => "Không gian học tập & nghiên cứu hiện đại, kết nối cộng đồng giảng viên và sinh viên với kho tri thức toàn diện",
    library_description    => "Trung tâm Thông tin – Tri thức hiện đại, kết nối cộng đồng giảng viên và sinh viên FTU với nguồn học liệu số phong phú, sách in chuyên ngành chất lượng cao và dịch vụ hỗ trợ nghiên cứu chuẩn quốc tế.",
    library_description_en => "A modern center for information and knowledge, connecting FTU faculty, researchers, and students with high-impact digital databases, comprehensive print collections, and world-class academic support.",

    # ── 3. LOGO & BIỂU TRƯNG NHẬN DIỆN ──────────────────────────────────────
    logo_url               => "/opac-tmpl/bootstrap/images/ftu-logo.png",
    logo_alt               => "FTU Logo - Thư viện Phân hiệu Trường Đại học Ngoại thương",
    favicon_svg            => "/opac-tmpl/bootstrap/images/favicon.svg?v=ftu",
    favicon_ico            => "/opac-tmpl/bootstrap/images/favicon.ico?v=ftu",

    # ── 4. EMAIL & HOTLINE HỖ TRỢ BẠN ĐỌC ──────────────────────────────────
    email_contact          => "tv.hcmc@ftu.edu.vn",
    email_cs2              => "tv.hcmc@ftu.edu.vn",
    hotline_hanoi          => "(024) 3835 6800",
    hotline_hanoi_ext      => "Máy lẻ: 532 / 535",
    hotline_hcmc           => "(028) 3512 7254",
    hotline_hcmc_sub       => "(028) 3512 7258",
    hotline_quangninh      => "(0203) 3850 411",

    # ── 5. GIỜ PHỤC VỤ / LỊCH MỞ CỬA ────────────────────────────────────────
    hours_status           => "Đang mở cửa",
    hours_status_en        => "Open Now",
    hours_summary          => "Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 16:00",
    hours_summary_en       => "Mon – Fri: 07:30 – 19:30 | Sat: 08:00 – 16:00",
    hours_weekdays         => "07:30 – 19:30 (Thứ 2 – Thứ 6)",
    hours_saturday         => "08:00 – 16:00 (Thứ 7)",
    hours_sunday           => "Nghỉ (Chủ nhật & Ngày Lễ)",

    # ── 6. ĐỊA CHỈ & LIÊN HỆ PHÂN HIỆU TP.HCM ───────────────────────────────
    campus_hcm_title       => "Phân hiệu Trường ĐH Ngoại thương tại TP. Hồ Chí Minh",
    campus_hcm_title_en    => "Foreign Trade University - Ho Chi Minh City Branch",
    campus_hcm_addr        => "Số 15, Đường D5, Phường 25, Quận Bình Thạnh, TP. Hồ Chí Minh",
    campus_hcm_addr_en     => "No. 15, D5 St., Ward 25, Binh Thanh District, Ho Chi Minh City",
    campus_hcm_phone       => "(028) 3512 7254 - 3512 7258",

    campus_hn_title        => "Trụ sở chính Hà Nội",
    campus_hn_title_en     => "FTU Main Campus - Hanoi",
    campus_hn_addr         => "91 Phố Chùa Láng, Phường Láng Thượng, Quận Đống Đa, TP. Hà Nội",
    campus_hn_addr_en      => "91 Chua Lang St., Lang Thuong Ward, Dong Da Dist., Hanoi",
    campus_hn_phone        => "(024) 3835 6800 (Ext: 532, 535)",

    campus_qn_title        => "Cơ sở Quảng Ninh",
    campus_qn_title_en     => "FTU Quang Ninh Campus",
    campus_qn_addr         => "Số 260 Bạch Đằng, Phường Nam Khê, TP. Uông Bí, Tỉnh Quảng Ninh",
    campus_qn_addr_en      => "260 Bach Dang, Nam Khe Ward, Uong Bi City, Quang Ninh",
    campus_qn_phone        => "(0203) 3850 411",

    # ── 7. ĐƯỜNG DẪN CỔNG THÔNG TIN & HỆ THỐNG LIÊN THÔNG ───────────────────
    link_portal            => "https://hcmc.ftu.edu.vn",
    link_portal_cs2        => "https://hcmc.ftu.edu.vn/",
    link_dspace            => "/elib",
    link_sso               => "/sso",
    link_drm               => "/drm",
    link_opac              => "",
    link_staff             => "",
    link_facebook          => "https://www.facebook.com/ftu2.hcmc",
    link_facebook_cs2      => "https://www.facebook.com/ftu2.hcmc",
    link_youtube           => "https://www.youtube.com/@FTUChannel",
    link_databases         => "/cgi-bin/ftu/opac-databases.pl",
    link_search            => "/cgi-bin/ftu/opac-search.pl",
    link_passwd            => "/cgi-bin/ftu/opac-passwd.pl",

    # ── 7b. CỘT 2: KHÁM PHÁ TÀI NGUYÊN (5 LIÊN KẾT) ────────────────────────
    footer_res_title1      => "Bộ sưu tập tài liệu số",
    footer_res_title1_en   => "Digital Collections",
    footer_res_link1       => "/cgi-bin/koha/opac-collections.pl",

    footer_res_title2      => "Tìm kiếm theo Tác giả",
    footer_res_title2_en   => "Search by Author",
    footer_res_link2       => "/cgi-bin/koha/opac-search.pl?idx=au",

    footer_res_title3      => "Tìm kiếm theo Chủ đề",
    footer_res_title3_en   => "Search by Subject",
    footer_res_link3       => "/cgi-bin/koha/opac-search.pl?idx=su",

    footer_res_title4      => "Giáo trình & Học phần",
    footer_res_title4_en   => "Course Reserves",
    footer_res_link4       => "/cgi-bin/koha/opac-course-reserves.pl",

    footer_res_title5      => "Kho tài liệu số DSpace",
    footer_res_title5_en   => "DSpace Digital Repository",
    footer_res_link5       => "/elib",

    # ── 7c. CỘT 3: HỖ TRỢ & DỊCH VỤ (4 LIÊN KẾT) ──────────────────────────
    footer_srv_title1      => "Tài khoản & Gia hạn sách",
    footer_srv_title1_en   => "Account & Renewals",
    footer_srv_link1       => "/cgi-bin/koha/opac-user.pl",

    footer_srv_title2      => "Quy định bản quyền học thuật",
    footer_srv_title2_en   => "Academic Copyright Policy",
    footer_srv_link2       => "/elib/info/end-user-agreement",

    footer_srv_title3      => "Thông báo & Lịch phục vụ",
    footer_srv_title3_en   => "News & Service Notices",
    footer_srv_link3       => "/cgi-bin/koha/opac-news-detail.pl?id=5",

    footer_srv_title4      => "Liên hệ Ban quản trị Thư viện",
    footer_srv_title4_en   => "Contact Library Admin",
    footer_srv_link4       => "/cgi-bin/koha/opac-reportproblem.pl",

    # ── 8. THÔNG TIN HỆ THỐNG & BẢN QUYỀN ────────────────────────────────────
    system_ils             => "Koha ILS 25.12",
    system_sso             => "FTU Single Sign-On",
    copyright_year         => "2026",
    copyright_text         => "© 2026 Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh. Bảo lưu mọi quyền.",
    copyright_text_en      => "© 2026 Library of Foreign Trade University - Ho Chi Minh City Branch. All rights reserved."
} %]

[%# ── BẢN ĐỊA HÓA CHO GIAO DIỆN TIẾNG ANH (EN) ────────────────────────────── %]
[% IF lang == 'en' %]
    [% FTU_BRAND.library_name_short   = "FTU Library" %]
    [% FTU_BRAND.campus_current_short = "Ho Chi Minh City Branch" %]
    [% FTU_BRAND.logo_alt             = "FTU Library Logo - Foreign Trade University" %]
[% END %]

[%# ── CÁC BIẾN TẮT THUẬN TIỆN TRUY XUẤT NHANH ────────────────────────────── %]
[% SET FTU_NAME         = FTU_BRAND.library_name %]
[% SET FTU_SHORT        = FTU_BRAND.library_name_short %]
[% SET FTU_UNI          = (lang == 'en' && FTU_BRAND.university_name_en) ? FTU_BRAND.university_name_en : FTU_BRAND.university_name %]
[% SET FTU_CAMPUS       = FTU_BRAND.campus_current %]
[% SET FTU_EMAIL        = FTU_BRAND.email_contact %]
[% SET FTU_PHONE        = FTU_BRAND.hotline_hcmc %]
[% SET FTU_ADDR         = FTU_BRAND.campus_hcm_addr %]
[% SET FTU_HOURS        = FTU_BRAND.hours_summary %]
[% SET FTU_PORTAL       = FTU_BRAND.link_portal %]
[% SET FTU_DSPACE       = FTU_BRAND.link_dspace %]
[% SET FTU_SSO          = FTU_BRAND.link_sso %]
[% SET FTU_DRM          = FTU_BRAND.link_drm %]
[% SET FTU_FACEBOOK     = FTU_BRAND.link_facebook %]
[% SET FTU_YOUTUBE      = FTU_BRAND.link_youtube %]
