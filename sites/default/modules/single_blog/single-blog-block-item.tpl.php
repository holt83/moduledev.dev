<?php

/**
 * @file
 * HTML for an item in the single blog's block listing.
 * 
 * Available variables:
 * - $classes: String of classes that can be used to style contextually through
 *   css. It can be manipulated through the variable $classes_array from
 *   preprocess functions.
 *   The default values can be one or more of the following:
 *   - single-blog-block-item: The current template type I.E. "theming hook".
 *   - $date: Formatted creation date. Preprocess funtions can reformat it by
 *            calling format_date() with the desired parameteres on the 
 *            $created variable.
 *   - $title: A renderable array that provides a title and link to the node.
 *   - $name: Themes username of node author output from theme_username().
 * 
 * - $classes_array: An array of HTML class attribute values. It is flattened
 *                   into a string in the $classes array.'
 * 
 * Other variables:
 * The following variables are provided for contextual information.
 * - $node: Partial node object. Contains data that may not be safe.
 * - $created: The time the node was published in UNIX timestamp.
 * - $user: The user object of the node author.
 * 
 * @see template_preprocess_single_blog_block_item().
 */
?>

<div class="<?php print $classes; ?>">
 
  <div class="date"><?php print $date; ?></div>
  
  <h4<?php print $title_attributes; ?>>
    <?php print render($title); ?>
  </h4>
  
  <div class="name">
    <?php print t('by !username', array('!username' => $name)); ?>
  </div>
  
</div>