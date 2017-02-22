jQuery(document).ready(function($){

var pathname = window.location.pathname;
var pathArray=pathname.split("/");

if(pathArray[1]=='groups'){
$('.group-context .gs-content > .gs-post, .gs-content > .region-content').css('padding','0 2em 0em');
}


$('.arttabs_primary').parent().css('dislay', 'none');
  if($('.view-gsa-og-content-tracker .views-exposed-form #edit-submit-gsa-og-content-tracker').size()) {
    setTimeout('refreshView()', Drupal.settings.refreshInterval * 1000);
    $('.breadcrumb').remove();
  }
  
   var cur_url= window.location.pathname;
 var url_arr=cur_url.split("/");

 if(url_arr[2]=='discuss' || url_arr[1]=='discuss' )
 {
  
  $(".panels-flexible-region-dashboard_layout-center").css("width", "100%");
 }
  
  
  $('.fancy-link').live('click', function(e) {
    e.preventDefault();
    $(this).parents('li:first').find('.comment-form').find('input:text').focus();
  });
  
  $('.views-field-comment-count').append('<span class="toggle-button">Click to show</span>');
    $('.toggle-button').addClass('toggle-up');
	$('.views-field-comment-count .comment-form-text').css('display','none');
 $('.toggle-button').parents('li').find('.views-field-php-1').slideUp();
  $('.toggle-button').live('click', function(){

  

    if($(this).hasClass('toggle-up')) {
      $(this).removeClass('toggle-up');
      $(this).parents('li:first').find('.views-field-php-1').slideDown();
	  $(this).parents('li:first').find('.views-field-comment-count .comment-form-text').css('display','block');
      $(this).html('Click to hide');
    }
    else {
      $(this).addClass('toggle-up');
      $(this).parents('li:first').find('.views-field-php-1').slideUp();
	  $(this).parents('li:first').find('.views-field-comment-count .comment-form-text').css('display','none');
      $(this).html('Click to show');
    }
  });
  
  
  $('.comment-form input:text').live("keydown", function(e) {
    if(e.keyCode == 13) {
      var data = $(this).parent().serialize();
      var commented_li = $(this).parents('li:first');
      $.ajax({
        url: Drupal.settings.basePath + 'gsa-comment-submit',
        type: "post",
        data: data,
        dataType: "json",
        success: function(jsondata) {
          $(commented_li).find('.views-field-php-1 .field-content').html(jsondata.comment_list);
          $(commented_li).find('.comment-form').prepend('<div class="messages status"><p>Your comment has been submitted. It may require the approval of a group moderator.</p></div>');
          $(commented_li).find('.comment-form input:text').val('');
          setTimeout("jQuery('.comment-form .messages').remove()", 3000);
        }
      });
      e.keyCode = null;
      return false;
    }
  });
  
  relocate_gsa_comment_form_timeout();
});

function refreshViewCommentSubmitted() {
  refreshView();
  jQuery('.comment-form').hide();
}

function refreshView() {
  jQuery('.view-gsa-og-content-tracker .views-exposed-form input.form-submit').trigger('click');
  setTimeout('refreshView()', Drupal.settings.refreshInterval * 1000);
}


function relocate_gsa_comment_form() {
  setTimeout("relocate_gsa_comment_form_timeout()", 100);
}

function relocate_gsa_comment_form_timeout() {
  /*jQuery('.fancy-link').each(function(i) {
    var target_id = $(this).attr('href');
    $(this).parents('li:first').find('.views-field-php-1').append($(target_id));
  });*/
  
  $('.comment-form input:text').watermark("Add a comment");
  
  $('.view-gsa-content-discover.view-display-id-block_1 .view-content').jScrollPane({
    'horizontalGutter': 5,
    'verticalGutter': 5,
    'showArrows': false,
    'enableKeyboardNavigation': false
  });
  
  
  /*$('.jspDrag').hide();
  $('.jspScrollable').mouseenter(function(){
      $(this).find('.jspDrag').stop(true, true).fadeIn('slow');
  });
  $('.jspScrollable').mouseleave(function(){
      $(this).find('.jspDrag').stop(true, true).fadeOut('slow');
  });*/
}