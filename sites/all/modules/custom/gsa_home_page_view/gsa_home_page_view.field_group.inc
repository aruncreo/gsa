<?php
/**
 * @file
 * gsa_home_page_view.field_group.inc
 */

/**
 * Implements hook_field_group_info().
 */
function gsa_home_page_view_field_group_info() {
  $export = array();

  $field_group = new stdClass();
  $field_group->disabled = FALSE; /* Edit this to true to make a default field_group disabled initially */
  $field_group->api_version = 1;
  $field_group->identifier = 'group_groupsettings|node|group|form';
  $field_group->group_name = 'group_groupsettings';
  $field_group->entity_type = 'node';
  $field_group->bundle = 'group';
  $field_group->mode = 'form';
  $field_group->parent_name = '';
  $field_group->data = array(
    'label' => 'Group settings',
    'weight' => '5',
    'children' => array(
      0 => 'field_featured_group',
      1 => 'group_group',
      2 => 'group_access',
      3 => 'og_roles_permissions',
      4 => 'field_group_content_featured_sta',
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
  $export['group_groupsettings|node|group|form'] = $field_group;

  return $export;
}
