<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$testQuery = json_encode(['@type' => 'getAuthorizationState', '@extra' => 1.01234]);

$client = new TDLib\JsonClient();
$client->create();
$result = $client->execute($testQuery);
$client->send($testQuery);
$result = $client->receive(10);
$result = $client->sendAndWait($testQuery, 10);
// $client->destroy(); // segfault
unset($client);
