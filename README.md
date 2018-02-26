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
make install
```

## install [PHP-CPP][2]
```bash
cd ~/projects
git clone https://github.com/CopernicaMarketingSoftware/PHP-CPP.git
cd PHP-CPP
make
```

## install extension
```bash
cd ~/projects
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib
cmake
sudo make

php -i | grep tdlib
php test.php
```

## use extension
```php

<?php

$client = new TDLibJsonClient();
$client->create();

$query = json_encode([
        '@type' => 'getAuthorizationState',
        '@extra' => 1.01234
    ]);

$client->send($query);
while (true) {
    $result = $client->receive(10);
    if (!empty($result)) {
        var_dump($result);
        break;
    }
}
```
[1]: https://github.com/tdlib/td#building
[2]: http://www.php-cpp.com/documentation/install
