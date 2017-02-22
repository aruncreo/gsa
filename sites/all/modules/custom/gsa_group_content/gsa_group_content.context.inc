<?php
/**
 * @file
 * gsa_group_content.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gsa_group_content_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-content';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'context_og_condition_group_type' => array(
      'values' => array(
        '_any_' => '_any_',
        'group' => 'group',
      ),
      'options' => array(
        'node_form' => 1,
      ),
    ),
    'views' => array(
      'values' => array(
        'group_information' => 'group_information',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'views-group_information-block' => array(
          'module' => 'views',
          'delta' => 'group_information-block',
          'region' => 'sidebar_right',
          'weight' => '-61',
        ),
        'views-gsa_og_announcement-block' => array(
          'module' => 'views',
          'delta' => 'gsa_og_announcement-block',
          'region' => 'sidebar_right',
          'weight' => '-60',
        ),
        'views-gsa_og_announcement-block_1' => array(
          'module' => 'views',
          'delta' => 'gsa_og_announcement-block_1',
          'region' => 'sidebar_right',
          'weight' => '-59',
        ),
        'views-group_events_block-block' => array(
          'module' => 'views',
          'delta' => 'group_events_block-block',
          'region' => 'sidebar_right',
          'weight' => '-58',
        ),
        'views-gsa_og_members-block_1' => array(
          'module' => 'views',
          'delta' => 'gsa_og_members-block_1',
          'region' => 'sidebar_right',
          'weight' => '-57',
        ),
        'views-grouppoll-block_1' => array(
          'module' => 'views',
          'delta' => 'grouppoll-block_1',
          'region' => 'sidebar_right',
          'weight' => '-56',
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
  $export['context_ui-group-content'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-content-events';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'group_events_block' => 'group_events_block',
        'group_events_block:page_1' => 'group_events_block:page_1',
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
  $export['context_ui-group-content-events'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-group-content-poll';
  $context->description = '';
  $context->tag = '';
  $context->conditions = array(
    'views' => array(
      'values' => array(
        'grouppoll' => 'grouppoll',
        'grouppoll:page' => 'grouppoll:page',
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
  $export['context_ui-group-content-poll'] = $context;

  return $export;
}
