<?php
/**
 * @file
 * gsa_cpat.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gsa_cpat_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'cpat_messages';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'gsa_cpat_message';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'My replies';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'none';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['grouping'] = '';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'sender_name' => 'sender_name',
    'reviewed' => 'reviewed',
    'timestamp' => 'timestamp',
    'message' => 'message',
  );
  $handler->display->display_options['style_options']['default'] = 'timestamp';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'sender_name' => array(
      'separator' => '',
    ),
    'reviewed' => array(
      'separator' => '',
    ),
    'timestamp' => array(
      'sortable' => 1,
      'separator' => '',
    ),
    'message' => array(
      'separator' => '',
    ),
  );
  $handler->display->display_options['style_options']['order'] = 'desc';
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'There are currently no messages.';
  $handler->display->display_options['empty']['text']['format'] = '1';
  /* Relationship: CTAT messages: Node */
  $handler->display->display_options['relationships']['nid']['id'] = 'nid';
  $handler->display->display_options['relationships']['nid']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['relationships']['nid']['field'] = 'nid';
  /* Relationship: CTAT messages: Sender */
  $handler->display->display_options['relationships']['sender_uid']['id'] = 'sender_uid';
  $handler->display->display_options['relationships']['sender_uid']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['relationships']['sender_uid']['field'] = 'sender_uid';
  /* Field: CTAT messages: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['relationship'] = 'nid';
  $handler->display->display_options['fields']['title']['label'] = 'Post';
  /* Field: CTAT messages: Sender (real name) */
  $handler->display->display_options['fields']['sender_name']['id'] = 'sender_name';
  $handler->display->display_options['fields']['sender_name']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['sender_name']['field'] = 'sender_name';
  $handler->display->display_options['fields']['sender_name']['label'] = 'Name';
  /* Field: CTAT messages: Status */
  $handler->display->display_options['fields']['reviewed']['id'] = 'reviewed';
  $handler->display->display_options['fields']['reviewed']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['reviewed']['field'] = 'reviewed';
  /* Field: CTAT messages: Message date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  /* Field: CTAT messages: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Preview';
  $handler->display->display_options['fields']['message']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['message']['alter']['path'] = 'node/[nid]/message/[mid]';
  $handler->display->display_options['fields']['message']['alter']['max_length'] = '75';
  $handler->display->display_options['fields']['message']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['message']['alter']['trim'] = TRUE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  /* Contextual filter: Content: User posted or commented */
  $handler->display->display_options['arguments']['uid_touch']['id'] = 'uid_touch';
  $handler->display->display_options['arguments']['uid_touch']['table'] = 'node';
  $handler->display->display_options['arguments']['uid_touch']['field'] = 'uid_touch';
  $handler->display->display_options['arguments']['uid_touch']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['uid_touch']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid_touch']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid_touch']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid_touch']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid_touch']['specify_validation'] = TRUE;
  /* Filter criterion: CTAT messages: Status */
  $handler->display->display_options['filters']['reviewed']['id'] = 'reviewed';
  $handler->display->display_options['filters']['reviewed']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['filters']['reviewed']['field'] = 'reviewed';
  $handler->display->display_options['filters']['reviewed']['group'] = '0';
  $handler->display->display_options['filters']['reviewed']['exposed'] = TRUE;
  $handler->display->display_options['filters']['reviewed']['expose']['operator_id'] = 'reviewed_op';
  $handler->display->display_options['filters']['reviewed']['expose']['label'] = 'Status';
  $handler->display->display_options['filters']['reviewed']['expose']['operator'] = 'reviewed_op';
  $handler->display->display_options['filters']['reviewed']['expose']['identifier'] = 'reviewed';

  /* Display: Replies - Group */
  $handler = $view->new_display('page', 'Replies - Group', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Group (group_group) */
  $handler->display->display_options['arguments']['group_group_value']['id'] = 'group_group_value';
  $handler->display->display_options['arguments']['group_group_value']['table'] = 'field_data_group_group';
  $handler->display->display_options['arguments']['group_group_value']['field'] = 'group_group_value';
  $handler->display->display_options['arguments']['group_group_value']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['group_group_value']['default_action'] = 'default';
  $handler->display->display_options['arguments']['group_group_value']['default_argument_type'] = 'node';
  $handler->display->display_options['arguments']['group_group_value']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['group_group_value']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['group_group_value']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['group_group_value']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['group_group_value']['validate']['type'] = 'node';
  $handler->display->display_options['arguments']['group_group_value']['validate_options']['types'] = array(
    'group' => 'group',
  );
  /* Contextual filter: Content: User posted or commented */
  $handler->display->display_options['arguments']['uid_touch']['id'] = 'uid_touch';
  $handler->display->display_options['arguments']['uid_touch']['table'] = 'node';
  $handler->display->display_options['arguments']['uid_touch']['field'] = 'uid_touch';
  $handler->display->display_options['arguments']['uid_touch']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['uid_touch']['default_action'] = 'default';
  $handler->display->display_options['arguments']['uid_touch']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['uid_touch']['default_argument_type'] = 'current_user';
  $handler->display->display_options['arguments']['uid_touch']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['uid_touch']['specify_validation'] = TRUE;
  $handler->display->display_options['path'] = 'node/%/my-replies';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'My replies';
  $handler->display->display_options['menu']['weight'] = '10';

  /* Display: Replies - CPAT */
  $handler = $view->new_display('page', 'Replies - CPAT', 'page_2');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['defaults']['fields'] = FALSE;
  /* Field: CTAT messages: Message ID */
  $handler->display->display_options['fields']['mid']['id'] = 'mid';
  $handler->display->display_options['fields']['mid']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['mid']['field'] = 'mid';
  $handler->display->display_options['fields']['mid']['exclude'] = TRUE;
  /* Field: Content: Nid */
  $handler->display->display_options['fields']['nid']['id'] = 'nid';
  $handler->display->display_options['fields']['nid']['table'] = 'node';
  $handler->display->display_options['fields']['nid']['field'] = 'nid';
  $handler->display->display_options['fields']['nid']['relationship'] = 'nid';
  $handler->display->display_options['fields']['nid']['exclude'] = TRUE;
  /* Field: CTAT messages: Sender (real name) */
  $handler->display->display_options['fields']['sender_name']['id'] = 'sender_name';
  $handler->display->display_options['fields']['sender_name']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['sender_name']['field'] = 'sender_name';
  $handler->display->display_options['fields']['sender_name']['label'] = 'Name';
  /* Field: CTAT messages: Status */
  $handler->display->display_options['fields']['reviewed']['id'] = 'reviewed';
  $handler->display->display_options['fields']['reviewed']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['reviewed']['field'] = 'reviewed';
  /* Field: CTAT messages: Message date */
  $handler->display->display_options['fields']['timestamp']['id'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['timestamp']['field'] = 'timestamp';
  $handler->display->display_options['fields']['timestamp']['label'] = 'Date';
  /* Field: CTAT messages: Message */
  $handler->display->display_options['fields']['message']['id'] = 'message';
  $handler->display->display_options['fields']['message']['table'] = 'gsa_cpat_message';
  $handler->display->display_options['fields']['message']['field'] = 'message';
  $handler->display->display_options['fields']['message']['label'] = 'Preview';
  $handler->display->display_options['fields']['message']['alter']['make_link'] = TRUE;
  $handler->display->display_options['fields']['message']['alter']['path'] = 'node/[nid]/message/[mid]';
  $handler->display->display_options['fields']['message']['alter']['max_length'] = '75';
  $handler->display->display_options['fields']['message']['alter']['strip_tags'] = TRUE;
  $handler->display->display_options['fields']['message']['alter']['trim'] = TRUE;
  $handler->display->display_options['defaults']['arguments'] = FALSE;
  /* Contextual filter: Content: Nid */
  $handler->display->display_options['arguments']['nid']['id'] = 'nid';
  $handler->display->display_options['arguments']['nid']['table'] = 'node';
  $handler->display->display_options['arguments']['nid']['field'] = 'nid';
  $handler->display->display_options['arguments']['nid']['relationship'] = 'nid';
  $handler->display->display_options['arguments']['nid']['exception']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['title_enable'] = TRUE;
  $handler->display->display_options['arguments']['nid']['title'] = 'Replies to %1';
  $handler->display->display_options['arguments']['nid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['nid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['nid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['nid']['validate']['type'] = 'node';
  $handler->display->display_options['path'] = 'node/%/replies';
  $handler->display->display_options['menu']['type'] = 'tab';
  $handler->display->display_options['menu']['title'] = 'Replies';
  $handler->display->display_options['menu']['weight'] = '10';
  $export['cpat_messages'] = $view;

  $view = new view();
  $view->name = 'cpat_opportunities';
  $view->description = '';
  $view->tag = '';
  $view->base_table = 'node';
  $view->human_name = '';
  $view->core = 0;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Defaults */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->display->display_options['title'] = 'Search Opportunities';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['query']['options']['query_comment'] = FALSE;
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'none';
  $handler->display->display_options['style_plugin'] = 'table';
  $handler->display->display_options['style_options']['columns'] = array(
    'title' => 'title',
    'field_cpat_category' => 'field_cpat_category',
    'field_cpat_company' => 'field_cpat_company',
    'field_cpat_contract' => 'field_cpat_contract',
    'changed' => 'changed',
  );
  $handler->display->display_options['style_options']['default'] = 'changed';
  $handler->display->display_options['style_options']['info'] = array(
    'title' => array(
      'sortable' => 1,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cpat_category' => array(
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cpat_company' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'field_cpat_contract' => array(
      'sortable' => 0,
      'default_sort_order' => 'asc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
    'changed' => array(
      'sortable' => 1,
      'default_sort_order' => 'desc',
      'align' => '',
      'separator' => '',
      'empty_column' => 0,
    ),
  );
  $handler->display->display_options['style_options']['sticky'] = TRUE;
  /* No results behavior: Global: Text area */
  $handler->display->display_options['empty']['text']['id'] = 'area';
  $handler->display->display_options['empty']['text']['table'] = 'views';
  $handler->display->display_options['empty']['text']['field'] = 'area';
  $handler->display->display_options['empty']['text']['content'] = 'There are currently no opportunities.';
  $handler->display->display_options['empty']['text']['format'] = '1';
  /* Field: Content: Title */
  $handler->display->display_options['fields']['title']['id'] = 'title';
  $handler->display->display_options['fields']['title']['table'] = 'node';
  $handler->display->display_options['fields']['title']['field'] = 'title';
  $handler->display->display_options['fields']['title']['label'] = 'Subject';
  /* Field: Content: Categories */
  $handler->display->display_options['fields']['field_cpat_category']['id'] = 'field_cpat_category';
  $handler->display->display_options['fields']['field_cpat_category']['table'] = 'field_data_field_cpat_category';
  $handler->display->display_options['fields']['field_cpat_category']['field'] = 'field_cpat_category';
  /* Field: Content: Company Name */
  $handler->display->display_options['fields']['field_cpat_company']['id'] = 'field_cpat_company';
  $handler->display->display_options['fields']['field_cpat_company']['table'] = 'field_data_field_cpat_company';
  $handler->display->display_options['fields']['field_cpat_company']['field'] = 'field_cpat_company';
  $handler->display->display_options['fields']['field_cpat_company']['label'] = 'Company';
  /* Field: Content: Contract Number */
  $handler->display->display_options['fields']['field_cpat_contract']['id'] = 'field_cpat_contract';
  $handler->display->display_options['fields']['field_cpat_contract']['table'] = 'field_data_field_cpat_contract';
  $handler->display->display_options['fields']['field_cpat_contract']['field'] = 'field_cpat_contract';
  $handler->display->display_options['fields']['field_cpat_contract']['exclude'] = TRUE;
  /* Field: Content: Updated date */
  $handler->display->display_options['fields']['changed']['id'] = 'changed';
  $handler->display->display_options['fields']['changed']['table'] = 'node';
  $handler->display->display_options['fields']['changed']['field'] = 'changed';
  $handler->display->display_options['fields']['changed']['label'] = 'Updated';
  $handler->display->display_options['fields']['changed']['date_format'] = 'short';
  /* Sort criterion: Search: Score */
  $handler->display->display_options['sorts']['score']['id'] = 'score';
  $handler->display->display_options['sorts']['score']['table'] = 'search_index';
  $handler->display->display_options['sorts']['score']['field'] = 'score';
  $handler->display->display_options['sorts']['score']['order'] = 'DESC';
  /* Contextual filter: Field: Groups audience (group_audience:gid) */
  $handler->display->display_options['arguments']['group_audience_gid']['id'] = 'group_audience_gid';
  $handler->display->display_options['arguments']['group_audience_gid']['table'] = 'field_data_group_audience';
  $handler->display->display_options['arguments']['group_audience_gid']['field'] = 'group_audience_gid';
  $handler->display->display_options['arguments']['group_audience_gid']['default_action'] = 'not found';
  $handler->display->display_options['arguments']['group_audience_gid']['default_argument_type'] = 'fixed';
  $handler->display->display_options['arguments']['group_audience_gid']['summary']['number_of_records'] = '0';
  $handler->display->display_options['arguments']['group_audience_gid']['summary']['format'] = 'default_summary';
  $handler->display->display_options['arguments']['group_audience_gid']['summary_options']['items_per_page'] = '25';
  $handler->display->display_options['arguments']['group_audience_gid']['specify_validation'] = TRUE;
  $handler->display->display_options['arguments']['group_audience_gid']['validate']['type'] = 'php';
  $handler->display->display_options['arguments']['group_audience_gid']['validate_options']['code'] = '$group = og_get_group(\'node\', $argument);
if(!$group->gid) return false;
$handler->argument = $group->gid;
return true;';
  /* Filter criterion: Content: Published */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'node';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = '0';
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Type */
  $handler->display->display_options['filters']['type']['id'] = 'type';
  $handler->display->display_options['filters']['type']['table'] = 'node';
  $handler->display->display_options['filters']['type']['field'] = 'type';
  $handler->display->display_options['filters']['type']['value'] = array(
    'gsa_cpat' => 'gsa_cpat',
  );
  $handler->display->display_options['filters']['type']['group'] = '0';
  $handler->display->display_options['filters']['type']['expose']['operator'] = FALSE;
  /* Filter criterion: Content: Categories (field_cpat_category) */
  $handler->display->display_options['filters']['field_cpat_category_value']['id'] = 'field_cpat_category_value';
  $handler->display->display_options['filters']['field_cpat_category_value']['table'] = 'field_data_field_cpat_category';
  $handler->display->display_options['filters']['field_cpat_category_value']['field'] = 'field_cpat_category_value';
  $handler->display->display_options['filters']['field_cpat_category_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cpat_category_value']['expose']['operator_id'] = 'field_cpat_category_value_op';
  $handler->display->display_options['filters']['field_cpat_category_value']['expose']['label'] = 'Category';
  $handler->display->display_options['filters']['field_cpat_category_value']['expose']['operator'] = 'field_cpat_category_value_op';
  $handler->display->display_options['filters']['field_cpat_category_value']['expose']['identifier'] = 'field_cpat_category_value';
  /* Filter criterion: Content: Company Name (field_cpat_company) */
  $handler->display->display_options['filters']['field_cpat_company_value']['id'] = 'field_cpat_company_value';
  $handler->display->display_options['filters']['field_cpat_company_value']['table'] = 'field_data_field_cpat_company';
  $handler->display->display_options['filters']['field_cpat_company_value']['field'] = 'field_cpat_company_value';
  $handler->display->display_options['filters']['field_cpat_company_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_cpat_company_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cpat_company_value']['expose']['operator_id'] = 'field_cpat_company_value_op';
  $handler->display->display_options['filters']['field_cpat_company_value']['expose']['label'] = 'Company';
  $handler->display->display_options['filters']['field_cpat_company_value']['expose']['operator'] = 'field_cpat_company_value_op';
  $handler->display->display_options['filters']['field_cpat_company_value']['expose']['identifier'] = 'field_cpat_company_value';
  /* Filter criterion: Content: Contract Number (field_cpat_contract) */
  $handler->display->display_options['filters']['field_cpat_contract_value']['id'] = 'field_cpat_contract_value';
  $handler->display->display_options['filters']['field_cpat_contract_value']['table'] = 'field_data_field_cpat_contract';
  $handler->display->display_options['filters']['field_cpat_contract_value']['field'] = 'field_cpat_contract_value';
  $handler->display->display_options['filters']['field_cpat_contract_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['field_cpat_contract_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['field_cpat_contract_value']['expose']['operator_id'] = 'field_cpat_contract_value_op';
  $handler->display->display_options['filters']['field_cpat_contract_value']['expose']['label'] = 'Contract';
  $handler->display->display_options['filters']['field_cpat_contract_value']['expose']['operator'] = 'field_cpat_contract_value_op';
  $handler->display->display_options['filters']['field_cpat_contract_value']['expose']['identifier'] = 'field_cpat_contract_value';
  /* Filter criterion: Content: Body (body) */
  $handler->display->display_options['filters']['body_value']['id'] = 'body_value';
  $handler->display->display_options['filters']['body_value']['table'] = 'field_data_body';
  $handler->display->display_options['filters']['body_value']['field'] = 'body_value';
  $handler->display->display_options['filters']['body_value']['operator'] = 'contains';
  $handler->display->display_options['filters']['body_value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['body_value']['expose']['operator_id'] = 'body_value_op';
  $handler->display->display_options['filters']['body_value']['expose']['label'] = 'Description contains';
  $handler->display->display_options['filters']['body_value']['expose']['operator'] = 'body_value_op';
  $handler->display->display_options['filters']['body_value']['expose']['identifier'] = 'body_value';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'node/%/cpat-opportunities';
  $handler->display->display_options['menu']['title'] = 'Opportunities';
  $handler->display->display_options['menu']['weight'] = '6';
  $handler->display->display_options['menu']['context'] = 0;
  $export['cpat_opportunities'] = $view;

  return $export;
}
