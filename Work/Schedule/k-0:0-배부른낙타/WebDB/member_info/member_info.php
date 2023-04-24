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

$sql = "select available_songs from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=member_info.php'";
}
mysqli_query($conn, "commit");
$row = mysqli_fetch_array($result);
$available_songs = $row['available_songs'];
?>
<html>
	<form action="password_change.php" method="post">
			<br><br>
			<h3>비밀번호 변경</h3><br>
			<input type="password" name="password1" id="password1" placeholder="새 비밀번호 입력"><br>
			<input type="password" name="password2" id="password2" placeholder="비밀번호 재입력"><br>
			<button type="submit" onclick="javascript:return validate_ps();">입력</button><br><br><br>
	</form>
	
	<form action="quit.php" method="post">
			<br><br>
			<h3>회원탈퇴</h3><br>
			<button type="submit" onclick="javascript:return deleteConfirm();"><h4>회원탈퇴</h4></button><br><br><br>
	</form>
</html>
<script>
	function validate_ps() {
			var password1 = document.getElementById('password1').value;
        	var password2 = document.getElementById('password2').value;
            if(password1 != password2) {
                alert ("입력한 새 비밀번호가 다릅니다. 다시 확인해주세요."); return false;
            }
            return true;
	}
	function deleteConfirm() {
		var songs = "<?php echo $available_songs;?>";
		if (songs != 0){
			alert ("이용 곡수가 남아있습니다. 환불하거나, 모두 이용한 후 탈퇴 가능합니다.");
			return false;
		}else{
            if (confirm("정말 회원을 탈퇴하시겠습니까?") == true){
            	return true;
    		}else{   //취소
                return false;
            }
		}
    }
</script>