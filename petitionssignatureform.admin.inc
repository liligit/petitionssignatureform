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
  $form['petitionssignatureform_api_endpoint'] = array(
    '#type' => 'textfield',
    '#title' => t('API endpoint'),
    '#description' => t('The absolute URL to the API endpoint for the Petitions site to submit signatures to, e.g., <code>http://example.com/v1</code>.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_api_endpoint'),
    '#required' => TRUE,
  );
  $form['petitionssignatureform_api_key'] = array(
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#description' => t('Your API key for the Petitions site, e.g., <code>95c0631b4986959bc0c22a5373c0e41f232dfab6</code>.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_api_key'),
    '#required' => TRUE,
  );
  $form['petitionssignatureform_allow_insecure'] = array(
    '#type' => 'checkbox',
    '#title' => t('Allow insecure SSL.'),
    '#description' => t('Do not verify the peer or check for a common name in the peer certificate. Enable this to use SSL with a self-signed certificate, for example.<br /><strong>Warning:</strong> This setting has <a href="!url">security implications</a>. Do not enable it without understanding them.', array(
      '!url' => 'http://php.net/manual/function.curl-setopt.php',
    )),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_allow_insecure'),
  );

  $form['petitionssignatureform_thank_you_title'] = array(
    '#type' => 'textfield',
    '#title' => t('Thank you title'),
    '#descritiption' => t('Title above thank you message to display upon signature submission. No markup allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_thank_you_title'),
  );
  $form['petitionssignatureform_thank_you_message'] = array(
    '#type' => 'textarea',
    '#title' => t('Thank you message'),
    '#descritiption' => t('The message to display upon signature submission. Some HTML allowed.'),
    '#default_value' => petitionssignatureform_variable_get('petitionssignatureform_thank_you_message'),
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
