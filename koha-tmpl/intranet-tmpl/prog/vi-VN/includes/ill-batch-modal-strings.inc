[% USE Koha %]
[% USE raw %]
<!-- ill-batch-table-strings.inc -->
<script nonce="[% Koha.CSPNonce | $raw %]">
    var ill_batch_add = _("Add new batch");
    var ill_batch_update = _("Update batch");
    var ill_batch_none = _("Không có");
    var ill_batch_retrieving_metadata = _("Retrieving metadata");
    var ill_batch_api_fail = _("Unable to retrieve batch details");
    var ill_batch_statuses_api_fail = _("Unable to retrieve batch statuses");
    var ill_batch_api_request_fail = _("Unable to create local request");
    var ill_batch_requests_api_fail = _("Unable to retrieve batch requests");
    var ill_batch_unknown = _("Không xác định");
    var ill_batch_doi = _("DOI");
    var ill_batch_pmid = _("PubMed ID");
    var ill_populate_waiting = _("Retrieving...");
    var ill_populate_failed = _("Failed to retrieve");
    var ill_button_remove = _("Loại bỏ");
    var ill_batch_create_api_fail = _("Unable to create batch request");
    var ill_batch_update_api_fail = _("Unable to update batch request");
    var ill_batch_item_remove = _("Are you sure you want to remove this item from the batch?");
    var ill_batch_create_cancel_button = _("Thoát");
    var ill_batch_metadata_more = _("More");
    var ill_batch_metadata_less = _("Less");
    var ill_batch_available_via = _("Available via");
    var ill_batch_metadata = {
        doi: _("DOI"),
        pmid: _("PubMed ID"),
        issn: _("Số ISSN"),
        title: _("Nhan đề"),
        year: _("Năm"),
        issue: _("Kỳ"),
        pages: _("Pages"),
        publisher: _("Nhà xuất bản"),
        article_title: _("Article title"),
        article_author: _("Article author"),
        volume: _("Tập"),
    };
</script>
<!-- / ill-batch-table-strings.inc -->
