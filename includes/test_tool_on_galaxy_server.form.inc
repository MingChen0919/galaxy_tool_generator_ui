<?php
/**
 * Form handler for test tool on galaxy server page.
 */
function test_tool_on_galaxy_server_form($form, &$form_state) {
  $form['test_tool_shed_credentials'] = [
    '#type' => 'fieldset',
    '#title' => t('Test Tool Shed Credentials'),
    '#collapsible' => TRUE,
  ];
  $form['test_tool_shed_credentials']['username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('Test Tool Shed account username.'),
    '#ajax' => [
      'callback' => 'tools_by_owner_ajax_callback',
      'wrapper' => 'tools_by_owner_wrapper',
    ],
  ];
  $form['test_tool_shed_credentials']['test_tool_shed_api_key'] = [
    '#type' => 'password',
    '#title' => t('Test Tool Shed API key'),
    '#ajax' => [
      'callback' => 'tools_by_owner_ajax_callback',
      'wrapper' => 'tools_by_owner_wrapper',
    ],
  ];
  $tools_by_owner_options = [];
  $username = isset($form_state['values']['username']) ? $form_state['values']['username'] : '';
  $test_tool_shed_api_key = isset($form_state['values']['test_tool_shed_api_key']) ? $form_state['values']['test_tool_shed_api_key'] : '';
  if (!empty($username) & !empty($test_tool_shed_api_key)) {
    $gtrepositories = new GTRepositories($username, $test_tool_shed_api_key, 'https://testtoolshed.g2.bx.psu.edu/');
    $all_tools = $gtrepositories->index('', '', '', '', '', '', $username);
    foreach ($all_tools as $tool) {
      $tools_by_owner_options[] = $tool->name;
    }
    $tools_by_owner_options = array_values($tools_by_owner_options);
  }
  $form['target_tool'] = [
    '#type' => 'fieldset',
    '#title' => t('Target tool'),
    '#collapsible' => TRUE,
    '#prefix' => '<div id="tools_by_owner_wrapper">',
    '#suffix' => '</div>',
  ];
  $form['target_tool']['tools_by_owner'] = [
    '#type' => 'select',
    '#title' => t('Select a tool'),
    '#description' => t(''),
    '#options' => drupal_map_assoc($tools_by_owner_options),
  ];

  return $form;
}

/**
 * ajax callback to update the tools_by_owner field.
 */
function tools_by_owner_ajax_callback($form, &$form_state) {
  return $form['target_tool'];
}