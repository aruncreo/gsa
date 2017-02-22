<?php

/**
 * Admin settings form for BBW
 */
function gsa_bbw_admin_settings() {
  $form = array();
  $form['gsa_bbw_group'] = array(
    '#type' => 'select',
    '#title' => t('BBW group'),
    '#description' => t('The group that is the BBW group.'),
    '#options' => og_all_groups_options(),
    '#default_value' => variable_get('gsa_bbw_group', 0),
  );
  
  // Fetch all published webforms
  $sql = "
    SELECT n.nid, n.title
    FROM {node} n
    WHERE n.type = 'webform'
    AND n.status = 1
  ";
  
  $query = new EntityFieldQuery;
  $results = $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'webform')
  ->propertyCondition('status', 1)
  ->execute();
  
  
  $webforms = array();
  foreach($results['node'] AS $node_record) {
    $node = node_load($node_record->nid);
    $webforms[$node->nid] = $node->title;
  }
  
  $form['gsa_bbw_webform'] = array(
    '#type' => 'select',
    '#title' => t('BBW webform'),
    '#description' => t('The webform that must be completed before joining the BBW group.'),
    '#options' => $webforms,
    '#default_value' => variable_get('gsa_bbw_webform', 0),
  );
  
  $form['gsa_bbw_delete_webform'] = array(
    '#type' => 'checkbox',
    '#title' => t('Delete webform submissions when member leaves group'),
    '#description' => t('If selected, a user\'s webform submission will be deleted when they leave the group.'),
    '#default_value' => variable_get('gsa_bbw_delete_webform', 0),
  );
  
  return system_settings_form($form);
}
