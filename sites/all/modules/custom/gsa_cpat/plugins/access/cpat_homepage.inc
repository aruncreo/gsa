<?php

/**
 * @file
 * Plugin to provide access control based on CPAT home page.
 */

/**
 * Plugins are described by creating a $plugin array which will be used
 * by the system that includes this file.
 */
$plugin = array(
  'title' => t('CPAT home page'),
  'description' => t('Is this the CPAT home page.'),
  'callback' => 'gsa_cpat_homepage_access_check',
  'default' => array('negate' => 0),
  'settings form' => 'gsa_cpat_homepage_access_settings',
  'summary' => 'gsa_cpat_homepage_access_summary',
  'required context' => new ctools_context_required(t('Node'), 'node'),
);

/**
 * Settings form for the 'CPAT home page' access plugin
 */
function gsa_cpat_homepage_access_settings($form, &$form_state, $conf) {
  // No additional configuration necessary.
  return $form;
}

/**
 * Check for access.
 */
function gsa_cpat_homepage_access_check($conf, $context) {

  if (empty($context) || empty($context->data) || empty($context->data->nid)) {
    return FALSE;
  }

  if (! $cpat_group = gsa_cpat_get_cpat_group()) {
    return FALSE;
  }

  return ($context->data->nid == $cpat_group->etid);
}

/**
 * Provide a summary description based upon the checked terms.
 */
function gsa_cpat_homepage_access_summary($conf, $context) {
  return t('CPAT home page');
}
