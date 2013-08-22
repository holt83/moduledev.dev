<?php

/**
 * HTML for a Facebook plugin. 
 * 
 * Available variables:
 * - $classes: String of classes that can be used to style contextually through
 *   css. The string can be manipulated through the variable $classes_array in
 *   preprocess functions.
 *   Note: The facebook specific classes to make the plugin work, is 
 *         contained in the classes array. Hence, if the classes array is not
 *         printed on the plugin container div, the plugin will not work.
 * - $attributes: String of attributes to be printed on the plugin container 
 *   div. The string can be manipulated through the variable $attributes_array
 *   in preprocess funtions.
 *   Note: The facebook specific attributes to make the plugin work, is 
 *         contained in the attributes array. Hence, if the array is not
 *         printed on the plugin container div, the plugin will not work.
 * 
 * Other variables:
 * - $url: Direct access to the url associated with the plugin.
 * - $colorscheme: Direct access to the colorscheme of the plugin
 * - $type: The type of the plugin. e.g.: 'like', 'follow'
 */

?>

<!-- Facebook plugin container div opening tag -->
<div class="<?php print $classes; ?>" <?php print $attributes; ?>>
</div>
<!-- /Facebook plugin container div closing tag -->