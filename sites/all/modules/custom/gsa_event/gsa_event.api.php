<?php

/**
 * Implements hook_gsa_event_save().
 *
 * This module is invoked during a sync operation when a given event
 * is supposed to be saved.
 *
 * @param $record
 *   The Saleforce event record
 * @param $type
 *   The event type, if available, otherwise NULL
 */
function hook_gsa_event_save($record, $type = NULL) {
  
}

/**
 * Implements hook_gsa_event_delete().
 *
 * This module is invoked during a sync operation when a given event
 * is supposed to be deleted.
 *
 * @param $record
 *   The Saleforce event record
 * @param $type
 *   The event type, if available, otherwise NULL
 */
function hook_gsa_event_delete($record, $type = NULL) {
  
}

/**
 * Implements hook_gsa_event_default_query_fields_alter().
 * 
 * Alter the default fields used in Salesforce event select queries
 * 
 * @param &$fields
 *   An array of field names
 */
function hook_gsa_event_default_query_fields_alter(&$fields) {
  
}

/**
 * Implements hook_gsa_event_default_campaign_query_fields_alter().
 * 
 * Alter the default fields used in Salesforce event select queries 
 * for the Campaign table sub-query
 * 
 * @param &$fields
 *   An array of field names
 */
function hook_gsa_event_default_campaign_query_fields_alter(&$fields) {
  
}
