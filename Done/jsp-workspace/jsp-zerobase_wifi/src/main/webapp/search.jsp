<%@page import="db.DB"%>
<%@page import="db.data"%>
<%@page import="db.location"%>
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
	<%
	DB wifidb = new DB();
	String LAT = "";
	String LNT = "";
	String address = "";
	LAT = request.getParameter("LAT");
	LNT = request.getParameter("LNT");

	location gps = new location(LAT, LNT);
	address = gps.getRegionAddress();
	address = gps.getAddress()[2];
	wifidb.dbUpdate(LAT, LNT, address);
	wifidb.dbHistoryInsert(LAT, LNT);

	List<data> wifiList = wifidb.dbSelect(address);
	%>


	<h1>와이파이 정보 구하기</h1>

	<a href="WiFiHome.jsp">홈</a> |
	<a href="WiFiHistory.jsp">위치 히스토리 목록</a> |
	<a href="WiFiListImport.jsp">Open API 와이파이 정보 가져오기</a>

	<form action="WiFiSearch.jsp">
		LAT : <input type='text' name='LAT' value=<%=LAT%>> LNT : <input
			type='text' name='LNT' value=<%=LNT%>>
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

	주소 :
	<%=gps.getRegionAddress()%>


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
		<tbody>
			<%
			for (data wifi : wifiList) {
			%>
			<tr>
				<td><%=wifi.getDIST()%></td>
				<td><%=wifi.getMGR_NO()%></td>
				<td><%=wifi.getWRDOFC()%></td>
				<td><%=wifi.getMAIN_NM()%></td>
				<td><%=wifi.getADRES1()%></td>
				<td><%=wifi.getADRES2()%></td>
				<td><%=wifi.getINSTL_FLOOR()%></td>
				<td><%=wifi.getINSTL_TY()%></td>
				<td><%=wifi.getINSTL_MBY()%></td>
				<td><%=wifi.getSVC_SE()%></td>
				<td><%=wifi.getCMCWR()%></td>
				<td><%=wifi.getCNSTC_YEAR()%></td>
				<td><%=wifi.getINOUT_DOOR()%></td>
				<td><%=wifi.getREMARS3()%></td>
				<td><%=wifi.getLAT()%></td>
				<td><%=wifi.getLNT()%></td>
				<td><%=wifi.getWORK_DTTM()%></td>
			</tr>
			<%
			}
			%>
		</tbody>
	</table>

</body>
</html>


