<?php 

/**
 * @file
 * 
 * Postit UI controller class.
 * 
 */

/**
 * UI Controller
 */
class PostItUIController extends EntityDefaultUIController {
  
  /**
   * Overrides hook_menu() defaults.
   */
  public function hook_menu() {
    $items = parent::hook_menu();
    $items[$this->path]['description'] = t('Create, Edit and Delete Postits.');
    return $items;
  }
  
}

/**
 * Generates the postit editing form.
 */
function postit_form($form, &$form_state, $postit, $op = 'edit') {
  $form['note'] = array(
    '#type' => 'textfield',
    '#title' => t('Note'),
    '#default_value' => $postit->note,
    '#description' => t('The main note of the PostIt'),
    '#size' => 60,
    '#maxlength' => 255,
    '#required' => TRUE,
  );
  $form['actions'] = array('#type' => 'actions');
  $form['actions']['submit'] = array(
    '#type' => 'submit',
    '#value' => t('Save PostIt'),
    '#weight' => 40,
  );
  field_attach_form('postit', $postit, $form, $form_state);
  return $form;  
}

/**
 * Form API submit callback for the postit editing form.
 */
function postit_form_submit($form, &$form_state) {
  $postit = entity_ui_controller('postit')->entityFormSubmitBuildEntity($form, $form_state);
  // Save and go back.
  $postit->save();
  $form_state['redirect'] = 'admin/content/postit';
}
