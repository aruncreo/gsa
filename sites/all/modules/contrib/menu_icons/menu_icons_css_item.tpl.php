<?php
// $Id: menu_icons_css_item.tpl.php 6 2012-06-19 23:25:16Z nikunjk $

/**
 * @file
 *
 * Template file for generating the CSS file used for the menu-items
 */

/**
 * Variables:
 * $mlid
 * $path
 *
 * @author dylan@opensourcery.com
 */
?>
a.menu-<?php print $mlid ?>, ul.links li.menu-<?php print $mlid ?> a {
  background-image: url(<?php print $path ?>);
  padding-<?php print "$pos:$size"?>px;
  background-repeat: no-repeat;
  background-position: <?php print $pos?>;
  height: <?php print $size?>px;
}

