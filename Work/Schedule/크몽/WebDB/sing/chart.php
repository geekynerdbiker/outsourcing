<?php
include 'sing.php';
session_start();

$query = "select * from song";

//번호 검색
if (array_key_exists("song_ID", $_POST)) { 
    $song_ID = $_POST["song_ID"];
    $query .= " where song_ID = '$song_ID'";
}
//제목 검색
else if (array_key_exists("title", $_POST)) { 
    $title = $_POST["title"];
    $query .= " where title like '%$title%'";
}
//가수 검색
else if (array_key_exists("singer", $_POST)) { 
    $singer = $_POST["singer"];
    $query .= " where singer like '%$singer%'";
}
//장르 인기차트
else if (array_key_exists("genre", $_POST)) { 
    $genre = $_POST["genre"];
    $query .= " where genre = '$genre' order by count desc";
}
// 전체 인기차트
else { 
    $query .= " order by count desc";
}
// Transaction, 불린 횟수를 기준으로 sort한 table을 읽어온다. 따라서 읽는 과정중 
// phantom read가 발생하면 곤란하다. 멀쩡한 수록곡이 노출되지 않는 등의 문제가
// 발생할 수 있다.
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level serializable");
mysqli_query($conn, "start transaction");
$result = mysqli_query($conn, $query);
if (!$result) {
    mysqli_query($conn, "rollback");
	s_msg('서버 오류로 차트를 불러오는 데에 실패해습니다. 다시 시도해주세요');
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
	            <th>불린 회수</th>
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
	            echo "<td>{$row['count']}</td>";
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
    
    
    
    
    
    