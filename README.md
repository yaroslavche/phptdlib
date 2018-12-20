[![Build Status](https://travis-ci.org/yaroslavche/phptdlib.svg?branch=master)](https://travis-ci.org/yaroslavche/phptdlib)

[Documentation](https://yaroslavche.github.io/phptdlib/)

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
    ->setParameter(\TDApi\TDLibParameters::USE_TEST_DC, true)
    ->setParameter(\TDApi\TDLibParameters::DATABASE_DIRECOTRY, '/var/tmp/tdlib')
    ->setParameter(\TDApi\TDLibParameters::FILES_DIRECTORY, '/var/tmp/tdlib')
    ->setParameter(\TDApi\TDLibParameters::USE_FILE_DATABASE, false)
    ->setParameter(\TDApi\TDLibParameters::USE_CHAT_INFO_DATABASE, false)
    ->setParameter(\TDApi\TDLibParameters::USE_MESSAGE_DATABASE, false)
    ->setParameter(\TDApi\TDLibParameters::USE_SECRET_CHATS, false)
    // SET API_CODE AND API_HASH
    ->setParameter(\TDApi\TDLibParameters::API_ID, 123)
    ->setParameter(\TDApi\TDLibParameters::API_HASH, 'xxx')
    ->setParameter(\TDApi\TDLibParameters::SYSTEM_LANGUAGE_CODE, 'en')
    ->setParameter(\TDApi\TDLibParameters::DEVICE_MODEL, php_uname('s'))
    ->setParameter(\TDApi\TDLibParameters::SYSTEM_VERSION, php_uname('v'))
    ->setParameter(\TDApi\TDLibParameters::APPLICATION_VERSION, '0.0.8')
    ->setParameter(\TDApi\TDLibParameters::ENABLE_STORAGE_OPTIMIZER, true)
    ->setParameter(\TDApi\TDLibParameters::IGNORE_FILE_NAMES, false);
$result = $client->setTdlibParameters($tdlibParams);
$result = $client->setDatabaseEncryptionKey();
// SET PHONE_NUMBER
$result = $client->setAuthenticationPhoneNumber("xxx");
// UNCOMMENT WHEN RECEIVE SMS AND INSERT CODE.
// $result = $client->query(json_encode(['@type' => 'checkAuthenticationCode', 'code' => 'xxx', 'first_name' => 'dummy', 'last_name' => 'dummy']), 10);
$result = $client->getAuthorizationState();
$result = $client->query(json_encode(['@type' => 'searchPublicChat', 'username' => 'telegram']), 10);
var_dump($result);

$allNotifications = $client->getReceivedResponses();
var_dump($allNotifications);

$client->destroy();
```

## Required
 - [PHP-CPP v2.0.0][2]
 
 All dependencies are installed via git submodules. But PHP-CPP
 currently has buggy CMake configuration and should be globally installed as a library.
 
```bash
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
sudo make install
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
