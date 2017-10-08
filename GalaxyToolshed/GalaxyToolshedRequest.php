<?php

/**
 * Provides RESTful HTTP request API.
 *
 * @file GalaxyToolshed/GalaxyToolshedRequest.php
 */
class GalaxyToolshedRequest {

  public static $toolshed_url = 'https://testtoolshed.g2.bx.psu.edu';

  /**
   * Create a GET request
   *
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function get($endpoint, $data = NULL) {
    return static::send('GET', $endpoint, $data);
  }

  /**
   * Create a POST request
   *
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function post($endpoint, $data = NULL) {
    return static::send('POST', $endpoint, $data);
  }

  /**
   * Create a DELETE request
   *
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function delete($endpoint, $data = NULL) {
    return static::send('DELETE', $endpoint, $data);
  }

  /**
   * Create a PUT request
   *
   * @param string $endpoint
   * $param null $data
   *
   * @return mixed
   */
  public static function put($endpoint, $data = NULL) {
    return static::send('PUT', $endpoint, $data);
  }

  /**
   * // TODO: implement PATCH request function.
   *
   * @param string $endpoint
   * @param null $data
   *
   * @return mixed
   */
  public static function patch($endpoint, $data = NULL) {
    return static::send('PATCH', $endpoint, $data);
  }

  /**
   * Create a curl HTTP request.
   *
   * @param string $method One of GET, PUT, POST or DELETE. Must be
   *   capitalized.
   * @param string $endpoint The url to call. If base_url is set, this value
   *   will be appended to base_url.
   * @param null|string|array $data
   *
   * @return mixed
   */
  public static function send($method, $endpoint, $data = NULL) {
    if (!empty(static::$toolshed_url)) {
      $url = static::$toolshed_url . $endpoint;
    }
    $curl = curl_init();
    switch ($method) {
      case "POST":
        curl_setopt($curl, CURLOPT_POST, 1);
        if ($data) {
          curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($data));
        }
        break;
      case "DELETE":
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        if ($data) {
          curl_setopt($curl, CURLOPT_POSTFIELDS, $data);
        }
        break;
      case "PUT":
        curl_setopt($curl, CURLOPT_PUT, 1);
        if ($data) {
          $url = sprintf("%s?%s", $url, http_build_query($data));
        }
        break;
      case "PATCH":
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'PATCH');
        if ($data) {
          curl_setopt($curl, CURLOPT_POSTFIELDS, json_encode($data));
        }
      default:
        if ($data) {
          $url = sprintf("%s?%s", $url, http_build_query($data));
        }
    }
    dpm($url);

    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_HEADER, TRUE);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    //curl_setopt($curl, CURLOPT_HTTPHEADER, ['Accept' => 'application/json']);
    $result = curl_exec($curl);
    $status = intval(curl_getinfo($curl, CURLINFO_HTTP_CODE));
    $header_size = curl_getinfo($curl, CURLINFO_HEADER_SIZE);

    if($status < 200 || $status > 300) {
      throw new Exception("Request to {$url} returned status code: {$status}", $status);
    }

    //dpm(curl_getinfo($curl));
    $result = substr($result, $header_size);
    curl_close($curl);
    return json_decode($result);
  }
}