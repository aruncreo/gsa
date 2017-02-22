<?php

/**
 * Implements hook_views_data().
 */
function gsa_subscriptions_views_data() {
  $data = array();
  
  $data['gsa_subscriptions_notifications']['table']['group'] = t('GSA Subscriptions');
  
  $data['gsa_subscriptions_notifications']['table']['base'] = array(
    'field' => 'snid',
    'title' => t('Subscription notification events'),
  );
  
  $data['gsa_subscriptions_notifications']['table']['join'] = array(
    'node' => array(
      'left_field' => 'nid',
      'field' => 'nid',
    ),
  );
  
  $data['gsa_subscriptions_notifications']['snid'] = array(
    'title' => t('Notification ID'),
    'help' => t('The unique ID of the notification'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  $data['gsa_subscriptions_notifications']['uid'] = array(
    'title' => t('User ID'),
    'help' => t('The user ID of the subscriber'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_numeric',
    ),
    'argument' => array(
      'argument' => 'views_handler_argument_numeric',
    ),
  );
  
  $data['gsa_subscriptions_notifications']['nid'] = array(
    'title' => t('Node ID'),
    'help' => t('The node ID of the content'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'relationship' => array(
      'base' => 'node',
      'base field' => 'nid',
      'handler' => 'views_handler_relationship',
    ),
  );
  
  $data['gsa_subscriptions_notifications']['action'] = array(
    'title' => t('Content action'),
    'help' => t('The content-related action (new, update, comment, etc.)'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_string',
    ),
  );
  
  $data['gsa_subscriptions_notifications']['timestamp'] = array(
    'title' => t('Time'),
    'help' => t('The time the action occurred'),
    'field' => array(
      'handler' => 'views_handler_field_date',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort_date',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );
  
  return $data;
}

/**
 * Implements hook_views_pre_render().
 */
function gsa_subscriptions_views_pre_render(&$view) {
  switch ($view->name) {

    // Rewrite the "action" in the subscription notifications view
    case 'gsa_my_subscription_events':
      foreach ($view->result as $row) {
        if ($row->gsa_subscriptions_notifications_action == 'comment') {
          $row->gsa_subscriptions_notifications_action = 'new comment in';
        }
      }
      break;

    // Show only other users' activity in the content notifications view
    case 'gsa_my_content_notifications':
      $path = drupal_get_path('module', 'gsa_subscriptions');
      drupal_add_js($path. '/js/gsa_subscriptions.js');
      foreach ($view->result as $key => $row) {
        if ($row->heartbeat_activity_uid == $view->args[0]) {
          unset($view->result[$key]);
        }
      }
      break;

  }
}