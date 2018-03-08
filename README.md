## example
[https://github.com/tdlib/td/blob/master/example/cpp/tdjson_example.cpp](https://github.com/tdlib/td/blob/master/example/cpp/tdjson_example.cpp)
```php
<?php
$client = td_json_client_create();
while(true)
{
    $result = td_json_client_receive($client, 10);
    if(!empty($result)) {
        echo $result;
        break;
    }
}
```
or
```php
<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$client = new TDLib\JsonClient();

$tdlibParams = new TDApi\TDLibParameters();
$tdlibParams
    ->setParameter('use_test_dc', true)
    ->setParameter('database_directory', '/var/tmp/tdlib')
    ->setParameter('files_directory', '/var/tmp/tdlib')
    ->setParameter('use_file_database', false)
    ->setParameter('use_chat_info_database', false)
    ->setParameter('use_message_database', false)
    ->setParameter('use_secret_chats', false)
    // SET API_CODE AND API_HASH
    ->setParameter('api_id', 'xxx')
    ->setParameter('api_hash', 'xxx')
    ->setParameter('system_language_code', 'en')
    ->setParameter('device_model', php_uname('s'))
    ->setParameter('system_version', php_uname('v'))
    ->setParameter('application_version', '0.0.7')
    ->setParameter('enable_storage_optimizer', true)
    ->setParameter('ignore_file_names', false);
$result = $client->setTdlibParameters($tdlibParams);
$result = $client->setDatabaseEncryptionKey();
// SET PHONE_NUMBER
$result = $client->setAuthenticationPhoneNumber("xxx");
// UNCOMMENT WHEN RECEIVE SMS AND INSERT CODE.
// $result = $client->query(json_encode(['@type' => 'checkAuthenticationCode', 'code' => 'xxx', 'first_name' => 'dummy', 'last_name' => 'dummy']), 10);
$result = $client->getAuthorizationState(1.01234);
$result = $client->query(json_encode(['@type' => 'searchPublicChat', 'username' => 'telegram']), 10);
var_dump($result);
$client->destroy();
```


## Required
 - [TDLib v1.1.1][1]
 - [PHP-CPP v2.0.0][2] (PHPCPP_API_VERSION 20150126)

## install extension
```bash
cd ~/projects
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib && mkdir build && cd build
cmake ..
make

php -i | grep tdlib
php ../php_examples/client.php
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
