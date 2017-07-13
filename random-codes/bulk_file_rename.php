<?php

echo "\n Bulk File Renamer @ Shahril";

$help_text = "
    \r {$argv[0]} --dir C:\Music --pattern \"/\d{2} \-/\" --rename \"Change\"

    \r Options :-
    \r  --dir <directory> : Directory of bulk file.
    \r  --pattern <regex> : Regex pattern to match.
    \r  --rename <name>   : String to replace the pattern.
  ";

if(in_array("--dir", $argv, true)){
	$key = array_search("--dir", $argv);
	$value = $key + 1;
	$dir = realpath($argv[$value]);
}else{
	echo $help_text;
	die();
}

if(in_array("--pattern", $argv, true)){
	$key = array_search("--pattern", $argv);
	$value = $key + 1;
	$pattern = $argv[$value];
}else{
	echo $help_text;
	die();
}

if(in_array("--rename", $argv, true)){
	$key = array_search("--rename", $argv);
	$value = $key + 1;
	$rename = $argv[$value];
}else{
	echo $help_text;
	die();
}

if(!file_exists($dir)) die("\n\n Directory not found or incorrect input!\n");

$files = array_diff(scandir($dir), array('..', '.'));

if(empty($files)) die("\n\n No file exist in that directory!\n");

chdir($dir);

foreach($files as $file){

  $changed = preg_replace($pattern, $rename, $file);
  
  if(!rename($file, $changed)) die("\n File '{$file}' has some problem!\n");
}

echo "\n\n All operations done!\n";




?>