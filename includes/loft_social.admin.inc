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

  $form['twitter'] = array(
    '#type' => 'fieldset',
    '#title' => t('Twitter'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );
  if (!module_exists('shorten')) {
    $form['twitter']['shorten'] = array(
      '#markup' => t('<span class="error">You should enable the <a href="!url">Shorten URLS module</a> to get short URLS for some services such as Twitter.</span>', array(
        '!url' => url('https://drupal.org/project/shorten'), 
      )),
    );
  }

  $form['twitter']['manage'] = array(
    '#markup' => t('Manage your twitter account <a href="!url">here.</a>', array(
      '!url' => url(LOFT_SOCIAL_URL_OTW_SETTINGS, array(
        'query' => drupal_get_destination(), 
      )),
    )),
  );

  $form['facebook'] = array(
    '#type' => 'fieldset',
    '#title' => t('Facebook'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  if ($data = fb_social_get_presets_by_type('like')) {
    $options = array();
    foreach ($data as $value) {
      $options[$value->name] = $value->description;
    }
    $form['facebook']['loft_social_fb_preset_like'] = array(
      '#type' => 'select',
      '#title' => t('Preset to use for  the Facebook Like button(s)'),
      '#default_value' => variable_get('loft_social_fb_preset_like', reset($options)),
      '#options' => $options,
    );

    $form['facebook']['manage'] = array(
      '#markup' => t('Manage your facebook <a href="!url2">master settings</a> and your <a href="!url">preset(s)</a>.', array (
        '!url' => url(LOFT_SOCIAL_URL_FB_PRESETS, array(
          'query' => drupal_get_destination(), 
        )), 
        '!url2' => url(LOFT_SOCIAL_URL_FB_SETTINGS, array(
          'query' => drupal_get_destination(), 
        )), 
      )),
    );
  }
  else {
    $form['facebook']['manage'] = array(
      '#markup' => t('<span class="error">Please <a href="!url">create</a> at least one Facebook like preset.</span>', array (
        '!url' => url(LOFT_SOCIAL_URL_FB_PRESETS . '/add', array(
          'query' => drupal_get_destination(), 
        )), 
      )),
    );
  }

  $form['rendering'] = array(
    '#type' => 'fieldset',
    '#title' => t('Placement on Website'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
  );

  $form['rendering']['loft_social_placement'] = array(
    '#type' => 'radios',
    '#title' => t('Page placement of social buttons'),
    '#default_value' => variable_get('loft_social_placement', LOFT_SOCIAL_PLACEMENT),
    '#options' => array(
      0 => t('<em>Hidden</em>'),
      1 => t('Before the Page Title'), 
      2 => t('After the Page Title'), 
      3 => t('Node Links <sup>2</sup>'), 
      4 => t('Node Content <sup>2</sup>'), 
    ),
  );


  // Per-path visibility.
  $form['rendering']['path'] = array(
    '#type' => 'fieldset',
    '#title' => t('Pages'),
    '#collapsible' => TRUE,
    '#collapsed' => FALSE,
    '#group' => 'visibility',
    '#states' => array(
      'visible' => array(
        ':input[name=loft_social_placement]' => array(
          array('value' => 1),
          array('value' => 2),
        ),
      ),
    ),    
  );
  
  $access = user_access('use PHP for settings');
  $page_visibility = variable_get('loft_social_page_visibility', BLOCK_VISIBILITY_NOTLISTED);
  $pages = variable_get('loft_social_pages', LOFT_SOCIAL_PAGES);
  if ($page_visibility == BLOCK_VISIBILITY_PHP && !$access) {
    $form['rendering']['path']['loft_social_page_visibility'] = array(
      '#type' => 'value',
      '#value' => BLOCK_VISIBILITY_PHP,
    );
    $form['rendering']['path']['loft_social_pages'] = array(
      '#type' => 'value',
      '#value' => $pages,
    );
  }
  else {
    $options = array(
      BLOCK_VISIBILITY_NOTLISTED => t('All public pages <sup>1</sup> except those listed'),
      BLOCK_VISIBILITY_LISTED => t('Only the listed pages'),
    );
    $description = t("Specify pages by using their paths. Enter one path per line. The '*' character is a wildcard. Example paths are %blog for the blog page and %blog-wildcard for every personal blog. %front is the front page.", array('%blog' => 'blog', '%blog-wildcard' => 'blog/*', '%front' => '<front>'));

    if (module_exists('php') && $access) {
      $options += array(BLOCK_VISIBILITY_PHP => t('Pages on which this PHP code returns <code>TRUE</code> (experts only)'));
      $title = t('Pages or PHP code');
      $description .= ' ' . t('If the PHP option is chosen, enter PHP code between %php. Note that executing incorrect PHP code can break your Drupal site.', array('%php' => '<?php ?>'));
    }
    else {
      $title = t('Pages');
    }
    $form['rendering']['path']['loft_social_page_visibility'] = array(
      '#type' => 'radios',
      '#title' => t('Show social links on specific pages'),
      '#options' => $options,
      '#default_value' => $page_visibility,
    );
    $form['rendering']['path']['loft_social_pages'] = array(
      '#type' => 'textarea',
      '#title' => '<span class="element-invisible">' . $title . '</span>',
      '#default_value' => $pages,
      '#description' => $description,
    );
  }

  $form['rendering']['weight'] = array(
    '#type' => 'container',
    '#states' => array(
      'visible' => array(
        ':input[name=loft_social_placement]' => array('value' => 4),
      ),
    ),
  );

  $form['rendering']['weight']['loft_social_placement_weight'] = array(
    '#type' => 'weight',
    '#title' => t('Weight'),
    '#description' => t('The lower weight will push this closer to the top in the node content render array.'),
    '#default_value' => variable_get('loft_social_placement_weight', 0),
    '#delta' => 10, //the range is from -1 * delta through delta
  );

  $form['rendering']['footnotes'] = array(
    '#weight' => '100', 
    '#markup' => t('<p><sup>1</sup> Pages are considered public if they are viewable by an anonymous user.</p><p><sup>2</sup> Buttons will not appear on non-node pages.</p>'), 
  );  
  
  $vars = array(
    '!url' => url('admin/structure/block', array(
      'query' => drupal_get_destination(), 
    )),
  );

  $form['rendering']['blocks'] = array(
    '#type' => 'fieldset',
    '#title' => t('Blocks'),
    '#description' => t('Blocks are independent and may be in addition to page placement.'), 
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
  );

  $form['rendering']['blocks']['loft_social_block_count'] = array(
    '#type' => 'select',
    '#title' => t('Number of page-linked blocks to provide?'),
    '#description' => t('This many blocks of page links will be <a href="!url">available</a> for placement by region.', $vars), 
    '#default_value' => variable_get('loft_social_block_count', LOFT_SOCIAL_BLOCK_COUNT),
    '#options' => drupal_map_assoc(range(0, 15)),
  );

  $form['rendering']['blocks']['loft_social_block_count_website'] = array(
    '#type' => 'select',
    '#title' => t('Number of website-linked blocks to provide?'),
    '#description' => t('This many blocks of website links (no matter where they are in your site the like, tweet, etc buttons will all point to the website homepage) will be <a href="!url">available</a> for placement by region.', $vars), 
    '#default_value' => variable_get('loft_social_block_count_website', LOFT_SOCIAL_BLOCK_COUNT_WEBSITE),
    '#options' => drupal_map_assoc(range(0, 15)),
  );

  if ($snippet = _loft_social_settings_snippet()) {
    $form['settings'] = array(
      '#type' => 'textarea',
      '#title' => '<code>settings.php</code> Protected Values', 
      '#description' => t('Once you are satisfied with your configuration, please add this snippet to <code>settings.php</code> to protect your website.'),  
      '#default_value' => $snippet,
      '#rows' => 5,
      '#attributes' => array(
        'readonly' => 'readonly', 
      ),
      '#resizable' => TRUE,
    );
  }  

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
