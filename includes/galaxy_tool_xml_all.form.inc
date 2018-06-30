<?php

function galaxy_tool_xml_all_form($form, &$form_state) {

  // Build the sortable table header.
  $header = [
    'galaxy_tool_xml_name' => [
      'data' => t('Tool Name'),
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
    '#title' => t('Tool XMLs'),
    '#description' => t('Select one or more XMLs and push them into the 
        <span style="color: #FF5666"><code>galaxy_tool_repository</code></span> directory.'),
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
      '#value' => 'Update XMLs in galaxy_tool_directory folder',
      '#submit' => ['register_selected_xmls'],
    ],
    //    'register_all_xmls' => [
    //      '#type' => 'submit',
    //      '#value' => 'Register All XMLs',
    //      '#submit' => ['register_all_xmls'],
    //    ],
  ];


  $galaxy_tool_repository = 'public://galaxy_tool_repository/';
  file_prepare_directory($galaxy_tool_repository, FILE_CREATE_DIRECTORY);
  $all_files = scandir($galaxy_tool_repository);
  $all_xml_files = [];
  $all_xml_files['type'] = 'ul';
  $all_xml_files['title'] = '';
  $all_xml_files['items'] = [];
  foreach ($all_files as $file) {
    if (preg_match('/\.xml$/', $file)) {
      $all_xml_files['items'][] = l($file, 'sites/default/files/galaxy_tool_repository/' . $file);
    }
  }
  if (count($all_xml_files['items']) == 0) {
    $markup = 'No XMLs in <span style="color: #FF5666"><code>galaxy_tool_repository</code></span>';
  }
  else {
    $markup = theme('item_list', $all_xml_files);
  }
  $form['selected_xmls'] = [
    '#type' => 'fieldset',
    '#title' => t('XMLs in <code>galaxy_tool_repository</code>'),
    '#description' => t('Only XMLs in <span style="color: #FF5666">
        <code>galaxy_tool_repository</code></span> can be published to the Galaxy Tool Shed (or Test Tool Shed).')
  ];
  $form['selected_xmls']['xml_list'] = [
    '#markup' => $markup,
  ];


  drupal_add_js(drupal_get_path('module', 'galaxy_tool_generator_ui') . '/js/build_repository_confirm.js');
  drupal_add_js(drupal_get_path('module', 'galaxy_tool_generator_ui') . '/js/remove_xml_confirm.js');

  return $form;
}

/**
 * @param $form
 * @param $form_state
 * submit callback to add xmls to build up repository
 */
function register_selected_xmls($form, &$form_state) {

  // remove all XMLs before copy any selected XMLs into the galaxy_tool_repository directory
  $galaxy_tool_repository = 'public://galaxy_tool_repository/';
  file_prepare_directory($galaxy_tool_repository, FILE_CREATE_DIRECTORY);
  $all_files = scandir($galaxy_tool_repository);
  foreach ($all_files as $file) {
    if (preg_match('/\.xml$/', $file)) {
      file_unmanaged_delete($galaxy_tool_repository . $file);
    }
  }

  // copy selected XML files into 'public://galaxy_tool_repository/'.
  $nids = array_filter($form_state['values']['unregistered_xmls']);
  foreach ($nids as $nid) {
    $node = db_select('node', 'n')
      ->fields('n')
      ->condition('nid', $nid)
      ->execute()
      ->fetchAssoc();
    $fid = $node['tool_xml_fid'];
    file_unmanaged_copy(file_load($fid)->uri, $galaxy_tool_repository, FILE_EXISTS_REPLACE);
  }

  $form_state['rebuild'] = TRUE;
}
