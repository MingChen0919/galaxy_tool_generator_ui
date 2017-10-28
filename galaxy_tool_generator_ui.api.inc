<?php

/**
 *
 */
function get_galaxy_tools()
{
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
function get_tool_template_components()
{
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
                'private' => 0
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
                'private' => 0
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
                        'version' => '1.3',
                        'XML_VALUE' => 'r-rmarkdown',
                    ],
                'private' => 0
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
                'private' => 0
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
                'private' => 0
            ]),
            'required' => 0,
            'weight' => 2,
        ],
        [
            'cid' => 9,
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
                        -t \'${__tool_directory__}/tool_template.Rmd
                    ',
                ],
                'private' => 0,
            ]),
            'required' => 0,
            'weight' => 3,
        ],
    ];

    return $tool_template_components;
}
