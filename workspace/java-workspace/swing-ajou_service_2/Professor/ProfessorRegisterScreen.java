package ajou_service.Professor;

import ajou_service.Lecture;
import ajou_service.Management;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

class ProfessorRegisterScreen extends JPanel implements ActionListener {

    Professor pf;
    JLabel name = new JLabel("강의명 : ");
    JLabel time = new JLabel("시간 : ");
    JLabel grade = new JLabel("학점 : ");
    JLabel info = new JLabel("           ");
    JTextField lecName = new JTextField(8);
    JTextField lecTime = new JTextField(8);
    JTextField lecGrade = new JTextField(2);

    ProfessorRegisterScreen() {
        pf = (Professor) Management.currMember;
        // TODO Auto-generated constructor stub
        JButton register = new JButton("등록");

        add(name);
        add(lecName);
        add(time);
        add(lecTime);
        add(grade);
        add(lecGrade);
        add(register);
        add(info);
        register.addActionListener(this);
    }


    public void actionPerformed(ActionEvent ae) {
        String s = ae.getActionCommand();
        Lecture temp;

        if (Objects.equals(s, "등록")) {
            pf = (Professor) Management.currMember;
            temp = new Lecture(lecName.getText(), pf.getName(), lecTime.getText(), lecGrade.getText());
            if (pf.registerLecture(temp))
                info.setText("정상적으로 강의가 등록되었습니다.");
            else
                info.setText("시간이 겹치는 과목이 있습니다. 다시 확인해 주세요.");
        }
    }
}
