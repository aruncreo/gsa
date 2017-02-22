<?php // $Id $

$plugin = array(
  'title' => t('Two column 30/70'),
  'category' => t('Columns: 2'),
  'icon' => 'twocol_30_70.png',
  'theme' => 'twocol_30_70',
  'theme arguments' => array('id', 'content'),
  'css' => 'twocol_30_70.css',
  'regions' => array(
    'top' => t('Top'),
    'left' => t('Left side'),
    'right' => t('Right side'),
    'bottom' => t('Bottom')
  ),
);
