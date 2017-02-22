<?php

/**
 * Info block: Site/group membership count
 */
function _gsa_charts_membership_count() {
  $group = og_features_get_group_context();
  
  // Get the total amount of active users either on the site, or in
  // the current group, using the query base for the agency charts.
  $query = _gsa_charts_generate_agency_chart_query();
  $query = str_replace("SELECT", "SELECT COUNT(users.uid)", $query);

  $result = db_query($query);
  $total = $result->fetchField();
  
  // Format the current date
  $date = format_date(time(), 'custom', 'F jS Y');
  
  // Format the message
  if ($group) {
    $message = t('* As of !date, %group membership is at !total.', array('!date' => $date, '%group' => check_plain($group->title), '!total' => $total));
  }
  else {
    $message = t('* As of !date, Interact membership is at !total.', array('!date' => $date, '!total' => $total));
  }
  
  return "<em>{$message}</em>";
}

/**
 * Chart: Is/Is-Not GSA
 */
function _gsa_charts_chart_is_gsa() {
  // Start the chart
  $chart = _gsa_charts_init_pie_chart('gsa_charts_is_gsa');
  
  // Determine the percentage of users that have GSA marked as their agency
  $query = _gsa_charts_generate_agency_chart_query(
    array(
      "ROUND(((COUNT((CASE WHEN (profile_value.value = 'General Services Administration') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS GSA",
      "(COUNT((CASE WHEN (profile_value.value = 'General Services Administration') THEN 1 END))) AS GSAtotal",
      "ROUND(((COUNT((CASE WHEN (profile_value.value <> 'General Services Administration') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS nonGSA",
      "(COUNT((CASE WHEN (profile_value.value <> 'General Services Administration') THEN 1 END))) AS nonGSAtotal",
    )
  );
  
  // Execute the query
  $result= db_query($query);
  $data = $result->fetchAssoc();
  
  // Add data
  _gsa_charts_add_chart_data($chart, $data);
  
  // Add labels
  _gsa_charts_add_chart_legend($chart, t('GSA: !count% (!total)', array('!count' => $data['GSA'], '!total' => $data['GSAtotal'])));
  _gsa_charts_add_chart_legend($chart, t('Non-GSA: !count% (!total)', array('!count' => $data['nonGSA'], '!total' => $data['nonGSAtotal'])));
  
  // Render the chart
  return theme('chart', array('chart' => $chart));

}

/**
 * Chart: Government/Non-Government
 */
function _gsa_charts_chart_government() {
  // Start the chart
  $chart = _gsa_charts_init_pie_chart('gsa_charts_government');
  
  // Determine the percentage of users that are in the government
  $query = _gsa_charts_generate_agency_chart_query(
    array(
      "ROUND(((COUNT((CASE WHEN (profile_value.value = 'Other - Industry, Non-Profit, Associations') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS nonGov", 
      "(COUNT((CASE WHEN (profile_value.value = 'Other - Industry, Non-Profit, Associations') THEN 1 END))) AS nonGovtotal", 
      "ROUND(((COUNT((CASE WHEN (profile_value.value <> 'Other - Industry, Non-Profit, Associations') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS Gov",
      "(COUNT((CASE WHEN (profile_value.value <> 'Other - Industry, Non-Profit, Associations') THEN 1 END))) AS Govtotal",
    )
  );

  // Execute the query
  $result= db_query($query);
  $data = $result->fetchAssoc();
  
  // Add data
  _gsa_charts_add_chart_data($chart, $data);
  
  // Add labels
  _gsa_charts_add_chart_legend($chart, t('Non-Government: !count% (!total)', array('!count' => $data['nonGov'], '!total' => $data['nonGovtotal'])));
  _gsa_charts_add_chart_legend($chart, t('Government: !count% (!total)', array('!count' => $data['Gov'], '!total' => $data['Govtotal'])));
  
  // Render the chart

return theme('chart', array('chart' => $chart));
}

/**
 * Chart: Military/Civilian/State/Tribal Members
 */
function _gsa_charts_chart_military_civilian() {
  // Start the chart
  $chart = _gsa_charts_init_pie_chart('gsa_charts_military_civilian');
  
  // Determine the percentage of users are Military/Civilian/State/Tribal Members
  $query = _gsa_charts_generate_agency_chart_query(
    array(
      "ROUND(((COUNT((CASE WHEN (profile_value.value = 'Tribal Nations') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS TribalNations",
      "(COUNT((CASE WHEN (profile_value.value = 'Tribal Nations') THEN 1 END))) AS TribalNationstotal",
      "ROUND(((COUNT((CASE WHEN (profile_value.value = 'State and Local') THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS StateLocal",
      "(COUNT((CASE WHEN (profile_value.value = 'State and Local') THEN 1 END))) AS StateLocaltotal",
      "ROUND(((COUNT((CASE WHEN (profile_value.value IN ('Air Force', 'Army', 'Defense', 'Marines', 'Navy', 'U.S. Army Corps of Engineers')) THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS Military",
      "(COUNT((CASE WHEN (profile_value.value IN ('Air Force', 'Army', 'Defense', 'Marines', 'Navy', 'U.S. Army Corps of Engineers')) THEN 1 END))) AS Militarytotal",
      "ROUND(((COUNT((CASE WHEN (profile_value.value NOT IN ('Air Force', 'Army', 'Defense', 'Marines', 'Navy', 'U.S. Army Corps of Engineers', 'Tribal Nations', 'State and Local')) THEN 1 END)) * 100) / COUNT(profile_value.value)), 2) AS Civilian",
      "(COUNT((CASE WHEN (profile_value.value NOT IN ('Air Force', 'Army', 'Defense', 'Marines', 'Navy', 'U.S. Army Corps of Engineers', 'Tribal Nations', 'State and Local', 'Other - Industry, Non-Profit, Associations', 'To be assigned')) THEN 1 END))) AS Civiliantotal",
    )
  );
  
  // Execute the query
  $result= db_query($query);
  $data = $result->fetchAssoc();
  
  // Add data
  _gsa_charts_add_chart_data($chart, $data);
  
  // Add labels
  _gsa_charts_add_chart_legend($chart, t('Tribal Nations: !count% (!total)', array('!count' => $data['TribalNations'], '!total' => $data['TribalNationstotal'])));
  _gsa_charts_add_chart_legend($chart, t('State and Local: !count% (!total)', array('!count' => $data['StateLocal'], '!total' => $data['StateLocaltotal'])));
  _gsa_charts_add_chart_legend($chart, t('Military: !count% (!total)', array('!count' => $data['Military'], '!total' => $data['Militarytotal'])));
  _gsa_charts_add_chart_legend($chart, t('Civilian: !count% (!total)', array('!count' => $data['Civilian'], '!total' => $data['Civiliantotal'])));
  
  // Render the chart
    return theme('chart', array('chart' => $chart));
}

/**
 * Chart: Military Members by Branch
 */
function _gsa_charts_chart_military_by_branch() {
  // Start the chart
  $chart = _gsa_charts_init_pie_chart('gsa_charts_military_by_branch');
  
  // Determine the percentage of users in each Military branch
  $query = _gsa_charts_generate_agency_chart_query(
    array(
      "COUNT((CASE WHEN (profile_value.value = 'Air Force') THEN 1 END)) AS AirForce",
      "COUNT((CASE WHEN (profile_value.value IN ('Army', 'U. S. Army Corps of Engineers')) THEN 1 END)) AS Army",
      "COUNT((CASE WHEN (profile_value.value = 'Marines') THEN 1 END)) AS Marines", 
      "COUNT((CASE WHEN (profile_value.value = 'Navy') THEN 1 END)) AS Navy",
      "COUNT((CASE WHEN (profile_value.value IN ('Defense')) THEN 1 END)) AS Defense",
    )
  );
  
  // Execute the query
  $result= db_query($query);
  $data = $result->fetchAssoc();

  // Determine the total, since we can't divide by all values like the other queries
  $total = 0;
  foreach ($data as $value) {
    $total += $value;
  }
 
  // Track individual totals
  $totals = $data;
  
  // Use the total to determine percentages
  if ($total > 0) {
    foreach ($data as $key => $value) {
      $data[$key] = (($data[$key] > 0) ? number_format(($data[$key] * 100) / $total, 2) : 0);
    }
  }
  
  // Add data
  _gsa_charts_add_chart_data($chart, $data);
  
  // Add labels
  _gsa_charts_add_chart_legend($chart, t('Air Force: !count% (!total)', array('!count' => $data['AirForce'], '!total' => $totals['AirForce'])));
  _gsa_charts_add_chart_legend($chart, t('Army: !count% (!total)', array('!count' => $data['Army'], '!total' => $totals['Army'])));
  _gsa_charts_add_chart_legend($chart, t('Marines: !count% (!total)', array('!count' => $data['Marines'], '!total' => $totals['Marines'])));
  _gsa_charts_add_chart_legend($chart, t('Navy: !count% (!total)', array('!count' => $data['Navy'], '!total' => $totals['Navy'])));
  _gsa_charts_add_chart_legend($chart, t('Defense: !count% (!total)', array('!count' => $data['Defense'], '!total' => $totals['Defense'])));
  
  // Render the chart
    return theme('chart', array('chart' => $chart));
}

/**
 * Chart: Top Ten Agencies
 */
function _gsa_charts_chart_top_ten_agencies() {
  // Start the chart
  $chart = _gsa_charts_init_bar_chart('gsa_charts_top_ten_agencies');
  
  // List the agencies we'll track
  $agencies = array(
    "'Agriculture'",
    "'Air Force'",
    "'Army'",
    "'Commerce'",
    "'Commissions/Boards/Courts'",
    "'Defense'",
    "'Education'",
    "'Energy'",
    "'Environmental Protection Agency'",
    "'Health and Human Services'",
    "'Homeland Security'",
    "'Housing and Urban Development'",
    "'Interior'",
    "'Justice'",
    "'Labor'",
    "'Marines'",
    "'National Aeronautics and Space Administration'",
    "'Navy'",
    "'Small Business Administration'",
    "'Social Security Administration'",
    "'State Department'",
    "'Transportation'",
    "'Treasury'",
    "'U. S. Army Corps of Engineers'",
    "'United States Postal Service'",
    "'Veterans Affairs'",
  );
  
  // Fetch the data
  $query = _gsa_charts_generate_agency_chart_query(
    array(
      "profile_value.value",
    ),
    array(
      "(profile_value.value IN (".implode(',', $agencies)."))",
    )
  );

  $results = db_query($query, $agencies);

  // Tally the results
  $data = array();
  $total = 0;
  
  while ($agency =  $results->fetchObject()) {
  $agency=$agency->value;

    // Group certain agencies into one
    switch ($agency) {
      case 'Air Force':
	  break;
      case 'Army':
	  break;
      case 'Defense':
	  break;
      case 'Navy':
	  break;
      case 'Marines':
	  break;
      case 'U. S. Army Corps of Engineers':
        $agency = 'Army';
        break;
    }
	
    
    // Increment the count and total
    if (!isset($data[$agency])) {
      $data[$agency] = 0;
    }
    $data[$agency]++;
    $total++;

  }
  
  // Sort the results in numeric order, descending
  arsort($data, SORT_NUMERIC);
  
  // Only keep the top ten agencies
  if (count($data) > 10) {
    array_splice($data, 10);
  }
  
  // Determine the top ten total
  $top_ten_total = 0;
  foreach ($data as $key => $value) {
    $top_ten_total += $value;
  }

  // Add the "Other" category
 // $data['Other'] = $total - $top_ten_total;  
  
  // Add data
  _gsa_charts_add_chart_data($chart, $data);

  // Add labels
  foreach ($data as $label => $count) {
    _gsa_charts_add_chart_label($chart, $label . ' (' . $count . ')', 'y');
	
  }

  // Render the chart
    return theme('chart', array('chart' => $chart));
}


/**********************************************
 * Chart helper functions
 *********************************************/

/**
 * Initialize a pie chart
 * 
 * @param $id
 *   A unique ID for this chart
 * @param $label
 *   An optional title/label for the chart
 * @return
 *   A template for a pie chart
 */
function _gsa_charts_init_pie_chart($id, $label = FALSE) {
  $chart = array(
    '#chart_id' => $id,
    '#title' => $label ? chart_title($label) : NULL,
    '#type' => CHART_TYPE_PIE,
    '#adjust_resolution' => TRUE,
    '#size' => chart_size(450, 200), 
  );
  
  // Change the dimensions if this is a group page.
  if ($group = og_features_get_group_context()) {
    $chart['#size'] = chart_size(350, 170);
  }
  
  return $chart;
}

/**
 * Initialize a bar chart
 * 
 * @param $id
 *   A unique ID for this chart
 * @param $label
 *   An optional title/label for the chart
 * @return
 *   A template for a bar chart
 */
function _gsa_charts_init_bar_chart($id, $label = FALSE) {
  return array(
    '#type' => CHART_TYPE_BAR_H,
    '#chart_id' => $id,
    '#title' => $label ? chart_title($label) : NULL,
    '#size' => chart_size(600, 400),
    '#bar_size' => chart_bar_size(25, 10),
    '#adjust_resolution' => TRUE,
  );
}

/**
 * Add a label to the chart
 * 
 * @param &$chart
 *   A chart array
 * @param $label
 *   The label to add to the chart
 * @param $axis
 *   The axis to add labels to (Either 'x' or 'y')
 */
function _gsa_charts_add_chart_label(&$chart, $label, $axis = 'x') {
  // Convert the label to a chart-friendly label
  $label = chart_mixed_axis_label($label);
  
  // Determine the axis to add the label to
  switch (strtolower($axis)) {
    case 'x':
      $chart['#mixed_axis_labels'][CHART_AXIS_X_BOTTOM][0][] = $label;
      break;
      
    case 'y':
      // y-axis must be added in reverse
      if (!isset($chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0])) {
        $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0] = array();
      }
      array_unshift($chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0], $label);
      break;
  }
}

/**
 * Add a legend to the chart
 * 
 * @param &$chart
 *   A chart array
 * @param $legend
 *   The legend to add to the chart
 */
function _gsa_charts_add_chart_legend(&$chart, $legend) {
  
  $chart['#legends'][] = $legend;
  $chart['#legend_position'] = CHART_LEGEND_RIGHT;
  return;
      
  // y-axis must be added in reverse
  if (!isset($chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0])) {
    $chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0] = array();
  }
  array_unshift($chart['#mixed_axis_labels'][CHART_AXIS_Y_LEFT][0], $label);

}

/**
 * Generate a SELECT query for agency charts
 * 
 * @param $select
 *   An array of fields to select
 * @param $where
 *   An array of additional WHERE clauses
 * @return
 *   An SQL query
 */
function _gsa_charts_generate_agency_chart_query($select = array(), $where = array()) {

  // Determine if we're inside a group context
  $group = og_features_get_group_context();
  $groupid = $group->gid;

  // Contruct the query
  $query = "\n  SELECT\n   ";
  $query .= ' ' . implode(",\n    ", $select);
  $query .= "
    FROM `users`  
    LEFT JOIN `profile_value` ON users.uid = profile_value.uid 
    LEFT JOIN `profile_field` ON profile_field.fid = profile_value.fid
  ";
  
  if ($group) {
    $query .= "
      LEFT JOIN `og_membership`  ON og_membership.etid = users.uid
    ";
  }
  
  $query .= "
    WHERE 
      (users.uid > 1) 
      AND (profile_value.value <> '') 
      AND (profile_value.value <> 'null') 
      AND (profile_value.value IS NOT NULL)
      AND (profile_field.name = 'profile_agency')
	 
  ";
  
  if ($group) {
    $query .= "
      AND (og_membership.gid = $groupid)
      AND (og_membership.entity_type = 'user')
    ";
  }

  $query .= !empty($where) ? ("    AND " . implode("\n      AND ", $where)) : '';

  return $query;
}

/**
 * Add database result data to a chart
 * 
 * @param &$chart
 *   A chart array
 * @param $data
 *   An array of data, with numeric data point values
 */
function _gsa_charts_add_chart_data(&$chart, $data) {
  if (!isset($chart['#data'])) {
    $chart['#data'] = array();
  }
  foreach ($data as $key => $value) {
    // Skip total counts
    if (substr($key, -5) == 'total') {
	
      continue;
    }
    $chart['#data'][] = $value;
  }
}

