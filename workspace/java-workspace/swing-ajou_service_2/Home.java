package ajou_service;

import ajou_service.Professor.ProfessorLoginScreen;
import ajou_service.Student.StudentLoginScreen;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Objects;

public class Home extends JFrame implements ActionListener {

    JLabel icon = new JLabel();
    JButton button1 = new JButton("Login");
    JButton button2 = new JButton("New");

    public Home() {
        Container c1 = getContentPane();
        ImageIcon ajou = new ImageIcon("ajou2.png");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        GridLayout b1 = new GridLayout(7, 1, 10, 10);
        c1.setLayout(b1);


        icon.setIcon(ajou);
        icon.setText("아주대학교 수강신청 프로그램 입니다.");

        button1.setText("학생 로그인");
        button2.setText("교수 로그인");

        c1.add(button1);
        c1.add(button2);

        button1.addActionListener(this);
        button2.addActionListener(this);

        setTitle("수강신청 프로그램");
        setSize(500, 400);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        if (Objects.equals(ae.getActionCommand(), "학생 로그인")) {
            new StudentLoginScreen();
        } else if (Objects.equals(ae.getActionCommand(), "교수 로그인")) {
            new ProfessorLoginScreen();
        }
    }

}


