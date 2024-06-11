package ajou_service.Student;

import ajou_service.Management;

import javax.swing.*;
import java.awt.*;

class StudentClassScreen extends JFrame {
    int numOfLectures = 6;
    private Student st;

    public StudentClassScreen() {
        st = (Student) Management.currMember;
        numOfLectures = st.getLectures().size();
        GridLayout b1 = new GridLayout(numOfLectures + 2, 4, 10, 10);
        setLayout(b1);


        String[] content = {"강의명", "시간", "교수", "학점"};


        JButton btn = new JButton("취소");

        if (numOfLectures == 0) {
            add(new JLabel("수강신청한 강의가 존재하지 않습니다."));
        } else {
            for (int i = 0; i < 4; i++)
                add(new JLabel(content[i]));

            for (int i = 0; i < numOfLectures; i++) {
                add(new JLabel(st.getLectures().get(i).getName()));
                add(new JLabel(st.getLectures().get(i).getTime()));
                add(new JLabel(st.getLectures().get(i).getProf()));
                add(new JLabel(Integer.toString(st.getLectures().get(i).getGrade())));
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