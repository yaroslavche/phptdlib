<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

if(file_exists(__DIR__ . '/credentials.php')) require_once __DIR__ . '/credentials.php';
else die('cp php_examples/credentials.php.dist php_examples/credentials.php && edit' . PHP_EOL);

$client = new TDLib\JsonClient();
$client->getAuthorizationState();

$tdlibParams = new TDApi\TDLibParameters();
$tdlibParams
    ->setParameter('use_test_dc', true)
    ->setParameter('database_directory', '/var/tmp/tdlib')
    ->setParameter('files_directory', '/var/tmp/tdlib')
    ->setParameter('use_file_database', false)
    ->setParameter('use_chat_info_database', false)
    ->setParameter('use_message_database', false)
    ->setParameter('use_secret_chats', false)
    ->setParameter('api_id', $api_id)
    ->setParameter('api_hash', $api_hash)
    ->setParameter('system_language_code', 'en')
    ->setParameter('device_model', php_uname('s'))
    ->setParameter('system_version', php_uname('v'))
    ->setParameter('application_version', '0.0.7')
    ->setParameter('enable_storage_optimizer', true)
    ->setParameter('ignore_file_names', false);
$result = $client->setTdlibParameters($tdlibParams);
$result = $client->setDatabaseEncryptionKey(); // checkDatabaseEncryptionKey(key) or DESTROY
$result = $client->setAuthenticationPhoneNumber($phone_number);
// $result = $client->query(json_encode(['@type' => 'checkAuthenticationCode', 'code' => 'xxx', 'first_name' => 'dummy', 'last_name' => 'dummy']), 10);
$result = $client->getAuthorizationState(1.01234);
$result = $client->query(json_encode(['@type' => 'searchPublicChat', 'username' => 'telegram']), 10);
var_dump($result);
$client->destroy();
