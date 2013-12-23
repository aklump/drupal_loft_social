<?php
/**
 * @file
 * api functions
 *
 * @ingroup loft_social
 * @{
 */

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