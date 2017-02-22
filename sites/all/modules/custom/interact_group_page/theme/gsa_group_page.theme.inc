<?php

/**
 * Theme a group page menu
 */
function theme_gsa_group_page_group_menu($vars) {
  
  $menu = $vars['menu'];
  $group = $vars['group'];
  $node = $vars['node'];
  $imageDetails = $node->field_group_image;
  $style = 'thumbnail';

  foreach ($vars['menu'] AS $key => $values) {
    $label = '';
    if (is_array($menu[$key])) {
      $label = '<span>'. $menu[$key]['_label'] . '</span>';
      $menu_items['items'][] = $label . theme('item_list', $menu[$key]);
    }
    else {
      $menu_items['items'][] = $values;
    }
  }
  
  foreach ($imageDetails AS $key => $values) {
	$imguri = '';  		
	if (is_array($imageDetails[$key])) {
		$imageURIDetails = $imageDetails[$key];
		foreach ($imageURIDetails AS $keys => $value) {
			if (is_array($imageURIDetails[$keys])) {
				$imguri = preg_replace('#(public|private)://#', '', $imageURIDetails[$keys]['uri']);
			}
		}	      
	}
	else {
		//$menu_items['items'][] = $values;
	}
   }  
    if($imguri!=''){ 

  
  list($width, $height) = getimagesize(image_style_url($style, $imguri));
	$margin=$width+10;
 	return  
	  '<div style="float:left;margin:50px 0 0 30px;background:url('.image_style_url($style, $imguri).') no-repeat;background-position:left center;background-size:100px 75px;"><h1 class="gsa-group-title" style="margin-left:110px;">' . $node->title . '</h1></div>' .
    '<div id="group-sub-menu">' . theme('item_list', $menu_items) . '</div>';
   }
   else{
    return
    '<h1 class="gsa-group-title">' . $node->title . '</h1>' .
    '<div id="group-sub-menu">' . theme('item_list', $menu_items) . '</div>';
    }
}
