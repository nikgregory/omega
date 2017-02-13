<?php

use Drupal\Core\Form\FormStateInterface;

/**
 * Implementation of HOOK_form_system_theme_settings_alter()
 *
 * @param $form
 *   Nested array of form elements that comprise the form.
 *
 * @param \Drupal\Core\Form\FormStateInterface $form_state
 *   A keyed array containing the current state of the form.
 */
function nik__form_system_theme_settings_alter(&$form, FormStateInterface &$form_state) {
  // Add custom validation handler. Uncomment following line to activate.
  // $form['#validate'][] = 'nik__theme_settings_validate';
  // Add custom submit handler. Uncomment following line to activate.
  // $form['#submit'][] = 'nik__theme_settings_submit';
}

/**
 * Custom validation for nik__form_system_theme_settings_alter()
 *
 * @param $form
 * @param \Drupal\Core\Form\FormStateInterface $form_state
 */
function nik__theme_settings_validate(&$form, FormStateInterface &$form_state) {

}

/**
 * Custom submit handler for nik__form_system_theme_settings_alter()
 *
 * @param $form
 * @param \Drupal\Core\Form\FormStateInterface $form_state
 */
function nik__theme_settings_submit(&$form, FormStateInterface &$form_state) {

}
