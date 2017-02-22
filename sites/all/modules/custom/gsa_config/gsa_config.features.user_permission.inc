<?php
/**
 * @file
 * gsa_config.features.user_permission.inc
 */

/**
 * Implements hook_user_default_permissions().
 */
function gsa_config_user_default_permissions() {
  $permissions = array();

  // Exported permission: create group_feed content.
  $permissions['create group_feed content'] = array(
    'name' => 'create group_feed content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  // Exported permission: create group_feed_item content.
  $permissions['create group_feed_item content'] = array(
    'name' => 'create group_feed_item content',
    'roles' => array(
      'authenticated user' => 'authenticated user',
    ),
    'module' => 'node',
  );

  return $permissions;
}
