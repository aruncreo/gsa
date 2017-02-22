<?php

/**
 * Implements hook_heartbeat_stream_info().
 */
function gsa_friend_activity_heartbeat_stream_info() {

  $heartbeatstreams = array();

  /**
   * gsarelationsactivity
   */
  $heartbeatstream = new HeartbeatStreamConfig();
  $heartbeatstream->disabled = FALSE; /* Edit this to true to make a default heartbeatstream disabled initially */
  $heartbeatstream->api_version = 1;
  $heartbeatstream->class = 'gsarelationsactivity';
  $heartbeatstream->real_class = 'gsarelationsactivity';
  $heartbeatstream->name = 'GSA user relations activity';
  $heartbeatstream->module = 'gsa_friend_activity';
  $heartbeatstream->title = 'GSA user relations activity';
  $heartbeatstream->path = 'streams/gsarelationsactivity.inc';
  $heartbeatstream->settings = array(
    'settings__active_tab' => 'edit-settings-fs-blocks',
    'messages_denied' => array(
    ),
    'skip_active_user' => 0,
    'show_message_times' => 1,
    'show_message_times_grouped' => 1,
    'poll_messages' => '0',
    'num_load_max' => '30',
    'grouping_seconds' => '7200',
    'has_block' => 1,
    'block_items_max' => '5',
    'block_show_pager' => '1',
    'block_view_mode' => 'default',
    'stream_path' => 'heartbeat/gsa-relations',
    'stream_profile_path' => 'gsa-friends-activity',
    'page_items_max' => '8',
    'page_show_pager' => 1,
    'page_pager_ajax' => 1,
    'page_view_mode' => 'full',
    'show_status_form' => '0',
    'shoutbox' => 0,
  );
  $heartbeatstream->variables = array();
  $heartbeatstreams['gsarelationsactivity'] = $heartbeatstream;

  return $heartbeatstreams;

}

