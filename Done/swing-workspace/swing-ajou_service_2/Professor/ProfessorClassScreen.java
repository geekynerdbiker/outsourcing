package ajou_service.Professor;

import ajou_service.Lecture;
import ajou_service.Management;
import ajou_service.Student.Student;

import javax.swing.*;
import java.awt.*;
import java.util.Objects;

class ProfessorClassScreen extends JFrame {
    private Professor pf;
    int numOfLectures = 0;
    int totalStudent = 0;

    public ProfessorClassScreen() {
        pf = (Professor) Management.currMember;

        for (Lecture lec : Management.lectures) {
            if (Objects.equals(lec.getProf(), pf.getName())) {
                numOfLectures++;
                for (Student s : lec.getStudents()) {
                    totalStudent++;
                }
            }
        }

        GridLayout b1 = new GridLayout(numOfLectures + 2, 5, 10, 10);
        setLayout(b1);


        String[] content = {"강의명", "이름", "학번", "학과", "이메일"};


        JButton btn = new JButton("취소");


        if (numOfLectures == 0 || totalStudent == 0) {
            add(new JLabel("개설된 강의 또는 수강 학생이 존재하지 않습니다."));
        } else {
            for (int i = 0; i < 5; i++)
                add(new JLabel(content[i]));

            for (Lecture lec : Management.lectures) {
                if (Objects.equals(lec.getProf(), pf.getName())) {
                    for (Student s : lec.getStudents()) {
                        add(new JLabel(lec.getName()));
                        add(new JLabel(s.getName()));
                        add(new JLabel(s.getSid()));
                        add(new JLabel(s.getDepart()));
                        add(new JLabel(s.getEmail()));
                    }
                }
            }

            add(new JLabel(""));
            add(new JLabel(""));
            add(new JLabel(""));

        }
        // TODO Auto-generated constructor stub
        setSize(400, 500);
        setVisible(true);
    }
}