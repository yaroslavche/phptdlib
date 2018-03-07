<?php

Error_Reporting(-1);
ini_set('display_errors', 1);

$testQuery = json_encode(['@type' => 'getAuthorizationState', '@extra' => 1.01234]);

$client = td_json_client_create();
$result = td_json_client_execute($client, $testQuery);
td_json_client_send($client, $testQuery);
td_json_client_send($client, $testQuery);
td_json_client_send($client, $testQuery);
$result = td_json_client_receive($client, 10);
td_json_client_destroy($client); // segfault if not set params?
