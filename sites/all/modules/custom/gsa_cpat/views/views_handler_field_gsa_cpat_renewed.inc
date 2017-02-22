<?php

class views_handler_field_gsa_cpat_renewed extends views_handler_field {
  function render($values) {
    return $values->gsa_cpat_message_reviewed ? t('Reviewed') : t('Unreviewed');
  }
}
