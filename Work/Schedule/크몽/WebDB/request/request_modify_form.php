<?
include "../header.php";
include "../db_connect.php";
include "../util.php";
session_start();


$request_ID = $_GET["request_ID"];

//repeatable하게 신청곡 정보를 읽는다.
mysqli_query($conn, "set autocommit = 0");
mysqli_query($conn, "set session transaction isolation level repeatable read");
mysqli_query($conn, "start transaction");
$query =  "select * from requests where request_ID = $request_ID";
$result = mysqli_query($conn, $query);
if (!$result) {
		mysqli_query($conn, "rollback");
		s_msg('서버 오류로 신청곡 정보를 불러오는 데에 실패해습니다. 다시 시도해주세요');
		echo "<meta http-equiv='refresh' content='0;url=request.php'";
}
mysqli_query($conn, "commit");
$request = mysqli_fetch_array($result);
if($request['requester'] != $_SESSION['member_ID']) {
    msg("신청곡 수정은 신청자만 할 수 있습니다.");
}
$mode = "수정";
$action = "request_modify.php";


$genres = array('가요', '댄스', '힙합', '발라드')
?>
    <div class="container">
        <form name="request_form" action="<?=$action?>" method="post" class="fullwidth">
            <input type="hidden" name="request_ID" value=<?=$request['request_ID']?>/>
            <h3>수록곡 <?=$mode?></h3>
            <p>
                <label for="title">제목</label>
                <input type="text" placeholder="제목 입력" id="title" name="title" value="<?=$request['title']?>"/>
            </p>
            <p>
                <label for="genre">장르</label>
                <select name="genre" id="genre">
                    <option value="-1">선택해 주십시오.</option>
                    <?
                        foreach($genres as $value) {
                            if($value == $request['genre']){
                                echo "<option value='{$value}' selected>{$value}</option>";
                            }else {
                                echo "<option value='{$value}'>{$value}</option>";
                            }
                        }
                    ?>
                </select>
            </p>
            <p>
                <label for="singer">가수</label>
                <input type="text" placeholder="가수명" id="singer" name="singer" value="<?=$request['singer']?>"/>
            </p>
            <p align="center"><button class="button primary large" onclick="javascript:return validate();"><?=$mode?></button></p>

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

        </form>
    </div>