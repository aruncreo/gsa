<?php

/**
 * @file
 * Class definition of BPANodeProcessor.
 */

define('FEEDS_CLEAR_EXISTING', 3);

/**
 * Creates nodes from BPA data feed items.
 */
class BPANodeProcessor extends FeedsNodeProcessor {

  /**
   * Implementation of FeedsProcessor::process().
   */
  public function process(FeedsImportBatch $batch, FeedsSource $source) {

    // Keep track of processed items in this pass, set total number of items.
    $processed = 0;
    if (!$batch->getTotal(FEEDS_PROCESSING)) {
      $batch->setTotal(FEEDS_PROCESSING, count($batch->items));

      // These two calls to setTotal() were added as a workaround to problems
      // upstream in Feeds. See http://drupal.org/node/1139376
      $batch->setTotal(FEEDS_FETCHING, $batch->getProgress(FEEDS_FETCHING));
      $batch->setTotal(FEEDS_PARSING, $batch->getProgress(FEEDS_PARSING));
    }

    // These variables are set outsite of the while loop to reduce the total
    // number of function calls.
    $feeds_node_batch_size = variable_get('feeds_node_batch_size', FEEDS_NODE_BATCH_SIZE);
    $batch_total = $batch->getTotal(FEEDS_PROCESSING);
    
    // For GSA, all mapped nodes must be cleared before any import operation is performed
    if ($this->config['update_existing'] == FEEDS_CLEAR_EXISTING) {
      $this->clear($batch, $source);
    }
    while ($item = $batch->shiftItem()) {

      // Create/update if item does not exist or update existing is enabled.
      if (!($nid = $this->existingItemId($batch, $source)) || ($this->config['update_existing'] != FEEDS_SKIP_EXISTING)) {
        // Only proceed if item has actually changed.
        $hash = $this->hash($item);
        if (!empty($nid) && $hash == $this->getHash($nid)) {
          continue;
        }

        $node = $this->buildNode($nid, $source->feed_nid);
        $node->feeds_node_item->hash = $hash;

        // Map and save node. If errors occur don't stop but report them.
        try {
          $this->map($batch, $node);
          if ($this->config['authorize']) {
            if (empty($node->nid)) {
              $op = 'create';
            }
            else {
              $op = 'update';
            }
            $account = user_load($node->uid);
            if (!node_access($op, $node, $account)) {
              throw new Exception('User ' . $account->uid . ' not authorized to ' . $op . ' content type ' . $node->type);
            }
          }
          // set the group, if non-zero
          $group = variable_get('bpa_listing:group', 0);
          if ($group != 0) {
          	$node->og_groups = array($group);
          }
          node_save($node);
          if (!empty($nid)) {
            $batch->updated++;
          }
          else {
            $batch->created++;
          }
        }
        catch (Exception $e) {
          drupal_set_message($e->getMessage(), 'warning');
          watchdog('feeds', $e->getMessage(), array(), WATCHDOG_WARNING);
        }
      }

      $processed++;
      // setProgress() does not handle well the case in which the feeds_node_batch_size
      // is exactly equal to the number of incoming items.
      // This first if statement is a workaround for that bug with setProgress.
      if ($processed == $batch_total && $processed == $feeds_node_batch_size) {
        // Explicitly set the progress to FEED_BATCH_COMPLETE rather than calculating
        // the value as the next 'else if' will do.
        $batch->setProgress(FEEDS_PROCESSING, FEEDS_BATCH_COMPLETE);
        return;
      }
      else if ($processed >= $feeds_node_batch_size) {
        $batch->setProgress(FEEDS_PROCESSING, $batch->created + $batch->updated);
        return;
      }
    }

    // Set messages.
    if ($batch->created) {
      drupal_set_message(format_plural($batch->created, 'Created @number @type node.', 'Created @number @type nodes.', array('@number' => $batch->created, '@type' => node_get_types('name', $this->config['content_type']))));
    }
    elseif ($batch->updated) {
      drupal_set_message(format_plural($batch->updated, 'Updated @number @type node.', 'Updated @number @type nodes.', array('@number' => $batch->updated, '@type' => node_get_types('name', $this->config['content_type']))));
    }
    else {
      drupal_set_message(t('There is no new content.'));
    }
    $batch->setProgress(FEEDS_PROCESSING, FEEDS_BATCH_COMPLETE);
  }

  /**
   * Implementation of FeedsProcessor::clear().
   */
  public function clear(FeedsBatch $batch, FeedsSource $source) {
  	parent::clear($batch, $source);
  }

  /**
   * Implement expire().
   */
  public function expire($time = NULL) {
  	return parent::expire($time);
  }

  /**
   * Return expiry time.
   */
  public function expiryTime() {
  	return parent::expiryTime();
  }

  /**
   * Override parent::configDefaults().
   */
  public function configDefaults() {
    $types = node_get_types('names');
    $type = isset($types['story']) ? 'story' : key($types);
    return array(
      'content_type' => $type,
      'input_format' => FILTER_FORMAT_DEFAULT,
      'update_existing' => FEEDS_SKIP_EXISTING,
      'expire' => FEEDS_EXPIRE_NEVER,
      'mappings' => array(),
      'author' => 0,
      'authorize' => 0,
    );
  }

  
  /**
   * Override parent::configForm().
   */
  public function configForm(&$form_state) {
    
    $form = parent::configForm($form_state);
    $form['update_existing'] = array(
      '#type' => 'radios',
      '#title' => t('Update/clear existing nodes'),
      '#description' => t('Select how existing nodes should be updated. Existing nodes will be determined using mappings that are a "unique target".'),
      '#options' => array(
        FEEDS_SKIP_EXISTING => 'Do not update existing nodes',
        FEEDS_REPLACE_EXISTING => 'Replace existing nodes',
        FEEDS_UPDATE_EXISTING => 'Update existing nodes (slower than replacing them)',
    	FEEDS_CLEAR_EXISTING => 'Clear existing nodes before import',
      ),
      '#default_value' => $this->config['update_existing'],
    );
    return $form;
  }

  /**
   * Override parent::configFormValidate().
   */
  public function configFormValidate(&$values) {
  	parent::configFormValidate(&$values);
  }

  /**
   * Reschedule if expiry time changes.
   */
  public function configFormSubmit(&$values) {
  	parent::configFormSubmit(&$values);
  }

  /**
   * Override setTargetElement to operate on a target item that is a node.
   */
  public function setTargetElement(&$target_node, $target_element, $value) {
  	parent::setTargetElement(&$target_node, $target_element, $value);
  }

  /**
   * Return available mapping targets.
   */
  public function getMappingTargets() {
  	return parent::getMappingTargets();
  }

}
