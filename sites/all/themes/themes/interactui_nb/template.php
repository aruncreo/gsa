<?php
// $Id

require_once("common_methods.php");


global $language;
if (isset($language)) {
	$language->direction = LANGUAGE_LTR;
}

switch (get_drupal_major_version()) {
	case 5:
	  require_once("drupal5_theme_methods.php");
	  break;
	case 6:
	  require_once("drupal6_theme_methods.php");
	  break;
	case 7:
	  require_once("drupal7_theme_methods.php");
	  break;
    default:
		  break;
}

/* Common methods */

function get_drupal_major_version() {
	$tok = strtok(VERSION, '.');
	//return first part of version number
	return (int)$tok[0];
}

function get_page_language($language) {
  if (get_drupal_major_version() >= 6) return $language->language;
  return $language;
}

function get_page_direction($language) {
  if (isset($language) && isset($language->dir)) {
	  return 'dir="'.$language->dir.'"';
  }
  return 'dir="'.ltr.'"';
}

function get_full_path_to_theme() {
  return base_path().path_to_theme();
}

function get_artx_drupal_view() {
	if (get_drupal_major_version() == 7)
		return new artx_view_drupal7();
	return new artx_view_drupal56();
}

function get_artisteer_export_version() {
	return 7;
}

if (!function_exists('render'))	{
	function render($var) {
		return $var;
	}
}

// Get transport protocol for script URLs
global $base_url;
preg_match('`https?://`', $base_url, $matches);
$protocol = $matches[0];

class artx_view_drupal56 {

	function print_head($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<!DOCTYPE html>
<html lang="<?php echo get_page_language($language); ?>" <?php echo get_page_direction($language); ?> >
<head>
  <?php echo $head; ?>
  <title><?php if (isset($head_title )) { echo $head_title; } ?></title>
  <!--[if lt IE 9]><script src="<?php echo $protocol; ?>html5shiv.googlecode.com/svn/trunk/html5.js"></script><![endif]-->
  <?php echo $styles ?>
  <?php echo art_compatible_scripts($scripts) ?>
  <!--[if lte IE 7]><link rel="stylesheet" href="<?php echo $base_path . $directory; ?>/style.ie7.css" media="screen" /><![endif]-->
  <link rel="stylesheet" type="text/css" href="<?php echo $protocol; ?>fonts.googleapis.com/css?family=Lora">
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>

<body <?php if (!empty($body_classes)) { echo 'class="'.$body_classes.'"'; } ?>>
<?php
	}


	function print_closure($vars) {
	echo $vars['closure'];
?>
</body>
</html>
<?php
	}

	function print_maintenance_head($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<!DOCTYPE html >
<html lang="<?php echo get_page_language($language); ?>" <?php echo get_page_direction($language); ?> >
<head>
  <?php echo $head; ?>
  <title><?php if (isset($head_title )) { echo $head_title; } ?></title>
  <?php echo $styles ?>
  <?php echo $scripts ?>
  <!--[if lte IE 7]><link rel="stylesheet" href="<?php echo $base_path . $directory; ?>/style.ie7.css" type="text/css" media="screen" /><![endif]-->
  <script type="text/javascript"><?php /* Needed to avoid Flash of Unstyle Content in IE */ ?> </script>
</head>

<body <?php if (!empty($body_classes)) { echo 'class="'.$body_classes.'"'; } ?>>
<?php
	}

	function print_maintenance_closure($vars) {
		echo $vars['closure'];
?>
</body>
</html>
<?php
	}

	function print_comment($vars) {
		foreach (array_keys($vars) as $name)
		$$name = & $vars[$name];
?>
<div class="comment<?php print ($comment->new) ? ' comment-new' : ''; print ' '. $status; print ' '. $zebra; ?>">

  <div class="clear-block">
  <?php if ($submitted): ?>
    <span class="submitted"><?php print $submitted; ?></span>
  <?php endif; ?>

  <?php if ($comment->new) : ?>
    <span class="new"><?php print drupal_ucfirst($new) ?></span>
  <?php endif; ?>

  <?php print $picture ?>

    <h3><?php print $title ?></h3>

    <div class="content">
      <?php print $content ?>
      <?php if ($signature): ?>
      <div class="clear-block">
        <div>-</div>
        <?php print $signature ?>
      </div>
      <?php endif; ?>
    </div>
  </div>

  <?php if ($links): ?>
    <div class="links"><?php print $links ?></div>
  <?php endif; ?>
</div>
<?php
	}

	function print_comment_wrapper($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<div id="comments">
  <?php print $content; ?>
</div>
	<?php
	}

	function print_comment_node($vars) {
		return;
	}

	function get_incorrect_version_message() {
		if (get_artisteer_export_version() > 6) {
			return t('This version is not compatible with Drupal 5.x or 6.x and should be replaced.');
		}
		return '';
	}
}


class artx_view_drupal7 {

	function print_head($vars) {
		print render($vars['page']['header']);
	}

	function print_closure($vars) {
		return;
	}

	function print_maintenance_head($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML+RDFa 1.0//EN" "http://www.w3.org/MarkUp/DTD/xhtml-rdfa-1.dtd">
<html xmlns="http://www.w3.org/1999/xhtml" xml:lang="<?php print $language->language; ?>" version="XHTML+RDFa 1.0" dir="<?php print $language->dir; ?>">

<head>
  <?php print $head; ?>
  <title><?php print $head_title; ?></title>
  <?php print $styles; ?>
  <?php print $scripts; ?>
  <!--[if lte IE 7]><link rel="stylesheet" href="<?php echo base_path() . $directory; ?>/style.ie7.css" type="text/css" media="screen" /><![endif]-->
</head>
<body class="<?php print $classes; ?>" <?php print $attributes;?>>
<?php
	}

	function print_maintenance_closure($vars) {
?>
</body>
</html>
<?php
	}

	function print_comment($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<div class="<?php print $classes; ?> clearfix"<?php print $attributes; ?>>
  <?php print $picture ?>

  <div class="submitted">
    <?php print $permalink; ?>
    <?php
      print t('Submitted by !username on !datetime.',
        array('!username' => $author, '!datetime' => $created));
    ?>
  </div>

  <?php if ($new): ?>
    <span class="new"><?php print $new ?></span>
  <?php endif; ?>

  <?php print render($title_prefix); ?>
  <h3><?php print $title ?></h3>
  <?php print render($title_suffix); ?>

  <div class="content"<?php print $content_attributes; ?>>
    <?php
      // We hide the comments and links now so that we can render them later.
      hide($content['links']);
      print render($content);
    ?>
    <?php if ($signature): ?>
    <div class="user-signature clearfix">
      <?php print $signature ?>
    </div>
    <?php endif; ?>
  </div>

  <?php print render($content['links']) ?>
</div>
<?php
	}

	function print_comment_wrapper($vars)	{
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
?>
<div id="comments" class="<?php print $classes; ?>"<?php print $attributes; ?>>
  <?php if ($content['comments'] && $node->type != 'forum'): ?>
    <?php print render($title_prefix); ?>
    <h2 class="gs-postheader"><?php print t('Comments'); ?></h2>
    <?php print render($title_suffix); ?>
  <?php endif; ?>

  <?php print render($content['comments']); ?>

  <?php if ($content['comment_form']): ?>
    <h2 class="gs-postheader"><?php print t('Add new comment'); ?></h2>
    <?php print render($content['comment_form']); ?>
  <?php endif; ?>
</div>
	<?php
	}

	function print_comment_node($vars) {
		foreach (array_keys($vars) as $name)
			$$name = & $vars[$name];
		$comments = (isset($content['comments']) ? render($content['comments']) : '');
		if (!empty($comments) && $page):
?>
<div class="gs-box gs-post">
	<div class="gs-box-body gs-post-body">
    <article class="gs-post-inner gs-article">
    <div class="gs-postcontent">
<?php
		echo $comments;
?>
	</div>
    <div class="cleared"></div>
    </article>
	<div class="cleared"></div>
    </div>
    </div>
<?php endif;
	}

	function get_incorrect_version_message() {
		if (get_artisteer_export_version() < get_drupal_major_version()) {
			return t('This version is not compatible with Drupal 7.x. and should be replaced.');
		}
		return '';
	}
}

/**
 * Implements of template_preprocess_html().
 */
function interactui_nb_preprocess_html(&$vars) {
  // Correct body classes for sidebar presence.
  $has_sidebar = FALSE;
  if (isset($vars['page']['sidebar_left'])) {
    $vars['classes_array'][] = 'sidebar-left';
    $has_sidebar = TRUE;
  }
  if (isset($vars['page']['sidebar_right'])) {
    $vars['classes_array'][] = 'sidebar-left';
    $has_sidebar = TRUE;
  }
  if ($has_sidebar) {
    $vars['classes_array'][] = 'has-sidebar';
  }
}




/**
 * Implements template_preprocess_node().
 */
function interactui_nb_preprocess_node(&$vars) {

$node = $vars['node'];

   if (!empty($vars['elements']['#gsa_hide_submitted']) && $vars['elements']['#gsa_hide_submitted'] == TRUE) {
     unset($vars['submitted']);
   }
    global $user;
   if($vars['node']->type == 'blog' && (array_key_exists(6, $user->roles) || array_key_exists(10, $user->roles))){
   	 $vars['featured_content_flag'] = isset($vars['content']['links']['flag']['#links']['flag-featured_content_flag']['title'])?$vars['content']['links']['flag']['#links']['flag-featured_content_flag']['title']:'';
   }

    //Enabling questionable flag link for CTAT group
 	if($node->group_audience['und'][0]['gid'] == 21 && og_is_member(21)){
	 	$vars['questionable_flag_link'] = isset($vars['content']['links']['flag']['#links']['flag-cpat_questionable']['title'])?$vars['content']['links']['flag']['#links']['flag-cpat_questionable']['title']:'';
	 	unset($vars['content']['links']);
	}else{
		unset($vars['content']['links']);
	}

	$vars['content']['count'] = statistics_get($node->nid);


}
function interactui_nb_link(&$variables) {
	if($variables['text']=='Read more'){
		$variables['text']='Read More';
		return '<a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a>';
	}else{
		return '<a href="' . check_plain(url($variables['path'], $variables['options'])) . '"' . drupal_attributes($variables['options']['attributes']) . '>' . ($variables['options']['html'] ? $variables['text'] : check_plain($variables['text'])) . '</a>';
	}
}


/**
* Implements hook_preprocess_views_view
*/
// Checks the number of users in each group and displays appropriate value under 'Members'
function interactui_nb_preprocess_views_view(&$vars) {
 	$groupid=$vars['view']->query->where[0]['conditions'][0]['value'][':og_membership_group'];
 	$view = $vars['view'];

	if($view->name=='gsa_og_content_tracker'){

		$curUrl=$_GET['q'];
		$paramArray= explode('/',$curUrl);
		if($paramArray[2]=='group-content'){

		$view->build_info['title']=ucfirst($view->args[1]).' Entries...';

		}

	}
	if($view->name=='gsa_my_groups'){

		global $user;
		if($view->current_display!='block_1'){
			$view->build_info['title']=$view->build_info['title'].' for <i>'.$user->name.'</i>';
		}
	}

	if($view->name=='gsa_content'){

		if($view->args[1]!='all'){
			$contenttype=str_replace("_"," ",$view->args[1]);
			$view->build_info['title']='Recent '.$contenttype.'\'s';
		}
	}

 	if($view->name=='gsa_og_members'){



if(!isset($groupid)){


	$groupid=$view->query->where[0]['conditions'][0]['value'][':og_membership_group1'];

}

$cache = cache_get('count_member_'.$groupid.'');
$count = ($cache==FALSE)?'':$cache->data;

if ($count == '') {
	// Getting the member count for a particular group
 	$count = gsa_group_page_get_member_count($groupid);
	cache_set('count_member_' . $groupid . '', $count, 'cache');
} else {
	$cache = cache_get('count_member_' . $groupid . '');
	$count = $cache->data;

}


  if($view->current_display!='page_1'){
  		$vars['view']->build_info['title']=$vars['view']->build_info['title'].'<br><div class="member-count">'.number_format($count).' members</div>';
		}

 	}
	$cururl=$_GET['q'];
	$paramArray=explode('/',$cururl);


	if($view->name=='gsa_discuss_page_1' || $view->name=='_gsa_archived_og_content_' || $view->name=='gsa_content_discover' || ($paramArray[2]=='group-content' && $view->name=='gsa_og_content_tracker') ){

		$count_query = $view->build_info['count_query'];
		$count_query->addMetaData('view', $view);
		$count_query->preExecute();
		$count_query = $count_query->countQuery();
		$total = $count_query->execute()->fetchField();


		$per_page = 10;
		// Initialise the pager
		$current_page = pager_default_initialize($total, $per_page);

		$vars['pager']=theme('pager', array('quantity',$total));

	}
}

/**
* Implements template_preprocess_block()
*/
function interactui_nb_preprocess_block(&$variables) {


$block=$variables['block'];


  if ($block->bid === 'views-gsa_og_members-block_2') {
  $block->subject='Members';
  }
  if ($block->bid == 'poll-recent') {


	$paramArray=explode('/',$_GET['q']);

	$selectog = db_select('og', 'og');
	$selectog->fields('og',array('gid'))
		->condition('og.etid', $paramArray[1]);
	$recordog = $selectog->execute()->fetchObject();

	 if (user_access('access content')) {
		// Retrieve the latest poll.
		$select = db_select('field_data_group_audience', 'og');
		$select->fields('og',array('entity_id'))
		->condition('og.group_audience_gid', $recordog->gid)
		->condition('og.bundle', 'poll')
		->orderBy('og.group_audience_created', 'DESC');

		$record = $select->execute()->fetchObject();

		if ($record) {

				$poll = node_load($record->entity_id);
				$poll = poll_block_latest_poll_view($poll);
				//$pollContent=str_replace('/poll','/group-poll/'.$recordog->gid,$poll->content);

				$poll->content['links']['#links'][0]['href']=$GLOBALS['base_url'].'/group-poll/'.$recordog->gid;
				$poll->links[0]['href']=$GLOBALS['base_url'].'/group-poll/'.$recordog->gid;

				$variables->subject = t('Poll');
				$poll->content['poll_view_results']['#markup']=str_replace('/poll','/group-poll/'.$recordog->gid,$poll->content['poll_view_results']['#markup']);
				$poll->content['poll_view_results']['#markup']=str_replace('Older polls','VIEW ALL',$poll->content['poll_view_results']['#markup']);
				  $poll->content['links']['#links'][0]['title']='VIEW ALL';
				$variables['content']= drupal_render($poll->content);
		}
		else{
			$variables['content']= '';
		}

	}

  }
}

function interactui_nb_select($variables) {

  $element = $variables['element'];
  $paramArray=explode('/',$_GET['q']);
  if(($paramArray[1]=='register')){

    if($element['#title']=='Groups'){
        static $i=0;
        $element['#attributes']['type'] = 'checkbox';
        element_set_attributes($element, array('id', 'name', 'size'));
        _form_set_class($element, array('form-select'));
        $OPTIONS= form_select_options($element);
        $output='';
        foreach($element['#options']['Other groups'] as $key=>$value){
            $i++;
            $output.= '<input type="checkbox" name="group_audience[und]['.$i.']" value="'.$key.'" class="form-checkbox" data-thmr="thmr_92">  <label class="option" for="edit-field-test-check-und-1" data-thmr="thmr_94">'.$value.'</label><br/>';
        }
    return $output;
    }else{
        element_set_attributes($element, array('id', 'name', 'size'));
        _form_set_class($element, array('form-select'));
        return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
    }
  }else{
    element_set_attributes($element, array('id', 'name', 'size'));
    _form_set_class($element, array('form-select'));
    return '<select' . drupal_attributes($element['#attributes']) . '>' . form_select_options($element) . '</select>';
  }
}

function interactui_nb_preprocess_field(&$vars) {

	if($vars['element']['#field_name'] == 'field_source') {
		$sourceNodeId=$vars['element']['#items'][0]['value'];
		$sourceNode = node_load($sourceNodeId);
    	$vars['element']['#items'][0]['safe_value'] = l($sourceNode->title, 'node/'.$sourceNodeId);
    	$vars['element']['#items'][0]['value'] = l($sourceNode->title, 'node/'.$sourceNodeId);
    	$vars['element'][0]['#markup'] = l($sourceNode->title, 'node/'.$sourceNodeId);
    	$vars['items'][0]['#markup'] = l($sourceNode->title, 'node/'.$sourceNodeId);
 	}

 	if($vars['element']['#field_name'] == 'field_permalink'){
		$vars['element']['#items'][0]['safe_value'] = l($vars['element']['#items'][0]['value'],$vars['element']['#items'][0]['value']);
		$vars['element']['#items'][0]['value'] = l($vars['element']['#items'][0]['value'],$vars['element']['#items'][0]['value']);
		$vars['element'][0]['#markup'] = l(strip_tags($vars['element']['#items'][0]['value']),strip_tags($vars['element']['#items'][0]['value']));
		$vars['items'][0]['#markup'] = l(strip_tags($vars['element']['#items'][0]['value']),strip_tags($vars['element']['#items'][0]['value']));
	}

}
