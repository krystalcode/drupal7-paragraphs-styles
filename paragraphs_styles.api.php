<?php

/**
 * @file
 * API documentation for the paragraphs_styles module.
 */

/**
 * Describe the styles that will be available in the drop-down.
 *
 * @param $options
 * @param $field
 * @param $instance
 *
 * @return array
 *   An associative array of all available styles, keyed by the style name,
 *   and with the human-readable name as its values.
 *
 * @see paragraphs_styles_get_options()
 */
function hook_paragraphs_styles_list_options($options, $field, $instance) {
  $options['full_width'] = t('Full width');
  $options['full_width_bg_grey'] = t('Full width with grey background');
  return $options;
}

/**
 * Alter the style names used on field.
 *
 * @param array $options
 *   An array of styles, keyed by style name, then by human-readable
 *   name.
 *
 * @see paragraphs_styles_get_options()
 */
function hook_paragraphs_styles_list_options_alter(&$options) {
  $options['full_width'] = t('Full width e.g. horizontally extending to the edges of the screen');
}
