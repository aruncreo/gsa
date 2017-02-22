<?php
/**
 * @file
 * gsa_event.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gsa_event_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_classes|node|gsa_event|default';
  $field_group->group_name = 'group_gsa_event_classes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Classes',
    'weight' => '28',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_classes|node|gsa_event|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_classes|node|gsa_event|form';
  $field_group->group_name = 'group_gsa_event_classes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Classes',
    'weight' => '5',
    'children' => array(
      0 => 'field_gsa_class_clp',
      1 => 'field_gsa_class_instructor',
      2 => 'field_gsa_class_name',
      3 => 'field_gsa_class_session',
      4 => 'field_gsa_class_sfid',
      5 => 'field_gsa_class_start_date_time',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_classes|node|gsa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_classes|node|gsa_event|teaser';
  $field_group->group_name = 'group_gsa_event_classes';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '7',
    'children' => array(),
    'format_type' => 'hidden',
    'format_settings' => array(
      'formatter' => '',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_classes|node|gsa_event|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_date|node|gsa_event|default';
  $field_group->group_name = 'group_gsa_event_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Date & Time',
    'weight' => '0',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_date|node|gsa_event|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_date|node|gsa_event|form';
  $field_group->group_name = 'group_gsa_event_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Date & Time',
    'weight' => '2',
    'children' => array(
      0 => 'field_gsa_end_date_time',
      1 => 'field_gsa_start_date_time',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_date|node|gsa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_date|node|gsa_event|teaser';
  $field_group->group_name = 'group_gsa_event_date';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '0',
    'children' => array(),
    'format_type' => 'fieldset',
  );
  $export['group_gsa_event_date|node|gsa_event|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_details|node|gsa_event|default';
  $field_group->group_name = 'group_gsa_event_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '1',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_details|node|gsa_event|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_details|node|gsa_event|form';
  $field_group->group_name = 'group_gsa_event_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Details',
    'weight' => '3',
    'children' => array(
      0 => 'field_gsa_business_line',
      1 => 'field_gsa_category',
      2 => 'field_gsa_event_hours',
      3 => 'field_gsa_event_website',
      4 => 'field_gsa_targeted_audience',
      5 => 'field_gsa_teaser',
      6 => 'field_gsa_type',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_details|node|gsa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_details|node|gsa_event|teaser';
  $field_group->group_name = 'group_gsa_event_details';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '1',
    'children' => array(),
    'format_type' => 'fieldset',
  );
  $export['group_gsa_event_details|node|gsa_event|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_location|node|gsa_event|default';
  $field_group->group_name = 'group_gsa_event_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '2',
    'children' => array(),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_location|node|gsa_event|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_location|node|gsa_event|form';
  $field_group->group_name = 'group_gsa_event_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Location',
    'weight' => '4',
    'children' => array(
      0 => 'field_gsa_address_1',
      1 => 'field_gsa_address_2',
      2 => 'field_gsa_city',
      3 => 'field_gsa_country',
      4 => 'field_gsa_hotel_information',
      5 => 'field_gsa_room',
      6 => 'field_gsa_state',
      7 => 'field_gsa_venue',
      8 => 'field_gsa_zip',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_gsa_event_location|node|gsa_event|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_event_location|node|gsa_event|teaser';
  $field_group->group_name = 'group_gsa_event_location';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => '',
    'weight' => '2',
    'children' => array(),
    'format_type' => 'fieldset',
  );
  $export['group_gsa_event_location|node|gsa_event|teaser'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_salesforce|node|gsa_event|form';
  $field_group->group_name = 'group_salesforce';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_event';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Salesforce',
    'weight' => '6',
    'children' => array(
      0 => 'field_gsa_id',
      1 => 'field_gsa_recordtype',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(
        'description' => '',
        'classes' => '',
        'required_fields' => 1,
      ),
    ),
  );
  $export['group_salesforce|node|gsa_event|form'] = $field_group;

  return $export;
}
