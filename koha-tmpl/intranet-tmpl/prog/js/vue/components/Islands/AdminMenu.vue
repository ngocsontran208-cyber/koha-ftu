<template>
    <div id="admin-menu" class="sidebar_menu">
        <template v-if="can_user_parameters_manage_sysprefs">
            <h5>{{ $__("Cấu hình hệ thống") }}</h5>
            <ul>
                <li>
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/preferences.pl"
                        >{{ $__("Cấu hình hệ thống") }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_parameters_manage_libraries ||
                can_user_parameters_manage_itemtypes ||
                can_user_parameters_manage_auth_values
            "
        >
            <h5>{{ $__("Thông số cơ bản") }}</h5>
            <ul>
                <template v-if="can_user_parameters_manage_libraries">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/branches.pl"
                            >{{ $__("Thư viện") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/library_groups.pl"
                            >{{ $__("Nhóm thư viện") }}</a
                        >
                    </li>
                </template>
                <li v-if="can_user_parameters_manage_itemtypes">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/itemtypes.pl"
                        >{{ $__("Kiểu tài liệu") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_auth_values">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/authorised_values.pl"
                        >{{ $__("Giá trị định chuẩn") }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_parameters_manage_patron_categories ||
                can_user_parameters_manage_circ_rules ||
                can_user_parameters_manage_patron_attributes ||
                can_user_parameters_manage_transfers ||
                can_user_parameters_manage_item_circ_alerts ||
                can_user_parameters_manage_cities ||
                can_user_parameters_manage_curbside_pickups ||
                can_user_parameters_manage_patron_restrictions
            "
        >
            <h5>{{ $__("Bạn đọc và lưu thông") }}</h5>
            <ul>
                <li v-if="can_user_parameters_manage_patron_categories">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/categories.pl"
                        >{{ $__("Kiểu bạn đọc") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_circ_rules">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/smart-rules.pl"
                        >{{ $__("Quy tắc mượn trả và tiền phạt") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_patron_attributes">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/patron-attr-types.pl"
                        >{{ $__("Kiểu thuộc tính bạn đọc") }}</a
                    >
                </li>
                <template v-if="can_user_parameters_manage_transfers">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/branch_transfer_limits.pl"
                            >{{ $__("Giới hạn chuyển tài liệu") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/transport-cost-matrix.pl"
                            >{{ $__("Bảng phí vận chuyển") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/float_limits.pl"
                            >{{ $__("Giới hạn luân chuyển") }}</a
                        >
                    </li>
                </template>
                <li v-if="can_user_sip2">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/sip2/sip2.pl"
                        >{{ $__("Lưu thông tự phục vụ (SIP2)") }}</a
                    >
                </li>
                <li
                    v-if="
                        can_user_parameters_manage_identity_providers &&
                        shibbolethauthentication
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/shibboleth/shibboleth.pl"
                        >{{ $__("Cấu hình Shibboleth") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_item_circ_alerts">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/item_circulation_alerts.pl"
                        >{{ $__("Cảnh báo mượn trả") }}</a
                    >
                </li>
                <li
                    v-if="
                        usecirculationdesks &&
                        can_user_parameters_manage_libraries
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/desks.pl"
                        >{{ $__("Bàn làm việc") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_cities">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/cities.pl"
                        >{{ $__("Thành phố và thị trấn") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_curbside_pickups">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/curbside_pickup.pl"
                        >{{ $__("Nhận tài liệu ngoài lề đường") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_patron_restrictions">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/restrictions.pl"
                        >{{ $__("Kiểu hạn chế bạn đọc") }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_parameters_manage_accounts ||
                (usecashregisters && can_user_parameters_manage_cash_registers)
            "
        >
            <h5>{{ $__("Kế toán") }}</h5>
            <ul>
                <template v-if="can_user_parameters_manage_accounts">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/debit_types.pl"
                            >{{ $__("Loại ghi nợ") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/credit_types.pl"
                            >{{ $__("Loại ghi có") }}</a
                        >
                    </li>
                </template>
                <li
                    v-if="
                        usecashregisters &&
                        can_user_parameters_manage_cash_registers
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/cash_registers.pl"
                        >{{ $__("Máy tính tiền") }}</a
                    >
                </li>
            </ul>
        </template>

        <template v-if="can_user_plugins && plugins_enabled">
            <h5>{{ $__("Gói mở rộng (Plugins)") }}</h5>
            <ul>
                <li>
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/plugins/plugins-home.pl"
                        >{{ $__("Gói mở rộng (Plugins)") }}</a
                    >
                </li>
            </ul>
        </template>

        <template v-if="can_user_parameters_manage_background_jobs">
            <h5>{{ $__("Tác vụ nền") }}</h5>
            <ul>
                <li>
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/background_jobs.pl"
                        >{{ $__("Tác vụ nền") }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_parameters_manage_marc_frameworks ||
                can_user_parameters_manage_classifications ||
                can_user_parameters_manage_matching_rules ||
                can_user_parameters_manage_oai_sets ||
                can_user_parameters_manage_item_search_fields ||
                can_user_parameters_manage_search_engine_config ||
                can_user_parameters_manage_marc_overlay_rules ||
                (savedsearchfilters &&
                    can_user_parameters_manage_search_filters)
            "
        >
            <h5>{{ $__("Biên mục") }}</h5>
            <ul>
                <template v-if="can_user_parameters_manage_marc_frameworks">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/biblio_framework.pl"
                            >{{ $__("Khung mẫu biên mục MARC") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/koha2marclinks.pl"
                            >{{ $__("Ánh xạ Koha - MARC") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/checkmarc.pl"
                            >{{ $__("Kiểm tra khung mẫu biên mục MARC") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/authtypes.pl"
                            >{{ $__("Kiểu dữ liệu kiểm soát") }}</a
                        >
                    </li>
                </template>
                <li v-if="can_user_parameters_manage_classifications">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/classsources.pl"
                        >{{ $__("Cấu hình khung phân loại") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_matching_rules">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/matching-rules.pl"
                        >{{ $__("Quy tắc so khớp biểu ghi") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_record_sources">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/record_sources"
                        >{{ $__("Nguồn biểu ghi") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_marc_overlay_rules">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/marc-overlay-rules.pl"
                        >{{ $__("Quy tắc ghi đè biểu ghi") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_oai_sets">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/oai_sets.pl"
                        >{{ $__("Cấu hình tập hợp OAI") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_item_search_fields">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/items_search_fields.pl"
                        >{{ $__("Trường tìm kiếm tài liệu") }}</a
                    >
                </li>
                <li
                    v-if="
                        savedsearchfilters &&
                        can_user_parameters_manage_search_filters
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/search_filters.pl"
                        >{{ $__("Bộ lọc tìm kiếm") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_search_engine_config">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/searchengine/elasticsearch/mappings.pl"
                        >{{
                            $__("Cấu hình máy tìm kiếm (Elasticsearch)")
                        }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_acquisition_currencies_manage ||
                can_user_acquisition_period_manage ||
                can_user_acquisition_budget_manage ||
                (edifact && can_user_acquisition_edi_manage) ||
                (marcorderingautomation &&
                    can_user_acquisition_marc_order_manage)
            "
        >
            <h5>{{ $__("Thông số bổ sung") }}</h5>
            <ul>
                <li v-if="can_user_acquisition_currencies_manage">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/currency.pl"
                        >{{ $__("Tiền tệ và tỷ giá") }}</a
                    >
                </li>
                <li v-if="can_user_acquisition_period_manage">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/aqbudgetperiods.pl"
                        >{{ $__("Ngân sách") }}</a
                    >
                </li>
                <li v-if="can_user_acquisition_budget_manage">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/aqbudgets.pl"
                        >{{ $__("Quỹ") }}</a
                    >
                </li>
                <template v-if="edifact && can_user_acquisition_edi_manage">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/edi_accounts.pl"
                            >{{ $__("Tài khoản EDI") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/edi_ean_accounts.pl"
                            >{{ $__("Mã EAN thư viện") }}</a
                        >
                    </li>
                </template>
                <li
                    v-if="
                        marcorderingautomation &&
                        can_user_acquisition_marc_order_manage
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/marc_order_accounts.pl"
                        >{{ $__("Tài khoản đặt mua MARC") }}</a
                    >
                </li>
            </ul>
        </template>

        <template
            v-if="
                can_user_parameters_manage_identity_providers ||
                can_user_parameters_manage_smtp_servers ||
                can_user_parameters_manage_file_transports ||
                can_user_parameters_manage_search_targets ||
                can_user_parameters_manage_didyoumean ||
                can_user_parameters_manage_column_config ||
                can_user_parameters_manage_audio_alerts ||
                (can_user_parameters_manage_sms_providers &&
                    smssenddriver == 'Email') ||
                can_user_parameters_manage_usage_stats ||
                can_user_parameters_manage_additional_fields ||
                (enableadvancedcatalogingeditor &&
                    can_user_parameters_manage_keyboard_shortcuts)
            "
        >
            <h5>{{ $__("Thông số bổ sung khác") }}</h5>
            <ul>
                <li v-if="can_user_parameters_manage_identity_providers">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/identity_providers.pl"
                        >{{ $__("Nhà cung cấp định danh") }}</a
                    >
                </li>
                <template v-if="can_user_parameters_manage_search_targets">
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/z3950servers.pl"
                            >{{ $__("Máy chủ Z39.50/SRU") }}</a
                        >
                    </li>
                    <li>
                        <a
                            :ref="el => templateRefs.push(el)"
                            href="/cgi-bin/koha/admin/oai_servers.pl"
                            >{{ $__("Kho lưu trữ OAI") }}</a
                        >
                    </li>
                </template>
                <li v-if="can_user_parameters_manage_smtp_servers">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/smtp_servers.pl"
                        >{{ $__("Máy chủ SMTP") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_file_transports">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/file_transports.pl"
                        >{{ $__("Truyền tải tập tin") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_didyoumean">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/didyoumean.pl"
                        >{{ $__("Có phải bạn muốn tìm?") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_column_config">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/columns_settings.pl"
                        >{{ $__("Cài đặt bảng") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_audio_alerts">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/audio_alerts.pl"
                        >{{ $__("Cảnh báo âm thanh") }}</a
                    >
                </li>
                <li
                    v-if="
                        can_user_parameters_manage_sms_providers &&
                        smssenddriver == 'Email'
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/sms_providers.pl"
                        >{{ $__("Nhà cung cấp dịch vụ SMS") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_usage_stats">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/usage_statistics.pl"
                        >{{ $__("Chia sẻ thống kê sử dụng") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_mana">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/share_content.pl"
                        >{{ $__("Chia sẻ nội dung với Mana KB") }}</a
                    >
                </li>
                <li v-if="can_user_parameters_manage_additional_fields">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/additional-fields.pl"
                        >{{ $__("Trường dữ liệu bổ sung") }}</a
                    >
                </li>
                <li
                    v-if="
                        enableadvancedcatalogingeditor &&
                        can_user_parameters_manage_keyboard_shortcuts
                    "
                >
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/adveditorshortcuts.pl"
                        >{{ $__("Phím tắt") }}</a
                    >
                </li>
                <li v-if="illmodule && can_user_ill">
                    <a
                        :ref="el => templateRefs.push(el)"
                        href="/cgi-bin/koha/admin/ill_batch_statuses.pl"
                        >{{ $__("Trạng thái lô mượn liên thư viện") }}</a
                    >
                </li>
            </ul>
        </template>
    </div>
    <!-- /.sidebar_menu -->
</template>

<script>
import { onMounted, ref } from "vue";

export default {
    name: "AdminMenu",
    props: {
        can_user_parameters_manage_sysprefs: Number,
        can_user_parameters_manage_libraries: Number,
        can_user_parameters_manage_itemtypes: Number,
        can_user_parameters_manage_auth_values: Number,
        can_user_parameters_manage_patron_categories: Number,
        can_user_parameters_manage_circ_rules: Number,
        can_user_parameters_manage_patron_attributes: Number,
        can_user_parameters_manage_transfers: Number,
        can_user_parameters_manage_item_circ_alerts: Number,
        can_user_parameters_manage_cities: Number,
        can_user_parameters_manage_curbside_pickups: Number,
        can_user_parameters_manage_patron_restrictions: Number,
        can_user_sip2: Number,
        can_user_parameters_manage_identity_providers: Number,
        can_user_parameters_manage_accounts: Number,
        can_user_parameters_manage_cash_registers: Number,
        can_user_plugins: Number,
        plugins_enabled: Number,
        can_user_parameters_manage_background_jobs: Number,
        can_user_parameters_manage_marc_frameworks: Number,
        can_user_parameters_manage_classifications: Number,
        can_user_parameters_manage_matching_rules: Number,
        can_user_parameters_manage_oai_sets: Number,
        can_user_parameters_manage_item_search_fields: Number,
        can_user_parameters_manage_search_engine_config: Number,
        can_user_parameters_manage_marc_overlay_rules: Number,
        can_user_parameters_manage_search_filters: Number,
        can_user_parameters_manage_record_sources: Number,
        can_user_acquisition_currencies_manage: Number,
        can_user_acquisition_period_manage: Number,
        can_user_acquisition_budget_manage: Number,
        can_user_acquisition_edi_manage: Number,
        can_user_acquisition_marc_order_manage: Number,
        can_user_parameters_manage_smtp_servers: Number,
        can_user_parameters_manage_file_transports: Number,
        can_user_parameters_manage_search_targets: Number,
        can_user_parameters_manage_didyoumean: Number,
        can_user_parameters_manage_column_config: Number,
        can_user_parameters_manage_audio_alerts: Number,
        can_user_parameters_manage_sms_providers: Number,
        can_user_parameters_manage_usage_stats: Number,
        can_user_parameters_manage_mana: Number,
        can_user_parameters_manage_additional_fields: Number,
        can_user_parameters_manage_keyboard_shortcuts: Number,
        can_user_ill: Number,
        shibbolethauthentication: Number,
        usecirculationdesks: Number,
        usecashregisters: Number,
        savedsearchfilters: Number,
        edifact: Number,
        marcorderingautomation: Number,
        smssenddriver: String,
        enableadvancedcatalogingeditor: Number,
        illmodule: Number,
    },
    setup() {
        const templateRefs = ref([]);

        onMounted(() => {
            const path = location.pathname.substring(1);

            templateRefs.value
                .find(a => a.href.includes(path))
                ?.classList.add("current");
        });
        return {
            templateRefs,
        };
    },
};
</script>

<style scoped>
.sidebar_menu a.current {
    font-weight: bold;
}
</style>