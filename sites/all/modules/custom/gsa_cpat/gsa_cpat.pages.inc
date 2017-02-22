<?php

/**
 * Authentication form to join the CPAT group
 */
function gsa_cpat_group_authentication_form($form, &$form_state) {
  global $user;
  
  // Load the CPAT group
  if (!($cpat = gsa_cpat_get_cpat_group())) {
    drupal_set_message(t('The CTAT group is not yet configured.'), 'error');
    drupal_goto('<front>');
  }
  
  // Determine the CPAT url
  $uri = entity_uri($cpat->entity_type, $cpat->entity);
  $cpat_url = $uri['path'];
  
  // See if the current user is already a member
  if (og_is_member($cpat->gid)) {
    // Set a message
    drupal_set_message(t('You are already a member of this group.'), 'notice');
    // Redirect to the group
    drupal_goto($cpat_url);
  }
  
  // Display a warning if the authentication system demo mode is enabled
  if (variable_get('gsa_cpat_authentication_demo_mode', 0)) {
    drupal_set_message(t('The CTAT authentication system is running in demo mode.'), 'warning');
  }

  $form['description'] = array(
    '#type' => 'item',
    '#markup' => check_plain(variable_get('gsa_cpat_authentication_instructions', 'Please provide the requested information to join the CTAT group.')),
  );
  $form['contract_number'] = array(
    '#type' => 'textfield',
    '#title' => t('Contract number'),
    '#required' => TRUE,
  );
  $form['password'] = array(
    '#type' => 'password',
    '#title' => t('VSC Password'),
    '#required' => TRUE,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Authenticate'),
    '#suffix' => l(t('Cancel'), $cpat_url),
  );
  $form['#cpat_url'] = $cpat_url;
  $form['#cpat'] = $cpat;
  return $form;
}

/**
 * Validate the CPAT group authentication
 */
function gsa_cpat_group_authentication_form_validate(&$form, &$form_state) {
  // Protection against the case that the cpat group was deleted before
  // this form was submitted
  if (!($cpat = gsa_cpat_get_cpat_group()) || ($cpat->gid != $form['#cpat']->gid)) {
    form_set_error('', t('An error occurred. Please try again later.'));
    // Stop the validation at this point
    return;
  }

  // External authentication
  $contract = $form_state['values']['contract_number'];
  $password = $form_state['values']['password'];
  if ($contract && $password) {
    switch (gsa_cpat_authenticate($contract, $password)) {
      case GSA_CPAT_AUTHENTICATION_SUCCESS:
        break;
    
      case GSA_CPAT_AUTHENTICATION_FAILURE:
        form_set_error('', t('Authentication failed. Please recheck the information you have provided and try again.'));
        break;
        
      case GSA_CPAT_AUTHENTICATION_ERROR:
        form_set_error('', t('An error occurred validating your information. Please try again later.'));
        break;
    }
  }
}

/**
 * Submit handler for the CPAT group authentication
 */
function gsa_cpat_group_authentication_form_submit(&$form, &$form_state) {  
  // If we've made it here, the user is not yet a member, but has
  // authenticated via the external authentication and can now be joined
  // into the group
  $cpat = $form['#cpat'];
  og_group($cpat->gid);
  drupal_set_message(t('You have successfully joined the group.'));
  drupal_goto($form['#cpat_url']);
}

/**
 * CPAT node renewal form
 */
function gsa_cpat_renew_form($form, &$form_state, $node) {
  $renewed = $node->gsa_cpat_renewed;
  $expires = $renewed + (variable_get('gsa_cpat_expiration_days', 0) * 86400);
  
  // Set the title
  drupal_set_title(t('Renew: %title', array('%title' => check_plain($node->title))));

  $form['message'] = array(
    '#type' => 'item',
    '#markup' => t('This post was last renewed at %renewed, and is set to expire at %expires.', array('%renewed' => format_date($renewed), '%expires' => format_date($expires))),
  );
  $form['renew'] = array(
    '#type' => 'submit',
    '#value' => t('Renew this post'),
    '#suffix' => l(t('Cancel'), "node/{$node->nid}"),
  );
  $form['#node'] = $node;
  return $form;
}

/**
 * CPAT node renewal form submission
 */
function gsa_cpat_renew_form_submit(&$form, &$form_state) {
  // Renew the post
  gsa_cpat_renew_post($form['#node']->nid);
  
  // Set a message
  drupal_set_message(t('%title has been successfully been renewed.', array('%title' => $form['#node']->title)));
  
  // Redirect back to the node
  drupal_goto('node/' . $form['#node']->nid);
}

/**
 * CPAT contact form
 */
function gsa_cpat_contact_form($form, &$form_state, $node) {
  global $user;

  $form['name'] = array(
    '#type' => 'textfield',
    '#title' => t('Name'),
    '#required' => TRUE,
  );
  $form['email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address where you wish to be contacted'),
    '#required' => TRUE,
    '#default_value' => $user->mail
  );
  $form['message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message'),
    '#required' => TRUE,
    '#rows' => 10,
  );
  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Send'),
  );
  $form['#node'] = $node;
  return $form;
}

/**
 * CPAT contact form validation handler
 */
function gsa_cpat_contact_form_validate(&$form, &$form_state) {
  // Filter name and make sure we still have a value
  $form_state['values']['name'] = filter_xss($form_state['values']['name']);
  if (!$form_state['values']['name']) {
    form_set_error('name', t('Enter a valid value for your name.'));
  }
  
  // Check that email address is valid
  if (!valid_email_address($form_state['values']['email'])) {
    form_set_error('email', t('Enter a valid email address.'));
  }
}

/**
 * CPAT contact form submit handler
 */
function gsa_cpat_contact_form_submit(&$form, &$form_state) {
  global $user;
  
  $node = $form['#node'];
  
  // Insert the message
  $message = new stdClass;
  $message->nid = $node->nid;
  $message->sender_uid = $user->uid;
  $message->sender_mail = $form_state['values']['email'];
  $message->sender_name = $form_state['values']['name'];
  $message->timestamp = time();
  $message->reviewed = 0;
  $message->message = check_plain($form_state['values']['message']);
  drupal_write_record('gsa_cpat_message', $message);
  
  // See if we should notify the user via email
  if ($email = _gsa_cpat_contact_notification_address($node)) {
    drupal_mail(
      'gsa_cpat',
      'contact_notification',
      $email,
      user_preferred_language($user),
      array(
        'node' => $node,
        'mid' => $message->mid,
      )
    );
  }
  
  // Log the action
  watchdog('CTAT', 'CTAT Contact form submitted for %title', array('%title' => check_plain($node->title))); 
  
  // Confirmation message
  drupal_set_message(t('Your message has been submitted.'));
  
  // Redirect
  $form['#redirect'] = 'node/' . $node->nid;
}

/**
 * View a CPAT message
 */
function gsa_cpat_message_page($node, $message) {
  return theme('gsa_cpat_message', array('node' => $node, 'message' => $message)); 
}
