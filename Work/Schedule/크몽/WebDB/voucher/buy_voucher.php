<?php
include '../db_connect.php';
include '../util.php';
session_start();

$member_ID = $_SESSION['member_ID'];
$voucher_ID = $_GET['voucher_ID'];

//transaction repeatable read
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level repeatable read");
mysqli_query($conn, "start transaction");

$sql = "select num_songs from vouchers where voucher_ID = '$voucher_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 이용권 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
$row = mysqli_fetch_array($result);
$songs = $row['num_songs'];

$sql = "select * from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
$row = mysqli_fetch_array($result);
$current_songs = $row['available_songs'];

$total = $songs + $current_songs;
$sql = "update members set available_songs = '$total' where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 업데이트 하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}

$sql = "insert into voucher_record (voucher_ID, member_ID, bought_time) values ('$voucher_ID', '$member_ID', NOW())";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 구매 정보를 추가하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
else
{
	mysqli_query($conn, "commit");
    s_msg ("성공적으로 구매했습니다. 충전된 곡수 : {$total}");
    echo "<script>location.replace('voucher.php');</script>";
}
?>