<?php

?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <div class="comment-user-information">
    <!--<span class="user-bubble"><?php print $picture; ?></span>-->
	<!--Here Comment Title Is User Name Which Is Linking To The Start Of Comment List-->
	<?php  $nodeid =$elements['#comment']->nid; ?>
	
    <span class="user-name"><?php print $author; ?></span>
  </div>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
	 
      print render($content);
    ?>
  </div>

  <div class="comment-submitted" style="width:100%">
  
  <div style="float:left">
    Posted <?php print date_format_date(new DateObject($comment->created), 'custom', 'm/d/Y g:i A') ?>
	</div >
	<div style="float:right">
		
		<?php
		$aliaspath=drupal_get_path_alias($GET['q']);
		$paramArray=explode('/',$aliaspath);

		if($paramArray[0]=='groups' || $paramArray[0]=='dashboard' || $paramArray[0]=='group'){
				
				  echo $content['links']['flag']['#links']['flag-like_comments']['title'];
		}
		
			
		?>
		
	</div>
  </div>
 
  <?php if(user_access('post comments')): ?>
  <?php print render($content['links']) ?>
  <?php endif; ?>
</div>
