<?php
/**
 * @file
 * gsa_wall.layouts.inc
 */

/**
 * Implements hook_default_panels_layout().
 */
function gsa_wall_default_panels_layout() {
  $export = array();

  $layout = new stdClass();
  $layout->disabled = FALSE; /* Edit this to true to make a default layout disabled initially */
  $layout->api_version = 1;
  $layout->name = 'dashboard_layout';
  $layout->admin_title = 'Dashboard Layout';
  $layout->admin_description = '';
  $layout->category = 'GSA Layouts';
  $layout->plugin = 'flexible';
  $layout->settings = array(
    'items' => array(
      'canvas' => array(
        'type' => 'row',
        'contains' => 'column',
        'children' => array(
          0 => 'main',
          1 => 2,
        ),
        'parent' => NULL,
      ),
      'main' => array(
        'type' => 'column',
        'width' => '76.07344904254089',
        'width_type' => '%',
        'children' => array(
          0 => 1,
          1 => 'main-row',
        ),
        'parent' => 'canvas',
      ),
      'main-row' => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'region_left',
          1 => 'center',
        ),
        'parent' => 'main',
      ),
      'center' => array(
        'type' => 'region',
        'title' => 'Center',
        'width' => '43.35740536881765',
        'width_type' => '%',
        'parent' => 'main-row',
      ),
      'region_left' => array(
        'type' => 'region',
        'title' => 'Region Left',
        'width' => '19.049590656187462',
        'width_type' => '%',
        'parent' => 'main-row',
        'class' => '',
      ),
      1 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'left_title',
        ),
        'parent' => 'main',
        'class' => '',
      ),
      'left_title' => array(
        'type' => 'region',
        'title' => 'Left Title',
        'width' => 100,
        'width_type' => '%',
        'parent' => '1',
        'class' => '',
      ),
      2 => array(
        'type' => 'column',
        'width' => '23.92655095745911',
        'width_type' => '%',
        'parent' => 'canvas',
        'children' => array(
          0 => 3,
        ),
        'class' => '',
      ),
      3 => array(
        'type' => 'row',
        'contains' => 'region',
        'children' => array(
          0 => 'region_right',
        ),
        'parent' => '2',
        'class' => '',
      ),
      'region_right' => array(
        'type' => 'region',
        'title' => 'Region Right',
        'width' => 100,
        'width_type' => '%',
        'parent' => '3',
        'class' => '',
      ),
    ),
  );
  $export['dashboard_layout'] = $layout;

  return $export;
}
