[% IF op == "batch_list" %]
 <h1>
 <span>View ILL requests batches</span>
 </h1>
 <div class="page-section">
 <h2>Details for all batches</h2>
 <table id="ill-batch-requests">
 <thead>
 <tr id="ill-batch-header">
 <th scope="col">Batch ID</th>
 <th scope="col">Tên</th>
 <th scope="col">Number of requests</th>
 <th scope="col">Trạng thái</th>
 <th scope="col">Bạn đọc</th>
 <th scope="col">Thư viện</th>
 <th scope="col"></th>
 </tr>
 </thead>
 <tbody id="ill-batch-body"> </tbody>
 </table>
 </div>
[% END %]
