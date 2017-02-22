<?php

/**
 * Page callback to show all nodes inside a given group with pending
 * revisions
 * 
 * @param $group
 *   The group node
 */
function og_revision_mod_moderated_revisions_page($entity_type, $entity_id) {
  // Set the breadcrumb
  og_set_breadcrumb($entity_type, $entity_id, array(l(t('Group'), "{$entity_type}/{$entity_id}/group")));
  
  // Load the group
  $group = og_get_group($entity_type, $entity_id);
  
  // Fetch all nodes inside this group, along with their revisions
  $nodes = og_revision_mod_get_moderated_revisions($group);
  
  // See if we have any moderated nodes to display
  if (empty($nodes)) {
    return t('There are currently no nodes containing moderated revisions.');
  }
  
  // Construct a table
  $headers = array(t('Node'), t('Node author'), t('Total revisions'), t('Link'));
  
  $rows = array();
  foreach ($nodes as $node) {
    $rows[] = array(
      l($node->title, 'node/' . $node->nid),
      user_access('access user profiles') ? l($node->name, 'user/' . $node->uid) : $node->name,
      count($node->revisions),
      l(t('View revisions'), 'node/' . $node->nid . '/revisions'),
    );
  }
  
  return theme('table', array('header' => $headers, 'rows' => $rows));
}

/**
 * Override of node_revision_overview()
 */
function og_revision_mod_node_revision_overview($node) {
  drupal_set_title(t('Revisions for %title', array('%title' => $node->title)), PASS_THROUGH);
  
  $group = og_features_get_group_context();

  $header = array(t('Revision'), array(
      'data' => t('Operations'),
      'colspan' => 2,
    ));

  $revisions = node_revision_list($node);

  $rows = array();
  $revert_permission = FALSE;
  if ((og_user_access($group->gid, 'revert revisions') || og_user_access($group->gid, 'administer nodes')) && node_access('update', $node)) {
    $revert_permission = TRUE;
  }
  $delete_permission = FALSE;
  if ((og_user_access($group->gid, 'delete revisions') || og_user_access($group->gid, 'administer nodes')) && node_access('delete', $node)) {
    $delete_permission = TRUE;
  }
  foreach ($revisions as $revision) {
    $row = array();
    $operations = array();

    if ($revision->current_vid > 0) {
      $row[] = array(
        'data' => t('!date by !username', array('!date' => l(format_date($revision->timestamp, 'short'), "node/$node->nid"), '!username' => theme('username', array('account' => $revision))))
                               . (($revision->log != '') ? '<p class="revision-log">' . filter_xss($revision->log) . '</p>' : ''), 
        'class' => array('revision-current'),
      );
      $operations[] = array(
        'data' => drupal_placeholder(t('current revision')),
        'class' => array('revision-current'),
        'colspan' => 2,
      );
    }
    else {
      $row[] = t('!date by !username', array('!date' => l(format_date($revision->timestamp, 'short'), "node/$node->nid/revisions/$revision->vid/view"), '!username' => theme('username', array('account' => $revision))))
               . (($revision->log != '') ? '<p class="revision-log">' . filter_xss($revision->log) . '</p>' : '');
      if ($revert_permission) {
        $operations[] = l(t('revert'), "node/$node->nid/revisions/$revision->vid/revert");
      }
      if ($delete_permission) {
        $operations[] = l(t('delete'), "node/$node->nid/revisions/$revision->vid/delete");
      }
    }
    $rows[] = array_merge($row, $operations);
  }

  $build['node_revisions_table'] = array(
    '#theme' => 'table', 
    '#rows' => $rows, 
    '#header' => $header,
  );

  return $build;
}