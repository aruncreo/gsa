<?php

/**
 * Override of og_ui_subscribe() page callback
 */
function gsa_group_bypass_join_callback($entity_type, $etid, $uid = NULL) {
  global $user;
  
  module_load_include('inc', 'og_ui', 'og_ui.pages');
  
  // If anonymous pass back to the original callback
  if (user_is_anonymous()) {
    return og_ui_subscribe($entity_type, $etid, $uid);
  }
  
  // Load the group
  $group = og_get_group($entity_type, $etid);
  
  // If user does not match bypass rules, pass back
  if (!gsa_group_bypass_can_bypass($group)) {
    return og_ui_subscribe($entity_type, $etid, $uid);
  }
  
  // Attempt to load the current user's membership for this group
  $membership = og_get_group_membership($group->gid, 'user', $user->uid);
  
  // Track if we've bypassed the group
  $bypassed = FALSE;
  
  // Check if the user is a member
  if ($membership) {
    // Check if the membership is active
    if ($membership->state == OG_STATE_ACTIVE) {
      drupal_set_message(t('You are already a member of this group.'), 'warning');
    }
    else {
      // Update the membership to be active
      $membership->state = OG_STATE_ACTIVE;
      og_membership_save($membership);
      $bypassed = TRUE;
    }
  }
  else {
    // Enroll the user in the group
    og_group($group->gid, array('entity' => $user));
    $bypassed = TRUE;
  }
  
  // If member was added, set a message and log the action
  if ($bypassed) {
    drupal_set_message(t('You are now a member of this group'));
    watchdog('gsa_group_bypass', '%user bypassed group, %group, membership', array('%user' => $user->name, '%group' => $group->label), WATCHDOG_ERROR);
  }
  
  // Load the group's entity
  $entity = isset($group->entity) ? $group->entity : NULL;
  if (!$entity) {
    $entity = reset(entity_load($entity_type, array($etid)));
  }
  
  // Redirect to the group homepage
  if ($uri = entity_uri($entity_type, $entity)) {
    drupal_goto($uri['path']);
  }
  else {
    drupal_goto('<front>');
  }
}

/**
 * Group form to configure bypass options
 */
function gsa_group_bypass_group_settings_form($form, &$form_state, $entity_type, $entity_id) {
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  
  // Get the groups setting, if one
  $setting = gsa_group_bypass_get_group_setting($group);
  
  // Add the controls
  $form['bypass_option'] = array(
    '#type' => 'radios',
    '#title' => t('Select which users can always join this group'),
    '#description' => t('Users that match the selected criteria will always be able to join this group, regardless of the other group settings.'),
    '#options' => array(
      GSA_BYPASS_NO_USERS => t('None'),
      GSA_BYPASS_ALL_USERS => t('All Users'),
      GSA_BYPASS_GSA_USERS => t('Users with a gsa.gov email address'),
      GSA_BYPASS_GOV_MILL_USERS => t('Users with a *.gov or *.mil email address'),
    ),
    '#required' => TRUE,
    '#default_value' => $setting ? $setting : GSA_BYPASS_NO_USERS,
  );
  $form['#bypass_group'] = $group;
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit handler for the group bypass option form
 */
function gsa_group_bypass_group_settings_form_submit(&$form, &$form_state) {
  // Save the setting
  gsa_group_bypass_save_setting($form['#bypass_group'], $form_state['values']['bypass_option']);
  // Set a message
  drupal_set_message(t('The bypass options have been saved.'));
}
