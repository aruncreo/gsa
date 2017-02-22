<div class="<?php if (isset($classes)) print $classes; ?>" id="<?php print $block_html_id; ?>"<?php print $attributes; ?>>
<div class="gs-box gs-post">
<div class="gs-box-body gs-post-body">
<article class="gs-post-inner gs-article">
<?php print render($title_prefix); ?>
<?php if ($block->subject): ?>
<h2 class="gs-postheader"><?php print $block->subject ?></h2>
<?php endif;?>
<?php print render($title_suffix); ?>
<div class="gs-postcontent">
<div class="gs-article content">
<?php print $content; ?>
</div>
</div>
<div class="cleared"></div>
</article>
<div class="cleared"></div>
</div>
</div>
</div>
