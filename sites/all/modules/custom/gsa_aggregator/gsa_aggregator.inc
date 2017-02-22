<?php
/**
 * $Id:$
 */

/**
 * Form constructor for adding and editing feed sources.
 *
 * @param $feed
 *   If editing a feed, the feed to edit as a PHP stdClass value; if adding a
 *   new feed, NULL.
 *
 * @ingroup forms
 * @see gsa_aggregator_form_feed_validate()
 * @see gsa_aggregator_form_feed_submit()
 */
function gsa_aggregator_form_feed($form, &$form_state, stdClass $feed = NULL) {
  
  if(!$feed){
    $nid = arg(1);
    
    $category_title = 'group-'. $nid;
    
    $category = db_query("SELECT * FROM {aggregator_category} WHERE title = :title", array(':title' => $category_title))->fetchObject();
    
    if(empty($category)) {
      $new = db_insert('aggregator_category')
      ->fields(array(
          'title' => $category_title,
          'description' => t('Category for feeds related to specific group page'),
          'block' => 3,
      ))
      ->execute();
    
      $category = db_query("SELECT * FROM {aggregator_category} WHERE title = :title", array(':title' => $category_title))->fetchObject();
    }
  }

  $period = drupal_map_assoc(array(900, 1800, 3600, 7200, 10800, 21600, 32400, 43200, 64800, 86400, 172800, 259200, 604800, 1209600, 2419200), 'format_interval');
  $period[AGGREGATOR_CLEAR_NEVER] = t('Never');

  $form['title'] = array('#type' => 'textfield',
    '#title' => t('Title'),
    '#default_value' => isset($feed->title) ? $feed->title : '',
    '#maxlength' => 255,
    '#description' => t('The name of the feed (or the name of the website providing the feed).'),
    '#required' => TRUE,
  );
  $form['url'] = array('#type' => 'textfield',
    '#title' => t('URL'),
    '#default_value' => isset($feed->url) ? $feed->url : '',
    '#maxlength' => 255,
    '#description' => t('The fully-qualified URL of the feed.'),
    '#required' => TRUE,
  );
  $form['refresh'] = array('#type' => 'select',
    '#title' => t('Update interval'),
    '#default_value' => isset($feed->refresh) ? $feed->refresh : 3600,
    '#options' => $period,
    '#description' => t('The length of time between feed updates'),
  );
  $form['block'] = array('#type' => 'select',
    '#title' => t('News items in block'),
    '#default_value' => isset($feed->block) ? $feed->block : 5,
    '#options' => drupal_map_assoc(array(0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20)),
    '#description' => t("Drupal can make a block with the most recent news items of this feed."),
  );

// Handling of categories.
  $options = array();
  $values = array();
  $categories = db_query('SELECT c.cid, c.title, f.fid FROM {aggregator_category} c LEFT JOIN {aggregator_category_feed} f ON c.cid = f.cid AND f.fid = :fid ORDER BY title', array(':fid' => isset($feed->fid) ? $feed->fid : NULL));
  foreach ($categories as $cat) {
    $options[$cat->cid] = check_plain($cat->title);
    if ($cat->fid) $values[] = $cat->cid;
  }
    if(!count($values)){
       $values[] = $category->cid;
    }
  
  if ($options) {
    $form['category'] = array(
      '#type' => 'checkboxes',
      '#title' => t('Categorize news items'),
      '#default_value' => $values,
      '#options' => $options,
      '#description' => t('New feed items are automatically filed in the checked categories.'),
    );
  }

  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save'),
  );
  if (!empty($feed->fid)) {
    $form['actions']['delete'] = array(
      '#type' => 'submit',
      '#value' => t('Delete'),
    );
    $form['fid'] = array(
      '#type' => 'hidden',
      '#value' => $feed->fid,
    );
  }

  return $form;
}

/**
 * Form validation handler for gsa_aggregator_form_feed().
 *
 * @see aggregator_form_feed_submit()
 */
function gsa_aggregator_form_feed_validate($form, &$form_state) {
  if ($form_state['values']['op'] == t('Save')) {
    // Ensure URL is valid.
    if (!valid_url($form_state['values']['url'], TRUE)) {
      form_set_error('url', t('The URL %url is invalid. Enter a fully-qualified URL, such as http://www.example.com/feed.xml.', array('%url' => $form_state['values']['url'])));
    }
    // Check for duplicate titles.
    if (isset($form_state['values']['fid'])) {
      $result = db_query("SELECT title, url FROM {aggregator_feed} WHERE (title = :title OR url = :url) AND fid <> :fid", array(':title' => $form_state['values']['title'], ':url' => $form_state['values']['url'], ':fid' => $form_state['values']['fid']));
    }
    else {
      $result = db_query("SELECT title, url FROM {aggregator_feed} WHERE title = :title OR url = :url", array(':title' => $form_state['values']['title'], ':url' => $form_state['values']['url']));
    }
    foreach ($result as $feed) {
      if (strcasecmp($feed->title, $form_state['values']['title']) == 0) {
        form_set_error('title', t('A feed named %feed already exists. Enter a unique title.', array('%feed' => $form_state['values']['title'])));
      }
      if (strcasecmp($feed->url, $form_state['values']['url']) == 0) {
        form_set_error('url', t('A feed with this URL %url already exists. Enter a unique URL.', array('%url' => $form_state['values']['url'])));
      }
    }
  }
}

/**
 * Form submission handler for aggregator_form_feed().
 *
 * @see gsa_aggregator_form_feed_validate()
 * @todo Add delete confirmation dialog.
 */
function gsa_aggregator_form_feed_submit($form, &$form_state) {
  
  $nid = arg(1);
  if ($form_state['values']['op'] == t('Delete')) {
    $title = $form_state['values']['title'];
    // Unset the title.
    unset($form_state['values']['title']);
  }
  aggregator_save_feed($form_state['values']);
  if (isset($form_state['values']['fid'])) {
    if (isset($form_state['values']['title'])) {
      drupal_set_message(t('The feed %feed has been updated.', array('%feed' => $form_state['values']['title'])));
        $form_state['redirect'] = 'node/'.$nid.'/group-feeds';
        return;
    }
    else {
      watchdog('aggregator', 'Feed %feed deleted.', array('%feed' => $title));
      drupal_set_message(t('The feed %feed has been deleted.', array('%feed' => $title)));
        $form_state['redirect'] = 'node/'.$nid.'/group-feeds';
        return;
    }
  }
  else {
    watchdog('aggregator', 'Feed %feed added.', array('%feed' => $form_state['values']['title']), WATCHDOG_NOTICE, l(t('view'), 'admin/config/services/aggregator'));
    drupal_set_message(t('The feed %feed has been added.', array('%feed' => $form_state['values']['title'])));
  }
}


/**
 * Deletes a feed.
 *
 * @param $feed
 *   An associative array describing the feed to be cleared.
 *
 * @see gsa_aggregator_delete_feed_submit()
 */
function gsa_aggregator_delete_feed($form, $form_state, $feed) {
  return confirm_form(
      array(
          'feed' => array(
              '#type' => 'value',
              '#value' => $feed,
          ),
      ),
      t('Are you sure you want to remove all items from the feed %feed?', array('%feed' => $feed->title)),
      '',
      t('This action cannot be undone.'),
      t('Remove Feed'),
      t('Cancel')
  );
}

/**
 * Form submission handler for gsa_aggregator_delete_feed().
 *
 * Removes all items from a feed and redirects to the overview page.
 */
function gsa_aggregator_delete_feed_submit($form, &$form_state) {
  db_delete('aggregator_category_feed')->condition('fid', $form_state['values']['feed']->fid)->execute();
  db_delete('aggregator_feed')->condition('fid', $form_state['values']['feed']->fid)->execute();
}
