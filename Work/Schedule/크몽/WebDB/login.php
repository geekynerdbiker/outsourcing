<?php
session_start();
include "db_connect.php";

$ID = $_POST['ID'];
$password = $_POST['password'];


if(empty($ID))	{
	header ("Location: index.php?error=ID 미입력");
	exit();
}
else if(empty($password))	{
	header ("Location: index.php?error=비밀번호 미입력");
	exit();
}
// Transaction
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");

$sql = "SELECT * FROM members where member_ID ='$ID' and password = '$password'";

$result = mysqli_query($conn, $sql);

if (!$result){
	mysqli_query($conn, "rollback");
	header("Location: index.php?error=서버 오류로 인한 로그인 실패, 다시 시도해주세요.");
	exit();
}
else if(mysqli_num_rows($result) === 1) {
	mysqli_query($conn, "commit");
	$row = mysqli_fetch_assoc($result);
	if($row['member_ID'] === $ID && $row['password'] === $password) {
		echo "로그인 완료";
		$_SESSION['member_ID'] = $row['member_ID'];
		$_SESSION['name'] = $row['name'];
		$_SESSION['available_songs'] = $row['available_songs'];
		$_SESSION['admin'] = $row['admin'];
		header("Location: home.php");
		exit();
	}
}
else{
	header("Location: index.php?error=로그인 실패, ID나 비밀번호를 확인하세요");
	exit();
}