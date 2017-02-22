<?php
/**
 * @file
 * gsa_cpat.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gsa_cpat_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cpat_files|node|gsa_cpat|default';
  $field_group->group_name = 'group_cpat_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_cpat';
  $field_group->mode = 'default';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach files to this post',
    'weight' => '9',
    'children' => array(
      0 => 'field_cpat_attachments',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_cpat_files|node|gsa_cpat|default'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cpat_files|node|gsa_cpat|form';
  $field_group->group_name = 'group_cpat_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_cpat';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach files to this post',
    'weight' => '9',
    'children' => array(
      0 => 'field_cpat_attachments',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_cpat_files|node|gsa_cpat|form'] = $field_group;

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_cpat_files|node|gsa_cpat|teaser';
  $field_group->group_name = 'group_cpat_files';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'gsa_cpat';
  $field_group->mode = 'teaser';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Attach files to this post',
    'weight' => '6',
    'children' => array(
      0 => 'field_cpat_attachments',
    ),
    'format_type' => 'fieldset',
    'format_settings' => array(
      'formatter' => 'collapsible',
      'instance_settings' => array(),
    ),
  );
  $export['group_cpat_files|node|gsa_cpat|teaser'] = $field_group;

  return $export;
}
