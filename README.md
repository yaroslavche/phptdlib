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
make
sudo make install

make clean
php -i | grep tdlib
php test.php
```

## use extension
```php

<?php

$client = td_json_client_create();
$query = json_encode([
        '@type' => 'getAuthorizationState',
        '@extra' => 1.01234
    ]);
$result = td_json_client_send($client, $query);
```
