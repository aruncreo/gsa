<?php

/**
 * Implementation of hook_feeds_importer_default().
 */
function gsa_bpa_feeds_importer_default1() {
  $export = array();
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'bpa_csv_standalone_importer';
  $feeds_importer->config = array(
    'name' => 'BPA CSV standalone importer',
    'description' => '',
    'fetcher' => array(
      'plugin_key' => 'FeedsFileFetcher',
      'config' => array(
        'direct' => FALSE,
      ),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsCSVParser',
      'config' => array(
        'delimiter' => ',',
        'no_headers' => 0,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'BPANodeProcessor',
      'config' => array(
        'content_type' => 'bpa_listing',
        'input_format' => '0',
        'update_existing' => '1',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'BPA Number',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'Issuing Agency',
            'target' => 'field_bpa_listing_agency',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'Product or Service',
            'target' => 'field_bpa_listing_product',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'BPA End Date',
            'target' => 'field_bpa_listing_end_date:start',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'Agency POC',
            'target' => 'field_bpa_listing_poc',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'View Terms and Conditions',
            'target' => 'field_bpa_listing_terms:url',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'Socio-economic',
            'target' => 'field_bpa_listing_socioeconomic',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'Authorized Users',
            'target' => 'field_bpa_listing_authorized',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'BPA Number',
            'target' => 'title',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'View Items',
            'target' => 'field_bpa_listing_url:url',
            'unique' => FALSE,
          ),
          10 => array(
            'source' => 'Vendor Name',
            'target' => 'field_bpa_listing_vendor_name',
            'unique' => FALSE,
          ),
        ),
        'author' => 0,
        'authorize' => 0,
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '-1',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['bpa_csv_standalone_importer'] = $feeds_importer;
  $feeds_importer = new stdClass;
  $feeds_importer->disabled = FALSE; /* Edit this to true to make a default feeds_importer disabled initially */
  $feeds_importer->api_version = 1;
  $feeds_importer->id = 'bpa_importer';
  $feeds_importer->config = array(
    'name' => 'BPA SOAP importer',
    'description' => 'Import BPA listings data from SOAP server',
    'fetcher' => array(
      'plugin_key' => 'SOAPFetcher',
      'config' => array(),
    ),
    'parser' => array(
      'plugin_key' => 'FeedsXPathParserXML',
      'config' => array(
        'sources' => array(
          'xpathparser:0' => '@number',
          'xpathparser:1' => 'IssuingAgency',
          'xpathparser:2' => 'ProductOrService',
          'xpathparser:3' => 'SocioEconomic',
          'xpathparser:4' => 'AuthorizedUsers',
          'xpathparser:5' => 'EndDate',
          'xpathparser:6' => 'TermsAndConditions',
          'xpathparser:7' => 'AgencyPoc',
          'xpathparser:8' => '$guid',
          'xpathparser:9' => 'substring-before(TermsAndConditions, \',\')',
        ),
        'rawXML' => array(
          'xpathparser:0' => 0,
          'xpathparser:1' => 0,
          'xpathparser:2' => 0,
          'xpathparser:3' => 0,
          'xpathparser:4' => 0,
          'xpathparser:5' => 0,
          'xpathparser:6' => 0,
          'xpathparser:7' => 0,
          'xpathparser:8' => 0,
          'xpathparser:9' => 0,
        ),
        'context' => '//Bpa',
        'exp' => array(
          'errors' => 1,
          'tidy' => 0,
          'tidy_encoding' => 'UTF8',
          'debug' => array(
            'xpathparser:8' => 'xpathparser:8',
            'context' => 0,
            'xpathparser:0' => 0,
            'xpathparser:1' => 0,
            'xpathparser:2' => 0,
            'xpathparser:3' => 0,
            'xpathparser:4' => 0,
            'xpathparser:5' => 0,
            'xpathparser:6' => 0,
            'xpathparser:7' => 0,
            'xpathparser:9' => 0,
          ),
        ),
        'allow_override' => 1,
      ),
    ),
    'processor' => array(
      'plugin_key' => 'BPANodeProcessor',
      'config' => array(
        'content_type' => 'bpa_listing',
        'input_format' => '0',
        'update_existing' => '3',
        'expire' => '-1',
        'mappings' => array(
          0 => array(
            'source' => 'xpathparser:0',
            'target' => 'guid',
            'unique' => 1,
          ),
          1 => array(
            'source' => 'xpathparser:1',
            'target' => 'field_bpa_listing_agency',
            'unique' => FALSE,
          ),
          2 => array(
            'source' => 'xpathparser:2',
            'target' => 'field_bpa_listing_product',
            'unique' => FALSE,
          ),
          3 => array(
            'source' => 'xpathparser:3',
            'target' => 'field_bpa_listing_socioeconomic',
            'unique' => FALSE,
          ),
          4 => array(
            'source' => 'xpathparser:4',
            'target' => 'field_bpa_listing_authorized',
            'unique' => FALSE,
          ),
          5 => array(
            'source' => 'xpathparser:5',
            'target' => 'field_bpa_listing_end_date:start',
            'unique' => FALSE,
          ),
          6 => array(
            'source' => 'xpathparser:6',
            'target' => 'field_bpa_listing_terms:url',
            'unique' => FALSE,
          ),
          7 => array(
            'source' => 'xpathparser:7',
            'target' => 'field_bpa_listing_poc',
            'unique' => FALSE,
          ),
          8 => array(
            'source' => 'xpathparser:8',
            'target' => 'title',
            'unique' => FALSE,
          ),
          9 => array(
            'source' => 'xpathparser:9',
            'target' => 'field_bpa_listing_terms:url',
            'unique' => FALSE,
          ),
        ),
        'author' => '1',
        'authorize' => 1,
        'og_node_group' => '1',
      ),
    ),
    'content_type' => '',
    'update' => 0,
    'import_period' => '1800',
    'expire_period' => 3600,
    'import_on_create' => 1,
  );

  $export['bpa_importer'] = $feeds_importer;
  return $export;
}
