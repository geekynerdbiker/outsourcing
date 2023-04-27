<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8" %>
<%@ page import="project.BoardDAO" %>
<%@ page import="java.io.PrintWriter" %>
<% request.setCharacterEncoding("UTF-8"); %>

<jsp:useBean id="board" class="project.Board" scope="page"></jsp:useBean>
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
  String userType = null;
  if (session.getAttribute("userID") != null){
    userID = (String) session.getAttribute("userID");
  }

  if (session.getAttribute("userType") != null){
    userType = (String) session.getAttribute("userType");
  }
  if (userID == null){
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('로그인하세요.')");
    script.println("location.href = 'login.jsp'");
    script.println("</script>");
  } else if (userType.compareTo("기업") != 0){
    PrintWriter script = response.getWriter();
    script.println("<script>");
    script.println("alert('기업 사용자가 아닙니다.')");
    script.println("</script>");
  }else{
    if (board.getBoardTitle() == null || board.getBoardContent() == null){
      PrintWriter script = response.getWriter();
      script.println("<script>");
      script.println("alert('모든 문항을 입력해주세요.')");
      script.println("history.back()");
      script.println("</script>");
    }else{
      BoardDAO boardDAO = new BoardDAO();
      int result = boardDAO.write(board.getBoardTitle(), userID, board.getBoardContent());
      if (result == -1){
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('글쓰기에 실패했습니다.')");
        script.println("history.back()");
        script.println("</script>");
      }else{
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("location.href = 'board.jsp'");
        script.println("</script>");
      }
    }
  }
%>

</html>
</body>
