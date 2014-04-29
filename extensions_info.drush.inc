<?php

/**
 * @file
 * Drupal extensions scanned commands.
 */

/**
 * Implements hook_drush_command().
 */
function extensions_info_drush_command() {
  $items = array();
  $options = array();

  $items['extensions_info'] = array(
    'description' => dt('Return information about Drupal extensions (modules, themes).'),
    'aliases' => array('mi'),
    'options' => $options,
    'outputformat' => array(
      'default' => 'table',
      'pipe-format' => 'list',
      'field-labels' => array(
        'name' => 'Name',
        'description' => 'Description',
        'package' => 'Package',
        'path' => 'Path',
      ),
      'output-data-type' => 'format-table',
    ),
    'bootstrap' => DRUSH_BOOTSTRAP_DRUSH,
  );

  return $items;
}

/**
 * Implements hook_drush_help().
 */
function extensions_info_drush_help($section) {
  switch ($section) {
    case 'drush:extensions_info':
      return dt('Return information about all Drupal extensions recursively scanning directories from current.');
  }
}

/**
 * Recursively scan for .info files and return their parsed data.
 */
function drush_extensions_info() {
  $result = array();
  $path = drush_get_option('path', drush_cwd());
  $files = drush_scan_directory($path, '/.info$/');

  foreach ($files as $file) {
    $info = drush_drupal_parse_info_file($file->filename);

    if (isset($info['project']) && $info['project'] !== 'drupal') {
      $row['name'] = $info['name'];
      $row['description'] = !empty($info['description']) ? $info['description'] : dt('(No description)');
      $row['package'] = !empty($info['package']) ? $info['package'] : dt('(No package)');
      if (strpos($file->filename, 'contrib') !== FALSE) {
        $row['path'] = 'http://drupal.org/project/' . $info['project'];
      } 
      else {
        // @todo Find out what to do with custom paths.
        $row['path'] = dt('(custom)');
      }
      $result[$info['project']] = $row;
      unset($row);
    }
  }

  return $result;
}
