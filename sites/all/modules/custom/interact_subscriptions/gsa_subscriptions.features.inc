<?php
/**
 * @file
 * gsa_subscriptions.features.inc
 */

/**
 * Implements hook_views_api().
 */
function gsa_subscriptions_views_api() {
  return array("api" => "3.0");
}

/**
 * Implements hook_flag_default_flags().
 */
function gsa_subscriptions_flag_default_flags() {
  $flags = array();
  // Exported flag: "Content".
  $flags['gsa_subscribe_node'] = array(
    'content_type' => 'node',
    'title' => 'Content',
    'global' => 0,
    'types' => array(
      0 => 'blog',
      1 => 'discussion',
      2 => 'document',
      3 => 'event',
      4 => 'group',
      5 => 'poll',
      6 => 'wiki',
    ),
    'flag_short' => 'Subscribe',
    'flag_long' => '',
    'flag_message' => 'You are now subscribed to this item.',
    'unflag_short' => 'Unsubscribe',
    'unflag_long' => '',
    'unflag_message' => 'You are no longer subscribed to this item.',
    'unflag_denied_text' => '',
    'link_type' => 'toggle',
    'roles' => array(
      'flag' => array(
        0 => 2,
      ),
      'unflag' => array(
        0 => 2,
      ),
    ),
    'weight' => 0,
    'show_on_form' => 1,
    'access_author' => '',
    'show_on_page' => 1,
    'show_on_teaser' => 1,
    'show_contextual_link' => 1,
    'i18n' => 0,
    'module' => 'gsa_subscriptions',
    'locked' => array(
      0 => 'name',
    ),
    'api_version' => 2,
  );
  return $flags;

}
