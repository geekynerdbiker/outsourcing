<!DOCTYPE html>
<html>
	<head>
		<title> Login </title>
	</head>
	<body>
		<form action="login.php" method="post">
			<h2>DB 노래방 접속 화면</h2><br><br><br>
			<?php if(isset($_GET['error'])) { ?>
			<p class="error"> <?php echo $_GET['error']; ?></p>
			<?php } ?>
			<label> ID </label>
			<input type="text" name="ID" placeholder="ID"><br><br>
			<label> 비밀번호 </label>
			<input type="password" name="password" placeholder="비밀번호"><br><br><br>
			
			<button type="submit"><h4>Login</h4></button>
		</form>
		<br>
		<a href='member_info/sign_up.php'><button type="submit"><h4>Sign Up</h4></button></a>
	</body>
</html>