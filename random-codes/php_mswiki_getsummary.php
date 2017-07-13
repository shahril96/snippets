<?php

// simple usage..
echo get_wiki_summary_ms('php');

/**
 * Error Code :-
 * 3 - search x dijumpai..
 * 4 - php gagal nk dptkan content dari wikipedia page..
 */
function get_wiki_summary_ms($search){

  // search keyword dkt wikipedia bahasa melayu..
  $search_wiki = file_get_contents('https://ms.wikipedia.org/w/index.php?search='.urlencode($search).'&button=&title=Khas%3AGelintar');
  
  if(strpos($search_wiki, '<title>Hasil carian')){
  
    // kalau lepas carian dia x auto direct ke wiki content page, dia scrap data dkt search page pulak..
    if(strpos($search_wiki, 'hasil yang sepadan')) return 3;
    preg_match('/\<a\ href\=\"(\/wiki\/.*?)\"\ title\=\"/', $search_wiki, $search_ngn);
    
    // dh dpt jumpa page yng betul, request sekali lagi page tu then mskkan ke var $data..
    $data = file_get_contents('https://ms.wikipedia.org'.$search_ngn[1]);
    
  } else { 
  
    // kalau auto direct, masukkan je terus data page tu dalam var $data..
    $data = $search_wiki;
  }
  preg_match_all('/\<p\>(.*?)\<\/p\>/', $data, $out);
  
  // loop dkt bawah nie buat checking kalau ada multiple <p></p>
  $chk = false; // guna untuk simpan boolean smada php dpt parse content wiki or dop..
  foreach($out[1] as $get_text){
    $strip = strip_tags($get_text);
    
    // checking, korng leh improve content checking dkt sini.. ;)
    if(strlen($strip) > 60 && !strpos($get_text, '//upload.wiki')){
      $out[0] = $get_text;
      $chk = true;
      break;
    }
  }
  
  if(!$chk) return 4; // kalau x dpt nk parse content dlm wiki tu, dia return error code 4
  $summary = preg_replace('/[\x00-\x1F\x80-\xFF]/', '', strip_tags($out[0])); // buang character yg bukan ascii..
  $summary = preg_replace('/\[\d{1,4}\]/', '', $summary); // buang bracket string mcm [1] or [12]
  return $summary;
}

?>