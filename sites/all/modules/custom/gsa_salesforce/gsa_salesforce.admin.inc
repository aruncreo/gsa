<?php

/**
 * Provide an admin setting form to map email domain with agency
 */
function  gsa_salesforce_admin_settings_email_domain($form, &$form_state) {
	//Getting agencies from salesforce
	$agencies = gsa_salesforce_get_picklist('Agency__c', 'Account');
	
	//List of allowed domains
	$allowed_domains = array('gov','mil','us','com','org','net','edu', 'biz');
	
	foreach($agencies as $agency_key => $agency_value){
		$agency_var_key = preg_replace('/[^a-zA-Z0-9]/', '_', $agency_key);
		
		$form[$agency_var_key] = array(
 			'#type' => 'markup',
 			'#markup' => $agency_key,
		);

		foreach($allowed_domains as $domain){
			$form['gsa_salesforce_agency_'.$agency_var_key.'_'.$domain] = array(
    			'#title' => t('.'.$domain),
    			'#type' => 'checkbox',
    			'#default_value' => variable_get('gsa_salesforce_agency_'.$agency_var_key.'_'.$domain,''),
  			);
		}
		
	}
	$form['#theme'] = array('agency_email_domain_setting_form');
	
	return system_settings_form($form);
}

/**
 * Provide an admin settings form
 */
function gsa_salesforce_admin_settings($form, &$form_state) {
  // Test if we can log into Salesforce
  if (!($sf = gsa_salesforce_connect('test'))) {
    drupal_set_message(t('Salesforce connection is currently unavailable. Make sure you have entered your !sf and can successfully connect.',
      array('!sf' => l(t('Salesforce API credentials'), 'admin/config/services/salesforce'))),
      'warning'
    );
  }
  
  // Fetch all available profile fields
  $fields = 
    db_select('profile_field', 'pf')
      ->fields('pf')
      ->orderBy('name')
      ->execute()
      ->fetchAll();
  
  // Format the profile fields into options
  $options = array();
  foreach ($fields as $field) {
    $options[$field->name] = "{$field->title} ({$field->name})";
  }
  
  $form['global_connect'] = array(
    '#type' => 'fieldset',
    '#title' => t('Global Salesforce connection'),
  );
  $form['global_connect']['gsa_salesforce_enabled'] = array(
    '#type' => 'checkbox',
    '#title' => t('Enabled'),
    '#description' => t('Allow the site to connect to Salesforce'),
    '#default_value' => variable_get('gsa_salesforce_enabled', 0),
  );
  
  $form['profile'] = array(
    '#type' => 'fieldset',
    '#title' => t('Profile options'),
    '#collapsible' => FALSE,
    '#description' => t('Salesforce requires the following fields to be supplied when created new entries, such as Leads and Contacts. Please choose which Drupal profile fields will be used for each of the required fields.'),
  );
  $form['profile']['gsa_salesforce_profile_first_name'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_first_name', ''),
    '#title' => t('First name'),
  );
  $form['profile']['gsa_salesforce_profile_last_name'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_last_name', ''),
    '#title' => t('Last name'),
  );
  $form['profile']['gsa_salesforce_profile_location'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_location', ''),
    '#title' => t('Location'),
  );
  $form['profile']['gsa_salesforce_profile_company'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_company', ''),
    '#title' => t('Company'),
  );
  $form['profile']['gsa_salesforce_profile_job_title'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_job_title', ''),
    '#title' => t('Job title'),
  );
  $form['profile']['gsa_salesforce_profile_procurement_role'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_procurement_role', ''),
    '#title' => t('Procurement role'),
  );
  /*
  $form['profile']['gsa_salesforce_profile_agency'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_agency', ''),
    '#title' => t('Agency'),
  );
  */
  $form['profile']['gsa_salesforce_profile_job_category'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_job_category', ''),
    '#title' => t('Job category'),
  );
  $form['profile']['gsa_salesforce_profile_email_optout'] = array(
    '#type' => 'select',
    '#required' => TRUE,
    '#options' => array('' => '') + $options,
    '#default_value' => variable_get('gsa_salesforce_profile_email_optout', ''),
    '#title' => t('Email opt-out'),
  );
  
  $form['objects'] = array(
    '#type' => 'fieldset',
    '#title' => t('Object options'),
    '#collapsible' => FALSE,
  );
  $form['objects']['gsa_salesforce_ownerid'] = array(
    '#type' => 'textfield',
    '#title' => t('Owner ID'),
    '#default_value' => variable_get('gsa_salesforce_ownerid', ''),
    '#description' => t('Supply a Salesforce ID to be set as the Owner ID for newly created lead objects.'),
  );
  
  $form['email_alert'] = array(
    '#type' => 'fieldset',
    '#title' => t('Email alerts'),
    '#collapsible' => FALSE,
  );
  $form['email_alert']['gsa_salesforce_email_alert'] = array(
    '#type' => 'textfield',
    '#title' => t('Email address'),
    '#default_value' => variable_get('gsa_salesforce_email_alert', ''),
    '#description' => t('Optionally supply an email address, or multiple addresses separated by a comma, to receive instant error alerts when Salesforce connections fail.'),
  );

  return system_settings_form($form);
}

/**
 * Provide the group mapping admin form.
 */
function gsa_salesforce_group_mapping_admin_settings_form($form, &$form_state) {
  // Stop if OG is not enabled.
  if (!module_exists('og')) {
    drupal_set_message(t('The Organic Groups module is not enabled.'), 'warning');
    return;
  }

  // Test if we can log into Salesforce
  if (!($sf = gsa_salesforce_connect('test'))) {
    drupal_set_message(t('Salesforce connection is currently unavailable. Make sure you have entered your !sf and can successfully connect.',
      array('!sf' => l(t('Salesforce API credentials'), 'admin/config/services/salesforce'))),
      'warning'
    );
    return;
  }
  
  // Reset the cached picklist of SFDC options.  
  $group_options = gsa_salesforce_get_picklist('Interact_Group_Affiliation__c', 'Lead', TRUE);

  // Fetch groups.
  $gids = og_get_group_ids();
  $groups = og_load_multiple($gids);
  foreach ($groups as $gid => $group) {
    $groups[$gid] = $group->label;
  }
  asort($groups);

  $form['markup'] = array(
    '#markup' => t('Salesforce stores Interact group affiliations for Leads and Contacts. Define how Interact groups are mapped to options in the Salesforce picklist.'),
  );
  
  foreach ($groups as $gid => $label) {
    $form["gsa_salesforce_group_gid{$gid}_sfdc_value"] = array(
      '#type' => 'select',
      '#title' => $label,
      '#options' => array('' => '(do not map)') + $group_options,
      '#default_value' => variable_get("gsa_salesforce_group_gid{$gid}_sfdc_value", ''),
    );
  }
  
  return system_settings_form($form);

}