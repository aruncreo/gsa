<?php

/**
 * Group feature selection form
 */
function og_features_feature_form($form, &$form_state, $entity_type, $entity_id) {
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);

  // Fetch the og features registry
  $registry = og_features_get_registry();

  // Iterate all the available features to provide a toggle switch
  foreach ($registry as $key => $feature) {
    // Make sure this feature can be toggled by this group
    if (!og_features_feature_can_toggle($group, $key)) {
      continue;  
    }
    
    $form["feature-{$key}"]["name-{$key}"] = array(
      '#type' => 'item',
      '#markup' => $feature->name,
    );
    $form["feature-{$key}"]["description-{$key}"] = array(
      '#type' => 'item',
      '#markup' => $feature->description,
    );
    $form["feature-{$key}"]["toggle-{$key}"] = array(
      '#type' => 'checkbox',
      '#default_value' => isset($group->features_disabled[$key]) ? 0 : 1,
    );
  }

  // Store the group
  $form['#group'] = $group;
  
  // Submit button
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit the group features form
 */
function og_features_feature_form_submit(&$form, &$form_state) {
  // Extract the group
  $group = $form['#group'];
  
  // Collect the disabled features
  $features = array();
  foreach ($form_state['values'] as $key => $value) {
    if (substr($key, 0, 7) == 'toggle-') {
      $feature = substr($key, 7);
      $features[$feature] = $value;
    }
  }
  
  // Save the new settings
  og_features_save_feature_settings($group, $features);
  
  // Alert other modules about the change
  module_invoke_all('og_features_toggle', $group, $features);
  
  // Set a message
  drupal_set_message(t('Your settings have been saved successfully'));
}
