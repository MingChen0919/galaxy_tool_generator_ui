<?php
/**
 * Form handler for associate accounts page.
 */
function api_keys_form($form, &$form_state) {
  $form['platform'] = [
    '#type' => 'radios',
    '#title' => t('Platform'),
    '#description' => t('Select a platform that you API key is associated.'),
    '#options' => drupal_map_assoc([
      'Test Tool Shed',
      'Tool Shed',
      //            'Galaxy Instance with Admin API',
    ]),
    '#default_value' => 'Test Tool Shed',
  ];
  $form['test_tool_shed'] = [
    '#type' => 'fieldset',
    '#title' => t('Test Tool Shed Account Info'),
    '#collapsible' => TRUE,
    '#states' => [
      'visible' => [
        ':input[name="platform"]' => ['value' => 'Test Tool Shed'],
      ],
    ],
  ];
  $form['test_tool_shed']['test_tool_shed_username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The public username of your <span style="color: #FF5666">Test Tool Shed account</span>'),
  ];
  $form['test_tool_shed']['test_tool_shed_api_key'] = [
    '#type' => 'password',
    '#title' => t('API Key'),
    '#description' => t('The associated API key of your <span style="color: #FF5666">Test Tool Shed account</span>'),
  ];

  $form['tool_shed'] = [
    '#type' => 'fieldset',
    '#title' => t('Tool Shed Account Info'),
    '#collapsible' => TRUE,
    '#states' => [
      'visible' => [
        ':input[name="platform"]' => ['value' => 'Tool Shed'],
      ],
    ],
  ];
  $form['tool_shed']['tool_shed_username'] = [
    '#type' => 'textfield',
    '#title' => t('Username'),
    '#description' => t('The public username of your <span style="color: #19B5FE">Tool Shed account</span>'),
  ];
  $form['tool_shed']['tool_shed_api_key'] = [
    '#type' => 'password',
    '#title' => t('API Key'),
    '#description' => t('The associated API key of your <span style="color: #19B5FE">Tool Shed account</span>'),
  ];

  //    $form['galaxy_admin'] = [
  //        '#type' => 'fieldset',
  //        '#title' => t('Galaxy Admin Account Info'),
  //        '#collapsible' => TRUE,
  //        '#states' => [
  //            'visible' => [
  //                ':input[name="platform"]' => ['value' => 'Galaxy Instance with Admin API']
  //            ]
  //        ]
  //    ];
  //    $form['galaxy_admin']['galaxy_server_url'] = [
  //        '#type' => 'textfield',
  //        '#title' => t('Galaxy Server URL'),
  //        '#description' => t('The URL of a Galaxy server that you have admin permission.'),
  //    ];
  //    $form['galaxy_admin']['galaxy_admin_username'] = [
  //        '#type' => 'textfield',
  //        '#title' => t('Username'),
  //        '#description' => t('The username of a Galaxy server that you have admin permission.'),
  //    ];
  //    $form['galaxy_admin']['galaxy_admin_api_key'] = [
  //        '#type' => 'password',
  //        '#title' => t('API key'),
  //        '#description' => t('The associated API key of a Galaxy server that you have admin permission.'),
  //    ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => 'Submit',
  ];

  return $form;
}

/**
 * Form submission handler.
 */
function api_keys_form_submit($form, &$form_state) {
  $form_state['rebuild'] = TRUE;
  $platform = $form_state['values']['platform'];
  switch ($platform) {
    case 'Test Tool Shed':
      variable_set('testtoolshed_username', $form_state['values']['test_tool_shed_username']);
      variable_set('testtoolshed_api', $form_state['values']['test_tool_shed_api_key']);
      drupal_set_message('Test Tool Shed API has been updated.');
      break;
    case 'Tool Shed':
      variable_set('toolshed_username', $form_state['values']['tool_shed_username']);
      variable_set('toolshed_api', $form_state['values']['tool_shed_api_key']);
      drupal_set_message('Tool Shed API has been updated.');
      break;
    //        case 'Galaxy Instance with Admin API':
    //            variable_set('galaxy_admin_api', $form_state['values']['galaxy_admin_username']);
    //            variable_set('galaxy_admin_api', $form_state['values']['galaxy_admin_api_key']);
    //            drupal_set_message('Galaxy instance credentials has been updated.');
    //            break;
  }

}