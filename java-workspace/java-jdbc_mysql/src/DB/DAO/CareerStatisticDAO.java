package DB.DAO;

import java.sql.*;
import java.util.ArrayList;
import java.util.List;
import DB.DBConnection;
import DB.Models.CareerStatistic;

public class CareerStatisticDAO {
    public static List<CareerStatistic> getCareerStatistics(String departmentId, int year, int month) {
        List<CareerStatistic> stats = new ArrayList<>();
        String query = "SELECT * FROM Career_statistic WHERE department_id = ? AND year = ? AND month = ?";

        try (Connection conn = DBConnection.getConnection();
             PreparedStatement stmt = conn.prepareStatement(query)) {
            stmt.setString(1, departmentId);
            stmt.setInt(2, year);
            stmt.setInt(3, month);
            ResultSet rs = stmt.executeQuery();

            while (rs.next()) {
                int statisticId = rs.getInt("statistic_id");
                int employment = rs.getInt("employment");
                int graduate = rs.getInt("graduate");
                int entrepreneurship = rs.getInt("entrepreneurship");
                int other = rs.getInt("other");
                stats.add(new CareerStatistic(statisticId, departmentId, month, year, employment, graduate, entrepreneurship, other));
            }
        } catch (SQLException e) {
            e.printStackTrace();
        }
        return stats;
    }
}
