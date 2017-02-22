
Description:
------------
This module extends the webform module to easily allow submitting a webform 
to Salesforce.com.  It utilizes the Salesforce API, which must be downloaded
separately from the module.  In order to use the Salesforce API, your
Salesforce installation must be either the Enterprise, Ultimate, or Developer
editions.

The Salesforce API Toolkit can be downloaded freely from
http://wiki.apexdevnet.com/index.php/Web_Services_API#PHP
under the 'Toolkit' listing.  Make sure you follow the instructions on the
project page or the INSTALL.TXT file very closely to make sure the API is 
installed correctly.

The Salesforce Webform module does require PHP with SOAP enabled.  The Drupal
7 version of Salesforce Webform utilizes Webform 3.x.

If you are having issues with blank screens or errors on form submissions,
as a first troubleshooting step, make sure you have entered the correct
username and password + Security Token combination on the administration
page.

This module was originally sponsored by by Davis Applied Technology College, 
http://www.datc.edu.  

The port of this module to Drupal 7 and compatibility with Webform 3.x (both 
D6 and D7) was sponsored by Aktana, http://www.aktana.com
.
The module was programmed by Obsidian Design LLP, 
http://www.obsidiandesign.com.

The module is based, in part, on the sugarwebform module.