
(function ($) {

/**
 * Modal Frame object for child windows.
 */
Drupal.modalFrameChild = Drupal.modalFrameChild || {
  processed: false,
  behaviors: {}
};

/**
 * Drupal behavior.
 */
Drupal.behaviors.modalFrameChild = {
  attach: function(context) {
    Drupal.modalFrameChild.attachBehavior(context);
  }
};

/**
 * Attach child dialog behavior.
 */
Drupal.modalFrameChild.attachBehavior = function(context) {
  var self = Drupal.modalFrameChild;
  var settings = Drupal.settings.modalFrameChild || {};

  // If we cannot reach the parent window, then we have nothing else todo here.
  if (!self.isObject(parent.Drupal) || !self.isObject(parent.Drupal.modalFrame)) {
    return;
  }

  // Make sure this behavior is not processed more than once.
  if (!self.processed) {
    self.processed = true;

    // If a form has been submitted successfully, then the server side script
    // may have decided to tell us the parent window to close the popup dialog.
    if (settings.closeModal) {
      parent.Drupal.modalFrame.bindChild(window, true);
      // Close the child window from a separate thread because the current
      // one is busy processing Drupal behaviors.
      setTimeout(function() { parent.Drupal.modalFrame.close(settings.args, settings.statusMessages); }, 1);
      return;
    }

    // Ok, now we can tell the parent window we're ready.
    parent.Drupal.modalFrame.bindChild(window);

    // Install onBeforeUnload callback, if module is present.
    if (self.isObject(Drupal.onBeforeUnload) && !Drupal.onBeforeUnload.callbackExists('modalFrameChild')) {
      Drupal.onBeforeUnload.addCallback('modalFrameChild', function() {
        // Tell the parent window we're unloading.
        parent.Drupal.modalFrame.unbindChild(window);
      });
    }
  }

  // Attach child related behaviors to the current context.
  self.attachBehaviors(context);
};

/**
 * Check if the given variable is an object.
 */
Drupal.modalFrameChild.isObject = function(something) {
  return (something !== null && typeof something === 'object');
};

/**
 * Attach child related behaviors to the iframed document.
 */
Drupal.modalFrameChild.attachBehaviors = function(context) {
  $.each(this.behaviors, function() {
    this(context);
  });
};

/**
 * Add target="_new" to all external URLs.
 */
Drupal.modalFrameChild.behaviors.parseLinks = function(context) {
  $('a:not(.modalframe-processed)', context).addClass('modalframe-processed').each(function() {
    // Do not process links that have the class "modalframe-exclude".
    if ($(this).hasClass('modalframe-exclude')) {
      return;
    }
    // Obtain the href attribute of the link.
    var href = $(this).attr('href');
    // Do not process links with an empty href, or that only have the fragment.
    if (!href || href.length <= 0 || href.charAt(0) == '#') {
      return;
    }
    $(this).attr('target', '_new');
  });
};

})(jQuery);
