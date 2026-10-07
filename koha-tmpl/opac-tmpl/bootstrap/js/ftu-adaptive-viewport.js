/**
 * =============================================================================
 * FTU ADAPTIVE VIEWPORT ENGINE (HỆ THỐNG ĐIỀU BIẾN GIAO DIỆN DI ĐỘNG & ĐA THIẾT BỊ)
 * Tự động tính toán kích thước màn hình theo thời gian thực (Real-time Viewport Calculation)
 * và đưa ra quyết định giao diện tối ưu (Mobile Dock, Touch Carousel, Responsive Tables, Filter Drawer)
 * =============================================================================
 */
(function ($) {
  'use strict';

  var ViewportEngine = {
    state: {
      vw: 0,
      vh: 0,
      dpr: 1,
      isTouch: false,
      orientation: 'portrait',
      category: 'desktop', // 'mobile-xs' | 'mobile' | 'tablet' | 'desktop'
      isPhone: false,
      isTablet: false,
      isDesktop: true
    },

    listeners: [],

    init: function () {
      this.calculate();
      this.bindEvents();
      this.setupMobileDock();
      this.setupTouchGestures();
      this.setupMobileSearch();
      this.setupMobileFacets();
      this.enhanceHoldingsTables();
      this.setupDetailMobileLayout();
    },

    /**
     * 1. TÍNH TOÁN KÍCH THƯỚC MÀN HÌNH VÀ PHÂN LOẠI THIẾT BỊ
     */
    calculate: function () {
      var vw = window.innerWidth || document.documentElement.clientWidth;
      var vh = window.innerHeight || document.documentElement.clientHeight;
      var dpr = window.devicePixelRatio || 1;
      var isTouch = ('ontouchstart' in window) ||
                    (navigator.maxTouchPoints > 0) ||
                    (navigator.msMaxTouchPoints > 0);
      var orientation = vw > vh ? 'landscape' : 'portrait';

      var category = 'desktop';
      if (vw <= 390) {
        category = 'mobile-xs';
      } else if (vw <= 600) {
        category = 'mobile';
      } else if (vw <= 992) {
        category = 'tablet';
      }

      var isPhone = vw <= 600;
      var isTablet = vw > 600 && vw <= 992;
      var isDesktop = vw > 992;

      this.state = {
        vw: vw,
        vh: vh,
        dpr: dpr,
        isTouch: isTouch,
        orientation: orientation,
        category: category,
        isPhone: isPhone,
        isTablet: isTablet,
        isDesktop: isDesktop
      };

      // Áp dụng thuộc tính trạng thái lên thẻ gốc HTML để CSS tương thích ngay lập tức
      var root = document.documentElement;
      root.style.setProperty('--ftu-vw', vw + 'px');
      root.style.setProperty('--ftu-vh', vh + 'px');
      root.setAttribute('data-ftu-screen', category);
      root.setAttribute('data-ftu-orientation', orientation);
      root.setAttribute('data-ftu-touch', isTouch ? 'true' : 'false');

      if (isPhone) {
        root.classList.add('ftu-is-phone');
        root.classList.remove('ftu-is-desktop', 'ftu-is-tablet');
      } else if (isTablet) {
        root.classList.add('ftu-is-tablet');
        root.classList.remove('ftu-is-phone', 'ftu-is-desktop');
      } else {
        root.classList.add('ftu-is-desktop');
        root.classList.remove('ftu-is-phone', 'ftu-is-tablet');
      }

      // Thông báo cho các thành phần con đăng ký lắng nghe
      for (var i = 0; i < this.listeners.length; i++) {
        try {
          this.listeners[i](this.state);
        } catch (e) {
          console.warn('[FTU-VIEWPORT] Lỗi listener:', e);
        }
      }
    },

    bindEvents: function () {
      var self = this;
      var resizeTimer = null;

      // Lắng nghe thay đổi kích thước & xoay màn hình (Debounced 60fps)
      window.addEventListener('resize', function () {
        if (resizeTimer) cancelAnimationFrame(resizeTimer);
        resizeTimer = requestAnimationFrame(function () {
          self.calculate();
        });
      }, { passive: true });

      window.addEventListener('orientationchange', function () {
        setTimeout(function () {
          self.calculate();
        }, 120);
      }, { passive: true });
    },

    /**
     * 2. ĐIỀU PHỐI THANH ĐIỀU HƯỚNG DƯỚI ĐÁY ỨNG DỤNG DI ĐỘNG (MOBILE DOCK)
     */
    setupMobileDock: function () {
      var self = this;

      function updateActiveDock() {
        var path = window.location.pathname;
        var search = window.location.search || '';
        var $items = $('.ftu-dock-item');
        $items.removeClass('active');

        if (path.indexOf('opac-databases') !== -1) {
          $('#ftuDockDatabases').addClass('active');
        } else if (path.indexOf('opac-collections') !== -1) {
          $('#ftuDockCollections').addClass('active');
        } else if (path.indexOf('opac-user') !== -1 || path.indexOf('opac-readingrecord') !== -1 || path.indexOf('opac-account') !== -1) {
          $('#ftuDockUser').addClass('active');
        } else if (path.indexOf('opac-search') !== -1 && !search.includes('q=*')) {
          $('#ftuDockSearch').addClass('active');
        } else if (path === '/opac/' || path === '/' || path.indexOf('opac-main') !== -1) {
          $('#ftuDockHome').addClass('active');
        }
      }

      $(document).ready(function () {
        updateActiveDock();
      });

      // Xử lý nút Tìm kiếm trên thanh Dock
      $(document).on('click', '#ftuDockSearch', function (e) {
        e.preventDefault();
        var $heroInput = $('.ftu-search-input-large');
        if ($heroInput.length && $heroInput.is(':visible')) {
          $('html, body').animate({
            scrollTop: $heroInput.offset().top - 80
          }, 350, function () {
            $heroInput.focus();
          });
        } else {
          window.location.href = '/cgi-bin/koha/opac-search.pl';
        }
      });
    },

    /**
     * 3. XỬ LÝ VUỐT CHẠM CẢM ỨNG CHO BANNER CAROUSEL (TOUCH SWIPE)
     */
    setupTouchGestures: function () {
      function bindCarouselTouch() {
        var carousel = document.getElementById('ftuBannerCarousel');
        if (!carousel || carousel._touchBound) return;
        carousel._touchBound = true;

        var startX = 0;
        var startY = 0;
        var distX = 0;
        var distY = 0;
        var threshold = 40; // Ngưỡng vuốt tối thiểu 40px

        carousel.addEventListener('touchstart', function (e) {
          if (!e.touches || e.touches.length > 1) return;
          var touch = e.touches[0];
          startX = touch.pageX;
          startY = touch.pageY;
          distX = 0;
          distY = 0;
        }, { passive: true });

        carousel.addEventListener('touchmove', function (e) {
          if (!e.touches || e.touches.length > 1) return;
          var touch = e.touches[0];
          distX = touch.pageX - startX;
          distY = touch.pageY - startY;
        }, { passive: true });

        carousel.addEventListener('touchend', function () {
          // Chỉ xử lý nếu cử chỉ vuốt theo chiều ngang rõ rệt hơn chiều dọc
          if (Math.abs(distX) > Math.abs(distY) && Math.abs(distX) > threshold) {
            if (distX < 0) {
              var nextBtn = document.getElementById('ftuBannerNext');
              if (nextBtn) nextBtn.click();
            } else {
              var prevBtn = document.getElementById('ftuBannerPrev');
              if (prevBtn) prevBtn.click();
            }
          }
        }, { passive: true });
      }

      $(document).ready(function () {
        bindCarouselTouch();
        setTimeout(bindCarouselTouch, 1000);
      });
    },

    /**
     * 4. TỐI ƯU HÓA KHUNG TÌM KIẾM TRÊN DI ĐỘNG (MOBILE SEARCH FOCUS)
     */
    setupMobileSearch: function () {
      var self = this;
      $(document).on('focus', '.ftu-search-input-large', function () {
        if (self.state.isPhone) {
          var el = this;
          setTimeout(function () {
            el.scrollIntoView({ behavior: 'smooth', block: 'center' });
          }, 300);
        }
      });
    },

    /**
     * 5. NGĂN KÉO BỘ LỌC TÌM KIẾM THÔNG MINH TRÊN DI ĐỘNG (MOBILE FACETS DRAWER)
     */
    setupMobileFacets: function () {
      var self = this;
      $(document).ready(function () {
        var $facets = $('#search-facets');
        if (!$facets.length) return;

        // Bổ sung nút bấm mở Bộ lọc nổi dành cho thiết bị di động
        if (!$('#ftuMobileFilterBtn').length) {
          var $btn = $(`
            <button type="button" class="ftu-mobile-filter-btn" id="ftuMobileFilterBtn" title="Mở bộ lọc tìm kiếm">
              <i class="fa fa-sliders-h"></i>
              <span>Bộ lọc kết quả</span>
            </button>
          `);
          $('body').append($btn);

          // Tạo lớp nền mờ che phủ khi mở bộ lọc
          var $backdrop = $('<div class="ftu-facet-backdrop" id="ftuFacetBackdrop"></div>');
          $('body').append($backdrop);

          // Nút đóng bộ lọc
          if (!$facets.find('.ftu-facet-close-btn').length) {
            var $closeBar = $(`
              <div class="ftu-facet-header-mobile">
                <h5><i class="fa fa-sliders-h"></i> Bộ lọc &amp; Phân loại</h5>
                <button type="button" class="ftu-facet-close-btn" id="ftuFacetCloseBtn" aria-label="Đóng">&times;</button>
              </div>
            `);
            $facets.prepend($closeBar);
          }

          $(document).on('click', '#ftuMobileFilterBtn', function () {
            $facets.addClass('ftu-facet-open');
            $backdrop.addClass('active');
            $('body').addClass('ftu-no-scroll');
          });

          $(document).on('click', '#ftuFacetCloseBtn, #ftuFacetBackdrop', function () {
            $facets.removeClass('ftu-facet-open');
            $backdrop.removeClass('active');
            $('body').removeClass('ftu-no-scroll');
          });
        }
      });
    },

    /**
     * 6. NÂNG CAO TRẢI NGHIỆM BẢNG LƯU THÔNG & BẢN SÁCH TRÊN MÀN HÌNH NHỎ
     */
    enhanceHoldingsTables: function () {
      function wrapTables() {
        var tables = document.querySelectorAll('table:not(.ftu-responsive-wrapped):not(.ui-datepicker-calendar)');
        tables.forEach(function (table) {
          if (table.closest('.table-responsive') || table.closest('.dataTables_scrollBody')) {
            return;
          }
          var isHoldingCard = (table.id === 'holdingst' || table.id === 'otherholdingst');
          var wrap = document.createElement('div');
          wrap.className = isHoldingCard 
            ? 'table-responsive ftu-holding-cards-wrap ftu-cards-scroller' 
            : 'table-responsive ftu-table-scroller';
          table.classList.add('ftu-responsive-wrapped');
          table.parentNode.insertBefore(wrap, table);
          wrap.appendChild(table);

          if (isHoldingCard) {
            table.style.setProperty('width', '100%', 'important');
            table.style.setProperty('max-width', '100%', 'important');
            table.style.setProperty('min-width', '0px', 'important');
          }
        });

        var cardTables = document.querySelectorAll('#holdingst, #otherholdingst');
        cardTables.forEach(function (ct) {
          ct.style.setProperty('width', '100%', 'important');
          ct.style.setProperty('max-width', '100%', 'important');
          ct.style.setProperty('min-width', '0px', 'important');
          if (ct.parentElement && ct.parentElement.classList.contains('dataTables_wrapper')) {
            ct.parentElement.style.setProperty('width', '100%', 'important');
            ct.parentElement.style.setProperty('max-width', '100%', 'important');
          }
        });
      }

      $(document).ready(wrapTables);
      $(document).on('draw.dt shown.bs.tab page.dt', function () {
        setTimeout(wrapTables, 50);
      });
    },

    /**
     * 7. TỐI ƯU HÓA BỐ CỤC TRANG CHI TIẾT TÀI LIỆU TRÊN DI ĐỘNG (OPAC DETAIL)
     */
    setupDetailMobileLayout: function () {
      function adjustDetailLayout() {
        var isMobile = window.innerWidth <= 991;
        var path = window.location.pathname;
        if (path.indexOf('opac-detail') !== -1 || document.getElementById('catalogue_detail_biblio')) {
          var $actions = $('#ulactioncontainer');
          var $biblio = $('#catalogue_detail_biblio');
          var $sidebarCol = $('.col-lg-3');
          if ($actions.length && $biblio.length) {
            if (isMobile && !$actions.data('mobile-repositioned')) {
              $actions.insertAfter($biblio).data('mobile-repositioned', 'true');
            } else if (!isMobile && $actions.data('mobile-repositioned') && $sidebarCol.length) {
              $actions.prependTo($sidebarCol).data('mobile-repositioned', 'false');
            }
          }
        }
      }

      $(document).ready(adjustDetailLayout);
      $(window).on('resize orientationchange', adjustDetailLayout);
    }
  };

  // Kích hoạt ngay Engine
  window.FTUViewportEngine = ViewportEngine;
  $(document).ready(function () {
    ViewportEngine.init();
  });

  // Hỗ trợ hàm kích hoạt đăng nhập nhanh từ Dock
  window.triggerMobileLogin = function () {
    var $modalBtn = $('[data-bs-target="#loginModal"], #user-menu, .koha-login-link, #loginmenulink');
    if ($modalBtn.length) {
      $modalBtn.first().click();
    } else {
      window.location.href = '/cgi-bin/koha/opac-user.pl';
    }
  };

})(window.jQuery || window.$);
