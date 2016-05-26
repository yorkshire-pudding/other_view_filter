<?php

/**
 * @file
 * Definition of views_handler_filter_entity_other_view
 */

/**
 * Filter class which allows to filter by certain bundles of an entity.
 *
 * This class provides workarounds for taxonomy and comment.
 *
 * @ingroup views_filter_handlers
 */
class other_view_handler_filter_entity extends views_handler_filter_in_operator {
  var $value_form_type = 'select';
  /**
   * Stores the entity type on which the filter filters.
   *
   * @var string
   */
  public $entity_type;

  function init(&$view, &$options) {
    parent::init($view, $options);

    $this->get_entity_type();
  }

  /**
   * Set and returns the entity_type.
   *
   * @return string
   *   The entity type on the filter.
   */
  function get_entity_type() {
    if (!isset($this->entity_type)) {
      $data = views_fetch_data($this->table);
      if (isset($data['table']['entity type'])) {
        $this->entity_type = $data['table']['entity type'];
      }

      // If the current filter is under a relationship you can't be sure that the
      // entity type of the view is the entity type of the current filter
      // For example a filter from a node author on a node view does have users as entity type.
      if (!empty($this->options['relationship']) && $this->options['relationship'] != 'none') {
        $relationships = $this->view->display_handler->get_option('relationships');
        if (!empty($relationships[$this->options['relationship']])) {
          $options = $relationships[$this->options['relationship']];
          $data = views_fetch_data($options['table']);
          $this->entity_type = $data['table']['entity type'];
        }
      }
    }

    return $this->entity_type;
  }

  /**
   * Return a list of all available views.
   */
  function get_value_options() {
    if (!isset($this->value_options)) {
      // Create a list of all the view:display combos.
      $this->value_title = t('View: display');
      $this->value_options = views_get_views_as_options();
    }
  }

  /**
   *
   */
  function query() {
    $this->ensure_my_table();
    // This only handles one at a time. If there are more, it uses the last.
    // @todo: enforce single selection.
    foreach($this->value as $other_view_name_display) {
      $other_view_name_display_array = explode(':', $other_view_name_display);
      $other_view_name = $other_view_name_display_array[0];
      $other_view_display = $other_view_name_display_array[1];
    }
    // Figure out what this entity id is called (eg. nid, uid, etc.)
    $entity_info = entity_get_info($this->entity_type);
    $id_id = $entity_info['entity keys']['id'];
    // Get the results of the specified view/display combo.
    $other_view_result = views_get_view_result($other_view_name, $other_view_display);
    $other_ids = array();
    foreach($other_view_result as $result) {
      $other_ids[] = $result->$id_id;
    }
    // Add them as a condition to the query.
    $this->query->add_where(0, $id_id, $other_ids, $this->operator);
  }
}
