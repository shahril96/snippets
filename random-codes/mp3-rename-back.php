<?php

// require getid3
require_once('../getid3/getid3.php');

$getID3 = new getID3;

echo "\n MP3 File Renamer @ Shahril";

$help_text = "
    \r {$argv[0]} --dir C:\Music

    \r Options :-
    \r  --dir <directory> : Directory of MP3 file..
  ";

if(in_array("--dir", $argv, true)){
	$key = array_search("--dir", $argv);
	$value = $key + 1;
	$dir = realpath($argv[$value]);
}else{
	echo $help_text;
	die();
}

if(!file_exists($dir)) die("\n\n Directory not found or incorrect input!\n");

$files = array_diff(scandir($dir), array('..', '.'));

if(empty($files)) die("\n\n No file exist in that directory!\n");

chdir($dir);

foreach($files as $file){

  $get = $getID3->analyze($file);
  
  if(empty($get['tags_html']['id3v1'])) continue;
  
  if(!empty($get['tags_html']['id3v1'])){
    $get = $get['tags_html']['id3v1'];
  }else{
    $get = $get['tags_html']['id3v2'];
  }
  
  $artist = $get['artist'][0];
  $title = $get['title'][0];
  
  if(!empty($title)){
    if(empty($artist)){
      $t = rename($file, trim(forbidden_word($title.'.mp3')));
      if(!$t){
        die('error!');
      }
    }else{
      $t = rename($file, trim(forbidden_word($artist.' - '.$title.'.mp3')));
      if(!$t){
        die('error!');
      }
    }
  }

}

echo "\n\n All operations done!\n";

function forbidden_word($str){
  return str_replace(array('|','\\','?','*','<','"','>','+','[',']'), '', $str);
}

?>