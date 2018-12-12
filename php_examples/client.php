<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

if(file_exists(__DIR__ . '/credentials.php')) require_once __DIR__ . '/credentials.php';
else die('cp php_examples/credentials.php.dist php_examples/credentials.php && edit' . PHP_EOL);

TDApi\LogConfiguration::setLogVerbosityLevel(\TDApi\LogConfiguration::LVL_ERROR);

$client = new TDLib\JsonClient();
$client->getAuthorizationState();

$tdlibParams = new TDApi\TDLibParameters();
$tdlibParams
    ->setParameter(TDApi\TDLibParameters::USE_TEST_DC, true)
    ->setParameter(TDApi\TDLibParameters::DATABASE_DIRECOTRY, '/var/tmp/tdlib')
    ->setParameter(TDApi\TDLibParameters::FILES_DIRECTORY, '/var/tmp/tdlib')
    ->setParameter(TDApi\TDLibParameters::USE_FILE_DATABASE, false)
    ->setParameter(TDApi\TDLibParameters::USE_CHAT_INFO_DATABASE, false)
    ->setParameter(TDApi\TDLibParameters::USE_MESSAGE_DATABASE, false)
    ->setParameter(TDApi\TDLibParameters::USE_SECRET_CHATS, false)
    ->setParameter(TDApi\TDLibParameters::API_ID, $api_id)
    ->setParameter(TDApi\TDLibParameters::API_HASH, $api_hash)
    ->setParameter(TDApi\TDLibParameters::SYSTEM_LANGUAGE_CODE, 'en')
    ->setParameter(TDApi\TDLibParameters::DEVICE_MODEL, php_uname('s'))
    ->setParameter(TDApi\TDLibParameters::SYSTEM_VERSION, php_uname('v'))
    ->setParameter(TDApi\TDLibParameters::APPLICATION_VERSION, '0.0.7')
    ->setParameter(TDApi\TDLibParameters::ENABLE_STORAGE_OPTIMIZER, true)
    ->setParameter(TDApi\TDLibParameters::IGNORE_FILE_NAMES, false);
$result = $client->setTdlibParameters($tdlibParams);
$result = $client->setDatabaseEncryptionKey(); // checkDatabaseEncryptionKey(key) or DESTROY
$result = $client->setAuthenticationPhoneNumber($phone_number);
// $result = $client->query(json_encode(['@type' => 'checkAuthenticationCode', 'code' => 'xxx', 'first_name' => 'dummy', 'last_name' => 'dummy']), 10);
$result = $client->getAuthorizationState();
$result = $client->query(json_encode(['@type' => 'searchPublicChat', 'username' => 'telegram']), 10);
var_dump($result);
$client->destroy();
