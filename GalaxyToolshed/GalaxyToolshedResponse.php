<?php
/**
 * Provides a response interface for HTTP request.
 */
class GalaxyToolshedResponse {
  public $toolshed_base_url = '';
  public $endpoint = '';

  /**
   * Create a GET request
   *
   * @param string $tool_shed_base_url
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function get($tool_shed_base_url, $endpoint, $data = NULL) {
    return static::send('GET', $tool_shed_base_url, $endpoint, $data);
  }

  /**
   * Create a POST request
   *
   * @param string $tool_shed_base_url
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function post($tool_shed_base_url, $endpoint, $data = NULL) {
    return static::send('GET', $tool_shed_base_url, $endpoint, $data);
  }

  /**
   * Create a DELETE request
   *
   * @param string $tool_shed_base_url
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function delete($tool_shed_base_url, $endpoint, $data = NULL) {
    return static::send('GET', $tool_shed_base_url, $endpoint, $data);
  }

  /**
   * Create a PUT request
   *
   * @param string $tool_shed_base_url
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function put($tool_shed_base_url, $endpoint, $data = NULL) {
    return static::send('GET', $tool_shed_base_url, $endpoint, $data);
  }

  /**
   * Create a curl HTTP request.
   */
  public static function send($method, $toolshed_base_url, $endpoint, $data = NULL) {

  }
}