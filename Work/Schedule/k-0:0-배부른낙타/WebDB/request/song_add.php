<?php
include "../util.php";
include "../db_connect.php";    //데이터베이스 연결 설정파일
session_start();

$admin = $_SESSION['admin'];

if(!$admin){
	msg('관리자 권한이 있는 사람만 수록곡 추가가 가능합니다.');
}
$request_ID = $_GET['request_ID'];

//transaction serializable
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

$sql = "select title, genre, singer from requests where request_ID = '$request_ID'";

$result = mysqli_query($conn, $sql);

if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 신청곡 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=request.php'";
}
else{
	$row = mysqli_fetch_array($result);
	$title = $row['title'];
	$genre = $row['genre'];
	$singer = $row['singer'];
	
	$sql = "insert into song (title, genre, singer) values ('$title', '$genre', '$singer')";
	$result = mysqli_query($conn, $sql);
	if (!$result) {
		mysqli_query($conn, "rollback");
		s_msg('서버 오류로 신청곡 정보를 추가하는 데에 실패해습니다. 다시 시도해주세요');
		echo "<meta http-equiv='refresh' content='0;url=request.php'";
	}
	//수록곡을 추가했다면, 신청곡을 삭제한다.
	else{
    	s_msg ('신청곡이 추가되었습니다');
    	$sql = "Delete from requests where request_ID = '$request_ID'";
    	$result = mysqli_query($conn, $sql);
		if (!$result) {
			mysqli_query($conn, "rollback");
			s_msg('서버 오류로 신청곡 정보를 삭제하는 데에 실패해습니다. 다시 시도해주세요');
			echo "<meta http-equiv='refresh' content='0;url=request.php'";
		}
		else
		{
			mysqli_query($conn, "commit");
		    s_msg ('신청곡이 삭제되었습니다');
		    echo "<script>location.replace('request.php');</script>";
		}
	}
}

?>
