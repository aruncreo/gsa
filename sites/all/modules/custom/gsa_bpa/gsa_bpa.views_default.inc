<?php

/**
 * Implementation of hook_views_default_views().
 */
function gsa_bpa_views_default_views() {
  $views = array();

  // Exported view: gsa_bpa_listings
  $view = new view;
  $view->name = 'gsa_bpa_listings';
  $view->description = 'BPA listing data.';
  $view->tag = '';
  $view->base_table = 'node';
  $view->core = 0;
  $view->api_version = '2';
  $view->disabled = FALSE; /* Edit this to true to make a default view disabled initially */
  $handler = $view->new_display('default', 'Defaults', 'default');
  $handler->override_option('fields', array(
    'field_bpa_listing_product_value' => array(
      'label' => 'Product or service',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_product_value',
      'table' => 'node_data_field_bpa_listing_product',
      'field' => 'field_bpa_listing_product_value',
      'relationship' => 'none',
    ),
    'field_bpa_listing_vendor_name_value' => array(
      'label' => 'Vendor Name',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_vendor_name_value',
      'table' => 'node_data_field_bpa_listing_vendor_name',
      'field' => 'field_bpa_listing_vendor_name_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_bpa_listing_terms_url' => array(
      'label' => 'View Terms and Conditions',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_bpa_listing_terms_url',
      'table' => 'node_data_field_bpa_listing_terms',
      'field' => 'field_bpa_listing_terms_url',
      'relationship' => 'none',
    ),
    'title' => array(
      'label' => 'BPA Number',
      'alter' => array(
        'alter_text' => 0,
        'text' => '<a href="[field_bpa_listing_terms_url]">[title]</a>[field_bpa_listing_url_url]',
        'make_link' => 1,
        'path' => '[field_bpa_listing_terms_url]',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'exclude' => 0,
      'id' => 'title',
      'table' => 'node',
      'field' => 'title',
      'relationship' => 'none',
    ),
    'field_bpa_listing_url_url' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<span class="bpa-view-items-link">[field_bpa_listing_url_url]</span>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 1,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'label',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_url_url',
      'table' => 'node_data_field_bpa_listing_url',
      'field' => 'field_bpa_listing_url_url',
      'relationship' => 'none',
    ),
    'field_bpa_listing_end_date_value' => array(
      'label' => 'End Date',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'custom',
      'format' => 'short',
      'multiple' => array(
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_to' => '',
        'group' => '',
      ),
      'repeat' => array(
        'show_repeat_rule' => '',
      ),
      'fromto' => array(
        'fromto' => 'both',
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_end_date_value',
      'table' => 'node_data_field_bpa_listing_end_date',
      'field' => 'field_bpa_listing_end_date_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_bpa_listing_socioeconomic_value' => array(
      'label' => 'Socio-economic',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 1,
        'path' => 'blog/utilizing-set-aside-special-item-numbers-sins-small-business',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => 1,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => 0,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_socioeconomic_value',
      'table' => 'node_data_field_bpa_listing_socioeconomic',
      'field' => 'field_bpa_listing_socioeconomic_value',
      'relationship' => 'none',
    ),
    'field_bpa_listing_authorized_value_1' => array(
      'label' => '',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 1,
        'max_length' => '80',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'none',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 1,
      'id' => 'field_bpa_listing_authorized_value_1',
      'table' => 'node_data_field_bpa_listing_authorized',
      'field' => 'field_bpa_listing_authorized_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_bpa_listing_authorized_value' => array(
      'label' => 'Authorized Users',
      'alter' => array(
        'alter_text' => 1,
        'text' => '<a title="[field_bpa_listing_authorized_value]">[field_bpa_listing_authorized_value_1]</a>',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '80',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_authorized_value',
      'table' => 'node_data_field_bpa_listing_authorized',
      'field' => 'field_bpa_listing_authorized_value',
      'relationship' => 'none',
      'override' => array(
        'button' => 'Override',
      ),
    ),
    'field_bpa_listing_poc_email' => array(
      'label' => 'Agency POC',
      'alter' => array(
        'alter_text' => 0,
        'text' => '',
        'make_link' => 0,
        'path' => '',
        'link_class' => '',
        'alt' => '',
        'prefix' => '',
        'suffix' => '',
        'target' => '',
        'help' => '',
        'trim' => 0,
        'max_length' => '',
        'word_boundary' => 1,
        'ellipsis' => 1,
        'html' => 0,
        'strip_tags' => 0,
      ),
      'empty' => '',
      'hide_empty' => 0,
      'empty_zero' => 0,
      'link_to_node' => 0,
      'label_type' => 'widget',
      'format' => 'default',
      'multiple' => array(
        'group' => TRUE,
        'multiple_number' => '',
        'multiple_from' => '',
        'multiple_reversed' => FALSE,
      ),
      'exclude' => 0,
      'id' => 'field_bpa_listing_poc_email',
      'table' => 'node_data_field_bpa_listing_poc',
      'field' => 'field_bpa_listing_poc_email',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('sorts', array(
    'nid' => array(
      'order' => 'ASC',
      'id' => 'nid',
      'table' => 'node',
      'field' => 'nid',
      'relationship' => 'none',
    ),
  ));
  $handler->override_option('arguments', array(
    'group_nid' => array(
      'default_action' => 'not found',
      'style_plugin' => 'default_summary',
      'style_options' => array(),
      'wildcard' => 'all',
      'wildcard_substitution' => 'All',
      'title' => '',
      'breadcrumb' => '',
      'default_argument_type' => 'fixed',
      'default_argument' => '',
      'validate_type' => 'og_group_types',
      'validate_fail' => 'not found',
      'break_phrase' => 0,
      'not' => 0,
      'id' => 'group_nid',
      'table' => 'og_ancestry',
      'field' => 'group_nid',
      'validate_user_argument_type' => 'uid',
      'validate_user_roles' => array(
        2 => 0,
        10 => 0,
        7 => 0,
        3 => 0,
        8 => 0,
        9 => 0,
        6 => 0,
        5 => 0,
      ),
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'default_options_div_prefix' => '',
      'default_argument_fixed' => '',
      'default_argument_user' => 0,
      'default_argument_php' => '',
      'validate_argument_node_type' => array(
        'blog' => 0,
        'poll' => 0,
        'discussion' => 0,
        'document' => 0,
        'event' => 0,
        'wiki' => 0,
        'gallery' => 0,
        'gsa_event' => 0,
        'slider' => 0,
        'gsa_webinar' => 0,
        'group' => 0,
        'notice' => 0,
        'page' => 0,
        'bpa_listing' => 0,
      ),
      'validate_argument_node_access' => 0,
      'validate_argument_nid_type' => 'nid',
      'validate_argument_vocabulary' => array(
        2 => 0,
        1 => 0,
        3 => 0,
      ),
      'validate_argument_type' => 'tid',
      'validate_argument_transform' => 0,
      'validate_user_restrict_roles' => 0,
      'validate_argument_node_flag_name' => '*relationship*',
      'validate_argument_node_flag_test' => 'flaggable',
      'validate_argument_node_flag_id_type' => 'id',
      'validate_argument_user_flag_name' => '*relationship*',
      'validate_argument_user_flag_test' => 'flaggable',
      'validate_argument_user_flag_id_type' => 'id',
      'validate_argument_is_member' => 'OG_VIEWS_DO_NOT_VALIDATE_MEMBERSHIP',
      'validate_argument_group_node_type' => array(
        'group' => 0,
      ),
      'validate_argument_php' => '',
    ),
  ));
  $handler->override_option('filters', array(
    'type' => array(
      'operator' => 'in',
      'value' => array(
        'bpa_listing' => 'bpa_listing',
      ),
      'group' => '0',
      'exposed' => FALSE,
      'expose' => array(
        'operator' => FALSE,
        'label' => '',
      ),
      'id' => 'type',
      'table' => 'node',
      'field' => 'type',
      'relationship' => 'none',
    ),
    'field_bpa_listing_end_date_value' => array(
      'operator' => 'between',
      'value' => array(
        'value' => NULL,
        'min' => NULL,
        'max' => NULL,
        'default_date' => '',
        'default_to_date' => '',
      ),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'field_bpa_listing_end_date_value_op',
        'identifier' => 'field_bpa_listing_end_date_value',
        'label' => 'End Date',
        'optional' => 1,
        'remember' => 0,
      ),
      'date_fields' => array(
        'node_data_field_bpa_listing_end_date.field_bpa_listing_end_date_value' => 'node_data_field_bpa_listing_end_date.field_bpa_listing_end_date_value',
      ),
      'date_method' => 'OR',
      'granularity' => 'day',
      'form_type' => 'date_popup',
      'default_date' => '',
      'default_to_date' => '',
      'year_range' => '-3:+3',
      'id' => 'field_bpa_listing_end_date_value',
      'table' => 'node_data_field_bpa_listing_end_date',
      'field' => 'field_bpa_listing_end_date_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_bpa_listing_product_value' => array(
      'operator' => 'allwords',
      'value' => '',
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'field_bpa_listing_product_value_op',
        'identifier' => 'field_bpa_listing_product_value',
        'label' => 'Product or service',
        'optional' => 1,
        'remember' => 0,
      ),
      'case' => 1,
      'id' => 'field_bpa_listing_product_value',
      'table' => 'node_data_field_bpa_listing_product',
      'field' => 'field_bpa_listing_product_value',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
    ),
    'field_bpa_listing_socioeconomic_value_many_to_one' => array(
      'operator' => 'or',
      'value' => array(),
      'group' => '0',
      'exposed' => TRUE,
      'expose' => array(
        'use_operator' => 0,
        'operator' => 'field_bpa_listing_socioeconomic_value_many_to_one_op',
        'identifier' => 'field_bpa_listing_socioeconomic_value_many_to_one',
        'label' => 'Socio-economic',
        'optional' => 1,
        'single' => 0,
        'remember' => 0,
        'reduce' => 0,
      ),
      'id' => 'field_bpa_listing_socioeconomic_value_many_to_one',
      'table' => 'node_data_field_bpa_listing_socioeconomic',
      'field' => 'field_bpa_listing_socioeconomic_value_many_to_one',
      'override' => array(
        'button' => 'Override',
      ),
      'relationship' => 'none',
      'reduce_duplicates' => 0,
    ),
  ));
  $handler->override_option('access', array(
    'type' => 'none',
  ));
  $handler->override_option('cache', array(
    'type' => 'none',
  ));
  $handler->override_option('items_per_page', 20);
  $handler->override_option('use_pager', '1');
  $handler->override_option('style_plugin', 'table');
  $handler->override_option('style_options', array(
    'grouping' => '',
    'override' => 1,
    'sticky' => 0,
    'order' => 'asc',
    'columns' => array(
      'field_bpa_listing_product_value' => 'field_bpa_listing_product_value',
      'field_bpa_listing_terms_url' => 'field_bpa_listing_terms_url',
      'title' => 'title',
      'field_bpa_listing_url_url' => 'title',
      'field_bpa_listing_end_date_value' => 'field_bpa_listing_end_date_value',
      'field_bpa_listing_vendor_name_value' => 'field_bpa_listing_vendor_name_value',
      'field_bpa_listing_socioeconomic_value' => 'field_bpa_listing_socioeconomic_value',
      'field_bpa_listing_authorized_value_1' => 'field_bpa_listing_authorized_value_1',
      'field_bpa_listing_authorized_value' => 'field_bpa_listing_authorized_value',
      'field_bpa_listing_poc_email' => 'field_bpa_listing_poc_email',
    ),
    'info' => array(
      'field_bpa_listing_product_value' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_bpa_listing_terms_url' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'title' => array(
        'sortable' => 1,
        'separator' => '<br />',
      ),
      'field_bpa_listing_url_url' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_bpa_listing_end_date_value' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_bpa_listing_vendor_name_value' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_bpa_listing_socioeconomic_value' => array(
        'separator' => '',
      ),
      'field_bpa_listing_authorized_value_1' => array(
        'sortable' => 0,
        'separator' => '',
      ),
      'field_bpa_listing_authorized_value' => array(
        'sortable' => 1,
        'separator' => '',
      ),
      'field_bpa_listing_poc_email' => array(
        'sortable' => 1,
        'separator' => '',
      ),
    ),
    'default' => 'field_bpa_listing_end_date_value',
  ));
  $handler = $view->new_display('page', 'Page', 'page_1');
  $handler->override_option('path', 'node/%/bpa-data');
  $handler->override_option('menu', array(
    'type' => 'tab',
    'title' => 'BPA Data',
    'description' => '',
    'weight' => '30',
    'name' => 'navigation',
  ));
  $handler->override_option('tab_options', array(
    'type' => 'none',
    'title' => '',
    'description' => '',
    'weight' => 0,
    'name' => 'navigation',
  ));

  $views[$view->name] = $view;

  return $views;
}
