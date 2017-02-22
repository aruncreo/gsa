<?php

/**
 * Implementation of hook_strongarm().
 */
function gsa_bpa_strongarm() {
  $export = array();
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_anonymous_bpa_listing';
  $strongarm->value = 0;

  $export['comment_anonymous_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_bpa_listing';
  $strongarm->value = '0';

  $export['comment_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_controls_bpa_listing';
  $strongarm->value = '3';

  $export['comment_controls_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_mode_bpa_listing';
  $strongarm->value = '4';

  $export['comment_default_mode_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_order_bpa_listing';
  $strongarm->value = '1';

  $export['comment_default_order_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_default_per_page_bpa_listing';
  $strongarm->value = '50';

  $export['comment_default_per_page_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_form_location_bpa_listing';
  $strongarm->value = '0';

  $export['comment_form_location_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_preview_bpa_listing';
  $strongarm->value = '1';

  $export['comment_preview_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'comment_subject_field_bpa_listing';
  $strongarm->value = '1';

  $export['comment_subject_field_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'content_extra_weights_bpa_listing';
  $strongarm->value = array(
    'title' => '-1',
    'revision_information' => '10',
    'author' => '9',
    'options' => '11',
    'comment_settings' => '12',
    'menu' => '7',
    'path' => '13',
    'og_nodeapi' => '1',
    'locations' => '8',
  );

  $export['content_extra_weights_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'node_options_bpa_listing';
  $strongarm->value = array(
    0 => 'status',
  );

  $export['node_options_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_content_type_bpa_listing';
  $strongarm->value = array();

  $export['notifications_content_type_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'notifications_node_ui_bpa_listing';
  $strongarm->value = array();

  $export['notifications_node_ui_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'og_content_type_usage_bpa_listing';
  $strongarm->value = 'group_post_standard';

  $export['og_content_type_usage_bpa_listing'] = $strongarm;
  $strongarm = new stdClass;
  $strongarm->disabled = FALSE; /* Edit this to true to make a default strongarm disabled initially */
  $strongarm->api_version = 1;
  $strongarm->name = 'upload_bpa_listing';
  $strongarm->value = '0';

  $export['upload_bpa_listing'] = $strongarm;
  return $export;
}
