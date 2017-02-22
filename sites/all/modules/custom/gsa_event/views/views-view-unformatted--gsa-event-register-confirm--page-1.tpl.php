<?php
// $Id: views-view-unformatted--gsa-event-register-confirm--page-1.tpl.php 6 2012-06-19 23:25:16Z nikunjk $
/**
 * @file views-view-unformatted.tpl.php
 * Default simple view template to display a list of rows.
 *
 * @ingroup views_templates
 */
?>
<?php if (!empty($title)): ?>
  <h3><?php print $title; ?></h3>
<?php endif; ?>
<?php foreach ($rows as $id => $row): ?>
  <div class="<?php print $classes[$id]; ?>">
    <?php print $row; ?>
  </div>
<?php endforeach; ?>
<?php if ($class_output): ?>
<?php print $class_output; ?>
<?php endif; ?>
