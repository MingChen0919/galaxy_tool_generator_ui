<?php

/**
 * @param $form
 * @param $form_state
 *
 * @return mixed
 */
function planemo_test_tool_form($form, &$form_state) {

  $all_files = scandir('public://galaxy_tool_repository/');
  $all_xml_files = [];
  foreach ($all_files as $file) {
    if (preg_match('/\.xml$/', $file)) {
      $all_xml_files[$file] = $file;
    }
  }

  if (count($all_xml_files) < 1) {
    $form['markup'] = [
      '#markup' => t('No tools available. Please go to the ' . l('Create Tool XML', 'node/add/webform') .
        ' page to create some tools.'),
    ];
    return $form;
  }

  $form['xml_file'] = [
    '#type' => 'select',
    '#title' => t('Select a tool (XML file)'),
    '#options' => $all_xml_files,
  ];

  $form['planemo_command'] = [
    '#type' => 'select',
    '#title' => t('Planemo command'),
    '#options' => [
      'planemo lint' => 'planemo lint (check requirements availability in Conda channels)',
      'planemo conda_install' => 'planemo conda_install (install requirements with conda)',
      'planemo conda_env' => 'planemo conda_env (interactively explore installed tool)',
      'planemo test' => 'planemo test (test tool)',
    ],
  ];

  $form['submit'] = [
    '#type' => 'submit',
    '#value' => t('Run command'),
    '#submit' => ['planemo_test_form_form_submit'],
  ];

  $list = [];
  $list['type'] = 'ul';
  $list['title'] = 'Open the following URLs in a new tab to check results';
  $list['items'] = [];

  $list['items'][] = l('command stdout and stderr', 'sites/default/files/planemo.log.txt');
  $list['items'][] = l('tool_test_output.html', 'sites/default/files/galaxy_tool_repository/tool_test_output.html');
  $list['items'][] = l('tool_test_output.json', 'sites/default/files/galaxy_tool_repository/tool_test_output.json');


  $form['instruction'] = [
    '#markup' => theme('item_list', $list),
  ];

  return $form;
}


function planemo_test_form_form_submit($form, &$form_state) {
  $xml_file = $form_state['values']['xml_file'];
  if ($form_state['values']['planemo_command'] == 'planemo conda_env') {
    $planemo_command = '. <(planemo conda_env ' . $xml_file . ')';
  }
  else {
    $planemo_command = $form_state['values']['planemo_command'] . ' ' . $xml_file;
  }

  $command = 'sudo su && cd /var/www/html/sites/default/files/galaxy_tool_repository && sudo -u root ' .
    $planemo_command . ' >/var/www/html/sites/default/files/planemo.log.txt 2>&1 &';
  passthru($command, $return_var);

}
