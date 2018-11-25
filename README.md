[![Build Status](https://travis-ci.org/yaroslavche/phptdlib.svg?branch=master)](https://travis-ci.org/yaroslavche/phptdlib)
[Documentation](https://yaroslavche.github.io/phptdlib/docs/index.html)
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

```php
<?php
Error_Reporting(E_ALL);
ini_set('display_errors', 1);

TDApi\LogConfiguration::setLogVerbosityLevel(\TDApi\LogConfiguration::LVL_ERROR);

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

$allNotifications = $client->getReceivedResponses();
var_dump($allNotifications);

$client->destroy();
```

## Required
 - [TDLib v1.3.0][1]
```bash
git clone https://github.com/tdlib/td.git
cd td && mkdir build && cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
sudo cmake --build . --target install
```
 - [PHP-CPP v2.0.0][2]
```bash
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
sudo make install
```
 - [nlohmann/json v3.2.0 (JSON for Modern C++)][3]
```bash
git clone https://github.com/nlohmann/json.git
cd json && mkdir build && cd build
cmake ..
make install
```

## install extension
```bash
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib && mkdir build && cd build
cmake ..
make
```
### check
```bash
php -i | grep tdlib
php ../php_examples/func.php
```


## Docker

```
docker build -t phptdlib .
docker run -it phptdlib

php -i | grep tdlib

cd $HOME/phptdlib/php_examples

php func.php

cp credentials.php.dist credentials.php
php client.php
```

### yaroslavche/phptdlib
[docker image][phptdlib_docker_image]

```
docker build -f Dockerfile.phptdlib_env -t yaroslavche/phptdlib .
```

`OpenSUSE Leap` with installed `sudo` `which` `gcc` `gcc-c++` `zlib` `gperf` `openssl` `openssl-devel` `cmake` `git` `php7` `php7-devel` `php7-ctype` `php7-json`. Needs min [4GB RAM][td_ram_issue] and must wait a while.
1.25Gb
needs: g++ -> clang (RAM issue) and opensuse -> alpine (size), docker-compose

[1]: https://github.com/tdlib/td
[2]: https://github.com/CopernicaMarketingSoftware/PHP-CPP/
[3]: https://github.com/nlohmann/json
[td_ram_issue]: https://github.com/tdlib/td/issues/67
[phptdlib_docker_image]: https://hub.docker.com/r/yaroslavche/phptdlib/
