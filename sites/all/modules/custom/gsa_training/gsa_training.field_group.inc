<?php
/**
 * @file
 * gsa_training.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gsa_training_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_gsa_webinar_salesforce|node|gsa_webinar|form';
  $field_group->group_name = 'group_gsa_webinar_salesforce';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_webinar';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_gsa_webinar_salesforce|node|gsa_webinar|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_salesforce|node|gsa_webinar|default';
  $field_group->group_name = 'group_salesforce';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_webinar';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_salesforce|node|gsa_webinar|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_salesforce|node|gsa_webinar|teaser';
  $field_group->group_name = 'group_salesforce';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_webinar';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = '';
  $export['group_salesforce|node|gsa_webinar|teaser'] = $field_group;

  return $export;
}
