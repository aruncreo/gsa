<?php
/**
 * @file gsa_map_title_plugin_style.inc
 */


/**
* handler to extend the default style plugin of leaflet views
*/
class gsa_map_title_plugin_style extends leaflet_views_plugin_style{
	
  function options_form(&$form,&$form_state){
  	parent::options_form($form,$form_state);
	
	// Defining new option in leaflet map format setting page
	$form['group_title'] = array(
	  '#type' => 'radios',
	  '#title' => t('Group Title'),
	  '#description' => t('Allow multiple title at a single geolocation'),
	  '#options'  => array( 0 => 'No', 1 => 'Yes'),
	  '#required' => FALSE,
	  '#default_value'   => isset($this->options['group_title'])?$this->options['group_title']:0,
	);
    
	
  }
  
  function render($values){
    if (!empty($this->view->live_preview)) {
      return t('No preview available');
    }

    $data = array();
	$des_array=array();
    if ($this->options['data_source']) {
      $this->render_fields($this->view->result);
      foreach ($this->view->result as $id => $result) {
        $geofield = $this->get_field_value($id, $this->options['data_source']);

        if (!empty($geofield)) {
          $points = leaflet_process_geofield($geofield);

          // Render the entity with the selected view mode
          if ($this->options['description_field'] === '#rendered_entity' && is_object($result)) {
            $entities = entity_load($this->entity_type, array($result->{$this->entity_info['entity keys']['id']}));

            $build = entity_view(
              $this->entity_type,
              $entities,
              $this->options['view_mode']
            );

            $description = drupal_render($build);
          }
		  

          // Normal rendering via fields
          elseif ($this->options['description_field']) {
		  	$lat = ($points[0]['lat']!="") ? "lat".round($points[0]['lat'],6) : 0;
			$lon = ($points[0]['lon']!="") ? "lon".round($points[0]['lon'],6) : 0;
		  	// Checking weather grouping of title is allowed in map
		  	if ($this->options['group_title'] == 1) {
              $des_array[$lat][$lon][] .= $this->rendered_fields[$id][$this->options['description_field']];
			}else{
		      $des_array[$lat][$lon][] = $this->rendered_fields[$id][$this->options['description_field']];
			}
          }

          // Attach pop-ups if we have a description field
		
          if (isset($des_array[$lat][$lon])) {
            foreach ($points as &$point) {
              $point['popup'] = implode('<br/>',$des_array[$lat][$lon]);
            }
          }

          // Attach also titles, they might be used later on
          if ($this->options['name_field']) {
            foreach ($points as &$point) {
              $point['label'] = $this->rendered_fields[$id][$this->options['name_field']];
            }
          }

          // Let modules modify the points data.
          drupal_alter('leaflet_views_alter_points_data', $result, $points);

          $data = array_merge($data, $points);

          if (!empty($this->options['icon']) && $this->options['icon']['iconUrl']) {
            foreach ($data as $key => $feature) {
              $data[$key]['icon'] = $this->options['icon'];
            }
          }
        }
     }

	 $map = leaflet_map_get_info($this->options['map']);

      if (!empty($data) || (isset($this->options['hide_empty']) && !$this->options['hide_empty'])) {
        return leaflet_render_map($map, $data, $this->options['height'] . 'px');
      }
    }

    return '';
		
  }
  
}