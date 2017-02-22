<?php
/**
 * @file gsa_map_title.views.inc
 */

/**
* Implements hook_views_plugins_alter().
* @param $plugins
*   Existing plugins
*/
function gsa_map_title_views_plugins_alter(&$plugins) {
  //Overriding the style plugin of leaflet views
  $plugins['style']['leaflet']['handler']='gsa_map_title_plugin_style';
  $plugins['style']['leaflet']['parent']='leaflet_views_plugin_style';
  $plugins['style']['leaflet']['path']='sites/all/modules/custom/gsa_map_title/handler';
}


