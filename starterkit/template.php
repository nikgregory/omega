<?php
// $Id: template.php,v 1.3.2.2.2.1 2010/11/01 16:26:38 himerus Exp $

/**
 * @file
 * Starter template.php file for subthemes of Omega.
 */

/*
 * Add any conditional stylesheets you will need for this sub-theme.
 *
 * To add stylesheets that ALWAYS need to be included, you should add them to
 * your .info file instead. Only use this section if you are including
 * stylesheets based on certain conditions.
 */

/**
 * Implements hook_theme().
 */
function omega_starterkit_theme(&$existing, $type, $theme, $path) {
  $hooks = array();
  //$hooks = omega_theme($existing, $type, $theme, $path);
  return $hooks;
}
