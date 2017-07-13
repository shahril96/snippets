<?php

echo tahukah_anda();

function tahukah_anda(){
  $rd = rand(1000,7000);
  if($rd >= 1000 && $rd <= 2000){
    $year = '/Arkib/2008';
  }elseif($rd >= 2000 && $rd <= 3000){
    $year = '/Arkib/2009';
  }elseif($rd >= 3000 && $rd <= 4000){
    $year = '/Arkib/2010';
  }elseif($rd >= 4000 && $rd <= 5000){
    $year = '/Arkib/2011';
  }elseif($rd >= 5000 && $rd <= 6000){
   $year = '/Arkib/2012';
  }else{
    $year = '';
  }
  $get = file_get_contents('https://ms.wikipedia.org/wiki/Wikipedia:Tahukah_anda'.$year);
  preg_match_all('/\<li\>\"([^\/wiki\/][\"\.\.\.].*?)\"\<\/li\>/', $get, $out_tahukah);
  return 'Tahukah '.strip_tags($out_tahukah[1][array_rand($out_tahukah[1])]);
}

?>