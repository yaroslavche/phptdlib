<?php

Error_Reporting(E_ALL);
ini_set('display_errors', 1);

$tdlibParameters = new TDApi\TDLibParameters();
$tdlibParameters->setParameter('use_test_dc', true);
// $tdlibParameters->set(); // send query
// $tdlibParameters->get(); // or get formatted query?
