(function($) {
	  
Drupal.behaviors.gsaCPAT = {
	
  attach: function (context, settings) {
  	var res = window.location.pathname.split('/'); 

  	if(res[3] != 'edit'){
		$('#edit-field-cpat-open-date-und-0-value label').append('<span class="required_span" style="color:red;">*</span>');
		$('#edit-field-cpat-close-date-und-0-value label').append('<span class="required_span" style="color:red;">*</span>');
	}
  }
  
};

})(jQuery);
 

