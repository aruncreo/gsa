<?php
$vars = get_defined_vars();
$view = get_artx_drupal_view();
$message = $view->get_incorrect_version_message();
if (!empty($message)) {
print $message;
//die();
}
$is_blog_page = isset($node->body['und'][0]['summary']) && ($node->body['und'][0]['summary'] == 'ART_BLOG_PAGE') ? true : false;
?>
<div id="node-<?php print $node->nid; ?>" class="node<?php if(!empty($type)) { echo ' '.$type; } if ($sticky) { echo ' sticky'; } if ($promote) { print ' promote'; } if (!$status) { print ' node-unpublished'; } ?>">
  <?php if (!$is_blog_page): ?>
<article class="gs-post gs-article">

<h2 class="gs-postheader"><?php print render($title_prefix); ?>
<?php echo art_node_title_output($title, $node_url, $page); ?>
<?php print render($title_suffix); ?>
</h2>

<?php if ($submitted): ?>
<div class="gs-postheadericons gs-metadata-icons">
<?php print render($submitted); ?>
</div>
<?php endif; ?>

<div class="gs-postcontent gs-postcontent-0 clearfix">
<div class="gs-article dasda">
  <?php endif; ?>
  <?php
    // We hide the comments and links now so that we can render them later.
    hide($content['comments']);
    $terms = get_terms_D7($content);
    print render($content);
    if ($is_front != 1) :
      if (arg(0) !== 'dashboard' && $node->type !== 'poll') :
        print '<p><strong>Views:</strong> ' . $content['count']['totalcount'] . '</p>';
      endif;
    endif;
    print $featured_content_flag;
    print $questionable_flag_link;
  ?>

<?php if (!$is_blog_page): ?>
</div>
</div>
</article><?php
$view->print_comment_node($vars);
?>
  <?php endif; ?>
</div>

