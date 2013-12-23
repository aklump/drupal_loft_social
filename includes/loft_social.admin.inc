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

  $form['facebook']['og'] = array(
    '#type' => 'fieldset',
    '#title' => t('Open Graph'),
    '#description' => t('Learn more about <a href="!url">Open Graph</a> on the web or manage your <a href="!url2">Open Graph metatags</a>.', array(
      '!url' => url('http://ogp.me/'), 
      '!url2' => url(LOFT_SOCIAL_URL_OG_SETTINGS), 
    )), 
    '#collapsible' => TRUE,
    '#collapsed' => TRUE,
    '#weight' => 10, 
  );

  // og:image
  $image_local = loft_social_og_image_uri(FALSE);
  $image_published = loft_social_og_image_uri();
  $collapsed = (bool) $image_local;


  $form['facebook']['image'] = array(
    '#type' => 'fieldset',
    '#title' => t('Image'),
    // '#description' => t('By uploading an image here, you will effectively lock all <a href="!url">global image metatags</a> fields rendering them unchangeable.', array(
    //   '!url' => url(LOFT_SOCIAL_URL_OG_SETTINGS . '/global', array(
    //       'query' => drupal_get_destination(), 
    //   )), 
    // )),
    '#collapsible' => TRUE,
    '#collapsed' => $collapsed,
    '#weight' => 5, 
  );

  // Upload og:image
  $form['#attributes'] = array('enctype' => "multipart/form-data");

  // Show the current image
  if ($image_local) {
    $form['facebook']['image']['image_local'] = array(
      '#prefix' => t('<h3>Current default <code>og:image</code></h3><p>@path</p>', array('@path' => $image_published)), 
      '#theme' => 'image', 
      '#path' => $image_local, 
      '#title' => t('Default og:image'), 
    );
    $form['facebook']['image']['delete_og_image'] = array(
      '#type' => 'checkbox',
      '#title' => t('Delete the current image.'),
      '#default_value' => FALSE,
    );        
    $form['facebook']['image']['image'] = array(
      '#prefix' => t('<h3>What the World Sees</h3><p>If you the second image is missing or incorrect, then the <code>og:image</code> metatag does not point to the image file.</p>'), 
      '#theme' => 'image', 
      '#path' => $image_published, 
      '#title' => t('Default og:image'), 
      //'#suffix' => '<p>' . check_plain($image) . '</p>', 
    );
  }

  $form['facebook']['image']['loft_social_og_image_style'] = array(
    '#type' => 'select',
    '#title' => t('Image style'),
    '#default_value' => variable_get('loft_social_og_image_style', LOFT_SOCIAL_OG_IMAGE_STYLE),
    '#options' => image_style_options(),
  );

  $form['facebook']['image']['loft_social_og_image'] = array(
    '#type' => 'file',
    '#title' => $image_local ? t('Replace with a new image') : t('Select your global fallback image'),
    '#description' => 'An image which should represent your object within the graph', 
    '#size' => 40,
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
      '#markup' => t('<p>Manage your <a href="!url2">facebook settings</a> and your <a href="!url">preset(s)</a>. Review the <a target="_blank" href="!url3">Open Graph Object Debugger</a> for your homepage.</p>', array (
        '!url' => url(LOFT_SOCIAL_URL_FB_PRESETS, array(
          'query' => drupal_get_destination(), 
        )), 
        '!url2' => url(LOFT_SOCIAL_URL_FB_SETTINGS, array(
          'query' => drupal_get_destination(), 
        )), 
        '!url3' => url('https://developers.facebook.com/tools/debug/og/object', array(
          'query' => array(
            'q' => loft_social_base_url(), 
          ),
          'attributes' => array('_target' => 'blank'),
        ))
      )),
    );
  }
  else {
    $form['facebook']['manage'] = array(
      '#markup' => t('<p class="error">Please <a href="!url">create</a> at least one Facebook like preset.</p>', array (
        '!url' => url(LOFT_SOCIAL_URL_FB_PRESETS . '/add', array(
          'query' => drupal_get_destination(), 
        )), 
      )),
    );
  }

  // if (1) {
  //   $form['facebook']['og']['manage'] = array(
  //     '#markup' => t('<p class="error"><strong>og:type:</strong> Please <a href="!url">choose</a> an Open Graph default type for your website.</p>', array (
  //       '!url' => url(LOFT_SOCIAL_URL_OG_SETTINGS, array(
  //         'query' => drupal_get_destination(), 
  //       )), 
  //     )),
  //   );
  // }

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
      '#rows' => 10,
      '#attributes' => array(
        'readonly' => 'readonly', 
      ),
      '#resizable' => TRUE,
    );
  }  

  $form = system_settings_form($form);
  $form['#submit'][] = 'loft_social_settings_submit';
  $form['#submit'][] = 'loft_social_form_fb_social_admin_settings_form_submit';
  
  return $form;
  
}

/**
 * Form validation handler for loft_social_settings().
 *
 * @see loft_social_settings()
 * @see loft_social_settings_submit()
 */
function loft_social_settings_validate($form, &$form_state) {
  // An image URL which should represent your object within the graph. The
  // image must be at least 50px by 50px and have a maximum aspect ratio of
  // 3:1. We support PNG, JPEG and GIF formats.
  $fid = NULL;
  if (($file = file_save_upload('loft_social_og_image', array(
    'file_validate_is_image' => array(),
    'file_validate_image_resolution' => array(0, variable_get('loft_social_og_image_min', LOFT_SOCIAL_OG_IMAGE_MIN)),
  ))) === NULL) {
    $fid = variable_get('loft_social_og_image', NULL);  
  }
  else {
    $dir = 'public://loft-social/og/';
    file_prepare_directory($dir, FILE_CREATE_DIRECTORY);
    $public = $dir . preg_replace('/.*(\.[^\.]+$)/', 'global\1', $file->filename);
    $file->status = FILE_STATUS_PERMANENT;
    $file = file_move($file, $public, FILE_EXISTS_REPLACE);
    $fid = $file->fid;
    image_path_flush($file->uri);
  }

  // if (empty($form_state['values']['delete_og_image']) && !$fid) {
  //   form_set_error('loft_social_og_image', t('A default fallback image is required.'));
  // }

  form_set_value($form['facebook']['image']['loft_social_og_image'], $fid, $form_state);
}

/**
 * Form submission handler for loft_social_settings().
 *
 * @see loft_social_settings()
 * @see loft_social_settings_validate()
 */
function loft_social_settings_submit($form, &$form_state) {
  if (!empty($form_state['values']['delete_og_image'])) {
    if (($file = file_load($form_state['values']['loft_social_og_image']))
      && file_delete($file)) {
      variable_del('loft_social_og_image');
      drupal_set_message(t("The default image has been deleted."), 'status', FALSE);
    }
  }
}