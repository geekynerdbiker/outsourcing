package ajou_service.Professor;

import ajou_service.Member;
import ajou_service.Management;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

public class ProfessorLoginScreen extends JFrame implements ActionListener {
    JTextField ID = new JTextField(20);
    JTextField PW = new JTextField(20);
    JLabel text1 = new JLabel();
    JLabel text2 = new JLabel();
    JButton button1 = new JButton();

    public ProfessorLoginScreen() {
        Container c1 = getContentPane();

        GridLayout b1 = new GridLayout(7, 1, 10, 10);
        c1.setLayout(b1);

        text1.setText("ID를 입력해 주세요");
        text2.setText("PW를 입력해 주세요");

        button1.setText("로그인");

        c1.add(text1);
        c1.add(ID);
        c1.add(text2);
        c1.add(PW);
        c1.add(button1);

        button1.addActionListener(this);

        ID.addActionListener(this);
        PW.addActionListener(this);

        setTitle("수강신청 프로그램 - 교수용");
        setSize(500, 400);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        Member member = null;
        String id;
        String pw;

        if (Objects.equals(ae.getActionCommand(), "로그인")) {

            id = ID.getText();
            pw = PW.getText();

            for (int i = 0; i < Management.professors.size(); i++) {
                if (id.equals(Management.professors.get(i).getId()) && pw.equals(Management.professors.get(i).getPw())) {
                    member = Management.professors.get(i);
                    break;
                }
            }

            if (member != null) {
                dispose();
                Management.currMember = member;
                new ProfessorScreen();
            }
        }
    }
}


