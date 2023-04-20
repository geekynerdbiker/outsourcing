<?php
include "../util.php";
include "../db_connect.php";
session_start();

$song_ID = $_GET['song_ID'];
$available_songs = $_GET['available_songs']-1;
$member_ID = $_SESSION['member_ID'];

// Transaction, 동일 테이블에 2 번 접근하는 경우가 생기므로, Repeatable Read를 보장해주는 것이
// 안전하다. 이전 세션에서 찾은 Song과 Member ID를 기준으로 실행하기에 Phantom Read는 일어나지 않을 것.
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level repeatable read");
mysqli_query($conn, "start transaction");

//add record
$sql = "insert into sing (member_ID, song_ID, sing_time) values ('$member_ID', '$song_ID', NOW())";
$result = mysqli_query($conn, $sql);
if(!$result)
{	
	mysqli_query($conn, "rollback");
    msg('Query Error : '.mysqli_error($conn));
}

//increment
$sql = "select title, count from song where song_ID = '$song_ID'";
$result = mysqli_query($conn, $sql);
if(!$result)
{	
	mysqli_query($conn, "rollback");
    msg('Query Error : '.mysqli_error($conn));
}
$row = mysqli_fetch_array($result);
$title = $row['title'];
$count = $row['count'] + 1;
$sql = "update song set count = '$count' where song_ID='$song_ID'";
$result = mysqli_query($conn, $sql);
if(!$result)
{
	mysqli_query($conn, "rollback");
    msg('Query Error : '.mysqli_error($conn));
}

//decrement
$sql = "update members set available_songs = '$available_songs' where member_ID='$member_ID'";
$result = mysqli_query($conn, $sql);
if(!$result)
{
	mysqli_query($conn, "rollback");
    msg('Query Error : '.mysqli_error($conn));
}else{
	mysqli_query($conn, "commit");
    s_msg ("{$title} 곡을 불렀습니다.");
    echo "<script>location.replace('chart.php');</script>";
}
?>
