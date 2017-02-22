<?php
/**
 * @file
 * gsa_home_page_view.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gsa_home_page_view_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "context" && $api == "context") {
    return array("version" => "3");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "panels_mini" && $api == "panels_default") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gsa_home_page_view_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function gsa_home_page_view_flag_default_flags() {
  $flags = array();
  // Exported flag: "Featured Blog Flag".
  $flags['featured_blog_flag'] = array(
    'content_type' => 'node',
    'title' => 'Featured Blog Flag',
    'global' => '1',
    'types' => array(
      0 => 'group',
    ),
    'flag_short' => 'Add to Featured Blog Posts',
    'flag_long' => 'Check this box to add this group to have its blogs featured',
    'flag_message' => '',
    'unflag_short' => 'Remove from Featured Blog Posts',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '10',
        1 => '6',
      ),
      'unflag' => array(
        0 => '10',
        1 => '6',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gsa_home_page_view',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  // Exported flag: "Featured Content Flag".
  $flags['featured_content_flag'] = array(
    'content_type' => 'node',
    'title' => 'Featured Content Flag',
    'global' => '1',
    'types' => array(
      0 => 'blog',
    ),
    'flag_short' => 'Mark this content as featured',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'Unmark this content as featured',
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
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gsa_home_page_view',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}
