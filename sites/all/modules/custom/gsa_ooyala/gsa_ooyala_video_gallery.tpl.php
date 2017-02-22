<?php
/**
 * @file
 * Template file for the theming example text form.
 *
 * Available custom variables:
 * - $text_form: A string containing the pre-rendered form.
 * - $text_form_content: An array of form elements keyed by the element name.
 *
 * The default example below renders the entire form and its form elements in
 * a default order provided by Drupal.
 *
 * Alternatively, you may print each form element in the order you desire,
 * adding any extra html markup you wish to decorate the form like this:
 *
 * <?php print $text_form_content['element_name']; ?>
 *
 * The following snippet will print the contents of the $text_form_content
 * array, hidden in the source of the page, for you to discover the individual
 * element names.
 *
 * <?php print '<!--' . print_r($text_form_content, TRUE) . '-->'; ?>
 */
?>


<div id="<?php print $player_id; ?>" class="ooyala_shared_player">
   <div id="<?php print $player_id; ?>-wrapper" style="padding-left:40px;">
    <script src="//player.ooyala.com/player.js?callback=receiveOoyalaEvent&playerId=<?php print $player_id; ?>-player&width=<?php print $width; ?>&height=<?php print $height; ?>&embedCode=<?php print $first_embed_code; ?>"></script><br/>
    
    <?php if(count($variables['ooyala_data']) == 1){  ?>
      <div style="font-weight: bold;" id="des-<?php print $player_id; ?>-player"><?php echo $first_video_des; ?></div>
    <?php } ?>
  </div>
  <ul class="ooyala_shared_player_items">
 <?php if(count($variables['ooyala_data']) > 1){  ?>
    <?php foreach ($variables['ooyala_data'] as $ooyala_data): ?>
      <li style="list-style:none;" class="ooyala_shared_player_row" data-embed-code="<?php print $ooyala_data['embed_code']; ?>">
      <ul >
      <li style="display: inline-block;"><a  href="#"><?php print theme('image', array('path' =>$ooyala_data['thumb_url'],'alt'=>'no-image','width' => '100px' )); ?></a></li>
      <li style="display: inline-block;height:78px;width:75%;"><a  href="#"><?php echo $ooyala_data['video_title']; ?></a><br/><b><?php echo $ooyala_data['video_des']; ?></b></li>
      </ul>
      
      
      </li>
    <?php endforeach; ?>
    <?php } ?>
  </ul>
</div>



