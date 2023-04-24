<?php
include "../db_connect.php";
include "../util.php";
session_start();

$member_ID = $_SESSION['member_ID'];
$password = $_POST['password1'];

//transaction repeatable read
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level repeatable read");
mysqli_query($conn, "start transaction");

$sql = "update members set password = '$password' where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 수정하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}else{
	mysqli_query($conn, "commit");
	s_msg ('비밀번호를 수정했습니다');
    echo "<script>location.replace('../home.php');</script>";
}

?>