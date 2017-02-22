<?php

class gsa_event_field extends views_handler_field_field {
 
  function option_definition() {
    $options = parent::option_definition();
    
        $options['sum_field_value'] = array(
      'default' => TRUE,
      'bool' => TRUE,
    );
       $options['sum_field_value_prefix'] = array(
      'default' => '',
     
    );
    
    
    
    return $options;
  }
  
    /**
   * Provide options for multiple value fields.
   */
  function multiple_options_form(&$form, &$form_state) {
  $field = $this->field_info;

    $form['multiple_field_settings'] = array(
      '#type' => 'fieldset',
      '#title' => t('Multiple field settings'),
      '#collapsible' => TRUE,
      '#collapsed' => TRUE,
      '#weight' => 5,
    );

    $form['group_rows'] = array(
      '#title' => t('Display all values in the same row'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['group_rows'],
      '#description' => t('If checked, multiple values for this field will be shown in the same row. If not checked, each value in this field will create a new row. If using group by, please make sure to group by "Entity ID" for this setting to have any effect.'),
      '#fieldset' => 'multiple_field_settings',
    );
$form['sum_field_value'] = array(
	  '#type' => 'radios',
	  '#title' => t('Sum field value'),
	  '#description' => t('Allow multiple title at a single geolocation'),
	  '#options'  => array( 0 => 'No', 1 => 'Yes'),
	  '#required' => FALSE,
	  '#default_value'   => $this->options['sum_field_value'],
	   '#fieldset' => 'multiple_field_settings',
	);
    
       $form['sum_field_value_prefix'] = array(
       '#title' => 'Add field prefix',
      '#type' => 'textfield',
      '#default_value' => $this->options['sum_field_value_prefix'],
      '#fieldset' => 'multiple_field_settings',
    );

    // Make the string translatable by keeping it as a whole rather than
    // translating prefix and suffix separately.
    list($prefix, $suffix) = explode('@count', t('Display @count value(s)'));

    if ($field['cardinality'] == FIELD_CARDINALITY_UNLIMITED) {
      $type = 'textfield';
      $options = NULL;
      $size = 5;
    }
    else {
      $type = 'select';
      $options = drupal_map_assoc(range(1, $field['cardinality']));
      $size = 1;
    }
    $form['multi_type'] = array(
      '#type' => 'radios',
      '#title' => t('Display type'),
      '#options' => array(
        'ul' => t('Unordered list'),
        'ol' => t('Ordered list'),
        'separator' => t('Simple separator'),
      ),
      '#dependency' => array('edit-options-group-rows' => array(TRUE)),
      '#default_value' => $this->options['multi_type'],
      '#fieldset' => 'multiple_field_settings',
    );

    $form['separator'] = array(
      '#type' => 'textfield',
      '#title' => t('Separator'),
      '#default_value' => $this->options['separator'],
      '#dependency' => array(
        'radio:options[multi_type]' => array('separator'),
        'edit-options-group-rows' => array(TRUE),
      ),
      '#dependency_count' => 2,
      '#fieldset' => 'multiple_field_settings',
    );
 
    $form['delta_limit'] = array(
      '#type' => $type,
      '#size' => $size,
      '#field_prefix' => $prefix,
      '#field_suffix' => $suffix,
      '#options' => $options,
      '#default_value' => $this->options['delta_limit'],
      '#prefix' => '<div class="container-inline">',
      '#dependency' => array('edit-options-group-rows' => array(TRUE)),
      '#fieldset' => 'multiple_field_settings',
    );

    list($prefix, $suffix) = explode('@count', t('starting from @count'));
    $form['delta_offset'] = array(
      '#type' => 'textfield',
      '#size' => 5,
      '#field_prefix' => $prefix,
      '#field_suffix' => $suffix,
      '#default_value' => $this->options['delta_offset'],
      '#dependency' => array('edit-options-group-rows' => array(TRUE)),
      '#description' => t('(first item is 0)'),
      '#fieldset' => 'multiple_field_settings',
    );
    $form['delta_reversed'] = array(
      '#title' => t('Reversed'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['delta_reversed'],
      '#suffix' => $suffix,
      '#dependency' => array('edit-options-group-rows' => array(TRUE)),
      '#description' => t('(start from last values)'),
      '#fieldset' => 'multiple_field_settings',
    );
    $form['delta_first_last'] = array(
      '#title' => t('First and last only'),
      '#type' => 'checkbox',
      '#default_value' => $this->options['delta_first_last'],
      '#suffix' => '</div>',
      '#dependency' => array('edit-options-group-rows' => array(TRUE)),
      '#fieldset' => 'multiple_field_settings',
    );
    
  	}
  
  
function render_items($items) {
    if (!empty($items)) {
    	
     	
      if($this->options['sum_field_value']){
      	if(count($items)>1){
		  $sum_field_value = 0;
      	  foreach($items as $item){
      	    $sum_field_value+=$item;	
		  }
		  return $this->options['sum_field_value_prefix'].' '.$sum_field_value;
		}
      	
	  } 
      if (!$this->options['group_rows']) {
        return implode('', $items);
      }

      if ($this->options['multi_type'] == 'separator') {
        return implode(filter_xss_admin($this->options['separator']), $items);
      }
      else {
        return theme('item_list',
          array(
            'items' => $items,
            'title' => NULL,
            'type' => $this->options['multi_type']
          ));
      }
    }
  }
 
}

