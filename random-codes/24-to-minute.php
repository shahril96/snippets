<?php

echo twentyfourminute('2000', '2200'); // input in string

function twentyfourminute($first, $end){
  $total = 0;
  if($first[0] == '0') $first = substr($first, 1);
  if($end[0] == '0') $end = substr($end, 1);
  if((intval($first) % 100) != 0){
    $total += 60 - (intval($first) % 100);
    $first -= (intval($first) % 100) - 100;
  }
  if((intval($end) % 100) != 0){
    $total += intval($end) % 100;
    $end -= intval($end) % 100;
  }
  $total += (($end/100) - ($first/100)) * 60;
  return $total;
}

?>