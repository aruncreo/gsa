<?php
/**
 * @file
 * gsa_group_content.features.taxonomy.inc
 */

/**
 * Implements hook_taxonomy_default_vocabularies().
 */
function gsa_group_content_taxonomy_default_vocabularies() {
  return array(
    'vocabulary_2' => array(
      'name' => 'Tags',
      'machine_name' => 'vocabulary_2',
      'description' => 'Free-tagging vocabulary for all content items',
      'hierarchy' => '1',
      'module' => 'taxonomy',
      'weight' => '0',
    ),
  );
}
