<?php

/**
 * Form builder for bulk OGUR modify
 */
function gsa_ogdr_modifyroles($form_state, $form, $entity_type, $entity_id) {

  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  

  drupal_set_title(t('Bulk modify roles for !title', array('!title' => $group->label)));

  $role_options = array('' => t('--select--')) + og_group_defaultroles_get_roles($group->gid);
  
  $form = array();
  
  $form['instructions'] = array(
    '#markup' => check_markup('The results of this operation cannot be undone. Please be sure you intend to modify role assignments
     for all selected users before you proceed.'),
  );
  
  $form['user_condition'] = array(
    '#title' =>  t('Selection criteria'),
    '#type' => 'select',
    '#options' => og_group_defaultroles_get_conditions(),
    '#description' => t('Selecting "Default" will apply changes to all existing group members.'),
  );
  
  $form['role'] = array(
    '#title' => t('Role'),
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => $role_options,
  );
  
  $form['operation'] = array(
    '#title' => t('Operation to perform'),
    '#type' => 'radios',
    '#required' => TRUE,
    '#options' => array(
      'add' => t('Add the selected role to each member'),
      'remove' => t('Remove the selected role from each member')
    ),
  );
  
  $form['gid'] = array(
    '#type' => 'hidden',
    '#value' => $group->gid,
  );
  
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Submit'),
  );

  return $form;
  
}

/**
 * Submit handler for bulk OGUR modify
 */
function gsa_ogdr_modifyroles_submit($form, &$form_state) {
  $values = $form_state['values'];
  
  $gid = $form_state['values']['gid'];

  // Get the condition comparison function name
  $user_condition_func = $values['user_condition'];
  
  // Retrieve list of all group users
  $query = db_select('og_membership', 'og');
  $query->condition('og.gid', $values['gid'], '=');
  $query->condition('og.entity_type', 'user', '=');
  $query->fields('og', array('etid'));
  $result = $query->execute();

  // Iterate users and filer by the comparison function, add to batch
  $operations = array();
  foreach ($result->fetchAll() as $row) {
    $account = user_load($row->etid);
    if ($user_condition_func($gid, $account)) {
      $operations[] = array(
        'gsa_ogdr_modifyroles_op',
        array($values['gid'], $account->uid, $values['role'], $values['operation']),
      );
    }
  }
  
  if (count($operations)) {
    batch_set(array(
      'title' => t('Modifying user roles'),
      'operations' => $operations,
    ));
 
    batch_process();
  }
}

