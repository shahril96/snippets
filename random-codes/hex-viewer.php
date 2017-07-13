<?php

hex_viewer('./test_file', 8);

function hex_viewer($File, $Length = 16) {

  $handle = @fopen($File, 'r');
  
  if(!$handle) {
    return 0;
  }
  
  $contents = fread($handle, filesize($File));
  fclose($handle);

  foreach( str_split($contents, $Length) as $n => $line ) {
    $N_Length = strtoupper(base_convert((($n) * $Length), 10, 16));
    echo ' '.str_pad($N_Length, 8, '0', STR_PAD_LEFT);
    $tmpStore = NULL;
    for( $i = 0; $i < strlen($line); $i++ ) {  
      $toHex = base_convert(ord($line[$i]), 10, 16);
      $toHex = (strlen($toHex) == 1)?'0'.$toHex:$toHex;
      $Spaces = ($i < (strlen($line) - 1))?' ':'';
      $tmpStore .= strtoupper($toHex).$Spaces;
    }
    if( $line < $Length ) {
      $Cnt = $Length - strlen($line);
      for( $i = 0; $i < $Cnt; $i++ ) {
        $tmpStore .= ' 00';
      }
    }
    $Str = preg_replace('/[\r|\t|\n]/', '.', $line);
    echo ' '.$tmpStore.' '.$Str."\n";
  }

}

?>