<?php
/**
 * @file
 * gsa_config.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function gsa_config_default_rules_configuration() {
  $items = array();
  $items['rules_auto_assign_users_to_group'] = entity_import('rules_config', '{ "rules_auto_assign_users_to_group" : {
      "LABEL" : "Auto-assign users to group",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "php", "rules" ],
      "ON" : [ "user_login" ],
      "DO" : [
        { "php_eval" : { "code" : "gsa_group_autojoin_join_user($account);\\t\\r\\n" } }
      ]
    }
  }');
  return $items;
}
