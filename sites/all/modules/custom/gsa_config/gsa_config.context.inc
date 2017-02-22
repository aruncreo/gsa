<?php
/**
 * @file
 * gsa_config.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gsa_config_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-global-global';
  $context->description = 'Show on every page';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        0 => '1',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-user_meta-block_1' => array(
          'module' => 'views',
          'delta' => 'user_meta-block_1',
          'weight' => 47,
          'region' => 'header',
          'status' => '0',
          'label' => 'User meta info',
          'type' => 'context_ui',
          'bid' => 'views_user_meta-block_1',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show on every page');
  $export['context_ui-global-global'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-content-feeds';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_feed' => 'group_feed',
        'group_feed:page_1' => 'group_feed:page_1',
        'group_feed_item' => 'group_feed_item',
        'group_feed_item:page_1' => 'group_feed_item:page_1',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_information-block_1' => array(
          'module' => 'views',
          'delta' => 'group_information-block_1',
          'region' => 'sidebar_right',
          'weight' => '-58',
        ),
        'views-group_events_block-block_1' => array(
          'module' => 'views',
          'delta' => 'group_events_block-block_1',
          'region' => 'sidebar_right',
          'weight' => '-56',
        ),
        'views-gsa_og_members-block_2' => array(
          'module' => 'views',
          'delta' => 'gsa_og_members-block_2',
          'region' => 'sidebar_right',
          'weight' => '-10',
        ),
        'gsa_group_page-groupmenu' => array(
          'module' => 'gsa_group_page',
          'delta' => 'groupmenu',
          'region' => 'banner3',
          'weight' => '-10',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['context_ui-group-content-feeds'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-gsa-global';
  $context->description = 'Show on every page';
  $context->tag = '';
  $context->conditions = array(
    'sitewide' => array(
      'values' => array(
        0 => '1',
      ),
      'options' => array(),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'user-0' => array(
          'module' => 'user',
          'delta' => '0',
          'weight' => 1,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'User login',
          'type' => 'context_ui',
        ),
        'gsa_config-0' => array(
          'module' => 'gsa_config',
          'delta' => '0',
          'weight' => 2,
          'region' => 'sidebar_last',
          'status' => '0',
          'label' => 'Join now!',
          'type' => 'context_ui',
        ),
        'views-user_meta-block_1' => array(
          'module' => 'views',
          'delta' => 'user_meta-block_1',
          'weight' => 49,
          'region' => 'header',
          'status' => '0',
          'label' => 'User meta info',
          'type' => 'context_ui',
        ),
        'menu-menu-footer' => array(
          'module' => 'menu',
          'delta' => 'menu-footer',
          'weight' => 49,
          'region' => 'footer',
          'status' => '0',
          'label' => 'Footer links',
          'type' => 'context_ui',
        ),
        'menu-primary-links' => array(
          'module' => 'menu',
          'delta' => 'primary-links',
          'weight' => 50,
          'region' => 'footer',
          'status' => '0',
          'label' => 'Primary links',
          'type' => 'context_ui',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Show on every page');
  $export['context_ui-gsa-global'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-gsa-not-home';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'context' => array(
      'values' => array(
        '~context_ui-gsa-home' => '~context_ui-gsa-home',
      ),
    ),
    'path' => array(
      'values' => array(
        '~content/register-outreach-asia-2011' => '~content/register-outreach-asia-2011',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 1;
  $export['context_ui-gsa-not-home'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-userprofile';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'user_page' => array(
      'values' => array(
        'view' => 'view',
      ),
      'options' => array(
        'mode' => 'all',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-gsa_user_details-block' => array(
          'module' => 'views',
          'delta' => 'gsa_user_details-block',
          'region' => 'sidebar_left',
          'weight' => '-10',
        ),
        'user_relationship_blocks-user-1' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'user-1',
          'region' => 'sidebar_right',
          'weight' => '-10',
        ),
        'user_relationship_blocks-actions' => array(
          'module' => 'user_relationship_blocks',
          'delta' => 'actions',
          'region' => 'sidebar_right',
          'weight' => '-9',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;
  $export['context_ui-userprofile'] = $context;

  return $export;
}
