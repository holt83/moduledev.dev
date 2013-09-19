<?php
/**
 * @file
 * weapons_feature.features.inc
 */

/**
 * Implements hook_node_info().
 */
function weapons_feature_node_info() {
  $items = array(
    'weapon' => array(
      'name' => t('Weapon'),
      'base' => 'node_content',
      'description' => t('A content type used to describe a weapon. This is a test content type created to test the features module.'),
      'has_title' => '1',
      'title_label' => t('Title'),
      'help' => '',
    ),
  );
  return $items;
}
