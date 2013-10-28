<?php 

/**
 * @file
 * 
 * Defines EntityController classes for our entities
 */

class PostItController extends DrupalDefaultEntityController {
  
  public function save($postit) {
    field_attach_presave('postit', $postit);
    drupal_write_record('postit', $postit);
    field_attach_insert('postit', $postit);
    module_invoke_all('entity_insert', 'postit', $postit);
    return $postit;
  }
  
}