<?php
 /**
  * This template is used to print a single field in a view. It is not
  * actually used in default Views, as this is registered as a theme
  * function which has better performance. For single overrides, the
  * template is perfectly okay.
  *
  * Variables available:
  * - $view: The view object
  * - $field: The field handler object that can process the input
  * - $row: The raw SQL result that can be used
  * - $output: The processed output that will normally be used.
  *
  * When fetching output from the $row, this construct should be used:
  * $data = $row->{$field->field_alias}
  *
  * The above will guarantee that you'll always get the correct data,
  * regardless of any changes in the aliasing that might happen if
  * the view is modified.
  */
?>
<?php

  // If user has registered to attend an event virtally, modify the location
  // information displayed.
  if (isset($view->args[2]) && strtolower($view->args[2]) == 'virtual') {

    switch ($field->real_field) {
      case 'field_gsa_venue_value':
        print t('You registered to attend this event virtually. Please refer to the event description for details.');
        break;
    
      case 'field_gsa_room_value':
      case 'field_gsa_address_1_value':
      case 'field_gsa_address_2_value':
      case 'field_gsa_city_value':
      case 'field_gsa_state_value':
      case 'field_gsa_zip_value':
      case 'field_gsa_country_value':
      case 'field_gsa_hotel_information_value':
        break;
        
      default:
        print $output;
    }
  } else {
    print $output;
  }
?>
