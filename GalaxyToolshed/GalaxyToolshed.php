<?php
/**
 * Class GalaxyToolshed
 * ================================
 * Provides methods to interact with Galaxy toolshed.
 *
 * @file GalaxyToolshed/GalaxyToolshed.php
 */
class GalaxyToolshed {
  protected $key;

  public function __construct() {
    $this->key = '6650626edf6ef75b2ed1fbf21141a660';

    dpm(GalaxyToolshedRequest::get('/api/repositories/get_repository_revision_install_info', [
        'name' => 'test_galaxy_tool_generator',
        'owner' => 'mingchen0919',
        'changeset_revision' => '20bc2025c2ea',
    ]));
  }

}