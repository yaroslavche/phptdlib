
<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$client = new TDLibJsonClient();
$client->create(); // move to constructor?

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
