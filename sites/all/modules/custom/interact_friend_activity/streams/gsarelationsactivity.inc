<?php

/**
 * @file
 * GSA Relations activity object.
 */

/**
 * Class GSARelationsActivity
 * Alter the default RelationsActivity stream to exclude the current user.
 */
class GSARelationsActivity extends RelationsActivity {

  /**
   * Fake constructor to hook this method instead of the constructor.
   */
  public function construct() {

    // Add the relations to the viewed user object.
    $this->viewer->relations = heartbeat_related_uids($this->viewer->uid);
    
    // This stream needs the viewed relations as well. Load them if different.
    if ($this->viewed->uid != $this->viewer->uid) {
      $this->viewed->relations = heartbeat_related_uids($this->viewed->uid);
    }
    else {
      $this->viewed->relations = $this->viewer->relations;
    }
    
    $this->config->skip_active_user = TRUE;

  }
  
}