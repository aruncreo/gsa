/**
 * Suppress quoted comments in "My Content" heartbeat stream
 */
(function ($) {
$(document).ready(function() {

  $('.view-gsa-my-content-notifications blockquote').css('display','none');
  
  $('.view-gsa-my-content-notifications .views-field-message .field-content').each( function() {
    $(this).html($(this).html().replace('</a>:', '</a>'));
  });

});
})(jQuery);