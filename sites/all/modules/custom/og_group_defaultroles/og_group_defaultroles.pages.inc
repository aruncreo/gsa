<?php

/**
 * Form builder function for settings form.
 *
 * @param $entity_type
 * @param $entity_id
 */
function og_group_defaultroles_group_settings_form($form, &$form_state, $entity_type, $entity_id) {
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  
  // Get the group roles by gid.
  $roles = og_group_defaultroles_get_roles($group->gid);

  // Get all defined conditions.
  $conditions = og_group_defaultroles_get_conditions();

  // Get all saved defaults for this group.
  $defaults = og_group_defaultroles_get_defaults($group->gid);

  // Save the gid as a form value so we don't have to retrieve it again.
  $form['og_group_defaultroles_gid'] = array(
    '#type' => 'value',
    '#value' => $group->gid,
  );

  // Write role checkboxes for each condition.
  foreach ($conditions as $condition => $name) {
    $form['ogdr_condition_' . $condition] = array(
      '#type' => 'checkboxes',
      '#title' => t($name),
      '#options' => $roles,
      '#default_value' => $defaults[$condition],
    );
  }

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit handler for settings form.
 */
function og_group_defaultroles_group_settings_form_submit(&$form, &$form_state) {
  $gid = $form_state['values']['og_group_defaultroles_gid'];
      
  $settings = array();
  foreach ($form_state['values'] as $label => $value) {
    if (strpos($label, 'ogdr_condition_') === 0) {
      $cond = preg_replace('/^ogdr_condition_/', '', $label);
      $settings[] = array('cond' => $cond, 'roles' => $value);
    }
  }
  og_group_defaultroles_save_defaults($gid, $settings);
  drupal_set_message(t('The default user role settings have been saved.'));
}

