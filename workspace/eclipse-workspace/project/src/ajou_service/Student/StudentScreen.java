package ajou_service.Student;

import ajou_service.Home;
import ajou_service.ProgramInfo;
import ajou_service.Init;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;
import java.util.Objects;

public class StudentScreen extends JFrame implements ActionListener {
    private StudentRegisterScreen src;
    private JTabbedPane jtp;


    public StudentScreen() {

        jtp = new JTabbedPane();
        src = new StudentRegisterScreen();

        JMenuBar jmb = new JMenuBar();

        JMenu menu1 = new JMenu("기능");
        JMenu menu2 = new JMenu("정보");

        jmb.add(menu1);
        jmb.add(menu2);


        JMenuItem jmi1 = new JMenuItem("로그아웃");
        JMenuItem jmi2 = new JMenuItem("수강 목록");
        JMenuItem jmi3 = new JMenuItem("종료");

        menu1.add(jmi1);
        menu1.add(jmi2);
        menu1.add(jmi3);

        JMenuItem jmi4 = new JMenuItem("학생 정보");
        JMenuItem jmi5 = new JMenuItem("프로그램 정보");

        menu2.add(jmi4);
        menu2.add(jmi5);

        jmi1.addActionListener(this);
        jmi2.addActionListener(this);
        jmi3.addActionListener(this);
        jmi4.addActionListener(this);
        jmi5.addActionListener(this);

        setJMenuBar(jmb);

        jtp.addTab("수강신청", src);
        getContentPane().add(jtp);

        setTitle("Student Panel");
        setSize(500, 500);
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
        } else if (Objects.equals(ae.getActionCommand(), "수강 목록")) {
            new StudentClassScreen();
        } else if (Objects.equals(ae.getActionCommand(), "학생 정보")) {
            new StudentInfo();
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

