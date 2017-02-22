(function($) {
  window.GD = {jquery: {}};
  GD.jquery.SubscribeOverlay = function (opts) {
    var options = $.extend({}, {
      cookie_name: 'govd_splash',
      observe_iframe: true,
      close_text: 'skip to site',
      href: null, //set this to what you want the overlay to render
      show: null,
      transition: 'none',
      form_id: '#govd_subscribe_form', 
      email_address_id: '#govd_email_address', 
      button_id: '#govd_submit', 
      close_selector: '#cboxCloseLink'
    }, opts);
    var self = this;
    var popup = null;
    
    function nextElement(evt, selector){
      if (evt.keyCode == 9) {
        $(selector).attr('tabindex', -1).focus();
        evt.preventDefault();
      }
    }
    
    var onComplete = function () {
      var content = $('#cboxContent');

      content.find(options.close_selector).bind('keydown', function(evt){
        nextElement(evt, options.email_address_id)
      });

      content.find(options.email_address_id).bind('keydown', function(evt){
        nextElement(evt, options.button_id)
      });

      content.find(options.button_id).bind('keydown', function(evt){
        nextElement(evt, options.close_selector);
      });

      content.find(options.close_selector).bind('click', self.deactivate);
      content.find(options.form_id).bind('submit', $.colorbox.close);

    // move tab to beginning of form
    content.attr('tabIndex',-1).css('outline', 'none').focus();
  }
  var isMobile = function() {
    return (/Android|webOS|iPhone|iPad|iPod|BlackBerry/i.test(navigator.userAgent));
  }
  this.init = function initialize() {
    if (options.show !== true) {
      options.show = !this.checkCookie();
    }
    options.show = options.show && !isMobile();
    $(document).ready(function () {
      self.activate();
    });
    return this;
  }
  this.activate = function activate() {
    if (!options.show) return false;
    popup = $.colorbox({
      href: options.href,
      iframe: false,
      transition: options.transition,
      innerWidth: options.width,
      innerHeight: options.height,
      onComplete: options.observe_iframe ? onComplete : null,
      fastIframe: false,
      close: '<a id="cboxCloseLink" href="#" aria-label="This is a popup. Fill out form and click submit or press esc."><span id="cboxCloseIcon"></span>'+options.close_text+'</a>'
    });
  }

  this.deactivate = function deactivate() {
    $.colorbox.close();
    return false;
  }

  this.checkCookie = function checkCookie() {
    var cookie = new GD.Cookie().init({name: options.cookie_name, expires: 90});
    if (cookie.getData('viewed')) {
      return true;
    } else {
      cookie.setData('viewed', true);
      return false;
    }
  }
}

GD.Cookie = function () {
  this.data = {};
  this.options = {expires: 1, domain: "", path: "", secure: false};

  this.init = function (options, data) {
    this.options = $.extend(this.options, options || {});

    var payload = this.retrieve();
    if (payload) {
      this.data = $.parseJSON(payload);
    }
    else {
      this.data = data || {};
    }
    this.store();
    return this;
  }

  this.getData = function (key) {
    return this.data[key];
  }

  this.setData = function (key, value) {
    this.data[key] = value;
    this.store();
  }
  this.removeData = function (key) {
    delete this.data[key];
    this.store();
  }
  this.retrieve = function () {
    var start = document.cookie.indexOf(this.options.name + "=");

    if (start == -1) {
      return null;
    }
    if (this.options.name != document.cookie.substr(start, this.options.name.length)) {
      return null;
    }

    var len = start + this.options.name.length + 1;
    var end = document.cookie.indexOf(';', len);

    if (end == -1) {
      end = document.cookie.length;
    }
    return unescape(document.cookie.substring(len, end));
  }
  this.store = function () {
    var expires = '';

    if (this.options.expires) {
      var today = new Date();
      expires = this.options.expires * 86400000;
      expires = ';expires=' + new Date(today.getTime() + expires);
    }

    document.cookie = this.options.name + '=' + escape(JSON.stringify(this.data)) + this.getOptions() + expires;
  }
  this.erase = function () {
    document.cookie = this.options.name + '=' + this.getOptions() + ';expires=Thu, 01-Jan-1970 00:00:01 GMT';
  }
  this.getOptions = function () {
    return (this.options.path ? ';path=' + this.options.path : '') + (this.options.domain ? ';domain=' + this.options.domain : '') + (this.options.secure ? ';secure' : '');
  }
};
})(jQuery);