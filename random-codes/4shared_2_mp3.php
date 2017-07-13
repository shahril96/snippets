// this shit is written as part of my project with my friends, but that idea was demolished
// this actually will try to find .mp3 direct link file from 4shared audio download link
// im surprised that this still working after 2 years i wrote this script
// btw, here you are, enjoy :) (warning: code looks suck!)

<?php

$shared = new four_shared;
//echo $shared->search('linkin park');
print_r($shared->take_link('https://www.4shared.com/mp3/1ZCsTQJY/fadirul_-_suasana_hari_raya_co.html'));


class four_shared {

	public function search($song){
	
		$form_data_search = array(
			"sortType" => 5,
			"sortOrder" => 1,
			"view" => "cl",
			"isSearchByTag" => 0,
			"searchmode" => 3,
			"searchName" => $song,
			"searchExtention" => "category:1"
		);
		
		$search_data = $this->curl("https://search.4shared.com/search.html", "search.view2=cl", $form_data_search);
		echo $search_data;
		
	}
	
	private function curl($url, $cookies = "", $post = ""){
		$ch = @curl_init();
		curl_setopt($ch, CURLOPT_URL, $url);
		curl_setopt($ch, CURLOPT_HEADER, 1);
		if($cookies) curl_setopt($ch, CURLOPT_COOKIE, $cookies);
		curl_setopt($ch, CURLOPT_USERAGENT, "Mozilla/5.0 (Windows NT 6.1) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/29.0.1521.3 Safari/537.36");
		curl_setopt($ch, CURLOPT_RETURNTRANSFER, 1);
		if($post){
			curl_setopt($ch, CURLOPT_POST, 1);
			curl_setopt($ch, CURLOPT_POSTFIELDS, $post); 
		}
		curl_setopt($ch, CURLOPT_SSL_VERIFYHOST, FALSE); 
		curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, FALSE);
		curl_setopt($ch, CURLOPT_TIMEOUT, 30); 
		curl_setopt($ch, CURLOPT_CONNECTTIMEOUT, 20);
		$page = curl_exec( $ch);
		curl_close($ch); 
		return $page;
    }
	
	public function take_link($fourshared_link){
	
		if(!preg_match('/http(s?):\/\/www\.4shared\.com\/mp3\/.*\/.*\.htm/', $fourshared_link)){
			return "Invalid Link";
		}else{
			$html = file_get_contents($fourshared_link);
			preg_match('/http(s?):\/\/[^www].*\.4shared\.com\/img\/.*\/preview.mp3/', $html, $link);
			return $link[0];
		}
		
	}
	
}


?>