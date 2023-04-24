<?php
include "../db_connect.php";
include "../util.php";
session_start();

$member_ID = $_SESSION['member_ID'];

//transaction serializable
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

$sql = "select available_songs from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
$row = mysqli_fetch_array($result);
$songs_left = $row['available_songs'];

$sql = "select sing_ID from sing where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 노래방 이용 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
$used = mysqli_num_rows($result) != 0;

$sql = "SELECT buy_ID, price, num_songs FROM voucher_record natural join vouchers";
$sql .= " WHERE member_ID='$member_ID' AND bought_time";
if ($used){
	$sql .= " > (SELECT max(sing_time) FROM sing WHERE member_ID = '$member_ID')";
}

$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 구매 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}if (mysqli_num_rows($result) == 0){
	msg('환불 가능한 이용권이 없습니다.');
}

$counts = 0;
$total = 0;
while ($row = mysqli_fetch_array($result)){
	$buy_ID = $row['buy_ID'];
	$total += $row['price'];
	$songs_left -= $row['num_songs'];
	$counts ++;
	$sql2 = "delete from voucher_record where buy_ID = '$buy_ID'";
	$result2 = mysqli_query($conn, $sql2);
	if (!$result2) {
		mysqli_query($conn, "rollback");
		s_msg('서버 오류로 이용권 구매 내역을 삭제하는 데에 실패해습니다. 다시 시도해주세요');
		echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
	}
}

$sql = "update members set available_songs = '$songs_left' where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 업데이트 하는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
}
mysqli_query($conn, "commit");

$msg = "총 {$counts}개의 환불이 진행되어 {$total}원이 환불되었습니다. 남은 곡 수는 {$songs_left}입니다.";
echo "<script>alert('{$msg}');</script>";
echo "<script>location.replace('voucher.php');</script>";
?>