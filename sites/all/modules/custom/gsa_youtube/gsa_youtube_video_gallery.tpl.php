<style type="text/css">
	.youtube_shared_player iframe{
		margin-left:40px;
	}
	
</style>
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



<div id="<?php print $player_id; ?>" class="youtube_shared_player">

<div id="player"></div>
<div id="player_desc"></div>
  <ul class="youtube_shared_player_items">
 <?php if(count($variables['youtube_data']) > 1){  ?>
    <?php foreach ($variables['youtube_data'] as $youtube_data): ?>
      <li style="list-style:none;" class="youtube_shared_player_row" data-embed-code="<?php print $youtube_data['embed_code']; ?>">
      <div class="youtube_shared_player_row_div">
      <ul>
      <li style="display: inline-block;">

      <a  href="javascript:void(0);"><?php print theme('image', array('path' =>$youtube_data['thumb_url'],'alt'=>'no-image','width' => '100px' )); ?></a>
     
      </li>
      <li style="display: inline-block;height:78px;width:75%;"><a  href="#"><?php echo $youtube_data['video_title']; ?></a><br/><b><?php echo $youtube_data['video_des']; ?></b></li>
      </ul>
       <input type="hidden" class="player_id" value="<?php print $youtube_data['embed_code']; ?>" />
	   <input type="hidden" class="player_desc" value="<?php print $youtube_data['video_des']; ?>" />
      </div>
          
      </li>
    <?php endforeach; ?>
    <?php } ?>
  </ul>
  <input type="hidden" value="<?php print $variables['first_embed_code']; ?>" id="first_player_id"/>
  <input type="hidden" value="<?php print $variables['first_video_des']; ?>" id="first_player_desc"/>
  <input type="hidden" value="<?php print $variables['width']; ?>" id="player_width"/>
  <input type="hidden" value="<?php print $variables['height']; ?>" id="player_height"/>
</div>


<script>
		$('document').ready(function(){
			$('.youtube_shared_player_row_div').click(function(){
				var video_embed_code = $(this).find('.player_id').val()
				player.loadVideoById(video_embed_code,0);
				var video_video_desc = $(this).find('.player_desc').val();
				$('#player_desc').html(video_video_desc);
				
			});	
			
			var first_video_desc = $(this).find('#first_player_desc').val();
			$('#player_desc').html(first_video_desc);
		});

    //Load player api asynchronously.
    var tag = document.createElement('script');
    tag.src = "https://www.youtube.com/iframe_api";
    var firstScriptTag = document.getElementsByTagName('script')[0];
    firstScriptTag.parentNode.insertBefore(tag, firstScriptTag);
    var done = false;
    var player;
    function onYouTubeIframeAPIReady() {
        player = new YT.Player('player', {
          height: $('#player_height').val(),
          width: $('#player_width').val(),
          videoId: $('#first_player_id').val(),
          events: {
            'onReady': onPlayerReady,
            'onStateChange': onPlayerStateChange
          }
        });
    }
	
	
    function onPlayerReady(evt) {
        evt.target.playVideo();
    }
    function onPlayerStateChange(evt) {
        if (evt.data == YT.PlayerState.PLAYING && !done) {
            setTimeout(pauseVideo, 0);
            done = true;
        }
    }
    function pauseVideo() {
    	
        player.pauseVideo();
    }
</script>



