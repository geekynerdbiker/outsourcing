<%@ page language="java" contentType="text/html; charset=UTF-8"
         pageEncoding="UTF-8" %>
    <%@ page import="project.UserDAO" %>
        <%@ page import="java.io.PrintWriter" %>
            <% request.setCharacterEncoding("UTF-8"); %>

                <jsp:useBean id="user" class="project.User" scope="page"></jsp:useBean>
                <jsp:setProperty name="user" property="userID" />
                <jsp:setProperty name="user" property="userPassword" />
                <jsp:setProperty name="user" property="userName" />
                <jsp:setProperty name="user" property="userGender" />
                <jsp:setProperty name="user" property="userEmail" />
                <jsp:setProperty name="user" property="userType" />
                <head>
                    <meta http-equiv="Content-Type" content="text/html; c harset=UTF-8">
                    <title>JSP</title>
                </head>

                <body>
                    <%
    String userID = null;
    if (session.getAttribute("userID") != null) {
        userID = (String) session.getAttribute("userID");
    }
    if (userID != null) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('이미 로그인되었습니다.')");
        script.println("location.href = 'main.jsp'");
        script.println("</script>");
    }
    if (user.getUserID() == null || user.getUserPassword() == null || user.getUserName() == null
            || user.getUserGender() == null || user.getUserEmail() == null || user.getUserType() == null) {
        PrintWriter script = response.getWriter();
        script.println("<script>");
        script.println("alert('모든 문항을 입력해주세요.')");
        script.println("history.back()");
        script.println("</script>");
    } else {
        UserDAO userDAO = new UserDAO();
        int result = userDAO.join(user);
        if (result == -1) {
            PrintWriter script = response.getWriter();
            script.println("<script>");
            script.println("alert('이미 존재하는 아이디입니다.')");
            script.println("history.back()");
            script.println("</script>");
        } else {
            PrintWriter script = response.getWriter();
            script.println("<script>");
            script.println("location.href = 'main.jsp'");
            script.println("</script>");
        }
    }
%>

                </body>

                </html>