## example
```php
<?php
/**
 * @see https://github.com/tdlib/td/blob/master/example/cpp/tdjson_example.cpp
 */
$client = td_json_client_create();
while(true)
{
    $result = td_json_client_receive($client, 10);
    if(!empty($result)) {
        echo $result;
        break;
    }
}

// $result = td_json_client_execute($client, $query);
// td_json_client_send($client, $query);

// td_json_client_destroy($client); // segfault here
```

```php
<?php

$testQuery = json_encode(['@type' => 'getAuthorizationState', '@extra' => 1.01234]);

$client = new TDLib\JsonClient();
$client->create();
$result = $client->execute($testQuery);
$client->send($testQuery);
$result = $client->receive(10);
$result = $client->sendAndWait($testQuery, 10);
// $client->destroy(); // segfault

$tdlibParameters = new TDApi\TDLibParameters();
$tdlibParameters->setParameter('use_test_dc', true);
// ...
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
cd phptdlib
cmake .
make

php -i | grep tdlib
php php_examples/func.php
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
