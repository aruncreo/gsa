<?php
/**
 * @file
 * gsa_event.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gsa_event_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-gsa-event_page';
  $context->description = 'Provide event information blocks on the event page';
  $context->tag = '';
  $context->conditions = array(
    'node' => array(
      'values' => array(
        'gsa_event' => 'gsa_event',
      ),
      'options' => array(
        'node_form' => '0',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'gsa_event-0' => array(
          'module' => 'gsa_event',
          'delta' => '0',
          'region' => 'sidebar_left',
          'weight' => '-61',
        ),
        'views-gsa_event_fieldgroups-block_2' => array(
          'module' => 'views',
          'delta' => 'gsa_event_fieldgroups-block_2',
          'region' => 'sidebar_left',
          'weight' => '-60',
        ),
        'views-gsa_event_minimap-block_1' => array(
          'module' => 'views',
          'delta' => 'gsa_event_minimap-block_1',
          'region' => 'sidebar_left',
          'weight' => '-59',
        ),
        'views-gsa_event_fieldgroups-block_1' => array(
          'module' => 'views',
          'delta' => 'gsa_event_fieldgroups-block_1',
          'region' => 'sidebar_left',
          'weight' => '-58',
        ),
        'views-gsa_event_fieldgroups-block' => array(
          'module' => 'views',
          'delta' => 'gsa_event_fieldgroups-block',
          'region' => 'sidebar_left',
          'weight' => '-57',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Provide event information blocks on the event page');
  $export['context_ui-gsa-event_page'] = $context;

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-gsa-event_registration';
  $context->description = 'Provide event information blocks on the registration form';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        'event-registration' => 'event-registration',
      ),
    ),
  );
  $context->reactions = array(
    'block' => array(
      'blocks' => array(
        'gsa_event-group_gsa_event_details' => array(
          'module' => 'gsa_event',
          'delta' => 'group_gsa_event_details',
          'region' => 'sidebar_left',
          'weight' => '-10',
        ),
        'gsa_event-1' => array(
          'module' => 'gsa_event',
          'delta' => '1',
          'region' => 'sidebar_left',
          'weight' => '-9',
        ),
        'gsa_event-group_gsa_event_date' => array(
          'module' => 'gsa_event',
          'delta' => 'group_gsa_event_date',
          'region' => 'sidebar_left',
          'weight' => '-8',
        ),
        'gsa_event-group_gsa_event_location' => array(
          'module' => 'gsa_event',
          'delta' => 'group_gsa_event_location',
          'region' => 'sidebar_left',
          'weight' => '-7',
        ),
      ),
    ),
  );
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('Provide event information blocks on the registration form');
  $export['context_ui-gsa-event_registration'] = $context;

  return $export;
}
