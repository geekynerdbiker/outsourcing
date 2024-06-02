package healthcare;

import java.sql.*;

public class Database {
    String url = "jdbc:mysql://localhost:3306/capstone";
    String userName = "root";
    String password = "root";

    Connection conn;

    public Database() throws SQLException {
        conn = DriverManager.getConnection(url, userName, password);
    }

    public void disconnect() throws SQLException {
        conn.close();
    }

    public boolean isIDExist(String id) throws SQLException {
        String sql = "select * from user where id = '" + id + "'";

        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(sql);

        return rs.next();
    }

    public boolean isCorrectPW(String id, String pw) throws SQLException {
        String sql = "select * from user where id = '" + id + "' and password = '" + pw + "'";

        Statement stmt = conn.createStatement();
        ResultSet rs = stmt.executeQuery(sql);

        return rs.next();
    }

    public int signUp(String id, String pw, String loc) throws SQLException {
        String sql = "insert into user values(?,?,?)";

        PreparedStatement stmt = conn.prepareStatement(sql);
        stmt.setString(1, id);
        stmt.setString(2, pw);
        stmt.setString(3, loc);

        return stmt.executeUpdate();
    }
}

