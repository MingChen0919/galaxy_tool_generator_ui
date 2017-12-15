<?php

function galaxy_tool_xml_all_form($form, &$form_state) {

  // Build the sortable table header.
  $header = [
    'galaxy_tool_xml_name' => [
      'data' => t('Too Name'),
      'field' => 'n.galaxy_tool_xml_name',
    ],
    'tool_synopsis' => ['data' => t('Synopsis'), 'field' => 'n.tool_synopsis'],
    'tool_description' => [
      'data' => t('Description'),
      'field' => 'n.tool_description',
    ],
    'tool_categories' => [
      'data' => t('Categories'),
      'field' => 'n.tool_categories',
    ],
    'author' => t('Author'),
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


  // restrict the query to galaxy_tool_xml node.
  $query->condition('n.galaxy_tool_xml_node', 1);
  $nids = $query
    ->fields('n', ['nid'])
    ->limit(50)
    ->orderByHeader($header)
    ->addTag('node_access')
    ->execute()
    ->fetchCol();
  $nodes = node_load_multiple($nids);

  // Prepare the list of nodes.
  $languages = language_list();
  $destination = drupal_get_destination();
  $options = [];

  foreach ($nodes as $node) {
    $res = db_select('node', 'n')
      ->fields('n')
      ->condition('nid', $node->nid)
      ->execute()
      ->fetchAssoc();
    $uri = entity_uri('node', $node);
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
      'tool_synopsis' => $res['tool_synopsis'],
      'tool_description' => $res['tool_description'],
      'tool_categories' => $res['tool_categories'],
      'author' => theme('username', ['account' => $node]),
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

  // Only use a tableselect when the current user is able to perform any
  // operations.
  $form['nodes'] = [
    '#type' => 'tableselect',
    '#header' => $header,
    '#options' => $options,
    '#empty' => t('No content available.'),
  ];


  $form['pager'] = ['#markup' => theme('pager')];
  return $form;
}