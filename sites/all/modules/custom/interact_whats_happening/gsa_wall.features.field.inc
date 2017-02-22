<?php
/**
 * @file
 * gsa_wall.features.field.inc
 */

/**
 * Implements hook_field_default_fields().
 */
function gsa_wall_field_default_fields() {
  $fields = array();

  // Exported field: 'node-blog-field_youtube_video'.
  $fields['node-blog-field_youtube_video'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_youtube_video',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(
        'embed_code' => array(
          0 => 'embed_code',
        ),
      ),
      'locked' => '0',
      'module' => 'gsa_youtube',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'gsa_youtube_video_field',
    ),
    'field_instance' => array(
      'bundle' => 'blog',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '<a href="/youtube-video/help" target="_blank">More information about YouTube videos</a>',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'gsa_youtube',
          'settings' => array(),
          'type' => 'gsa_youtube_embed_code_formatter',
          'weight' => 40,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_youtube_video',
      'label' => 'YouTube Video',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'gsa_youtube',
        'settings' => array(),
        'type' => 'gsa_youtube_embed_code_list',
        'weight' => '13',
      ),
    ),
  );

  // Exported field: 'node-document-field_youtube_video'.
  $fields['node-document-field_youtube_video'] = array(
    'field_config' => array(
      'active' => '1',
      'cardinality' => '-1',
      'deleted' => '0',
      'entity_types' => array(),
      'field_name' => 'field_youtube_video',
      'field_permissions' => array(
        'type' => '0',
      ),
      'foreign keys' => array(),
      'indexes' => array(
        'embed_code' => array(
          0 => 'embed_code',
        ),
      ),
      'locked' => '0',
      'module' => 'gsa_youtube',
      'settings' => array(),
      'translatable' => '0',
      'type' => 'gsa_youtube_video_field',
    ),
    'field_instance' => array(
      'bundle' => 'document',
      'default_value' => NULL,
      'deleted' => '0',
      'description' => '<a href="/youtube-video/help" target="_blank">More information about YouTube videos</a>',
      'display' => array(
        'default' => array(
          'label' => 'above',
          'module' => 'gsa_youtube',
          'settings' => array(),
          'type' => 'gsa_youtube_embed_code_formatter',
          'weight' => 9,
        ),
        'teaser' => array(
          'label' => 'above',
          'settings' => array(),
          'type' => 'hidden',
          'weight' => 0,
        ),
      ),
      'entity_type' => 'node',
      'field_name' => 'field_youtube_video',
      'label' => 'YouTube Video',
      'required' => 0,
      'settings' => array(
        'user_register_form' => FALSE,
      ),
      'widget' => array(
        'active' => 0,
        'module' => 'gsa_youtube',
        'settings' => array(),
        'type' => 'gsa_youtube_embed_code_list',
        'weight' => '19',
      ),
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('<a href="/youtube-video/help" target="_blank">More information about YouTube videos</a>');
  t('YouTube Video');

  return $fields;
}
