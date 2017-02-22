<?php


/**
* Implements hook_views_data_alter().
*/
function gsa_event_views_data_alter(&$data) { 
  $data['field_data_field_gsa_class_clp']['field_gsa_class_clp']['field']['handler'] = 'gsa_event_field';
}




