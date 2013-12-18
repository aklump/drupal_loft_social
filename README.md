# Drupal Module: Module Name
**Author:** Aaron Klump  <sourcecode@intheloftstudios.com>

##Summary
**This module overrides form values and metatags to increase the likelihood that you are setup correctly for Facebook and other social plugins.**

##Installation/Configuration
1. Install as usual, see [http://drupal.org/node/70151](http://drupal.org/node/70151) for further information.
1. You must submit the form at `admin/structure/fbsocial` at least once for this module to do it's magic.
2. After submitting, copy the text at the bottom of the form and paste into `settings.php`.

## API

1. You program your social services using the module settings of [On the Web][on_the_web] and you can programatically obtain a service name using `loft_social_get_name()`.  As an example, to set your Twitter name, which is used by the tweet button visit `admin/config/services/on_the_web` and enter your twitter url.



## Design Decisions/Rationale
To encapsulate a common pattern in a module. This modules insures that the following values in your html source on the front page match exactly.

1. og:url
2. shortlink
3. canonical

Furthermore, it makes sure you use http instead of https for the above.

##Contact
* **In the Loft Studios**
* Aaron Klump - Developer
* PO Box 29294 Bellingham, WA 98228-1294
* _aim_: theloft101
* _skype_: intheloftstudios
* _d.o_: aklump
* <http://www.InTheLoftStudios.com>

[on_the_web]: https://drupal.org/project/on_the_web