<?php
/**
 * @file
 * Provides Rules integration for the GSA Salesforce module.
 */

/**
 * Implements hook_rules_action_info().
 */
function gsa_salesforce_rules_action_info() {
  $actions = array(
    'gsa_salesforce_create_sf_user_callback' => array(
      'label' => t('Creates a new user in Salesforce'),
      'group' => t('User'),
      'parameter' => array(
        'account' => array(
          'type' => 'user',
          'label' => t('User'),
          'save' => TRUE,
        ),
      ),
    ),
  );
  return $actions;
}

function gsa_salesforce_create_sf_user_callback($account) {
	gsa_salesforce_create_sf_user($account);
}
