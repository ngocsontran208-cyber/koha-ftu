[%# ========================================================================= %]
[%# FTU BRAND & CONTACT CONFIGURATION (TRUNG TÂM CẤU HÌNH THƯƠNG HIỆU & LIÊN HỆ) %]
[%# ------------------------------------------------------------------------- %]
[%# File này chứa toàn bộ thông tin nhận diện thương hiệu, tên trường, tên thư%]
[%# viện, hotline, email, giờ mở cửa, địa chỉ các cơ sở, mạng xã hội...       %]
[%#                                                                           %]
[%# QUY TẮC SỬ DỤNG:                                                          %]
[%# Mọi trang cần dùng thông tin thương hiệu chỉ cần gọi:                     %]
[%#     PROCESS 'ftu-brand-config.inc'                                        %]
[%# Sau đó sử dụng biến dạng:                                                 %]
[%#     FTU_BRAND.library_name                                                %]
[%#     FTU_BRAND.email_contact                                               %]
[%#     FTU_BRAND.hotline_hcmc                                                %]
[%#                                                                           %]
[%# KHI CẦN THAY ĐỔI ĐỊA CHỈ, EMAIL, SỐ ĐIỆN THOẠI, LOGO HOẶC TÊN TRƯỜNG:     %]
[%# BẠN CHỈ CẦN CHỈNH SỬA DUY NHẤT FILE NÀY! TẤT CẢ CÁC TRANG SẼ TỰ CẬP NHẬT.  %]
[%# ========================================================================= %]

[% SET FTU_BRAND = {
    # ── 1. TÊN ĐƠN VỊ & PHÂN HIỆU ──────────────────────────────────────────
    university_name        => "Trường Đại học Ngoại thương",
    university_name_en     => "Foreign Trade University",
    university_short       => "FTU",
    campus_current         => "Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    campus_current_short   => "Cơ sở II – TP. Hồ Chí Minh",
    campus_current_en      => "Foreign Trade University - Ho Chi Minh City Branch",

    # ── 2. TÊN THƯ VIỆN & KHẨU HIỆU ─────────────────────────────────────────
    library_name           => "Thư viện Phân hiệu Trường Đại học Ngoại thương",
    library_name_short     => "Thư viện FTU",
    library_name_full      => "Thư viện Trường Đại học Ngoại thương",
    library_name_en        => "Foreign Trade University Library",
    library_sub_title      => "Foreign Trade University Library - Ho Chi Minh City Branch",
    library_slogan         => "Không gian học tập & nghiên cứu hiện đại, kết nối cộng đồng giảng viên và sinh viên với kho tri thức toàn diện",
    library_description    => "Trung tâm Thông tin – Tri thức hiện đại, kết nối cộng đồng giảng viên và sinh viên FTU với nguồn học liệu số phong phú, sách in chuyên ngành chất lượng cao và dịch vụ hỗ trợ nghiên cứu chuẩn quốc tế.",
    library_description_en => "A modern center for information and knowledge, connecting FTU faculty, researchers, and students with high-impact digital databases, comprehensive print collections, and world-class academic support.",

    # ── 3. LOGO & BIỂU TRƯNG NHẬN DIỆN ──────────────────────────────────────
    logo_url               => "/opac-tmpl/bootstrap/images/ftu-logo.png",
    logo_alt               => "FTU Logo - Thư viện Đại học Ngoại thương",
    favicon_svg            => "/opac-tmpl/bootstrap/images/favicon.svg?v=ftu",
    favicon_ico            => "/opac-tmpl/bootstrap/images/favicon.ico?v=ftu",

    # ── 4. EMAIL & HOTLINE HỖ TRỢ BẠN ĐỌC ──────────────────────────────────
    email_contact          => "thuvien@ftu.edu.vn",
    email_cs2              => "thuvien.cs2@ftu.edu.vn",
    hotline_hanoi          => "(024) 3835 6800",
    hotline_hanoi_ext      => "Máy lẻ: 532 / 535",
    hotline_hcmc           => "(028) 3512 7254",
    hotline_hcmc_sub       => "(028) 3512 7258",
    hotline_quangninh      => "(0203) 3850 411",

    # ── 5. GIỜ PHỤC VỤ / LỊCH MỞ CỬA ────────────────────────────────────────
    hours_status           => "Đang mở cửa",
    hours_status_en        => "Open Now",
    hours_summary          => "Thứ 2 – Thứ 6: 07:30 – 19:30 | Thứ 7: 08:00 – 17:00",
    hours_summary_en       => "Mon – Fri: 07:30 – 19:30 | Sat: 08:00 – 17:00",
    hours_weekdays         => "07:30 – 19:30 (Thứ 2 – Thứ 6)",
    hours_saturday         => "08:00 – 17:00 (Thứ 7)",
    hours_sunday           => "Nghỉ (Chủ nhật & Ngày Lễ)",

    # ── 6. ĐỊA CHỈ & LIÊN HỆ THƯ VIỆN PHÂN HIỆU FTU ──────────────────────────
    campus_hcm_title       => "Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    campus_hcm_title_en    => "Foreign Trade University - Ho Chi Minh City Branch",
    campus_hcm_addr        => "Số 15, Đường D5, P. Thạnh Mỹ Tây, TP. HCM",
    campus_hcm_addr_en     => "No. 15, D5 St., Thanh My Tay Ward, Ho Chi Minh City",
    campus_hcm_phone       => "(028) 3512 7254 - 3512 7258",

    campus_hn_title        => "Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    campus_hn_title_en     => "Foreign Trade University - Ho Chi Minh City Branch",
    campus_hn_addr         => "Số 15, Đường D5, P. Thạnh Mỹ Tây, TP. HCM",
    campus_hn_addr_en      => "No. 15, D5 St., Thanh My Tay Ward, Ho Chi Minh City",
    campus_hn_phone        => "(028) 3512 7254 - 3512 7258",

    campus_qn_title        => "Thư viện Phân hiệu Trường Đại học Ngoại thương tại TP. Hồ Chí Minh",
    campus_qn_title_en     => "Foreign Trade University - Ho Chi Minh City Branch",
    campus_qn_addr         => "Số 15, Đường D5, P. Thạnh Mỹ Tây, TP. HCM",
    campus_qn_addr_en      => "No. 15, D5 St., Thanh My Tay Ward, Ho Chi Minh City",
    campus_qn_phone        => "(028) 3512 7254 - 3512 7258",

    # ── 7. ĐƯỜNG DẪN CỔNG THÔNG TIN & HỆ THỐNG LIÊN THÔNG ───────────────────
    link_portal            => "http://ftu.edu.vn",
    link_portal_cs2        => "http://cs2.ftu.edu.vn",
    link_dspace            => Koha.Preference('FTU_DSpaceBaseURL') || "http://localhost:4000",
    link_sso               => Koha.Preference('FTU_SSOBaseURL') || "http://localhost:8090",
    link_drm               => Koha.Preference('FTU_DRMBaseURL') || "http://localhost:8095",
    link_opac              => Koha.Preference('OPACBaseURL') || "",
    link_staff             => Koha.Preference('staffClientBaseURL') || "",
    link_facebook          => "https://www.facebook.com/thuvienftuhanoi",
    link_facebook_cs2      => "https://www.facebook.com/ftu2.hcmc",
    link_youtube           => "https://www.youtube.com/@FTUChannel",
    link_databases         => "/cgi-bin/ftu/opac-databases.pl",
    link_search            => "/cgi-bin/ftu/opac-search.pl",
    link_passwd            => "/cgi-bin/ftu/opac-passwd.pl",

    # ── 7b. LIÊN KẾT NHANH CHÂN TRANG (FOOTER QUICK LINKS) ─────────────────
    title_home             => "Trang chủ Thư viện",
    title_home_en          => "Library Home",
    link_home              => "/cgi-bin/ftu/opac-main.pl",
    title_advsearch        => "Tìm kiếm tài liệu nâng cao",
    title_advsearch_en     => "Advanced Search",
    link_advsearch         => "/cgi-bin/ftu/opac-search.pl",
    title_databases        => "Cơ sở dữ liệu điện tử",
    title_databases_en     => "Electronic Databases",
    title_renew            => "Gia hạn sách trực tuyến",
    title_renew_en         => "Online Book Renewal",
    link_renew             => "/cgi-bin/ftu/opac-user.pl#opac-user-checkouts",
    title_guide            => "Hướng dẫn sử dụng OPAC",
    title_guide_en         => "OPAC User Guide",
    link_guide             => "/cgi-bin/ftu/opac-news-detail.pl?id=1",

    # ── 8. THÔNG TIN HỆ THỐNG & BẢN QUYỀN ────────────────────────────────────
    system_ils             => "Koha ILS 25.12",
    system_sso             => "FTU Single Sign-On",
    copyright_year         => "2026",
    copyright_text         => "© 2026 Thư viện Trường Đại học Ngoại thương (Foreign Trade University Library). Bảo lưu mọi quyền.",
    copyright_text_en      => "© 2026 Foreign Trade University Library. All rights reserved."
} %]

[%# ── TỰ ĐỘNG BẢN ĐỊA HÓA CHO GIAO DIỆN TIẾNG ANH (EN) ────────────────────── %]
[% IF lang == 'en' %]
    [% FTU_BRAND.library_name         = FTU_BRAND.library_name_en || FTU_BRAND.library_name %]
    [% FTU_BRAND.library_name_short   = "FTU Library" %]
    [% FTU_BRAND.campus_current       = FTU_BRAND.campus_current_en || FTU_BRAND.campus_current %]
    [% FTU_BRAND.campus_current_short = "Campus II – HCMC" %]
    [% FTU_BRAND.logo_alt             = "FTU Library Logo - Foreign Trade University" %]
    [% FTU_BRAND.hours_status         = FTU_BRAND.hours_status_en || FTU_BRAND.hours_status %]
    [% FTU_BRAND.hours_summary        = FTU_BRAND.hours_summary_en || FTU_BRAND.hours_summary %]
    [% FTU_BRAND.title_home           = FTU_BRAND.title_home_en || FTU_BRAND.title_home %]
    [% FTU_BRAND.title_advsearch      = FTU_BRAND.title_advsearch_en || FTU_BRAND.title_advsearch %]
    [% FTU_BRAND.title_databases      = FTU_BRAND.title_databases_en || FTU_BRAND.title_databases %]
    [% FTU_BRAND.title_renew          = FTU_BRAND.title_renew_en || FTU_BRAND.title_renew %]
    [% FTU_BRAND.title_guide          = FTU_BRAND.title_guide_en || FTU_BRAND.title_guide %]
    [% FTU_BRAND.copyright_text       = FTU_BRAND.copyright_text_en || FTU_BRAND.copyright_text %]
[% END %]

[%# ── CÁC BIẾN TẮT THUẬN TIỆN TRUY XUẤT NHANH ────────────────────────────── %]
[% SET FTU_NAME         = FTU_BRAND.library_name %]
[% SET FTU_SHORT        = FTU_BRAND.library_name_short %]
[% SET FTU_UNI          = (lang == 'en' && FTU_BRAND.university_name_en) ? FTU_BRAND.university_name_en : FTU_BRAND.university_name %]
[% SET FTU_CAMPUS       = FTU_BRAND.campus_current %]
[% SET FTU_EMAIL        = FTU_BRAND.email_contact %]
[% SET FTU_HOTLINE_HN   = FTU_BRAND.hotline_hanoi %]
[% SET FTU_HOTLINE_HCM  = FTU_BRAND.hotline_hcmc %]
[% SET FTU_ADDR_HCM     = (lang == 'en' && FTU_BRAND.campus_hcm_addr_en) ? FTU_BRAND.campus_hcm_addr_en : FTU_BRAND.campus_hcm_addr %]
[% SET FTU_LOGO         = FTU_BRAND.logo_url %]
[% SET FTU_LINK_DSPACE  = FTU_BRAND.link_dspace %]
[% SET FTU_LINK_SSO     = FTU_BRAND.link_sso %]
[% SET FTU_LINK_DRM     = FTU_BRAND.link_drm %]
[% SET FTU_LINK_OPAC    = FTU_BRAND.link_opac %]
[% SET FTU_LINK_STAFF   = FTU_BRAND.link_staff %]

