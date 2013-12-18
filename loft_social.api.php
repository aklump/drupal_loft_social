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