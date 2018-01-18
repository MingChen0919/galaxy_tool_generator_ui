<?php

/**
 * Form handler for publishing galaxy tools.
 */
function publish_tool_repository_form($form, &$form_state) {

  // repository content
  // markup to display structure of tool repository directory
  exec('tree -F /var/www/html/sites/default/files/galaxy_tool_repository', $output);
  $output = preg_replace('/`/', '|', $output);
  $form['repository_structure'] = [
    '#type' => 'fieldset',
    '#title' => 'Tool Repository Structure',
    '#collapsible' => TRUE,
  ];
  $output[0] = 'Repository Directory: galaxy_tool_repository';
  $repository_content_markup = implode('<br/>', $output);
  $form['repository_structure']['content'] = [
    '#markup' => $repository_content_markup,
  ];

  // first, check if API key and username for test tool shed account exists
  $testtoolshed_username = variable_get('testtoolshed_username', '');
  $testtoolshed_api = variable_get('testtoolshed_api', '');
  if ($testtoolshed_username == '' or $testtoolshed_api == '') {
    drupal_set_message('Please go to the ' . l('API Keys page', 'api_keys') .
      ' to add the API key for your <b>Galaxy Test Tool Shed account<b/>.', 'warning');
    return $form;
  }

  // check if API key and username for tool shed account exists
  $toolshed_username = variable_get('toolshed_username', '');
  $toolshed_api = variable_get('toolshed_api', '');
  if ($toolshed_username == '' or $toolshed_api == '') {
    drupal_set_message('Please go to the ' . l('API Keys page', 'api_keys') .
      ' to add the API key for your <b>Galaxy Tool Shed account<b/>.', 'warning');
    return $form;
  }

  // prepare tool repository
  $form['repository'] = [
    '#type' => 'fieldset',
    '#title' => t('Repository metadata'),
    '#collapsible' => TRUE,
  ];
  $form['repository']['name'] = [
    '#type' => 'textfield',
    '#title' => 'Name',
    '#required' => TRUE,
    '#description' => t('Tool repository name.'),
  ];
  $form['repository']['owner'] = [
    '#type' => 'value',
    '#value' => variable_get('testtoolshed_username'),
  ];
  $form['repository']['description'] = [
    '#type' => 'textfield',
    '#title' => t('Synopsis'),
    '#description' => t('A short description for the tool.'),
    '#required' => TRUE,
  ];
  $form['repository']['long_description'] = [
    '#type' => 'textarea',
    '#title' => t('Detailed description'),
    '#description' => t('A longer README type description of the package, as tool 
      dependencies do no currently support README files.'),
  ];
  $form['repository']['remote_repository_url'] = [
    '#type' => 'textfield',
    '#title' => t('Remote repository URL'),
    '#description' => t('This should be the path to the folder in your github repository, 
      on the branch you create releases from (usually master). This will eventually 
      be used with the toolshed for update hooks.'),
  ];
  $form['repository']['type'] = [
    '#type' => 'select',
    '#title' => t('The repository type'),
    '#options' => drupal_map_assoc([
      'unrestricted',
      'tool_dependency_definition',
      'repository_suite_definition',
    ]),
    '#default_value' => 'unrestricted',
  ];
  $form['repository']['categories'] = [
    '#type' => 'textarea',
    '#title' => t('Categories'),
    '#description' => t('The category that this tool should belong to. Multiple
      categories can be separated by comma, space or newline.'),
    '#required' => TRUE,
  ];
  $form['repository']['message'] = [
    '#type' => 'textfield',
    '#title' => t('Message'),
    '#description' => t('Commit message for tool shed upload.'),
    '#required' => TRUE,
  ];

  $form['repository']['actions'] = [
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
  drupal_set_message('Publish to <b>Test Tool Shed</b>');
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
  drupal_set_message('Publish to <b>Tool Shed</b>');
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


/**
 * @param $form
 * @param $form_state
 *
 * @return mixed returns a form elements array for mirroring GTG tool repository
 * and tool shed repository
 *
 */
function mirror_tool_repository_form($form, &$form_state) {
  // mirror tool repository
  $form['mirror_tool_repository'] = [
    '#type' => 'fieldset',
    '#title' => t('Mirror Tool Repository'),
    '#collapsible' => TRUE,
    '#description' => t('Allows mapping the GTG tool repository to a Galaxy tool repository and vice versa.
      The <b>From GTG to Galaxy</b> button is for integrating updates from GTG tool repository into tool repository running within 
      a Galaxy instance for checking development updates.
      The <b>From Galaxy to GTG</b> button is for integrating updates from Galaxy instance into GTG tool repository for publishing.'),
  ];
  $form['mirror_tool_repository']['mirror_tool_repository'] = [
    '#type' => 'textfield',
    '#title' => t('Tool Repository name'),
    '#description' => t('The name of an installed tool repository in a running Galaxy instance'),
    '#required' => TRUE,
  ];
  $form['mirror_tool_repository']['mirror_actions'] = [
    'from_gtg_to_galaxy' => [
      '#type' => 'submit',
      '#value' => 'From GTG to Galaxy',
      '#submit' => ['mirror_from_gtg_to_galaxy'],
    ],
    'from_galaxy_to_gtg' => [
      '#type' => 'submit',
      '#value' => 'From Galaxy to GTG',
      '#submit' => ['mirror_from_galaxy_to_gtg'],
    ],
  ];

  drupal_add_js(drupal_get_path('module', 'galaxy_tool_generator_ui') . '/js/mirror_gtg_to_galaxy_confirm.js');
  drupal_add_js(drupal_get_path('module', 'galaxy_tool_generator_ui') . '/js/mirror_galaxy_to_gtg_confirm.js');

  return $form;
}

/**
 * @param $form
 * @param $form_state
 * replace tool shed repository with GTG tool repository
 */
function mirror_from_gtg_to_galaxy($form, &$form_state) {

  $command = 'find . -name ' . $form_state['values']['mirror_tool_repository'];
  exec($command, $shed_tool_repository_paths, $shed_tool_return_var);


  if (isset($shed_tool_repository_paths[1]) && file_exists($shed_tool_repository_paths[1])) {
    $shed_tool_repository = str_replace('./sites/default/files/', 'public://', $shed_tool_repository_paths[1]);

    // remove shed_tool_repository
    $command_rm = 'rm -rf ' . $shed_tool_repository_paths[1] . '/*';
    exec($command_rm, $rm_output, $rm_return_var);

    // copy gtg_tool_repository to shed_tool_repository
    $command_cp = 'cp -r ./sites/default/files/galaxy_tool_repository/* ' . $shed_tool_repository_paths[1];
    exec($command_cp, $cp_output, $cp_return_var);
    $message = 'The Galaxy tool repository <b>' . $shed_tool_repository . '</b> has been
               replaced with the GTG tool repository.';
    drupal_set_message($message);
  }
  else {
    drupal_set_message('Tool repository <b>' .
      $form_state['values']['mirror_tool_repository'] .
      '</b> does not exist!<br/>' .
      'Please make sure you have a running Galaxy instance and the tool repository has been installed.', 'error');
  }

  $form_state['rebuild'] = TRUE;
}

/**
 * @param $form
 * @param $form_state
 * replace GTG tool repository with shed tool repository.
 */
function mirror_from_galaxy_to_gtg($form, &$form_state) {
  $command = 'find . -name ' . $form_state['values']['mirror_tool_repository'];
  exec($command, $shed_tool_repository_paths, $shed_tool_return_var);

  if (isset($shed_tool_repository_paths[1]) && file_exists($shed_tool_repository_paths[1])) {
    $shed_tool_repository = str_replace('./sites/default/files/', 'public://', $shed_tool_repository_paths[1]);

    // remove gtg_tool_repository
    $command_rm = 'rm -rf ./sites/default/files/galaxy_tool_repository/*';
    exec($command_rm, $rm_output, $rm_return_var);

    // copy shed_tool_repository to gtg_tool_repository
    $command_cp = 'cp -r ' . $shed_tool_repository_paths[1] . '/* ./sites/default/files/galaxy_tool_repository/ ';
    exec($command_cp, $cp_output, $cp_return_var);
    $message = 'The GTG tool repository  has been replaced with the shed tool repository <b>' . $shed_tool_repository . '</b>';
    drupal_set_message($message);
  }
  else {
    drupal_set_message('Tool repository <b>' .
      $form_state['values']['mirror_tool_repository'] .
      '</b> does not exist!<br/>' .
      'Please make sure you have a running Galaxy instance and the tool repository has been installed.', 'error');
  }

  $form_state['rebuild'] = TRUE;
}
