<?php
include '../db_connect.php';
include '../header.php';
include '../util.php';
session_start();

//transaction read committed
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level read comitted");
mysqli_query($conn, "start transaction");

$sql = 'select * from vouchers';
$result = mysqli_query($conn, $sql);
if (!$result) {
	mysqli_query($conn, "rollback");
	s_msg('서버 오류로 이용권 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
	echo "<meta http-equiv='refresh' content='0;url=voucher.php'";
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
		<div class="container">
		    <table class="table table-striped table-bordered">
		        <tr>
		            <th>No.</th>
		            <th>가격</th>
		            <th>곡 수</th>
		            <th>구입</th>
		        </tr>
		        <?
		        $row_index = 1;
		        while ($row = mysqli_fetch_array($result)) {
		            echo "<tr>";
		            echo "<td>{$row_index}</td>";
		            echo "<td>{$row['price']}원권</td>";
		            echo "<td>{$row['num_songs']}</td>";
		            echo "<td width='17%'>
		            	<a href='buy_voucher.php?voucher_ID={$row['voucher_ID']}'><button>구매</button></a>
		                </td>";
		            echo "</tr>";
		            $row_index++;
		        }
		        ?>
		    </table>
			    <br><br>
			    <a href="refund.php"><button type="submit" onclick="javascript:return refundConfirm();"><h4>환불</h4></button></a>
		    </form>
		</div>
	</body>
</html>
<script>
	function refundConfirm() {
            if (confirm("가장 최근에 노래방을 이용한 시간 이후에 구매한 교환권에 대해서만 환불이 가능합니다. 진행하시겠습니까?") == true){    //확인
                return true;
            }else{   //취소
                return false;
            }
        }
</script>