<?php

/**
 * @file
 *   Overrides of functions found in og_context.module
 * 
 * @see http://drupal.org/node/1781218
 */
 
module_load_include('inc', 'og_features', 'includes/overrides.menu');
 
/**
 * Override of og_context()
 */
function og_features_og_context($group = NULL) {
  global $user;
  $context = &drupal_static(__FUNCTION__, FALSE);

  if (!empty($group)) {
    $context = $group;
  }

  if (empty($context)) {
    // Get context from context handlers.
    if (($context = _og_features_og_context_determine_context()) && $user->uid) {
      // Save the group ID in the authenticated user's session,
      $_SESSION['og_context'] = $context->gid;
    }
  }

  return $context;
}

/**
 * Override of og_context_determine_context()
 */
function _og_features_og_context_determine_context($item = NULL) {
  $context = FALSE;

  // Enable url and node context handlers by default.
  $defaults = array('url' => -5, 'node' => -4);
  if ($enabled_providers = array_keys(variable_get("og_context_negotiation_group_context", $defaults))) {
    if (empty($item)) {
      $item = _og_features_menu_get_item();
    }

    foreach (og_context_negotiation_info() as $name => $provider) {
      if (in_array($name, $enabled_providers)) {
        $invoke = FALSE;
        if (!empty($provider['menu path'])) {
          foreach ($provider['menu path'] as $path) {
            if (strpos($item['path'], $path) === 0) {
              $invoke = TRUE;
              // Path matches, so we can break.
              break;
            }
          }
        }
        else {
          // Context isn't determined by the menu item.
          $invoke = TRUE;
        }

        $gids = array();
        
        // Change the callback, if needed
        if ($provider['callback'] == 'og_context_handler_node') {
          $provider['callback'] = '_og_features_og_context_handler_node';
        }

        if ($invoke && ($gids = call_user_func($provider['callback']))) {
          // Check if one of the group IDs already exists in the session, and if
          // so use it.
          if (!empty($_SESSION['og_context']) && in_array($_SESSION['og_context'], $gids)) {
            $gid = $_SESSION['og_context'];
          }
          else {
            // Grab the first group ID.
            $gid = reset($gids);
          }

          $context = og_load($gid);
          // We found the first context, so we can break.
          break;
        }
      }
    }
  }

  return $context;
}

/**
 * Override of og_context_handler_node()
 */
function _og_features_og_context_handler_node() {
  $node = _og_features_menu_get_object('node');
  if ($node) {
    return _og_features_group_context_handler_entity('node', $node);
  }

  // The path may not be %node, but in fact is a ctools-context, so extract the
  // node from it. We check only the 1st position (e.g. node/%/foo).
  $item = _og_features_menu_get_item();
  if (empty($item['map'][1]) || !is_object($item['map'][1]) || !($item['map'][1] instanceof ctools_context)) {
    return;
  }

  // Check the context is a node type. We check only path similar to node/%/foo
  // and don't traverse over the whole arguments, as it might be a page manager
  // page passing multiple nodes (e.g. some/path/with/%node/%node). Implementing
  // modules wanting to handle the above example, should implement their own
  // context handler.
  $context = clone $item['map'][1];
  if (empty($context->type[0]) || $context->type[0] != 'entity:node') {
    return;
  }
  return _og_features_group_context_handler_entity('node', $context->data);
}

/**
 * Override of _group_context_handler_entity()
 */
function _og_features_group_context_handler_entity($entity_type = 'node', $entity = NULL, $position = 1) {
  $context = array();

  if (empty($entity)) {
    $entity = _og_features_menu_get_object($entity_type, $position);
  }
  if ($entity) {
    // Check if the entity is itself a group.
    list($id) = entity_extract_ids($entity_type, $entity);
    // Only proceed if it really is the entity and we got an id.
    if (isset($id)) {
      if ($group = og_get_group($entity_type, $id)) {
        $context = drupal_map_assoc(array($group->gid));
      }
      elseif ($gids = og_get_entity_groups($entity_type, $entity)) {
        $context = $gids;
      }
    }
  }

  return $context;
}
