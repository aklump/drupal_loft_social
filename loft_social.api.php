<?php
/**
 * @file
 * api functions
 *
 * @ingroup loft_social
 * @{
 */

/**
 * Plug your module into loft_social.
 *
 * If you are generating a social-related element such as a block or render
 * array, by sending it through this function, you will hook into loft_social
 * and have access to debugging, disabling and other modules may hook into
 * your element as well.
 *
 * Implement this in your code something like this:
 *
 * @code
 *     if (module_exists('loft_social')) {
 *       loft_social_prepare($arg, __FUNCTION__));
 *     }
 * @endcode
 *
 * @param  mixed $mixed
 *   When loft_social is suspended, $mixed will be emptied to the original
 *   data type so an array will become an empty array, a string an empty string.
 *   If $mixed has properties then instead '#access' will be set to FALSE.
 * @param string $id
 * @param  ...
 */
function loft_social_prepare($mixed, $id) {

}

/**
 * Implements hook_loft_social_prepare().
 *
 * @param  mixed $mixed
 * @param  array $context
 *   - id string An optional identifier for $mixed.
 *   - suspend bool If social items are currently suspended or not.
 *   - original mixed $mixed before any manipulattion by loft_social.
 *   - args array Any additional args send to loft_social_prepare.
 */
function hook_loft_social_prepare(&$mixed, $context) {
  
}

/**
 * Implements hook_loft_social_button_alter().
 *
 * Alter the html content of a social button.
 *
 * @param  array $build The renderable array
 * @param  array $context 
 *   - type: fb_like, tweet
 */
function hook_loft_social_button_alter(&$build, $context) {
  switch ($context['type']) {
    case 'fb_like':
      # code...
      break;
    
    case 'tweet':
      # code...
      break;
  }
}

/**
 * Implements hook_loft_social_show_on_page_alter().
 *
 * Alter when social links are shown by page.
 *
 * @param array &$context
 * - url
 * - access
 */
function hook_loft_social_show_on_page_alter(&$context) {

  // Remove access to the /contact page which otherwise, as a public
  // page would receive the page-based links.
  if ($context['url'] === 'contact') {
    $context['access'] = FALSE;
  }

  // Or you can leverage drupal_match_path...
  if (drupal_match_path($context['url'], implode("\n", array(
    'user/*/*',
  )))) {
    $context['access'] = FALSE;
  }  
}

/**
 * Implements hook_loft_social_page_images_alter().
 *
 * @param  array &$files An array of image file arrays with at least 'uri' key of
 * images for for this page.  These images will be added to the page as multiple
 * og:image and so forth as appropriate.
 * @param  array $context
 * - path: The unaliased path
 * - node: If a node is associated with this page; same as menu_get_object()
 * - style: An image style to be applied to all uris if possible or FALSE
 */
function hook_loft_social_page_images_alter(&$files, $context) image file {
  // @todo
}


/**
 * Alter metatags before being cached.
 *
 * This hook is invoked prior to the meta tags for a given page are cached.  It 
 * differs from hook_metatag_metatags_view_alter in that it includes the path
 * and the node if available so you have more context.
 *
 * @param  array &$files An array of image file arrays with at least 'uri' key of
 * images for for this page.  These images will be added to the page as multiple
 * og:image and so forth as appropriate.
 * @param  array $context
 * - path: The unaliased path
 * - node: If a node is associated with this page; same as menu_get_object()
 * - style: An image style to be applied to all uris if possible or FALSE
 *
 * @see hook_metatag_metatags_view_alter().
 */
function hook_loft_social_metatags_alter(&$output, $context) {
  if (isset($output['description']['#attached']['drupal_add_html_head'][0][0]['#value'])) {
    $output['description']['#attached']['drupal_add_html_head'][0][0]['#value'] = 'O rly?';
  }
}