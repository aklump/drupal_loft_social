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