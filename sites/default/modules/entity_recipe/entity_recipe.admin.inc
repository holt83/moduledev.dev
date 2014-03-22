<?php 

/**
 * @file
 *
 * Admin configuration for the Entity recipe module.
 */

/**
 * Form-builder callback for the ingredient type edit form.
 */
function entity_recipe_ingredient_type_form($form, &$form_state, $ingredient_type, $op = 'edit') {
	if ($op == 'clone') {
		$ingredient_type->label .= (' (cloned)');
		// Can't have two ingredient types with identical machine-names.
		$ingredient_type->type = '';
	}

	$form['label'] = array(
		'#type' => 'textfield',
		'#title' => t('Label'),
		'#default_value' => $ingredient_type->label,
		'#description' => t('The human-readable name of this ingredient type.'),
		'#required' => TRUE,
		'#size' => 30,
	);

	// Machine-readable ingredient type name.
	$form['type'] = array(
		'#type' => 'machine_name',
		'#default_value' => isset($ingredient_type->type ? $ingredient_type->type : ''),
		'#max_length' => 32,
		'#disabled' => $ingredient_type->isLocked() && $op != 'clone',
		'#machine_name' => array(
			'exists' => 'entity_recipe_get_ingredient_types',
			'source' => array('label'),
		),
		'#description' => t('A unique machine-name for this ingredient type. It
			must only contain lowercase letter, numbers and underscores.'),
	);

	// Submit button.
	$form['actions'] = array('#type' => 'actions');
	$form['actions']['submit'] = array(
		'#type' => 'submit',
		'#value' => t('Save ingredient type'),
		'#weight' => 40,
	);

	// Listing weight.
	$form['weight'] = array(
		'#type' => 'weight',
		'#title' => t('Weight'),
		'#default_value' => $ingredient_type->weight,
		'#description' => t('When showing ingredients, those with lighter weights
			gets listed before those with heavier weights.'),
		'#weight' => 10, // YO Dawg, I heard you liked weights...
	);

	// We only provide a delete button, if the form isn't adding a new ingredient
	// type and isn't locked.  
	if (!$ingredient_type->isLocked() && $op != 'add' && $op != 'clone') {
		$form['actions']['delete'] = array(
			'#type' => 'submit',
			'#value' => t('Delete ingredient type'),
			'#weight' => 45,
			// Don't validate any form elements as the data is being deleted anyway.
			'#limit_validation_errors' => array(),
			'#submit' => array('entity_recipe_ingredient_type_form_delete'),
		);
	}

	return $form;
}

/**
 * Form API submit callback for the submit button on ingredient type form.
 */
function entity_recipe_ingredient_type_form_submit(&$form, &$form_state) {
	$ingredient_type = entity_ui_form_submit_build_entity($form, $form_state);
	// Save and go back.
	$ingredient_type->save();
	$form['redirect'] = 'admin/structure/ingredients';
}

/**
 * Form API submit callback for the delete button on ingredient type form.
 */
function entity_recipe_ingredient_type_form_delete(&$form, &$form_state) {
	$type = $form_state['ingredient_type']->type;
	$form['redirect'] = "admin/structure/ingredients/manage/$type/delete";
}