<?php
/**
 * @file
 * Contains other_view_filter_handler_filter_view.
 */

/**
 * Filter class which allows to filter by another view.
 *
 * @ingroup views_filter_handlers
 */
class other_view_filter_handler_filter_view extends views_handler_filter_in_operator {
  /**
   * Stores the form type.
   *
   * @var string
   */
  public $value_form_type = 'select';

  /**
   * Stores the entity type on which the filter filters.
   *
   * @var string
   */
  public $entity_type;

  /**
   * {@inheritdoc}
   */
  public function init(&$view, &$options) {
    parent::init($view, $options);
    $this->get_entity_type();
  }

  /**
   * {@inheritdoc}
   */
  public function construct() {
    parent::construct();
    $this->value_title = t('View: display');
  }

  /**
   * {@inheritdoc}
   */
  public function option_definition() {
    $options = parent::option_definition();
    // Set "not in" operator to have usual use case selected by default.
    $options['operator']['default'] = 'not in';
    return $options;
  }

  /**
   * Set and returns the entity_type.
   *
   * @return string
   *   The entity type on the filter.
   */
  public function get_entity_type() {
    if (isset($this->entity_type)) {
      return $this->entity_type;
    }

    $data = views_fetch_data($this->table);
    if (isset($data['table']['entity type'])) {
      $this->entity_type = $data['table']['entity type'];
    }

    // If the current filter is under a relationship you can't be sure that the
    // entity type of the view is the entity type of the current filter
    // For example a filter from a node author on a node view does
    // have users as entity type.
    if (!empty($this->options['relationship']) && $this->options['relationship'] != 'none') {
      $relationships = $this->view->display_handler->get_option('relationships');

      if (!empty($relationships[$this->options['relationship']])) {
        $options = $relationships[$this->options['relationship']];
        $data = views_fetch_data($options['table']);
        $this->entity_type = $data['table']['entity type'];
      }
    }

    return $this->entity_type;
  }

  /**
   * {@inheritdoc}
   */
  public function value_form(&$form, &$form_state) {
    parent::value_form($form, $form_state);
    unset($form['value']['#options']['all']);

    $form['user_warning'] = array(
      '#markup' => t(
        'Using more than 1 view in "@input" section will strongly decrease your site performance.',
        array('@input' => t('View: display'))
      ),
      '#prefix' => '<div class="messages warning">',
      '#suffix' => '</div>',
      '#weight' => -999,
    );
  }

  /**
   * Return a list of all available views.
   */
  public function get_value_options() {
    if (isset($this->value_options)) {
      return;
    }

    $views = views_get_all_views();
    $this->value_options = array();

    foreach ($views as $view) {

      // Only use views that output entities that might be in this view.
      if ($view->base_table == $this->table) {
        foreach ($view->display as $display) {

          // Don't let users filter views display results recursively.
          if ("{$this->view->name}:{$this->view->current_display}" !== "{$view->name}:{$display->id}") {
            $this->value_options["{$view->name}:{$display->id}"] = "{$view->human_name}: {$display->display_title}";
          }
        }
      }
    }

    return $this->value_options;
  }

  /**
   * {@inheritdoc}
   */
  public function accept_exposed_input($input) {
    $value = $this->value;
    $return = parent::accept_exposed_input($input);

    // If the parent method produced a nested array, remove the nesting.
    if ($this->value !== $value && is_array($this->value) && count($this->value) === 1) {
      $this->value = reset($this->value);
    }

    return $return;
  }

  /**
   * {@inheritdoc}
   */
  public function query() {
    $this->ensure_my_table();

    // Figure out what this entity id is called (eg. nid, uid, etc.)
    $entity_info = entity_get_info($this->entity_type);
    $id_key = $entity_info['entity keys']['id'];

    $ids = array();
    foreach ($this->value as $value) {
      list($name, $display) = explode(':', $value, 2);

      if ($name && $display) {
        // Get the results of the specified view/display combo.
        $results = views_get_view_result($name, $display);
        foreach ($results as $result) {
          $ids[$result->{$id_key}] = $result->{$id_key};
        }
      }
    }

    // Apply filter if selected views return some results.
    if ($ids) {
      $ids = array_values($ids);
      $this->query->add_where($this->options['group'], $this->table_alias . '.' . $id_key, $ids, $this->operator);
    }
    // Prevent any results display if selected views return empty result.
    elseif ($this->operator === 'in') {
      $this->query->add_where_expression($this->options['group'], '1 = 2');
    }
  }

}
