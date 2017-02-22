<?php

/**
 * Group autojoin settings form
 */
function gsa_group_autojoin_group_settings_form($form, &$form_state, $entity_type, $entity_id) {
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  
  // Get the groups setting, if one
  $setting = gsa_group_autojoin_get_group_setting($group);
  
  // Add the controls
  $form['autojoin_option'] = array(
    '#type' => 'radios',
    '#title' => t('Select which users should be automatically joined into this group'),
    '#description' => t('Upon successfully registering on this site, the users that match the selected criteria will be automatically enrolled in this group.'),
    '#options' => array(
      GSA_AUTOJOIN_NO_USERS => t('None'),
      GSA_AUTOJOIN_ALL_USERS => t('All users'),
      GSA_AUTOJOIN_GSA_USERS => t('Users with a gsa.gov email address'),
      GSA_AUTOJOIN_GOV_MILL_USERS => t('Users with a *.gov or *.mil email address'),
    ),
    '#default_value' => $setting ? $setting : GSA_AUTOJOIN_NO_USERS,
  );
  $form['#autojoin_group'] = $group;
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  return $form;
}

/**
 * Group autojoin settings form submit handler
 */
function gsa_group_autojoin_group_settings_form_submit(&$form, &$form_state) {
  // Save the setting
  gsa_group_autojoin_save_setting($form['#autojoin_group'], $form_state['values']['autojoin_option']);
  // Set a message
  drupal_set_message(t('The autojoin settings have been saved.'));
}
