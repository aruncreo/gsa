<?php
/**
 * @file
 *  API calls for use across all networks 
 */

/**
 * @return
 *  An associative array of all available network names
 */
function user_relationship_locator_networks() {
  $result = db_select('user_relationship_locator','url')
    ->fields('url', array('netname', 'users'))
    ->execute();

  $networks = array();
  foreach ($result as $network) {
    $networks[$network->netname] = $network->users;
  }

  if (empty($networks)) {
    if (user_access('Administer relationship location')) {
      drupal_set_message('Please enable a network module to provide user data to the relationship locator.');
    }
  }
  return $networks;
}

/**
 * Returns a list of networks a given user is part of 
 * @param $uid
 *  User ID is most likely the current user.
 * @return $memberships
  $memberships = array();
  if($networks = user_relationship_locator_networks()) {
    foreach($networks as $network) {
 *  an array of network names
 */
function user_relationship_locator_network_memberships($uid) {
  if($networks = user_relationship_locator_networks()) {
    //TODO: fix this so it only returns networks we are part of
    $memberships = $networks;
    return $memberships;
    /*
    foreach($networks as $key => $value) {
      $users = unserialize($value);
      if(in_array($uid,$users)) {
        $memberships[] = $key;
      }
      return $memberships;
    }
    */
  }
}

/**
 * Given a network name return the module name
 */
function user_relationship_locator_network_module($netname) {
  //TODO: this feels um... fragile
  $module_name = 'user_relationship_locator_' . $netname;
  return $module_name;
}

/**
 * Returns a list of user ids who are possible matches
 */
function user_relationship_locator_matches($uid) {
  $current_user = user_load($uid);
  $relationshipid = variable_get('user_relationship_locator_relationship','0');
  //TODO: permission check for have and maintain
  $max = variable_get('user_relationship_locator_max','');
  $min = variable_get('user_relationship_locator_min','');
  $matches = array();
  
  //don't waste energy querying networks our user doesn't belong to
  if($memberships = user_relationship_locator_network_memberships($uid)) {
    foreach($memberships as $network => $users) {
      $modulename = user_relationship_locator_network_module($network); 
      $network_users = module_invoke($modulename, 'urlocator_user_query', $uid);
      if(!empty($network_users)) {
        foreach($network_users as $key => $value) {
          //Check for users already returned
          if(!array_key_exists($key,$matches)) {
            $matches[$key] = $value;
          }
          else {
            $matches[$key] = $matches[$key] + 0.1;
          }
        }
      }
    }
  }
  
  //Remove any returned uids that the user already has a relationship with
  $current_rels = array();
  $current_query = db_query("SELECT DISTINCT requestee_id FROM {user_relationships} WHERE rtid = :rtid AND requester_id = :requester", array(':rtid' => $relationshipid, ':requester' => $uid));
  foreach ($current_query as $user) {
    $current_rels[$user->requestee_id] = $user->requestee_id;
  }
  foreach($current_rels as $current) {
    unset($matches[$current]);
  }

  //Sort by final score
  arsort($matches);

  //user_load doesn't like our score values
  foreach($matches as $key => $value) {
    $matches[$key] = $key;
  }

  //Fill out array with other users if minimum number not already there
  if(count($matches) < $min) {
    $num_needed = $min - count($matches);
    $filler = user_relationship_locator_filler($num_needed, $uid);
    if(count($matches) >= 1) {
      $matches = array_merge($matches,$filler);
    } else {
      $matches = $filler;
    }
  }

  $matches = user_load_multiple($matches);
  return $matches;
}

/**
 * Ensure our min is met with random users if enough matches aren't found
 * * $number = required number of filler spots
 * $uid = user to exclude
 */

function user_relationship_locator_filler($number, $uid) {

  //TODO: instead of random this could be pseudo random where it starts only filling random people from in-network then branches out
  $result = db_query('SELECT uid from {users} WHERE uid > 1 AND uid != :uid', array(':uid' => $uid));
  $allusers = array();
  foreach($result as $value) {
    $allusers[$value->uid] = $value->uid;
  }
  if($number <= count($allusers)) {
    $filler = array_rand($allusers,$number);
  } else {
    $filler = $allusers;
  }
  return $filler;
}

/**
 * Create a new network 
 */
function user_relationship_locator_network_create($netname,$users) {
  //TODO: do check here to see if $netname already exists and throw error if does
  //TODO: have the network name automatically be the submodule name? this is necessary
  $users = serialize($users);
  $fields = array('netname' => $netname, 'status' => 1, 'users' => $users); 
  db_insert('user_relationship_locator')->fields($fields)->execute();
}

/**
 * Load an entire network object
 * @param $netname
 *  Network name.
 * @return $network
 *  Network object. 
 */
function user_relationship_locator_network_load($netname) {
}

/**
 * Returns a list of users from a given network 
 * @param $netname
 *  Network name.
 * @return $members
 *  an array of uids 
 */
function user_relationship_locator_network_users($netname) {
}

/**
 * Delete a network 
 */
function user_relationship_locator_network_delete($netname) {
  db_delete('user_relationship_locator')
    ->condition('netname', $netname)
    ->execute();
}

/**
 * Update an existing network's information. 
 * @param $users
 *  Associative array key = uid, value = unique network id for user
 * @return $success 
 *  boolean if update succeeeds 
 */
function hook_urlocator_network_update($netname, $users, $status = 1) {
}

/**
 * UID comparison list from a network.
 * @return $users
 *  an associative array of possible user id matches and score to act upon
 */
function hook_urlocator_user_query($uid) {
}
