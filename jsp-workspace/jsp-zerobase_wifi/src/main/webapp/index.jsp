<%@page import="db.DB"%>
<%@page import="db.data"%>
<%@page import="java.util.*"%>
<%@ page language="java" contentType="text/html; charset=UTF-8"
	pageEncoding="UTF-8"%>
<!DOCTYPE html>
<html>
<head>
<style>
#WifiDetail {
	font-family: Arial, Helvetica, sans-serif;
	border-collapse: collapse;
	width: 100%;
}

#WifiDetail td, #WifiDetail th {
	border: 1px solid #ddd;
	padding: 8px;
}

#WifiDetail tr:nth-child(even) {
	background-color: #f2f2f2;
}

#WifiDetail tr:hover {
	background-color: #ddd;
}

#WifiDetail th {
	padding-top: 12px;
	padding-bottom: 12px;
	text-align: left;
	background-color: #04AA6D;
	color: white;
}
</style>
</head>
<body>
	<h1>와이파이 정보 구하기</h1>


	<a href="index.jsp">홈</a> |
	<a href="history.jsp">위치 히스토리 목록</a> |
	<a href="load-wifi.jsp">Open API 와이파이 정보 가져오기</a>
	<br>

	<form action="search.jsp">
		LAT : <input type='text' name='LAT'> 
		LNT : <input type='text' name='LNT'>
		<button type='submit' onclick="getCurrent()">
			내 위치 가져오기</button>
			
		<script>
			function getCurrent() {
				if (!navigator.geolocation) {
		            throw "위치 정보가 지원되지 않습니다.";
		        }
		        navigator.geolocation.getCurrentPosition(success);
			}
		</script>
		<button type='submit' onclick="location.href='search.jsp'">
			근처 WIFI 정보 보기</button>
	</form>

	<table id="WifiDetail">
		<thead>
			<tr>
				<th>거리(Km)</th>
				<th>관리번호</th>
				<th>자치구</th>
				<th>와이파이명</th>
				<th>도로명주소</th>
				<th>상세주소</th>
				<th>설치위치(층)</th>
				<th>설치유형</th>
				<th>설치기관</th>
				<th>서비스구분</th>
				<th>망종류</th>
				<th>설치년도</th>
				<th>실내외구분</th>
				<th>WiFi접속환경</th>
				<th>X좌표</th>
				<th>Y좌표</th>
				<th>작업일자</th>
			</tr>
		</thead>
	</table>

</body>
</html>


