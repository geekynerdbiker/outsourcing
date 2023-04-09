<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8"%>
<%@ page import="board.BoardDAO" %>
<%@ page import = "java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>

<jsp:useBean id="board" class="board.Board" scope="page"></jsp:useBean>
<jsp:setProperty name="board" property="boardTitle"/>
<jsp:setProperty name="board" property="boardContent"/>

<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; c harset=UTF-8">
  <title>JSP</title>
</head>
<body>
<%
  String userID = null;
  if (session.getAttribute("userID") != null){
    userID = (String) session.getAttribute("userID");
  }
  if (userID == null){
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('로그인하세요.')");
    script.println("location.href = 'login.jsp'");    // 메인 페이지로 이동
    script.println("</script>");
  }else{
    if (board.getBoardTitle() == null || board.getBoardContent() == null){
      PrintWriter script = response.getWriter();
      script.println("<script>");
      script.println("alert('모든 문항을 입력해주세요.')");
      script.println("history.back()");    // 이전 페이지로 사용자를 보냄
      script.println("</script>");
    }else{
      BoardDAO boardDAO = new BoardDAO();
      int result = boardDAO.write(board.getBoardTitle(), userID, board.getBoardContent());
      if (result == -1){ // 글쓰기 실패시
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('글쓰기에 실패했습니다.')");
        script.println("history.back()");    // 이전 페이지로 사용자를 보냄
        script.println("</script>");
      }else{ // 글쓰기 성공시
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("location.href = 'board.jsp'");    // 메인 페이지로 이동
        script.println("</script>");
      }
    }
  }
%>

</html>
</body>
