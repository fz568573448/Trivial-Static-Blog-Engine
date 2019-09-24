<?php
    require 'simple_html_dom.php';
    date_default_timezone_set('Asia/Shanghai');
    $postnum=$_SERVER['argv'][1];
    $myfile = fopen("feed", "w") or die("Unable to open file!");
    
    function getItem($id)
    {
        $data=file_get_contents("archives/$id");
        $dom = new simple_html_dom();
        $dom->load($data);
        $title=trim($dom->find('h1.title a',1)->innertext);
        $date=date(DATE_RFC2822,strtotime(trim($dom->find('span.date',0)->plaintext)));
        $tagst=$dom->find('span.tags a');
        $tags='';
        foreach ($tagst as $i => $tag)
            $tags.='<category><![CDATA['.trim($tag->innertext).']]></category>';
        
        // var_dump($tags);
        // system("pause");
        $post=trim($dom->find('div.post_body',0)->innertext);
        $des=mb_substr(strip_tags($post),0,200).'......';
        
        $item=<<<ITEM
        <item>
            <title>$title</title>
            <link>https://YourSite.org/archives/$id</link>
            <comments>https://YourSite.org/archives/$id#comments</comments>
            <pubDate>$date</pubDate>
            $tags
            <guid isPermaLink="false">https://YourSite.org/archives/$id</guid>
            <description><![CDATA[$des]]></description>
            <content:encoded><![CDATA[$post]]></content:encoded>
        </item>
        
ITEM;
        return $item;
    }
    $items='';
    $postst=max(0,$postnum-9);
    for ($i=$postnum;$i>=$postst;$i--)
        $items.=getItem($i);
    
    $lastBuildDate=date(DATE_RFC2822);
    
    $feed=<<<CONTENT
<?xml version="1.0" encoding="UTF-8"?>
<rss version="2.0" xmlns:content="http://purl.org/rss/1.0/modules/content/">
    <channel>
        <title><![CDATA[YourSite's Blog]]></title>
        <link>https://YourSite.org/</link>
        <description><![CDATA[YourSite's Blog]]></description>
        <lastBuildDate>$lastBuildDate</lastBuildDate>
        <language>zh-CN</language>
        <generator>You</generator>
        
$items
    </channel>
</rss>

CONTENT;
    fwrite($myfile,$feed);
    fclose($myfile);
?>
