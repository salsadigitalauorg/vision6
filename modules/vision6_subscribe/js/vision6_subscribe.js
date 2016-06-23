/**
 * Javascript for vision6_subscribe module.
 * @file vision6.js.
 */

/*global jQuery, Drupal, document, console, window*/

(function ($) {
  'use strict';

  Drupal.behaviors.VisionSixSubscribe = {
    attach: function (context) {
      $(document).ready(function () {

        var validateEmail = function (email) {
          var re = /^([\w-]+(?:\.[\w-]+)*)@((?:[\w-]+\.)*\w[\w-]{0,66})\.([a-z]{2,6}(?:\.[a-z]{2})?)$/i;
          return re.test(email);
        };
        var validateForm = function (sub_form) {
          sub_form.find('[id^="subscribe_message"]').html('');
          sub_form.find('[id^="subscribe_message"]').hide();
          // validate the form via js before it gets submitted
          if (Drupal.settings.vision6_subscribe.email) {
            if (sub_form.find('[id^="edit-email"]').val() === '') {
              sub_form.find('[id^="subscribe_message"]').html(sub_form.find('[id^="subscribe_message"]').html() + '<p>The ' + Drupal.settings.vision6_subscribe.email + ' field is mandatory</p>');
            }
            else if (!validateEmail(sub_form.find('[id^="edit-email"]').val())) {
              sub_form.find('[id^="subscribe_message"]').html(sub_form.find('[id^="subscribe_message"]').html() + '<p>The ' + Drupal.settings.vision6_subscribe.email + ' email you have entered is invalid</p>');
            }
          }
          if (Drupal.settings.vision6_subscribe.approval) {
            if (sub_form.find('[id^="edit-approval"]').prop('checked') === '') {
              sub_form.find('[id^="subscribe_message"]').html(sub_form.find('[id^="subscribe_message"]').html() + '<p>You must accept the privacy statement to subscribe</p>');
            }
          }
          if (sub_form.find('[id^="subscribe_message"]').html() === '') {
            sub_form.find('[id^="edit-submit"]').trigger('click');
          }
          else {
            sub_form.find('[id^="subscribe_message"]').show();
          }
        }
        $('[id^="-vision6-subscribe-subscribe-form"] [id^="edit-submit"]').click(function () {validateForm($(this).parent().parent().parent()); return false; });
      });
    }
  };
})(jQuery);
