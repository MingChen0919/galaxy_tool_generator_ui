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
   * @param $method
   * @param $endpoint
   * @param null $data
   *
   * @return mixed
   * @throws \Exception
   */
  public static function send($method, $endpoint, $data = NULL) {
    if (!empty(static::$toolshed_url)) {
      $url = static::$toolshed_url . $endpoint;
    }
    if ($data) {
      $url = sprintf("%s?%s", $url, http_build_query($data));
    }
    $curl = curl_init();
    switch ($method) {
      case "POST":
        curl_setopt($curl, CURLOPT_POST, TRUE);
        if ($data) {
          if ($data['payload']['file']) {
            curl_setopt($curl, CURLOPT_POSTFIELDS, [
              'file' => '@' . realpath($data['payload']['file']),
            ]);
          }
        }
        break;
      case "DELETE":
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, "DELETE");
        break;
      case "PUT":
        curl_setopt($curl, CURLOPT_PUT, 1);
        break;
      case "PATCH":
        curl_setopt($curl, CURLOPT_CUSTOMREQUEST, 'PATCH');
    }

    curl_setopt($curl, CURLOPT_URL, $url);
    curl_setopt($curl, CURLOPT_HEADER, TRUE);
    curl_setopt($curl, CURLOPT_RETURNTRANSFER, TRUE);
    $result = curl_exec($curl);
    $status = intval(curl_getinfo($curl, CURLINFO_HTTP_CODE));
    $header_size = curl_getinfo($curl, CURLINFO_HEADER_SIZE);

    if ($status < 200 || $status > 300) {
      throw new Exception("Request to {$url} returned status code: {$status}", $status);
    }

    $result = substr($result, $header_size);
    curl_close($curl);
    return json_decode($result);
  }
}