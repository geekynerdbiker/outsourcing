<html>
	<form action="add_member.php" method="post">
			<br><br>
			<h3>회원정보 입력</h3><br>
			<label>ID</label>
			<input type="text" name="member_ID" id="member_ID" placeholder="12자 이내 영문+숫자"><br>
			<label>이름</label>
			<input type="text" name="name" id="name" placeholder="5자 이내 한글 또는 영문"><br>
			<label>비밀번호</label>
			<input type="password" name="password1" id="password1" placeholder="12자 이내 영문+숫자"><br>
			<label>비밀번호 재입력</label>
			<input type="password" name="password2" id="password2" placeholder="비밀번호 재입력"><br>
			<button type="submit" onclick="javascript:return validate();">가입</button><br><br><br>
	</form>
</html>
<script>
	function validate() {
			var ID = document.getElementById('member_ID').value;
			var name = document.getElementById('name').value;
			var password1 = document.getElementById('password1').value;
        	var password2 = document.getElementById('password2').value;
        	
        	var engCheck = /[a-z]/;
	        var numCheck = /[0-9]/;
    		var specialCheck = /[`~!@#$%^&*|\\\'\";:\/?]/gi;

            if(ID == "" || ID.length > 12){
            	alert ("ID 길이가 잘못되었습니다"); return false;
            }else if(name == "" || name.length > 5){
            	alert ("이름의 길이가 잘못되었습니다"); return false;
            }else if(password1 == "" || password1.length > 12){
            	alert ("비밀번호의 길이가 잘못되었습니다"); return false;
            }else if(specialCheck.test(ID)){
            	alert ("ID는 특수문자가 포함될 수 없습니다"); return false;
            }else if(specialCheck.test(name) || numCheck.test(name)){
            	alert ("이름에는 숫자나 특수문자가 포함될 수 없습니다"); return false;
            }else if(password1 != password2) {
                alert ("입력한 비밀번호가 서로 다릅니다. 다시 확인해주세요."); return false;
            }
            return true;	
	}
</script>