<?php
session_start();
include "../header.php";
include "../db_connect.php";
include "../util.php";

$member_ID = $_SESSION['member_ID'];

//transaction repeatable read
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level repeatable read");
mysqli_query($conn, "start transaction");

$sql = "select password from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=gain_access.php'";
}
mysqli_query($conn, "commit");
$row = mysqli_fetch_array($result);
$password = $row['password'];

?>
<html>
	<form action="member_info.php" method="post">
			<br><br>
			<h3>비밀번호를 입력해주세요</h3><br>
			<input type="password" name="password" id="password" placeholder="비밀번호 입력">
			<button type="submit" onclick="javascript:return validate_p();">입력</button><br><br><br>
	</form>
</html>
<script>
	function validate_p() {
			var original = "<?php echo $password;?>";
        	var password = document.getElementById('password').value;
            if(original != password) {
                alert ("비밀번호가 틀립니다."); return false;
            }
            return true;
	}
</script>