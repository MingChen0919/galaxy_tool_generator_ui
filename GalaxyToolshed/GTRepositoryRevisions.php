<?php

/**
 * class GTRepositories
 * ============================
 * provides methods to interact with Galaxy Toolshed repository revisions.
 */

class GTRepositoryRevisions extends GalaxyToolshed {

  /**
   * @param string $name the name of the Repository
   * @param string $changeset_revision the changeset_revision of the
   *   RepositoryMetadata object associated with the Repository
   * @param bool $export_repository_dependencies (optional): whether to export
   *   repository dependencies - defaults to False
   * @param string $download_dir (optional): the local directory to which to
   *   download the archive - defaults to /tmp
   */
  public function export($name, $changeset_revision, $export_repository_dependencies = FALSE, $download_dir = '/temp') {
    $endpoint = '/api/repository_revisions/export';
    $data = array_filter([
      'tool_shed_utl' => $this->tool_shed_url,
      'name' => $name,
      'owner' => $this->owner,
      'changeset_revision' => $changeset_revision,
      'export_repository_dependencies' => $export_repository_dependencies,
      'download_dir' => $download_dir,
    ]);
  }
}