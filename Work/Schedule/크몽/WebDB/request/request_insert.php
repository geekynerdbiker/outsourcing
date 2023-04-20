<?php
include "../util.php";
include "../db_connect.php";
session_start();

$title = $_POST['title'];
$genre = $_POST['genre'];
$singer = $_POST['singer'];
$requester = $_SESSION['member_ID'];

//transaction serializable
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

// 신청곡 중복 체크
$sql = "select * from requests where title = '$title' and genre = '$genre' and singer = '$singer'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 신청곡 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=request.php'";
}
$count = mysqli_num_rows($result);
if($count){
	msg('이미 신청된 신청곡입니다.');
}

// 수록곡 중복 체크
$sql = "select * from song where title = '$title' and genre = '$genre' and singer = '$singer'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 수록곡 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=request.php'";
}
$count = mysqli_num_rows($result);
if($count){
	msg('이미 수록된 곡입니다.');
}

$sql = "insert into requests (title, genre, singer, requester) values ('$title', '$genre', '$singer', '$requester')";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 수록곡 정보를 추가하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=request.php'";
}
else
{
	mysqli_query($conn, "commit");
    s_msg ('성공적으로 신청되었습니다');
    echo "<script>location.replace('request.php');</script>";
}

?>
