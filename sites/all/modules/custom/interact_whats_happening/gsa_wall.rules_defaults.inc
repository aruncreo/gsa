<?php
/**
 * @file
 * gsa_wall.rules_defaults.inc
 */

/**
 * Implements hook_default_rules_configuration().
 */
function gsa_wall_default_rules_configuration() {
  $items = array();
  $items['rules_add_comment'] = entity_import('rules_config', '{ "rules_add_comment" : {
      "LABEL" : "Add Comment",
      "PLUGIN" : "reaction rule",
      "ACTIVE" : false,
      "REQUIRES" : [ "rules", "comment" ],
      "ON" : [ "comment_insert" ],
      "IF" : [
        { "entity_has_field" : { "entity" : [ "comment" ], "field" : "comment_body" } }
      ],
      "DO" : [
        { "mail" : {
            "to" : "[site:mail]",
            "subject" : "New Comment added by [comment:author]",
            "message" : "[comment:body]\\r\\n\\r\\n\\r\\nLink to Comment  [comment:url]\\r\\n",
            "language" : [ "" ]
          }
        }
      ]
    }
  }');
  $items['rules_heartbeat_node_like'] = entity_import('rules_config', '{ "rules_heartbeat_node_like" : {
      "LABEL" : "Log activity when a user likes a node",
      "PLUGIN" : "reaction rule",
      "REQUIRES" : [ "rules", "heartbeat_rules", "flag" ],
      "ON" : [ "flag_flagged_dlike" ],
      "DO" : [
        { "heartbeat_activity_heartbeat_like_node" : {
            "nid" : "[flagged-node:nid]",
            "uid" : "[flagging-user:uid]",
            "message_id" : { "value" : { "heartbeat_like_node" : "heartbeat_like_node" } },
            "!username" : "[flagging-user:link]",
            "!node_title" : "[flagged-node:link]"
          }
        }
      ]
    }
  }');
  return $items;
}
