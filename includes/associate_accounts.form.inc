<?php
/**
 * Form handler for associate accounts page.
 */
function associate_accounts_form($form, &$form_state) {
  $form['test_tool_shed'] = [
    '#type' => 'fieldset',
    '#title' => t('Test Tool Shed Account Info'),
    '#collapsible' => TRUE,
  ];
  $form['test_tool_shed']['username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The public username of your Test Tool Shed account'),
  ];
  $form['test_tool_shed']['test_tool_shed_api_key'] = [
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#description' => t('The associated API key of your Test Tool Shed account'),
  ];
  
  $form['tool_shed'] = [
    '#type' => 'fieldset',
    '#title' => t('Tool Shed Account Info'),
    '#collapsible' => TRUE,
  ];
  $form['tool_shed']['username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The public username of your Test Tool Shed account'),
  ];
  $form['tool_shed']['tool_shed_api_key'] = [
    '#type' => 'textfield',
    '#title' => t('API Key'),
    '#description' => t('The associated API key of your Test Tool Shed account'),
  ];

  $form['galaxy_admin'] = [
    '#type' => 'fieldset',
    '#title' => t('Galaxy Admin Account Info'),
    '#collapsible' => TRUE,
  ];
  $form['galaxy_admin']['galaxy_server_url'] = [
    '#type' => 'textfield',
    '#title' => t('Galaxy Server URL'),
    '#description' => t('The URL of a Galaxy server that you have admin permission.'),
  ];
  $form['galaxy_admin']['username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The username of a Galaxy server that you have admin permission.'),
  ];
  $form['galaxy_admin']['galaxy_admin_api_key'] = [
    '#type' => 'textfield',
    '#title' => t('API key'),
    '#description' => t('The associated API key of a Galaxy server that you have admin permission.'),
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Submit',
  ];

  return $form;
}

/**
 * Form submission handler.
 */
function associate_accounts_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
}