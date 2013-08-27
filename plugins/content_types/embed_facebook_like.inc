<?php

/**
 * @file
 * 
 * This file describes the plugins that the embed facebook module provides. The
 * type of the plugins is a simple content type plugin with no context. 
 */

$plugin = array(
  'title' => t('Embed facebook like'),
  'description' => t('Embed a facebook like button as a ctools plugin'),
  'single' => TRUE, // No subtypes
  'content_types' => array('embed_facebook_like'), // Constructor
  'render callback' => 'embed_facebook_like_render',
  'defaults' => array(), // Default context (nothing)
  'edit form' => 'embed_facebook_like_edit_form',
  'category' => array(t('Embed Facebook'), 0),  
);

/**
 * Render callback for this plugin.
 */
function embed_facebook_like_render($subtype, $conf, $args, $context) {
  $block = new stdClass();
  $block->title = t('Embed Facebook');
  $block->content = array(
    '#theme' => 'embed_facebook__like',  
    '#type' => 'like',
    '#action' => 'recommend',  
  );
  return $block;
}

function embed_facebook_like_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['test'] = array(
    '#type' => 'textfield',
    '#title' => t('Test'),
    '#size' => 50,
    '#description' => t('This is a test'),
    '#default_value' => empty($conf['test']) ? '' : $conf['test'],
  );
  return $form;
}

function embed_facebook_like_edit_form_submit($form, &$form_state) {
  $form_keys = array(
    'test',  
  );
  foreach ($form_keys as $form_key) {
    $form_state['conf'][$form_key] = $form_state['values'][$form_key];
  }
}
