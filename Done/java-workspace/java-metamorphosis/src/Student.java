import java.util.ArrayList;

public class Student {
    private String name;
    private String department;
    private int age;
    private String userName;
    private String studentNumber;
    private boolean fullTime;
    public ArrayList<Grade> grades;

    public Student(String name, String department, int age, String studentNumber, boolean fullTime) {
        this.name = name;
        this.department = department;
        this.age = age;
        this.studentNumber = studentNumber;
        this.fullTime = fullTime;

        String[] tokens = name.split(" ");
        if (tokens[1].length() < 4)
            userName = tokens[0].substring(0, 1).toLowerCase() + tokens[1].substring(0, tokens[1].length()).toLowerCase() + studentNumber.substring(0, 3);
        else
            userName = tokens[0].substring(0, 1).toLowerCase() + tokens[1].substring(0, 4).toLowerCase() + studentNumber.substring(0, 3);
        grades = new ArrayList<>();
    }

    public String getName() {
        return name;
    }

    public String getDepartment() {
        return department;
    }

    public int getAge() {
        return age;
    }

    public String getUserName() {
        return userName;
    }

    public String getStudentNumber() {
        return studentNumber;
    }

    public boolean isFullTime() {
        return fullTime;
    }

    public void setName(String name) {
        this.name = name;
    }

    public void setDepartment(String department) {
        this.department = department;
    }

    public void setAge(int age) {
        this.age = age;
    }

    public void setUserName(String userName) {
        this.userName = userName;
    }

    public void setStudentNumber(String studentNumber) {
        this.studentNumber = studentNumber;
    }

    public void setFullTime(boolean fullTime) {
        this.fullTime = fullTime;
    }
}
