<?php
include 'header.php';
session_start();

if(isset($_SESSION['member_ID']) && isset($_SESSION['name'])){
	?>
	
	<!DOCTYPE html>
	<html>
		 
		<body>
			<div class='container'>
        	<p align="center"><img src="images/karaoke.png" width="30%"></p>
        		<h1>DB 노래방</h1>
				<h2><?php echo $_SESSION['name'];?>님 안녕하세요!</h2>
		</body>
	</html>
	<?php
}
else {
	header("Location: index.php");
	exit();
}
?>