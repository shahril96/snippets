<?php

/*
 * title     : simple instagram info fetcher
 *
 * author    : shahril
 * receipant : afif zafri
 * date      : 29-dis-2015
 */

$username = 'mohdshahrilzainol';

//
//
// code start here
//
//
function http_request($url, $post = "", $cookies = "", $headers = "", $show_header = true) {
	$ch = @curl_init();
	curl_setopt($ch, CURLOPT_URL, $url);
	curl_setopt($ch, CURLOPT_HEADER, $show_header);
	curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
	if ($post) {
		curl_setopt($ch, CURLOPT_POST, 1);
		curl_setopt($ch, CURLOPT_POSTFIELDS, $post);
	}
	if ($cookies) {
		curl_setopt($ch, CURLOPT_COOKIE, $cookies);
	}
	if ($headers) {
		curl_setopt($ch, CURLOPT_HTTPHEADER, $headers);
	}
	curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE);
	curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
	curl_setopt($ch, CURLOPT_TIMEOUT, 30);
	curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 20);
	$page = curl_exec($ch);
	curl_close($ch);
	return $page;
}

$data = http_request("https://www.instagram.com/{$username}/");
file_put_contents("insta.html", $data);

preg_match_all('#\_sharedData \= (.*?)\;\<\/script\>#', $data, $out);
$object = json_decode($out[1][0]);
$userObj = $object->entry_data->ProfilePage[0]->user;
$mediaObj = $userObj->media;

$ret = array();

// get number of photos + videos + others (integer)
$ret['number_of_media'] = $mediaObj->count;

// information about those medias (array)
$ret['info_each_media'] = $mediaObj->nodes;

// fetch next medias
// initial media info is 24, (dats y i minus 24)
// each /query request give us next 32 media info, (dats y i minus 32)
for($count = $mediaObj->count - 33; $count > 0; $count -= 33) {

    $n = count($ret['info_each_media']);
    $last_media_id = $ret['info_each_media'][$n-1]->id;

    $post_data = "q=ig_user({$userObj->id})+%7B+media.after({$last_media_id}%2C+33)+%7B%0A++count%2C%0A++nodes+%7B%0A".
                 "++++caption%2C%0A++++code%2C%0A++++comments+%7B%0A++++++count%0A++++%7D%2C%0A++++date%2C%0A++++dim".
                 "ensions+%7B%0A++++++height%2C%0A++++++width%0A++++%7D%2C%0A++++display_src%2C%0A++++id%2C%0A++++is_".
                 "video%2C%0A++++likes+%7B%0A++++++count%0A++++%7D%2C%0A++++owner+%7B%0A++++++id%0A++++%7D%2C%0A++++th".
                 "umbnail_src%0A++%7D%2C%0A++page_info%0A%7D%0A+%7D&ref=users%3A%3Ashow";

	preg_match_all('/Set-Cookie: (.*);/U', $data, $cookies); // get all cookies
	preg_match('#csrftoken\=(.*?)\;#', $data, $csrftoken); // get only csrf token

	// instagram nak header bwh nie, klau tidak nnti return FORBIDDEN
	$headers = array();
	$headers[] = "Referer:https://www.instagram.com/{$username}/";
	$headers[] = "X-CSRFToken:" . $csrftoken[1];

    $get = http_request("https://www.instagram.com/query/", $post_data, implode('; ', $cookies[1]), $headers, false);

    $jsondec = json_decode($get);

	if(!$jsondec || $jsondec->status != 'ok') {
		die("error");
	}

	// append next medies into last array
	$ret['info_each_media'] = array_merge($ret['info_each_media'], $jsondec->media->nodes);
}

//
//
// code end here
//
//

# contoh cara nk guna
# nk cari summation number of likes

$sum = 0;

$highest_like_index = 0;
$highest_like = 0;

foreach($ret['info_each_media'] as $index => $each_media) {

	$sum += $each_media->likes->count;

	if($each_media->likes->count > $highest_like) {
		$highest_like_index = $index;
		$highest_like = $each_media->likes->count;
	}
}

echo "\nNumber of instagram media(s) : " . $ret['number_of_media'] . "\n\n";
echo "Summation of likes : " . $sum . "\n\n";
echo "Info about highest liked photo : \n\n";
var_dump($ret['info_each_media'][$highest_like_index]);

?>
