<?php

function og_role_messages_group_settings_form($form, &$form_state, $entity_type, $entity_id) {
  $form = array();

  // Retain hierarchy in $form_state['values']
  $form['#tree'] = TRUE;
  
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  
  // Get the defined messages
  $messages = og_role_messages_get($group);
  
  // Save the gid as a form value so we don't have to retrieve it again.
  $form['gid'] = array(
    '#type' => 'value',
    '#value' => $group->gid,
  );

  $instructions = t('The following messages can be inserted in your group\'s information page. ');
  $instructions .= t('Messages will replace the pseudo-token !token in the body field of the page. You may include HTML.', array('!token' => OG_ROLE_MESSAGES_TOKEN));
  
  $form['instructions'] = array(
    '#markup' => $instructions,
  );

  $form['role_messages']['member'] = array(
    '#type' => 'textarea',
    '#title' => t('Group members'),
    '#default_value' => $messages['member'],
  );
  $form['role_messages']['non-member'] = array(
    '#type' => 'textarea',
    '#title' => t('Non-members, logged into Interact'),
    '#default_value' => $messages['non-member'],
  );
  $form['role_messages']['anonymous'] = array(
    '#type' => 'textarea',
    '#title' => t('Anonymous visitors'),
    '#default_value' => $messages['anonymous'],
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  
  return $form;
}

/**
 * Submit handler for settings form.
 */
function og_role_messages_group_settings_form_submit(&$form, &$form_state) {
  $gid = $form_state['values']['gid'];
  
  og_role_messages_delete($gid);
      
  $settings = array();
  foreach ($form_state['values']['role_messages'] as $key => $value) {
    og_role_messages_create($gid, $key, $value);
  }

  drupal_set_message(t('The role messages have been saved.'));
}

