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
$client = new TDLib\JsonClient();
$client->create();

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
        "application_version" => "0.0.6",
        "enable_storage_optimizer" => true,
        "ignore_file_names" => false
    ]
]);
$result = $client->sendAndWait($query, 10);
$response = json_decode($result, true);
var_dump($response);
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
```

```
../php_examples/old.php:34:
array(2) {
  '@type' =>
  string(24) "updateAuthorizationState"
  'authorization_state' =>
  array(1) {
    '@type' =>
    string(37) "authorizationStateWaitTdlibParameters"
  }

}
../php_examples/old.php:40:
array(2) {
  '@type' =>
  string(24) "updateAuthorizationState"
  'authorization_state' =>
  array(2) {
    '@type' =>
    string(35) "authorizationStateWaitEncryptionKey"
    'is_encrypted' =>
    bool(true)
  }
}
../php_examples/old.php:47:
array(2) {
  '@type' =>
  string(2) "ok"
  '@extra' =>
  NULL
}
```

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
cd phptdlib && mkdir build && cd build
cmake ..
make
cd ../php_examples

php -i | grep tdlib
php func.php
php client.php
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
