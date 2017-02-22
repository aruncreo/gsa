<?php

/**
 * Callback for hook_og_features_registry()
 */
function _gsa_config_og_features_registry() {
  $registry = array();
  
  // Feature: commons_blog
  $feature = new stdClass;
  $feature->id = 'commons_blog';
  $feature->name = t('Blogs');
  $feature->description = t('Enable your group members to create blog entries relevant to your group.');
  $feature->components = array( 
    'views' => array(
      'og_tab_blogs',
    ),
    'node' => array(
      'blog',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: commons_discussion
  $feature = new stdClass;
  $feature->id = 'commons_discussion';
  $feature->name = t('Discussions');
  $feature->description = t('Enable collaborative (threaded) discussions among your group members.');
  $feature->components = array( 
    'views' => array(
      'og_tab_discussions',
    ),
    'node' => array(
      'discussion',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: commons_document
  $feature = new stdClass;
  $feature->id = 'commons_document'; 
  $feature->name = t('Documents');
  $feature->description = t('Create document content inside your group');
  $feature->components = array( 
    'views' => array(
      'og_tab_documents',
    ),
    'node' => array(
      'document',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: commons_event
  $feature = new stdClass;
  $feature->id = 'commons_event';
  $feature->name = t('Events');
  $feature->description = t('Enable your group members to announce events associated with your group, and display them on calendars & sidebar blocks.');
  $feature->components = array( 
    'views' => array(
      'og_calendar',
    ),
    'node' => array(
      'event',
    ),
    'pane' => array(
      'og_calendar',
    ),
    'context' => array(
      'context_ui-group-event',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: commons_poll
  $feature = new stdClass;
  $feature->id = 'commons_poll';
  $feature->name = t('Topic polls');
  $feature->description = t('Enable your group members to create multiple-choice polls that other group members can vote on.');
  $feature->components = array( 
    'views' => array(
      'group_tab_polls',
    ),
    'node' => array(
      'poll',
    ),
    'context' => array(
      'context_ui-group-poll',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: commons_wiki
  $feature = new stdClass;
  $feature->id = 'commons_wiki';
  $feature->name = t('Wikis');
  $feature->description = t('Enable a type of page where the body of the page can be edited by any group member, and which lets members use Wiki-style syntax.');
  $feature->components = array( 
    'views' => array(
      'og_tab_wikis',
    ),
    'node' => array(
      'wiki',
    ),
  );
  $registry[$feature->id] = $feature;
  
  // Feature: og_public_default
  $feature = new stdClass;
  $feature->id = 'og_public_default';
  $feature->name = t('Default content to public');
  $feature->description = t('If enabled, when creating new content within this group, it will default to being public.');
  $feature->components = array();
  $registry[$feature->id] = $feature;

  return $registry;
}
