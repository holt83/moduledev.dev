<?php
/**
 * @file
 * postit.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function postit_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'postit-postit-field_simple_textfield'
  $field_instances['postit-postit-field_simple_textfield'] = array(
    'bundle' => 'postit',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => '',
    'display' => array(
      'default' => array(
        'label' => 'hidden',
        'module' => 'text',
        'settings' => array(),
        'type' => 'text_default',
        'weight' => 0,
      ),
    ),
    'entity_type' => 'postit',
    'field_name' => 'field_simple_textfield',
    'label' => 'Additonal Text',
    'required' => 0,
    'settings' => array(
      'text_processing' => 0,
      'user_register_form' => FALSE,
    ),
    'widget' => array(
      'active' => 1,
      'module' => 'text',
      'settings' => array(
        'size' => 60,
      ),
      'type' => 'text_textfield',
      'weight' => 1,
    ),
  );

  // Translatables
  // Included for use with string extractors like potx.
  t('Additonal Text');

  return $field_instances;
}
