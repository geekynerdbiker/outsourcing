package DB.DAO;

import java.sql.*;
import DB.DBConnection;

public class BookLoanDAO {
    public static void borrowBook(int studentId, String bookIsbn) {
        String findCourseDeptQuery =
                "SELECT cd.dept_name FROM Reference_book rb JOIN Teaches t ON rb.book_id = t.book_id " +
                        "JOIN Section s ON t.sec_id = s.sec_id AND t.semester = s.semester AND t.year = s.year " +
                        "JOIN Course_Dept cd ON s.course_id = cd.course_id WHERE rb.ISBN = ?;";

        String findStudentDeptQuery =
                "SELECT sd.dept_name " +
                        "FROM Stu_dept sd " +
                        "WHERE sd.id = ?";

        try (Connection conn = DBConnection.getConnection();
             PreparedStatement courseDeptStmt = conn.prepareStatement(findCourseDeptQuery);
             PreparedStatement studentDeptStmt = conn.prepareStatement(findStudentDeptQuery)) {

            courseDeptStmt.setString(1, bookIsbn);
            ResultSet courseDeptRs = courseDeptStmt.executeQuery();

            if (courseDeptRs.next()) {
                String courseDept = courseDeptRs.getString("dept_name");

                studentDeptStmt.setInt(1, studentId);
                ResultSet studentDeptRs = studentDeptStmt.executeQuery();

                if (studentDeptRs.next()) {
                    String studentDept = studentDeptRs.getString("dept_name");

                    if (courseDept.equals(studentDept)) {
                        System.out.println("대출 완료! 도서 ISBN: " + bookIsbn);
                    } else {
                        System.out.println("대출 불허! 해당 학과의 학생만 대출 가능합니다.");
                    }
                }
            } else {
                System.out.println("대출 불허! 해당 도서는 수업에 지정된 도서가 아닙니다.");
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}
