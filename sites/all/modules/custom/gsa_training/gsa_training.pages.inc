<?php

/**
 * Javascript callback to retrieve a user's course data
 */
function gsa_training_js_get_data() {
  global $user;
  
  // Fetch webinar ID
  $wid = $_GET['wid'];
  
  // Validate the webinar ID requested
  if (!$wid || !is_numeric($wid) || !($webinar = gsa_training_webinar_query(array('wid' => $wid)))) {
    return array('data' => NULL, 'success' => FALSE);
  }
  
  // Fetch user data for the webinar
  if ($user->uid) {
    $record = gsa_training_get_user_course_data($wid, $user);
    
    $init = gsa_training_initialize_course_record($record, $webinar, $user);
    if (!$init) {
      return array('data' => NULL, 'success' => FALSE);
    }
  }
  
  return array(
    'data' => empty($record->data) ? FALSE : $record->data,
    'success' => TRUE,
    'authenticated' => ($user->uid ? TRUE : FALSE)
  );
}

/**
 * Javascript callback to save a user's course data
 */
function gsa_training_js_save_data() {
  global $user;
  
  // Permissions are checked but we need to make sure
  // that only authenticated users can save data
  if (!$user->uid) {
    return array('success' => FALSE, 'response' => t('Unauthenticated'));
  }
  
  // Build the data array passed by JS
  $data = array();
  foreach ($_POST as $key => $value) {
    // Only capture the data that we want
    switch ($key) {
      case 'wid':
      case 'suspend_data':
      case 'completion_status':
      case 'location':
      case 'success_status':
      case 'scaled_score':
        $data[$key] = filter_xss($value);
    }
  }
  
  // Make sure we were given at least some data
  if (empty($data)) {
    return array('success' => FALSE, 'response' => t('Missing data'));
  }

  // Make sure we have a webinar ID that is valid
  if (!$data['wid'] || !($webinar = gsa_training_webinar_query(array('wid' => $data['wid'])))) {
    return array('success' => FALSE, 'response' => t('Invalid webinar ID'));
  }
  
  // Check the course progress
  gsa_training_check_progress($webinar, $data, $user);
  
  // Save the data
  $result = gsa_training_save_user_course_data($data['wid'], $data, $user);
  
  return array('success' => $result ? TRUE : FALSE);
}
