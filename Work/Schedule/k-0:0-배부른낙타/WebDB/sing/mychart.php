<?php
include 'sing.php';
session_start();

$member_ID = $_SESSION['member_ID'];

$query =  "select song_ID, title, genre, singer, count(song_ID) as num_sing";
$query .= " from sing natural join song where member_ID = '$member_ID'";
$query .= " group by song_ID order by num_sing desc";

// Transaction, 부른 횟수를 기준으로 sort한 table을 읽어온다. 내가 부르지 않은 곡은 불러오지
// 않으므로, 또한 검색 중에는 노래하지 않으므로 isolation level을 낮춰도 문제 없다.
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level read committed");
mysqli_query($conn, "start transaction");
$result = mysqli_query($conn, $query);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 애창곡 리스트를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=sing.php'";
}
mysqli_query($conn, "commit");
?>
<html>
	<head>
		<style>
			table{
				border: 2px solid;
				border-collapse:collapse;
			}
			th, td {border: 1px solid; padding: 10px 5px;}
		</style>
	</head>
	<body>
		<table>
		        <tr>
		            <th>No.</th>
		            <th>곡 번호</th>
		            <th>제목</th>
		            <th>장르</th>
		            <th>가수</th>
		            <th>부른 회수</th>
		            <th>부르기</th>
		        </tr>
		        <?
		        $row_index = 1;
		        while ($row = mysqli_fetch_array($result)) {
		            echo "<tr>";
		            echo "<td>{$row_index}</td>";
		            echo "<td>{$row['song_ID']}</td>";
		            echo "<td>{$row['title']}</td>";
		            echo "<td>{$row['genre']}</td>";
		            echo "<td>{$row['singer']}</td>";
		            echo "<td>{$row['num_sing']}</td>";
		            echo "<td width='17%'>
		            	<a href='sing_song.php?song_ID={$row['song_ID']}&available_songs={$available_songs}'><button onclick='javascript:return can_sing();'>부르기</button></a>
		            	</td>";
		            echo "</tr>";
		            $row_index++;
		        }
		        ?>
		</table>
	</body>
</html>
<script>
	function can_sing() {
        	var songs = "<?php echo $available_songs;?>";
            if(songs == 0) {
                alert ("곡 충전량이 부족합니다. 이용권을 구매해 주세요."); return false;
            }
        }
</script>
    
    
    
    
    
    