<?php

/**
 * @file
 * Admin page callback file for the Petitions Signature Form module.
 */

/**
 * Page callback: Form constructor for the admin settings form.
 *
 * @see petitionssignatureform_menu()
 * @see petitionssignatureform_admin_settings_form_validate()
 *
 * @ingroup forms
 */
function petitionssignatureform_admin_settings_form() {
  // Test for the presence of the Petitions PHP SDK.
  $library = libraries_detect(PETITIONSSIGNATUREFORM_SDK);
  if (empty($library['installed'])) {
    $message = t('Install the Petitions PHP SDK according to the instructions in the petitionssignatureform module <a href="!url">README.txt</a>.', array(
      '!url' => url(drupal_get_path('module', 'petitionssignatureform') . '/README.txt'),
    ));
    drupal_set_message($message, 'error');
  }

  $form = array();
  $form['api_settings'] = array(
    '#type' => 'fieldset',
    '#title' => t('API settings'),
    '#collapsible' => TRUE,
    '#collapsed' => petitionssignatureform_module_is_configured(),
  );
  $form['api_settings']['petitionssignatureform_api_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('API endpoint'),
    '#description' => t('The absolute URL to the API endpoint for the Petitions site to submit signatures to, e.g., <code>http://api.whitehouse.gov/v1</code>.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_api_endpoint'),
    '#required' => TRUE,
  );
  $form['api_settings']['petitionssignatureform_petitions_website_url'] = array(
    '#type' => 'textfield',
    '#title' => t('Petitions website URL'),
    '#description' => t('This may be different from the API endpoint, e.g., <code>!petitions</code> and <code>!api</code>.', array(
      '!petitions' => 'https://petitions.whitehouse.gov/',
      '!api' => 'http://api.whitehouse.gov/',
    )),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_petitions_website_url'),
    '#required' => TRUE,
  );
  $form['api_settings']['petitionssignatureform_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#description' => t('Your API key for the Petitions site, e.g., <code>95c0631b4986959bc0c22a5373c0e41f232dfab6</code>.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_api_key'),
    '#required' => TRUE,
  );
  $form['api_settings']['petitionssignatureform_allow_insecure'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow insecure SSL.'),
    '#description' => t('Do not verify the peer or check for a common name in the peer certificate. Enable this to use SSL with a self-signed certificate, for example.<br /><strong>Warning:</strong> This setting has <a href="!url">security implications</a>. Do not enable without understanding them.', array(
      '!url' => 'http://php.net/manual/function.curl-setopt.php',
    )),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_allow_insecure'),
  );

  $form['interface_text_title'] = array(
    '#type' => 'item',
    '#title' => t('User interface text'),
  );
  $form['interface_text'] = array(
    '#type' => 'vertical_tabs',
  );

  $form['interface_text']['accepting_signatures'] = array(
    '#type' => 'fieldset',
    '#title' => t('Petition is accepting signatures'),
    '#description' => t('The interface text to display when the form points at a petition that is accepting signatures.'),
  );
  $form['interface_text']['accepting_signatures']['petitionssignatureform_accepting_signatures_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_accepting_signatures_title'),
  );
  $form['interface_text']['accepting_signatures']['petitionssignatureform_sign_up_field_label'] = array(
    '#type' => 'textfield',
    '#title' => t('"Sign up" field label'),
    '#description' => t('The text to use for the "Sign up" checkbox label. No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_sign_up_field_label'),
  );
  $form['interface_text']['accepting_signatures']['petitionssignatureform_accepting_signatures_privacy_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Privacy policy/terms of service'),
    '#description' => t('An optional statement of privacy policy or terms of service. Leave blank to omit. Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_accepting_signatures_privacy_message'),
  );
  $form['interface_text']['accepting_signatures']['petitionssignatureform_accepting_signatures_note'] = array(
    '#type' => 'textarea',
    '#title' => t('Form note'),
    '#description' => t('A final notice to the user that displays at the bottom of the form. Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_accepting_signatures_note'),
  );

  $form['interface_text']['no_signatures'] = array(
    '#type' => 'fieldset',
    '#title' => t('Petition is not accepting signatures'),
    '#description' => t('The interface text to display when the form points at a petition that is not accepting signatures.'),
  );
  $form['interface_text']['no_signatures']['petitionssignatureform_no_signatures_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_no_signatures_title', t('Petition Closed')),
  );
  $form['interface_text']['no_signatures']['petitionssignatureform_no_signatures_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message text'),
    '#description' => t('Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_no_signatures_message'),
  );

  $form['interface_text']['form_error'] = array(
    '#type' => 'fieldset',
    '#title' => t('Form error'),
    '#description' => t('The interface text to display when an error prevents the form from displaying.'),
  );
  $form['interface_text']['form_error']['petitionssignatureform_error_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_error_title'),
  );
  $form['interface_text']['form_error']['petitionssignatureform_error_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message text'),
    '#description' => t('Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_error_message'),
  );

  $form['interface_text']['signature_submitted'] = array(
    '#type' => 'fieldset',
    '#title' => t('Signature successfully submitted'),
    '#description' => t('The interface text to display when the form submits successfully.'),
  );
  $form['interface_text']['signature_submitted']['petitionssignatureform_thank_you_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_thank_you_title'),
  );
  $form['interface_text']['signature_submitted']['petitionssignatureform_thank_you_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message text'),
    '#description' => t('Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_thank_you_message'),
  );

  $form['interface_text']['submission_failed'] = array(
    '#type' => 'fieldset',
    '#title' => t('Signature submission failed'),
    '#description' => t('The interface text to display when the form encounters an error submitting.'),
  );
  $form['interface_text']['submission_failed']['petitionssignatureform_submission_failed_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Block title'),
    '#description' => t('No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_submission_failed_title'),
  );
  $form['interface_text']['submission_failed']['petitionssignatureform_submission_failed_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Message text'),
    '#description' => t('Some basic HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_submission_failed_message'),
  );

  return system_settings_form($form);
}

/**
 * Form submission handler for petitionssignatureform_admin_settings_form().
 */
function petitionssignatureform_admin_settings_form_validate($form, &$form_state) {
  if (!valid_url($form_state['values']['petitionssignatureform_api_endpoint'], TRUE)) {
    form_set_error('petitionssignatureform_api_endpoint', t('The API endpoint must be a valid absolute URL.'));
  }
}
