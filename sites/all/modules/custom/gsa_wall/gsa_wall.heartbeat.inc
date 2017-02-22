<?php
/**
 * @file
 * gsa_wall.heartbeat.inc
 */

/**
 * Implements hook_heartbeat_template_info().
 */
function gsa_wall_heartbeat_template_info() {
  $export = array();

  $heartbeatmessagetemplate = new HeartbeatMessageTemplate();
  $heartbeatmessagetemplate->disabled = FALSE; /* Edit this to true to make a default heartbeatmessagetemplate disabled initially */
  $heartbeatmessagetemplate->api_version = 1;
  $heartbeatmessagetemplate->message_id = 'heartbeat_like_node';
  $heartbeatmessagetemplate->description = 'User liked some content';
  $heartbeatmessagetemplate->message = '!username likes !node_title';
  $heartbeatmessagetemplate->message_concat = '';
  $heartbeatmessagetemplate->perms = 4;
  $heartbeatmessagetemplate->group_type = 'single';
  $heartbeatmessagetemplate->concat_args = array(
    'group_by' => 'none',
    'group_target' => '',
    'group_by_target' => '',
    'group_num_max' => '',
    'merge_separator' => '',
    'merge_end_separator' => '',
    'roles' => array(
      1 => 0,
      2 => 0,
      12 => 0,
      11 => 0,
      6 => 0,
      7 => 0,
      3 => 0,
      9 => 0,
      5 => 0,
      10 => 0,
      8 => 0,
    ),
  );
  $heartbeatmessagetemplate->variables = array(
    '!username' => '',
    '!node_title' => '',
  );
  $heartbeatmessagetemplate->attachments = array(
    'buttons' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'settings' => array(
        'activitycomments' => array(
          'activitycomments_node' => 0,
        ),
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
    'content' => array(
      'weight' => array(
        'flagattachment:like' => '0',
        'activitycomments' => '2',
      ),
      'enabled' => array(
        'flagattachment:like' => 0,
        'activitycomments' => 0,
      ),
    ),
  );
  $export['heartbeat_like_node'] = $heartbeatmessagetemplate;

  return $export;
}

/**
 * Implements hook_heartbeat_stream_info().
 */
function gsa_wall_heartbeat_stream_info() {
  $export = array();

  $heartbeatstream = new HeartbeatStreamConfig();
  $heartbeatstream->disabled = FALSE; /* Edit this to true to make a default heartbeatstream disabled initially */
  $heartbeatstream->api_version = 1;
  $heartbeatstream->class = 'nodeactivity_like';
  $heartbeatstream->real_class = 'nodeactivity';
  $heartbeatstream->name = 'Node activity';
  $heartbeatstream->module = 'heartbeat_defaults';
  $heartbeatstream->title = 'Node "Like" activity';
  $heartbeatstream->path = 'streams/nodeactivity.inc';
  $heartbeatstream->settings = array(
    'settings__active_tab' => 'edit-settings-fs-activity-status',
    'messages_denied' => array(
      'heartbeat_add_comment' => 'heartbeat_add_comment',
      'heartbeat_add_node' => 'heartbeat_add_node',
      'heartbeat_edit_account' => 'heartbeat_edit_account',
      'heartbeat_edit_node' => 'heartbeat_edit_node',
      'heartbeat_become_friends' => 'heartbeat_become_friends',
      'heartbeat_tweet' => 'heartbeat_tweet',
      'heartbeat_like_node' => 0,
    ),
    'skip_active_user' => 0,
    'show_message_times' => 1,
    'show_message_times_grouped' => 1,
    'poll_messages' => '60',
    'poll_messages_type' => '0',
    'num_load_max' => '20',
    'grouping_seconds' => '7200',
    'has_block' => 0,
    'block_items_max' => '5',
    'block_show_pager' => '1',
    'block_view_mode' => 'default',
    'stream_path' => '',
    'stream_profile_path' => '',
    'page_items_max' => '8',
    'page_show_pager' => 0,
    'page_pager_ajax' => 0,
    'page_view_mode' => 'full',
    'exclude_og' => 0,
    'show_status_form' => '0',
  );
  $heartbeatstream->variables = array();
  $export['nodeactivity_like'] = $heartbeatstream;

  return $export;
}
