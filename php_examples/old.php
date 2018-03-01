<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$client = new TDLibJsonClient();
$client->create();

/**
 * @see https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1tdlib_parameters.html
 */
$query = json_encode([
    "@type" => "setTdlibParameters",
    "parameters" => [
        "use_test_dc" => true,
        "database_directory" => "/var/tmp/tdlib",
        "files_directory" => "/var/tmp/tdlib",
        "use_file_database" => false,
        "use_chat_info_database" => false,
        "use_message_database" => false,
        "use_secret_chats" => false,
        "api_id" => 111111,
        "api_hash" => "a1b2c3",
        "system_language_code" => "en",
        "device_model" => php_uname('s'),
        "system_version" => php_uname('v'),
        "application_version" => "0.0.4",
        "enable_storage_optimizer" => true,
        "ignore_file_names" => false
    ]
]);
$result = $client->sendAndWait($query, 10);
$query = json_encode([
    '@type' => 'setDatabaseEncryptionKey',
]);
$result = $client->sendAndWait($query, 10);
$response = json_decode($result, true);
var_dump($response);
$query = json_encode([
    '@type' => 'getAuthorizationState',
    '@extra' => 1.01234
]);
$result = $client->sendAndWait($query, 10);
$response = json_decode($result, true);
var_dump($response);

$client->destroy();
