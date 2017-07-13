// this was my attempt to write my own php obfuscator
// this was inspired by Carbylamine PHP Script Encoder
// its currently in alpha, because sometimes its work, and sometimes it doesnt
// this was written 3 years ago (ahh memories again)
// so code looks suck
// thanks to Mokhdzani Faeq for created good regexs
// have fun!

<?php

echo "\n Simple PHP Encoder @ Shahril";
echo "\n Thanks to personant (good regex!)\n";

$help_text = "
			\r {$argv[0]} -input script.php -output decode.php
			\r {$argv[0]} -input script.php -repeat 3
			\r {$argv[0]} -input script.php -repeat 5 -encode fv
			\r {$argv[0]} -input script.php -output decode.php -repeat 10 -encode v
			
			\r Options :-
			\r  -input [file]       : File to encode.
			\r  -output [file]      : [Optional]
			\r  -repeat [number]    : [Optional] Multiple encode file for bypassing
			\r                        antivirus.
			\r  -encode [parameter] : v - variable, f - function, s - string (not stable)
			\r                        Change all variable or function or string name
			\r                        before encode. Note that this function maybe
			\r                        make some php broken after encode.
			";

if(empty($argv[1])){
	echo $help_text;
	die();
}

if(in_array("-input", $argv, true)){
	$key = array_search("-input", $argv);
	$value = $key + 1;
	$filename = $argv[$value];
}else{
	echo $help_text;
	die();
}

if(in_array("-output", $argv, true)){
	$key = array_search("-output", $argv);
	$value = $key + 1;
	$output = $argv[$value];
}else{
	$output = $filename."_encoded.php";
}

if(in_array("-repeat", $argv, true)){
	$key = array_search("-repeat", $argv);
	$value = $key + 1;
	$repeat_encode = $argv[$value];
}else{
	$repeat_encode = 1;
}

if(in_array("-encode", $argv, true)){
	$key = array_search("-encode", $argv);
	$value = $key + 1;
	$method = strtolower($argv[$value]);
}

$piece_pecah = rand(20,35);

$tempfile = rndStr(4);
$data = file_get_contents($filename);

$except_list = array(
	"_POST",
	"_GET",
	"_FILES",
	"_SERVER",
	"_REQUEST",
	"_SESSION",
	"_COOKIE",
	"_ENV",
	"GLOBALS",
	"argc",
	"argv",
	"this",
	"php_errormsg",
	"HTTP_SERVER_VARS",
	"HTTP_POST_VARS",
	"HTTP_POST_FILES",
	"HTTP_GET_VARS",
	"HTTP_COOKIE_VARS",
	"HTTP_RAW_POST_DATA",
	"http_response_header"
);

if(str_check_char($method, "v")){
	preg_match_all('/\$[A-Za-z0-9-_]+/', $data, $var_list);
	$wakil = array_values(array_unique($var_list[0]));
	$collect = array();
	foreach($wakil as $wakil_s){
		$collect[] = str_replace("$", "", $wakil_s);
	}
	foreach($except_list as $ignore){
		if(in_array($ignore, $collect, true)){
			$key = array_search($ignore, $collect);
			unset($collect[$key]);
		}
	}
	$collect_flip = array_flip($collect);
	foreach($collect_flip as $key => $value){
		$collect_flip[$key] = rndStr(rand(9, 12));
	}
	foreach($collect_flip as $key => $rand){
		$data = str_replace("$".$key, "$".$rand, $data);
	}
}


if(str_check_char($method, "f")){
	preg_match_all('/function[\s\n]+(\S+)[\s\n]*\(/', $data, $func_list);
	$func_list = $func_list[1];
	$func_list_flip = array_flip($func_list);
	foreach($func_list_flip as $key => $function){
		$func_list_flip[$key] = rndStr(rand(9, 12));
	}
	foreach($func_list_flip as $key => $rand){
		if(strpos($data, $key."(")){
			$data = str_replace($key."(", $rand."(", $data);
		}
	}
}

//encode string - not stable..

if(str_check_char($method, "s")){
	preg_match_all('/([\"\'])(?:(?=(\\\\?))\\2.)*?\\1/s', $data, $string_store);
	$string_store = array_unique($string_store[0]);
	$str_store_flip = array_flip($string_store);

	foreach($str_store_flip as $name => $value){
		if(strpos($data, $name) !== FALSE && strlen($name) > 4 && strpos($name, "\n") === FALSE){
			if(substr($name, 0, 1) == '"'){
				$str_store_flip[$name] = '"'.obfus(cutstr($name, '"', '"')).'"';
			}else{
				unset($str_store_flip[$name]);
			}
		}else{
			unset($str_store_flip[$name]);
		}
	}
	foreach($str_store_flip as $original => $replace){
		$data = str_replace($original, $replace, $data);
	}
}
	

if(strpos($data, "<?php") !== false) $data = striptag($data);
$data = base64_encode(gzcompress($data, 9));
$junk_replace_last = rndStr(rand(6,12));
$data = remove_trace($data, $junk_replace_last);
$get_piece = round(strlen($data)/$piece_pecah);
$random_var = array();
for($i = 0;$i <= $piece_pecah;$i++){
	$random_var[] = rndStr(rand(8,15));
}
$random_var_flip = array_flip($random_var);
for($i = 0;$i <= $piece_pecah;$i++){
	$random_var_flip[$random_var[$i]] = "";
}
$take_piece = 0;
for($i = 0;$i <= $piece_pecah;$i++){
	$take_piece++;
	if(strlen($data) <= $get_piece){
		$random_var_flip[$random_var[$i]] = substr($data, 0, $get_piece);
		break;
	}
	$random_var_flip[$random_var[$i]] = substr($data, 0, $get_piece);
	$data = substr($data, $get_piece);
}
$random_var_flip = array_filter($random_var_flip);
$array_piece = count($random_var_flip);
if(file_exists($output)){ unlink($output); }
file_put_contents($tempfile, "<?php\r\n", FILE_APPEND);
$repair_trace_var = rndStr(rand(5,9));
$junk_var_1 = rndStr(rand(9,12));
$junk_var_2 = rndStr(rand(9,12));
$function_in_code = "\r\nfunction {$repair_trace_var}(\${$junk_var_1}, \${$junk_var_2}){ return str_replace(\${$junk_var_2}, \"=\", \${$junk_var_1}); }\r\n";
$random_var_to_collect = rndStr(30);
file_put_contents($tempfile, "\${$random_var_to_collect} = \"\";", FILE_APPEND);
foreach($random_var_flip as $name => $value){
	file_put_contents($tempfile, "\${$name} = \"{$value}\";", FILE_APPEND);
	file_put_contents($tempfile, "\$".rndStr(rand(8,20))." = \"".rndStr(rand(90,150))."\";", FILE_APPEND);
	file_put_contents($tempfile, "\$".$random_var_to_collect." .= \$".$name.";\n", FILE_APPEND);
	file_put_contents($tempfile, "\$".rndStr(rand(8,20))." = \"".rndStr(rand(90,150))."\";", FILE_APPEND);
}
$get_s = encode_encode();
file_put_contents($tempfile, $get_s[0], FILE_APPEND);
file_put_contents($tempfile, $function_in_code, FILE_APPEND);
file_put_contents($tempfile, "\r\neval({$get_s[1]}({$get_s[2]}({$repair_trace_var}(\${$random_var_to_collect}, \"{$junk_replace_last}\"))));", FILE_APPEND);
for($i = 1;$i <= $repeat_encode;$i++){
	if($i == 1){
		$int_to_compress = 9;
	}else{
		$int_to_compress = 1; // for script executing time..lower is better
	}
	if($i == $repeat_encode){
		multi_in_encode($tempfile, $output, $int_to_compress);
	}else{
		multi_in_encode($tempfile, $tempfile, $int_to_compress);
	}
}

echo "\r\n\r\n Done :) \r\n";

// function2...

function multi_in_encode($file, $output, $int_to_compress){
	$data = file_get_contents($file);
	unlink($file);
	$data = striptag($data);
	$collect_rand_var = array();
	file_put_contents($output, "<?php\r\n", FILE_APPEND);
	$get_s = encode_encode();
	file_put_contents($output, $get_s[0], FILE_APPEND);
	file_put_contents($output, "eval({$get_s[1]}({$get_s[2]}(\"".base64_encode(gzcompress($data, $int_to_compress))."\")));", FILE_APPEND);
}

function encode_encode(){
	for($i = 0;$i <= 7;$i++){
		$soh[] = rndStr(rand(8,12));
	}
	$rand_combine_1 = rndStr(rand(8,12));
	$rand_combine_2 = rndStr(rand(8,12));
	$data_function = "\r\${$soh[1]} = \"gzu\";\${$soh[2]} = \"ncomp\";\${$soh[3]} = \"ress\";
					\r\${$rand_combine_1} = \${$soh[1]}.\${$soh[2]}.\${$soh[3]};
					\r\${$soh[4]} = \"base\";\${$soh[5]} = \"64_d\";\${$soh[6]} = \"ec\";\${$soh[7]} = \"ode\";
					\r\${$rand_combine_2} = \${$soh[4]}.\${$soh[5]}.\${$soh[6]}.\${$soh[7]};";
	$data_function = "eval(str_rot13(gzuncompress(base64_decode(\"".base64_encode(gzcompress(str_rot13($data_function), 9))."\"))));";
	$return_data = array($data_function, "\$".$rand_combine_1, "\$".$rand_combine_2);
	return $return_data;
}

function cutstr($data, $str1, $str2){
	$data = explode($str1, $data);
	$data = explode($str2, $data[1]);
	return $data[0];
}

function remove_trace($string, $junk){
	return str_replace("=", $junk, $string);
}

function obfus($string){
	$string = str_split($string);
	foreach($string as &$char){
		$char = (++$i%2) ? "\x".dechex(ord($char)) : "\\".decoct(ord($char));
	}
	return implode('',$string);
}

function str_check_char($string, $char){
	for($i = 0;$i < strlen($string);$i++){
		if($string[$i] == $char){
			return true;
			break;
		}
	}
}

function rndStr($length) {
    $keys = array_merge(range('A', 'Z'), range('a', 'z'));
	$key = "";
    for($i=0; $i < $length; $i++) {
        $key .= $keys[array_rand($keys)];
    }
    return $key;
}

// function from carbylamine php encoder.. :)
function striptag($in){
  $pos = strpos($in, "<?php");
  if (is_numeric($pos)){
      for ($i = $pos; $i <= $pos + 4 && strlen($in) >= 5; $i++) {
          $in[$i] = ' ';
      }
      return $in;
  }else{
      return $in;
  }
}


?>