
CONTENTS OF THIS FILE
---------------------

 * Introduction
 * Installation
 * Usage


INTRODUCTION
------------

Current Maintainer: The White House <https://drupal.org/u/whitehouse>

This module provides a form (with a block implementation) for posting signatures
to a petitions <https://drupal.org/project/petitions> website like the White
House's "We the People" <https://petitions.whitehouse.gov/> application.


INSTALLATION
------------

Petitions Signature Form requires version 2.x of the Libraries module
<https://drupal.org/project/libraries>, and it needs the Petitions PHP SDK
<https://github.com/WhiteHouse/petitions-php-sdk/> installed at
sites/all/libraries/petitions-php-sdk. The module itself is installed in the
usual way. See http://drupal.org/documentation/install/modules-themes/modules-7.
It must be configured at admin/config/services/petitionssignatureform to talk to
a Petitions <https://drupal.org/project/petitions> API endpoint.


USAGE
-----

A Petitions signature form can be placed on your site via the provided
"Petitions signature form" block or programmatically in PHP:

 * Place the "Petitions signature form" block as you would any other, e.g., via
   the core Blocks interface at admin/structure/block or using Panels
   <https://drupal.org/project/panels> or Context
   <https://drupal.org/project/context>. You must configure the block to know
   where to get the ID of the petition it should sign or it will present a
   "Petition ID" field to the end user.

 * Place the form programmatically using code like the following in your module
   or theme:

   <?php
   $form = drupal_get_form('petitionssignatureform_signature_form', $petition_id);
   print drupal_render($form);
   ?>
