<?php

class views_handler_filter_gsa_cpat_reviewed extends views_handler_filter_in_operator {
  function construct() {
    parent::construct();
    $this->value_form_type = 'radios';
  }  
  
  function get_value_options() {
    $this->value_title = t('Status');
    $this->value_options = $this->allowed_values();
  }

  function allowed_values() {
    return array(
      0 => t('Unreviewed'),
      1 => t('Reviewed'),
    );
  }
}
