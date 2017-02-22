<?php
/**
 * @file
 * gsa_salesforce.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function gsa_salesforce_default_rules_configuration() {
  $items = array();
  $items['rules_clean_up_expired_accounts'] = entity_import('rules_config', '{ "rules_clean_up_expired_accounts" : {
      "LABEL" : "Clean up expired accounts",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "views_bulk_operations", "rules" ],
      "ON" : [ "cron" ],
      "IF" : [
        { "views_bulk_operations_condition_result_count" : { "view" : "expired_users|default", "minimum" : "1" } }
      ],
      "DO" : [
        { "views_bulk_operations_action_load_list" : {
            "USING" : { "view" : "expired_users|default" },
            "PROVIDE" : { "entity_list" : { "user_list" : "A list of users" } }
          }
        },
        { "LOOP" : {
            "USING" : { "list" : [ "user-list" ] },
            "ITEM" : { "user_id" : "Current user id" },
            "DO" : [ { "entity_delete" : { "data" : [ "user-id" ] } } ]
          }
        }
      ]
    }
  }');
  $items['rules_remove_the_expiration_date_after_first_login'] = entity_import('rules_config', '{ "rules_remove_the_expiration_date_after_first_login" : {
      "LABEL" : "After first login, remove expiration and sync user to Salesforce",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "user_expire", "gsa_salesforce" ],
      "ON" : [ "user_login" ],
      "IF" : [ { "data_is_empty" : { "data" : [ "account:last-access" ] } } ],
      "DO" : [
        { "user_expire_clear" : { "account" : [ "account" ] } },
        { "gsa_salesforce_create_sf_user_callback" : { "account" : [ "account" ] } }
      ]
    }
  }');
  $items['rules_set_an_expiration_date_on_new_user_registrations'] = entity_import('rules_config', '{ "rules_set_an_expiration_date_on_new_user_registrations" : {
      "LABEL" : "Set an expiration date on new user registrations",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "user_expire" ],
      "ON" : [ "user_insert" ],
      "DO" : [
        { "user_expire" : { "account" : [ "account" ], "expiration" : "+3 days" } }
      ]
    }
  }');
  return $items;
}
