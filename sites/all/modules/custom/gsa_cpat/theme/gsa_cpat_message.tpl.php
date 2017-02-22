<?php
  /**
   * Theme template for CPAT mesages
   */
?>
<div class="cpat-message">
  <fieldset class="message-info">
    <div class="message-field">
      <span class="message-label">
        <?php print t('Name:'); ?>
      </span>
      <span class="message-value">
        <?php print $message->sender_name; ?>
      </span>
    </div>
    <div class="message-field">
      <span class="message-label">
        <?php print t('Email:'); ?>
      </span>
      <span class="message-value">
        <?php print "<a href=\"mailto:{$message->sender_mail}\">{$message->sender_mail}</a>"; ?>
      </span>
    </div>
    <div class="message-field">
      <span class="message-label">
        <?php print t('User:'); ?>
      </span>
      <span class="message-value">
        <?php print $username; ?>
      </span>
    </div>
    <div class="message-field">
      <span class="message-label">
        <?php print t('Time:'); ?>
      </span>
      <span class="message-value">
        <?php print format_date($message->timestamp, 'long'); ?>
      </span>
    </div>
    <div class="message-field">
      <span class="message-label">
        <?php print t('Post:'); ?>
      </span>
      <span class="message-value">
        <?php print l($node->title, "node/{$node->nid}"); ?>
      </span>
    </div>
  </fieldset>
  
  <div class="message-field">
    <div class="content">
      <?php print $message->message; ?>
    </div>
  </div>
  
  <div class="message-form">
    <?php print $form; ?>
  </div>
</div>
