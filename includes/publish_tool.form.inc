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
  $form['prepare_repository']['long_description'] = [
    '#type' => 'textarea',
    '#title' => t('Long description'),
    '#description' => t('A longer README type description of the package, as tool 
      dependencies do no currently support README files.'),
  ];
  $form['prepare_repository']['remote_repository_url'] = [
    '#type' => 'textfield',
    '#title' => t('Remote repository URL'),
    '#description' => t('This should be the path to the folder in your github repository, 
      on the branch you create releases from (usually master). This will eventually 
      be used with the toolshed for update hooks.'),
  ];
  $form['prepare_repository']['type'] = [
    '#type' => 'select',
    '#title' => t('The repository type'),
    '#options' => drupal_map_assoc([
      'Data Managers',
      'Packages',
      'Tool Suites',
      'Tools',
    ]),
  ];
  $form['prepare_repository']['categories'] = [
    '#type' => 'textarea',
    '#title' => t('Categories'),
    '#description' => t('The category that this tool should belong to. Multiple
      categories can be separated by comma, space or newline.'),
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Publish'),
  ];
  return $form;
}

/**
 * publish_tool_form submit callback.
 */
function publish_tool_form_submit($form, &$form_state) {
  dpm($form_state);
  $galaxy_tool_name = $form_state['values']['galaxy_tool_directory'];
  $shed_yml = 'public://galaxy_tools/' . $galaxy_tool_name . '/.shed.yml';
  $shed_yml_string = 'name: ' . $form_state['values']['name'];
  $shed_yml_string .= 'owner: ' . $form_state['values']['owner'];
  $shed_yml_string .= 'description: ' . $form_state['values']['description'];
  $shed_yml_string .= 'long_description' . $form_state['values']['long_description'];
  $shed_yml_string .= 'remote_repository_url: ' . $form_state['values']['remote_repository_url'];
  $shed_yml_string .= 'type: ' . $form_state['values']['type'];
  $shed_yml_string .= 'categories: ' . $form_state['values']['categories'];

  file_put_contents($shed_yml, $shed_yml_string);

  $form_state['rebuild'] = TRUE;
}