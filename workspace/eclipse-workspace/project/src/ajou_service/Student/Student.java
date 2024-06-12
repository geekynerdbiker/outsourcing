package ajou_service.Student;

import ajou_service.Member;
import ajou_service.Lecture;

import java.util.ArrayList;

public class Student extends Member {
    private String sid;
    private String grade;


    private ArrayList<Lecture> lectures = new ArrayList<>();

    public Student(String name, String id, String pw) {
        super(name, id, pw, 0);
    }

    public Student(String name, String id, String pw, String gender, String tel, String email, String depart, String semester, String sid, String grade) {
        super(name, id, pw, gender, tel, email, depart, semester);
        this.sid = sid;
        this.grade = grade;
    }

    public String getSid() {
        return sid;
    }

    public void setSid(String sid) {
        this.sid = sid;
    }

    public String getGrade() {
        return grade;
    }

    public void setGrade(String grade) {
        this.grade = grade;
    }

    public ArrayList<Lecture> getLectures() {
        return lectures;
    }

    public void setLectures(ArrayList<Lecture> lectures) {
        this.lectures = lectures;
    }

    public int getNumOfLectures() {
        return this.lectures.size();
    }

    public Lecture getIndexLecture(int index) {
        return lectures.get(index);
    }

    public boolean registerLecture(Lecture lec) {
        if (this.duplicationCheck(lec) && this.scheduleCheck(lec) && this.scheduleCheck(lec)) {
            lec.getStudents().add(this);
            this.lectures.add(lec);
            return true;
        } else
            return false;

    }

    public boolean cancelLecture(Lecture lec) {
        if (!this.duplicationCheck(lec)) {
            lec.getStudents().remove(this);
            this.lectures.remove(lec);
            return true;
        }
        return false;
    }

    public boolean duplicationCheck(Lecture check) {
        for (Lecture temp : this.lectures) {
            if (check == temp) {
                return false;
            }
        }
        return true;
    }


    public boolean scheduleCheck(Lecture check) {
        int time1, time2;
        time1 = check.getTimeNum1();
        time2 = check.getTimeNum2();
        for (Lecture temp : this.lectures) {

            if (time1 == temp.getTimeNum1() || time1 == temp.getTimeNum2() || time2 == temp.getTimeNum1() || time2 == temp.getTimeNum2()) {
               return false;
            }
        }
        return true;
    }

    public boolean total_grade_check(Lecture check) {
        int total = 0;
        for (Lecture temp : this.lectures) {
            total += temp.getGrade();
        }

        return total + check.getGrade() <= 18;
    }

} 