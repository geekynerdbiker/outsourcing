package ajou_service.Professor;

import ajou_service.Member;
import ajou_service.Lecture;
import ajou_service.Management;

import java.util.ArrayList;

public class Professor extends Member {

    private ArrayList<Lecture> lectures = new ArrayList<>();

    public Professor(String name, String id, String pw) {
        super(name, id, pw, 1);
    }

    public Professor(String name, String id, String pw, String gender, String tel, String email, String depart, String semester) {
        super(name, id, pw, gender, tel, email, depart, semester);
    }

    public int getNumOfLectures() {
        return this.lectures.size();
    }

    public Lecture getIndexLecture(int index) {
        return lectures.get(index);
    }

    public boolean registerLecture(Lecture lec) {
        if (scheduleCheck(lec)) {
            lectures.add(lec);
            Management.lectures.add(lec);
            return true;
        }
        return false;

    }

    public void registerLecture(String lectureName, String time, String grade) {

        Lecture lecture = new Lecture(lectureName, this.getName(), time, grade);
        if (scheduleCheck(lecture)) {
            lectures.add(lecture);
            Management.lectures.add(lecture);
        }

    }


    public boolean scheduleCheck(Lecture check) {

        int time1, time2;
        time1 = check.getTimeNum1();
        time2 = check.getTimeNum2();
        for (Lecture temp : this.lectures) {

            if (time1 == temp.getTimeNum1() || time1 == temp.getTimeNum2() || time2 == temp.getTimeNum1() || time2 == temp.getTimeNum2())
                return false;

        }
        return true;
    }

}
