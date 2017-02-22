<?php
/**
 * @file
 * gsa_members_page.views_default.inc
 */

/**
 * Implements hook_views_default_views().
 */
function gsa_members_page_views_default_views() {
  $export = array();

  $view = new view();
  $view->name = 'members';
  $view->description = '';
  $view->tag = 'default';
  $view->base_table = 'users';
  $view->human_name = 'Members';
  $view->core = 7;
  $view->api_version = '3.0';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */

  /* Display: Master */
  $handler = $view->new_display('default', 'Master', 'default');
  $handler->display->display_options['title'] = 'Members';
  $handler->display->display_options['use_more_always'] = FALSE;
  $handler->display->display_options['access']['type'] = 'perm';
  $handler->display->display_options['access']['perm'] = 'access user profiles';
  $handler->display->display_options['cache']['type'] = 'none';
  $handler->display->display_options['query']['type'] = 'views_query';
  $handler->display->display_options['exposed_form']['type'] = 'basic';
  $handler->display->display_options['exposed_form']['options']['submit_button'] = 'Search';
  $handler->display->display_options['exposed_form']['options']['reset_button'] = TRUE;
  $handler->display->display_options['pager']['type'] = 'full';
  $handler->display->display_options['pager']['options']['items_per_page'] = '16';
  $handler->display->display_options['pager']['options']['offset'] = '0';
  $handler->display->display_options['pager']['options']['id'] = '0';
  $handler->display->display_options['style_plugin'] = 'grid';
  $handler->display->display_options['row_plugin'] = 'fields';
  /* Field: User: Picture */
  $handler->display->display_options['fields']['picture']['id'] = 'picture';
  $handler->display->display_options['fields']['picture']['table'] = 'users';
  $handler->display->display_options['fields']['picture']['field'] = 'picture';
  $handler->display->display_options['fields']['picture']['label'] = '';
  $handler->display->display_options['fields']['picture']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['picture']['image_style'] = 'member_list_image';
  /* Field: User: Name */
  $handler->display->display_options['fields']['name']['id'] = 'name';
  $handler->display->display_options['fields']['name']['table'] = 'users';
  $handler->display->display_options['fields']['name']['field'] = 'name';
  $handler->display->display_options['fields']['name']['label'] = '';
  $handler->display->display_options['fields']['name']['alter']['word_boundary'] = FALSE;
  $handler->display->display_options['fields']['name']['alter']['ellipsis'] = FALSE;
  /* Field: Profile: Personal information: First name */
  $handler->display->display_options['fields']['value_2']['id'] = 'value_2';
  $handler->display->display_options['fields']['value_2']['table'] = 'profile_value_profile_name';
  $handler->display->display_options['fields']['value_2']['field'] = 'value';
  $handler->display->display_options['fields']['value_2']['label'] = '';
  $handler->display->display_options['fields']['value_2']['exclude'] = TRUE;
  $handler->display->display_options['fields']['value_2']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value_2']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_2']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['value_2']['link_to_user'] = FALSE;
  /* Field: Profile: Personal information: Last name */
  $handler->display->display_options['fields']['value_3']['id'] = 'value_3';
  $handler->display->display_options['fields']['value_3']['table'] = 'profile_value_profile_last_name';
  $handler->display->display_options['fields']['value_3']['field'] = 'value';
  $handler->display->display_options['fields']['value_3']['label'] = '';
  $handler->display->display_options['fields']['value_3']['alter']['alter_text'] = TRUE;
  $handler->display->display_options['fields']['value_3']['alter']['text'] = '[value_2] [value_3]';
  $handler->display->display_options['fields']['value_3']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value_3']['element_default_classes'] = FALSE;
  $handler->display->display_options['fields']['value_3']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['value_3']['link_to_user'] = FALSE;
  /* Field: Profile: Work information: Job title */
  $handler->display->display_options['fields']['value']['id'] = 'value';
  $handler->display->display_options['fields']['value']['table'] = 'profile_value_profile_job';
  $handler->display->display_options['fields']['value']['field'] = 'value';
  $handler->display->display_options['fields']['value']['label'] = '';
  $handler->display->display_options['fields']['value']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['value']['link_to_user'] = FALSE;
  /* Field: Profile: Work information: Organization */
  $handler->display->display_options['fields']['value_1']['id'] = 'value_1';
  $handler->display->display_options['fields']['value_1']['table'] = 'profile_value_profile_organization';
  $handler->display->display_options['fields']['value_1']['field'] = 'value';
  $handler->display->display_options['fields']['value_1']['label'] = '';
  $handler->display->display_options['fields']['value_1']['alter']['text'] = '[value], [value_1]';
  $handler->display->display_options['fields']['value_1']['element_label_colon'] = FALSE;
  $handler->display->display_options['fields']['value_1']['hide_empty'] = TRUE;
  $handler->display->display_options['fields']['value_1']['link_to_user'] = FALSE;
  /* Field: Profile: Personal information: Location */
  $handler->display->display_options['fields']['value_4']['id'] = 'value_4';
  $handler->display->display_options['fields']['value_4']['table'] = 'profile_value_profile_location';
  $handler->display->display_options['fields']['value_4']['field'] = 'value';
  $handler->display->display_options['fields']['value_4']['label'] = '';
  $handler->display->display_options['fields']['value_4']['element_label_colon'] = FALSE;
  /* Sort criterion: Profile: Personal information: Last name */
  $handler->display->display_options['sorts']['value_1']['id'] = 'value_1';
  $handler->display->display_options['sorts']['value_1']['table'] = 'profile_value_profile_last_name';
  $handler->display->display_options['sorts']['value_1']['field'] = 'value';
  /* Sort criterion: Profile: Personal information: First name */
  $handler->display->display_options['sorts']['value']['id'] = 'value';
  $handler->display->display_options['sorts']['value']['table'] = 'profile_value_profile_name';
  $handler->display->display_options['sorts']['value']['field'] = 'value';
  /* Filter criterion: User: Active */
  $handler->display->display_options['filters']['status']['id'] = 'status';
  $handler->display->display_options['filters']['status']['table'] = 'users';
  $handler->display->display_options['filters']['status']['field'] = 'status';
  $handler->display->display_options['filters']['status']['value'] = '1';
  $handler->display->display_options['filters']['status']['group'] = 1;
  $handler->display->display_options['filters']['status']['expose']['operator'] = FALSE;
  /* Filter criterion: Profile: Personal information: First name */
  $handler->display->display_options['filters']['value']['id'] = 'value';
  $handler->display->display_options['filters']['value']['table'] = 'profile_value_profile_name';
  $handler->display->display_options['filters']['value']['field'] = 'value';
  $handler->display->display_options['filters']['value']['operator'] = 'contains';
  $handler->display->display_options['filters']['value']['group'] = 1;
  $handler->display->display_options['filters']['value']['exposed'] = TRUE;
  $handler->display->display_options['filters']['value']['expose']['operator_id'] = 'value_op';
  $handler->display->display_options['filters']['value']['expose']['label'] = 'First Name';
  $handler->display->display_options['filters']['value']['expose']['operator'] = 'value_op';
  $handler->display->display_options['filters']['value']['expose']['identifier'] = 'firstname';
  /* Filter criterion: Profile: Personal information: Last name */
  $handler->display->display_options['filters']['value_1']['id'] = 'value_1';
  $handler->display->display_options['filters']['value_1']['table'] = 'profile_value_profile_last_name';
  $handler->display->display_options['filters']['value_1']['field'] = 'value';
  $handler->display->display_options['filters']['value_1']['operator'] = 'contains';
  $handler->display->display_options['filters']['value_1']['group'] = 1;
  $handler->display->display_options['filters']['value_1']['exposed'] = TRUE;
  $handler->display->display_options['filters']['value_1']['expose']['operator_id'] = 'value_1_op';
  $handler->display->display_options['filters']['value_1']['expose']['label'] = 'Last name';
  $handler->display->display_options['filters']['value_1']['expose']['operator'] = 'value_1_op';
  $handler->display->display_options['filters']['value_1']['expose']['identifier'] = 'lastname';
  /* Filter criterion: Profile: Work information: Organization */
  $handler->display->display_options['filters']['value_3']['id'] = 'value_3';
  $handler->display->display_options['filters']['value_3']['table'] = 'profile_value_profile_organization';
  $handler->display->display_options['filters']['value_3']['field'] = 'value';
  $handler->display->display_options['filters']['value_3']['operator'] = 'contains';
  $handler->display->display_options['filters']['value_3']['group'] = 1;
  $handler->display->display_options['filters']['value_3']['exposed'] = TRUE;
  $handler->display->display_options['filters']['value_3']['expose']['operator_id'] = 'value_3_op';
  $handler->display->display_options['filters']['value_3']['expose']['label'] = 'Organization';
  $handler->display->display_options['filters']['value_3']['expose']['operator'] = 'value_3_op';
  $handler->display->display_options['filters']['value_3']['expose']['identifier'] = 'organization';
  /* Filter criterion: Profile: Personal information: Location */
  $handler->display->display_options['filters']['value_2']['id'] = 'value_2';
  $handler->display->display_options['filters']['value_2']['table'] = 'profile_value_profile_location';
  $handler->display->display_options['filters']['value_2']['field'] = 'value';
  $handler->display->display_options['filters']['value_2']['group'] = 1;
  $handler->display->display_options['filters']['value_2']['exposed'] = TRUE;
  $handler->display->display_options['filters']['value_2']['expose']['operator_id'] = 'value_2_op';
  $handler->display->display_options['filters']['value_2']['expose']['label'] = 'Location';
  $handler->display->display_options['filters']['value_2']['expose']['operator'] = 'value_2_op';
  $handler->display->display_options['filters']['value_2']['expose']['identifier'] = 'location';

  /* Display: Page */
  $handler = $view->new_display('page', 'Page', 'page');
  $handler->display->display_options['defaults']['hide_admin_links'] = FALSE;
  $handler->display->display_options['path'] = 'members';
  $handler->display->display_options['menu']['type'] = 'normal';
  $handler->display->display_options['menu']['title'] = 'Members';
  $handler->display->display_options['menu']['name'] = 'main-menu';
  $export['members'] = $view;

  return $export;
}
