<?php

/**
 * Return an array of locations
 */
function gsa_salesforce_get_locations() {
  return array(
    'AE' => array('name' => 'AE - US Forces Europe', 'region' => '3'),
    'AK' => array('name' => 'AK - Alaska', 'region' => '10'),
    'AL' => array('name' => 'AL - Alabama', 'region' => '4'),
    'AP' => array('name' => 'AP - US Forces Pacific', 'region' => '9'),
    'AR' => array('name' => 'AR - Arkansas', 'region' => '7'),
    'AS' => array('name' => 'AS - American Samoa', 'region' => '9'),
    'AZ' => array('name' => 'AZ - Arizona', 'region' => '9'),
    'CA' => array('name' => 'CA - California', 'region' => '9'),
    'CO' => array('name' => 'CO - Colorado', 'region' => '8'),
    'CT' => array('name' => 'CT - Connecticut', 'region' => '1'),
    'DC' => array('name' => 'DC - District of Columbia', 'region' => '11 - NCR'),
    'DE' => array('name' => 'DE - Delaware', 'region' => '3'),
    'FL' => array('name' => 'FL - Florida', 'region' => '4'),
    'FM' => array('name' => 'FM - Federated States of Micronesia', 'region' => '9'),
    'GA' => array('name' => 'GA - Georgia', 'region' => '4'),
    'GU' => array('name' => 'GU - Guam', 'region' => '9'),
    'HI' => array('name' => 'HI - Hawaii', 'region' => '9'),
    'IA' => array('name' => 'IA - Iowa', 'region' => '6'),
    'ID' => array('name' => 'ID - Idaho', 'region' => '10'),
    'IL' => array('name' => 'IL - Illinois', 'region' => '5'),
    'IN' => array('name' => 'IN - Indiana', 'region' => '5'),
    'KS' => array('name' => 'KS - Kansas', 'region' => '6'),
    'KY' => array('name' => 'KY - Kentucky', 'region' => '4'),
    'LA' => array('name' => 'LA - Louisiana', 'region' => '7'),
    'MA' => array('name' => 'MA - Massachusetts', 'region' => '1'),
    'MD' => array('name' => 'MD - Maryland', 'region' => '3'),
    'ME' => array('name' => 'ME - Maine', 'region' => '1'),
    'MH' => array('name' => 'MH - Marshall Islands', 'region' => '9'),
    'MI' => array('name' => 'MI - Michigan', 'region' => '5'),
    'MN' => array('name' => 'MN - Minnesota', 'region' => '5'),
    'MO' => array('name' => 'MO - Missouri', 'region' => '6'),
    'MP' => array('name' => 'MP - Northern Mariana Islands', 'region' => '9'),
    'MS' => array('name' => 'MS - Mississippi', 'region' => '4'),
    'MT' => array('name' => 'MT - Montana', 'region' => '8'),
    'NC' => array('name' => 'NC - North Carolina', 'region' => '4'),
    'ND' => array('name' => 'ND - North Dakota', 'region' => '8'),
    'NE' => array('name' => 'NE - Nebraska', 'region' => '6'),
    'NH' => array('name' => 'NH - New Hampshire', 'region' => '1'),
    'NJ' => array('name' => 'NJ - New Jersey', 'region' => '2'),
    'NM' => array('name' => 'NM - New Mexico', 'region' => '7'),
    'NV' => array('name' => 'NV - Nevada', 'region' => '9'),
    'NY' => array('name' => 'NY - New York', 'region' => '2'),
    'OH' => array('name' => 'OH - Ohio', 'region' => '5'),
    'OK' => array('name' => 'OK - Oklahoma', 'region' => '7'),
    'OR' => array('name' => 'OR - Oregon', 'region' => '10'),
    'PA' => array('name' => 'PA - Pennsylvania', 'region' => '3'),
    'PR' => array('name' => 'PR - Puerto Rico', 'region' => '2'),
    'PW' => array('name' => 'PW - Palau', 'region' => '9'),
    'RI' => array('name' => 'RI - Rhode Island', 'region' => '1'),
    'SC' => array('name' => 'SC - South Carolina', 'region' => '4'),
    'SD' => array('name' => 'SD - South Dakota', 'region' => '8'),
    'TN' => array('name' => 'TN - Tennessee', 'region' => '4'),
    'TX' => array('name' => 'TX - Texas', 'region' => '7'),
    'UT' => array('name' => 'UT - Utah', 'region' => '8'),
    'VA' => array('name' => 'VA - Virginia', 'region' => '3'),
    'VI' => array('name' => 'VI - Virgin Islands', 'region' => '2'),
    'VT' => array('name' => 'VT - Vermont', 'region' => '1'),
    'WA' => array('name' => 'WA - Washington', 'region' => '10'),
    'WI' => array('name' => 'WI - Wisconsin', 'region' => '5'),
    'WV' => array('name' => 'WV - West Virginia', 'region' => '3'),
    'WY' => array('name' => 'WY - Wyoming', 'region' => '8'),
  );
}

/**
 * Provide options suitable for a form select element.
 *
 * @return
 *   Array of location names keyed by US postal state (or other) abbreviation.
 */
function gsa_salesforce_locations_options() {
  $options = array();
  foreach (gsa_salesforce_get_locations() as $key => $values) {
    $options[$key] = $values['name'];
  }
  return $options;
}

/**
 * Determine the GSA region for a location.
 *
 * @param $code
 *   String value matching a US postal state (or other) abbreviation.
 *
 * @return
 *   String indicating region number and optional label.
 */
function gsa_salesforce_get_region($code) {
  $locations = gsa_salesforce_get_locations();
  if (isset($locations[$code])) {
    return $locations[$code]['region'];
  }
  return NULL;
}

/**
 * Determine the location by providing an abbreviation
 * 
 * @param $abbr
 *   The location abbreviation
 * @return
 *   The location, if one is found
 */
function gsa_salesforce_get_location_by_abbr($abbr) {
  $abbr = strtoupper($abbr);
  $locations = gsa_salesforce_get_locations();
  if (isset($locations[$abbr])) {
    return $locations[$abbr]['name'];
  }
  return NULL;
}

