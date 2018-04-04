<?php

/**
 *
 * function get_tool_repositories() {
 * // create galaxy_tools directory if it doesn't exist.
 * $galaxy_tools_directory = 'public://galaxy_tools/';
 * file_prepare_directory($galaxy_tools_directory, FILE_CREATE_DIRECTORY);
 * // get all galaxy tools names by scanning the galaxy_tools directory.
 * $directories_in_galaxy_tools = scandir($galaxy_tools_directory);
 * // remove '.' an '..' directories.
 * $all_galaxy_tools = [];
 * foreach ($directories_in_galaxy_tools as $directory) {
 * if (!in_array($directory, ['.', '..'])) {
 * $all_galaxy_tools[] = $directory;
 * }
 * }
 * // convert $all_galaxy_tools to a non-associative array.
 * $all_galaxy_tools = array_values($all_galaxy_tools);
 * return $all_galaxy_tools;
 * }
 */

/**
 * Return an array to build tool template components.
 */
function get_tool_template_components() {
  $tool_template_components = [
    [
      'cid' => 1,
      'pid' => 0,
      'form_key' => 'tool_template',
      'name' => 'tool_template',
      'type' => 'tool',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'tool',
        'attributes' =>
          [
            'id' => 'tool_template',
            'name' => 'tool name',
            'version' => '1.0.0',
            'hidden' => NULL,
            'display_interface' => NULL,
            'tool_type' => NULL,
            'workflow_compatible' => NULL,
            'URL_method' => NULL,
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 0,
    ],
    [
      'cid' => 2,
      'pid' => 1,
      'form_key' => 'requirements',
      'name' => 'requirements',
      'type' => 'tool_requirements',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirements',
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 1,
    ],
    [
      'cid' => 3,
      'pid' => 2,
      'form_key' => 'pandoc',
      'name' => 'pandoc',
      'type' => 'tool_requirements_requirement',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirement',
        'attributes' =>
          [
            'type' => 'package',
            'version' => '1.15.0.6-0',
            'XML_VALUE' => 'pandoc',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 2,
    ],
    [
      'cid' => 4,
      'pid' => 2,
      'form_key' => 'r_getopt',
      'name' => 'r_getopt',
      'type' => 'tool_requirements_requirement',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirement',
        'attributes' =>
          [
            'type' => 'package',
            'version' => '1.20.0',
            'XML_VALUE' => 'r-getopt',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 3,
    ],
    [
      'cid' => 5,
      'pid' => 2,
      'form_key' => 'r_rmarkdown',
      'name' => 'r_rmarkdown',
      'type' => 'tool_requirements_requirement',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirement',
        'attributes' =>
          [
            'type' => 'package',
            'version' => '1.6',
            'XML_VALUE' => 'r-rmarkdown',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 4,
    ],
    [
      'cid' => 6,
      'pid' => 2,
      'form_key' => 'r-htmltools',
      'name' => 'r-htmltools',
      'type' => 'tool_requirements_requirement',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirement',
        'attributes' =>
          [
            'type' => 'package',
            'version' => '0.3.5',
            'XML_VALUE' => 'r-htmltools',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 5,
    ],
    [
      'cid' => 7,
      'pid' => 2,
      'form_key' => 'r-dplyr',
      'name' => 'r-dplyr',
      'type' => 'tool_requirements_requirement',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'requirement',
        'attributes' =>
          [
            'type' => 'package',
            'version' => '0.5.0',
            'XML_VALUE' => 'r-dplyr',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 6,
    ],
    [
      'cid' => 8,
      'pid' => 1,
      'form_key' => 'description',
      'name' => 'description',
      'type' => 'tool_description',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'description',
        'attributes' =>
          [
            'XML_VALUE' => 'some descriptions about the tool.',
          ],
        'private' => 0,


      ]),
      'required' => 0,
      'weight' => 2,
    ],
    [
      'cid' => 9,
      'pid' => 1,
      'form_key' => 'stdio',
      'name' => 'stdio',
      'type' => 'tool_stdio',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'stdio',
        'attributes' => '',
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 3,
    ],
    [
      'cid' => 10,
      'pid' => 9,
      'form_key' => 'regex',
      'name' => 'regex',
      'type' => 'tool_stdio_regex',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'regex',
        'attributes' =>
          [
            'source' => 'stderr',
            'match' => 'XXX',
            'level' => 'warning',
            'description' => 'Check the warnings_and_errors.txt file for more details.',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 9,
    ],
    [
      'cid' => 11,
      'pid' => 1,
      'form_key' => 'command',
      'name' => 'command',
      'type' => 'tool_command',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'command',
        'attributes' => [
          //  keep the space at the first line.
          'XML_VALUE' => '
                    Rscript \'${__tool_directory__}/tool_template_render.R\'
                        -e $echo
                        -r $report
                        -d $report.files_path
                        -s $sink_message
                        -t \'${__tool_directory__}/tool_template.Rmd\'
                    ',
        ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 4,
    ],
    [
      'cid' => 12,
      'pid' => 1,
      'form_key' => 'inputs',
      'name' => 'inputs',
      'type' => 'tool_inputs',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'inputs',
        'attributes' =>
          [
            'check_values' => NULL,
            'method' => NULL,
            'nginx_upload' => NULL,
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 5,
    ],
    [
      'cid' => 13,
      'pid' => 12,
      'form_key' => 'input_boolean',
      'name' => 'input_boolean',
      'type' => 'tool_inputs_param_type_boolean',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'param',
        'attributes' =>
          [
            'type' => 'boolean',
            'name' => 'echo',
            'label' => 'Display analysis code in report?',
            'optional' => 'False',
            'refresh_on_change' => NULL,
            'checked' => 'False',
            'truevalue' => 'TRUE',
            'falsevalue' => 'FALSE',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 7,
    ],
    [
      'cid' => 14,
      'pid' => 1,
      'form_key' => 'outputs',
      'name' => 'outputs',
      'type' => 'tool_outputs',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'outputs',
        'attributes' => [],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 6,
    ],
    [
      'cid' => 15,
      'pid' => 14,
      'form_key' => 'output_1',
      'name' => 'output_1',
      'type' => 'tool_outputs_data',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'data',
        'attributes' =>
          [
            'name' => 'report',
            'auto_format' => NULL,
            'format' => 'html',
            'label' => 'tool name report',
            'hidden' => 'false',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 8,
    ],
    [
      'cid' => 16,
      'pid' => 14,
      'form_key' => 'output_2',
      'name' => 'output_2',
      'type' => 'tool_outputs_data',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'data',
        'attributes' =>
          [
            'name' => 'sink_message',
            'auto_format' => NULL,
            'format' => 'txt',
            'label' => 'Warnings and Errors',
            'from_work_dir' => 'warnings_and_errors.txt',
            'hidden' => 'false',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 9,
    ],
    [
      'cid' => 17,
      'pid' => 1,
      'form_key' => 'help',
      'name' => 'help',
      'type' => 'tool_help',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'help',
        'attributes' =>
          [
            'XML_VALUE' => 'some help text',
          ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 8,
    ],
    [
      'cid' => 18,
      'pid' => 1,
      'form_key' => 'citations',
      'name' => 'citations',
      'type' => 'tool_citations',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'citations',
        'private' => 0,
        'attributes' => '',
      ]),
      'required' => 0,
      'weight' => 9,
    ],
    [
      'cid' => 19,
      'pid' => 18,
      'form_key' => 'citation_1',
      'name' => 'citation_1',
      'type' => 'tool_citations_citation',
      'value' => '',
      'extra' => serialize([
        'galaxy_tool_xml_tag' => 'citation',
        'attributes' => [
          'type' => 'bibtex',
          //  keep the space at the first line.
          'XML_VALUE' => '
                    @article{allaire2016rmarkdown,
                        title={rmarkdown: Dynamic Documents for R, 2016},
                        author={Allaire, J and Cheng, Joe and Xie, Yihui and McPherson, Jonathan and Chang, Winston and Allen, Jeff
                        and Wickham, Hadley and Atkins, Aron and Hyndman, Rob},
                        journal={R package version 0.9},
                        volume={6},
                        year={2016}
                    }',
        ],
        'private' => 0,
      ]),
      'required' => 0,
      'weight' => 9,
    ],

  ];

  return $tool_template_components;
}


/*
 * This function converts a Galaxy tool XML file back to an array of webform components.
 */
function convert_xml_to_webform_components($xml_file_path) {
  $cid = 1;


  // add id attribute to node 'tool', the id is in the format of element tag + cid.
  $xml_file = file_get_contents($xml_file_path);
  $dom = new DOMDocument();
  //  $dom->preserveWhiteSpace = FALSE;
  $dom->loadXML($xml_file, LIBXML_NOCDATA);
  $dom->getElementsByTagName('tool')
    ->item(0)
    ->setAttribute('id', 'tool_' . $cid);
  // get all nodes.
  $node_list = $dom->getElementsByTagName('*');

  // set tool as the root component.
  $tool_node = $dom->getElementsByTagName('tool')->item(0);
  $attributes = [];
  foreach ($tool_node->attributes as $attr) {
    //    if ($attr->name != 'id') {
    //      $attributes[$attr->name] = $attr->value;
    //    }
    $attributes[$attr->name] = $attr->value;
  };
  $webform_components[] = [
    'cid' => $cid,
    'pid' => 0,
    'form_key' => 'tool_template',
    'name' => 'tool_template',
    'type' => 'tool',
    'value' => '',
    'extra' => serialize([
      'galaxy_tool_xml_tag' => 'tool',
      'attributes' => $attributes,
      'private' => 0,
    ]),
    'required' => 0,
  ];

  // loop through all nodes. If the node has parent node, use the parent cid as the pid of the current node.
  // also, add id attribute to the current node.
  foreach ($node_list as $key => $node) {
    if (!in_array($node->nodeName, [
      '#text',
      '#comment',
      '#document',
      'tool',
    ])) {
      ++$cid;
      if ($node->parentNode) {
        // get parent node cid and use it as the node pid.
        $matches = [];
        preg_match('/\d+$/', $node->parentNode->getAttribute('id'), $matches);
        $pcid = $matches[0];
        // set id attribute for the current node.
        $dom->getElementsByTagName('*')->item($key)->setAttribute('id', $cid);
        // get node path.
        $node_path = $node->getNodePath();
        $node_path = preg_replace('/\[\d+\]/', '', $node_path);
        $node_path = preg_replace('/\//', '_', $node_path);
        $node_path = preg_replace('/^_/', '', $node_path);
        // build component.
        $attributes = [];
        foreach ($node->attributes as $attr) {
          if ($attr->name != 'id') {
            $attributes[$attr->name] = $attr->value;
          }
        };

        // tool->inputs->param is special webform component, we need to add the type to complete the path.
        if ($node_path == 'tool_inputs_param') {
          $node_path = $node_path . '_type_' . $attributes['type'];
        }

        // check if the current node has value. We can't use DOMNode->nodeValue
        // since it will return all values from its child nodes.
        $child_nodes = $node->childNodes;
        if (isset($child_nodes[0])) {
          if (isset($child_nodes[0]->nodeValue)) {
            $attributes['XML_VALUE'] = $child_nodes[0]->nodeValue;
          }

        }
        $webform_components[] = [
          'cid' => $cid,
          'pid' => $pcid,
          'form_key' => $node->nodeName . '_' . $cid,
          'name' => $node->nodeName,
          'type' => $node_path,
          'value' => '',
          'extra' => serialize([
            'galaxy_tool_xml_tag' => $node->nodeName,
            'attributes' => $attributes,
            'private' => 0,
          ]),
          'required' => 0,
          'weight' => $cid,
        ];
      }
    }
  }

  return $webform_components;
}


/**
 * @param $webform_node a webform node.
 */
function get_tool_command_string_from_sh($webform_node) {
  $xml_basename = preg_replace('/\.xml$/', '', $webform_node->title);
  $tool_command_sh = 'public://galaxy_tool_repository/' . $xml_basename . '.sh';
  if (!file_exists($tool_command_sh)) {
    return;
  }
  $tool_command_string = file_get_contents($tool_command_sh);
  foreach ($webform_node->webform['components'] as $key => $value) {
    if ($value['type'] == 'tool_command') {
      $webform_node->webform['components'][$key]['extra']['attributes']['XML_VALUE'] = $tool_command_string;
    }
  }
  $extra = serialize([
    'galaxy_tool_xml_tag' => 'command',
    'attributes' => [
      'XML_VALUE' => $tool_command_string,
    ],
    'private' => 0,
  ]);
  db_update('webform_component')
    ->fields(['extra' => $extra])
    ->condition('nid', $webform_node->nid)
    ->condition('type', 'tool_command')
    ->execute();
}

/**
 * @param $xml the name of an XML file in the galaxy tool repository (e.g.,
 *   'fastqc.xml').
 * @param $tool_type The tool repository type. Valid types include: 'rmarkdown_report' and 'rmarkdown_website'
 */
function get_rmarkdown_non_xml_templates($xml, $tool_type) {

  $galaxy_tool_basename = preg_replace('/\.xml$/', '', $xml);
  $galaxy_tool_repository = 'public://galaxy_tool_repository/';
  file_prepare_directory($galaxy_tool_repository, FILE_CREATE_DIRECTORY);

  file_put_contents($galaxy_tool_repository . '/helper.R', file_get_contents(RMARKDOWN_HELPER_R));
  if ($tool_type == 'rmarkdown_report') {
    file_put_contents($galaxy_tool_repository . $galaxy_tool_basename . '_render.R', file_get_contents(RMARKDOWN_REPORT_RENDER));
    file_put_contents($galaxy_tool_repository . $galaxy_tool_basename . '.Rmd', file_get_contents(RMARKDOWN_REPORT_RMD));
  }
  else {
    file_put_contents($galaxy_tool_repository . $galaxy_tool_basename . '_render.R', file_get_contents(RMARKDOWN_WEBSITE_RENDER));
    file_put_contents($galaxy_tool_repository . $galaxy_tool_basename . '_site.yml', file_get_contents(RMARKDOWN_WEBSITE_YML));
    file_put_contents($galaxy_tool_repository . $galaxy_tool_basename . '_index.Rmd', file_get_contents(RMARKDOWN_WEBSITE_INDEX_RMD));
  }
}


/**
 * @param $xml the name of an xml file in 'public://galaxy_tool_repository/'
 */
function delete_rmarkdown_non_xml_templates($xml) {
  $galaxy_tool_basename = preg_replace('/\.xml$/', '', $xml);
  $galaxy_tool_repository = 'public://galaxy_tool_repository/';

  $render = $galaxy_tool_repository . $galaxy_tool_basename . '_render.R';
  $rmd = $galaxy_tool_repository . $galaxy_tool_basename . '.Rmd';
  $yml = $galaxy_tool_repository . $galaxy_tool_basename . '_site.yml';
  $index_rmd = $galaxy_tool_repository . $galaxy_tool_basename . '_index.Rmd';

  if (file_exists($render)) {
    file_unmanaged_delete($render);
  }

  if (file_exists($rmd)) {
    file_unmanaged_delete($rmd);
  }

  if (file_exists($yml)) {
    file_unmanaged_delete($yml);
  }

  if (file_exists($index_rmd)) {
    file_unmanaged_delete($index_rmd);
  }
}