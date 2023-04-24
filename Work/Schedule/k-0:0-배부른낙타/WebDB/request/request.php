<?php
include '../db_connect.php';
include '../header.php';
include '../util.php';
session_start();
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
		<div class="container">
			<form action="request_insert.php" method="post">
					<h3>신청곡 정보 입력</h3><br>
					<p>아래 리스트를 참고해 중복되지 않는 곡을 신청해주세요.</p><br>
					<label> 제목 </label>
					<input type="text" name="title" id="title" placeholder="제목"><br>
					<label> 장르 </label>
					<select name="genre" id = "genre">
		                    <option value="-1">선택해 주십시오.</option>
		                    <option value="가요">가요</option>
		                    <option value="힙합">힙합</option>
		                    <option value="댄스">댄스</option>
		                    <option value="발라드">발라드</option>
		            </select><br>
					<label> 가수 </label>
					<input type="text" name="singer" id="singer" placeholder="가수"><br>
					<button onclick="javascript:return validate();">신청</button>
			</form>
		    <?php
		    //commit된 신청곡만 읽어들인다.
			mysqli_query($conn, "set autocommit = 0");
			mysqli_query($conn, "set session transaction isolation level read committed");
			mysqli_query($conn, "start transaction");
		    $query = "select * from requests";
		    $result = mysqli_query($conn, $query);
		    if (!$result) {
				mysqli_query($conn, "rollback");
				s_msg('서버 오류로 신청곡 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
				echo "<meta http-equiv='refresh' content='0;url=request.php'";
			}
			mysqli_query($conn, "commit");
		    ?>
		    
		    <table class="table table-striped table-bordered">
		        <tr>
		            <th>No.</th>
		            <th>제목</th>
		            <th>장르</th>
		            <th>가수</th>
		            <th>신청자</th>
		            <th>기능</th>
		        </tr>
		        <?
		        $row_index = 1;
		        while ($row = mysqli_fetch_array($result)) {
		            echo "<tr>";
		            echo "<td>{$row_index}</td>";
		            echo "<td>{$row['title']}</td>";
		            echo "<td>{$row['genre']}</td>";
		            echo "<td>{$row['singer']}</td>";
		            echo "<td>{$row['requester']}</td>";
		            echo "<td width='17%'>
		            	<a href='request_modify_form.php?request_ID={$row['request_ID']}'><button>수정</button></a>
		            	<a href='request_delete.php?request_ID={$row['request_ID']}'><button>삭제</button></a>
		            	<a href='song_add.php?request_ID={$row['request_ID']}'><button>추가</button></a>
		                </td>";
		            echo "</tr>";
		            $row_index++;
		        }
		        ?>
		    </table>
		    <script>
		        function validate() {
		            if(document.getElementById("title").value == "") {
		                alert ("제목을 입력해 주십시오"); return false;
		            }
		            else if(document.getElementById("genre").value == "-1") {
		                alert ("장르를 입력해 주십시오"); return false;
		            }
		            else if(document.getElementById("singer").value == "") {
		                alert ("가수명을 입력해 주십시오"); return false;
		            }
		            return true;
		        }
		    </script>
		</div>
	</body>
</html>