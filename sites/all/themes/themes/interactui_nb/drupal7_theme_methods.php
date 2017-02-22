<?php

/* Drupal 7 methods definitons */
$art_style = '';
$art_head = '';
function interactui_nb_process_html(&$variables) {
    global $art_style, $art_head;
	$view = get_artx_drupal_view();
	$message = $view->get_incorrect_version_message();
	if (!empty($message)) {
		drupal_set_message($message, 'error');
	}
	$variables['styles'] .= $art_style;
	$variables['scripts'] .= $art_head;
}

function interactui_nb_breadcrumb($variables) {
  $breadcrumb = $variables['breadcrumb'];

  if (!empty($breadcrumb)) {
    // Provide a navigational heading to give context for breadcrumb links to
    // screen-reader users. Make the heading invisible with .element-invisible.
    $output = '<h2 class="element-invisible gs-postheader">' . t('You are here') . '</h2>';
	
	// Supress breadcrumb functionality 
    $output .= '<div class="breadcrumb gs-postcontent">' . /*implode(' | ', $breadcrumb) .*/ '</div>';
    return $output;
  }
}

/**
 * Returns HTML for a button form element.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: An associative array containing the properties of the element.
 *     Properties used: #attributes, #button_type, #name, #value.
 *
 * @ingroup themeable
 */
function interactui_nb_button($variables) {
  $element = $variables['element'];
  $element['#attributes']['type'] = 'submit';
  element_set_attributes($element, array('id', 'name', 'value'));

  $element['#attributes']['class'][] = 'form-' . $element['#button_type'] . ' gs-button';
  if (!empty($element['#attributes']['disabled'])) {
    $element['#attributes']['class'][] = 'form-button-disabled';
  }

  return '<input' . drupal_attributes($element['#attributes']) . ' />';
}

/**
 * Override or insert variables into the page template.
 */
function interactui_nb_preprocess_page(&$vars) {
  global $art_style, $art_head;
  $vars['tabs'] = menu_primary_local_tasks();
  $vars['tabs2'] = menu_secondary_local_tasks();

  if (isset($vars['node'])) {
    if (isset($vars['art_style_'.$vars['node']->nid])) {
      $art_style = $vars['art_style_'.$vars['node']->nid];
    }
    if (isset($vars['art_head_'.$vars['node']->nid])) {
      $art_head = $vars['art_head_'.$vars['node']->nid];
    }
  }
}

/**
 * Returns HTML for a single local task link.
 *
 * @param $variables
 *   An associative array containing:
 *   - element: A render element containing:
 *     - #link: A menu link array with 'title', 'href', and 'localized_options'
 *       keys.
 *     - #active: A boolean indicating whether the local task is active.
 *
 * @ingroup themeable
 */
function interactui_nb_menu_local_task($variables) {
  $link = $variables['element']['#link'];
  $link_text = $link['title'];
  
  $active_class = '';
  if (!empty($variables['element']['#active'])) {
    // Add text to indicate active tab for non-visual users.
    $active = '<span class="element-invisible">' . t('(active tab)') . '</span>';
    $active_class = ' active';

    // If the link does not contain HTML already, check_plain() it now.
    // After we set 'html'=TRUE the link will not be sanitized by l().
    if (empty($link['localized_options']['html'])) {
      $link['title'] = check_plain($link['title']);
    }
    $link['localized_options']['html'] = TRUE;
    $link_text = t('!local-task-title!active', array('!local-task-title' => $link['title'], '!active' => $active));
  }

   if($variables['element']['#link']['tab_parent'] == 'gsa-training' ){
  	if($variables['element']['#active'] == 1){
	  return "<li>".l($link_text, $link['href'], $link['localized_options'])."</li>\n";	
	}
  }else{
  	return "<li>".l($link_text, $link['href'], $link['localized_options'])."</li>\n";
  }
}

/**
 * Returns HTML for a feed icon.
 *
 * @param $variables
 *   An associative array containing:
 *   - url: The url of the feed.
 *   - title: A descriptive title of the feed.
 */
function interactui_nb_feed_icon($variables) {
  $text = t('Subscribe to @feed-title', array('@feed-title' => $variables['title']));
  return l(NULL, $variables['url'], array('html' => TRUE, 'attributes' => array('class' => array('feed-icon', 'gs-rss-tag-icon'), 'title' => $text)));
}

/**
 * Returns HTML for a node preview for display during node creation and editing.
 *
 * @param $variables
 *   An associative array containing:
 *   - node: The node object which is being previewed.
 *
 * @ingroup themeable
 */
function interactui_nb_node_preview($variables) {
  $node = $variables['node'];

  $output = '<div class="preview">';

  $preview_trimmed_version = FALSE;

  $elements = node_view(clone $node, 'teaser');
  $trimmed = drupal_render($elements);
  $elements = node_view($node, 'full');
  $full = drupal_render($elements);

  // Do we need to preview trimmed version of post as well as full version?
  if ($trimmed != $full) {
    drupal_set_message(t('The trimmed version of your post shows what your post looks like when promoted to the main page or when exported for syndication.<span class="no-js"> You can insert the delimiter "&lt;!--break--&gt;" (without the quotes) to fine-tune where your post gets split.</span>'));
	$preview_trimmed_version = t('Preview trimmed version');
	$output .= <<< EOT
    <div class="gs-box gs-post">
	<div class="gs-box-body gs-post-body">
    <article class="gs-post-inner gs-article">
    <div class="gs-postcontent">
      <h3>
	  $preview_trimmed_version
	  </h3>
	</div>
    <div class="cleared"></div>
    </article>
	<div class="cleared"></div>
    </div>
    </div>
EOT;
	$output .= $trimmed;
    
	$preview_full_version = t('Preview full version');
	$output .= <<< EOT
    <div class="gs-box gs-post">
	<div class="gs-box-body gs-post-body">
    <article class="gs-post-inner gs-article">
    <div class="gs-postcontent">
      <h3>
	  $preview_full_version
	  </h3>
    </div>
    <div class="cleared"></div>
    </article>
	<div class="cleared"></div>
    </div>
    </div>
EOT;

    $output .= $full;
  }
  else {
    $output .= $full;
  }
  $output .= "</div>\n";

  return $output;
}

/**
 * Return a Artisteer themed set of links.
 *
 * @param $content
 *   An object with node content.
 * @return
 *   A string containing an unordered list of links.
 */
function art_links_woker_D7($content) {
  $result = '';
  if (!isset($content['links'])) return $result;
  foreach (array_keys($content['links']) as $name) {
	$$name = & $content['links'][$name];
	if (isset($content['links'][$name]['#links'])) {
	  $links = $content['links'][$name]['#links'];
	  if (is_array($links)) {
		$output = get_links_html_output_D7($links);
		if (!empty($output)) {
			$result .= (empty($result)) ? $output : '&nbsp;|&nbsp;' . $output;
		}
	  }
    }
  }

  
  return $result;  
}

function get_terms_D7($content) {
	$result = NULL;
	foreach (array_keys($content) as $name)	{
		$$name = & $content[$name];
		$field_type = NULL;
		if (is_array($content[$name])) {
			if (isset($content[$name]['#field_type']))
				$field_type = $content[$name]['#field_type'];
		} else if (is_object($content[$name])) {
			if (isset($content[$name]->field_type))
				$field_type = $content[$name]->field_type;
		}
	    if ($field_type == NULL || $field_type != "taxonomy_term_reference") continue;
	    $result = $content[$name];
	}
	return $result;
}

function get_links_html_output_D7($links) {
	$output = '';
	$num_links = count($links);
    $index = 0;

	foreach ($links as $key => $link) {
	  $class = array($key);

      // Add first, last and active classes to the list of links to help out themers.
      if ($index == 0) {
        $class[] = 'first';
      }
      if ($index == $num_links) {
        $class[] = 'last';
      }
      if (isset($link['href']) && ($link['href'] == $_GET['q'] || ($link['href'] == '<front>' && drupal_is_front_page()))
          && (empty($link['language']) || $link['language']->language == $language_url->language)) {
        $class[] = 'active';
      }
      
	  $link_output = '';

      if (isset($link['href'])) {
        // Pass in $link as $options, they share the same keys.
        $link_output = l($link['title'], $link['href'], $link);
      }
      elseif (!empty($link['title'])) {
        // Some links are actually not links, but we wrap these in <span> for adding title and class attributes.
        if (empty($link['html'])) {
          $link['title'] = check_plain($link['title']);
        }
        $span_attributes = '';
        if (isset($link['attributes'])) {
          $span_attributes = drupal_attributes($link['attributes']);
        }
        $link_output = '<span' . $span_attributes . '>' . $link['title'] . '</span>';
      }
		
		
        

	}
	return $output;
}

/*
 * Replace old JQuery version with new one from Artisteer generated theme. 
*/
function art_compatible_scripts($scripts) {
  $result = preg_replace('~(<script[^>]+misc/jquery.js)([^<]*)(</script>)~', '<script type="text/javascript" src="'.get_full_path_to_theme().'/jquery.js$2$3', $scripts);
  return $result;
}

/* Theming Drupal search form 
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 * @param $form_state
 *   A keyed array containing the current state of the form. The arguments
 *   that drupal_get_form() was originally called with are available in the
 *   array $form_state['build_info']['args'].
 * @param $form_id
 *   String representing the name of the form itself. Typically this is the
 *   name of the function that generated the form.
*/
function interactui_nb_form_alter(&$form, &$form_state, $form_id) {
  if ($form_id == 'search_block_form' || $form_id == 'search_form') {
    $form['#attributes'] = array('class' => array('gs-search')); // Add Artisteer class
    $form['actions']['submit']['#attributes'] = array('class' => array('gs-search-button')); // Add Artisteer class
  }
}