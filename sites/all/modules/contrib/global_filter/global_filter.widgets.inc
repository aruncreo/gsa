<?php

/**
 * @file
 * global_filter.widgets.inc
 */

define('GLOBAL_FILTER_DEF_OPTION_ALL_TEXT', t('All'));
define('GLOBAL_FILTER_VIEWS_COUNTRY_FIELD', 'country'); // does not require Location module
define('GLOBAL_FILTER_VIEWS_PROXIMITY_FIELD', 'distance'); // requires Location module
define('GLOBAL_FILTER_VIEWS_SEARCH_TERMS_FIELD', 'keys'); // core Search module
define('GLOBAL_FILTER_VIEWS_SEARCH_API_FULLTEXT', 'search_api_views_fulltext'); // requires Search API module

/**
 * Implements hook_forms();
 *
 * Called as a result of the fact that there are no hard-coded handlers for the
 * unique form_id's ('global_filter_block_1', 'global_filter_block_2'...),
 * generated in global_filter_block_info().
 * Here we map these form_id's back to the same 'global_filter_block_form'.
 */
function global_filter_forms($form_id, $args) {
  if (strpos($form_id, GLOBAL_FILTER_BLOCK_ID_PREFIX) === 0) {
    // Convert $form_id to block#
    $block_number = drupal_substr($form_id, -1);
    $form = array(
      $form_id => array(
        'callback' => 'global_filter_submission_form',
        'callback arguments' => array($block_number)
      )
    );
    return $form;
  }
}

/**
 * Creates the global selector widgets, e.g. drop-down, radio-boxes, links...
 *
 * @ingroup forms
 */
function global_filter_submission_form($form, &$form_state, $block_number) {

  if (!isset($form_state['language'])) {
    $form_state['language'] = LANGUAGE_NONE;
  }
  foreach (global_filter_get_filters_for_block($block_number) as $key => $filter) {

    $form_state['global_filters'][$key]['name'] = $filter['name'];
    $form_state['global_filters'][$key]['widget'] = $filter['widget'];
    $form_state['global_filters'][$key]['label'] = $filter['label'];

    global_filter_create_widget($key, $form, $form_state);
  }
  // Complete form with markup and visible or invisible submit button (unless
  // the form contains link widgets only
  global_filter_finalise_form($form, $block_number);

  $path = drupal_get_path('module', 'global_filter');
  $form['#attached']['css'][] = $path . '/global_filter.css';
  $form['#attributes']['class'][] = drupal_html_class('global-filter');

  return $form;
}

/**
 * Based on the requested or field-implied widget there are three main case:
 *
 * o global filter driven by a view: user may request any list widget
 * o global filter driven by a node property, search term or location proximity: textfield
 * o global filter driven by a field: widget default may be overriden by user,
 *   provided the widget default is not a text field or or date field;
 *   autocomplete fields may be overridden.
 *
 * @param $filter_key, 1, 2, 3..
 * @param $form, the form that will be added to, cannot be NULL
 * @param $form_state
 * @return nothing
 */
function global_filter_create_widget($filter_key, &$form, &$form_state) {

  $name  = $form_state['global_filters'][$filter_key]['name'];
  $widget_label = $form_state['global_filters'][$filter_key]['label'];

  $option_all_text = global_filter_get_parameter($filter_key, 'option_all_text');
  $options = empty($option_all_text)
    ? array('' => GLOBAL_FILTER_DEF_OPTION_ALL_TEXT)
    : ($option_all_text == '<none>' ? array() : array('' => $option_all_text));

  // Establish the widget type and create widget form accordingly.
  if (drupal_substr($name, 0, 4) == 'view') {

    $requested_widget = $form_state['global_filters'][$filter_key]['widget'];
    if (empty($requested_widget) || $requested_widget == 'default') {
      $requested_widget = 'select';
    }
    $view_name = drupal_substr($name, 5);
    global_filter_add_view_results($options, $view_name);
  }
  elseif (in_array($name, array(GLOBAL_FILTER_VIEWS_PROXIMITY_FIELD, GLOBAL_FILTER_VIEWS_SEARCH_TERMS_FIELD, GLOBAL_FILTER_VIEWS_SEARCH_API_FULLTEXT)) ||
          in_array($name, array_keys(global_filter_get_node_properties()))) {

    $requested_widget = 'textfield';
  }
  else { // Probably a field widget

    if (!($requested_widget = $form_state['global_filters'][$filter_key]['widget'])) {
      $requested_widget = 'default';
    }
    if ($name == GLOBAL_FILTER_VIEWS_COUNTRY_FIELD) {

      if (global_filter_get_module_parameter('take_countries_from_location_module', TRUE) && module_exists('location')) {
        // Assemble country list based on the 2-letter country codes in the location table
        $countries = array();
        $result = db_query('SELECT DISTINCT country FROM {location}');
        foreach ($result as $country) {
          $countries[$country->country] = location_country_name($country->country);
        }
      }
      else {
        // Use core's list. Note: country codes will be in uppercase
        include_once DRUPAL_ROOT . '/includes/locale.inc';
        $countries = country_get_list();
      }
      natcasesort($countries);
      $options = array_merge($options, $countries);
    }
    else {
      // Field-based widget
      $field = field_info_field($name);
      if (!$field) {
        if ($name) {
          drupal_set_message(t('The field %name used for filter #@filter does not exist. Please re-configure the associated Global Filter block.',
            array('%name' => $name, '@filter' => $filter_key)), 'error');
        }
        return;
      }
      $instance = global_filter_get_field_instance($name);

      if ($requested_widget == 'default' || drupal_substr($instance['widget']['type'], 0, 4) == 'date') {
        // Inherit native widget
        $form_state['global_filters'][$filter_key]['widget'] = $instance['widget']['type'];
        if (!empty($widget_label)) {
          $instance['label'] = ($widget_label == '<none>') ? NULL : $widget_label; // field_default_form() does check_plain()
        }
        global_filter_create_field_instance_widget($option_all_text, $field, $instance, $form, $form_state);

        $lang = $form_state['language'];
        if (empty($form[$name][$lang]['#title'])) {
          // Remove empty title so that it wont' take up any space
          unset($form[$name][$lang]['#title']);
        }
        return;
      }

      // Simple or links widget, load up the $options.
      if ($field['type'] == 'taxonomy_term_reference') {
        $vocabulary_name = $field['settings']['allowed_values'][0]['vocabulary'];
        // Only show hierarchy depth indicators for select and multi-select.
        $show_depth = drupal_substr($requested_widget, -6) == 'select';
        _global_filter_add_terms($options, $vocabulary_name, $show_depth);
      }
      elseif (!empty($field['settings']['allowed_values'])) {
        foreach (list_allowed_values($field) as $value => $label) {
          $options[$value] = $label;
        }
      }
    }
  }

  $form_state['global_filters'][$filter_key]['widget'] = $requested_widget;
  if ($requested_widget == 'links') {
    global_filter_create_links_widget($filter_key, $options, $form, $form_state);
  }
  else {
    global_filter_create_simple_widget($filter_key, $options, $form, $form_state);
  }
  if (!empty($widget_label) && $widget_label != '<none>') {
    $form[$name]['#title'] = check_plain($widget_label);
  }
}

/**
 * Cast widget in the mould of the widget configured for the supplied's field.
 *
 * @param $option_all_text
 *   Currently not used. See global_filter_options_none().
 * @param $field
 * @param $instance
 * @param $form
 * @param $form_state
 */
function global_filter_create_field_instance_widget($option_all_text, $field, $instance, &$form, &$form_state) {

  if (!isset($form['#parents'])) {
    $form['#parents'] = array(); // must be set for most widgets before creation
  }
  $name = $field['field_name'];
  $lang = $form_state['language'];

  // $items is used to set the default value on the widget
  $items = array();
  if (drupal_substr($instance['widget']['type'], 0, 4) == 'date') {
    // @todo refactor into its own function
    if (empty($form_state['input'][$name][$lang])) {
      // If this is the first time the form is presented, tell
      // hook_field_widget_form_alter() to take the date range from the session
      // and to convert it into a format compatible with the widget.
      $form_state['set_date_from_session'] = TRUE;
    }
    else {
      $items = $form_state['input'][$name][$lang];
    }
    $form_state['field'][$name][$lang] = array(
      'field' => $field,
      'instance' => $instance,
      'items_count' => 1
    );
    // Make sure that a Date global filter always appears with an end date
    $form_state['field'][$name][$lang]['field']['settings']['todate'] = TRUE; // for date_combo_element_process()
    $field['settings']['todate'] = TRUE; // for date_default_value()
  }
  else {
    // Any widget other than the Date widget.
    $session_value = global_filter_get_session_value($name);
    $items = global_filter_set_instance_widget_value($session_value, $field, $form_state);
  }

  // Uncomment next two lines to obtain control over the option list, with the
  // exception of the first 'none' option. See global_filter_options_list().
  //$field['real_module'] = $field['module'];
  //$field['module'] = 'global_filter';

  // Trying to add/suppress 'All' option. Line below doesn't have desired effect.
  // $instance['required'] = ($option_all_text == '<none>');

  // Add some context to the widget. This allows us for instance to make sure
  // that the Date widget doesn't impose its defaults.
  $instance['widget']['is_global_filter'] = TRUE;

  $form += field_default_form($instance['entity_type'], NULL, $field, $instance, $lang, $items, $form, $form_state);
}

function global_filter_create_links_widget($filter_key, $options, &$form, &$form_state) {
  $post_it = global_filter_get_module_parameter('links_widget_via_post', TRUE);
  $no_language = new stdClass();
  $no_language->language = FALSE;
  $name = $form_state['global_filters'][$filter_key]['name'];
  $selected_value = global_filter_get_session_value($name);
  $links = '';

  foreach ($options as $value => $link_text) {
    $active = is_array($selected_value) ? in_array($value, $selected_value) : $value == $selected_value;
    $link_options = array(
      'attributes' => array('title' => $link_text),
      'language' => $active ? NULL : $no_language // Hack to avoid every link being classed as 'active'
    );
    if (empty($value)) {
      $value = '';
    }
    if ($post_it) {
      $link_options['attributes']['id'] = "$name:$value";
      if ($active) {
        $link_options['attributes']['class'] = drupal_html_class('active');
      }
    }
    else {
      $link_options['query'] = array($name => $value);
    }
    $link = $post_it
      ? '<a href="" ' . drupal_attributes($link_options['attributes']) . ">$link_text</a>"
      : l($link_text, $_GET['q'], $link_options);
    $links .= ($active ? '<li class="active">' : '<li>') . $link . '</li>';
  }
  $form[$name]['#markup'] = '<ul class="global-filter-links ' . GLOBAL_FILTER_FILTER_KEY_PREFIX . "$filter_key-$name" . '">' . $links . '</ul>';
  $form[$name]['#suffix'] = '<div class="suffix">' . t('Click link to filter') . '</div>';
}

function global_filter_create_simple_widget($filter_key, $options, &$form, &$form_state) {
  $name   = $form_state['global_filters'][$filter_key]['name'];
  $widget = $form_state['global_filters'][$filter_key]['widget'];

  $default_value = isset($form_state['input'][$name])
    ? $form_state['input'][$name]
    : global_filter_get_session_value($name);

  if (is_array($default_value)) {
    if ($widget == 'radios' || $widget == 'textfield') {
      $default_value = reset($default_value);
    }
  }
  else {
    if ($widget == 'checkboxes') {
      $default_value = array($default_value);
    }
  }
  $form[$name] = array(
    '#type' => ($widget == 'multiselect') ? 'select' : $widget,
    '#default_value' => $default_value,
    '#description' => empty($description) ? NULL : $description
  );
  if ($widget != 'textfield' && !empty($options)) {
    $form[$name]['#options'] = $options;
    $form[$name]['#multiple'] = in_array($widget, array('multiselect', 'checkboxes'));
  }
}

function global_filter_finalise_form(&$form, $block_number) {
  // Preserve filter order as selected on the block configuration page
  $num_filters = 0;
  foreach ($form as $key => &$filter_element) {
    if (drupal_substr($key, 0, 1) != '#') {
      $filter_element['#weight'] = ++$num_filters;
    }
  }
  $submit_required = $button_required = FALSE;
  foreach ($filters = global_filter_get_filters_for_block($block_number) as $key => $filter) {

    $name = $filter['name'];
    $filter_delta = GLOBAL_FILTER_FILTER_KEY_PREFIX . $key;

    // We're adding a class rather than an id as it needs to be attached to all
    // of the <input>'s of each sequence of check boxes or radio buttons.
    $form[$name]['#attributes']['class'][] = "$filter_delta-$name";

    $confirm_question = global_filter_get_parameter($key, 'confirm_question');
    $auto_submit = global_filter_get_parameter($key, 'set_on_select');

    if ($filter['widget'] != 'links') {
      $submit_required = TRUE;
      if (!$auto_submit) {
        $button_required = TRUE;
      }
    }

    if ($confirm_question || $auto_submit) {
      drupal_add_js(array($filter_delta => array("$filter_delta-$name", $confirm_question, $auto_submit)), 'setting');
      $form[$name]['#attached']['js'][] = drupal_get_path('module', 'global_filter') . '/js/global_filter_all.js';
    }
  }
  if (global_filter_get_module_parameter('links_widget_via_post', TRUE)) {
    drupal_add_js(array('links_widget_via_post' => TRUE), 'setting');
  }
  if ($submit_required) {
    $form['submit'] = array(
      '#type' => 'submit',
      '#value' => t('Set'),
      '#submit' => array('global_filter_set_form_on_session'),
      '#attributes' => array('class' => array(
        drupal_html_class('global-filter-set-' . ($num_filters > 1 ? 'all' : $filter['widget']))
      )),
      '#weight' => ++$num_filters,
    );
    if (!$button_required) {
      // Suppress the 'Set' submit button defined above.
      $form['submit']['#attributes']['style'][] = 'display:none';
    }
  }
}

function global_filter_add_view_results(&$options, $view_id) {
  $view = views_get_view($view_id);
  if (!is_object($view)) {
    drupal_set_message(t('Global Filter: could not find view: %view.', array(
      '%view' => empty($view_id) ? t('no name specified') : $view_id)), 'error');
    return FALSE;
  }
  $view->init_display();
  $view->pre_execute();
  $view->execute();
  // Pick the first non-id field of each returned row as the next value for
  // the filter.
  foreach ($view->result as $row) {
    $row_as_array = (array)$row;
    foreach ($row_as_array as $fid => $value) {
      if ($fid != $view->base_field) { // e.g. 'nid', 'uid', 'cid', 'tid', 'aid' {accesslog}
        break;
      }
    }
    $key = isset($row_as_array[$view->base_field]) ? $row_as_array[$view->base_field] : NULL;
    $options[empty($key) ? $value : $key] = $value;
  }
}

function global_filter_get_field_instance($field_name) {
  foreach (field_info_instances() as $type_bundles) {
    foreach ($type_bundles as $bundle_instances) {
      foreach ($bundle_instances as $f_name => $instance) {
        if ($f_name == $field_name) {
          return $instance;
        }
      }
    }
  }
  return NULL;
}

function global_filter_set_instance_widget_value($session_value, $field, $form_state) {
  $name = $field['field_name'];
  $lang = $form_state['language'];

  $form_input  = isset($form_state['input' ][$name][$lang]) ? $form_state['input' ][$name][$lang] : NULL;
  $form_values = isset($form_state['values'][$name][$lang]) ? $form_state['values'][$name][$lang] : NULL;

  if (is_array($form_input)) {
    $value = $form_input;
  }
  if (is_array($form_values)) {
    // Usually this means an autocomplete taxonomy, retrieve the term id.
    $form_values = reset($form_values);
    $value = empty($form_values['tid']) ? $form_values['name'] : $form_values['tid'];
  }

  if (empty($value)) {
    $value = $session_value;
  }
  // $items is used to set defaults. Must use this format (multi-valued):
  //   $items[0][$key] = 4
  //   $items[1][$key] = 23
  // where $key tends to equal 'value' or 'tid'
  $items = array();
  $key = key($field['columns']);
  if (!empty($value) && is_array($value)) {
    foreach (global_filter_array_flatten($value) as $value) {
      $items[] = array($key => $value);
    }
  }
  else {
    $items[0][$key] = $value;
  }
  // If nothing set, return something that represents 'All'. Otherwise the
  // field widget will set the instance default.
  return empty($items) ? array(0 => array()) : $items;
}

/**
 * Stashes the selected global filter value(s) in the user's session.
 *
 * @param array $form
 * @param array $form_state
 */
function global_filter_set_form_on_session($form, &$form_state) {
  $is_done = &drupal_static(__FUNCTION__, array());

  $lang = $form_state['language'];

  foreach ($form_state['global_filters'] as $filter_key => $info) {

    if (empty($is_done[$filter_key])) {

      $name = $info['name'];
      $widget = $info['widget'];

      if (drupal_substr($widget, 0, 4) == 'date') {
        // If successful this function returns a date range in the format
        // YYYY-MM-DD--YYYY-MM-DD, which is what Views' contextual filters need.
        $session_value = global_filter_extract_date_range($form_state, $filter_key);
        global_filter_set_on_session($name, $session_value);
      }
      elseif (isset($form_state['values'][$name])) {
        // The rest of the widgets, both single and multi-choice.
        $form_values = $form_state['values'][$name];
        if (is_array($form_values)) {
          // $lang level won't be there for simple widgets
          if (empty($form_values[$lang])) {
            $session_value = array_values($form_values);
          }
          else {
            $session_value = array();
            foreach ($form_values[$lang] as $v) {
              $session_value[] = is_array($v) ? reset($v) : $v;
            }
          }
        }
        else {
          $session_value = $form_values;
        }
        global_filter_set_on_session($name, $session_value);
      }
      $is_done[$filter_key] = TRUE;
    }
  }
  // If rebuild=FALSE there will be an unnecessary drupal_goto(), so need to
  // force it not to redirect.
  // @see drupal_redirect_form()
  $form_state['rebuild'] = FALSE;
  $form_state['no_redirect'] = TRUE; // unless set-on-init==TRUE?
}

function _global_filter_add_terms(&$options, $vocabulary_machine_name, $show_depth = TRUE) {
  if (!module_exists('taxonomy')) {
    drupal_set_message(t('Global Filter: using vocabulary %vocabulary, but Taxonomy module is not enabled.', array('%vocabulary' => $vocabulary_machine_name)), 'error');
    return;
  }
  if (!empty($vocabulary_machine_name)) {
    foreach (taxonomy_get_vocabularies() as $vid => $vocabulary) {
      $found = ($vocabulary->machine_name == $vocabulary_machine_name);
      if ($found) {
        break;
      }
    }
  }
  if (empty($found)) {
    drupal_set_message(t('Global Filter: the vocabulary %vocabulary does not exist.', array('%vocabulary' => $vocabulary_machine_name)), 'error');
  }
  else {
    foreach (taxonomy_get_tree($vid) as $term) {
      // If $show_depth is set, we follow core's way and add one hyphen for each
      // hierarchy level.
      $options[$term->tid] = $show_depth ? (str_repeat('-', $term->depth) . $term->name) : $term->name;
    }
  }
}

/**
 * Quick and dirty way to flatten an array.
 *
 * @param $array
 * @return flattened array
 */
function global_filter_array_flatten($array) {
  foreach ($array as $key => $value) {
    $array[$key] = (array)$value;
  }
  return call_user_func_array('array_merge', $array);
}

/**
 * Implements hook_theme_registry_alter().
 *
 * Override theme_options_none() (options.module) to make the '- None -' text
 * configurable for buttons and select lists, but only for Global Filter
 * widgets, see function global_filter_options_none() below.
 */
function global_filter_theme_registry_alter(&$theme_registry) {
  $theme_registry['options_none']['function'] = 'global_filter_options_none';
  $theme_registry['options_none']['theme_path'] = drupal_get_path('module', 'global_filter');
}

/*
 * theme_options_none() override.
 *
 * In addition to the regular options as returned by hook_options_list, the
 * Options module will always prepend a 'none' for non-required fields, whether
 * appearing as a single or multiple-select. We can't intercept this process.
 * We could make the select mandatory and then prepend a 'none' option
 * ourselves, but than we end up with a red asterisk for a select that isn't
 * really mandatory...
 *
 * Until I can find a way to determine if this is a global filter context,
 * I'll switch this feature off for global filters driven by field widgets.
 */
function global_filter_options_none($variables) {
  if (!empty($variables['global_filter_context'])) { // see comment above
    $filter_key = global_filter_key_by_name($variables['instance']['field_name']);
    $option_all_text = global_filter_get_parameter($filter_key, 'option_all_text');
    if (!empty($option_all_text)) {
      return $option_all_text == t('<none>') ? '' : check_plain($option_all_text);
    }
  }
  // Not used in a global filter context or no 'All' text specified, so return
  // the widget default.
  return theme_options_none($variables);
}

function global_filter_options_list($field, $instance) {
  $options = (array) module_invoke($field['real_module'], 'options_list', $field, $instance);
  // ...
  return $options;
}

//----- Date handling functions -----//

/**
 * Implements hook_field_widget_properties_alter().
 *
 * Called from field_default_form() this alters the widget properties of a
 * field instance before it gets displayed.
 * Used here to make sure that the Date module doesn't impose its defaults on
 * the widget, as we already do that based on the session when
 * 'set_date_from_session' is set on the form_state.
 * @see global_filter_field_widget_form_alter()
 */
function global_filter_field_widget_properties_alter(&$widget, $context) {
  if ($widget['module'] == 'date' && !empty($widget['is_global_filter'])) {
    $widget['is_new'] = FALSE;
  }
}

/**
 * Implements hook_date_combo_process_alter().
 *
 * Remove the 'Show End Date' checkbox and line up the start and end date boxes.
 */
function global_filter_date_combo_process_alter(&$element, &$form_state, &$context) {
  if (!empty($context['form']['#id']) && drupal_substr($context['form']['#id'], 0, 13) == 'global-filter') {
    unset($element['show_todate']); // remove 'Show End Date' checkbox
    if (empty($element['value']['#title'])) {
      // Remove 'to:' from end date box so that it lines up with start date box
      unset($element['value2']['#title']);
    }
  }
}

/**
 * Implements hook_field_widget_form_alter().
 *
 * Called from field_default_form().
 * Responds to 'set_date_from_session' being set on the $form_state.
 */
function global_filter_field_widget_form_alter(&$element, &$form_state, $context) {

  if (!empty($form_state['set_date_from_session'])) {
    $session_value = global_filter_get_session_value($element['#field_name']);

    $date_range = new date_sql_handler();
    $parts = $date_range->arg_parts($session_value);

    if (!empty($parts[0]['date'])) {
      $field = $context['field'];
      $instance = $context['instance'];
      $lang = $context['langcode'];
      $instance['settings']['default_value'] = 'strtotime';
      $instance['settings']['default_value_code']  = implode('-', $parts[0]['date']);
      if (!empty($parts[1]['date'])) {
        $instance['settings']['default_value2'] = 'strtotime';
        $instance['settings']['default_value_code2'] = implode('-', $parts[1]['date']);
      }
      $default_date_range = date_default_value($field, $instance, $lang);
      $element['#default_value'] = reset($default_date_range);
    }
  }
}

/**
 * Convert the date range received on the form to the format YYYY-MM-DD--YYYY-MM-DD.
 *
 * @param $form_state
 * @return date range in the format YYYY-MM-DD--YYYY-MM-DD
 */
function global_filter_extract_date_range($form_state, $filter_key) {
  $name = $form_state['global_filters'][$filter_key]['name'];
  $lang = $form_state['language'];
  if (empty($form_state['input'][$name][$lang][0]) || !is_array($form_state['input'][$name][$lang][0])) {
    // Not a date
    return FALSE;
  }
  $values = $form_state['input'][$name][$lang][0];
  if (isset($values['value']['date'])) { // from date_popup
    $date_string = $values['value']['date'];
    $time_string = empty($values['value']['time']) ? '' : $values['value']['time'];
    if (!empty($date_string)) {
      // @todo Add support for hours and minutes
      $timestamp = strtotime($date_string);
      $value = format_date($timestamp, 'custom', 'Y-m-d');
      if (!empty($values['value2']['date'])) {
        $timestamp2 = strtotime($values['value2']['date']);
        $value .= '--' . format_date($timestamp2, 'custom', 'Y-m-d');
      }
    }
  }
  elseif (!empty($values['value']['day'])) { // from_date_select
    $value = $form_state['input'][$name][$lang][0]['value'];
    $day = drupal_strlen($value['day']) == 1 ? ('0' . $value['day']) : $value['day'];
    $month = drupal_strlen($value['month']) == 1 ? ('0' . $value['month']) : $value['month'];
    $value = $value['year'] . '-' . $month . '-' . $day;
    if (!empty($form_state['input'][$name][$lang][0]['value2']['day'])) {
      $value2 = $form_state['input'][$name][$lang][0]['value2'];
      $day = drupal_strlen($value2['day']) == 1 ? ('0' . $value2['day']) : $value2['day'];
      $month = drupal_strlen($value2['month']) == 1 ? ('0' . $value2['month']) : $value2['month'];
      $value .= '--' . $value2['year'] . '-' . $month . '-' . $day;
    }
  }
  // Check for corrupt date and return.
  return (empty($value) || drupal_strlen($value) < 10) ? '' : $value;
}