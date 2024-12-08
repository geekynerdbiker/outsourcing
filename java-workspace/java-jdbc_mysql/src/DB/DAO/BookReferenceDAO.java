package DB.DAO;

import java.sql.*;
import java.util.HashMap;
import java.util.Map;

import DB.DBConnection;

public class BookReferenceDAO {
    public static void getReferenceBooksForCourse(String courseId, int secId, String semester, int year) {
        String query =
                "SELECT t.ID AS professor_id, rb.book_id, rb.title, rb.author, rb.publisher, rb.isbn, s.course_id " +
                        "FROM Teaches t " +
                        "JOIN Reference_book rb ON t.book_id = rb.book_id " +
                        "JOIN Section s ON t.sec_id = s.sec_id AND t.semester = s.semester AND t.year = s.year " +
                        "WHERE s.course_id = ? " +
                        "AND t.sec_id = ? " +
                        "AND t.semester = ? " +
                        "AND t.year = ?";


        try (Connection conn = DBConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {

            stmt.setString(1, courseId);
            stmt.setInt(2, secId);
            stmt.setString(3, semester);
            stmt.setInt(4, year);

            ResultSet rs = stmt.executeQuery();

            Map<Integer, Map<Integer, String>> professorBookMap = new HashMap<>();

            while (rs.next()) {
                int professorId = rs.getInt("professor_id");
                int bookId = rs.getInt("book_id");
                String title = rs.getString("title");
                String author = rs.getString("author");
                String publisher = rs.getString("publisher");
                String isbn = rs.getString("isbn");

                professorBookMap.computeIfAbsent(professorId, k -> new HashMap<>())
                        .put(bookId, String.format("도서 제목: %s\n저자: %s\n출판사: %s\nISBN: %s",
                                title, author, publisher, isbn));
            }

            for (int professorId : professorBookMap.keySet()) {
                String deptQuery =
                        "SELECT d.dept_name " +
                                "FROM Inst_Dept idp " +
                                "JOIN Department d ON idp.dept_name = d.dept_name " +
                                "WHERE idp.id = ?";

                try (PreparedStatement deptStmt = conn.prepareStatement(deptQuery)) {
                    deptStmt.setInt(1, professorId);
                    ResultSet deptRs = deptStmt.executeQuery();

                    if (deptRs.next()) {
                        String professorDept = deptRs.getString("dept_name");

                        String courseDeptQuery =
                                "SELECT cd.dept_name " +
                                        "FROM Course_Dept cd " +
                                        "WHERE cd.course_id = ?";

                        try (PreparedStatement courseDeptStmt = conn.prepareStatement(courseDeptQuery)) {
                            courseDeptStmt.setString(1, courseId);
                            ResultSet courseDeptRs = courseDeptStmt.executeQuery();

                            if (courseDeptRs.next()) {
                                String courseDept = courseDeptRs.getString("dept_name");

                                if (professorDept.equals(courseDept)) {
                                    System.out.println("교수 ID: " + professorId);
                                    Map<Integer, String> books = professorBookMap.get(professorId);
                                    for (String bookDetails : books.values()) {
                                        System.out.println(bookDetails + "\n");
                                    }
                                }
                            }
                        }
                    }
                }
            }

        } catch (SQLException e) {
            e.printStackTrace();
        }
    }
}