<?php

/**
 * Menu callback for Email configuration page
 */
function gsa_event_admin_config($form, &$form_state) {

  // Form field for configuring the 'To' address
  $form['gsa_event_email_capacity_to'] = array(
    '#type' => 'textfield',
    '#description' => 'The "to" address of the GSA Event mail',
    '#title' => 'To',
    '#token_insert' => TRUE,
  	'#default_value' => variable_get('gsa_event_email_capacity_to'),
  );
  
  // Form field for configuring the email subject
  $form['gsa_event_email_capacity_subject'] = array(
    '#type' => 'textfield',
    '#description' => 'The subject of the GSA Event mail',
    '#title' => 'Subject',
    '#token_insert' => TRUE,
  	'#default_value' => variable_get('gsa_event_email_capacity_subject'),
  );
  
  // Form field for configuring the email body
  $form['gsa_event_email_capacity_body'] = array(
    '#type' => 'textarea',
    '#description' => 'The body of the GSA Event mail',
    '#title' => 'Body',
    '#token_insert' => TRUE,
  	'#default_value' => variable_get('gsa_event_email_capacity_body'),
  );

  // Retrieve the tokens required for this form
  $form['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('gsa_event'),
  );
  
  return system_settings_form($form);
}

/**
 * Menu callback for Notification configuration page
 */
function gsa_event_admin_config_notification($form, &$form_state){

  // Form field for configuring the submit button
  $form['gsa_event_notification_capacity_register_button'] = array(
    '#type' => 'textfield',
    '#title' => 'Register button label',
    '#description' => 'Alternate text for the register button if capacity is reached',
    '#token_insert' => TRUE,
	  '#default_value' => variable_get('gsa_event_notification_capacity_register_button'),
  );


  // Form field for configuring the capacity warning
  $form['gsa_event_notification_capacity_warning'] = array(
    '#type' => 'textarea',
    '#title' => 'Event description capacity reached warning message',
    '#description' => 'The warning to be displayed at event description page if capacity is reached',
    '#token_insert' => TRUE,
	  '#default_value' => variable_get('gsa_event_notification_capacity_warning'),
  );

  // Form field for configuring the confirmation message
  $form['gsa_event_notification_capacity_confirmation_message'] = array(
    '#type' => 'textarea',
    '#title' => 'Event Registration confirmation message',
    '#description' => 'The notification to be displayed after the event registration is successful',
    '#token_insert' => TRUE,
	  '#default_value' => variable_get('gsa_event_notification_capacity_confirmation_message'),
  );

  // Retrieve the tokens required for this form
  $form['tokens'] = array(
    '#theme' => 'token_tree',
    '#token_types' => array('gsa_event'),
  );

  return system_settings_form($form);
}

/**
 * Menu callback for Threshold configuration page
 */
function gsa_event_admin_config_threshold($form, &$form_state){

  // Form field for configuring the event capacity threshold value
  $form['gsa_event_threshold'] = array(
    '#type' => 'textfield',
    '#description' => 'Set the percentage threshold value for event capacity',
    '#title' => 'Threshold',
    '#token_insert' => TRUE,
	  '#default_value' => variable_get('gsa_event_threshold'),
  );

	return system_settings_form($form);
}

