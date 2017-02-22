<?php

/**
 * Menu callback for event registrations
 * 
 * Either return an error for an invalid or missing event ID,
 * or the registration form
 */

function gsa_event_registration($form, &$form_state) {
  // Get Salesforce ID from URL query
  $sfid = filter_xss($_GET['id']);
  
  // Try to load the event record with the ID
  $event = $sfid ? gsa_event_get_event_by_sfid($sfid) : NULL;
  
  if (!$event) {
    // Return error message for missing or invalid ID
    return array('error' => array(
      '#type' => 'item',
      '#markup' => $sfid ? t('The event you are attempting to register for is either invalid or has expired.') : t('You have not specified an event ID.'),
    )); 
  }
  
  // Make sure the event is still open to registration
  if (!gsa_event_is_open($event)) {
    // Return closed message
    return array('error' => array(
      '#type' => 'item',
      '#markup' => t('Registration for this event is no longer available.'),
    ));
  }
  
  return gsa_event_registration_form($form, $form_state, $event);
}

/**
 * The event registration form
 */
function gsa_event_registration_form($form, &$form_state, $event) {
  global $user;
  
  drupal_set_title(t('Register for !title', array('!title' => check_plain($event->data['Name']))));
  
  if ($user->uid) {
    // Get user's previous form input, if any
    $input = gsa_event_get_registration_input($user);
    
    // Map the user's profile
    $profile = gsa_salesforce_map_profile($user);
    
    // Get the user's Salesforce object reference
    $sfUser = gsa_salesforce_user_sfid_get($user);
  }
  
  // Show event details
  /*
  $form['event_details'] = array(
    '#type' => 'fieldset',
    '#title' => t('Event Details'),
  );
  $form['event_details']['event_title'] = array(
    '#type' => 'item',
    '#markup' => $event->data['Name'],
  );

  $form['event_details']['event_link'] = array(
    '#type' => 'item',
    '#markup' => l(t('View all event details'), 'node/' . $event->nid),
  );
  */
  $form['event_details']['event_sfid'] = array(
    '#type' => 'value',
    '#value' => $event->sfid,
  );
  $form['event_details']['event_nid'] = array(
    '#type' => 'value',
    '#value' => $event->nid,
  );
  $form['event_details']['event_ownerid'] = array(
    '#type' => 'value',
    '#value' => $event->data['OwnerId'],
  );
  
  if (gsa_event_capacity($event->sfid) >= variable_get('gsa_event_threshold', 95)) {
    $form['event_full_warning'] = array(
      '#markup' => t('<div class="messages warning">' . variable_get('gsa_event_notification_capacity_warning', 'This event is currently full.') . '</div>'),
    );
  }
   
  // Show available classes, with option to deselect prior to registration
  if (isset($event->data['CampaignClasses__r']->records)) {

    $form['classes'] = array(
      '#type' => 'fieldset',
      '#title' => t('Available Classes'),
    );
  
    $form['classes']['instructions'] = array(
      '#type' => 'item',
      '#markup' => t('Please deselect the classes you do not wish to attend at this event.'),
    );

    // Get each class and render a checkbox, pre-selected
    $classes_taught = array();
    foreach ($event->data['CampaignClasses__r']->records as $theClass) { 
      $fields = get_object_vars($theClass);

      $classId = $fields['Id'];
      $classes_taught[] = $classId;

      $description = t('Instructor') . ': ' . $fields['Instructor_Name__c'];
      $description .= '<br/>';
      $description .= t('CLP Credits') . ': ' . $fields['CLP__c'];
      $description .= '<br/>';
      $description .= t('Start Time') . ': ' . $fields['Start_Date_Time_Hidden__c'];
      $description .= '<br/>';

      $form['classes'][$classId] = array(
        '#type' => 'checkbox',
        '#title' => $fields['Class_Name__c'],
        '#return_value' => 1,
        '#default_value' => 1,
        '#description' => $description,
      );
    }
  
    // Store the list of classes taught for use by the registration function
    $form['classes']['taught'] = array(
      '#type' => 'value',
      '#value' => serialize($classes_taught),
    );
  }

  // Already have an account?
  if (!$user->uid) {
    $form['account_check'] = array(
      '#type' => 'fieldset',
      '#title' => t('Already have an account?'),
    );
    $form['account_check']['anonymous_message'] = array(
      '#type' => 'item',
      '#markup' => t('Click !link to log in and use your existing account information to register.', 
       //array('!link' => l(t('here'), 'user/login', array('query' => array('destination' => 'node/' . $event->nid))))
       // array('!link' => l(t('here'), 'user/login', array('query' => array('destination' => $_SERVER['REQUEST_URI']))))
        array('!link' => l(t('here'), 'user/login', array('query' => array('destination' =>'' . array_pop(explode('/',$_SERVER['REQUEST_URI']))))))
	 ),
    );
  }

  // Personal information
  $form['personal_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Personal information'),
  );
  $form['personal_information']['FirstName'] = array(
    '#type' => 'textfield',
    '#title' => t('First name'),
    '#default_value' => (isset($profile['FirstName']) && $profile['FirstName']) ? $profile['FirstName'] : '',
    '#disabled' => ($user->uid && isset($profile['FirstName']) && $profile['FirstName']) ? TRUE : FALSE,
    '#required' => TRUE,
    '#maxlength' => 40,
    '#salesforce' => 'FirstName',
  );
  $form['personal_information']['LastName'] = array(
    '#type' => 'textfield',
    '#title' => t('Last name'),
    '#default_value' => (isset($profile['LastName']) && $profile['LastName']) ? $profile['LastName'] : '',
    '#disabled' => ($user->uid && isset($profile['LastName']) && $profile['LastName']) ? TRUE : FALSE,
    '#required' => TRUE,
    '#maxlength' => 80,
    '#salesforce' => 'LastName',
  );
  $form['personal_information']['Email'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#default_value' => $user->uid ? $user->mail : '',
    '#disabled' => $user->uid ? TRUE : FALSE,
    '#required' => TRUE,
    '#maxlength' => 80,
    '#salesforce' => 'Email',
  );
  $form['personal_information']['Phone'] = array(
    '#type' => 'textfield',
    '#title' => t('Phone'),
    '#default_value' => (isset($input['Phone']) && $input['Phone']) ? $input['Phone'] : '',
    '#maxlength' => 20,
    '#salesforce' => 'Phone',
    '#description' => t('Example: 123-456-7890 or 123-456-7890 Ext.123'),
  );
  $form['personal_information']['Address'] = array(
    '#type' => 'textfield',
    '#title' => t('Address'),
    '#default_value' => (isset($input['Address']) && $input['Address']) ? $input['Address'] : '',
    '#salesforce' => 'Street',
  );
  $form['personal_information']['Address_2'] = array(
    '#type' => 'textfield',
    '#title' => t('Address (continued)'),
    '#default_value' => isset($input['Address_2']) ? $input['Address_2'] : '',
  );
  $form['personal_information']['City'] = array(
    '#type' => 'textfield',
    '#title' => t('City'),
    '#default_value' => isset($input['City']) ? $input['City'] : '',
    '#maxlength' => 40,
    '#salesforce' => 'City',
  );
  module_load_include('inc', 'gsa_salesforce', 'includes/gsa_salesforce.locations');
  $states = gsa_salesforce_locations_options();
  $form['personal_information']['State'] = array(
    '#type' => 'select',
    '#title' => t('State'),
    '#options' => $states,
    '#salesforce' => 'State',
  );
  if (isset($input['State']) && isset($states[$input['State']])) {
    $form['personal_information']['State']['#default_value'] = $input['State'];
  }
  else if (isset($profile['State'])) {
    $form['personal_information']['State']['#default_value'] = $profile['State'];
  }
  $form['personal_information']['Zip'] = array(
    '#type' => 'textfield',
    '#title' => t('Zip code'),
    '#default_value' => isset($input['PostalCode']) ? $input['PostalCode'] : '',
    '#maxlength' => 20,
    '#salesforce' => 'PostalCode',
  );
  $form['personal_information']['Country'] = array(
    '#type' => 'textfield',
    '#title' => t('Country'),
    '#default_value' => isset($input['Country']) ? $input['Country'] : '',
    '#maxlength' => 40,
    '#salesforce' => 'Country',
  );
  
  if (!$user->uid) {
    $form['personal_information']['HasOptedOutOfEmail'] = array(
      '#type' => 'checkbox',
      '#title' => t('Do not contact me about GSA offerings'),
      '#description' => t('Do not use my information to better serve me in the future by contacting me about GSA offerings. GSA will never sell or rent your information to anyone. Our privacy policy details our practices on how we use and store personal information.'),
    ); 
  }
  
  $form['personal_information']['special_needs'] = array(
    '#type' => 'textfield',
    '#title' => t('Special needs'),
    '#default_value' => isset($input['special_needs']) ? $input['special_needs'] : '',
    '#maxlength' => 255,
    '#size' => 80,
    '#salesforce' => 'Special_Needs_Option__c',
  );
  
  // Work information
  $form['work_information'] = array(
    '#type' => 'fieldset',
    '#title' => t('Work information'),
    '#disabled' => TRUE,
    '#description' => t('If you are a Federal, State or Local government employee, or with the military, please select your Agency/Branch and then enter your office/department in the Organization field. If you are an Industry, Non-Profit or Association employee, please select "Other - Industry, Non-Profit, Associations."'),
  );
  $form['work_information']['Title'] = array(
    '#type' => 'textfield',
    '#title' => t('Job title'),
    '#default_value' => isset($profile['Title']) ? $profile['Title'] : '',
    '#required' => TRUE,
    '#disabled' => ($user->uid && isset($profile['Title']) && $profile['Title']) ? TRUE : FALSE,
    '#salesforce' => 'Title',
  );  
  // Suppress Agency field if user is an SFDC Contact
  if (!isset($sfUser['type']) || ($sfUser['type'] != 'Contact')) {
    $form['work_information']['Agency__c'] = array(
      '#type' => 'select',
      '#title' => t('Agency'),
      '#default_value' => isset($profile['Agency__c']) ? $profile['Agency__c'] : '',
      '#required' => TRUE,
      '#disabled' => ($user->uid && isset($profile['Agency__c']) && $profile['Agency__c']) ? TRUE : FALSE,
      '#salesforce' => 'Agency__c',
      '#options' => array('' => '') + gsa_salesforce_get_picklist('Agency__c', 'Account'),
    );
  }
  $form['work_information']['Company'] = array(
    '#type' => 'textfield',
    '#title' => t('Office/Company/Organization'),
    '#default_value' => isset($profile['Company']) ? $profile['Company'] : '',
    '#disabled' => ($user->uid && isset($profile['Company']) && $profile['Company']) ? TRUE : FALSE,
    '#required' => TRUE,
    '#maxlength' => 255,
    '#salesforce' => 'Company',
  );
  $form['work_information']['Job_Category__c'] = array(
    '#type' => 'select',
    '#title' => t('Job category'),
    '#default_value' => isset($profile['Job_Category__c']) ? $profile['Job_Category__c'] : '',
    '#disabled' => ($user->uid && isset($profile['Job_Category__c']) && $profile['Job_Category__c']) ? TRUE : FALSE,
    '#required' => TRUE,
    '#salesforce' => 'Job_Category__c',
    '#options' => array('' => '') + gsa_salesforce_get_picklist('Job_Category__c', 'Lead'),
  );
  
  // If logged in, explicity set certain values that the profile handles
  if ($user->uid) {
    $form['personal_information']['Email']['#value'] = $user->mail;
    if (isset($profile['FirstName'])) {
      $form['personal_information']['FirstName']['#value'] = $profile['FirstName'];
    }
    if (isset($profile['LastName'])) {
      $form['personal_information']['LastName']['#value'] = $profile['LastName'];
    }
    if (isset($profile['Agency__c'])) {
      $form['work_information']['Agency__c']['#value'] = $profile['Agency__c'];
    }
    if (isset($profile['Title'])) {
      $form['work_information']['Title']['#value'] = $profile['Title'];
    }
    if (isset($profile['Company'])) {
      $form['work_information']['Company']['#value'] = $profile['Company'];
    }
    if (isset($profile['Job_Category__c'])) {
      $form['work_information']['Job_Category__c']['#value'] = $profile['Job_Category__c'];
    }
  }
  
  // Give profile edit link if user is logged in
  if ($user->uid) {
    $form['work_information']['edit_profile_link'] = array(
      '#type' => 'item',
      '#markup' => t('If this information is incorrect, !link to edit your account.', array('!link' => l(t('click here'), "user/{$user->uid}/edit"))),
    );
  }
  
  // Present attendance type field if event offers the option
  // of attending virtually or in person, otherwise, put the
  // only choice available into a hidden field for the registration.
  if (trim(strtolower($event->data['Attendance_Type__c'])) == 'both') {
    $form['Attendance_Type__c'] = array(
      '#type' => 'radios',
      '#title' => t('Attendance type'),
      '#required' => TRUE,
      '#options' => array(
        'In Person' => t('I will attend this event in person.'),
        'Virtual' => t('I will attend this event virtually.'),
      ),
      '#salesforce' => 'Attendance_Type__c',
    );
  } else if (isset($event->data['Attendance_Type__c'])) {
    $form['Attendance_Type__c'] = array(
      '#type' => 'value',
      '#value' => $event->data['Attendance_Type__c'],
    );
  }
  
  // Create an account
  if (!$user->uid && variable_get('gsa_event_allow_registration', 1)) {
    $form['create_account'] = array(
      '#type' => 'fieldset',
      '#title' => t('Create an account (optional)'),
      '#description' => t('Enter a desired user name and password if you would like to create an account here. Doing so will make future event registrations quicker.'),
    );
    $form['create_account']['user_name'] = array(
      '#type' => 'textfield',
      '#title' => t('User name'),
      '#required' => FALSE,
    );
    if (!variable_get('user_email_verification', TRUE)) {
      $form['create_account']['password'] = array(
        '#type' => 'password_confirm',
        '#title' => t('Choose a password'),
        '#required' => FALSE,
      );
    }
  }
  
  // Placeholders for user's Salesforce Data
  $form['user_salesforce_sfid'] = array(
    '#type' => 'value',
    '#value' => 0,
  );
  $form['user_salesforce_type'] = array(
    '#type' => 'value',
    '#value' => 0,
  );
  
  $form['register'] = array(
    '#type' => 'submit',
    '#value' => t('Register'),
  );
  
  if (gsa_event_capacity($event->sfid) >= variable_get('gsa_event_threshold', 95)) {
    $form['register']['#value'] = t(variable_get('gsa_event_notification_capacity_register_button', 'Register'));
  }
  
  return $form; 
}

/**
 * Validate the event registration form
 */
function gsa_event_registration_validate(&$form, &$form_state) {
  global $user;
  
  if (!$user->uid) {
    // Validate the e-mail address (only if not logged in)
    gsa_event_registration_email_validation($form_state);

    // Validate the account registration data, if any
    if (variable_get('gsa_event_allow_registration', 1)) {
      gsa_event_registration_account_validation($form_state);
    }
  }
  
  // Validate the phone length and format.
  // Regex provided by Salesforce team to ensure Leads will
  // convert to Contacts.
  $regex = "/^\(?([0-9]{3})\)?[-. ]?([0-9]{3})[-. ]?([0-9]{4})(?:\s*(?:#|x\.?|x\#?||X\.?|X\#?|ext\.?|ext\#?|Ext\.?|Ext\#?|EXT\.?|EXT\#?|extension|Extension)\s*(\d+))?$/";
  if ($form_state['values']['Phone'] != '' && 0 == preg_match($regex, $form_state['values']['Phone'])) {
    form_set_error('Phone', t('Please enter a phone number in the format "123-456-7890" or "123-456-7890 Ext.123" '));
  }
}

/**
 * Submit the event registration form
 *
 * @todo Roll back creation of a campaign member if class
 *   registration fails.
 */
function gsa_event_registration_submit(&$form, &$form_state) {
  global $user;
  
  // We need to be able to modify the $user without
  // changing the global variable
  $current_user = clone $user;
  
  // If not logged in,
  if (!$current_user->uid) {
    // If account registration data is provided and valid, create
    // user and possibly log them in
    if (variable_get('gsa_event_allow_registration', 1)) {
      if ($form_state['values']['user_name']) {
        if (!($current_user = gsa_event_registration_create_account($form_state))) {
          // If creating the user failed, just end here
          return; 
        }
      }
    }
  }
  
  // If logged in, save form input for next time
  if ($current_user->uid) {
    gsa_event_registration_save_input($current_user, $form_state);
  }
  
  // Determine the user's Salesforce ID
  $sfUser = gsa_event_registration_get_user_sfid($current_user, $form_state);
  if (!$sfUser) {
    // If no Salesforce data, we must exit here
    form_set_error('', t('Event registration is currently not available at this time. Please check back shortly.<!--no data for user on salesforce--->'));
    return; 
  }
  
  // Get the event object
  $event = gsa_event_get_event_by_sfid($form_state['values']['event_sfid']);
  
  $op = t('Event registration (determine registration status)');
  $debug = array(
    'Event' => $form_state['values']['event_sfid'],
    'User' => $sfUser,
  );

  // Determine the classes offered, and those the user has selected
  $classes = array();
  $classes['selected'] = array();
  $classes['taught'] = unserialize($form_state['values']['taught']);
  foreach ($classes['taught'] as $classId) {
    if (isset($form_state['values'][$classId]) && $form_state['values'][$classId] == 1) {
      $classes['selected'][] = $classId;
    }
  }

  // Connect to Salesforce
  if (!($sf = gsa_salesforce_connect($op, $debug))) {
    return FALSE;
  }

  // Set event name
  $eventName = $event->data['Name'];
  
  // If we've made it thus far, redirect the submission to the event page.
  
  // Check if user is already registered for the event
  if (gsa_event_registration_already_registered($form_state, $sfUser)) {
    $form_state['redirect'] = 'node/' . $form_state['values']['event_nid'];
    form_set_error('Email', t('You have already registered for this event.'));
    return;
  }
  
  // Update their Salesforce record with the form data
  gsa_event_registration_sync_salesforce($form, $form_state, $sfUser);
  
  // Register for the event
  if (!gsa_event_process_campaign_registration($form_state['values']['event_sfid'], $sfUser, $form_state['values'])) {
    $form_state['redirect'] = 'node/' . $form_state['values']['event_nid'];
    drupal_set_message(t('Event registration is currently not available at this time. Please check back shortly.<!--redirect values error form state 
user'.$form_state['values']['event_sfid'].'-'.print_r($sfUser).'-'.print_r($form_state['values']).' -->'), 'warning');
  } 
  else if (!gsa_event_register_classes($form_state['values']['event_sfid'], $sfUser, $classes['selected'])) {
    $form_state['redirect'] = 'node/' . $form_state['values']['event_nid'];
    drupal_set_message(
      t(
        'Interact encountered an error processing your class selections for this event. Please contact !email for assistance.',
        array('!email' => variable_get('site_mail', 'the administrator'))
      ),
      'warning'
    );
  } 
  else {
    watchdog('gsa_event', 'A user has registered for Event ID !sfid', array('!sfid' => $form_state['values']['event_sfid']));
    
    // Retrieve Event ID
    $event_capacity = gsa_event_capacity($form_state['values']['event_sfid']);

    if (isset($event_capacity) && $event_capacity >= variable_get('gsa_event_threshold', 100)){
      
      // Check to see whether the $waitlist already exists for that event
      if ($waitlist = variable_get('gsa_event_waitlist')){

        // Initiate a counter to hold the waitlist position for a user
        $waitlist_counter = 0;

        foreach ($waitlist as $user_waitlist){
          if ($user_waitlist['event_id'] == $form_state['values']['event_sfid']){
            if ($user_waitlist['waitlist_id'] > $waitlist_counter){
              $waitlist_counter = $user_waitlist['waitlist_id'];
            }
          }
        }

        $user_waitlist_id = $waitlist_counter + 1;
        $waitlist[] = array(
          'event_id' => $form_state['values']['event_sfid'],
          'user_id' => $current_user->uid, 
          'waitlist_id' => $user_waitlist_id
        );
        variable_set('gsa_event_waitlist', $waitlist);
        
      } else {
        $waitlist = array(0 => array(
          'event_id' => $form_state['values']['event_sfid'],
          'user_id' => $current_user->uid, 
          'waitlist_id' => 1)
        );
        variable_set('gsa_event_waitlist', $waitlist);
      }
      
      // Initiating default variables that are required for sending an email
      $from = $form_state['values']['Email'];
      $to = token_replace(variable_get('gsa_event_email_capacity_to'), array('gsa_event' => $event));
      $subject = token_replace(variable_get('gsa_event_email_capacity_subject'), array('gsa_event' => $event));
      $message =  token_replace(variable_get('gsa_event_email_capacity_body'), array('gsa_event' => $event));

      // Send email to the event owner
      gsa_event_mail($from, $to, $subject, $message);

      // Displays a message to the user indicating that they've been added to the waitlist
      drupal_set_message(t(token_replace(variable_get('gsa_event_notification_capacity_confirmation_message'), array('gsa_event' => $event))), 'warning');
    }

    // Add query parameters to the redirection page URL for use
    // by the View generating the confirmation page
    if (!isset($classes['selected']) || $classes['selected'] == NULL) {
      $classes['selected'] = array('none');
    }
    $attend_type_arg = '';
    if (isset($form_state['values']['Attendance_Type__c'])) {
      $attend_type_arg = '/' . $form_state['values']['Attendance_Type__c'];
    }
    $form_state['redirect'] = 'event-registration/confirm/' . $form_state['values']['event_sfid'] . '/' . implode('+', $classes['selected']) . $attend_type_arg;
  }
}

/**
 * Save a user's registration form input so that it can 
 * be prepopulated the next time
 * 
 * @param $user
 *   A user object
 * @param $input
 *   The form state
 */
function gsa_event_registration_save_input($user, $form_state) {
  $input = array();
  
  // Skip these items
  $skip = array('Email', 'user_name', 'password', 'op', 'register', 'form_build_id', 'form_token', 'form_id', 'Attendance_Type__c');
  
  // Add form values to new array
  foreach ($form_state['values'] as $key => $value) {
    if (array_search($key, $skip)) {
      continue;
    }
    $input[$key] = $value; 
  }
  
  // Delete the user's old settings
  db_delete('gsa_event_user_input')->condition('uid', $user->uid)->execute();
  
  // Insert the new input
  db_insert('gsa_event_user_input')
    ->fields(array(
      'uid' => $user->uid,
      'data' => serialize($input),
    ))
    ->execute();
}

/**
 * Fetch a user's registration form input for prepopulation
 * 
 * @param $user
 *   A user object
 * @return
 *   An associative array using the form field name as the key, or NULL
 *   if no data exists yet
 */
function gsa_event_get_registration_input($user) {
  $input = 
    db_select('gsa_event_user_input', 'g')
      ->fields('g', array('data'))
      ->condition('uid', $user->uid)
      ->execute()
      ->fetchField();
  
  return $input ? unserialize($input) : NULL; 
}

/**
 * Validate the supplied email address
 */
function gsa_event_registration_email_validation($form_state) {
  // Check for valid format
  if ($error = user_validate_mail($form_state['values']['Email'])) {
    form_set_error('Email', $error);
    return FALSE;
  }
  // Check access rules
  else if (drupal_is_denied('mail', $form_state['values']['Email'])) {
    form_set_error('Email', t('The e-mail address %email has been denied access.', array('%email' => $form_state['values']['Email'])));
    return FALSE;
  }  
  
  return TRUE;
}

/**
 * Validate the account credentials for creating a new account
 * 
 * @param $form_state
 *   The form state
 * @return
 *   TRUE if the user chose to create a new account, and the data is valid,
 *   otherwise FALSE.
 */
function gsa_event_registration_account_validation($form_state) {
  // Check if either user name or password was entered
  if ($form_state['values']['user_name'] || $form_state['values']['password']) {
    // Make sure we have a user name
    if (!($form_state['values']['user_name'])) {
      form_set_error('user_name', t('If you\'re creating an account, both user name and password fields are required.'));
      return FALSE; 
    }
    
    // If needed, make sure we have a password
    if (!variable_get('user_email_verification', TRUE) && !$form_state['values']['password']) {
      form_set_error('password', t('If you\'re creating an account, both user name and password fields are required.'));
      return FALSE;
    }
    
    // Check the user name
    if ($error = user_validate_name($form_state['values']['user_name'])) {
      form_set_error('user_name', $error);
      return FALSE;
    }
    else if (db_select('users', 'u')->fields('u', array('uid'))->where("LOWER(u.name) = LOWER(:name)", array(':name' => $form_state['values']['user_name']))->execute()->fetchField()) {
      form_set_error('user_name', t('The name %name is already taken.', array('%name' => $form_state['values']['user_name'])));
      return FALSE;
    }
    else if (drupal_is_denied('user', $form_state['values']['user_name'])) {
      form_set_error('user_name', t('The name %name has been denied access.', array('%name' => $form_state['values']['user_name'])));
      return FALSE;
    }
      
    return TRUE;
  }  
  
  return FALSE;
}

/**
 * Create a new user based on event registration form input and log 
 * them in
 * 
 * @param $form_state
 *   The form state
 * @return
 *   A user object is successfully created and authenticated,
 *   otherwise FALSE
 */
function gsa_event_registration_create_account($form_state) {
  // Create user data array
  $user_data = array(
    'name' => $form_state['values']['user_name'], 
    'mail' => $form_state['values']['Email'], 
    'pass' => $form_state['values']['password'] ? $form_state['values']['password'] : user_password(),
    'status' => 1
  );
  
  // Fill in user's Drupal profile based on form input
  $map = gsa_salesforce_get_profile_map();
  foreach ($map as $key => $value) {
    // Build the profile field values
    if (isset($form_state['values'][$key])) {
      $user_data[$value['field']] = $form_state['values'][$key];
    }
  }

  // Create new user
  if (!($account = user_save('', $user_data))) {
    form_set_error('', t('Event registration is currently not available at this time. Please check back shortly.<!--cant create new user-->'), 'warning');
    watchdog('gsa_event', 'Error creating new account during event registration', NULL, WATCHDOG_CRITICAL);
    return FALSE;
  }
  
  // Either log them in, or send a welcome email
  if (variable_get('user_email_verification', TRUE)) {
    // Send the welcome email
    drupal_mail('user', 'register_no_approval_required', $account->mail, NULL, array('account' => $account));
    // Provide a message
    drupal_set_message(t('Your password and further instructions have been sent to your e-mail address.'));
  }
  else {
    // Attempt to log the user in
    if (user_authenticate($user_data['name'], $user_data['pass'])) {
      global $user;
      $user = user_load($account->uid);
      user_login_finalize($user_data);
      drupal_set_message(t('Your account has been created. You are now logged in.'));
    }
    else {
      form_set_error('', t('Event registration is currently not available at this time. Please check back shortly.<!--not authenticated user-->'), 'warning');
      watchdog('gsa_event', 'Error authenticating new account during event registration', NULL, WATCHDOG_CRITICAL);
      return FALSE;
    }
  }
  
  return $user;
}

/**
 * Determine the user's Salesforce ID
 * 
 * @param $form_state
 *   The form state
 * @return
 *   An associative array containing the user's identifing Salesforce
 *   data with the keys type and sfid
 */
function gsa_event_registration_get_user_sfid($user, $form_state) {
  $sfUser = '';
  if ($user->uid) {
    // See if logged in user already has one
    $sfUser = gsa_salesforce_user_sfid_get($user); 
  }
  
  // See if we have the user's sfid now
  if (!$sfUser) {
    $data = array();
    
    // Get required fields from map
    $map = gsa_salesforce_get_profile_map();
    
    // Pull required fields from the form
    foreach ($map as $key => $value) {
      $data[$key] = $form_state['values'][$key];
    }
    
    // Fetch/create one based on email address provided
    if ($user->uid) {
      $sfUser = gsa_salesforce_user_sync($data, $user); 
    }
    else {
      // Add the supplied email address
      $data['Email'] = $form_state['values']['Email'];
      
      // Provide defaults for a new lead
      $newData = array(
        'LeadSource' => 'Event',
        'Status' => 'New',
        'Rating' => 'Warm',
        'OwnerId' => $form_state['values']['event_ownerid'],
      );
      $sfUser = gsa_salesforce_user_sync($data, NULL, $newData);
    }
  }
  
  return $sfUser ? $sfUser : NULL;
}

/**
 * Check if the user is already registered for the event
 * 
 * @param $form_state
 *   The form state
 * @param $sfUser
 *   An associative array containing the user's identifing Salesforce
 *   data with the keys type and sfid
 * @return
 *   TRUE if the user is already registered for the given event,
 *   otherwise FALSE
 */
function gsa_event_registration_already_registered($form_state, $sfUser) {
  $op = t('Event registration (determine registration status)');
  $debug = array(
    'Event' => $form_state['values']['event_sfid'],
    'User' => $sfUser,
  );
  
  // Connect to Salesforce
  if (!($sf = gsa_salesforce_connect($op, $debug))) {
    return FALSE;
  }
  
  try {
    // Check user's Salesforce ID against the event registrants
    $sfResult = $sf->client->query("SELECT Id FROM CampaignMember WHERE CampaignId = '" . $form_state['values']['event_sfid'] . "' AND " . $sfUser['type'] . "Id = '" . $sfUser['sfid'] . "'");
    // Check results
    if (count($sfResult->records)) {
      return TRUE; 
    }
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op, $debug);
  }
  
  return FALSE;
}

/**
 * Sync a user's Salesforce record with the information provided
 * on the event registration form
 * 
 * @param $form
 *   The form
 * @param $form_state
 *   The form state
 * @param $sfUser
 *   The user's Salesforce data
 * @return
 *   TRUE if the operation succeeded, otherwise FALSE.
 */
function gsa_event_registration_sync_salesforce($form, $form_state, $sfUser) {
  // Create a Salesforce object based on the form input
  $sfObject = gsa_event_registration_form_to_salesforce($form, $form_state);
  // Remove stray campaign fields to prevent errors
  if (isset($sfObject->Special_Needs_Option__c)) {
    unset($sfObject->Special_Needs_Option__c);
  }
  if (isset($sfObject->Attendance_Type__c)) {
    unset($sfObject->Attendance_Type__c);
  }
  return gsa_salesforce_user_sync($sfObject);
  // @todo: we no longer need to pass in $sfUser
}

/**
 * Register a user for the event
 * 
 * @param $eventId
 *   String, SF Id field for Campaign object
 * @param $sfUser
 *   Object containin user info
 * @param $values
 *   The form state values from the submitted registration form
 * @return
 *   TRUE if the registration process was successful, otherwise FALSE
 */
function gsa_event_process_campaign_registration($eventId, $sfUser, $values) {
  $op = t('Event registration (campaign member)');
  $idType = $sfUser['type'] . "Id";
  
  // Create Salesforce object from the form  
  $sfObject = new stdClass;
  $sfObject->CampaignId = $eventId;
  $sfObject->$idType = $sfUser['sfid'];
  $sfObject->Status = 'Responded/Registered';
  if ($values['special_needs']) {
    $sfObject->Special_Needs_Option__c = $values['special_needs'];
  }
  if ($values['Attendance_Type__c']) {
    $sfObject->Attendance_Type__c = $values['Attendance_Type__c'];
  }

  // Connect to Salesforce
  if (!($sf = gsa_salesforce_connect($op, $sfObject))) {
    return FALSE;
  }
  
  try {
    // Add user as a registrant
    $sfResponse = $sf->client->create(array($sfObject), 'CampaignMember');
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op, $sfObject);
    return FALSE;
  }
  
  return gsa_salesforce_check_response($sfResponse, $op, $sfObject);
}

/**
 * Register a user for classes they selected on the form.
 *
 * In its current implementation, this function actually *deletes*
 * Class_Member__c records for any classes the user deselected on
 * the form. This is beacuse SFDC creates a class member
 * for each class taught when the Campaign Member is created. 
 *
 * @param $eventId
 *   String, SF Id field for Campaign object
 * @param $sfUser
 *   Object containin user info
 * @param $classes
 *   Array containing Ids of classes taught and selected
 *
 * @return
 *   TRUE if the process was successful, otherwise FALSE
 */
function gsa_event_register_classes($eventId, $sfUser, $classes) {

  // Connect to Salesforce
  $op = t('Event registration (connect for class registration)');
  if (!($sf = gsa_salesforce_connect($op))) {
    return FALSE;
  }
  
  // Get the class members for this campaign, save this user's class members
  // in $user_class_member_ids
  $op = t('Event registration (get user class member IDs)');
  try {
    $sfResponse = $sf->client->query("SELECT Id, Classes_Taught__c, Contact__c, Lead__c FROM Class_Member__c  WHERE Campaign__c = '" . $eventId . "'");
    $user_class_member_ids = array();
    foreach ($sfResponse->records as $key => $class_member) {
      if (isset($class_member->Contact__c) && $class_member->Contact__c == $sfUser['sfid']) {
        $user_class_member_ids[$class_member->Classes_Taught__c] = $class_member->Id;
      }
      if (isset($class_member->Lead__c) && $class_member->Lead__c == $sfUser['sfid']) {
        $user_class_member_ids[$class_member->Classes_Taught__c] = $class_member->Id;
      }
    }
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op);
    return FALSE;
  }
    
  // Delete class members for classes the user deselected on the form
  $op = t('Event registration (unregister classes)');
  $delete_ids = array();
  foreach ($user_class_member_ids as $c => $v) {
    if (!in_array($c, $classes)) {
      $delete_ids[] = $user_class_member_ids[$c];
    }
  }

  if (count($delete_ids)) {
    try {
      $sfResponse = $sf->client->delete($delete_ids);
    }
    catch (Exception $e) {
      gsa_salesforce_log_exception($e, $op, $delete_ids);
      return FALSE;
    }
    return gsa_salesforce_check_response($sfResponse, $op, $delete_ids);
  } 
  else {
    return true;
  }
}


/**
 * Fetch values from the submitted registration form and
 * map them to an object using the #salesforce field key
 * specified on the form declaration
 * 
 * @param $form
 *    The form
 * @param $form_state
 *   The form state
 * @return
 *   An object formatted for Salesforce
 */
function gsa_event_registration_form_to_salesforce($form, $form_state) {
  $map = new stdClass;
  
  // Combine address fields
  $form_state['values']['Address'] .= "\n" . $form_state['values']['Address_2'];
  $form_state['values']['Address'] = substr($form_state['values']['Address'], 0, 255);

  foreach ($form_state['values'] as $id => $value) {
    if ($value) {
      $sfField = gsa_event_registration_search_form($form, $id, '#salesforce');
      if ($sfField) {
        $map->$sfField = $value; 
      }
    }
  }

  return $map;
}

/**
 * Helper function to recursively iterate through an array,
 * the registration form, searching for form fields which contain
 * a given $element.
 * 
 * @param $array
 *   An associative array created from a form declaration
 * @param $key
 *   The form field ID
 * @param $element
 *   The form field element to return
 * @return
 *   The value of the $key's $element
 */
function gsa_event_registration_search_form($array, $key, $element = '#salesforce') {
  foreach ($array as $id => $field) {
    if (isset($value) && $value) {
      return $value; 
    }
    else if ($id && ($id == $key)) {
      if (isset($field[$element])) {
        return $field[$element];
      }
    }
    else if (is_array($field)) {
      $value = gsa_event_registration_search_form($field, $key, $element);
    }
  }

  return NULL;
}
