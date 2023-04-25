Other View Filter
========
<!--
The first paragraph of this file should be kept short as it will be used as the
project summary on BackdropCMS.org. Aim for about 240 characters (three lines at
80 characters each).

All lines in this file should be no more than 80 characters long for legibility,
unless including a URL or example that requires the line to not wrap.
|<- - - - - - - This line is exactly 80 characters for reference - - - - - - ->|

Detail in READMEs should be limited to the minimum required for installation and
getting started. More detailed documentation should be moved to a GitHub wiki
page; for example: https://github.com/backdrop-contrib/setup/wiki/Documentation.
-->

Other View Filter enables you to filter the contents of one view by the
contents of another view. You can either filter by items that exist in the
other view or filter by items that do not exist in the other view.

You may wish to include two view displays on on one page and filter out items
in one view that are included in the other view. Or it may be that you need to
filter a view in a way that cannot be done in a single display.

To minimize the cost to performance of running multiple views queries, the
number of instances of this filter on the same display should be kept to a
minimum and caching should be employed liberally. Using more than 1 view for
filtering will strongly decrease your site performance. To minimize performance
decreasing use simple and cached views.

Usage
---------------------
1. In the view from which you wish exclude or include items, add filter "Other
view result".
2. In the filter criterion screen choose the "View: display" combination you
want to filter by.
3. Select the Operator to:
    - include items from the other view (Is one of);
    - exclude items from the other view (Is not one of);
4. Apply to this display or to all displays.
5. Save the view.

Requirements
------------
<!--
List any dependencies here. Remove this section if not needed.
-->

This module requires that the following modules are also enabled:

- Views (Core - Enabled by default)

Installation
------------
<!--
List the steps needed to install and configure the module. Add/remove steps as
necessary.
-->

- Install this module using the official Backdrop CMS instructions at
  https://docs.backdropcms.org/documentation/extend-with-modules.

Issues
------
<!--
Link to the repo's issue queue.
-->

Bugs and Feature Requests should be reported in the Issue Queue:
https://github.com/backdrop-contrib/other_view_filter/issues.


Credits
-------
- Ported to Backdrop CMS by - [Martin Price](https://github.com/yorkshire-pudding) - [System Horizons](https://www.systemhorizons.co.uk).
- Port sponsored by [System Horizons](https://www.systemhorizons.co.uk).

Current Maintainers
-------------------
<!--
List the current maintainer(s) of the module, and note if this module needs
new/additional maintainers.
-->

- [Martin Price](https://github.com/yorkshire-pudding) - [System Horizons Ltd](https://www.systemhorizons.co.uk)
- Collaboration and co-maintainers welcome!

Credits
-------
<!--
Give credit where credit's due.
If this is a Drupal port, state who ported it, and who wrote the original Drupal
module. If this module is based on another project, or uses third-party
libraries, list them here. You can also mention any organisations/companies who
sponsored the module's development.
-->

- Ported to Backdrop CMS by - [Martin Price](https://github.com/yorkshire-pudding) - [System Horizons Ltd](https://www.systemhorizons.co.uk).
- Port sponsored by [System Horizons Ltd](https://www.systemhorizons.co.uk).
- Originally written for Drupal by [Anton Ivanov](https://www.drupal.org/u/antonnavi).

License
-------
<!--
Mention what license this module is released under, and where people can find
it.
-->

This project is GPL v2 software.
See the LICENSE.txt file in this directory for complete text.