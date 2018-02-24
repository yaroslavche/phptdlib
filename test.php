
<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$client = td_json_client_create();
var_dump($client);

$query = json_encode([
        '@type' => 'getAuthorizationState',
        '@extra' => 1.01234
    ]);
var_dump($query);

td_json_client_send($client, $query);
while (true) {
    $result = td_json_client_receive($client, 10);
    if (!empty($result)) {
        var_dump($result);
        break;
    }
}
