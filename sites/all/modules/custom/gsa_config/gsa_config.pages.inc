<?php

/**
 * Page callback override for the user contact page
 */
function gsa_config_contact_user_page($account) {
  global $user;
  module_load_include('inc', 'contact', 'contact.pages');
  
  // See if this is considere a site admin, or any group admin
  $admin = FALSE;
  if (user_access('administer site configuration')) {
    $admin = TRUE;
  }
  else if (user_access('administer gsa')) {
    $admin = TRUE;
  }
  else {
    foreach ($user->og_groups as $gid => $group) {
      if ($group['is_active'] && $group['is_admin']) {
        $admin = TRUE;
        break;
      }
    }
  }

  if (!valid_email_address($user->mail)) {
    $output = t('You need to provide a valid e-mail address to contact other users. Please update your <a href="@url">user information</a> and try again.', array('@url' => url("user/$user->uid/edit")));
  }
  else if (!$admin && !flood_is_allowed('contact', variable_get('contact_hourly_threshold', 3))) {
    $output = t('You cannot contact more than %number users per hour. Please try again later.', array('%number' => variable_get('contact_hourly_threshold', 3)));
  }
  else {
    drupal_set_title(check_plain($account->name));
    $output = drupal_get_form('contact_mail_user', $account);
  }

  return $output;
}
