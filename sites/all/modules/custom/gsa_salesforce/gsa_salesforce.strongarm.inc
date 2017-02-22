<?php
/**
 * @file
 * gsa_salesforce.strongarm.inc
 */

/**
 * Implements hook_strongarm().
 */
function gsa_salesforce_strongarm() {
  $export = array();

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_ownerid';
  $strongarm->value = '00530000003M1S2';
  $export['gsa_salesforce_ownerid'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_agency';
  $strongarm->value = 'profile_agency';
  $export['gsa_salesforce_profile_agency'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_company';
  $strongarm->value = 'profile_organization';
  $export['gsa_salesforce_profile_company'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_email_optout';
  $strongarm->value = 'profile_email_optout';
  $export['gsa_salesforce_profile_email_optout'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_first_name';
  $strongarm->value = 'profile_name';
  $export['gsa_salesforce_profile_first_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_job_category';
  $strongarm->value = 'profile_job_category';
  $export['gsa_salesforce_profile_job_category'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_job_title';
  $strongarm->value = 'profile_job';
  $export['gsa_salesforce_profile_job_title'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_last_name';
  $strongarm->value = 'profile_last_name';
  $export['gsa_salesforce_profile_last_name'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_location';
  $strongarm->value = 'profile_location';
  $export['gsa_salesforce_profile_location'] = $strongarm;

  $strongarm = new stdClass();
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'gsa_salesforce_profile_procurement_role';
  $strongarm->value = 'profile_procurement_role';
  $export['gsa_salesforce_profile_procurement_role'] = $strongarm;

  return $export;
}
