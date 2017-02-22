<?php
// $Id$

/**
 * @file
 * Home of the FeedsSOAPFetcher and related classes.
 * Depends on soapclient module.
 *
 * Initial version by roderik (http://drupal.org/user/8841),
 * based on various files in Feeds distribution by alex_b
 * and SOAP Client module by ilo.
 *
 * Feel free to change any code and comments, if you can support this code better than I can.
 */

/**
 * Definition of the import batch object created on the fetching stage by
 * FeedsFileFetcher.
 */
class FeedsSOAPBatch extends FeedsImportBatch {
  protected $config;

  // Apparently needed in case FeedsImportBatch::getFilePath() ever gets called?
  // We don't do anything with this.
  protected $file_path;

  /**
   * Constructor.
   */
  public function __construct($config) {
    $this->config = $config;
    parent::__construct();
  }

  /**
   * Implementation of FeedsImportBatch::getRaw().
   */
  public function getRaw() {

	ini_set("soap.wsdl_cache_enabled", "0");
  	// code largely taken from soapclient_test_submit()

    $param_str = preg_replace('/[\s]*=[\s]*/', '=', $this->config['arguments']);
    $params    = split("\n", $param_str);

    $args = array();
    foreach ($params as $param) {
      list($name, $value) = split('=', $param);

      if ( isset($value) ) {
        $args[$name] = trim($value);
      }
      else {
        $args[] = trim($name);
      }
    }

    $option_param_str = preg_replace('/[\s]*=[\s]*/', '=', $this->config['connect_options']);
    $option_params = split("\n", $option_param_str);

    $connect_args = array();
    foreach ($option_params as $param) {
      list($name, $value) = split('=', $param);

      if ( isset($value) ) {
        $connect_args[$name] = trim($value);
      }
      else {
        $connect_args[] = trim($name);
      }
    }

    $options = array();
    $options['namespace'] = $this->config['namespace'];
    $options['use']       = ( $this->config['use']   == 0 ? SOAP_ENCODED : SOAP_LITERAL );
    $options['style']     = ( $this->config['style'] == 0 ? SOAP_RPC     : SOAP_DOCUMENT);
    
    $options = array_merge($options, $connect_args);
    
    if ( !extension_loaded('soap') ) {
      throw new Exception(t('PHP5 SOAP extension is not enabled. Please follow the documentation of how to enable PHP5 SOAP extension.'));
    }
    if ( ! $this->config['wsdl'] ) {
      if ( empty($options['namespace']) ) {
        throw new Exception(t('Target namespace uri is required when using non-WSDL mode of PHP5 SOAP.'));
      }

      $options['location'] = $this->config['endpoint'];
      $options['uri']      = $options['namespace'];      
    }

    $client = new SoapClient( ($this->config['wsdl'] ? $this->config['endpoint'] : NULL), $options );
    
    $result = array();
    $result['#error']  = FALSE;
    $result['#return'] = NULL;
    try {
      $result['#return'] = $client->__soapCall(
        $this->config['function'],
        array($args)
      );
    }
    catch (Exception $e) {
      $result['#error'] = t($e->getMessage());
    }

    if ( is_soap_fault($result['#return']) ) {
      $result['#error'] = t('Fault !code: !msg', array( '!code' => $result['#return']->faultcode, '!msg' => $result['#return']->faultstring ));
    }   

    if ( $result['#error'] !== FALSE ) {
      throw new Exception(t('SOAP fetch from @url failed with error: !msg', array('@url' => $this->config['endpoint'], '!msg' => $result['#error'])));
    }
    
    $key = $this->config['function'] . 'Result';
    return $result['#return']->$key->any;
  }
}

/**
 * Fetches data via SOAP.
 */
class FeedsSOAPFetcher extends FeedsFetcher {

  /**
   * Implementation of FeedsFetcher::fetch().
   */
  public function fetch(FeedsSource $source) {
    $source_config = $source->getConfigFor($this);
    return new FeedsSOAPBatch($source_config);
  }

  /**
   * Source form.
   */
  public function sourceForm($source_config) {
    $form = array();
    $form['endpoint'] = array(
      '#type'  => 'textfield',
      '#title' => t('SOAP server endpoint URL'),
      '#size'  => 60,
      '#maxlength'   => 256,
      '#description' => t('Enter the absolute endpoint URL of the SOAP Server service. If WSDL is being used (see SOAPFetcher settings), this will be the URL to retrieve the WSDL.'),
      '#default_value' => isset($source_config['endpoint']) ? $source_config['endpoint'] : '',
      '#required'    => TRUE
    );
    $form['wsdl'] = array(
      '#type'  => 'checkbox',
      '#title' => t('Use WSDL?'),
      '#default_value' => $source_config['wsdl'],
    );
    $form['namespace'] = array(
      '#type'  => 'textfield',
      '#title' => t('Target Namespace'),
      '#default_value' => $source_config['namespace'],
      '#size'  => 60,
      '#maxlength'   => 256,
      '#description' => t('If WSDL is <strong>not</strong> used, enter the target namespace URI here. Otherwise, leave it blank.'),
    );
    $form['use'] = array(
      '#type'  => 'radios',
      '#title' => 'Use',
      '#default_value' => $source_config['use'],
      '#options'       => array('encoded', 'literal'),
      '#description'   => t('Specify how the SOAP client serializes the message.'),
    );
    /* This always needs to be 'document', I guess?
    $form['style'] = array(
      '#type'  => 'radios',
      '#title' => 'Style',
      '#default_value' => 0,
      '#options'       => array('rpc', 'document'),
      '#description'   => t('Specify the style of SOAP call.'),
    );*/
    $form['connect_options'] = array(
      '#type' => 'textarea',
      '#title' => t('Connect options'),
      '#cols' => 60,
      '#rows' => 10,
      '#description' => t('Enter additional options for the SOAP Client connection, one option ' .
                          'per line, in the format <em>name=value</em>.'),
      '#default_value' => isset($source_config['connect_options']) ? $source_config['connect_options'] : '',
    );
    $form['function'] = array(
      '#type'  => 'textfield',
      '#title' => t('SOAP Function'),
      '#size'  => 60,
      '#maxlength'   => 256,
      '#description' => t('Enter the function name to be called.'),
      '#default_value' => isset($source_config['function']) ? $source_config['function'] : '',
      '#required'    => TRUE
    );
    $form['arguments'] = array(
      '#type'  => 'textarea',
      '#title' => t('Arguments'),
      '#cols'  => 60,
      '#rows'  => 10,
      '#description' => t('Enter the arguments of the function. One argument per line, '.
                          'for named arguments, the format of <em>name=value</em> may be used.'),
      '#default_value' => isset($source_config['arguments']) ? $source_config['arguments'] : '',
    );
    return $form;
  }

}