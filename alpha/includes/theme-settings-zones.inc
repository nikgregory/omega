<?php

/*
 * @todo
 */
function alpha_theme_settings_zones(&$form, &$form_state) {  
  $sections = alpha_sections();
  $zones = $form_state['#zones'];
  $containers = $form_state['#containers'];
  $regions = $form_state['#regions'];
  
  foreach ($regions as $region => $info) {
    if (isset($zones[$info['zone']])) {
      $zones[$info['zone']]['regions'][$region] = $info['name'];
    }
  }
  
  $form['alpha_settings']['zones'] = array(
    '#weight' => -9,
    '#type' => 'fieldset',
    '#title' => t('Zone configuration'),
  );
  
  $form['alpha_settings']['zones']['unassigned'] = array(
    '#type' => 'fieldset',
    '#title' => t('Unassigned zones'),
    '#description' => t('There are no unassigned zones.'),
    '#weight' => 100,
    '#attributes' => array(
      'class' => array('alpha-unassigned'),
    ),
  );
  
  foreach ($sections as $key => $section) {
    $form['alpha_settings']['zones']['section_' . $key] = array(
      '#type' => 'fieldset',
      '#title' => $section . ' ' . t('Section'),
      '#description' => t('This section is empty.'),
    );
  }
    
  foreach ($zones as $zone => $item) {
    $section = isset($sections[$item['section']]) ? 'section_' . $item['section'] : 'unassigned';
    $item['regions'] = !empty($item['regions']) ? $item['regions'] : array();
    
    unset($form['alpha_settings']['zones'][$section]['#description']);
    
    $form['alpha_settings']['zones'][$section]['zone_' . $zone] = array(
      '#type' => 'fieldset',
      '#title' => $item['name'] . ' ' . t('Zone'),
      '#weight' => $item['weight'],
      '#attributes' => array(
        'class' => array('alpha-inline'),
      ),
    );
    
    // Provide a full width wrapper around the zone (allowing for design elements outside the grid)
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_wrapper'] = array(
      '#type' => 'checkbox',
      '#title' => t('Provide full width wrapper around this zone'),
      '#description' => t('Enabling this feature will give a &lt;div&gt; wrapper around the zone itself, allowing you to theme in elements that appear outside the 960 pixel container zone.'),
      '#default_value' => $item['wrapper'],
    );
    
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_section'] = array(
      '#type' => 'select',
      '#title' => t('Section'),
      '#default_value' => $item['section'],
      '#element_validate' => array('alpha_theme_settings_validate_not_empty'),
      '#options' => array('_none' => '- None -') + $sections,
    );
    
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_weight'] = array(
      '#type' => 'weight',
      '#title' => t('Weight'),
      '#default_value' => $item['weight'],
    );
          
    // Create a container width selection menu for EACH zone
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_columns'] = array(
      '#type' => 'select',
      '#title' => t('Column count'),
      '#default_value' => $item['columns'],
      '#options' => $containers,
    );
    
    // Decide which region is the primary item.
    // The primary region is the one that will absorb the size of empty regions that are related in the same zone.
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_primary'] = array(
      '#type' => 'select',
      '#title' => t('Primary Region'),
      '#default_value' => $item['primary'],
      '#options' => array('_none' => t('- None -')) + $item['regions'],
      '#element_validate' => array('alpha_theme_settings_validate_not_empty'),
    );
    
    // Allow for zone classes
    $form['alpha_settings']['zones'][$section]['zone_' . $zone]['alpha_zone_' . $zone . '_css'] = array(
      '#type' => 'textfield',
      '#title' => t('Additional zone classes'),
      '#size' => 60,
      '#default_value' => $item['css'],
    );
  }
}