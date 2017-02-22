(function($) {
  $('.comment-like-anchor').live('click', function(e) {
    e.preventDefault();
    var target = $(this).attr('href');
    var clicked_follow_link = this;
    $(this).append('<span class="gsa-wall-flag-throbber">&nbsp;</span>');
    $.ajax({
      url: target,
      dataType: 'json',
      success: function(data) {
        $(clicked_follow_link).html(data.html);
        $(clicked_follow_link).attr('href', data.href);
      }
    });
  });
})(jQuery);