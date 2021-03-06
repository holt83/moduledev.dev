<?php

/**
 * Implementation of hook_drush_command().
 *
 * In this hook, you specify which commands your
 * drush module makes available, what it does and
 * description.
 *
 * Notice how this structure closely resembles how
 * you define menu hooks.
 *
 * @See drush_parse_command() for a list of recognized keys.
 *
 * @return
 *   An associative array describing your command(s).
 */
function entity_recipe_drush_command() {
  $items = array();

  $defaults = array(
    'required-arguments' => TRUE,
  );

  $items['print-entity'] = array(
    'description' => 'Prints an entity.',
    'arguments' => array(
      'entity' => 'Entity ID.',
      'type' => 'Entity type.',
    ),
    'aliases' => array('pe'),
  ) + $defaults;

  $items['dump-entity-info'] = array(
    'description' => "Output a dump of an entity type's information.",
    'arguments' => array(
      'type' => 'Entity type.',
    ),
    'aliases' => array('dei'),
  ) + $defaults;

  $items['dump-entity-properties'] = array(
    'description' => "Output a dump of an entity's property information.",
    'arguments' => array(
      'type' => 'Entity type.',
      'entity' => 'Entity ID.',
    ),
    'aliases' => array('dep'),
  ) + $defaults;

  $items['print-table'] = array(
    'description' => 'Prints the contents of a database table.',
    'arguments' => array(
      'table' => 'Table name',
    ),
    'aliases' => array('pt'),
  ) + $defaults;

  $items['entity-create'] = array(
    'description' => 'Create an entity.',
    'arguments' => array(
      'type' => 'Entity type',
      'data' => 'Data to use for the new entity.',
    ),
    'examples' => array(
      'drush entity-create ingredient \'{"name": "Salt"}\'' => dt('Creates an ingredient entity named "Salt" and displays the properties of the new entity.'),
      'drush ec ingredient \'{"name": "Salt"}\'' => dt('Same result as the previous example except the command alias is used.'),
    ),
    'aliases' => array('ec'),
  ) + $defaults;

  $items['entity-read'] = array(
    'description' => 'Reads an entity and prints the properties.',
    'arguments' => array(
      'id' => 'Entity ID',
    ),
    'examples' => array(
      'drush entity-read 1' => dt('Reads an ingredient entity named "Salt" and displays the contents of the ingredient database table.'),
      'drush er 1' => dt('Same result as the previous example except the command alias is used.'),
    ),
    'aliases' => array('er'),
  ) + $defaults;

  $items['entity-update'] = array(
    'description' => 'Update an ingredient entity property and prints the whole entity after the update.',
    'arguments' => array(
      'type' => 'Entity type',
      'pkey' => 'Property name',
      'pval' => 'Property value',
    ),
    'examples' => array(
      'drush entity-update ingredient name Sugar' => dt("Updates an ingredient entity's \"name\" property with the value \"Sugar\" and displays the entity properties after the update."),
      'drush eu ingredient name Sugar' => dt('Same result as the previous example except the command alias is used.'),
    ),
    'aliases' => array('eu'),
  ) + $defaults;

  $items['entity-delete'] = array(
    'description' => "Delete an entity and prints the entity type's storage table.",
    'arguments' => array(
      'type' => 'Entity type',
      'id' => 'Entity ID',
    ),
    'examples' => array(
      'drush entity-delete ingredient 1' => dt('Deletes an ingredient entity with the ID 1.'),
      'drush ed ingredient 1' => dt('Same result as the previous example except the command alias is used.'),
    ),
    'aliases' => array('ed'),
  ) + $defaults;

  return $items;
}

/**
 * Implementation of hook_drush_help().
 *
 * This function is called whenever a drush user calls
 * 'drush help <name-of-your-command>'. This hook is optional. If a command
 * does not implement this hook, the command's description is used instead.
 *
 * This hook is also used to look up help metadata, such as help
 * category title and summary.  See the comments below for a description.
 *
 * @param
 *   A string with the help section (prepend with 'drush:' or 'meta:')
 *
 * @return
 *   A string with the help text for your command.
 */
function entity_recipe_drush_help($section) {
  switch ($section) {
    case 'drush:dump-entity-info':
      return dt('Type drush dump-entity-info (or dei) followed by an entity type, to show info about that type');
    // The 'title' meta item is used to name a group of
    // commands in `drush help`.  If a title is not defined,
    // the default is "All commands in ___", with the
    // specific name of the commandfile (e.g. sandwich).
    // Command files with less than four commands will
    // be placed in the "Other commands" section, _unless_
    // they define a title.  It is therefore preferable
    // to not define a title unless the file defines a lot
    // of commands.
    case 'meta:entity_recipe:title':
      return dt('Entity recipe module commands');
    // The 'summary' meta item is displayed in `drush help --filter`,
    // and is used to give a general idea what the commands in this
    // command file do, and what they have in common.      
    case 'meta:entity_recipe:summary':
      return dt('Use Drush to perform various entity operation with the entity API');
  }
}

/**
 * Print the property names and values of the entity with the
 * given type and ID.
 *
 * @param $entity
 *   Either the identifier of the entity, an Entity object or an
 *   EntityMetadataWrapper object.
 * @param $type
 *   Type of the entity. Only needed if $id
 * @return
 *   Table output or, if unsucessful, returns FALSE.
 */
function drush_entity_recipe_print_entity($entity, $type = NULL) {
  // Convert anything we're given into a wrapper object
  $wrapper = _entity_recipe_assert_wrapper($entity, $type);
  if (!is_object($wrapper)) {
    // A non-object means a wrapper was not possible
    return $wrapper;
  }

  $handle = _entity_recipe_handle();

  $header = ' Entity (' . $wrapper->type();
  $header .= ') - ID# '. $wrapper->getIdentifier().':';
  // equivalents: $wrapper->value()->entityType()
  //              $wrapper->value()->identifier()

  $rows = array();
  foreach ($wrapper as $pkey => $property) {
    // $wrapper->$pkey === $property
    if (!($property instanceof EntityValueWrapper)) {
      $rows[$pkey] = $property->raw()
        . ' (' . $property->label() . ')';
    }
    else {
      $rows[$pkey] = $property->value();
    }
  }

  $table = drush_key_value_to_array_table($rows);
  drush_print($header."\n", 0, $handle);
  $tbl = drush_print_table($table, TRUE, array(), $handle);

  return $header."\n\n".$tbl->getTable();
}

/**
 * Print the entity information of the given entity type.
 *
 * @param $type
 *   Entity type.
 */
function drush_entity_recipe_dump_entity_info($type) {
  $info = entity_get_info($type);
  drush_print_r($info);
}

/**
 * Print the property names and values of the entity with the
 * given type and ID.
 *
 * @param $type
 *   Entity type.
 * @param $id
 *   Entity ID. If not given the entity property information of
 *   the entity type will be printed instead.
 */
function drush_entity_recipe_dump_entity_properties($type, $id = NULL) {
  if (!isset($id)) {
    $info = entity_get_property_info($type);
    drush_print_r($info);
  }
  else {
    // Convert anything we're given into a wrapper object
    $wrapper = _entity_recipe_assert_wrapper($id, $type);
    if (!is_object($wrapper)) {
      // A non-object means a wrapper was not possible
      return $wrapper;
    }

    drush_print_r($wrapper->getPropertyInfo());
  }
}

/**
 * Ensures the given object is a wrapper object by wrapping it if
 * necessary.
 *
 * @param $object
 *   Either an EntityMetadataWrapper, an Entity or an identifier.
 *   If this is an identifier the $type argument is required.
 * @param $type
 *   Entity type.
 * @return
 *   EntityMetadataWrapper object or FALSE if it was not possible.
 */
function _entity_recipe_assert_wrapper($object, $type = NULL) {
  if (!is_object($object)) {
    if (!$type) {
      return _entity_recipe_error(dt('An entity type must be given.'));
    }
    return entity_metadata_wrapper($type, $object);
  }
  else if (!($object instanceof EntityMetadataWrapper)) {
    if (!($object instanceof Entity)) {
      return _entity_recipe_error(dt('Unable to wrap object. Not an Entity.'));
    }
    // Entity class has entityType method
    return entity_metadata_wrapper($object->entityType(), $object);
  }
  else {
    return $object;
  }
}

function drush_entity_recipe_print_table($table, $key = NULL) {
  $header = "Database Table - $table:";
  $handle = _entity_recipe_handle();

  if (!($schema = drupal_get_schema($table))) {
    return FALSE;
  }

  $rows = array(array_keys($schema['fields']));

  if (!isset($key)) {
    if (count($schema['primary key']) > 1) {
      // No support for multi-key tables
      return _entity_recipe_error(dt('The "@table" table has a primary key with more than one field. Can not print it!', array('@table' => $table)));
    }
    $key = $schema['primary key'][0];
  }

  $rows += db_select($table, 't')->fields('t', $rows[0])->execute()->fetchAllAssoc($key);

  drush_print($header."\n", 0, $handle);
  $tbl = drush_print_table($rows, TRUE, array(), $handle);
  return $header."\n\n".$tbl->getTable();
}

/**
 * CREATE an entity and display its properties.
 *
 * @param $type
 *   Entity type
 * @param $data
 *   Either JSON string, an object or an associative array.
 * @return
 *   The created entity wrapped in an EntityMetadataWrapper.
 */
function drush_entity_recipe_entity_create($type, $data) {
  if (!is_array($data)) {
    if (is_string($data)) {
      $data = drupal_json_decode($data);
    }
    else if (is_object($data)) {
      $data = (array) $data;
    }
  }

  $entity = entity_create($type, $data);
  // Can call $entity->save() here or wrap, save then play
  $wrapper = entity_metadata_wrapper($type, $entity);
  $wrapper->save();

  drush_entity_recipe_print_entity($wrapper);
  return $wrapper;
}

/**
 * READ an entity and display its properties.
 */
function drush_entity_recipe_entity_read($type, $id) {
  $wrapper = entity_metadata_wrapper($type, $id);

  drush_entity_recipe_print_entity($wrapper);
}

/**
 * UPDATE an entity and display its properties.
 *
 * @param $type
 *   Entity type.
 * @param $id
 *   Entity ID.
 * @param $pname
 *   Property name.
 * @param $pval
 *   New property value.
 */
function drush_entity_recipe_entity_update($type, $id, $pname, $pval) {
  $wrapper = entity_metadata_wrapper($type, $id);

  $wrapper->$pname = $pval;
  $wrapper->save();

  // Reload the entity bypassing the cache
  // Not normally needed since an exception is thrown on error
  $entity = entity_load_unchanged($type, $id);
  $wrapper->set($entity);

  drush_entity_recipe_print_entity($wrapper);
}

/**
 * DELETE an entity and display its table.
 *
 * @param $type
 *   Entity type.
 * @param $id
 *   Entity ID.
 */
function drush_entity_recipe_entity_delete($type, $id) {
  $wrapper = entity_metadata_wrapper($type, $id);
  $wrapper->delete();

  _entity_recipe_print_entity_base_table($wrapper);
}

function drush_entity_recipe_drush_entity_recipe_init() {

}

/**
 * Prints the contents of the given entity's base table.
 */
function _entity_recipe_print_entity_base_table($entity) {
  if ($entity instanceof Entity) {
    $info = $entity->entityInfo();
  }
  else if ($entity instanceof EntityMetadataWrapper) {
    $info = $entity->value()->entityInfo();
  }
  else {
    return FALSE;
  }

  drush_entity_recipe_print_table($info['base table']);
}

/**
 * Suppresses all normal output from entity_recipe commands.
 * @ingroup entity_recipe_helpers
 */
function _entity_recipe_suppress_output($setting = FALSE) {
  static $suppress;

  if (!is_null($setting)) {
    $suppress = $setting;
  }

  return $suppress;
}

/**
 * Returns the correct handle to use in output calls.
 * @ingroup entity_recipe_helpers
 */
function _entity_recipe_handle() {
  static $handle = NULL;

  if (($suppress = _entity_recipe_suppress_output()) && is_null($handle)) {
    if ($handle = fopen('/dev/null', 'w')) {
      // Make sure we clean up
      register_shutdown_function('_entity_recipe_handle_close');
    }
  }

  return ($suppress ? $handle : NULL);
}

/**
 * Close the output handle we have used.
 * @ingroup entity_recipe_helpers
 */
function _entity_recipe_handle_close() {
  $handle = _entity_recipe_handle();
  fclose($handle);
}

/**
 * @ingroup entity_recipe_helpers
 */
function _entity_recipe_error($msg) {
  return drush_set_error(DRUSH_FRAMEWORK_ERROR, $msg);
}
