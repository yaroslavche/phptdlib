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
    ->setParameter('api_id', '1112341')
    ->setParameter('api_hash', 'a1b2c3')
    ->setParameter('system_language_code', 'en')
    ->setParameter('device_model', php_uname('s'))
    ->setParameter('system_version', php_uname('v'))
    ->setParameter('application_version', '0.0.7')
    ->setParameter('enable_storage_optimizer', true)
    ->setParameter('ignore_file_names', false);
$result = $client->setTdlibParameters($tdlibParams);
$result = $client->setDatabaseEncryptionKey();
$result = $client->updateAuthorizationState();
$result = $client->getAuthorizationState(1.01234);
$result = $client->updateOption("version", "1.1.1");
$result = $client->getAuthorizationState(1.01234);
$client->destroy();
```

```
debug:
yaroslav@localhost:~/projects/phptdlib/build> php ../php_examples/client.php
query: {"@type":"setTdlibParameters","parameters":{"use_test_dc":true,"database_directory":"/var/tmp/tdlib","files_directory":"/var/tmp/tdlib","use_file_database":false,"us
e_chat_info_database":false,"use_message_database":false,"use_secret_chats":false,"api_id":"1112341","api_hash":"a1b2c3","system_language_code":"en","device_model":"Linux",
"system_version":"#1 SMP PREEMPT Thu Feb 22 21:48:29 UTC 2018 (52ce732)","application_version":"0.0.7","enable_storage_optimizer":true,"ignore_file_names":false}}, timeout:
 10
result: {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitTdlibParameters"}}

query: {"@type":"setDatabaseEncryptionKey"}, timeout: 10
result: {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitEncryptionKey","is_encrypted":true}}

query: {"@type":"updateAuthorizationState"}, timeout: 10

result: {"@type":"ok","@extra":null}

query: {"@type":"getAuthorizationState","@extra":0.1234}, timeout: 10
result: {"@type":"updateOption","name":"version","value":{"@type":"optionValueString","value":"1.1.1"}}

query: {"@type":"updateOption", "parameters":{"version":"1.1.1"}}, timeout: 10
result: {"@type":"updateConnectionState","state":{"@type":"connectionStateConnecting"}}

query: {"@type":"getAuthorizationState","@extra":0.1234}, timeout: 10
result: {"@type":"updateAuthorizationState","authorization_state":{"@type":"authorizationStateWaitPhoneNumber"}}
```


## Required
 - [TDLib v1.1.1][1]
 - [PHP-CPP v2.0.0][2] (PHPCPP_API_VERSION 20150126)

## install extension
```bash
cd ~/projects
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib
cmake .
make

php -i | grep tdlib
php php_examples/client.php
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
