<?php

/**
 * @file
 * Main view template.
 *
 * Variables available:
 * - $classes_array: An array of classes determined in
 *   template_preprocess_views_view(). Default classes are:
 *     .view
 *     .view-[css_name]
 *     .view-id-[view_name]
 *     .view-display-id-[display_name]
 *     .view-dom-id-[dom_id]
 * - $classes: A string version of $classes_array for use in the class attribute
 * - $css_name: A css-safe version of the view name.
 * - $css_class: The user-specified classes names, if any
 * - $header: The view header
 * - $footer: The view footer
 * - $rows: The results of the view query, if any
 * - $empty: The empty text to display if the view is empty
 * - $pager: The pager next/prev links to display, if any
 * - $exposed: Exposed widget form/info to display
 * - $feed_icon: Feed icon to display, if any
 * - $more: A link to view more, if any
 *
 * @ingroup views_templates
 */
?>
<div class="<?php print $classes; ?>">
  <?php print render($title_prefix); ?>
  <?php if ($title): ?>
    <?php print $title; ?>
  <?php endif; ?>
  <?php print render($title_suffix); ?>
  <?php if ($exposed): ?>
    <div class="view-filters">
      <?php print $exposed; ?>
    </div>
  <?php endif; ?>
  
  <?php if ($header): ?>
    <?php drupal_add_js('misc/form.js'); ?>
	<?php drupal_add_js('misc/collapse.js'); ?>
	
	<?php drupal_add_js(
		  '$("#mapdiv .fieldset-wrapper").css({ "opacity" : -24.3 });
		 setTimeout(function(){ 
		 $("#mapdiv").addClass("collapsed");
		 $("#mapdiv .fieldset-wrapper").css({ "opacity" : 1 });
		 $("#mapdiv").css({ "border" : "2px groove threedface" });
		 }, 500);
		 
		 '
		  ,array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
		  );
    ?>
	<?php  //To remove the title attribute of leaflet map marker icons
		  drupal_add_js('jQuery(document).ready(function () { $(".leaflet-marker-pane img").removeAttr("title"); });',array('type' => 'inline', 'scope' => 'footer', 'weight' => 5)
		  );
	?>	  
 
	<fieldset id="mapdiv" class="collapsible">
  		<legend style="border: 1px solid #218CBA;border-radius: 3px;"><span class="fieldset-legend">View on map</span></legend>
		<div class="fieldset-wrapper">
      		<?php print $header; ?>
		</div>
	</fieldset>
  <?php endif; ?>
  <?php
  		$path = $_GET['q'];
  		$pathArray = explode('/',$path);
  ?>
  
  <br/>
    <br/>
  <div class="archive-link" style="height: 24px;">
  	
  		<?php if(!isset($pathArray[1])){ ?>
  		<span style="border: 1px solid #218cba;border-radius: 3px;padding:0 4px 0 4px;">
	  	<a class="fieldset-title" href="<?php echo $_GLOBALS['base_url'].'/gsa-training/archive/inperson' ?>">Past Training Sessions</a>
	  	</span>
		<?php }elseif($pathArray[1] == 'virtual'){ ?>
		<span style="border: 1px solid #218cba;border-radius: 3px;padding:0 4px 0 4px;">
	   <a class="fieldset-title" href="<?php echo $_GLOBALS['base_url'].'/gsa-training/archive/virtual' ?>">Past Training Sessions</a>
	   </span>
		<?php } ?>
  	
  </div>



  <?php if ($attachment_before): ?>
    <div class="attachment attachment-before">
      <?php print $attachment_before; ?>
    </div>
  <?php endif; ?>

  <?php if ($rows): ?>
    <div class="view-content">
      <?php print $rows; ?>
    </div>
  <?php elseif ($empty): ?>
    <div class="view-empty">
      <?php print $empty; ?>
    </div>
  <?php endif; ?>

  <?php if ($pager): ?>
    <?php print $pager; ?>
  <?php endif; ?>

  <?php if ($attachment_after): ?>
    <div class="attachment attachment-after">
      <?php print $attachment_after; ?>
    </div>
  <?php endif; ?>

  <?php if ($more): ?>
    <?php print $more; ?>
  <?php endif; ?>

  <?php if ($footer): ?>
    <div class="view-footer">
      <?php print $footer; ?>
    </div>
  <?php endif; ?>

  <?php if ($feed_icon): ?>
    <div class="feed-icon">
      <?php print $feed_icon; ?>
    </div>
  <?php endif; ?>

</div><?php /* class view */ ?>
