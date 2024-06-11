package ajou_service.Student;

import ajou_service.Lecture;
import ajou_service.Management;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

class StudentRegisterScreen extends JPanel implements ActionListener {
    int numOfLectures = 6;
    ButtonGroup gb = new ButtonGroup();
    JCheckBox[] jc = new JCheckBox[numOfLectures + 1];
    private Student st;

    StudentRegisterScreen() {
        st = (Student) Management.currMember;
        numOfLectures = Management.lectures.size();
        JLabel temp;
        GridLayout b1 = new GridLayout(numOfLectures + 2, 4, 10, 10);
        setLayout(b1);


        String[] content = {"강의명", "시간", "교수", "학점", "", ""};


        for (int i = 0; i < 6; i++)
            add(new JLabel(content[i]));

        for (int i = 0; i < numOfLectures; i++) {
            add(new JLabel(Management.lectures.get(i).getName()));
            add(new JLabel(Management.lectures.get(i).getTime()));
            add(new JLabel(Management.lectures.get(i).getProf()));
            add(new JLabel(Integer.toString(Management.lectures.get(i).getGrade())));

            JButton btn1 = new JButton("수강");
            btn1.setActionCommand("수강," + i);
            btn1.addActionListener(this);
            add(btn1);

            JButton btn2 = new JButton("취소");
            btn2.setActionCommand("취소," + i);
            btn2.addActionListener(this);
            add(btn2);
        }

        add(new JLabel(""));
        add(new JLabel(""));
        add(new JLabel(""));

        // TODO Auto-generated constructor stub
    }

    public void actionPerformed(ActionEvent ae) {
        String[] s = ae.getActionCommand().split(",");
        Lecture temp;
        if (Objects.equals(s[0], "수강")) {
            st = (Student) Management.currMember;

            int i = Integer.parseInt(s[1]);
            temp = Management.lectures.get(i);

            if (st.registerLecture(temp)) {
                new StudentPopUp(0);
            } else {
                new StudentPopUp(1);
            }
        } else if (Objects.equals(s[0], "취소")) {
            st = (Student) Management.currMember;

            int i = Integer.parseInt(s[1]);
            temp = Management.lectures.get(i);

            if (st.cancelLecture(temp)) {
                new StudentPopUp(2);
            } else {
                new StudentPopUp(3);
            }
        }
    }
}