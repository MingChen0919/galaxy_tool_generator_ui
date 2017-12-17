<?php

/**
 * Form handler for publishing galaxy tools.
 */
function publish_tool_repository_form($form, &$form_state) {
  // first, check if API key and username for test tool shed exists
  $testtoolshed_username = variable_get('testtoolshed_username', '');
  $testtoolshed_api = variable_get('testtoolshed_api', '');
  if ($testtoolshed_username == '' or $testtoolshed_api == '') {
    drupal_set_message('It seems you have not provided API keys associated with your test tool shed account. 
    Please go to the ' . l('API Keys page', 'api_keys') . ' to add this information.', 'warning');
  }

  $toolshed_username = variable_get('toolshed_username', '');
  $toolshed_api = variable_get('toolshed_api', '');
  if ($toolshed_username == '' or $toolshed_api == '') {
    drupal_set_message('It seems you have not provided API keys associated with your tool shed account. 
    Please go to the ' . l('API Keys page', 'api_keys') . ' to add this information.', 'warning');
  }

  // prepare tool repository
  $form['name'] = [
    '#type' => 'textfield',
    '#title' => 'Name',
    '#required' => TRUE,
    '#description' => t('Tool repository name.'),
  ];
  $form['owner'] = [
    '#type' => 'value',
    '#value' => variable_get('testtoolshed_username'),
  ];
  $form['description'] = [
    '#type' => 'textfield',
    '#title' => t('Synopsis'),
    '#description' => t('A short description for the tool.'),
    '#required' => TRUE,
  ];
  $form['long_description'] = [
    '#type' => 'textarea',
    '#title' => t('Detailed description'),
    '#description' => t('A longer README type description of the package, as tool 
      dependencies do no currently support README files.'),
  ];
  $form['remote_repository_url'] = [
    '#type' => 'textfield',
    '#title' => t('Remote repository URL'),
    '#description' => t('This should be the path to the folder in your github repository, 
      on the branch you create releases from (usually master). This will eventually 
      be used with the toolshed for update hooks.'),
  ];
  $form['type'] = [
    '#type' => 'select',
    '#title' => t('The repository type'),
    '#options' => drupal_map_assoc([
      'unrestricted',
      'tool_dependency_definition',
      'repository_suite_definition',
    ]),
    '#default_value' => 'unrestricted',
  ];
  $form['categories'] = [
    '#type' => 'textarea',
    '#title' => t('Categories'),
    '#description' => t('The category that this tool should belong to. Multiple
      categories can be separated by comma, space or newline.'),
  ];
  $form['message'] = [
    '#type' => 'textfield',
    '#title' => t('Message'),
    '#description' => t('Commit message for tool shed upload.'),
    '#required' => TRUE,
  ];

  $form['actions'] = [
    '#type' => 'action',
    'test_tool_shed' => [
      '#type' => 'submit',
      '#value' => 'Publish to Test Tool Shed',
      '#submit' => ['publish_to_test_tool_shed'],
    ],
    'tool_shed' => [
      '#type' => 'submit',
      '#value' => 'Publish to Tool Shed',
      '#submit' => ['publish_to_tool_shed'],
    ],
  ];
  return $form;
}

/**
 * @param $form
 * @param $form_state
 * submit callback to publish repository to test tool shed.
 */
function publish_to_test_tool_shed($form, &$form_state) {
  // create .shed.yml file for planemo to publish tool to toolshed.
  $shed_yml_path = 'public://galaxy_tool_repository/.shed.yml';
  $shed_yml = [];
  $shed_yml['name'] = $form_state['values']['name'];
  $shed_yml['owner'] = $form_state['values']['owner'];
  $shed_yml['description'] = $form_state['values']['description'];
  $shed_yml['long_description'] = $form_state['values']['long_description'];
  $shed_yml['remote_repository_url'] = $form_state['values']['remote_repository_url'];
  $shed_yml['type'] = $form_state['values']['type'];
  $shed_yml['categories'] = array_map('trim', explode(',', $form_state['values']['categories']));

  $shed_yml_string = yaml_emit($shed_yml);
  file_unmanaged_save_data($shed_yml_string, $shed_yml_path, FILE_EXISTS_REPLACE);

  $tool_directory = '/var/www/html/sites/default/files/galaxy_tool_repository';
  $shed_key = variable_get('testtoolshed_api', '');
  $shed_owner = variable_get('testtoolshed_username', '');
  $shed = 'testtoolshed';
  $message = $form_state['values']['message'];
  publish_tool_repository($tool_directory, $shed_key, $shed_owner, $shed, $message);

  $form_state['rebuild'] = TRUE;
}


/**
 * @param $form
 * @param $form_state
 * submit callback to publish repository to tool shed.
 */
function publish_to_tool_shed($form, &$form_state) {
  // create .shed.yml file for planemo to publish tool to toolshed.
  $shed_yml_path = 'public://galaxy_tool_repository/.shed.yml';
  $shed_yml = [];
  $shed_yml['name'] = $form_state['values']['name'];
  $shed_yml['owner'] = $form_state['values']['owner'];
  $shed_yml['description'] = $form_state['values']['description'];
  $shed_yml['long_description'] = $form_state['values']['long_description'];
  $shed_yml['remote_repository_url'] = $form_state['values']['remote_repository_url'];
  $shed_yml['type'] = $form_state['values']['type'];
  $shed_yml['categories'] = array_map('trim', explode(',', $form_state['values']['categories']));

  $shed_yml_string = yaml_emit($shed_yml);
  file_unmanaged_save_data($shed_yml_string, $shed_yml_path, FILE_EXISTS_REPLACE);

  $tool_directory = '/var/www/html/sites/default/files/galaxy_tool_repository';
  $shed_key = variable_get('toolshed_api', '');
  $shed_owner = variable_get('toolshed_username', '');
  $shed = 'toolshed';
  $message = $form_state['values']['message'];
  publish_tool_repository($tool_directory, $shed_key, $shed_owner, $shed, $message);

  $form_state['rebuild'] = TRUE;
}


/**
 * @param $tool_directory
 * @param $shed_key
 * @param $shed_owner
 * @param $shed
 * @param $message
 * this function prepare a tool repository directory and publish the repository
 * to test tool shed or tool shed.
 */
function publish_tool_repository($tool_directory, $shed_key, $shed_owner, $shed, $message) {
  // create repository on tool shed.
  $command_create_repo = 'sudo -u root planemo shed_create --shed_key ' . $shed_key .
    ' --owner ' . $shed_owner .
    ' --shed_target ' . $shed . ' ' . $tool_directory;
  exec($command_create_repo, $create_repo_output, $return_var_create);

  $create_repo_output = implode('<br/>', $create_repo_output);
  if (preg_match('/successfully/', $create_repo_output)) {
    drupal_set_message('Repository has been successfully created!');
  }
  else {
    drupal_set_message($create_repo_output, 'warning');
  }

  // update repository
  $command_update_repo = 'sudo -u root planemo shed_update --check_diff --shed_key ' . $shed_key .
    ' --message \'' . $message . '\'' .
    ' --owner \'' . $shed_owner . '\'' .
    ' --shed_target ' . $shed . ' ' . $tool_directory;
  exec($command_update_repo, $update_repo_output, $return_var_update);
  $update_repo_output = implode('<br/>', $update_repo_output);
  if (preg_match('/successfully/', $update_repo_output)) {
    drupal_set_message('Repository has been successfully updated!');
  }
  else {
    drupal_set_message($update_repo_output, 'warning');
  }
}