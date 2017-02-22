<?php
/**
 * @file
 * Provide views data and handlers
 */

/**
 * Implementation of hook_views_data()
 */
function gsa_cpat_views_data() {
  // ----------------------------------------------------------------
  // gsa_cpat_message table

  $data['gsa_cpat_message']['table']['group']  = t('CTAT messages');

  // Advertise this table as a possible base table
  $data['gsa_cpat_message']['table']['base'] = array(
    'field' => 'mid',
    'title' => t('CTAT messages'),
    'help' => t('Messages submitted for CTAT nodes.'),
    'weight' => 20,
  );

  // For other base tables, explain how we join
  $data['gsa_cpat_message']['table']['join'] = array(
    'users' => array(
      'left_table' => 'users',
      'field' => 'sender_uid',
      'left_field' => 'uid',
      'type' => 'LEFT',
    ),
    'node' => array(
      'left_table' => 'node',
      'field' => 'nid',
      'left_field' => 'nid',
      'type' => 'LEFT',
    ),
  );

  // Message id
  $data['gsa_cpat_message']['mid'] = array(
    'title' => t('Message ID'),
    'help' => t('The message ID.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click sortable' => TRUE,
     ),
     'filter' => array(
      'handler' => 'views_handler_filter_numeric',
     ),
     'argument' => array(
       'handler' => 'views_handler_argument_numeric',
     ),
     'sort' => array(
      'handler' => 'views_handler_numeric',
     ),
  );
  
  // Timestamp
  $data['gsa_cpat_message']['timestamp'] = array(
    'title' => t('Message date'),
    'help' => t('When the message was sent.'),
    'field' => array(
      'handler' => 'views_handler_field_date',
      'click sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_date',
    ),
  );

  // Reviewed
  $data['gsa_cpat_message']['reviewed'] = array(
    'title' => t('Status'),
    'help' => t('Whether the message has been reviewed or not.'),
    'field' => array(
      'handler' => 'views_handler_field_gsa_cpat_renewed',
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
    'filter' => array(
      'handler' => 'views_handler_filter_gsa_cpat_reviewed',
    ),
  );

  // Message
  $data['gsa_cpat_message']['message'] = array(
    'title' => t('Message'),
    'help' => t('The message text.'),
    'field' => array(
      'handler' => 'views_handler_field',
    ),
  );
  
  // Node
  $data['gsa_cpat_message']['nid'] = array(
    'title' => t('Node'),
    'help' => t('The node the messages were submitted through.'),
    'relationship' => array(
      'base' => 'node',
      'handler' => 'views_handler_relationship',
      'label' => t('Node'),
      'skip base' => array('node', 'node_revisions'),
    ),
  );

  // User (sender)
  $data['gsa_cpat_message']['sender_uid'] = array(
    'title' => t('Sender'),
    'help' => t('The user who submitted the message.'),
    'relationship' => array(
      'base' => 'users',
      'handler' => 'views_handler_relationship',
      'label' => t('User'),
      'skip base' => array('users', 'node', 'node_revisions'),
    ),
  );
  
  // Sender name
  $data['gsa_cpat_message']['sender_name'] = array(
    'title' => t('Sender (real name)'),
    'help' => t('The message sender\'s real name.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click_sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  // Sender email
  $data['gsa_cpat_message']['sender_mail'] = array(
    'title' => t('Sender (email address)'),
    'help' => t('The message sender\'s supplied email address.'),
    'field' => array(
      'handler' => 'views_handler_field',
      'click_sortable' => TRUE,
    ),
    'sort' => array(
      'handler' => 'views_handler_sort',
    ),
  );

  return $data;
}

/**
 * Implementation of hook_views_handlers() to register all of the basic handlers
 * views uses.
 */
function gsa_cpat_views_handlers() {
  return array(
    'info' => array(
      'path' => drupal_get_path('module', 'gsa_cpat') . '/views',
    ),
    'handlers' => array(
      'views_handler_field_gsa_cpat_renewed' => array(
        'parent' => 'views_handler_field',
      ),
      'views_handler_filter_gsa_cpat_reviewed' => array(
        'parent' => 'views_handler_filter_in_operator',
      ),
    ),
  );
}
