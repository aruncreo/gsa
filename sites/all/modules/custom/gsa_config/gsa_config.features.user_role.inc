<?php
/**
 * @file
 * gsa_config.features.user_role.inc
 */

/**
 * Implements hook_user_default_roles().
 */
function gsa_config_user_default_roles() {
  $roles = array();

  // Exported role: analytics user.
  $roles['analytics user'] = array(
    'name' => 'analytics user',
    'weight' => '0',
  );

  // Exported role: community contributor.
  $roles['community contributor'] = array(
    'name' => 'community contributor',
    'weight' => '0',
  );

  // Exported role: community manager.
  $roles['community manager'] = array(
    'name' => 'community manager',
    'weight' => '0',
  );

  // Exported role: content manager.
  $roles['content manager'] = array(
    'name' => 'content manager',
    'weight' => '0',
  );

  // Exported role: site admin.
  $roles['site admin'] = array(
    'name' => 'site admin',
    'weight' => '0',
  );

  // Exported role: site administrator.
  $roles['site administrator'] = array(
    'name' => 'site administrator',
    'weight' => '0',
  );

  // Exported role: user manager.
  $roles['user manager'] = array(
    'name' => 'user manager',
    'weight' => '0',
  );

  return $roles;
}
