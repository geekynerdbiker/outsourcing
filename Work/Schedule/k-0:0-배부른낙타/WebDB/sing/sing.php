<?php
include '../db_connect.php';
include '../header.php';
include '../util.php';
session_start();

$member_ID = $_SESSION['member_ID'];

//commit된 회원의 곡 충전 transaction 이후의 데이터만 불러오게 한다. 
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level read committed");
mysqli_query($conn, "start transaction");
$sql = "select available_songs from members where member_ID = '$member_ID'";
$result = mysqli_query($conn, $sql);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 회원정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=sing.php'";
}
else{
	mysqli_query($conn, "commit");
	$row = mysqli_fetch_array($result);
	$available_songs = $row['available_songs'];
}
?>
<div class="container">
    <form action="chart.php" method="post">
			<label> 곡 번호로 찾기 </label>
			<input type="text" name="song_ID" id="song_ID" placeholder="수록곡 번호 입력">
			<button type="submit" onclick="javascript:return validate_I();">검색</button><br>
	</form>
	<form action="chart.php" method="post">
			<label> 제목으로 찾기 </label>
			<input type="text" name="title" id="title" placeholder="수록곡 제목 입력">
			<button type="submit" onclick="javascript:return validate_t();">검색</button><br>
	</form>
	<form action="chart.php" method="post">
			<label> 가수명으로 찾기 </label>
			<input type="text" name="singer" id="singer" placeholder="가수명 입력">
			<button type="submit" onclick="javascript:return validate_s();">검색</button><br><br><br>
	</form>
	<a href='chart.php'><button>전체인기차트</button></a>
	<form action="chart.php" method="post">
		<a href='chart.php'><button onclick="javascript:return validate_g();">장르별 인기차트</button></a>
		<select name="genre" id = "genre">
                <option value="-1">장르 선택</option>
                <option value="가요">가요</option>
                <option value="힙합">힙합</option>
                <option value="댄스">댄스</option>
                <option value="발라드">발라드</option>
        </select>
	</form>
	<a href='mychart.php'><button>나의 애창곡</button></a><br><br>
	<h3>남은 곡 수 : <?php echo $available_songs;?></h3>
    <script>
        function validate_t() {
            if(document.getElementById("title").value == "") {
                alert ("제목을 입력해 주십시오"); return false;
            }
        }
        function validate_s() {
            if(document.getElementById("singer").value == "") {
                alert ("가수명을 입력해 주십시오"); return false;
            }
        }
        function validate_I() {
        	var id = document.getElementById("song_ID").value;
            if(isNaN(id) || id == "") {
                alert ("올바른 곡 번호를 입력해 주십시오"); return false;
            }
            return true;
        }
        function validate_g() {
        	var selection = document.getElementById('genre').value;
            if(selection == "-1") {
                alert ("장르를 입력해 주십시오"); return false;
            }
            return true;
        }
    </script>
</div>