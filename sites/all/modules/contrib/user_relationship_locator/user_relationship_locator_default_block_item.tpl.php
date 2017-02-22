<?php

/**
 * @file
 *  Theme for individual block item
 *
 * $requester
 * $requestee
 * $relationship
 */
?>

<li>
  <a class="user-link" href="<?php print base_path();?>user/<?php print $requestee->uid ?>"><?php print $requestee->name?></a>
    <div class="relationship-link">
      <?php print theme('user_relationships_request_relationship_direct_link', array('relate_to' => $requestee, 'relationship_type' => $relationship)); ?>
    </div>
</li>
