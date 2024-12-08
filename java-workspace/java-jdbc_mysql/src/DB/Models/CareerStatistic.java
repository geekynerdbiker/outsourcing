package DB.Models;

public class CareerStatistic {
    private int statisticId;
    private String departmentId;
    private int month;
    private int year;
    private int employment;
    private int graduate;
    private int entrepreneurship;
    private int other;

    public CareerStatistic(int statisticId, String departmentId, int month, int year, int employment,
                           int graduate, int entrepreneurship, int other) {
        this.statisticId = statisticId;
        this.departmentId = departmentId;
        this.month = month;
        this.year = year;
        this.employment = employment;
        this.graduate = graduate;
        this.entrepreneurship = entrepreneurship;
        this.other = other;
    }

    @Override
    public String toString() {
        return "Department: " + departmentId + ", Year: " + year + ", Month: " + month +
                ", Employment: " + employment + ", Graduate: " + graduate + ", Entrepreneurship: " + entrepreneurship +
                ", Other: " + other;
    }
}
