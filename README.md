## prepare TDLib
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
```

## install extension
```bash
cd ~/projects
git clone https://github.com/yaroslavche/phptdlib.git
cd phptdlib
cmake
sudo make

php -i | grep tdlib
php -r "echo td_version(), PHP_EOL;"
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
