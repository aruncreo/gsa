<?php
/**
 * @file
 * gsa_home_page_view.pages_default.inc
 */

/**
 * Implements hook_default_page_manager_pages().
 */
function gsa_home_page_view_default_page_manager_pages() {
  $page = new stdClass();
  $page->disabled = FALSE; /* Edit this to true to make a default page disabled initially */
  $page->api_version = 1;
  $page->name = 'page_front';
  $page->task = 'page';
  $page->admin_title = 'page-front';
  $page->admin_description = '';
  $page->path = 'interact';
  $page->access = array();
  $page->menu = array();
  $page->arguments = array();
  $page->conf = array(
    'admin_paths' => FALSE,
  );
  $page->default_handlers = array();
  $handler = new stdClass();
  $handler->disabled = FALSE; /* Edit this to true to make a default handler disabled initially */
  $handler->api_version = 1;
  $handler->name = 'page_page_front_panel_context';
  $handler->task = 'page';
  $handler->subtask = 'page_front';
  $handler->handler = 'panel_context';
  $handler->weight = 0;
  $handler->conf = array(
    'title' => 'Panel',
    'no_blocks' => 0,
    'pipeline' => 'standard',
    'body_classes_to_remove' => '',
    'body_classes_to_add' => '',
    'css_id' => '',
    'css' => '',
    'contexts' => array(),
    'relationships' => array(),
  );
  $display = new panels_display();
  $display->layout = 'flexible';
  $display->layout_settings = array();
  $display->panel_settings = array(
    'style_settings' => array(
      'default' => NULL,
      'center' => NULL,
    ),
  );
  $display->cache = array();
  $display->title = '';
  $display->content = array();
  $display->panels = array();
    $pane = new stdClass();
    $pane->pid = 'new-1';
    $pane->panel = 'center';
    $pane->type = 'custom';
    $pane->subtype = 'custom';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'admin_title' => 'front-balloons',
      'title' => '',
      'body' => '<div class="front-balloons"><div class="balloon join"><h2><a href="/join">Join</a></h2><p>Join Interact today and gain access to the many groups that focus on topics from GSA Schedules to sustainability and beyond.</p><a href="/join">More</a></div><div class="balloon learn"><h2><a href="/gsa-training-home">Learn</a></h2><p>Learn about the many upcoming events and training opportunities available online and at a location near&nbsp;you.</p><a href="/gsa-training-home">More</a></div><div class="balloon connect"><h2><a href="/groups">Connect</a></h2><p>Connect to share information with thousands of community members from government staff to industry partners.</p><a href="/groups">More</a></div><div class="balloon discuss"><h2><a href="/discuss">Discuss</a></h2><p>Discuss your views on trending topics and discover the collaborative experience of&nbsp;Interact.</p><a href="/discuss">More</a></div></div>',
      'format' => 'full_html',
      'substitute' => TRUE,
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 0;
    $pane->locks = array();
    $display->content['new-1'] = $pane;
    $display->panels['center'][0] = 'new-1';
    $pane = new stdClass();
    $pane->pid = 'new-2';
    $pane->panel = 'center';
    $pane->type = 'panels_mini';
    $pane->subtype = 'featured_getting_started_panel';
    $pane->shown = TRUE;
    $pane->access = array();
    $pane->configuration = array(
      'override_title' => 0,
      'override_title_text' => '',
    );
    $pane->cache = array();
    $pane->style = array(
      'settings' => NULL,
    );
    $pane->css = array();
    $pane->extras = array();
    $pane->position = 1;
    $pane->locks = array();
    $display->content['new-2'] = $pane;
    $display->panels['center'][1] = 'new-2';
  $display->hide_title = PANELS_TITLE_FIXED;
  $display->title_pane = 'new-1';
  $handler->conf['display'] = $display;
  $page->default_handlers[$handler->name] = $handler;
  $pages['page_front'] = $page;

  return $pages;

}
