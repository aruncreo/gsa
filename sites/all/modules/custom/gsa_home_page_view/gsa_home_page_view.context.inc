<?php
/**
 * @file
 * gsa_home_page_view.context.inc
 */

/**
 * Implements hook_context_default_contexts().
 */
function gsa_home_page_view_context_default_contexts() {
  $export = array();

  $context = new stdClass();
  $context->disabled = FALSE; /* Edit this to true to make a default context disabled initially */
  $context->api_version = 3;
  $context->name = 'context_ui-gsa-home';
  $context->description = 'The home page';
  $context->tag = '';
  $context->conditions = array(
    'path' => array(
      'values' => array(
        '<front>' => '<front>',
      ),
    ),
  );
  $context->reactions = array();
  $context->condition_mode = 0;

  // Translatables
  // Included for use with string extractors like potx.
  t('The home page');
  $export['context_ui-gsa-home'] = $context;

  return $export;
}
