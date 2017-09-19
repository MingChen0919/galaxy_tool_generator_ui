<?php

/**
 * form builder for galaxy tool xml.
 */
function galaxy_tool_xml_form($form, &$form_state) {
  $markup = 'test';
  $form['galaxy_tool_xml'] = [
    '#type' => 'markup',
    '#markup' => $markup,
  ];

  return $form;
}