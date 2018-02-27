## install [TDLib][1]
```bash
# opensuse
sudo zypper in php7 gperf cmake gcc-c++ openssl-devel
cd ~/projects
git clone https://github.com/tdlib/td.git
cd td
mkdir build
cd build
cmake -DCMAKE_BUILD_TYPE=Release ..
cmake --build .
sudo make install
```

## install [PHP-CPP][2]
```bash
cd ~/projects
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
sudo make
```

## install extension
```bash
cd ~/projects
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib
cmake .
sudo make

php -i | grep tdlib
php test.php
```

## use extension
```php
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
        "application_version" => "0.0.2",
        "enable_storage_optimizer" => true,
        "ignore_file_names" => false
    ]
]);
$result = $client->send($query, 10);
$query = json_encode([
    '@type' => 'setDatabaseEncryptionKey',
]);
$result = $client->send($query, 10);
$response = json_decode($result, true);
var_dump($response);
$query = json_encode([
    '@type' => 'getAuthorizationState',
    '@extra' => 1.01234
]);
$result = $client->send($query, 10);
$response = json_decode($result, true);
var_dump($response);

$client->destroy();
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
