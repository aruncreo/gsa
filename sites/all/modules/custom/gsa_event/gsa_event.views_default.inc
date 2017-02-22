<?php
/**
 * @file
 * gsa_event.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gsa_event_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'gsa_customer_training';
  $view->description = 'View all upcoming GSA training events';
  $view->tag = 'GSA';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Upcoming GSA Training Sessions';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['distinct'] = TRUE;
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '15';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_gsa_start_date_time' => 'field_gsa_start_date_time',
    'field_gsa_end_date_time' => 'field_gsa_start_date_time',
    'title' => 'title',
    'field_gsa_teaser' => 'title',
    'field_gsa_city' => 'field_gsa_city',
    'field_gsa_state' => 'field_gsa_city',
    'field_gsa_class_clp' => 'field_gsa_class_clp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_gsa_start_date_time' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;-<br/>',
      'empty_column' => 0,
    ),
    'field_gsa_end_date_time' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'field_gsa_teaser' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gsa_city' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ', ',
      'empty_column' => 0,
    ),
    'field_gsa_state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gsa_class_clp' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Header: Global: View area */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'gsa_event_map:page';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'text';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['empty'] = TRUE;
  $handler->display->display_options['empty']['text']['content'] = 'There are currently no upcoming GSA Training Sessions.';
  $handler->display->display_options['empty']['text']['format'] = 'full_html';
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: CLP Credits */
  $handler->display->display_options['fields']['field_webinar_class_clp']['id'] = 'field_webinar_class_clp';
  $handler->display->display_options['fields']['field_webinar_class_clp']['table'] = 'field_data_field_webinar_class_clp';
  $handler->display->display_options['fields']['field_webinar_class_clp']['field'] = 'field_webinar_class_clp';
  /* Sort criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Event';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Location: City */
  $handler->display->display_options['filters']['city']['id'] = 'city';
  $handler->display->display_options['filters']['city']['table'] = 'location';
  $handler->display->display_options['filters']['city']['field'] = 'city';
  $handler->display->display_options['filters']['city']['operator'] = 'contains';
  $handler->display->display_options['filters']['city']['group'] = 1;
  $handler->display->display_options['filters']['city']['exposed'] = TRUE;
  $handler->display->display_options['filters']['city']['expose']['operator_id'] = 'city_op';
  $handler->display->display_options['filters']['city']['expose']['label'] = 'City';
  $handler->display->display_options['filters']['city']['expose']['operator'] = 'city_op';
  $handler->display->display_options['filters']['city']['expose']['identifier'] = 'city';
  /* Filter criterion: Content: State (field_gsa_state) */
  $handler->display->display_options['filters']['field_gsa_state_value']['id'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['filters']['field_gsa_state_value']['field'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_state_value']['group'] = 1;
  $handler->display->display_options['filters']['field_gsa_state_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator_id'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['identifier'] = 'field_gsa_state_value';

  /* Display: Root */
  $handler = $view->new_display('page', 'Root', 'page_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming Live: In-Person';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['label'] = 'CLP';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_gsa_class_clp']['sum_field_value_prefix'] = 'Up to';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Event';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Content: City (field_gsa_city) */
  $handler->display->display_options['filters']['field_gsa_city_value']['id'] = 'field_gsa_city_value';
  $handler->display->display_options['filters']['field_gsa_city_value']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['filters']['field_gsa_city_value']['field'] = 'field_gsa_city_value';
  $handler->display->display_options['filters']['field_gsa_city_value']['group'] = 1;
  $handler->display->display_options['filters']['field_gsa_city_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_gsa_city_value']['expose']['operator_id'] = 'field_gsa_city_value_op';
  $handler->display->display_options['filters']['field_gsa_city_value']['expose']['label'] = 'City ';
  $handler->display->display_options['filters']['field_gsa_city_value']['expose']['operator'] = 'field_gsa_city_value_op';
  $handler->display->display_options['filters']['field_gsa_city_value']['expose']['identifier'] = 'field_gsa_city_value';
  $handler->display->display_options['filters']['field_gsa_city_value']['expose']['remember_roles'] = array(
    2 => '2',
    8 => 0,
    1 => 0,
    7 => 0,
    3 => 0,
    9 => 0,
    12 => 0,
    13 => 0,
    10 => 0,
    6 => 0,
    5 => 0,
    11 => 0,
  );
  /* Filter criterion: Content: State (field_gsa_state) */
  $handler->display->display_options['filters']['field_gsa_state_value']['id'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['filters']['field_gsa_state_value']['field'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_state_value']['group'] = 1;
  $handler->display->display_options['filters']['field_gsa_state_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator_id'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['identifier'] = 'field_gsa_state_value';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'Virtual';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['group'] = 1;
  $handler->display->display_options['path'] = 'gsa-training';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Training';
  $handler->display->display_options['menu']['description'] = 'View all upcoming training events';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'primary-links';
  $handler->display->display_options['tab_options']['type'] = 'normal';
  $handler->display->display_options['tab_options']['title'] = 'Training';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'primary-links';

  /* Display: Tab */
  $handler = $view->new_display('page', 'Tab', 'page_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming Live: In Person';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['area']['id'] = 'area';
  $handler->display->display_options['header']['area']['table'] = 'views';
  $handler->display->display_options['header']['area']['field'] = 'area';
  $handler->display->display_options['header']['area']['content'] = 'text';
  $handler->display->display_options['header']['area']['format'] = 'full_html';
  /* Header: Global: View area */
  $handler->display->display_options['header']['view']['id'] = 'view';
  $handler->display->display_options['header']['view']['table'] = 'views';
  $handler->display->display_options['header']['view']['field'] = 'view';
  $handler->display->display_options['header']['view']['view_to_insert'] = 'gsa_event_map:page';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: CLP Credits */
  $handler->display->display_options['fields']['field_webinar_class_clp']['id'] = 'field_webinar_class_clp';
  $handler->display->display_options['fields']['field_webinar_class_clp']['table'] = 'field_data_field_webinar_class_clp';
  $handler->display->display_options['fields']['field_webinar_class_clp']['field'] = 'field_webinar_class_clp';
  $handler->display->display_options['fields']['field_webinar_class_clp']['label'] = 'CLP';
  $handler->display->display_options['fields']['field_webinar_class_clp']['element_label_colon'] = FALSE;
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  $handler->display->display_options['path'] = 'gsa-training/events';
  $handler->display->display_options['menu']['title'] = 'In Person';
  $handler->display->display_options['menu']['weight'] = '0';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Archive In-Person */
  $handler = $view->new_display('page', 'Archive In-Person', 'page_3');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Past GSA Training Sessions';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'There are currently no past GSA Training Sessions.';
  $handler->display->display_options['empty']['text']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['label'] = 'CLP';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_gsa_class_clp']['sum_field_value_prefix'] = 'Up to';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '<';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Event';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Location: City */
  $handler->display->display_options['filters']['city']['id'] = 'city';
  $handler->display->display_options['filters']['city']['table'] = 'location';
  $handler->display->display_options['filters']['city']['field'] = 'city';
  $handler->display->display_options['filters']['city']['operator'] = 'contains';
  $handler->display->display_options['filters']['city']['group'] = 1;
  $handler->display->display_options['filters']['city']['exposed'] = TRUE;
  $handler->display->display_options['filters']['city']['expose']['operator_id'] = 'city_op';
  $handler->display->display_options['filters']['city']['expose']['label'] = 'City';
  $handler->display->display_options['filters']['city']['expose']['operator'] = 'city_op';
  $handler->display->display_options['filters']['city']['expose']['identifier'] = 'city';
  /* Filter criterion: Content: State (field_gsa_state) */
  $handler->display->display_options['filters']['field_gsa_state_value']['id'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['filters']['field_gsa_state_value']['field'] = 'field_gsa_state_value';
  $handler->display->display_options['filters']['field_gsa_state_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_state_value']['group'] = 1;
  $handler->display->display_options['filters']['field_gsa_state_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator_id'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['label'] = 'State';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['operator'] = 'field_gsa_state_value_op';
  $handler->display->display_options['filters']['field_gsa_state_value']['expose']['identifier'] = 'field_gsa_state_value';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'virtual';
  $handler->display->display_options['path'] = 'gsa-training/archive/inperson';
  $handler->display->display_options['menu']['title'] = 'Past Training Sessions';
  $handler->display->display_options['menu']['weight'] = '8';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = '0';
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'node_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'node_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  $handler->display->display_options['path'] = 'gsa-training/events/feed';
  $handler->display->display_options['displays'] = array(
    'page_1' => 'page_1',
    'page_2' => 'page_2',
    'default' => 0,
    'page_3' => 0,
  );

  /* Display: Virtual */
  $handler = $view->new_display('page', 'Virtual', 'page_4');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming Live: Virtual';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_gsa_start_date_time' => 'field_gsa_start_date_time',
    'field_gsa_end_date_time' => 'field_gsa_start_date_time',
    'title' => 'title',
    'field_gsa_teaser' => 'title',
    'field_gsa_city' => 'field_gsa_city',
    'field_gsa_state' => 'field_gsa_city',
    'field_gsa_class_clp' => 'field_gsa_class_clp',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_gsa_start_date_time' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '&nbsp;-<br/>',
      'empty_column' => 0,
    ),
    'field_gsa_end_date_time' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '<br/>',
      'empty_column' => 0,
    ),
    'field_gsa_teaser' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gsa_city' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => ' ',
      'empty_column' => 0,
    ),
    'field_gsa_state' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_gsa_class_clp' => array(
      'align' => 'views-align-center',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_city']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_city']['alter']['text'] = ' ';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['label'] = 'CLP';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_gsa_class_clp']['sum_field_value_prefix'] = 'Up to';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '>=';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Event';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'Virtual';
  $handler->display->display_options['path'] = 'gsa-training/virtual';
  $handler->display->display_options['menu']['title'] = 'Virtual';
  $handler->display->display_options['menu']['description'] = 'Virtual';
  $handler->display->display_options['menu']['weight'] = '4';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['title'] = 'Videos';
  $handler->display->display_options['tab_options']['weight'] = '0';
  $handler->display->display_options['tab_options']['name'] = 'menu-menu-connectwithus';

  /* Display: Archive Virtual */
  $handler = $view->new_display('page', 'Archive Virtual', 'page_5');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Past GSA Training Sessions';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['header'] = FALSE;
  $handler->display->display_options['defaults']['empty'] = FALSE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'There are currently no past GSA Training Sessions.';
  $handler->display->display_options['empty']['text']['format'] = 'filtered_html';
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Date';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'short',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = 'Location';
  $handler->display->display_options['fields']['field_gsa_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['label'] = 'CLP';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  $handler->display->display_options['fields']['field_gsa_class_clp']['sum_field_value_prefix'] = 'Up to';
  $handler->display->display_options['defaults']['sorts'] = FALSE;
  /* Sort criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['sorts']['field_gsa_start_date_time_value']['order'] = 'DESC';
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = 1;
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Date: Date (node) */
  $handler->display->display_options['filters']['date_filter']['id'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['table'] = 'node';
  $handler->display->display_options['filters']['date_filter']['field'] = 'date_filter';
  $handler->display->display_options['filters']['date_filter']['operator'] = '<';
  $handler->display->display_options['filters']['date_filter']['group'] = 1;
  $handler->display->display_options['filters']['date_filter']['expose']['operator'] = FALSE;
  $handler->display->display_options['filters']['date_filter']['default_date'] = 'now';
  $handler->display->display_options['filters']['date_filter']['default_to_date'] = 'now - 1 day';
  $handler->display->display_options['filters']['date_filter']['date_fields'] = array(
    'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value' => 'field_data_field_gsa_start_date_time.field_gsa_start_date_time_value',
  );
  /* Filter criterion: Content: Title */
  $handler->display->display_options['filters']['title']['id'] = 'title';
  $handler->display->display_options['filters']['title']['table'] = 'node';
  $handler->display->display_options['filters']['title']['field'] = 'title';
  $handler->display->display_options['filters']['title']['operator'] = 'contains';
  $handler->display->display_options['filters']['title']['group'] = 1;
  $handler->display->display_options['filters']['title']['exposed'] = TRUE;
  $handler->display->display_options['filters']['title']['expose']['operator_id'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['label'] = 'Event';
  $handler->display->display_options['filters']['title']['expose']['operator'] = 'title_op';
  $handler->display->display_options['filters']['title']['expose']['identifier'] = 'title';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'virtual';
  $handler->display->display_options['path'] = 'gsa-training/archive/virtual';
  $handler->display->display_options['menu']['title'] = 'Past Training Sessions';
  $handler->display->display_options['menu']['weight'] = '8';
  $handler->display->display_options['menu']['context'] = 0;
  $handler->display->display_options['tab_options']['weight'] = '0';
  $export['gsa_customer_training'] = $view;

  $view = new view();
  $view->name = 'gsa_event_class';
  $view->description = 'Shows classes for an event';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Available Classes';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Class Name */
  $handler->display->display_options['fields']['field_gsa_class_name']['id'] = 'field_gsa_class_name';
  $handler->display->display_options['fields']['field_gsa_class_name']['table'] = 'field_data_field_gsa_class_name';
  $handler->display->display_options['fields']['field_gsa_class_name']['field'] = 'field_gsa_class_name';
  $handler->display->display_options['fields']['field_gsa_class_name']['label'] = 'Name';
  $handler->display->display_options['fields']['field_gsa_class_name']['delta_offset'] = '0';
  /* Field: Content: Class Instructor */
  $handler->display->display_options['fields']['field_gsa_class_instructor']['id'] = 'field_gsa_class_instructor';
  $handler->display->display_options['fields']['field_gsa_class_instructor']['table'] = 'field_data_field_gsa_class_instructor';
  $handler->display->display_options['fields']['field_gsa_class_instructor']['field'] = 'field_gsa_class_instructor';
  $handler->display->display_options['fields']['field_gsa_class_instructor']['label'] = 'Instructor';
  $handler->display->display_options['fields']['field_gsa_class_instructor']['delta_offset'] = '0';
  /* Field: Content: Class CLP Credits */
  $handler->display->display_options['fields']['field_gsa_class_clp']['id'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['table'] = 'field_data_field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['field'] = 'field_gsa_class_clp';
  $handler->display->display_options['fields']['field_gsa_class_clp']['label'] = 'CLP Credits';
  $handler->display->display_options['fields']['field_gsa_class_clp']['delta_offset'] = '0';
  /* Field: Content: Class Session */
  $handler->display->display_options['fields']['field_gsa_class_session']['id'] = 'field_gsa_class_session';
  $handler->display->display_options['fields']['field_gsa_class_session']['table'] = 'field_data_field_gsa_class_session';
  $handler->display->display_options['fields']['field_gsa_class_session']['field'] = 'field_gsa_class_session';
  $handler->display->display_options['fields']['field_gsa_class_session']['label'] = 'Session';
  $handler->display->display_options['fields']['field_gsa_class_session']['delta_offset'] = '0';
  /* Field: Content: Class Start Date/Time */
  $handler->display->display_options['fields']['field_gsa_class_start_date_time']['id'] = 'field_gsa_class_start_date_time';
  $handler->display->display_options['fields']['field_gsa_class_start_date_time']['table'] = 'field_data_field_gsa_class_start_date_time';
  $handler->display->display_options['fields']['field_gsa_class_start_date_time']['field'] = 'field_gsa_class_start_date_time';
  $handler->display->display_options['fields']['field_gsa_class_start_date_time']['label'] = 'Start Time';
  $handler->display->display_options['fields']['field_gsa_class_start_date_time']['delta_offset'] = '0';
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  $export['gsa_event_class'] = $view;

  $view = new view();
  $view->name = 'gsa_event_fieldgroups';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'gsa_event_fieldgroups';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Event Info';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['pager']['options']['items_per_page'] = '1';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );

  /* Display: Details Block */
  $handler = $view->new_display('block', 'Details Block', 'block');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Details';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Teaser */
  $handler->display->display_options['fields']['field_gsa_teaser']['id'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['table'] = 'field_data_field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['field'] = 'field_gsa_teaser';
  $handler->display->display_options['fields']['field_gsa_teaser']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_teaser']['element_label_colon'] = FALSE;
  /* Field: Content: Event hours */
  $handler->display->display_options['fields']['field_gsa_event_hours']['id'] = 'field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['table'] = 'field_data_field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['field'] = 'field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['hide_empty'] = TRUE;
  /* Field: Content: Event Website */
  $handler->display->display_options['fields']['field_gsa_event_website']['id'] = 'field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['table'] = 'field_data_field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['field'] = 'field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['hide_empty'] = TRUE;

  /* Display: Date & Time Block */
  $handler = $view->new_display('block', 'Date & Time Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Date & Time';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );

  /* Display: Location Block */
  $handler = $view->new_display('block', 'Location Block', 'block_2');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Location';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: Content: Venue */
  $handler->display->display_options['fields']['field_gsa_venue']['id'] = 'field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['table'] = 'field_data_field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['field'] = 'field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['hide_empty'] = TRUE;
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_gsa_room']['id'] = 'field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['table'] = 'field_data_field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['field'] = 'field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['hide_empty'] = TRUE;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_gsa_address_1']['id'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['table'] = 'field_data_field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['field'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['hide_empty'] = TRUE;
  /* Field: Content: Address 2 */
  $handler->display->display_options['fields']['field_gsa_address_2']['id'] = 'field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['table'] = 'field_data_field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['field'] = 'field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['hide_empty'] = TRUE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['hide_empty'] = TRUE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['hide_empty'] = TRUE;
  /* Field: Content: Zip */
  $handler->display->display_options['fields']['field_gsa_zip']['id'] = 'field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['table'] = 'field_data_field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['field'] = 'field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['hide_empty'] = TRUE;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_gsa_country']['id'] = 'field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['table'] = 'field_data_field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['field'] = 'field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['hide_empty'] = TRUE;
  /* Field: Content: Hotel Information */
  $handler->display->display_options['fields']['field_gsa_hotel_information']['id'] = 'field_gsa_hotel_information';
  $handler->display->display_options['fields']['field_gsa_hotel_information']['table'] = 'field_data_field_gsa_hotel_information';
  $handler->display->display_options['fields']['field_gsa_hotel_information']['field'] = 'field_gsa_hotel_information';
  $handler->display->display_options['fields']['field_gsa_hotel_information']['hide_empty'] = TRUE;
  /* Field: Content: Attendance Type */
  $handler->display->display_options['fields']['field_gsa_attendance_type']['id'] = 'field_gsa_attendance_type';
  $handler->display->display_options['fields']['field_gsa_attendance_type']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['fields']['field_gsa_attendance_type']['field'] = 'field_gsa_attendance_type';
  $handler->display->display_options['fields']['field_gsa_attendance_type']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_attendance_type']['element_label_colon'] = FALSE;
  /* Field: Location: Address */
  $handler->display->display_options['fields']['address']['id'] = 'address';
  $handler->display->display_options['fields']['address']['table'] = 'location';
  $handler->display->display_options['fields']['address']['field'] = 'address';
  $handler->display->display_options['fields']['address']['label'] = '';
  $handler->display->display_options['fields']['address']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['address']['hide'] = array(
    'name' => 'name',
    'street' => 'street',
    'additional' => 'additional',
    'city' => 'city',
    'province' => 'province',
    'postal_code' => 'postal_code',
    'country' => 'country',
    'locpick' => 'locpick',
    'province_name' => 'province_name',
    'country_name' => 'country_name',
    'coords' => 'coords',
    'map_link' => 0,
  );
  $export['gsa_event_fieldgroups'] = $view;

  $view = new view();
  $view->name = 'gsa_event_map';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'GSA Event Map';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'GSA Event Map';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'leaflet';
  $handler->display->display_options['style_options']['data_source'] = 'field_geo_field';
  $handler->display->display_options['style_options']['name_field'] = 'title';
  $handler->display->display_options['style_options']['description_field'] = 'title';
  $handler->display->display_options['style_options']['map'] = 'OSM Mapnik';
  $handler->display->display_options['style_options']['icon'] = array(
    'iconUrl' => '',
    'shadowUrl' => '',
    'iconSize' => array(
      'x' => '',
      'y' => '',
    ),
    'iconAnchor' => array(
      'x' => '',
      'y' => '',
    ),
    'shadowAnchor' => array(
      'x' => '',
      'y' => '',
    ),
    'popupAnchor' => array(
      'x' => '',
      'y' => '',
    ),
  );
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Content: Geo Field */
  $handler->display->display_options['fields']['field_geo_field']['id'] = 'field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['table'] = 'field_data_field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['field'] = 'field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['click_sort_column'] = 'wkt';
  $handler->display->display_options['fields']['field_geo_field']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Content: Coordinates */
  $handler->display->display_options['fields']['field_gsa_coords']['id'] = 'field_gsa_coords';
  $handler->display->display_options['fields']['field_gsa_coords']['table'] = 'field_data_field_gsa_coords';
  $handler->display->display_options['fields']['field_gsa_coords']['field'] = 'field_gsa_coords';
  /* Sort criterion: Content: Post date */
  $handler->display->display_options['sorts']['created']['id'] = 'created';
  $handler->display->display_options['sorts']['created']['table'] = 'node';
  $handler->display->display_options['sorts']['created']['field'] = 'created';
  $handler->display->display_options['sorts']['created']['order'] = 'DESC';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  /* Filter criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['default_date'] = 'now +1 day';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'Virtual';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['path'] = 'gsa-event-map';

  /* Display: Virtual */
  $handler = $view->new_display('page', 'Virtual', 'page_1');
  $handler->display->display_options['defaults']['filter_groups'] = FALSE;
  $handler->display->display_options['defaults']['filters'] = FALSE;
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  /* Filter criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['default_date'] = 'now +1 day';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'Virtual';
  $handler->display->display_options['path'] = 'gsa-event-map/virtual';
  $export['gsa_event_map'] = $view;

  $view = new view();
  $view->name = 'gsa_event_minimap';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'GSA Event Minimap';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_gsa_address_1']['id'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['table'] = 'field_data_field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['field'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_address_1']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_address_1']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_city']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Geo Field */
  $handler->display->display_options['fields']['field_geo_field']['id'] = 'field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['table'] = 'field_data_field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['field'] = 'field_geo_field';
  $handler->display->display_options['fields']['field_geo_field']['label'] = '';
  $handler->display->display_options['fields']['field_geo_field']['exclude'] = TRUE;
  $handler->display->display_options['fields']['field_geo_field']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['field_geo_field']['click_sort_column'] = 'geom';
  $handler->display->display_options['fields']['field_geo_field']['settings'] = array(
    'data' => 'full',
  );
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<a class="maplink"  style="color: #0393C9;" target="blank" href="http://maps.google.com/maps?daddr=[field_gsa_address_1],+[field_gsa_city] ,+[field_gsa_state]">View this Address in Google Maps</a>';
  $handler->display->display_options['fields']['nothing']['element_label_colon'] = FALSE;
  /* Field: Content: Coordinates */
  $handler->display->display_options['fields']['field_gsa_coords']['id'] = 'field_gsa_coords';
  $handler->display->display_options['fields']['field_gsa_coords']['table'] = 'field_data_field_gsa_coords';
  $handler->display->display_options['fields']['field_gsa_coords']['field'] = 'field_gsa_coords';
  $handler->display->display_options['fields']['field_gsa_coords']['exclude'] = TRUE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['default_action'] = 'default';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['nid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  /* Filter criterion: Content: Start Date (field_gsa_start_date_time) */
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['id'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['field'] = 'field_gsa_start_date_time_value';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['operator'] = '>=';
  $handler->display->display_options['filters']['field_gsa_start_date_time_value']['default_date'] = 'now +1 day';
  /* Filter criterion: Content: Attendance Type (field_gsa_attendance_type) */
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['id'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['table'] = 'field_data_field_gsa_attendance_type';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['field'] = 'field_gsa_attendance_type_value';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['operator'] = 'not';
  $handler->display->display_options['filters']['field_gsa_attendance_type_value']['value'] = 'virtual';

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $export['gsa_event_minimap'] = $view;

  $view = new view();
  $view->name = 'gsa_event_register_confirm';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Registration Confirmation';
  $handler->display->display_options['css_class'] = 'event-registration-confirmation';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'default';
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['row_options']['inline'] = array(
    'field_gsa_city' => 'field_gsa_city',
    'field_gsa_state' => 'field_gsa_state',
    'field_gsa_zip' => 'field_gsa_zip',
  );
  $handler->display->display_options['row_options']['separator'] = ' ';
  $handler->display->display_options['row_options']['hide_empty'] = TRUE;
  /* Header: Global: Text area */
  $handler->display->display_options['header']['text']['id'] = 'text';
  $handler->display->display_options['header']['text']['table'] = 'views';
  $handler->display->display_options['header']['text']['field'] = 'area';
  $handler->display->display_options['header']['text']['content'] = 'Thank you for registering. You may print this page for reference.';
  $handler->display->display_options['header']['text']['format'] = 'filtered_html';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = '';
  $handler->display->display_options['fields']['title']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['title']['alter']['text'] = '<h2>[title]</h2>';
  $handler->display->display_options['fields']['title']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['title']['link_to_node'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_1']['id'] = 'nothing_1';
  $handler->display->display_options['fields']['nothing_1']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_1']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_1']['label'] = '';
  $handler->display->display_options['fields']['nothing_1']['alter']['text'] = '<h3>Date & Time</h3>';
  /* Field: Content: Start Date */
  $handler->display->display_options['fields']['field_gsa_start_date_time']['id'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['table'] = 'field_data_field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['field'] = 'field_gsa_start_date_time';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['label'] = 'Begins';
  $handler->display->display_options['fields']['field_gsa_start_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: End Date */
  $handler->display->display_options['fields']['field_gsa_end_date_time']['id'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['table'] = 'field_data_field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['field'] = 'field_gsa_end_date_time';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['label'] = 'Ends';
  $handler->display->display_options['fields']['field_gsa_end_date_time']['settings'] = array(
    'format_type' => 'long',
    'fromto' => 'both',
    'multiple_number' => '',
    'multiple_from' => '',
    'multiple_to' => '',
  );
  /* Field: Content: Event hours */
  $handler->display->display_options['fields']['field_gsa_event_hours']['id'] = 'field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['table'] = 'field_data_field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['field'] = 'field_gsa_event_hours';
  $handler->display->display_options['fields']['field_gsa_event_hours']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_event_hours']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing']['id'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['table'] = 'views';
  $handler->display->display_options['fields']['nothing']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing']['label'] = '';
  $handler->display->display_options['fields']['nothing']['alter']['text'] = '<h3>Location</h3>';
  /* Field: Content: Venue */
  $handler->display->display_options['fields']['field_gsa_venue']['id'] = 'field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['table'] = 'field_data_field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['field'] = 'field_gsa_venue';
  $handler->display->display_options['fields']['field_gsa_venue']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_venue']['element_label_colon'] = FALSE;
  /* Field: Content: Room */
  $handler->display->display_options['fields']['field_gsa_room']['id'] = 'field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['table'] = 'field_data_field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['field'] = 'field_gsa_room';
  $handler->display->display_options['fields']['field_gsa_room']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_room']['element_label_colon'] = FALSE;
  /* Field: Content: Address */
  $handler->display->display_options['fields']['field_gsa_address_1']['id'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['table'] = 'field_data_field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['field'] = 'field_gsa_address_1';
  $handler->display->display_options['fields']['field_gsa_address_1']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_address_1']['element_label_colon'] = FALSE;
  /* Field: Content: Address 2 */
  $handler->display->display_options['fields']['field_gsa_address_2']['id'] = 'field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['table'] = 'field_data_field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['field'] = 'field_gsa_address_2';
  $handler->display->display_options['fields']['field_gsa_address_2']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_address_2']['element_label_colon'] = FALSE;
  /* Field: Content: City */
  $handler->display->display_options['fields']['field_gsa_city']['id'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['table'] = 'field_data_field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['field'] = 'field_gsa_city';
  $handler->display->display_options['fields']['field_gsa_city']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_city']['element_label_colon'] = FALSE;
  /* Field: Content: State */
  $handler->display->display_options['fields']['field_gsa_state']['id'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['table'] = 'field_data_field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['field'] = 'field_gsa_state';
  $handler->display->display_options['fields']['field_gsa_state']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_state']['element_label_colon'] = FALSE;
  /* Field: Content: Zip */
  $handler->display->display_options['fields']['field_gsa_zip']['id'] = 'field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['table'] = 'field_data_field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['field'] = 'field_gsa_zip';
  $handler->display->display_options['fields']['field_gsa_zip']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_zip']['element_label_colon'] = FALSE;
  /* Field: Content: Country */
  $handler->display->display_options['fields']['field_gsa_country']['id'] = 'field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['table'] = 'field_data_field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['field'] = 'field_gsa_country';
  $handler->display->display_options['fields']['field_gsa_country']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_country']['element_label_colon'] = FALSE;
  /* Field: Content: Hotel Information */
  $handler->display->display_options['fields']['field_gsa_hotel_information']['id'] = 'field_gsa_hotel_information';
  $handler->display->display_options['fields']['field_gsa_hotel_information']['table'] = 'field_data_field_gsa_hotel_information';
  $handler->display->display_options['fields']['field_gsa_hotel_information']['field'] = 'field_gsa_hotel_information';
  /* Field: Content: Event Website */
  $handler->display->display_options['fields']['field_gsa_event_website']['id'] = 'field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['table'] = 'field_data_field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['field'] = 'field_gsa_event_website';
  $handler->display->display_options['fields']['field_gsa_event_website']['label'] = '';
  $handler->display->display_options['fields']['field_gsa_event_website']['element_label_colon'] = FALSE;
  /* Field: Global: Custom text */
  $handler->display->display_options['fields']['nothing_2']['id'] = 'nothing_2';
  $handler->display->display_options['fields']['nothing_2']['table'] = 'views';
  $handler->display->display_options['fields']['nothing_2']['field'] = 'nothing';
  $handler->display->display_options['fields']['nothing_2']['label'] = '';
  $handler->display->display_options['fields']['nothing_2']['alter']['text'] = '<h3>About this event</h3>';
  /* Field: Content: Body */
  $handler->display->display_options['fields']['body']['id'] = 'body';
  $handler->display->display_options['fields']['body']['table'] = 'field_data_body';
  $handler->display->display_options['fields']['body']['field'] = 'body';
  $handler->display->display_options['fields']['body']['label'] = '';
  $handler->display->display_options['fields']['body']['element_label_colon'] = FALSE;
  /* Contextual filter: Content: Salesforce ID (field_gsa_id) */
  $handler->display->display_options['arguments']['field_gsa_id_value']['id'] = 'field_gsa_id_value';
  $handler->display->display_options['arguments']['field_gsa_id_value']['table'] = 'field_data_field_gsa_id';
  $handler->display->display_options['arguments']['field_gsa_id_value']['field'] = 'field_gsa_id_value';
  $handler->display->display_options['arguments']['field_gsa_id_value']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['field_gsa_id_value']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['field_gsa_id_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['field_gsa_id_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['field_gsa_id_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['field_gsa_id_value']['limit'] = '0';
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null']['id'] = 'null';
  $handler->display->display_options['arguments']['null']['table'] = 'views';
  $handler->display->display_options['arguments']['null']['field'] = 'null';
  $handler->display->display_options['arguments']['null']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['null']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['null']['specify_validation'] = TRUE;
  /* Contextual filter: Global: Null */
  $handler->display->display_options['arguments']['null_1']['id'] = 'null_1';
  $handler->display->display_options['arguments']['null_1']['table'] = 'views';
  $handler->display->display_options['arguments']['null_1']['field'] = 'null';
  $handler->display->display_options['arguments']['null_1']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['null_1']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['null_1']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['null_1']['summary_options']['items_per_page'] = '25';
  /* Filter criterion: Content: Published or admin */
  $handler->display->display_options['filters']['status_extra']['id'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['table'] = 'node';
  $handler->display->display_options['filters']['status_extra']['field'] = 'status_extra';
  $handler->display->display_options['filters']['status_extra']['group'] = '0';
  $handler->display->display_options['filters']['status_extra']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_event' => 'gsa_event',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'event-registration/confirm';
  $export['gsa_event_register_confirm'] = $view;

  $view = new view();
  $view->name = 'gsa_events';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'node';
  $view->human_name = 'GSA Events';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Upcoming GSA Events';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '10';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'field_event_date' => 'field_event_date',
    'title' => 'title',
    'field_event_location' => 'field_event_location',
  );
  $handler->display->display_options['style_options']['default'] = '-1';
  $handler->display->display_options['style_options']['info'] = array(
    'field_event_date' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_event_location' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => 'views-align-left',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_event_date']['id'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['fields']['field_event_date']['field'] = 'field_event_date';
  $handler->display->display_options['fields']['field_event_date']['label'] = 'Date';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Event';
  $handler->display->display_options['fields']['title']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['title']['alter']['ellipsis'] = FALSE;
  /* Field: Broken/missing handler */
  $handler->display->display_options['fields']['field_event_location']['id'] = 'field_event_location';
  $handler->display->display_options['fields']['field_event_location']['table'] = 'field_data_field_event_location';
  $handler->display->display_options['fields']['field_event_location']['field'] = 'field_event_location';
  $handler->display->display_options['fields']['field_event_location']['label'] = 'Location';
  /* Sort criterion: Broken/missing handler */
  $handler->display->display_options['sorts']['field_event_date_value']['id'] = 'field_event_date_value';
  $handler->display->display_options['sorts']['field_event_date_value']['table'] = 'field_data_field_event_date';
  $handler->display->display_options['sorts']['field_event_date_value']['field'] = 'field_event_date_value';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = 1;
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'event' => 'event',
  );

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'gsa-events';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'GSA Events';
  $handler->display->display_options['menu']['weight'] = '3';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $handler->display->display_options['menu']['context'] = 0;

  /* Display: Feed */
  $handler = $view->new_display('feed', 'Feed', 'feed');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['pager']['type'] = 'some';
  $handler->display->display_options['style_plugin'] = 'rss';
  $handler->display->display_options['row_plugin'] = 'node_rss';
  $handler->display->display_options['path'] = 'gsa-events.xml';
  $handler->display->display_options['displays'] = array(
    'default' => 'default',
    'page' => 'page',
  );

  /* Display: Block */
  $handler = $view->new_display('block', 'Block', 'block_1');
  $handler->display->display_options['defaults']['title'] = FALSE;
  $handler->display->display_options['title'] = 'Upcoming GSA Events & Training Sessions';
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['style_plugin'] = FALSE;
  $handler->display->display_options['style_plugin'] = 'gmap';
  $handler->display->display_options['style_options']['markertype'] = 'small dblue';
  $handler->display->display_options['style_options']['latfield'] = 'title';
  $handler->display->display_options['style_options']['lonfield'] = 'title';
  $handler->display->display_options['style_options']['markerfield'] = 'title';
  $handler->display->display_options['style_options']['enablermt'] = 0;
  $handler->display->display_options['style_options']['rmtfield'] = 'title';
  $handler->display->display_options['style_options']['tooltipenabled'] = 1;
  $handler->display->display_options['style_options']['tooltipfield'] = 'title';
  $handler->display->display_options['style_options']['bubbletextenabled'] = 1;
  $handler->display->display_options['style_options']['bubbletextfield'] = 'title';
  $handler->display->display_options['defaults']['style_options'] = FALSE;
  $handler->display->display_options['defaults']['row_plugin'] = FALSE;
  $handler->display->display_options['row_plugin'] = 'fields';
  $handler->display->display_options['defaults']['row_options'] = FALSE;
  $export['gsa_events'] = $view;

  return $export;
}
