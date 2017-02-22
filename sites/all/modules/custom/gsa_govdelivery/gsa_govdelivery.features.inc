<?php

/**
 * Implements hook_flag_default_flags().
 */
function gsa_govdelivery_flag_default_flags() {
  $flags = array();
  // Exported flag: "GSA GovDelivery subscription status".
  $flags['gsa_govdelivery_subscription'] = array(
    'content_type' => 'user',
    'title' => 'GSA GovDelivery subscription status',
    'global' => '0',
    'types' => array(),
    'flag_short' => 'flag',
    'flag_long' => '',
    'flag_message' => '',
    'unflag_short' => 'unflag',
    'unflag_long' => '',
    'unflag_message' => '',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => '2',
      ),
      'unflag' => array(
        0 => '2',
      ),
    ),
    'weight' => 0,
    'show_on_form' => 0,
    'access_author' => '',
    'show_on_profile' => 0,
    'access_uid' => '',
    'api_version' => 2,
    'module' => 'gsa_govdelivery',
    'locked' => array(
      0 => 'name',
    ),
  );
  return $flags;

}
