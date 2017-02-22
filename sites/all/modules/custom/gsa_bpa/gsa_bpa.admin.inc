<?php

/**
 * @file
 * Admin settings pages for the BPA listing module.
 */

/**
 * The admin settings form
 */
function bpa_listing_settings_form() {
  $form = array();

  $form['bpa_listing:group'] = array(
    '#type' => 'select',
    '#title' => t('Group'),
    '#description' => t('The group that BPA listings are associated with.'),
    '#options' => og_all_groups_options(),
    '#default_value' => variable_get('bpa_listing:group', 0),
  );

  return system_settings_form($form);
}

/**
 * CSV input form.
 *
 * @ingroup forms
 */
function bpa_listing_import_form() {
  $form = array();
  // Create a form widget that we can reuse to direct admins to set the BPA
 $link = array(
    'link' => array(
      '#value' => t('!link to set the BPA group', array('!link' => l(t('Click here'), 'admin/config/bpa_listing', array('query' => array('destination' => 'admin/content/bpa_listing'))))),
    ),
  ); 
  // Prevent an import if none or invalid BPA group
  if (!($group_id = variable_get('bpa_listing:group', 0)) || !is_numeric($group_id)) {
    drupal_set_message(t('A BPA group must be selected before an import can take place'), 'warning');
    return $error;
  }
  // Make sure the group is still available
  else if (!($group = node_load($group_id))) {
    drupal_set_message(t('The selected BPA group is no longer available'), 'warning');
    return $error;
  }
  
  // Make the user aware of the current BPA group
  $form['bpa_group'] = array(
    '#type' => 'fieldset',
    '#title' => t('BPA group'),
    '#value' => $link['link']['#value'],
    '#description' => '<strong>' . t('Current BPA group:') . ' </strong>' . "{$group->title} (NID: {$group->nid})",
  );

  $form['#attributes'] = array('enctype' => 'multipart/form-data');

  $form['upload'] = array(
    '#type' => 'file',
    '#title' => t('Upload the CSV export'),
    '#size' => 40,
  );

  $form['skip_first'] = array(
    '#type' => 'checkbox',
    '#title' => t('Do not import first line'),
    '#description' => t('Sometimes the first line of a CSV file contains column headings which shouldn\'t be imported.'),
    '#default_value' => 1,
  );

  $form['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Import BPA data'),
  );

  return $form;
}

/**
 * Preprocesses bpa_listing_import_form form submissions.
 */
function bpa_listing_import_form_submit(&$form, &$form_state) {
  global $user;
  // @todo: use node_object_prepare()
  module_load_include('inc', 'node', 'node.pages');

  // Column-to-field mappings from flat file.
  // @todo: build admin interface for field mappings
  $bpa_listing_active_field_mapping = 'consolidated with items';
  $bpa_listing_field_mappings = array (
    // RFA_8001 - BPA Dataset Full and Consolidated - 03-09-11.xlsx
    // Full BPA Dataset tab
    'full' => array(
      'field_bpa_listing_agency',
      'field_bpa_listing_product',
      'title',
      'field_bpa_listing_end_date',
      'field_bpa_listing_poc',
      'field_bpa_listing_terms',
      'field_bpa_listing_socioeconomic',
      'field_bpa_listing_status',
      'field_bpa_listing_authorized',
    ),
  
    // RFA_8001 - BPA Dataset Full and Consolidated - 03-09-11.xlsx
    // Consolidated Set tab
    'consolidated' => array(
      'field_bpa_listing_product',
      'title',
      'field_bpa_listing_end_date',
      'field_bpa_listing_poc',
      'field_bpa_listing_socioeconomic',
      'field_bpa_listing_authorized',  
    ),
  
    // Flatfile 6.2.11 RFA 8328.xlsx
    //Product or Service,BPA Number,BPA End Date,Agency POC,View Terms and Conditions,Socio-economic,Authorized Users,View Items
    'consolidated with items' => array(
      'field_bpa_listing_product',
      'title',
      'field_bpa_listing_end_date',
      'field_bpa_listing_poc',
      'field_bpa_listing_terms',
      'field_bpa_listing_socioeconomic',
      'field_bpa_listing_authorized',
      'field_bpa_listing_url',
    ),
  );

  // Delete all imported nodes.
  // @todo Batch operation??
  $query = new EntityFieldQuery;
  $result = $query->entityCondition('entity_type', 'node')
  ->entityCondition('bundle', 'bpa_listing')
  ->propertyCondition('status', 1)
  ->execute();
  
  if (isset($result['node'])) {
    $listing = array_keys($result['node']);
    $bpa_listing = entity_load('node', $listing);
  }
  if($bpa_listing){
    foreach($bpa_listing as $key => $value) {
      node_delete($value->nid);
    }
  }
 /*  $result = db_query("SELECT nid FROM {node} WHERE type = 'bpa_listing'");
  while ($record = db_fetch_object($result)) {
    node_delete($record->nid);
  } */
  // Get path to temp file, open file for reading.
  $filename = $_FILES['files']['tmp_name']['upload'];
  if (FALSE !== ($handle = fopen($filename, 'r'))) {
    $num_rows = 0;

    // Parse CSV file one row at a time.
    // @todo Remove the limit? Keep it as a safe guard?
    $first_line = TRUE;
    while (FALSE !== ($row = fgetcsv($handle)) && $num_rows < 1000) {
      // If we are iterating over the first line, check if we should skip it
      // based on whether the "skip_first" checkbox is selected.
      if ($first_line) {
        $first_line = FALSE;
        if (!empty($form_state['values']['skip_first'])) {
          continue;
        }
      }

      // Get group specified via the admin interface.
      $gid = variable_get('bpa_listing:group', 0);
      // Add the node data here.
      // @todo: separate function for creating the object
      $node = array(
        'type' => 'bpa_listing',
        'uid' => $user->uid,
        'name' => $user->name,

        // Associate node with the BPA group.
        'og_initial_groups' => array($gid => $gid),
        'og_groups' => array($gid => $gid),
        'og_public' => FALSE,
      );

      // Populate node with data, using preprocessors.
      foreach ($bpa_listing_field_mappings[$bpa_listing_active_field_mapping] as $key => $val) {
        $node[$val] = bpa_listing_preprocess_field($val, $row[$key]);
      }
      
      // Save the node.
      $node = (object) $node;
      // @todo: batch
      node_save($node);
      drupal_set_message(t('BPA Listing !link has been imported.', array('!link' => l($node->title, "node/{$node->nid}"))));

      // Increment the row counter.
      $num_rows++;
    }

    // Close the pointer.
    fclose($handle);
  }
  else {
    drupal_set_message(t('Error reading file.'), 'error');
  }
}

/**
 * Hook for preprocessing fields from CSV input.
 *
 * Fields without a corresponding preprocessor function will be wrapped in
 * an array (we're assuming they're CCK fields). For standard node fields
 * (title, body) we must define a preprocessor function that simply returns
 * the raw input.
 */
function bpa_listing_preprocess_field($field, $raw) {
  $preprocess_function = 'bpa_listing_preprocess_field_' . $field;
  if (is_callable($preprocess_function)) {
    $value = call_user_func($preprocess_function, $raw);
  } else {
    $value = array(0 => array('value' => $raw));
  }
  return $value;
}

/**
 * Preprocess title.
 */
function bpa_listing_preprocess_field_title($raw) {
  return $raw;
}

/**
 * Preprocess poc field.
 */
function bpa_listing_preprocess_field_field_bpa_listing_poc($raw) {
  return array(0 => array('email' => $raw));
}

/**
 * Preprocess end date field.
 */
function bpa_listing_preprocess_field_field_bpa_listing_end_date($raw) {
  // Parse date information, normalize and build date value.
  preg_match('@^(\d+)/(\d+)/(\d+) (\d+):(\d+)$@', $raw, $matches);
  $year = '20'. $matches[3];
  $month = str_pad($matches[1], 2, '0', STR_PAD_LEFT);
  $day = str_pad($matches[2], 2, '0', STR_PAD_LEFT);
  $hour = str_pad($matches[4] + 4, 2, '0', STR_PAD_LEFT);
  $minute = str_pad($matches[5], 2, '0', STR_PAD_LEFT);
  $date_value = "{$year}-{$month}-{$day}T{$hour}:{$minute}:00";
  
  return array(
    0 => array(
      'value' => $date_value,
      'value2' => $date_value,
      'timezone' => 'America/New_York',
      'offset' => -14000,
      'offset2' => -14000,
    ),
  );
}

/**
 * Preprocess socioeconomic field.
 */
function bpa_listing_preprocess_field_field_bpa_listing_socioeconomic($raw) {
  $statuses = array();
  preg_match_all('@\([a-zA-Z0-9]+\)@', $raw, $matches);
  foreach ($matches[0] as $status) {
	$statuses[] = array('value' => strtolower($status));
  }
  return $statuses;
}

/**
 * Preprocess terms field.
 */
function bpa_listing_preprocess_field_field_bpa_listing_terms($raw) {
  return array(
    0 => array(
     'url' => $raw,
     'weight' => '0',
    ),
  );
}

/**
 * Preprocess url ("view items") field.
 */
function bpa_listing_preprocess_field_field_bpa_listing_url($raw) {
  return array(
    0 => array(
      'url' => $raw,
      'weight' => '0',
    ),
  );
}