<?php

$get = file_get_contents("https://sapsnkra.moe.gov.my/ibubapa2/semak.php?txtIC=010610101490&Semak=Semak+Laporan&jenissek=2&tahun_semasa=2015");

// build up custom header + cookie
preg_match_all('#Set-Cookie: (.*?);#', implode('', $http_response_header), $out);
$opts = array('http'=>array('header'=> "Cookie: " . implode('; ', $out[1]) . "\r\n"));

$get = file_get_contents("https://sapsnkra.moe.gov.my/ibubapa2/menu.php", false, stream_context_create($opts));
preg_match_all('#<strong>(.*?)&nbsp;</strong>#', $get, $out);

var_dump($out[1]);

?>
