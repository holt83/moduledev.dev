<?php
/**
 * @file
 * postit.features.field_base.inc
 */

/**
 * Implements hook_field_default_field_bases().
 */
function postit_field_default_field_bases() {
  $field_bases = array();

  // Exported field_base: 'field_postit_additional_note'
  $field_bases['field_postit_additional_note'] = array(
    'active' => 1,
    'cardinality' => 1,
    'deleted' => 0,
    'entity_types' => array(),
    'field_name' => 'field_postit_additional_note',
    'foreign keys' => array(
      'format' => array(
        'columns' => array(
          'format' => 'format',
        ),
        'table' => 'filter_format',
      ),
    ),
    'indexes' => array(
      'format' => array(
        0 => 'format',
      ),
    ),
    'locked' => 0,
    'module' => 'text',
    'settings' => array(
      'max_length' => 255,
      'profile2_private' => FALSE,
    ),
    'translatable' => 0,
    'type' => 'text',
  );

  return $field_bases;
}
