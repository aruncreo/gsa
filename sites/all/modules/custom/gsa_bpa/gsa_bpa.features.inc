<?php

/**
 * Implementation of hook_ctools_plugin_api().
 */
function gsa_bpa_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "feeds" && $api == "feeds_importer_default") {
    return array("version" => 1);
  }
  elseif ($module == "strongarm" && $api == "strongarm") {
    return array("version" => 1);
  }
}

/**
 * Implementation of hook_node_info().
 */
function gsa_bpa_node_info() {
  $items = array(
    'bpa_listing' => array(
      'name' => t('BPA Listing'),
      'module' => 'features',
      'description' => t('BPA data uploaded as CSV files and displayed in tabular format.'),
      'has_title' => '1',
      'title_label' => t('BPA Number'),
      'has_body' => '0',
      'body_label' => '',
      'min_word_count' => '0',
      'help' => '',
    ),
  );
  return $items;
}

/**
 * Implementation of hook_views_api().
 */
function gsa_bpa_views_api() {
  return array(
    'api' => '2',
  );
}
