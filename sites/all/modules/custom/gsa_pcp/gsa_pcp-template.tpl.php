<?php

/**
 * @file
 * Default theme implementation for PCP block
 *
 * Available variables:
 *  $uid: Current user ID.
 *  $current_percent: From 0 to 100% of how much the profile is complete.
 *  $next_percent: The percent if the user filled the next field.
 *  $completed: How many fields the user has filled.
 *  $incomplete: The inverse of $completed, how many empty fields left.
 *  $total: Total number of fields in profile.
 *  $nextfield_title: The name of the suggested next field to fill (human readable name).
 *  $nextfield_name: The name of the suggested next field to fill (machine name).
 *  $nextfield_id: The id of the $nextfield.
 *
 * @see template_preprocess_pcp_profile_percent_complete()
 */
?>
<style type="text/css">
  .gsa_pcp-percent-bar{ width: <?php print $current_percent; ?>%; }
</style>

<div class="gsa_pcp-wrapper">
  <?php print t('!complete% Complete', array('!complete' => $current_percent)); ?>

  <div class="gsa_pcp-percent-bar-wrapper">
    <div class="gsa_pcp-percent-bar"></div>
  </div>
</div>

<?php
  if (isset($nextfield_id) && isset($next_percent)) {
    print t('Filling out <em>!empty-field</em> will bring your profile to !complete% complete', array('!empty-field' => l($nextfield_title, $next_path), '!complete' => $next_percent));
  }
?>
