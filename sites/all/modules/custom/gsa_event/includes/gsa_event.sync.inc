<?php

/**
 * @file
 *   Operations needed for event syncing with Salesforce
 */

/**
 * Perform a time-based sync with Salesforce
 *
 * This will query Salesforce for changes that occurred since
 * the last sync.
 *
 * @param $not_cron
 *   TRUE if this is not being executed during cron, otherwise FALSE.
 */
function gsa_event_sync_period($not_cron = TRUE) {
  $op = t('Periodic event sync (fetch added/updated events)');
  $last = gsa_event_last_sync();
  $now = gsa_event_current_time();
  $operations = array();

  // Check if we've synced once before
  if (!$last) {
    // Perform a full sync instead
    gsa_event_sync_full();
    return;
  }
  
  // Check if it's been more than 30 days
  if (($now - $last) > (30 * 86400)) {
    // Perform a full sync instead
    gsa_event_sync_full();
    return;
  }

  // Check if it's been less than 2 minutes
  if (($now - $last) < 120) {
    // Can't sync this often
    if ($not_cron) {
      drupal_set_message(t('You must wait at least 2 minutes before performing a periodic sync.'), 'warning');
    }
    return;
  }
  
  // Connect to Salesforce
  if (!($sf = gsa_salesforce_connect($op))) {
    return FALSE;
  }
  
  // Determine which items have been added or updated
  try {
    $update_ids = array();
    $sfResult = $sf->client->getUpdated('Campaign', $last, $now);
    
    // If an array is returned, there are multiple
    if (isset($sfResult->ids)) {
      if (is_array($sfResult->ids)) {
        foreach ($sfResult->ids as $id) {
          $update_ids[] = $id;
        }
      }
      // If a string is returned, there is only one
      else if (is_string($sfResult->ids)) {
        $update_ids[] = $sfResult->ids;
      }
    }
    
    // See if we have records to fetch to new data
    if (count($update_ids)) {
      $sfResult = $sf->client->query(gsa_event_select_query() . " WHERE Id IN ('" . implode("', '", $update_ids) . "')");
      
      foreach ($sfResult->records as $record) {
        // Save the record
        $operations[] = array('_gsa_event_batch_sync_operation', array('save', $record));
      }
    }
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op);
    return FALSE;
  }

  // Determine which items have been deleted
  try {
    $sfResult = $sf->client->getDeleted('Campaign', $last, $now);

    // If object is returned, there is only one entry
    if (isset($sfResult->deletedRecords)) {
      if (is_object($sfResult->deletedRecords)) {
        $operations[] = array('_gsa_event_batch_sync_operation', array('delete', $sfResult->deletedRecords));
      }
      // If an array is returned, there are multiple
      else if (is_array($sfResult->deletedRecords)) {
        foreach ($sfResult->deletedRecords as $record) {
          // Delete the record
          $operations[] = array('_gsa_event_batch_sync_operation', array('delete', $record));
        }
      }
    }
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op);
    return FALSE;
  }
  
  // Perform the batch
  _gsa_event_sync_set_batch($operations, $not_cron);
}

/**
 * Perform a full sync with Salesforce
 *
 * This will import every available record as well as
 * delete any records in Drupal that no longer exist
 * in Salesforce
 *
 * @param $not_cron
 *   TRUE if this is not being executed during cron, otherwise FALSE.
 */
function gsa_event_sync_full($not_cron = TRUE) {
  $op = t('Full event sync');
  $operations = array();
  $event_ids = array();
  
  // Connect to Salesforce
  if (!($sf = gsa_salesforce_connect($op))) {
    return FALSE;
  }
  
  try {
    // Fetch records from SFDC
    $sfResult = $sf->client->query(gsa_event_select_query());
    // Iterate each record
    $done = FALSE;
    
    while (!$done) {
      foreach ($sfResult->records as $record) {
        $operations[] = array('_gsa_event_batch_sync_operation', array('save', $record));
      }
      
      // If we're done, exit
      if ($sfResult->done) {
        $done = TRUE;
      }
      else {
        // If not, get the next group of records
        $sfResult = $sf->client->queryMore($sfResult->queryLocator);
      }
    }
  }
  catch (Exception $e) {
    gsa_salesforce_log_exception($e, $op);
    return FALSE;
  }

  // Place all of the saved record Id's into a new array
  foreach ($operations as $operation) {
    $event_ids[] = $operation[1][1]->Id;
  }

  // Determine which records are in our database that are
  // no longer in Salesforce
  if (!empty($event_ids)) {
    $depreciated = db_select('gsa_events')
      ->fields('gsa_events')
      ->condition('sfid', $event_ids, 'NOT IN')
      ->execute()
      ->fetchAll();
      
    foreach ($depreciated AS $item) {
      $item->Id = $item->sfid;
      $operations[] = array('_gsa_event_batch_sync_operation', array('delete', $item));
    }
  }
 
  // Save/delete records via a batch operation
  _gsa_event_sync_set_batch($operations, $not_cron);
}

/**
 * Build and execute a batch operation
 *
 * @param $operations
 *   Batch API operations array
 * @param $cron
 *   If this batch is running during cron
 */
function _gsa_event_sync_set_batch($operations, $not_cron = TRUE) {
  // Build batch operation
  if (!empty($operations)) {
    // Add an initial call to make sure the toolkit is loaded
    array_unshift($operations, array('gsa_event_include_toolkit', array()));
    
    $batch['operations'] = $operations;
    $batch['finished'] = '_gsa_event_log_sync';
    $batch['file'] = drupal_get_path('module', 'gsa_event') . '/gsa_event.sync.inc';
  
    // Execute the batch
    batch_set($batch);

    // If this is for cron
    if (!$not_cron) {
      // We don't want to use the JS UI
      $batch = &batch_get();
      $batch['progressive'] = FALSE;
      batch_process();
    }
  }
  else {
    // We still need to record to time of sync
    _gsa_event_log_sync(TRUE);
  }
}

/**
 * Log the time of the sync
 *
 * @param $success
 *   Passed in via the batch API, if present
 */
function _gsa_event_log_sync($success = NULL) {
  if ($success === TRUE) {
    drupal_set_message(t('Salesforce syncronization was completed successfully.'));
  }
  else if ($success === FALSE) {
    drupal_set_message(t('An error occurred while syncronizing with Salesforce.'), 'error');
  }
  
  variable_set('gsa_event_last_sync', time());
}

/**
 * Return the time of the last sync
 */
function gsa_event_last_sync() {
  $last = variable_get('gsa_event_last_sync', 0);
  return $last ? gsa_event_adjust_time($last) : 0;
}

/**
 * Invoke modules implementing event hooks
 *
 * @param $op
 *   The operation being performed
 * @param $record
 *   The Salesforce record object
 */
function _gsa_event_batch_sync_operation($op, $record) {
  // Needed to handle SObject classes during batch
  gsa_event_include_toolkit();

  // Salesforce thought having the ID field formatted differently was smart
  if (!isset($record->Id)) {
    if (isset($record->id)) {
      $record->Id = $record->id;
    }
    else {
      // No SFID, exit here
      return FALSE;
    }
  }
  
  // Convert record type relationship
  if (isset($record->RecordType)) {
    $record->RecordType = $record->RecordType->Name;
  }
  else {
    $record->RecordType = NULL;
  }

  // Invoke the hooks
  module_invoke_all("gsa_event_{$op}", $record, $record->RecordType);
}

/**
 * Helper function to generate a select query for event records in 
 * Salesforce
 *
 * @param $fields
 *   The fields to select. If omitted, the default fields will be used
 * @param $table
 *   The table to select from. If omitted, Campaign will be used
 * @return
 *   A SELECT statement to be used with SFDC API
 */
function gsa_event_select_query($fields = array(), $table = 'Campaign') {
  // Use the default fields, if needed
  if (empty($fields)) {
    $fields = array(
      'Id',
      'OwnerId',
      'RecordType.name',
      'Name',
      'Type',
      'Description',
      'Teaser__c',
      'Detailed_Description_for_Publication__c',
      'Start_Date_Time__c',
      'End_Date_Time__c',
      'Venue__c',
      'Room__c',
      'Address_1__c',
      'Address_2__c',
      'City__c',
      'State__c',
      'Zip__c',
      'Country__c',
      'Event_Website__c',
      'Event_Hours__c',
      'Business_Line__c',
      'Hotel_Information__c',
      'Category__c',
      'Targeted_Audience__c',
      'Portal_Status__c',
      'Sync_Changes__c',
      'Published_Event_Title__c',
      'Attendance_Type__c',
      'External_Registration_URL__c',
      'Customer_Registration__c',
    );
  
    // Allow other modules to alter the fields
    drupal_alter('gsa_event_default_query_fields', $fields);
  }
  
  // Start building the query
  $query  = "SELECT " . implode(',', $fields);
  
  // Campaign queries use additional fields
  if ($table == 'Campaign') {
    // Default campaign fields
    $campaign_fields = array(
      'Id',
      'Class_Name__c',
      'Name',
      //'Start_Date_Time__c',
      'Start_Date_Time_Hidden__c',
      'Instructor_Name__c',
      'CLP__c',
      'Webinar_Number__c',
    );
    
    // Allow other modules to alter the fields
    drupal_alter('gsa_event_default_campaign_query_fields', $campaign_fields);
    
    // Embedded query for classes
    $query .= ", (SELECT " . implode(',', $campaign_fields) . " FROM CampaignClasses__r)";
  }
  
  // Finish the query
  $query .= " FROM " . $table;

  return $query;
}
