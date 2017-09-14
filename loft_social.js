/**
 * @file
 * The main javascript file for loft_social
 *
 * @ingroup loft_social
 */
(function ($, Drupal, window, document, undefined) {
  "use strict";

  Drupal.loftSocial = {};

  /**
   * Compute the point that causes part to be centered in full.
   *
   * @param  {int} full The larger distance (container).
   * @param  {int} part The smaller distance
   *
   * @return {int}
   */
  function center(full, part) {
    return full / 2 - part / 2;
  }

  /**
   * Return data for simulating social service popups.
   *
   * @type {Object}
   *   - Keyed by service id
   *   - Values are
   *     - height
   *     - left
   *     - top
   *     - width
   *
   * @see Drupal.loftSocial.popup
   * @link https://dev.twitter.com/web/intents
   */
  Drupal.loftSocial.popups = {
    facebook: {
      height: 290,
      left: center(screen.width, 670),
      top: center(screen.height, 290),
      width: 670
    },
    twitter: {
      height: 420,
      left: center(screen.width, 550),
      top: center(screen.height, 420),
      width: 550
    },
    pinterest: {
      height: 380,
      left: 0,
      top: 0,
      width: 535
    },
    google_classroom: {
      height: 595,
      left: 0,
      top: 0,
      width: 640
    }
  };

  /**
   * Open up a new social-based window to mimick standard services.
   *
   * @param  {object} popup
   *   - height
   *   - left
   *   - top
   *   - width
   * @param  {string} href
   * @param  {string} title
   */
  Drupal.loftSocial.popup = function (popup, href, title) {
    window.open(href, title, "status=0,toolbar=0,location=1,menubar=0,directories=0,resizable=1,scrollbars=1,left=" + popup.left + ",top=" + popup.top + ",height=" + popup.height + ",width=" + popup.width);
  };

  Drupal.behaviors.loftSocial = {};
  Drupal.behaviors.loftSocial.attach = function () {
    $('.loft-social-is-popup-ready').each(function () {
      var _ = this;
      $(_).removeClass('loft-social-is-popup-ready');
      var service = $(_).data('loft-social-service');
      if (service) {
        var title = $(_).data('loft-social-title');
        var popup = Drupal.loftSocial.popups[service];
        var href = $(_).attr('href');

        $(_).click(function (e) {
          Drupal.loftSocial.popup(popup, href, title);
          e.preventDefault();
        });
      }
    });
  };

})(jQuery, Drupal, window, document, undefined);
