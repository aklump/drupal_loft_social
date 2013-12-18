# Drupal Module: Loft Social Extras
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

## Summary
**This module provides extra help for using social media links in Drupal**

It provides a set of social buttons that can be placed in your website in several ways: on all public pages, on all node pages as part of node content or node links, or as one or more blocks placed in regions.  It's up to you to decide how you'd like to use it.

### Facebook
This module leverages [Facebook Social][fb_social] module and overrides form values and metatags to increase the likelihood that you are setup correctly for Facebook.  It insures that the following values in your html source on the front page match exactly.

1. og:url
2. shortlink
3. canonical

Furthermore, it makes sure you use http instead of https for your social page links.

### Twitter
* This module works hand-in-hand with [On the Web][on_the_web] to create a tweet button from the account you've entered in On the Web.
* If you enable [Shorten URLs][shorten], twitter links will be shortened using the chosen service.

## Installation/Configuration
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.
1. This module needs a fb_social like preset, so if you haven't created one, do so now.
1. Set your twitter url in the On the Web settings form.
1. Now, set Base URL at `admin/structure/fbsocial` and this module will do it's magic.
1. Return to the module settings page and copy the text at the bottom of the form and paste into `settings.php`.

## API

1. You program your social services using the module settings of [On the Web][on_the_web] and you can programatically obtain a service name using `loft_social_get_name()`.  As an example, to set your Twitter name, which is used by the tweet button visit `admin/config/services/on_the_web` and enter your twitter url.



## Design Decisions/Rationale
To encapsulate a common pattern in a module. 

## Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>

[on_the_web]: https://drupal.org/project/on_the_web
[shorten]: https://drupal.org/project/shorten
[fb_social]: https://drupal.org/project/fb_social