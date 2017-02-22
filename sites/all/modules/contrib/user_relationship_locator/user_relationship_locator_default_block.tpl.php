<?php
/**
 *  Theme wrapper html for relationship list
 */
?>
<ul class="user-relationship-locator-list">
<?php
  if($matches = user_relationship_locator_matches($user->uid)) {
    foreach($matches as $match) {
      print theme('user_relationship_locator_default_block_item',
        array(
          'requester' => $requester,
          'requestee' => $match,
          'relationship' => $relationship,
        )
      );
    }
  }

  //See if we have the Facebook data source module enabled and show a button if data isn't available.
  if(module_exists('user_relationship_locator_facebook')) {
    if(user_relationship_locator_facebook_result_cache() == FALSE) {
      print fboauth_action_display('user_relationship_locator_users');
    }
  }
?>
</ul>
