<?php

/**
 * Form handler for publishing galaxy tools.
 */
function publish_to_test_tool_shed_form($form, &$form_state)
{
    // first, check if API key and username for test tool shed exists
    $testtoolshed_username = variable_get('testtoolshed_username', '');
    $testtoolshed_api = variable_get('testtoolshed_api', '');
    if ($testtoolshed_username == '' or $testtoolshed_api == '') {
        $form['return_to_account_form'] = [
            '#markup' => t('Username or API key from a Test Tool Shed account is required. ' . l('Please provide this information first.', 'associate_accounts'))
        ];
        return $form;
    }

    // select a galaxy tool to publish.
    $all_galaxy_tools = get_galaxy_tools();
    if (empty($all_galaxy_tools)) {
        $form['no_galaxy_tools'] = [
            '#markup' => 'No Galaxy tools available. Please ' . l('create a Galaxy tool', 'node/add/webform') . ' first.',
        ];
        return $form;
    }
    $form['galaxy_tool_directory'] = [
        '#type' => 'select',
        '#title' => t('Select a Galaxy tool'),
        '#options' => drupal_map_assoc($all_galaxy_tools),
    ];

    // select publishing destination
    //  $form['publish_destination'] = [
    //    '#type' => 'radios',
    //    '#title' => t('Publishing destination'),
    //    '#options' => [
    //      'testtoolshed' => l('Test Toolshed', 'https://testtoolshed.g2.bx.psu.edu'),
    //      'toolshed' => l('Toolshed', 'https://toolshed.g2.bx.psu.edu'),
    //    ],
    //    '#default_value' => 'testtoolshed',
    //  ];

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
        '#type' => 'value',
        '#value' => variable_get('testtoolshed_username'),
    ];
    $form['prepare_repository']['description'] = [
        '#type' => 'textfield',
        '#title' => t('Synopsis'),
        '#description' => t('A short description for the tool.'),
        '#required' => TRUE,
    ];
    $form['prepare_repository']['long_description'] = [
        '#type' => 'textarea',
        '#title' => t('Detailed description'),
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
            'unrestricted',
            'tool_dependency_definition',
            'repository_suite_definition',
        ]),
        '#default_value' => 'unrestricted',
    ];
    $form['prepare_repository']['categories'] = [
        '#type' => 'textarea',
        '#title' => t('Categories'),
        '#description' => t('The category that this tool should belong to. Multiple
      categories can be separated by comma, space or newline.'),
    ];
    $form['prepare_repository']['message'] = [
        '#type' => 'textfield',
        '#title' => t('Message'),
        '#description' => t('Commit message for tool shed upload.'),
        '#required' => TRUE,
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
function publish_to_test_tool_shed_form_submit($form, &$form_state)
{
    // create .shed.yml file for planemo to publish tool to toolshed.
    $galaxy_tool_name = $form_state['values']['galaxy_tool_directory'];
    $shed_yml_path = 'public://galaxy_tools/' . $galaxy_tool_name . '/.shed.yml';
    $shed_yml = [];
    $shed_yml['name'] = $form_state['values']['name'];
    $shed_yml['owner'] = $form_state['values']['owner'];
    $shed_yml['description'] = $form_state['values']['description'];
    $shed_yml['long_description'] = $form_state['values']['long_description'];
    $shed_yml['remote_repository_url'] = $form_state['values']['remote_repository_url'];
    $shed_yml['type'] = $form_state['values']['type'];
    $shed_yml['categories'] = $form_state['values']['categories'];

    $shed_yml_string = yaml_emit($shed_yml);
    file_put_contents($shed_yml_path, $shed_yml_string);


    // publish tool
    $tool_directory = '/var/www/html/sites/default/files/galaxy_tools/' . $galaxy_tool_name;


    // TODO: unable to get some toolshed API working, therefore, switch to the planemo method to upload updated files.
    //  // construct a tar/zip archive from the files within the galaxy tool directory.
    //  if (file_exists($tool_directory . '.tar.gz')) {
    //    unlink($tool_directory . '.tar.gz');
    //  }
    //  $phar = new PharData($tool_directory . '.tar');
    //  $phar->compress(Phar::GZ);
    //  $gtrepositories = new GTRepositories('https://testtoolshed.g2.bx.psu.edu/', 'mingchen0919', '6650626edf6ef75b2ed1fbf21141a660');
    //  $gtrepositories->create_changeset_revision('e55c0ae923f1d2c4', $tool_directory . '.tar.gz', 'update new xml files');


    // create repo
    // TODO: first check if the repository already exists.
    // TODO: if repository doesn't exist, use GTRepositories->index() to create the repository.
    // TODO: if repository already exists, use     to update the repository.

    // publish to untested tools only to test tool shed.
    $shed_key = variable_get('testtoolshed_api', '');
    $shed_owner = variable_get('testtoolshed_username', '');
    $command_create_repo = 'sudo -u root planemo shed_create --shed_key ' . $shed_key .
        ' --owner ' . $shed_owner .
        ' --shed_target testtoolshed ' . $tool_directory;
    exec($command_create_repo, $create_repo_output, $return_var_create);
    if (!empty($create_repo_output)) {
        $create_repo_output = implode('<br/>', $create_repo_output);
        if (preg_match('/successfully/', $create_repo_output)) {
            drupal_set_message('Repository has been successfully created!');
        } else {
            drupal_set_message($create_repo_output);
        }
    }

    // update repo
    $message = $form_state['values']['message'];
    $command_update_repo = 'sudo -u root planemo shed_update --check_diff --shed_key ' . $shed_key .
        ' --message' . $message .
        ' --owner ' . $shed_owner .
        ' --shed_target testtoolshed ' . $tool_directory;
    exec($command_update_repo, $update_repo_output, $return_var_update);
    if (!empty($update_repo_output)) {
        $update_repo_output = implode('<br/>', $update_repo_output);
        if (preg_match('/successfully/', $update_repo_output)) {
            drupal_set_message('Repository has been successfully updated!');
        } else {
            drupal_set_message($update_repo_output);
        }
    }

    $form_state['rebuild'] = TRUE;
}