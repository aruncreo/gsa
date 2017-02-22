(function($) {
  
$('.view-id-gsa_og_list.view-display-id-page_1 .views-field-group-group a').addClass('gs-button');
$('.view-id-group_information.view-display-id-block .views-field-group-group a').addClass('gs-button');
    
Drupal.behaviors.gsaGroupPage = {
  attach: function (context, settings) {

    if ($('#group-sub-menu', context).size()) {
      $('body').addClass('gsa-group-page');
    }
    
  }
};

})(jQuery);
 

