package ajou_service.Professor;

import ajou_service.Management;
import ajou_service.Member;
import ajou_service.Student.Student;
import ajou_service.Student.StudentInfo;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

public class FindStudentInfo extends JFrame implements ActionListener {
    JTextField SID = new JTextField(20);
    JLabel text1 = new JLabel();
    JButton button1 = new JButton();

    public FindStudentInfo() {
        Container c1 = getContentPane();

        GridLayout b1 = new GridLayout(7, 1, 10, 10);
        c1.setLayout(b1);

        text1.setText("검색할 학생의 학번을 입력해 주세요");

        button1.setText("검색");

        c1.add(text1);
        c1.add(SID);
        c1.add(button1);

        button1.addActionListener(this);

        SID.addActionListener(this);

        setTitle("학생 찾기 - 교수용");
        setSize(500, 400);
        setVisible(true);
    }

    public void actionPerformed(ActionEvent ae) {
        Student member = null;
        String sid;

        if (Objects.equals(ae.getActionCommand(), "검색")) {
            sid = SID.getText();

            for (int i = 0; i < Management.students.size(); i++) {
                if (Management.students.get(i).getType() == 0) {
                    if (sid.equals(Management.students.get(i).getSid())) {
                        member = Management.students.get(i);
                        break;
                    }
                }
            }

            if (member != null) {
                dispose();
                new StudentInfo(member);
            } else {
                dispose();
                new StudentInfo("null");
            }
        }
    }
}
