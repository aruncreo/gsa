<?php
/**
 * @file
 * gsa_charts.features.inc
 */

/**
 * Implements hook_ctools_plugin_api().
 */
function gsa_charts_ctools_plugin_api() {
  list($module, $api) = func_get_args();
  if ($module == "page_manager" && $api == "pages_default") {
    return array("version" => "1");
  }
}
