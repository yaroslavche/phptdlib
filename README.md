[![Build Status](https://travis-ci.com/yaroslavche/phptdlib.svg?branch=master)](https://travis-ci.com/yaroslavche/phptdlib)

The PHP extension `tdlib` allows you to work with the [Telegram database library](https://core.telegram.org/tdlib).
If simple, this is the usual [functions wrapper](include/td_json_client_func.hpp) for working with the `tdlib/td` json client. You can:
 - create a JSON client `$client = td_json_client_create()`
 - execute the synchronous request `$result = td_json_client_execute($client, $json);`
 - perform an asynchronous request `td_json_client_send($client, $json);` *
 - get all the responses at the moment `$response = td_json_client_receive($client, $timeout);`
 - and destroy client `td_json_client_destroy($client);`

`*` you must use `td_json_client_receive` to get a response from an asynchronous request.

[Getting started with TDLib](https://core.telegram.org/tdlib/getting-started)

[td_json_client.h File Reference](https://core.telegram.org/tdlib/docs/td__json__client_8h.html)

[Video tutorial how to install and simple usage](https://www.youtube.com/watch?v=gtQOjSVlvlI)

[phptdlib Documentation](https://yaroslavche.github.io/phptdlib/)

## Example
[https://github.com/tdlib/td/blob/master/example/cpp/tdjson_example.cpp](https://github.com/tdlib/td/blob/master/example/cpp/tdjson_example.cpp)
```php
<?php
$client = td_json_client_create();
td_json_client_execute($client, json_encode(['@type' => 'setLogVerbosityLevel', 'new_verbosity_level' => '0']));
$waitTimeout = 10;
while(true)
{
    $result = td_json_client_receive($client, $waitTimeout);
    if(!empty($result)) {
        echo $result;
        break;
    }
}
td_json_client_destroy($client);
```

## TDLib\JsonClient

```php
$client = new \TDLib\JsonClient();
$client->setDefaultTimeout(10);
$result = $client->execute($stringQuery);
$client->send($stringQuery);
$response = $client->receive($floatTimeout);
$response = $client->query($stringQuery, $floatTimeout);
$responses = $client->getReceivedResponses();
$client->destroy();
```

Thanks to @maxvgi, `phptdlib` has a really good implementation of `query` method. You no longer need to use `send` and `receive` (but you can if you want). An additional field will be added to `query`, and will wait for this additional field in the responses. Since this is for asynchronous requests, before you get an answer to the request, you can get others. And you can get all the responses to the last request with `$client->getReceivedResponses();` 

Example. Simple workflow:
 - create a client
 - `setTdlibParameters`
 - if need, `setDatabaseEncryptionKey`
 - if `getAuthorizationState` returns `authorizationStateWaitPhoneNumber`, then `setAuthenticationPhoneNumber`
 - if `getAuthorizationState` returns `authorizationStateWaitCode`, then `checkAuthenticationCode`
 - if `getAuthorizationState` returns `authorizationStateReady`, then you are allowed to do what you want with `tdlib/td` ([Function class reference](https://core.telegram.org/tdlib/docs/classtd_1_1td__api_1_1_function.html)).

```php
<?php
Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$api_id = 11111; // must be an integer
$api_hash = 'abcdef1234567890abcdef1234567890';
$phone_number = '+380991234567';

try {
    \TDApi\LogConfiguration::setLogVerbosityLevel(\TDApi\LogConfiguration::LVL_ERROR);
    
    $client = new \TDLib\JsonClient();
    
    $tdlibParams = new \TDApi\TDLibParameters();
    $tdlibParams
        ->setParameter(\TDApi\TDLibParameters::USE_TEST_DC, true)
        ->setParameter(\TDApi\TDLibParameters::DATABASE_DIRECTORY, '/var/tmp/tdlib')
        ->setParameter(\TDApi\TDLibParameters::FILES_DIRECTORY, '/var/tmp/tdlib')
        ->setParameter(\TDApi\TDLibParameters::USE_FILE_DATABASE, false)
        ->setParameter(\TDApi\TDLibParameters::USE_CHAT_INFO_DATABASE, false)
        ->setParameter(\TDApi\TDLibParameters::USE_MESSAGE_DATABASE, false)
        ->setParameter(\TDApi\TDLibParameters::USE_SECRET_CHATS, false)
        ->setParameter(\TDApi\TDLibParameters::API_ID, $api_id)
        ->setParameter(\TDApi\TDLibParameters::API_HASH, $api_hash)
        ->setParameter(\TDApi\TDLibParameters::SYSTEM_LANGUAGE_CODE, 'en')
        ->setParameter(\TDApi\TDLibParameters::DEVICE_MODEL, php_uname('s'))
        ->setParameter(\TDApi\TDLibParameters::SYSTEM_VERSION, php_uname('v'))
        ->setParameter(\TDApi\TDLibParameters::APPLICATION_VERSION, '0.0.10')
        ->setParameter(\TDApi\TDLibParameters::ENABLE_STORAGE_OPTIMIZER, true)
        ->setParameter(\TDApi\TDLibParameters::IGNORE_FILE_NAMES, false);
    $result = $client->setTdlibParameters($tdlibParams);

    $result = $client->setDatabaseEncryptionKey();
    
    $state = $client->getAuthorizationState();
    
    // you must check the state and follow workflow. Lines below is just for an example.
    // $result = $client->setAuthenticationPhoneNumber($phone_number, 3); // wait response 3 seconds. default - 1.
    // $result = $client->query(json_encode(['@type' => 'checkAuthenticationCode', 'code' => 'xxxxx', 'first_name' => 'dummy', 'last_name' => 'dummy']), 10);
    
    $result = $client->query(json_encode(['@type' => 'searchPublicChat', 'username' => 'telegram']), 10);
    
    $allNotifications = $client->getReceivedResponses();
} catch (\Exception $exception) {
    echo sprintf('something goes wrong: %s', $exception->getMessage());
}
```

## Required

Please note that TDLib itself requires a lot of resources. The extension will be built in a couple of seconds. But the extension requires compiled [tdlib/td](https://github.com/tdlib/td). A minimum of 4GB of RAM is recommended. But I know that it is possible to build on a VPS with g++ and 2GB RAM + swap.

The most of dependencies are installed via git submodules currently.

But PHP-CPP currently has to be built separately.
 
 - [PHP-CPP v2.0.0][2]
 
```bash
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git

cd PHP-CPP
make
sudo make install
```

If you want to link other dependencies as dynamic libraries, you can pass
 some options to cmake. Look through CMakeLists.txt comments to find out how.

## install extension
```bash
git clone --recurse-submodules https://github.com/yaroslavche/phptdlib.git
cd phptdlib && mkdir build && cd build
cmake ..
make
sudo make install
```
### check
```bash
php -i | grep tdlib
php ../php_examples/func.php
```

---

Feel free to `$client->query(json_encode(['@type' => 'sendMessage', 'chat' => '@yaroslavche']));` if you have any questions.

[1]: https://github.com/tdlib/td
[2]: https://github.com/CopernicaMarketingSoftware/PHP-CPP/
[3]: https://github.com/nlohmann/json
[td_dependencies]: https://github.com/tdlib/td#dependencies
[td_ram_issue]: https://github.com/tdlib/td/issues/67
[phptdlib_docker_image]: https://hub.docker.com/r/yaroslavche/phptdlib/
