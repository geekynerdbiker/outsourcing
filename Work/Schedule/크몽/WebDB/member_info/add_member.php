<?php
include "../db_connect.php";
include "../util.php";

$member_ID = $_POST['member_ID'];
$name = $_POST['name'];
$password = $_POST['password1'];

//transaction serializable
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

//uniqueness check
$sql = "select * from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=sign_up.php'";
}
if (mysqli_num_rows($result) != 0){
	msg('이미 존재하는 ID입니다');
}

$sql = "insert into members (member_ID, name, password) values ('$member_ID', '$name', '$password')";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 추가하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=sign_up.php'";
}
else{
	mysqli_query($conn, "commit");
	s_msg('회원가입 성공');
	echo "<script>location.replace('../index.php');</script>";
}
?>
