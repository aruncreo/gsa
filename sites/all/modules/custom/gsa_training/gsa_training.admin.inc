<?php

/**
 * The admin settings form
 */
function gsa_training_admin_settings($form, &$form_state) {  
  // Determine webinar counts
  $webinar_nodes = gsa_training_webinar_query();
  $in_system = count($webinar_nodes);
  $on_server = count(gsa_training_get_webinars());
  $not_used = $on_server - $in_system;
  
  $form['webinar_status'] = array(
    '#type' => 'fieldset',
    '#title' => t('Status report'),
  );
  $form['webinar_status']['about_sync'] = array(
    '#type' => 'item',
    '#markup' => '<strong>' . t('The webinars are imported using the same mechanism for event importing from Salesforce. Use the !sfconfig page to initiate an import.', array('!sfconfig' => l(t('Salesforce configuration'), 'admin/config/gsa_salesforce'))) . '</strong>',
  );
  $form['webinar_status']['link'] = array(
    '#type' => 'item',
    '#markup' => l(t('Click here to view the webinars'), 'gsa-training/webinars'),
  );
  $form['webinar_status']['in_system'] = array(
    '#type' => 'item',
    '#description' => t('Webinars loaded into the system: !count', array('!count' => $in_system)),
  );
  $form['webinar_status']['on_server'] = array(
    '#type' => 'item',
    '#description' => t('Webinars available on the server: !count', array('!count' => $on_server)),
  );
  $form['webinar_status']['not_used'] = array(
    '#type' => 'item',
    '#description' => t('Webinars available that are currently not being used: !count', array('!count' => $not_used)),
  );
  
  $form['webinar_location'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webinar files'),
  );
  $form['webinar_location']['gsa_training_webinar_path'] = array(
    '#type' => 'textfield',
    '#title' => t('Courseware location'),
    '#required' => TRUE,
    '#default_value' => gsa_training_get_webinar_path(),
    '#description' => t('Specify the path to the webinar files relative to the Drupal root.'),
  );
  
  $form['webinar_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webinar settings'),
  );
  $form['webinar_settings']['gsa_training_webinar_alert'] = array(
    '#type' => 'textarea',
    '#title' => t('Alert message'),
    '#default_value' => variable_get('gsa_training_webinar_alert', ''),
    '#description' => t('Display this message on each webinar page.'),
  );
  $form['webinar_settings']['gsa_training_passing_score'] = array(
    '#type' => 'textfield',
    '#title' => t('Passing score'),
    '#required' => TRUE,
    '#default_value' => variable_get('gsa_training_passing_score', 0.7),
    '#description' => t('Specify the minimum passing score. This value must be a decimal between 0.0 and 1.0.'),
  );
  $form['webinar_settings']['gsa_training_enable_salesforce'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enable Salesforce tracking'),
    '#default_value' => variable_get('gsa_training_enable_salesforce', FALSE),
    '#description' => t('If checked, users will be registered for webinar events in Salesforce upon beginning the course. Once completed, their campaign member status will be updated. If a user completed a course before this setting was turned on, their results will not be sent to Salesforce.'),
  );
  $form['webinar_settings']['gsa_training_confirmation_email_template'] = array(
    '#type' => 'textarea',
    '#title' => t('Email confirmation text'),
    '#default_value' => variable_get('gsa_training_confirmation_email_template', ''),
    '#description' => t('Message to send to a logged-in user upon successful completion (passing) of a webinar. Use the placeholder !title to insert the webinar name.'),
  );
    
  $form['webinar_list_page'] = array(
    '#type' => 'fieldset',
    '#title' => t('Webinar list page'),
  );
  
  $footer = variable_get('gsa_training_list_page_footer', array(
  'value' => '',
  'format' => NULL));
  $form['webinar_list_page']['gsa_training_list_page_footer'] = array(
    '#type' => 'text_format',
    '#title' => t('Page footer text'),
    '#default_value' => $footer['value'],
    '#format' => $footer['format'],
    '#description' => t('Displayed below the list of active webinars.'),
  );
    
  return system_settings_form($form);
}

/**
 * Validate the admin settings form
 */
function gsa_training_admin_settings_validate(&$form, &$form_state) {
  // Ensure passing score is a decimal between 0.0 and 1.0
  $passing_score = $form_state['values']['gsa_training_passing_score'];
  if (!is_numeric($passing_score) || $passing_score < 0 || $passing_score > 1) {
    form_set_error('gsa_training_passing_score', t('Passing score must be a decimal between 0.0 and 1.0'));
  }
  else {
    // Format the score like #.#
    $form_state['values']['gsa_training_passing_score'] = str_pad(number_format($passing_score, 1), 3, 0, STR_PAD_LEFT);
  }
}
