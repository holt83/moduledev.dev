<?php

/**
 * @file
 * 
 * This file describes the ctools plugin that the embed facebook module 
 * provides. The type of the plugin is a simple content type plugin with no use 
 * of context. 
 */

$plugin = array(
  'title' => t('Embed Facebook like'),
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
  $block->title = t('Embed Facebook like');
  $block->content = array(
    '#theme' => 'embed_facebook',  
    '#type' => 'like',
    '#display_type' => 'plugin',  
    '#url' => empty($conf['url']) ? '' : $conf['url'],  
    '#action' => empty($conf['action']) ? 'like' : $conf['action'],
    '#layout' => empty($conf['layout']) ? 'standard' : $conf['layout'],  
    '#colorscheme' => empty($conf['colorscheme']) ? 'light' : $conf['colorscheme'],
    '#send' => isset($conf['send']) ? _convert_int_to_bool_value($conf['send']) : 0,
    '#faces' => isset($conf['faces']) ? _convert_int_to_bool_value($conf['faces']) : 0,  
  );
  return $block;
}

/**
 * Form builder for the edit settings form for this plugin. When using this
 * particular callback for conent type plugins, the settings can be changed
 * directly from panels user interface.
 * Here we allow the user to setup the various facebook attributes on the plugin.
 * These attributes control the look and behavior of the plugin.
 */
function embed_facebook_like_edit_form($form, &$form_state) {
  $conf = $form_state['conf'];
  $form['type'] = array(
    '#type' => 'radios',
    '#title' => t('Facebook plugin type'),
    '#description' => t('Select the type of Facebook plugin to use'),
    '#default_value' => 'like',
    '#options' => array(
      'like' => t('Like'),
      'send' => t('Send'),
      'follow' => t('Follow'),  
    ),  
  );
  $form['url'] = array(
    '#type' => 'textfield',
    '#title' => t('URL to like'),
    '#description' => t('The url of the webpage to like') . '<br/>' .
                      t('Leave empty to point to the current url'),                
    '#default_value' => empty($conf['url']) ? '' : $conf['url'],
    '#size' => 50,  
  );
  $form['send'] = array(
    '#type' => 'checkbox',
    '#title' => t('Include a send button'),
    '#default_value' => isset($conf['send']) ? $conf['send'] : 0,  
  );
  $form['faces'] = array(
    '#type' => 'checkbox',
    '#title' => t('Show Facebook profile pictures'),
    '#default_value' => isset($conf['faces']) ? $conf['faces'] : 0,  
  );
  $form['layout'] = array(
    '#type' => 'radios',
    '#title' => t('Facebook layout'),
    '#description' => t('Chooce a Facebook layout'),
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
    '#description' => t('Choose a Facebook coloscheme'),
    '#default_value' => empty($conf['colorscheme']) ? 'light' : $conf['colorscheme'],
    '#options' => array(
      'light' => t('Light'),
      'dark' => t('Dark'),  
    ),  
  );
  $form['action'] = array(
    '#type' => 'select',
    '#title' => t('Facebook action text'),
    '#description' => t('Chooce the Facebook action text to display'),
    '#default_value' => empty($conf['action']) ? 'like' : $conf['action'],
    '#options' => array(
      'like' => t('Like'),
      'recommend' => t('Recommend'),  
    ),  
  );
  $css_options = array(
    'type' => 'file',  
    'group' => CSS_DEFAULT,
    'data' => EMBED_FACEBOOK_PATH . '/css/plugin-edit-form.css',  
  );
  $form['#attached']['css'] = $css_options;
  return $form;
}

/**
 * Submit handler for the edit plugin settings form. 
 */
function embed_facebook_like_edit_form_submit($form, &$form_state) {
  $form_keys = array('url', 'colorscheme', 'layout', 'action', 'send', 'faces');
  foreach ($form_keys as $form_key) {
    if (isset($form_state['values'][$form_key])) {
      $form_state['conf'][$form_key] = $form_state['values'][$form_key];
    }
  }
}

/**
 * Converts an integer value to a string with values 'false' or 'true'.
 * This funtion is needed because boolean values on the facebook specific
 * attributes is respresented as strings.
 * 'false' if integer value is 0.
 * 'true' if integer value is not 0.
 */
function _convert_int_to_bool_value($int) {
  if ($int == 1) {
    return 'true';
  }
  return 'false';
}