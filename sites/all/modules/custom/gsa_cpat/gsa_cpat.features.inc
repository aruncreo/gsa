<?php
/**
 * @file
 * gsa_cpat.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gsa_cpat_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "field_group" && $api == "field_group") {
    return array("version" => "1");
  }
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
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
function gsa_cpat_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function gsa_cpat_flag_default_flags() {
  $flags = array();
  // Exported flag: "Questionable".
  $flags['cpat_questionable'] = array(
    'content_type' => 'node',
    'title' => 'Questionable',
    'global' => '0',
    'types' => array(
      0 => 'gsa_cpat',
    ),
    'flag_short' => 'Flag as questionable',
    'flag_long' => '',
    'flag_message' => 'Flagged as questionable',
    'unflag_short' => 'Unflag as questionable',
    'unflag_long' => '',
    'unflag_message' => 'Unflagged as questionable',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
        1 => '6',
      ),
      'unflag' => array(
        0 => '2',
        1 => '6',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 0,
    'i18n' => 0,
    'module' => 'gsa_cpat',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}

/**
 * Implements hook_node_info().
 */
function gsa_cpat_node_info() {
  $items = array(
    'gsa_cpat' => array(
      'name' => t('CTAT Opportunity'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Subject'),
      'help' => '',
    ),
  );
  return $items;
}
