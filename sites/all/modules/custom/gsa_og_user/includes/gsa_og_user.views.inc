<?php


/**
 * @file
 * Provides support for the Views module.
 */

/**
 * Implements hook_views_plugins().
 */
function gsa_og_user_views_plugins() {
	
  return array(
    'argument default' => array(
      'gsa_og_user' => array(
        'title' => t('Current OG group node id from context'),
        'handler' => 'og_og_user_plugin_argument_default_group_context',
        'parent' => 'views_plugin_argument_default',
		
      ),
    ),
    'access' => array(
      'gsa_og_user' => array(
        'title' => t('OG permission'),
        'handler' => 'og_context_plugin_access_og_perm',
        'uses options' => TRUE,
      ),
    ),
  );
}

class og_og_user_plugin_argument_default_group_context extends views_plugin_argument_default{
	function get_argument() {
    	$return = FALSE;
    	if ($group = og_context()) {
      	  if ($node = gsa_group_page_get_group_node($group)) {
    		return $node->nid;
 		  }
 	   }
     }
	
}