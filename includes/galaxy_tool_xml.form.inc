<?php

/**
 * form builder for galaxy tool xml.
 */
function galaxy_tool_xml_form($form, &$form_state) {

  $node = node_load(1);
  $webform_components = $node->webform['components'];
  $markup = build_galaxy_tool_xml($webform_components);
  dpm($markup);
  $form['galaxy_tool_xml'] = [
    '#type' => 'markup',
    '#markup' => $markup,
    '#theme' => NULL,
    '#theme_wrappers' => NULL,
  ];

  return $form;
}