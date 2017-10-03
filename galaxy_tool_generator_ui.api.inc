<?php

/**
 *
 */
function get_galaxy_tools() {
  // create galaxy_tools directory if it doesn't exist.
  $galaxy_tools_directory = 'public://galaxy_tools/';
  file_prepare_directory($galaxy_tools_directory, FILE_CREATE_DIRECTORY);
  // get all galaxy tools names by scanning the galaxy_tools directory.
  $directories_in_galaxy_tools = scandir($galaxy_tools_directory);
  // remove '.' an '..' directories.
  $all_galaxy_tools = [];
  foreach ($directories_in_galaxy_tools as $directory) {
    if (!in_array($directory, ['.', '..'])) {
      $all_galaxy_tools[] = $directory;
    }
  }
  // convert $all_galaxy_tools to a non-associative array.
  $all_galaxy_tools = array_values($all_galaxy_tools);
  return $all_galaxy_tools;
}