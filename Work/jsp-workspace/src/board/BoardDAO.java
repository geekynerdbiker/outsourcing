package board;

import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.PreparedStatement;
import java.sql.ResultSet;

public class BoardDAO {
    private Connection conn;
    private ResultSet rs;

    public BoardDAO() {
        try {
            String dbURL = "jdbc:mysql://localhost:3306/Board";
            String dbID = "root";
            String dbPassword = "aa1277aa!";
            Class.forName("com.mysql.jdbc.Driver");
            conn = DriverManager.getConnection(dbURL, dbID, dbPassword);
        }catch(Exception e) {
            e.printStackTrace();
        }
    }

    public String getDate() {
        String SQL = "SELECT NOW()";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getString(1);
            }
        }catch(Exception e) {
            e.printStackTrace();
        }
        return ""; //DB 오류
    }

    public int getNext() {
        String SQL = "SELECT boardID FROM Board ORDER BY boardID DESC";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            rs = pstmt.executeQuery();
            if (rs.next()) {
                return rs.getInt(1) + 1;
            }
            return 1;
        }catch(Exception e) {
            e.printStackTrace();
        }
        return -1; //DB 오류
    }

    public int write(String boardTitle, String userID, String boardContent){
        String SQL = "INSERT INTO Board VALUES (?, ?, ?, ?, ?, ?)";
        try {
            PreparedStatement pstmt = conn.prepareStatement(SQL);
            pstmt.setInt(1, getNext());
            pstmt.setString(2, boardTitle);
            pstmt.setString(3, userID);
            pstmt.setString(4, getDate());
            pstmt.setString(5, boardContent);
            pstmt.setInt(6, 1);
            return pstmt.executeUpdate();
        }catch(Exception e) {
            e.printStackTrace();
        }
        return -1; //DB 오류
    }
}