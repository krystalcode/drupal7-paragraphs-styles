<?php

/**
 * @file
 * Implements custom fields for the Paragraphs Styles module.
 *
 */

/**
 * Implements hook_field_info().
 */
function paragraphs_styles_field_info() {
  return array(
    PARAGRAPHS_STYLES_FIELD_TYPE_LIST => array(
      'label' => t('Paragraph styles'),
      'description' => t('Allows associating a paragraph with a specific style.'),
      'default_widget' => 'options_select',
      'default_formatter' => 'list_default',
      // The settings below are necessary for "options_select" widget and
      // "list_default" formatter to work correctly without warnings.
      'settings' => array('allowed_values' => array(), 'allowed_values_function' => ''),
    ),
  );
}

/**
 * Implements hook_field_is_empty().
 */
function paragraphs_styles_field_is_empty($item, $field) {
  if (empty($item['value'])) {
    return TRUE;
  }
  return FALSE;
}

/**
 * Implements hook_field_validate().
 */
function paragraphs_styles_field_validate($entity_type, $entity, $field, $instance, $langcode, $items, &$errors) {
  foreach ($items as $delta => $item) {
    if (!empty($item['value'])) {
      $selected = $item['value'];
      $possible_options = paragraphs_styles_get_options($field, $instance);

      // Validate the selected option.
      if (!isset($possible_options[$selected])) {
        $errors[$field['field_name']][$langcode][$delta][] = array(
          'error' => 'paragraphs_styles_invalid',
          'message' => t('Selected option "%selected" is not allowed.', array(
            '%selected' => $selected,
          )),
        );
      }
    }
  }
}

/**
 * Implements hook_field_widget_info_alter().
 *
 * The PARAGRAPHS_STYLES_FIELD_TYPE_LIST field type does not implement widgets
 * of its own, but reuses the widget defined in options.module.
 *
 * @see paragraphs_pack_options_list()
 */
function paragraphs_styles_field_widget_info_alter(&$info) {
  $widgets = array(
    'options_select' => array(PARAGRAPHS_STYLES_FIELD_TYPE_LIST),
    'options_buttons' => array(PARAGRAPHS_STYLES_FIELD_TYPE_LIST),
  );

  foreach ($widgets as $widget => $field_types) {
    $info[$widget]['field types'] = array_merge($info[$widget]['field types'], $field_types);
  }
}

/**
 * Implements hook_options_list().
 */
function paragraphs_styles_options_list($field, $instance, $entity_type, $entity) {
  $options = array();

  switch ($field['type']) {
    case PARAGRAPHS_STYLES_FIELD_TYPE_LIST:
      $options = paragraphs_styles_get_options($field, $instance);
      break;
  }

  return $options;
}
