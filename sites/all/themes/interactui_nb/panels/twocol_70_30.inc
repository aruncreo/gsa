<?php // $Id $

/**
 * @file twocol_70_30.inc
 * Implementation of hook_panels_layouts()
 */
// Plugin definition
$plugin = array(
  'title' => t('Two column 70/30'),
  'category' => t('Columns: 2'),
  'icon' => 'twocol_70_30.png',
  'theme' => 'twocol_70_30',
  'css' => 'twocol_70_30.css',
  'regions' => array(
    'left' => t('Left side'),
    'right' => t('Right side')
  ),
);
