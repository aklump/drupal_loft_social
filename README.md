# Drupal Module: Loft Social Manager
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

## Summary
**This module provides extra help for using social media links in Drupal**

It provides a set of social buttons that can be placed in your website in several ways: on all public pages, on all node pages as part of node content or node links, or as one or more blocks placed in regions.  It's up to you to decide how you'd like to use it.

### Facebook
This module leverages the [Facebook Social][fb_social] and provides a default like preset.  It also leverages the [Metatag][metatag] modules and overrides form values and metatags to increase the likelihood that you are setup correctly for Facebook.  It insures that the following values in your html source on the front page match exactly.

1. og:url
2. shortlink
3. canonical

Furthermore, it makes sure you use `http` instead of `https` for your social page links.

#### Image
Upload an image to have the og:image and image_url metatags handled for you.  Delete your image and you can modify these fields in the metatag module as expected.


### Twitter
* This module works hand-in-hand with [On the Web][on_the_web] to create a tweet button from the account you've entered in On the Web.
* If you enable [Shorten URLs][shorten], twitter links will be shortened using the chosen service.

## Installation/Configuration
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.
1. Visit `admin/structure/fbsocial` and set your _Facebook application id_ and _Base URL_ and submit the form.
1. Visit `admin/config/services/loft-social` and review/alter/submit the settings form.

1. Set your twitter url in the On the Web settings form.
1. Return to the module settings page and copy the text at the bottom of the form and paste into `settings.php` if you wish to disable the ability for admins to change these settings (a good idea once you start getting like counts, etc.)

## API
1. Get the current page url for sharing links, Twitter, Facebook, etc. using `loft_social_url()`.

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
[metatag]: https://drupal.org/project/metatag