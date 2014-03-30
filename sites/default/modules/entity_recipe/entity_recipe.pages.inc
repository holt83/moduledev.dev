<?php

/**
 * @file
 *
 * Page callbacks for adding, editing and deleting ingredients.
 */

/**
 * Displayes add ingredient links for available types.
 */
function ingredient_add_page() {
	$item = menu_get_item();
	$content = system_admin_menu_block($item);
	if (count($content) == 1) {
		$item = array_shift($item);
		drupal_goto($item['href']);
	}
	return theme('ingredient_add_list', array('content' => $content));
}

/**
 * Returns HTML for a list of available types for ingredient creation.
 *
 * @param $variables
 *   An associative array containing:
 *   - content: An array of ingredient types.
 *
 * @ingroup themeable
 */
function theme_ingredient_add_list($variables) {
  $content = $variables['content'];
  $output = '';

  if ($content) {
  	$output = '<h2>' . t('Pick an ingredient type') . '</h2>';
  	$output .= '<hr>';
    $output .= '<dl class="ingredient-type-list">';
    foreach ($content as $item) {
    	$output .= '<br>';
      $output .= '<dt>' . l($item['title'], $item['href'], $item['localized_options']);
      $output .= '<span> - ' . filter_xss_admin($item['description']) . '</span></dt>';
      $output .= '<br>';
      $output .= '<hr>';
    }
    $output .= '</dl>';
  }
  else {
    $output = '<p>' . t('You have not created any ingredient types yet. Go to the <a href="@create-content">ingredient type creation page</a> to add a new type.', array('@create-content' => url('admin/structure/ingredients/add'))) . '</p>';
  }
  return $output;
}

/**
 * Return an ingredient submission form.
 */
function ingredient_add($type) {

}