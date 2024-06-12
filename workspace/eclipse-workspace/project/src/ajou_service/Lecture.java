package ajou_service;

import ajou_service.Student.Student;

import java.util.ArrayList;

public class Lecture {
    private String name;
    private String prof;
    private String time;
    private int timeNum1;
    private int timeNum2;
    private int grade;
    private ArrayList<Student> students;
    public Lecture(String name, String professor, String time, String grade) {
        this.name = name;
        this.prof = professor;
        this.time = time;
        this.grade = Integer.parseInt(grade);
        this.students = new ArrayList<>();

        timeNum1 = dayToInt(time.substring(0, 1)) * 5 + alphabetToInt(time.substring(1, 2));
        timeNum2 = dayToInt(time.substring(2, 3)) * 5 + alphabetToInt(time.substring(3, 4));
    }

    public String getName() {
        return name;
    }

    public void setName(String name) {
        this.name = name;
    }

    public String getProf() {
        return prof;
    }

    public void setProf(String prof) {
        this.prof = prof;
    }

    public String getTime() {
        return time;
    }

    public void setTime(String time) {
        this.time = time;
    }

    public int getTimeNum1() {
        return timeNum1;
    }

    public void setTimeNum1(int timeNum1) {
        this.timeNum1 = timeNum1;
    }

    public int getTimeNum2() {
        return timeNum2;
    }

    public void setTimeNum2(int timeNum2) {
        this.timeNum2 = timeNum2;
    }
    public int getGrade() {
        return grade;
    }

    public void setGrade(int grade) {
        this.grade = grade;
    }
    public ArrayList<Student> getStudents() {
        return students;
    }

    public void setStudents(ArrayList<Student> students) {
        this.students = students;
    }

    public static int dayToInt(String day) {
        if (day.equals("월"))
            return 0;
        else if (day.equals("화"))
            return 1;
        else if (day.equals("수"))
            return 2;
        else if (day.equals("목"))
            return 3;
        else if (day.equals("금"))
            return 4;
        else {
            return -1;
        }
    }

    public static int alphabetToInt(String alphabet) {
        if (alphabet.equals("A"))
            return 0;
        else if (alphabet.equals("B"))
            return 1;
        else if (alphabet.equals("C"))
            return 2;
        else if (alphabet.equals("D"))
            return 3;
        else if (alphabet.equals("E"))
            return 4;
        else {
            return -1;
        }
    }
}