<?php
/**
 * @file
 * gsa_ask.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gsa_ask_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "strongarm" && $api == "strongarm") {
    return array("version" => "1");
  }
}

/**
 * Implements hook_views_api().
 */
function gsa_ask_views_api() {
  return array("version" => "3.0");
}

/**
 * Implements hook_node_info().
 */
function gsa_ask_node_info() {
  $items = array(
    'faq' => array(
      'name' => t('FAQ'),
      'base' => 'node_content',
      'description' => '',
      'has_title' => '1',
      'title_label' => t('Question'),
      'help' => '',
    ),
  );
  return $items;
}
