[% USE Koha %]
[% USE raw %]
[% PROCESS 'modal-claims.inc' %]
[% INCLUDE 'format_price.inc' %]

[% IF ( issuecount ) %]
    <div id="issues-table-loading-message">
        <p>
            <a id="issues-table-load-now-button" href="#" class="btn btn-default"><i class="fa fa-book"></i> Hiển thị tài liệu đang mượn</a>
            [% SET LoadCheckoutsTableDelay = Koha.Preference('LoadCheckoutsTableDelay') %]
            [% IF LoadCheckoutsTableDelay && patronpage == 'circ' %]
                <span id="issues-table-load-delay">
                    <i id="issues-table-load-delay-spinner" class="fa fa-spinner fa-pulse fa-fw"></i>
                    <span id="issues-table-load-delay-message">Bảng tài liệu đang mượn sẽ tự động hiển thị sau [% LoadCheckoutsTableDelay | html %] giây...</span>
                </span>
            [% END %]
        </p>
    </div>
    <form name="issues" action="/cgi-bin/koha/tools/export.pl" method="post">
        [% INCLUDE 'csrf-token.inc' %]
        <table id="issues-table" style="width: 100% !Important; display: none;">
            <thead>
                <tr>
                    <th data-colname="sort_order" scope="col">&nbsp;</th>
                    <th data-colname="todays_or_previous_checkouts" scope="col">&nbsp;</th>
                    <th data-colname="title" scope="col">Nhan đề</th>
                    <th data-colname="record_type" scope="col">Kiểu tài liệu thư mục</th>
                    <th data-colname="item_type" scope="col">Kiểu tài liệu</th>
                    <th data-colname="collection" scope="col">Bộ sưu tập</th>
                    <th data-colname="location" scope="col">Kho tài liệu</th>
                    <th data-colname="homebranch" scope="col">Thư viện nhà</th>
                    <th data-colname="checkout_on_unformatted" scope="col">&nbsp;</th>
                    <th data-colname="checkout_on" scope="col">Ghi mượn lúc</th>
                    <th data-colname="due_date_unformatted" scope="col">Hạn trả</th>
                    <th data-colname="due_date" scope="col">Hạn trả</th>
                    <th data-colname="checkout_from" scope="col">Ghi mượn từ</th>
                    <th data-colname="callno" scope="col">Số phân loại</th>
                    <th data-colname="copynumber" scope="col">Số bản</th>
                    <th data-colname="charge" scope="col">Khoản phí</th>
                    <th data-colname="fine" scope="col">Khoản phạt</th>
                    <th data-colname="price" scope="col">Giá tiền</th>
                    <th data-colname="renew" scope="col"
                        >Gia hạn <p class="column-tool"><a href="#" id="CheckAllRenewals">chọn tất cả</a> | <a href="#" id="UncheckAllRenewals">bỏ chọn</a></p></th
                    >
                    <th data-colname="checkin" scope="col"
                        >Ghi trả <p class="column-tool"><a href="#" id="CheckAllCheckins">chọn tất cả</a> | <a href="#" id="UncheckAllCheckins">bỏ chọn</a></p></th
                    >
                    <th data-colname="claims_returned" scope="col">Khiếu nại ghi trả</th>
                    <th data-colname="export" scope="col"
                        >Xuất dữ liệu <p class="column-tool"><a href="#" id="CheckAllExports">chọn tất cả</a> | <a href="#" id="UncheckAllExports">bỏ chọn</a></p></th
                    >
                    <th data-colname="ftu_status" scope="col">Trạng thái</th>
                    <th data-colname="ftu_action" scope="col">Thao tác</th>
                </tr>
            </thead>
            [% INCLUDE 'checkouts-table-footer.inc' %]
        </table>
        [% UNLESS Koha.Preference( 'AlwaysLoadCheckoutsTable' ) %]
            <label for="issues-table-load-immediately">Luôn tự động hiển thị tài liệu đang mượn</label>
            <input id="issues-table-load-immediately" type="checkbox" />
        [% END %]

        <div id="issues-table-actions" style="display: none;">
            <fieldset class="action">
                [% IF ( CAN_user_circulate_override_renewals ) %]
                    [% IF Koha.Preference( 'AllowRenewalLimitOverride' ) || Koha.Preference( 'AllowRenewalOnHoldOverride' ) %]
                        <label for="override_limit">Override renewal restrictions:</label>
                        <input type="checkbox" name="override_limit" id="override_limit" value="1" />
                    [% END %]
                    [% IF Koha.Preference( 'AllowFineOverrideRenewing' ) %]
                        <label for="override_debt">Override fine restrictions:</label>
                        <input type="checkbox" name="override_debt" id="override_debt" value="1" />
                    [% END %]
                [% END %]
                [% IF ( CAN_user_circulate_circulate_remaining_permissions ) %]
                    [% IF Koha.Preference( 'UnseenRenewals' ) %]
                        <label id="renew_as_unseen_label" for="override_limit">Renew as &quot;unseen&quot; if appropriate:</label>
                        <input type="checkbox" name="renew_as_unseen" id="renew_as_unseen_checkbox" value="1" />
                    [% END %]
                    <button class="btn btn-default" id="CheckinChecked" disabled="disabled"><i class="fa fa-download"></i> Check in selected items</button>
                    <button class="btn btn-default" id="RenewChecked" disabled="disabled"><i class="fa fa-retweet"></i> Renew selected items</button>
                    <button class="btn btn-default" id="RenewAll"><i class="fa fa-book"></i> Renew all</button>
                [% END %]
            </fieldset>
            [% IF patron.account.non_issues_charges >= Koha.Preference('FineNoRenewals') %]
                <p
                    ><strong>Note: </strong> Patron has <strong><span id="patron-non-issues-charges">[% patron.account.non_issues_charges | $Price %]</span></strong> of non-issuing charges outstanding, renewals are restricted at
                    <strong><span id="fine-no-renewals-limit">[% Koha.Preference('FineNoRenewals') | $Price %]</span></strong></p
                >
            [% END %]

            [% IF Koha.Preference('ExportCircHistory') %]
                <fieldset>
                    <label for="issues-table-output-format"><strong>Export checkouts using format:</strong></label>
                    <select name="issues-table-output-format" id="issues-table-output-format">
                        <option value="iso2709_995">MARC with items</option>
                        <option value="iso2709">MARC without items</option>
                        [% IF csv_profiles.count %]
                            <option value="csv">CSV</option>
                        [% END %]
                    </select>

                    [% IF csv_profiles.count %]
                        <select name="csv_profile_id">
                            [% FOREACH csv_profile IN csv_profiles %]
                                <option value="[% csv_profile.export_format_id | html %]">[% csv_profile.profile | html %]</option>
                            [% END %]
                        </select>
                    [% END %]
                    <label for="export_items_bundle_contents">Export items bundle contents</label> <input type="checkbox" name="export_items_bundle_contents" id="export_items_bundle_contents" />
                    <label for="export_remove_fields">Don't export fields:</label>
                    <input type="text" id="export_remove_fields" name="export_remove_fields" value="[% Koha.Preference('ExportRemoveFields') | html %]" title="Use for MARC exports" />
                    <input type="hidden" name="op" value="cud-export" />
                    <input type="hidden" id="output_format" name="output_format" value="iso2709" />
                    <input type="hidden" id="dont_export_item" name="dont_export_item" value="0" />
                    <input type="hidden" id="record_type" name="record_type" value="bibs" />
                    <button class="btn btn-default btn-sm" id="export_submit"><i class="fa fa-download"></i> Export</button>
                </fieldset>
            [% END %]
        </div>
    </form>
[% ELSE %]
    <p>Bạn đọc chưa mượn tài liệu nào.</p>
[% END %]

<!-- Claims Returned Modal -->
[% PROCESS 'modal-claims-display' %]
