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

  $selected_xmls = variable_get('xmls_in_repository', []);
  $selected_xmls_options = [];
  foreach ($selected_xmls as $xml) {
    $selected_xmls_options[$xml] = $options[$xml];
  }

  // Only use a tableselect when the current user is able to perform any
  // operations.
  $form['all_xmls'] = [
    '#type' => 'fieldset',
    '#title' => t('All Tool XMLs'),
  ];
  $form['all_xmls']['xmls'] = [
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No content available.'),
  ];


  $form['all_xmls']['pager'] = ['#markup' => theme('pager')];
  $form['all_xmls']['actions'] = [
    '#type' => 'action',
    'add_to_repository' => [
      '#type' => 'submit',
      '#value' => 'Add to repository',
      '#submit' => ['add_xml_to_repository'],
    ],
  ];

  $form['repository'] = [
    '#type' => 'fieldset',
    '#title' => t('Tool XMLs in repository'),
  ];
  $form['repository']['selected_nodes'] = [
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $selected_xmls_options,
    '#empty' => t('No content available.'),
  ];
  $form['repository']['actions'] = [
    '#type' => 'action',
    'remove_from_repository' => [
      '#type' => 'submit',
      '#value' => 'Remove from repository',
      '#submit' => ['remove_xml_from_repository'],
    ],
    'empty_repository' => [
      '#type' => 'submit',
      '#value' => 'Empty repository',
      '#submit' => ['remove_all_xml_from_repository'],
    ],
  ];


  return $form;
}

/**
 * @param $form
 * @param $form_state
 * submit callback to add xmls to build up repository
 */
function add_xml_to_repository($form, &$form_state) {
  // add selected XMLs to xmls_in_repository array.
  $xmls_in_repository = variable_get('xmls_in_repository', []);
  $selected_xmls = array_filter($form_state['values']['xmls']);
  $combined_xmls = array_unique(array_merge($xmls_in_repository, $selected_xmls));
  // set array keys equal to array values
  $combined_xmls = drupal_map_assoc(array_values($combined_xmls));
  variable_set('xmls_in_repository', $combined_xmls);
}

/**
 * @param $form
 * @param $form_state
 * submit callback to remove xmls from repository
 */
function remove_xml_from_repository($form, &$form_state) {
  $xmls_in_repository = variable_get('xmls_in_repository', []);
  $selected_xmls = array_filter($form_state['values']['selected_nodes']);
  foreach ($selected_xmls as $xml) {
    unset($xmls_in_repository[$xml]);
  }
  variable_set('xmls_in_repository', $xmls_in_repository);
}

/**
 * @param $form
 * @param $form_state
 * submit callback to remove all selected xml from repository.
 */
function remove_all_xml_from_repository($form, &$form_state) {
  variable_set('xmls_in_repository', []);
}