<?php
/**
 * @file
 * Functions for the handling of Salesforce fields in the Salesforce Webform
 * Module.
 *
 */
 
/**
 * Output the custom fields specified in the admin section.
 * Deprecated in D7.
 */
function salesforcewebform_load_custom_fields($loadtype) {
  return array();
}


/*
 * Obtain the available fields in Salesforce
 * @param string $form_sfobject_typecode 
 * Salesforce Object Type
 * @return $fields 
 * Array of fields available
 */

function salesforcewebform_available_fields($form_sfobject_typecode) {
  $fields = array(
    //Special Field to block Processing
    0 => '--Do Not Map to Salesforce--',
  );

  //Define Implementation for hook_salesforcewebform_fields
  $fields = array_merge($fields, module_invoke_all('salesforcewebform_fields', $form_sfobject_typecode));

  return $fields;
}


/**
 * Determine the required fields in Salesforce for a given object type.
 * @param string $form_sfobject_Typecode
 * @return $fields
 */
function salesforcewebform_required_fields($form_sfobject_typecode) {

  //Define Implementation for hook_salesforcewebform_fields
  $fields = module_invoke_all('salesforcewebform_required_fields', $form_sfobject_typecode);

  return $fields;
}
