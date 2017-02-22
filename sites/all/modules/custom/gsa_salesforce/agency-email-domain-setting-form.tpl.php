<?php



$agencies = gsa_salesforce_get_picklist('Agency__c', 'Account');
	
	//List of allowed domains
	$allowed_domains = array('gov','mil','us','com','org','net','edu','biz');
	
	$output = '<table style="border:none;">';
	$output .= '<tr>';
	$output .= '<td style="border-right:none;">';
	$output .= 'Define the top-level domains permitted for each options in the user profile Agency field. If no domains are <br/>selected for an agency, any email address will be permitted when users select that agency.<br/><br/>Return to this page to update the settings whenever the list of agencies is updated in Salesforce.';
	$output .= '</td>';
	$output .= '</tr>';
	$output .= '</table>';
	$output .= '<table>';
	
	$output .= '<thead>';
	$output .= '<th>';
	$output .= 'Agency';
	$output . '</th>';
	$output .= '<th colspan = '.count($allowed_domains).'>';
	$output .= 'Allowed Domains';
	$output . '</th>';
	$output .= '</thead>';
	
	foreach($agencies as $agency_key => $agency_value){
		$agency_var_key = preg_replace('/[^a-zA-Z0-9]/', '_', $agency_key);
		
		$output .= '<tr>';
		$output .= '<td>';
		$output .= drupal_render($form[$agency_var_key]);
		$output .= '</td>';

		foreach($allowed_domains as $domain){
			
			$output .= '<td>';
			$output .= drupal_render($form['gsa_salesforce_agency_'.$agency_var_key.'_'.$domain]);
  			$output .= '</td>';
  			
		}
		
		$output .= '</tr>';
	}
	
	$output .= '</table>';
	$output .= drupal_render_children($form); 


print $output;