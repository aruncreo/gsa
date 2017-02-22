<?php

/**
 * Group demographics page
 */
function gsa_charts_group_demographics_page($node) {
  // Load the page_manager plugin
  module_load_include('inc', 'page_manager', 'plugins/tasks/page');
  // Generate the panel page
  if ($page = page_manager_page_execute('demographics_page')) {
    // Set the title
    drupal_set_title(t('Demographics: %group', array('%group' => check_plain($node->title))));
    return $page;
  }
  drupal_not_found();
}
