(function ($) {
  "use strict";

  /**
   * Provides client-side form validation for the petitions signature form.
   */
  Drupal.behaviors.petitionssignatureformFormValidation = {
    attach: function () {
      $('#petitionssignatureform-signature-form').submit(function (event) {
        var emailField = $('#edit-email'), emailValue = emailField.val().trim(), pattern = /^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,4}$/;
        if (!pattern.test(emailValue)) {
          emailField.next('.error-message').remove();
          emailField.addClass('error');
          event.preventDefault();
        }
        else {
          emailField
            .removeClass('error');
        }
      });
    }
  };

})(jQuery);
