<?php

/**
 *
 */
function get_galaxy_tools() {
  // create galaxy_tools directory if it doesn't exist.
  $galaxy_tools_directory = 'public://galaxy_tools/';
  file_prepare_directory($galaxy_tools_directory, FILE_CREATE_DIRECTORY);
  // get all galaxy tools names by scanning the galaxy_tools directory.
  $directories_in_galaxy_tools = scandir($galaxy_tools_directory);
  // remove '.' an '..' directories.
  $all_galaxy_tools = [];
  foreach ($directories_in_galaxy_tools as $directory) {
    if (!in_array($directory, ['.', '..'])) {
      $all_galaxy_tools[] = $directory;
    }
  }
  // convert $all_galaxy_tools to a non-associative array.
  $all_galaxy_tools = array_values($all_galaxy_tools);
  return $all_galaxy_tools;
}

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
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:4:"tool";s:10:"attributes";a:8:{s:2:"id";s:13:"tool_template";s:4:"name";s:9:"tool name";s:7:"version";s:5:"1.0.0";s:6:"hidden";N;s:17:"display_interface";N;s:9:"tool_type";N;s:19:"workflow_compatible";N;s:10:"URL_method";N;}s:7:"private";i:0;}',
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
            'extra' => 'a:2:{s:19:"galaxy_tool_xml_tag";s:12:"requirements";s:7:"private";i:0;}',
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
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:11:"requirement";s:10:"attributes";a:3:{s:4:"type";s:7:"package";s:7:"version";s:10:"1.15.0.6-0";s:9:"XML_VALUE";s:6:"pandoc";}s:7:"private";i:0;}',
            'required' => 0,
            'weight' => 2,
        ],
        [
            'cid' => 4,
            'pid' => 3,
            'form_key' => 'r_getopt',
            'name' => 'r_getopt',
            'type' => 'tool_requirements_requirement',
            'value' => '',
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:11:"requirement";s:10:"attributes";a:3:{s:4:"type";s:7:"package";s:7:"version";s:6:"1.20.0";s:9:"XML_VALUE";s:8:"r-getopt";}s:7:"private";i:0;}',
            'required' => 0,
            'weight' => 3,
        ],
        [
            'cid' => 5,
            'pid' => 4,
            'form_key' => 'r_rmarkdown',
            'name' => 'r_rmarkdown',
            'type' => 'tool_requirements_requirement',
            'value' => '',
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:11:"requirement";s:10:"attributes";a:3:{s:4:"type";s:7:"package";s:7:"version";s:3:"1.3";s:9:"XML_VALUE";s:11:"r-rmarkdown";}s:7:"private";i:0;}',
            'required' => 0,
            'weight' => 4,
        ],
        [
            'cid' => 6,
            'pid' => 5,
            'form_key' => 'r-htmltools',
            'name' => 'r-htmltools',
            'type' => 'tool_requirements_requirement',
            'value' => '',
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:11:"requirement";s:10:"attributes";a:3:{s:4:"type";s:7:"package";s:7:"version";s:5:"0.3.5";s:9:"XML_VALUE";s:11:"r-htmltools";}s:7:"private";i:0;}',
            'required' => 0,
            'weight' => 5,
        ],
        [
            'cid' => 7,
            'pid' => 6,
            'form_key' => 'r-dplyr',
            'name' => 'r-dplyr',
            'type' => 'tool_requirements_requirement',
            'value' => '',
            'extra' => 'a:3:{s:19:"galaxy_tool_xml_tag";s:11:"requirement";s:10:"attributes";a:3:{s:4:"type";s:7:"package";s:7:"version";s:5:"0.5.0";s:9:"XML_VALUE";s:7:"r-dplyr";}s:7:"private";i:0;}',
            'required' => 0,
            'weight' => 6,
        ],
    ];

    return $tool_template_components;
}
