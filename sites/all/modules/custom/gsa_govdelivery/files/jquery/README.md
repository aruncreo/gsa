### What is this?

  This code presents a jQuery-friendly overlay to be used with present client-specific content to users (e.g. a "get email updates" form).

### Dependencies

  jQuery 1.4.3+ (if client is using a version other than the one included)
  json2 (for cookie parsing in older browsers without native JSON support)


### Installation
  * copy javascripts and stylesheets dirs to target web server
  * make sure overlay content is web-accessible
  * include scripts and CSS on page:

        <link rel='stylesheet' href='stylesheets/colorbox.css'/>
   	<script type='text/javascript' src="https://ajax.googleapis.com/ajax/libs/jquery/1.7.1/jquery.min.js"></script>
    	<script type='text/javascript' src='javascripts/json2.js'></script>
    	<script type='text/javascript' src='javascripts/jquery.colorbox.js'></script>
    	<script type='text/javascript' src='javascripts/govdpopup.js'></script>
         	<script type='text/javascript'>
       		 var overlay = new GD.jquery.SubscribeOverlay({
           		 show: false,
            	href: '../client_popup_code/splash.html'
            	close_text: 'Skip to Content'
        		}).init();
    	</script>

  * initialize overlay with desired options:

         <script type='text/javascript'>
             var overlay = new GD.jquery.SubscribeOverlay({
                 href: '../client_popup_code/splash2.html',
                 close_text: 'skippity doo dah'
             }).init();
         </script>


  available options are:

      - href:               overlay content URL (required or nothing will work)
      - show:               Explicitly set overlay visibility (true will always show it, false will never show it). If this value is omitted, visbility will be based on a cookie check.
      - observe_iframe:     If the overlay is hosted on the same server as the page content, do the following:
      - close_text:         The text that shows up next to the close button. Default is 'skip to site'.
      - width:              Effective overlay content width. Default is 365 (px).
      - height:              Effective overlay content height. Default is 223 (px).    

When the overlay is displayed, the code will automatically do the following:

  * set form focus on input#email_address, e.g. subscribe form in client popup code should look like this:
        
            <form action="https://public.govdelivery.com/accounts/ACCT_CODE/subscribers/qualify">                            
                 <input type="textfield" id="email_address" name="email" value="Enter email address"
                        onfocus="this.value=''"/>
                 <input type="submit" value="Go"/>
             </form>
            
  * propagate keypress events upward to the parent (so Esc still closes the overlay even when you're in the iframe)
  * Observe a.close_link clicks and close the overlay. This means you can make an accessible close link with code like this:

      <a href="#" class="close_link" style="display:none">skip to site</a>

    Defaults to true, but should be false if the overlay is hosted elsewhere. In that case, the form will have to
    set focus itself, and the close link would look like this:

      <a href="#" onclick="parent.$.fn.colorbox.close();return false" style="display:none">skip to site</a>


### Examples

    see index.htm