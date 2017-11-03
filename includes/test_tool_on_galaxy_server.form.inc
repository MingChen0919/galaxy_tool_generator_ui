<?php
/**
 * Form handler for test tool on galaxy server page.
 */
function test_tool_on_galaxy_server_form($form, &$form_state)
{
    // first, check if API key and username for test tool shed exists
    $testtoolshed_username = variable_get('testtoolshed_username', '');
    $testtoolshed_api = variable_get('testtoolshed_api', '');
    if ($testtoolshed_username == '' or $testtoolshed_api == '') {
        $form['return_to_account_form'] = [
            '#markup' => t('Username or API key from a Test Tool Shed account is required. ' . l('Please provide this information first.', 'associate_accounts'))
        ];
        return $form;
    }


    $gtrepositories = new GTRepositories($testtoolshed_username, $testtoolshed_api, 'https://testtoolshed.g2.bx.psu.edu/');
    $all_tools = $gtrepositories->index($testtoolshed_username);
    $tools_by_owner_options = [];
    if (is_array($all_tools)) {
        foreach ($all_tools as $tool) {
            $tools_by_owner_options[] = $tool->name;
        }
    } else {
        drupal_set_message(t('No tools available from owner <b>' . $testtoolshed_username . '</b>'), 'warning');
    }
    $tools_by_owner_options = array_merge(['- Select a tool -'], array_values($tools_by_owner_options));

    $form['target_tool'] = [
        '#type' => 'fieldset',
        '#title' => t('Target tool'),
        '#collapsible' => TRUE,
    ];
    $form['target_tool']['tools_by_owner'] = [
        '#type' => 'select',
        '#title' => t('Select a tool'),
        '#options' => drupal_map_assoc($tools_by_owner_options),
        '#ajax' => [
            'callback' => 'tool_info_ajax_callback',
            'wrapper' => 'tool_info_wrapper',
        ]
    ];
    $selected_tool = isset($form_state['values']['tools_by_owner']) ? $form_state['values']['tools_by_owner'] : '';
    $markup = '';
    if ($selected_tool != '' and $selected_tool != '- Select a tool -') {
        // get tool info for the selected tool
        $rows = [];
        $tool_info = $gtrepositories->index($testtoolshed_username, $selected_tool);
        $tool_info = (array)$tool_info[0];
        foreach ($tool_info as $label => $value) {
            // display $value in table when $value is a boolean object
            if ($value == FALSE) {
                $value = 'FALSE';
            }
            // convert array $value to string
            if (is_array($value)) {
                $value = implode(',', $value);
            }
            $rows[] = [$label, $value];
        }
        $markup = theme('table', [
            'header' => ['Label', 'Value'],
            'rows' => $rows,
        ]);
    }
    $form['target_tool']['tool_info'] = [
        '#markup' => $markup,
        '#prefix' => '<div id="tool_info_wrapper">',
        '#suffix' => '</div>',
    ];
    $form['install_tool_on_galaxy'] = [
        '#type' => 'submit',
        '#value' => t('Install tool on Galaxy'),
    ];

    return $form;
}

/**
 * ajax callback to update the tools_info field.
 */
function tool_info_ajax_callback($form, &$form_state)
{
    return $form['target_tool']['tool_info'];
}