<?php
/**
 * Class GalaxyToolshed
 * ================================
 * A base class to collect necessary data for interacting with toolshed.
 *
 * @file GalaxyToolshed/GalaxyToolshed.php
 */
class GalaxyToolshed {
  protected $owner;
  protected $key;
  protected $tool_shed_url;

  public function __construct($toolshed_url, $owner, $key) {
    $this->tool_shed_url = $toolshed_url;
    $this->owner = $owner;
    $this->key = $key;
  }
}