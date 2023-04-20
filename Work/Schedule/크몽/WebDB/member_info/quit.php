<?php
include "../db_connect.php";
include "../util.php";
session_start();

$member_ID = $_SESSION['member_ID'];

//transaction repeatable read
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

//delete song requests;
$sql = "delete from requests where requester = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 신청곡 정보를 삭제하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}


//delete sing records;
$sql = "delete from sing where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 노래방 이용 정보를 삭제하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}

//delete voucher bought records;
$sql = "delete from voucher_record where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 이용권 구매 정보를 삭제하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}

//delete members;
$sql = "delete from members where member_ID = '$member_ID'";
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 삭제하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}

mysqli_query($conn, "commit");
s_msg ('회원 탈퇴 및 정보 삭제 완료');
echo "<script>location.replace('../index.php');</script>";

?>