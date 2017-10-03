<?php

/**
 * Form handler for publishing galaxy tools.
 */
function publish_tool_form($form, &$form_state) {
  // select a galaxy tool to publish.
  $all_galaxy_tools = get_galaxy_tools();
  $form['galaxy_tool_directory'] = [
    '#type' => 'select',
    '#title' => t('Select a Galaxy tool'),
    '#options' => drupal_map_assoc($all_galaxy_tools),
  ];

  // select publishing destination
  $form['publish_destination'] = [
    '#type' => 'radios',
    '#title' => t('Publishing destination'),
    '#options' => [
      'testtoolshed' => l('Test Toolshed', 'https://testtoolshed.g2.bx.psu.edu'),
      'toolshed' => l('Toolshed', 'https://toolshed.g2.bx.psu.edu'),
    ],
    '#default_value' => 'testtoolshed',
  ];

  // prepare tool repository
  $form['prepare_repository'] = [
    '#type' => 'fieldset',
    '#title' => t('Prepare Tool Repository'),
    '#collapsible' => TRUE,
  ];
  $form['prepare_repository']['name'] = [
    '#type' => 'textfield',
    '#title' => 'Name',
    '#required' => TRUE,
    '#description' => t('Tool repository name.'),
  ];
  $form['prepare_repository']['owner'] = [
    '#type' => 'textfield',
    '#title' => 'Owner',
    '#required' => TRUE,
    '#description' => t('Username of your toolshed/testtoolshed account.'),
  ];
  $form['prepare_repository']['description'] = [
    '#type' => 'textfield',
    '#title' => t('Description'),
    '#description' => t('A short description for the tool.'),
    '#required' => TRUE,
  ];
  $form['prepare_repository']['remote_repository_url'] = [
    '#type' => 'textfield',
    '#title' => t('Remote repository URL'),
    '#description' => t('A github URL to your tool.'),
  ];
  $form['prepare_repository']['long_description'] = [
    '#type' => 'textarea',
    '#title' => t('Long description'),
    '#description' => t('A more detailed description for the tool.'),
  ];
  $form['prepare_repository']['category'] = [
    '#type' => 'textarea',
    '#title' => t('Category'),
    '#description' => t('The category that this tool should belong to. Multiple
      categories can be separated by comma, space or newline.'),
  ];

  return $form;
}

/**
 * publish_tool_form submit callback.
 */
function publish_tool_form_submit($form, &$form_state) {
  dpm($form_state);
}