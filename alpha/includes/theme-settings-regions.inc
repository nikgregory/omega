<?php

function alpha_theme_settings_regions(&$form, &$form_state) {
  $theme = $form_state['build_info']['args'][0];
  $zones = $form_state['#zones'];
  $regions = $form_state['#regions'];
  $containers = $form_state['#containers'];
  $options = alpha_zone_options($theme);
  $columns = $spacing = alpha_column_options(max(array_keys($containers)));  
  $sections = alpha_sections();
  
  unset($columns[0]);
  array_pop($spacing);
  
  $form['alpha_settings']['regions'] = array(
    '#type' => 'fieldset',
    '#title' => t('Region configuration'),
    '#weight' => -8,
  ); 
  
  $form['alpha_settings']['regions']['unassigned'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unassigned zones'),
    '#description' => t('There are no unassigned zones.'),
    '#weight' => 100,
    '#attributes' => array(
      'class' => array('alpha-unassigned'),
    ),
  );
  
  $form['alpha_settings']['regions']['unassigned']['unassigned'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unassigned regions'),
    '#description' => t('There are no unassigned regions.'),
    '#weight' => 100,
    '#attributes' => array(
      'class' => array('alpha-unassigned'),
    ),
  );
  
  foreach ($sections as $key => $section) {
    $form['alpha_settings']['regions']['section_' . $key] = array(
      '#type' => 'fieldset',
      '#title' => $section . ' ' . t('Section'),
      '#description' => t('This section is empty.'),
    );
  }
  
  foreach ($zones as $key => $zone) {
    $section = isset($sections[$zone['section']]) ? 'section_' . $zone['section'] : 'unassigned';

    unset($form['alpha_settings']['regions'][$section]['#description']);
    
    $form['alpha_settings']['regions'][$section]['zone_' . $key] = array(
      '#type' => 'fieldset',
      '#title' => $zone['name'] . ' ' . t('Zone'),
      '#description' => t('This zone is empty.'),
      '#weight' => $zone['weight'],
    );
  }
  
  foreach($regions as $region => $item) {
    $zone = isset($zones[$item['zone']]) ? 'zone_' . $item['zone'] : 'unassigned';
    $section = isset($zones[$item['zone']]) && isset($sections[$zones[$item['zone']]['section']]) ? 'section_' . $zones[$item['zone']]['section'] : 'unassigned';
    
    unset($form['alpha_settings']['regions'][$section][$zone]['#description']);

    $form['alpha_settings']['regions'][$section][$zone][$region] = array(
      '#type' => 'fieldset',
      '#title' => $item['name'],
      '#weight' => $item['weight'],
      '#attributes' => array(
        'class' => array('alpha-inline'),
      ),
    );
           
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_zone'] = array(
      '#type' => 'select',
      '#title' => t('Zone'),
      '#default_value' => !empty($item['zone']) ? $item['zone'] : array('_none'),
      '#element_validate' => array('alpha_theme_settings_validate_not_empty'),
      '#options' => array('_none' => '- None -') + $options,
    );
    
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_prefix'] = array(
      '#type' => 'select',
      '#title' => t('Prefix'),
      '#default_value' => $item['prefix'],
      '#options' => $spacing,
    );
    
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_columns'] = array(
      '#type' => 'select',
      '#title' => t('Width'),
      '#default_value' => $item['columns'],
      '#options' => $columns,
    );
    
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_suffix'] = array(
      '#type' => 'select',
      '#title' => t('Suffix'),
      '#default_value' => $item['suffix'],
      '#options' => $spacing,
    );
    
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_weight'] = array(
      '#type' => 'weight',
      '#delta' => 50,
      '#title' => t('Weight'),
      '#default_value' => $item['weight'],
    );
    
    $form['alpha_settings']['regions'][$section][$zone][$region]['alpha_region_' . $region . '_css'] = array(
      '#type' => 'textfield',
      '#title' => t('Additional region classes'),
      '#size' => 50,
      '#default_value' => $item['css'],
    );
  }
}
