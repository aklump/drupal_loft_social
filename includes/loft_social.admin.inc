<?php
/**
 * @file
 * Admin functions
 *
 * @ingroup loft_social
 * @{
 */

/**
 * Form builder for the loft_social_settings form.
 *
 * Admin settings for the module.
 *
 * @param array $form
 * @param array &$form_state
 *
 * @see loft_social_settings_validate()
 * @see loft_social_settings_submit()
 * @ingroup forms
 */
function loft_social_settings($form, &$form_state) {

  $form['loft_social_placement'] = array(
    '#type' => 'radios',
    '#title' => t('Placement of page-linked Like, Tweet buttons'),
    '#default_value' => variable_get('loft_social_placement', LOFT_SOCIAL_PLACEMENT),
    '#options' => array(
      0 => t('<em>Do not render</em>'),
      1 => t('Before the Page Title on Every Non-Admin Page'), 
      2 => t('After the Page Title on Every Non-Admin Page'), 
      3 => t('Node Links'), 
      4 => t('Node Content'), 
    ),
  );

  if ($data = fb_social_get_presets_by_type('like')) {
    $options = array();
    foreach ($data as $value) {
      $options[$value->name] = $value->description;
    }
    $form['loft_social_fb_preset_like'] = array(
      '#type' => 'select',
      '#title' => t('Preset to use or Facebook Like button(s)'),
      '#default_value' => variable_get('loft_social_fb_preset_like', reset($options)),
      '#options' => $options,
    );  
  }
  else {
    $form['loft_social_fb_preset_like'] = array(
      '#markup' => t('Please <a href="!url">create</a> at least one Facebook like preset.', array(
        '!url' => url('admin/structure/fbsocial/presets/add', array(
          'query' => drupal_get_destination(), 
        )), 
      )),
    );
  }
  
  $vars = array(
    '!url' => url('admin/structure/block', array(
      'query' => drupal_get_destination(), 
    )),
  );

  $form['loft_social_block_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of page-linked blocks to provide?'),
    '#description' => t('This many blocks of page links will be <a href="!url">available</a> for placement by region.', $vars), 
    '#default_value' => variable_get('loft_social_block_count', LOFT_SOCIAL_BLOCK_COUNT),
    '#options' => drupal_map_assoc(range(0, 15)),
  );

  $form['loft_social_block_count_website'] = array(
    '#type' => 'select',
    '#title' => t('Number of website-linked blocks to provide?'),
    '#description' => t('This many blocks of website links (no matter where they are in your site the like, tweet, etc buttons will all point to the website homepage) will be <a href="!url">available</a> for placement by region.', $vars), 
    '#default_value' => variable_get('loft_social_block_count_website', LOFT_SOCIAL_BLOCK_COUNT_WEBSITE),
    '#options' => drupal_map_assoc(range(0, 15)),
  );

  return system_settings_form($form);
}

/**
 * Form validation handler for loft_social_settings().
 *
 * @see loft_social_settings()
 * @see loft_social_settings_submit()
 */
function loft_social_settings_validate($form, &$form_state) {
  $values = $form_state['values'];

  #if ($values['name'] == '') {
  #  form_set_error('', t('You must select a name for this group of settings.'));
  #}
}

/**
 * Form submission handler for loft_social_settings().
 *
 * @see loft_social_settings()
 * @see loft_social_settings_validate()
 */
function loft_social_settings_submit($form, &$form_state) {

  //Drupal 7 Multistep
  //$form_state['rebuild'] = TRUE;
  //Add carryover values here...
  //$form_state['storage'] = array('key' => 'value');

  //one of these needs to answer where this form goes
  //$form_state['redirect'] = array('user/register', $query);
  //$form_state['redirect'] = 'user/register'
}
