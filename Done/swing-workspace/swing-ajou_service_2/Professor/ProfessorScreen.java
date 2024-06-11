package ajou_service.Professor;

import ajou_service.*;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Objects;

public class ProfessorScreen extends JFrame implements ActionListener {

    private ProfessorRegisterScreen rsc;
    private JTabbedPane jtp;


    public ProfessorScreen() {

        jtp = new JTabbedPane();
        rsc = new ProfessorRegisterScreen();

        JMenuBar jmb = new JMenuBar();

        JMenu menu1 = new JMenu("기능");
        JMenu menu2 = new JMenu("정보");

        jmb.add(menu1);
        jmb.add(menu2);


        JMenuItem jmi1 = new JMenuItem("로그아웃");
        JMenuItem jmi2 = new JMenuItem("학생 찾기");
        JMenuItem jmi3 = new JMenuItem("강의 조회");
        JMenuItem jmi4 = new JMenuItem("종료");

        menu1.add(jmi1);
        menu1.add(jmi2);
        menu1.add(jmi3);
        menu1.add(jmi4);

        JMenuItem jmi5 = new JMenuItem("교수 정보");
        JMenuItem jmi6 = new JMenuItem("프로그램 정보");

        menu2.add(jmi5);
        menu2.add(jmi6);

        jmi1.addActionListener(this);
        jmi2.addActionListener(this);
        jmi3.addActionListener(this);
        jmi4.addActionListener(this);
        jmi5.addActionListener(this);
        jmi6.addActionListener(this);

        setJMenuBar(jmb);

        jtp.addTab("강의등록", rsc);
        getContentPane().add(jtp);


        setTitle("Student Panel");
        setSize(400, 500);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        if (Objects.equals(ae.getActionCommand(), "로그아웃")) {
            try {
                Init.saveProgram();
                Init.initProgram();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            new Home();
            this.dispose();
        } else if (Objects.equals(ae.getActionCommand(), "학생 찾기")) {
            new FindStudentInfo();
        } else if (Objects.equals(ae.getActionCommand(), "강의 조회")) {
            new ProfessorClassScreen();
        } else if (Objects.equals(ae.getActionCommand(), "교수 정보")) {
            new ProfessorInfo();
        } else if (Objects.equals(ae.getActionCommand(), "프로그램 정보")) {
            new ProgramInfo();
        } else if (Objects.equals(ae.getActionCommand(), "종료")) {
            try {
                Init.saveProgram();
                Init.initProgram();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            System.exit(0);
        }
    }

}


