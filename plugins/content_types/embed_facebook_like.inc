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
  $block->title = t('Embed facebook like');
  $block->content = array(
    '#theme' => 'embed_facebook__like',  
    '#type' => 'like',
    '#url' => empty($conf['url']) ? '' : $conf['url'],  
    '#action' => empty($conf['action']) ? 'like' : $conf['action'],
    '#layout' => empty($conf['layout']) ? 'standard' : $conf['layout'],  
    '#colorscheme' => empty($conf['colorscheme']) ? 'light' : $conf['colorscheme'],
    '#send' => empty($conf['send']) ? '' : (bool)$conf['send']
  );
  return $block;
}

function embed_facebook_like_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL to like'),
    '#description' => t('The url of the webpage to like') . '<br/>' .
                      t('Leave empty to point to the current url'),                
    '#default_value' => empty($conf['url']) ? '' : $conf['url'],
  );
  $form['layout'] = array(
    '#type' => 'radios',
    '#title' => t('Facebook layout'),
    '#description' => t('Chooce a facebook layout'),
    '#default_value' => empty($conf['layout']) ? 'standard' : $conf['layout'],
    '#options' => array(
      'standard' => t('Standard'),
      'button_count' => t('Count button'),
      'box_count' => t('Count box'),  
    ),  
  );
  $form['colorscheme'] = array(
    '#type' => 'select',
    '#title' => t('Facebook colorscheme'),
    '#description' => t('Choose a facebook coloscheme'),
    '#default_value' => empty($conf['colorscheme']) ? 'light' : $conf['colorscheme'],
    '#options' => array(
      'light' => t('Light'),
      'dark' => t('Dark'),  
    ),  
  );
  $form['action'] = array(
    '#type' => 'select',
    '#title' => t('Facebook action text'),
    '#description' => t('Chooce the facebook action text to display'),
    '#default_value' => empty($conf['action']) ? 'like' : $conf['action'],
    '#options' => array(
      'like' => t('Like'),
      'recommend' => t('Recommend'),  
    ),  
  );
  $form['send'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include a send button'),
  );
  return $form;
}

function embed_facebook_like_edit_form_submit($form, &$form_state) {
  $form_keys = array('url', 'colorscheme', 'layout', 'action');
  foreach ($form_keys as $form_key) {
    if (!empty($form_state['values'][$form_key])) {
      $form_state['conf'][$form_key] = $form_state['values'][$form_key];
    }
  }
  if (isset($form_state['values']['send'])) {
    if ($form_state['values']['send'] == 0) {
      $form_state['conf']['send'] = 'false'; 
    }
    else {
      $form_state['conf']['send'] = 'true'; 
    }
  }
  file_put_contents("/home/quickstart/debug/debug.txt", print_r($form_state['conf']['send'], TRUE), FILE_APPEND);
}
