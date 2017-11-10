<?php
/**
 * @file
 * Views hooks for Other View filter module.
 */

/**
 * Implements hook_views_data_alter().
 */
function other_view_filter_views_data_alter(&$data) {
  $entities = entity_get_info();

  foreach ($entities as $entity) {
    if (isset($entity['base table'])) {
      if (isset($data[$entity['base table']])) {

        $data[$entity['base table']]['other_view_filter'] = array(
          'title' => t('Other view result'),
          'help' => t('Filters this view against results of selected other view.'),
          'filter' => array('handler' => 'other_view_filter_handler_filter_view'),
        );
      }
    }
  }
}
