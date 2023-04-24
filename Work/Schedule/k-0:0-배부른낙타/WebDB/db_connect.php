<?php

$host = "localhost";
$db_ID = "db2017150422";
$db_pw = "jskwak98@naver.com";
$db_name = "db2017150422";

$conn = mysqli_connect($host, $db_ID, $db_pw, $db_name);

if(!$conn) {
	echo "Connection Failed";
}

?>