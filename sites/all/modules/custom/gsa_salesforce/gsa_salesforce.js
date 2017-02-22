(function($) {
	  
Drupal.behaviors.gsaSalesforce = {
	
  attach: function (context, settings) {
  	var userMail = '';
  	var userAgency = '';
	
	$("#user-register-form #edit-mail").focusout(function(){
		 userAgency = $('#edit-profile-agency').val();
    	var userAgency = userAgency.replace(/[^a-zA-Z0-9]/ig, "_");
  		var userMail = '';
		userMail = $(this).val();
		userDomainArr = userMail.split('.');
		userDomainArr.reverse();
         $.ajax( {
             url:'/check_valid_email_domain/'+userAgency+'/'+userDomainArr[0],
             success:function(data) {
             	if(data){
					html = '<div class="messages error"><h2 class="element-invisible">Error message</h2><ul><li>';
              		html +=data;
              		html +='</li></ul></div>';
			   		$('#email-domain-validation-msg').html(html);
				}
				else{
					$('#email-domain-validation-msg').html('');
				}
             }
          });
	});
  	
    $("#edit-profile-agency").change(function(){
    	userAgency = $(this).val();
    	var userAgency = userAgency.replace(/[^a-zA-Z0-9]/ig, "_");
  		var userMail = '';
		userMail = $('#user-register-form #edit-mail').val();
		userDomainArr = userMail.split('.');
		userDomainArr.reverse();
         $.ajax( {
             url:'/check_valid_email_domain/'+userAgency+'/'+userDomainArr[0],
             success:function(data) {
             	if(data){
					html = '<div class="messages error"><h2 class="element-invisible">Error message</h2><ul><li>';
              		html +=data;
              		html +='</li></ul></div>';
			   		$('#email-domain-validation-msg').html(html);
				}
				else{
					$('#email-domain-validation-msg').html('');
				}
             }
          });
      });
  }
  
};

})(jQuery);
 

