<?php

/**
 * @file
 *
 * Provides entity metadata integration.
 */

/**
 * Customize the default metadata controller for the ingredient entity.
 */
class IngredientMetaDataController extends EntityDefaultMetadataController {

	public function entityPropertyInfo() {
		$info = parent::entityPropertyInfo();
		$properties = &$info[$this->type]['properties']; 

		$properties['name'] = array(
			'label' => t('Name'),
			'description' => t('ingredient name.'),
			'setter callback' => 'entity_property_verbatim_set',
			'setter permission' => 'administer ingredients',
			'schema field' => 'name',
		);

		$properties['type'] = array(
			'type' => 'ingredient_type',
			'getter callback' => 'entity_property_getter_method',
			'setter callback' => 'entity_property_verbatim_set',
			'setter permission' => 'administer ingredients',
			'reqiured' => TRUE,
			'description' => t('The ingredient type.'), 
		) + $properties['type'];
		
		return $info;
	}

}