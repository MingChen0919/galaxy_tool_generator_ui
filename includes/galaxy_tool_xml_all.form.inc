<?php

function galaxy_tool_xml_all_form($form, &$form_state) {

  // Build the sortable table header.
  $header = [
    'galaxy_tool_xml_name' => [
      'data' => t('Too Name'),
      'field' => 'n.galaxy_tool_xml_name',
    ],
    'tool_description' => [
      'data' => t('Description'),
      'field' => 'n.tool_description',
    ],
    'changed' => [
      'data' => t('Updated'),
      'field' => 'n.changed',
      'sort' => 'desc',
    ],
  ];
  $header['operations'] = ['data' => t('Operations')];

  $query = db_select('node', 'n')->extend('PagerDefault')->extend('TableSort');
  $query->addTag('node_admin_filter');
  //  node_build_filter_query($query);


  $nids = $query
    ->fields('n', ['nid'])
    ->limit(50)
    ->orderByHeader($header)
    ->addTag('node_access')
    ->execute()
    ->fetchCol();
  $nodes = node_load_multiple($nids);

  // Prepare the list of nodes.
  $destination = drupal_get_destination();
  $options = [];

  foreach ($nodes as $node) {
    $res = db_select('node', 'n')
      ->fields('n')
      ->condition('nid', $node->nid)
      ->execute()
      ->fetchAssoc();
    $uri = entity_uri('node', $node);
    // it is important to use nid as the options keys, because we will need the nid
    // to track which XMLs are selected when we build a repository.
    $options[$node->nid] = [
      'galaxy_tool_xml_name' => [
        'data' => [
          '#type' => 'link',
          '#title' => $node->title,
          '#href' => $uri['path'],
          '#options' => $uri['options'],
          '#suffix' => ' ' . theme('mark', ['type' => node_mark($node->nid, $node->changed)]),
        ],
      ],
      'tool_description' => $res['tool_description'],
      'changed' => format_date($node->changed, 'short'),
    ];
    // Build a list of all the accessible operations for the current node.
    $operations = [];
    $operations['view'] = [
      'title' => t('view'),
      'href' => 'node/' . $node->nid . '/webform-results',
      'query' => $destination,
    ];
    if (node_access('update', $node)) {
      $operations['edit'] = [
        'title' => t('edit'),
        'href' => 'node/' . $node->nid . '/webform',
        'query' => $destination,
      ];
    }
    if (node_access('delete', $node)) {
      $operations['delete'] = [
        'title' => t('delete'),
        'href' => 'node/' . $node->nid . '/delete',
        'query' => $destination,
      ];
    }
    $options[$node->nid]['operations'] = [];
    if (count($operations) > 1) {
      // Render an unordered list of operations links.
      $options[$node->nid]['operations'] = [
        'data' => [
          '#theme' => 'links__node_operations',
          '#links' => $operations,
          '#attributes' => ['class' => ['links', 'inline']],
        ],
      ];
    }
    elseif (!empty($operations)) {
      // Render the first and only operation as a link.
      $link = reset($operations);
      $options[$node->nid]['operations'] = [
        'data' => [
          '#type' => 'link',
          '#title' => $link['title'],
          '#href' => $link['href'],
          '#options' => ['query' => $link['query']],
        ],
      ];
    }
  }

  $registered_xmls = variable_get('registered_xml_nids', []);
  $registered_xmls_options = [];
  foreach ($registered_xmls as $xml) {
    $registered_xmls_options[$xml] = $options[$xml];
    if ($registered_xmls_options[$xml]['operations']['data']['#links']['delete']) {
      unset($registered_xmls_options[$xml]['operations']['data']['#links']['delete']);
    }
  }

  // table to display all unregistered XMLs
  $unregistered_xmls_options = array_diff_key($options, $registered_xmls_options);
  $form['unregistered_xmls'] = [
    '#type' => 'fieldset',
    '#title' => t('Unregistered XMLs'),
    '#description' => t('<span style="color: #42D9C8">Unregistered XMLs</span> can 
        be added to the <span style="color: #19B5FE">Registered XMLs</span> table below
        to build an galaxy tool Repository.'),
    '#collapsible' => TRUE,
  ];
  $form['unregistered_xmls']['unregistered_xmls'] = [
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $unregistered_xmls_options,
    '#empty' => t('No content available.'),
  ];
  $form['unregistered_xmls']['pager'] = ['#markup' => theme('pager')];
  $form['unregistered_xmls']['unregister_actions'] = [
    '#type' => 'action',
    'register_xmls' => [
      '#type' => 'submit',
      '#value' => 'Register XMLs',
      '#submit' => ['register_xmls'],
    ],
    'register_all_xmls' => [
      '#type' => 'submit',
      '#value' => 'Register All XMLs',
      '#submit' => ['register_all_xmls'],
    ],
  ];


  // table to display all registered XMLs
  $form['registered_xmls'] = [
    '#type' => 'fieldset',
    '#title' => t('Registered XMLs'),
    '#description' => t('<span style="color: #19B5FE">Registered XMLs</span> are XMLs that 
        will be included into a Galaxy tool repository. Every time the 
        <span style="color: #19B5FE">registered XMLs</span> are updated, 
        the <b>Build Repository</b> button needs to be clicked to include the updates.'),
    '#collapsible' => TRUE,
  ];
  $form['registered_xmls']['registered_xmls'] = [
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $registered_xmls_options,
    '#empty' => t('No content available.'),
  ];
  $form['registered_xmls']['register_actions'] = [
    '#type' => 'action',
    'remove_from_repository' => [
      '#type' => 'submit',
      '#value' => 'Unregister XMLs',
      '#submit' => ['unregister_xmls'],
    ],
    'empty_repository' => [
      '#type' => 'submit',
      '#value' => 'Unregister All XMLs',
      '#submit' => ['unregister_all_xmls'],
    ],
    'build_repository' => [
      '#type' => 'submit',
      '#value' => 'Build Repository',
      '#submit' => ['build_galaxy_tool_repository'],
    ],
  ];


  // markup to display structure of tool repository directory
  exec('tree -F /var/www/html/sites/default/files/galaxy_tool_repository', $output);
  $output = preg_replace('/`/', '|', $output);
  $form['tool_repository_structure'] = [
    '#type' => 'fieldset',
    '#title' => 'Tool Repository Structure',
    '#collapsible' => TRUE,
  ];
  $output[0] = 'Repository Directory: galaxy_tool_repository';
  $repository_content_markup = implode('<br/>', $output);
  $form['tool_repository_structure']['content'] = [
    '#markup' => $repository_content_markup,
  ];
  // save the markup to a variable


  // store all xmls options
  $form_state['storage']['all_xmls'] = $options;
  return $form;
}

/**
 * @param $form
 * @param $form_state
 * submit callback to add xmls to build up repository
 */
function register_xmls($form, &$form_state) {
  // add selected XMLs to registered_xml_nids array.
  $registered_xml_nids = variable_get('registered_xml_nids', []);
  $registered_xmls = array_filter($form_state['values']['unregistered_xmls']);
  $combined_xmls = array_unique(array_merge($registered_xml_nids, $registered_xmls));
  // set array keys equal to array values
  $combined_xmls = drupal_map_assoc(array_values($combined_xmls));
  variable_set('registered_xml_nids', $combined_xmls);
}

/**
 * @param $form
 * @param $form_state
 * submit callback to register all XMLs
 */
function register_all_xmls($form, &$form_state) {
  variable_set('registered_xml_nids', array_keys($form_state['storage']['all_xmls']));
}

/**
 * @param $form
 * @param $form_state
 * submit callback to unregister selected xmls
 */
function unregister_xmls($form, &$form_state) {
  $registered_xml_nids = drupal_map_assoc(variable_get('registered_xml_nids', []));
  $registered_xmls = array_filter($form_state['values']['registered_xmls']);
  foreach ($registered_xmls as $xml) {
    unset($registered_xml_nids[$xml]);
  }
  variable_set('registered_xml_nids', $registered_xml_nids);
}

/**
 * @param $form
 * @param $form_state
 * submit callback to remove all selected xml from repository.
 */
function unregister_all_xmls($form, &$form_state) {
  variable_set('registered_xml_nids', []);
}


function build_galaxy_tool_repository($form, &$form_state) {
  // copy selected XML files into 'public://galaxy_tool_repository/'.
  $nids = array_keys($form_state['values']['registered_xmls']);
  copy_registered_xmls_to_repository($nids);
}

/**
 * @param $nids array an array of nids of galaxy webform nodes.
 * copy registered XMLs to tool repository directory.
 * Every time we click the build repository button, the previously copied files
 * get removed. And we update the variable copied_xml_fids to store the new copied file fids.
 */
function copy_registered_xmls_to_repository ($nids) {
  // prepare the galaxy tool repository directory. Copy XML files into this directory,
  // and add any other files into this directory. When all files are ready, this directory
  // will be used as a galaxy tool repository and published to test tool shed or tool shed.
  $galaxy_tool_repository = 'public://galaxy_tool_repository/';
  file_prepare_directory($galaxy_tool_repository, FILE_CREATE_DIRECTORY);

  // delete previously copied XMLs
  foreach (variable_get('copied_xml_fids', []) as $copied_xml_fid) {
    file_delete(file_load($copied_xml_fid), TRUE);
  }


  // we need to record which files are copied to the tool repository. Every time
  // we click the build repository button, the previously copied files get removed.
  $copied_xml_fids = [];
  foreach ($nids as $nid) {
    $node = db_select('node', 'n')
      ->fields('n')
      ->condition('nid', $nid)
      ->execute()
      ->fetchAssoc();
    $fid = $node['tool_xml_fid'];
    $file = file_copy(file_load($fid), $galaxy_tool_repository, FILE_EXISTS_REPLACE);
    // TODO: save fids of copied files into a variable.
    $copied_xml_fids[] = $file->fid;
  }
  // update variable copied_xml_fids
  variable_set('copied_xml_fids', $copied_xml_fids);


}
