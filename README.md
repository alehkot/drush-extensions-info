Drush Extensions Info
=====================

A Drush plugin to recursively scan sub-directories for .info files and output the information from these files in variety of formats: Table, CSV, Yaml, XML, etc.
Useful to quickly determine which modules were used in a project.
drush pm-list command requires installed and configured Drupal website, which might not be an option in some cases.
This plugin doesn't have this limitation.

Installation procedure is the same as for other Drush plugins and commands: just clone the repository and copy the contents to ~/.drush folder (on Windows, C:\Users\\[Username]\\.drush).

## Usage ##
*Basic usage*
Go to any directory, which contains sub-folders with Drupal .info files, e.g. "sites/all" and execute the following statement:

`drush extensions_info`

*Export in YAML-format*

`drush extensions_info --format=YAML > output.yml`
