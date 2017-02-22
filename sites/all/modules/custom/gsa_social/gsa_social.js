jQuery(document).ajaxStop(function() {
  bindSocialFancy();
});

jQuery(document).ready(function() {
  bindSocialFancy();
});

function refreshViewSocial() {
  setTimeout("bindSocialFancy()", 100);
}

function bindSocialFancy() {
  
  
  
  jQuery('.sharethis-wrapper').each(function() {
    var nid = jQuery(this).parents('li:first').find('a.gsa-social-share-button').attr('nid');
    jQuery(this).attr('id', 'share-div-' + nid);
  });
  
  jQuery('.gsa-social-share-button').fancybox();
  
  /*jQuery('.gsa-social-share-button').fancybox({ 'type' : 'iframe', 'height': 30, 'width' : Drupal.settings.socialFrameWidth });*/
}
