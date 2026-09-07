[% USE raw %]
[% USE ItemTypes %]
<div
    class="bookcover"
    data-itemtype="[% SEARCH_RESULT.itemtype | html %]"
    data-itemtype_description="[% ItemTypes.GetDescription(SEARCH_RESULT.itemtype) | html %]"
    data-biblionumber="[% SEARCH_RESULT.biblionumber | html %]"
    data-title="[% SEARCH_RESULT.title | html %]"
    data-subtitle="[% SEARCH_RESULT.subtitle | html %]"
    data-author="[% SEARCH_RESULT.author | html %]"
    data-isbn="[% SEARCH_RESULT.normalized_isbn | html %]"
>
 <div
        class="cover-slider cover-slides itemtype_[% SEARCH_RESULT.itemtype | html %]"
        data-biblionumber="[% SEARCH_RESULT.biblionumber | html %]"
        data-title="[% SEARCH_RESULT.title | html %]"
        data-isbn="[% SEARCH_RESULT.normalized_isbn | html %]"
        data-isbn="[% To.json(SEARCH_RESULT.normalized_isbn) | $raw %]"
    >
 [% IF ( OPACLocalCoverImages && SEARCH_RESULT.has_local_cover_image ) %]
 <div class="cover-image local-coverimg">
 <a href="/cgi-bin/koha/opac-image.pl?biblionumber=[% SEARCH_RESULT.biblionumber | uri %]">
 <img alt="Ảnh bìa cục bộ" src="/cgi-bin/koha/opac-image.pl?thumbnail=1&biblionumber=[% SEARCH_RESULT.biblionumber | uri %]" />
 </a>
 <div class="hint">Ảnh bìa cục bộ</div>
 </div>
 [% END %]

 [% IF ( OPACAmazonCoverImages && SEARCH_RESULT.normalized_isbn) %]
 <div class="cover-image amazon-coverimg">
 <a href="https://images-na.ssl-images-amazon.com/images/P/[% SEARCH_RESULT.normalized_isbn | uri %].01.LZZZZZZZ.jpg">
 <img alt="Ảnh bìa lấy từ Amazon" data-link="http://www.amazon[% AmazonTld | uri %]/gp/reader/[% SEARCH_RESULT.normalized_isbn | html %][% AmazonAssocTag | html %]#reader-link" id="amazon-thumbnail-[% SEARCH_RESULT.biblionumber | html %]" src="https://images-na.ssl-images-amazon.com/images/P/[% SEARCH_RESULT.normalized_isbn | uri %].01.MZZZZZZZ.jpg" />
 </a>
 <div class="hint">Ảnh từ Amazon.com</div>
 </div>
 [% END %]

 [% IF ( SyndeticsCoverImages ) %]
 [% IF ( SEARCH_RESULT.normalized_isbn || SEARCH_RESULT.normalized_upc || SEARCH_RESULT.normalized_oclc ) %]
 <div class="cover-image syndetics-coverimg">
 <a
                        href="https://secure.syndetics.com/index.aspx?isbn=[% SEARCH_RESULT.normalized_isbn | uri %]/[% SyndeticsCoverImageSize | uri %].GIF&amp;client=[% SyndeticsClientCode | uri %]&amp;type=xw10&amp;upc=[% SEARCH_RESULT.normalized_upc | uri %]&amp;oclc=[% SEARCH_RESULT.normalized_oclc | uri %]"
                    >
 <img alt="Ảnh bìa lấy từ Syndetics" id="syndetics-thumbnail-[% SEARCH_RESULT.biblionumber | html %]" src="https://secure.syndetics.com/index.aspx?isbn=[% SEARCH_RESULT.normalized_isbn | uri %]/[% SyndeticsCoverImageSize | uri %].GIF&client=[% SyndeticsClientCode | uri %]&type=xw10&upc=[% SEARCH_RESULT.normalized_upc | uri %]&oclc=[% SEARCH_RESULT.normalized_oclc | uri %]" />
 </a>
 <div class="hint">Ảnh từ Syndetics</div>
 </div>
 [% END %]
 [% END %]

 [% IF ( GoogleJackets ) %]
 <div class="cover-image googlejacket-coverimg">
 <div class="[% SEARCH_RESULT.normalized_isbn | html %]" id="gbs-thumbnail-preview" data-use-data-link="1"></div>
 <div class="hint">Ảnh từ Google Jackets</div>
 </div>
 [% END %]

 [% IF ( OPACCoce && SEARCH_RESULT.normalized_isbn ) %]
 [% coce_id = normalized_ean || SEARCH_RESULT.normalized_isbn %]
 <div class="cover-image coce-coverimg">
 [% IF ( coce_id ) %]
 <a class="[% coce_id | html %]" id="coce-thumbnail-[% SEARCH_RESULT.biblionumber | html %]"></a>
 [% END %]
 <div class="hint">Ảnh từ Coce</div>
 </div>
 [% END %]

 [% IF OpenLibraryCovers %]
 <div class="cover-image openlibrary-coverimg">
 <div class="[% SEARCH_RESULT.normalized_isbn | html %]" id="openlibrary-thumbnail-[% SEARCH_RESULT.biblionumber | html %]" data-use-data-link="1"></div>
 <div class="hint">Ảnh từ OpenLibrary</div>
 </div>
 [% END %]

 [% IF OPACCustomCoverImages %]
 [% SET custom_cover_image_url = SEARCH_RESULT.biblio_object.custom_cover_image_url %]
 [% IF custom_cover_image_url %]
 <div class="cover-image custom-coverimg">
 <a class="custom_cover_image" href="[% custom_cover_image_url | url %]">
 <img alt="Ảnh bìa tùy chỉnh" id="custom-thumbnail-[% SEARCH_RESULT.biblionumber | html %]" src="[% custom_cover_image_url | url %]" />
 </a>
 <div class="hint">Ảnh bìa tùy chỉnh</div>
 </div>
 [% END %]
 [% END %]
 </div>
 <!-- /.cover-slider --> </div
><!-- / .bookcover -->
