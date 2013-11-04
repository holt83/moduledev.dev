<?php
/**
 * @file
 * postit_fields.features.field_instance.inc
 */

/**
 * Implements hook_field_default_field_instances().
 */
function postit_fields_field_default_field_instances() {
  $field_instances = array();

  // Exported field_instance: 'postit-postit-field_additional_note'
  $field_instances['postit-postit-field_additional_note'] = array(
    'bundle' => 'postit',
    'default_value' => NULL,
    'deleted' => 0,
    'description' => 'Enter an additional note for the postit.',
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
    'field_name' => 'field_additional_note',
    'label' => 'Additional note',
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
  t('Additional note');
  t('Enter an additional note for the postit.');

  return $field_instances;
}
