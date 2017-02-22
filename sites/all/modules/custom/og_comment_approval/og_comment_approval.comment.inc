<?php

/**
 * Overridden page callback for comment_edit().
 */
function og_comment_approval_comment_edit($cid) {
  global $user;

  $query = db_select('comment', 'c');
  $query->join('users', 'u', 'c.uid = u.uid');
  $query->condition('c.cid', $cid)
  ->fields('c')
  ->fields('u', array('uid', 'name', 'data'));
  $result = $query->execute()->fetchObject();
  
  $comment = drupal_unpack($result);
  
  $comment->name = $comment->uid ? $comment->registered_name : $comment->name;
  
  if (og_comment_approval_comment_delete_access($comment->cid) || comment_access('edit', $comment)) {
    return og_comment_approval_comment_form_box((array) $comment);
  }
  else {
    drupal_access_denied();
  }
}

