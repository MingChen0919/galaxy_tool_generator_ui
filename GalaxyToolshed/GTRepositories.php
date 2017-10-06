<?php

/**
 * class GTRepositories
 * ============================
 * provides methods to interact with Galaxy Toolshed repositories
 *
 * info:
 * Many methods use {encoded_repository_id} as parameter. The Toolshed API documentation
 * does not have much information about this. I figured out that the {encoded_repository_id}
 * is the id that can be obtained by running the GTRepositories->index() method.
 */
class GTRepositories extends GalaxyToolshed {

  public function add_repository_registry_entry($repository_name = '') {
    $endpoint = '/api/repositories/add_repository_registry_entry';
    $data = [
      'key' => $this->key,
      'tool_shed_url' => $this->tool_shed_url,
      'name' => $repository_name,
      'owner' => $this->owner,
    ];
    return GalaxyToolshedRequest::post($endpoint, $data);
  }

  /**
   * @param string $name The name of the repository
   *
   * @return array An array of installable revisions of the repository.
   */
  public function get_ordered_installable_revisions($name) {
    $endpoint = '/api/repositories/get_ordered_installable_revisions';
    $data = [
      'name' => $name,
      'owner' => $this->owner,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param string $name The name of the repository
   * @param string $changeset_revision The changeset_revision of the
   *   RepositoryMetadata object associated with the Repository
   *
   * @return mixed
   */
  public function get_repository_revision_install_info($name, $changeset_revision) {
    $endpoint = '/api/repositories/get_repository_revision_install_info';
    $data = [
      'name' => $name,
      'owner' => $this->owner,
      'changeset_revision' => $changeset_revision,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param string $tsr_id The encoded toolshed ID of the repository.
   *
   * @return mixed
   */
  public function get_installable_revisions($tsr_id) {
    $endpoint = '/api/repositories/get_installable_revisions';
    $data = [
      'tsr_id' => $tsr_id,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param string $capsule_file_name The name of the capsule file.
   *
   * @return mixed
   */
  public function import_capsule($capsule_file_name) {
    $endpoint = '/api/repositories/new/import_capsule';
    $data = [
      'key' => $this->key,
      'tool_shed_url' => $this->tool_shed_url,
      'capsule_file_name' => $capsule_file_name,
    ];
    return GalaxyToolshedRequest::post($endpoint, $data);
  }

  /**
   * @param string $q (optional)if present search on the given query will be
   *   performed
   * @param int $page (optional)requested page of the search
   * @param int $page_size (optional)requested page_size of the search
   * @param bool $jsonp (optional)flag whether to use jsonp format response,
   *   defaults to False
   * @param string $callback (optional)name of the function to wrap callback in
   *   used only when jsonp is true, defaults to ‘callback’
   * @param bool $deleted (optional)displays repositories that are or are not
   *   set to deleted.
   * @param string $owner The owner's public username.
   * @param string $name (optional)the repository name.
   *
   * @return mixed
   */
  public function index($q = '', $page = 10, $page_size = 10, $jsonp = TRUE, $callback = '', $deleted = FALSE, $owner = '', $name = '') {
    $endpoint = '/api/repositories';
    $data = array_filter([
      'q' => $q,
      'page' => $page,
      'page_size' => $page_size,
      'jsonp' => $jsonp,
      'callback' => $callback,
      'deleted' => $deleted,
      'owner' => $owner,
      'name' => $name,
    ]);
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param $name the name of the Repository.
   *
   * @return mixed
   */
  public function remove_repository_registry_entry($name) {
    $endpoint = '/api/repositories/remove_repository_registry_entry';
    $data = [
      'key' => $this->key,
      'tool_shed_url' => $this->tool_shed_url,
      'name' => $name,
      'owner' => $this->owner,
    ];
    return GalaxyToolshedRequest::post($endpoint, $data);
  }

  /**
   * @param bool $my_writable (optional): if the API key is associated with an
   *   admin user in the Tool Shed, setting this param value.
   *
   * @return mixed display an array of repository ids ordered for setting
   *   metadata.
   */
  public function repository_ids_for_setting_metadata($my_writable = FALSE) {
    $endpoint = '/api/repository_ids_for_setting_metadata';
    $data = [
      'key' => $this->key,
      'my_writable' => $my_writable,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param bool $my_writable (optional): if the API key is associated with an
   *   admin user in the Tool Shed, setting this param value.
   *
   * @return mixed
   */
  public function reset_metadata_on_repositories($my_writable = FALSE) {
    $endpoint = '/api/repositories/reset_metadata_on_repositories';
    $data = [
      'key' => $this->key,
      'my_writable' => $my_writable,
    ];
    return GalaxyToolshedRequest::put($endpoint, $data);
  }

  /**
   * @param string $repository_id the encoded id of the repository on which
   *   metadata is to be reset.
   *
   * @return mixed
   */
  public function reset_metadata_on_repository($repository_id) {
    $endpoint = '/api/repositories/reset_metadata_on_repository';
    $data = [
      'key' => $this->key,
      'repository_id' => $repository_id,
    ];
    return GalaxyToolshedRequest::put($endpoint, $data);
  }

  /**
   * @param string $encoded_repository_id the encoded id of the Repository
   *   object
   *
   * @return mixed
   */
  public function show($encoded_repository_id) {
    $endpoint = '/api/repositories/' . $encoded_repository_id;
    $data = [
      'id' => $encoded_repository_id,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param string $name name of the repository
   * @param string $changeset_revision changeset of the repository
   * @param null $hexlify flag whether to hexlify the response (for backward
   *   compatibility)
   *
   * @return mixed
   */
  public function updates($name, $changeset_revision, $hexlify = NULL) {
    $endpoint = '/api/repositories/updates';
    $data = [
      'owner' => $this->owner,
      'name' => $name,
      'changeset_revision' => $changeset_revision,
      'hexlify' => $hexlify,
    ];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * TODO: documentation about this API is not available.
   *
   * @return mixed
   */
  public function show_tools() {
    $endpoint = '';
    $data = [];
    return GalaxyToolshedRequest::get($endpoint, $data);
  }

  /**
   * @param string $encoded_repository_id the encoded id of the Repository
   *   object
   *
   * @return mixed
   */
  public function metadata($encoded_repository_id) {
    $endpoint = '/api/repositories/' . $encoded_repository_id . '/metadata';
    return GalaxyToolshedRequest::get($endpoint);
  }

  /**
   * // TODO: implement PATCH request.
   *
   * @param string $encoded_repository_id the encoded id of the Repository
   *   object
   * @param string $name repo’s name (optional)
   * @param string $synopsis repo’s synopsis (optional)
   * @param string $description repo’s description (optional)
   * @param string $remote_repository_url repo’s remote repo (optional)
   * @param string $homepage_url repo’s homepage url (optional)
   * @param array $category_ids list of existing encoded TS category ids
   *
   * @return mixed
   */
  public function update($encoded_repository_id, $name = '', $synopsis = '', $description = '', $remote_repository_url = '', $homepage_url = '', $category_ids = []) {
    $endpoint = '/api/repositories/' . $encoded_repository_id;
    $data = array_filter([
      'id' => $encoded_repository_id,
      'payload' => [
        'name' => $name,
        'synposis' => $synopsis,
        'description' => $description,
        'remote_repository_url' => $remote_repository_url,
        'homepage_url' => $homepage_url,
        'categories_ids' => $category_ids,
      ],
    ]);
    return GalaxyToolshedRequest::patch($endpoint, $data);
  }


  /**
   * @param string $name new repo’s name (required)
   * @param string $synopsis new repo’s synopsis (required)
   * @param string $description new repo’s description (optional)
   * @param string $remote_repository_url new repo’s remote repo (optional)
   * @param string $homepage_url new repo’s homepage url (optional)
   * @param array $category_ids list of existing encoded TS category ids
   * @param string $type new repo’s type, defaults to 'unrestricted' (optional)
   *
   * @return mixed
   */
  public function create($name, $synopsis, $description = '', $remote_repository_url = '', $homepage_url = '', $category_ids = [], $type = 'unrestricted') {
    $endpoint = '/api/repositories/';
    $data = array_filter([
      'key' => $this->key,
      'name' => $name,
      'synopsis' => $synopsis,
      'description' => $description,
      'remote_repository_url' => $remote_repository_url,
      'homepage_url' => $homepage_url,
      'category_ids' => $category_ids,
      'type' => $type,
    ]);
    return GalaxyToolshedRequest::post($endpoint, $data);
  }

  /**
   * @param string $encoded_repository_id the encoded id of the Repository
   *   object
   *
   * @return mixed
   */
  public function create_changeset_revision($encoded_repository_id, $commit_message) {
    $endpoint = '/api/repositories/' . $encoded_repository_id . '/changeset_revision';
    $data = array_filter([
      'id' => $encoded_repository_id,
      'commit_message' => $commit_message,
    ]);
    return GalaxyToolshedRequest::post($endpoint, $data);
  }
}