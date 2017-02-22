<?php
/**
 * @file
 * gsa_group_page.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gsa_group_page_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gsa_group_page_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function gsa_group_page_flag_default_flags() {
  $flags = array();
  // Exported flag: "Like".
  $flags['like_comments'] = array(
    'content_type' => 'comment',
    'title' => 'Like',
    'global' => '0',
    'types' => array(
      0 => 'comment_node_blog',
      1 => 'comment_node_discussion',
      2 => 'comment_node_document',
    ),
    'flag_short' => 'like ([comment:flag-like-comments-count])',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'unlike ([comment:flag-like-comments-count])',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_comment' => 1,
    'module' => 'gsa_group_page',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}
