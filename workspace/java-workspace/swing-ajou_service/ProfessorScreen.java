package ajou_service;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class ProfessorScreen extends JFrame implements ActionListener {

    private Pf_RegisterScreen rsc;
    private JTabbedPane jtp;


    public ProfessorScreen() {

        jtp = new JTabbedPane();
        rsc = new Pf_RegisterScreen();
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        JMenuBar jmb = new JMenuBar();

        JMenu menu1 = new JMenu("기능");
        JMenu menu2 = new JMenu("정보");

        jmb.add(menu1);
        jmb.add(menu2);


        JMenuItem jmi1 = new JMenuItem("로그아웃");
        JMenuItem jmi2 = new JMenuItem("종료");

        menu1.add(jmi1);
        menu1.add(jmi2);

        JMenuItem jmi3 = new JMenuItem("프로그램 정보");

        menu2.add(jmi3);

        jmi1.addActionListener(this);
        jmi2.addActionListener(this);
        jmi3.addActionListener(this);

        setJMenuBar(jmb);

        jtp.addTab("강의등록", rsc);
        getContentPane().add(jtp);


        setTitle("Student Panel");
        setSize(400, 500);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        if (ae.getActionCommand() == "로그아웃") {
            try {
                init.Save_Program();
                init.Init_Program();
            } catch (IOException e) {
                throw new RuntimeException(e);
            }
            new LoginScreen();
            this.dispose();
        } else if (ae.getActionCommand() == "프로그램 정보") {
            new Program_info();
        } else if (ae.getActionCommand() == "종료") {
            System.exit(0);
        }
    }

}


class Pf_RegisterScreen extends JPanel implements ActionListener {

    professor pf;
    JLabel name = new JLabel("강의 명 : ");
    JLabel time = new JLabel("강의 시간 : ");
    JLabel info = new JLabel("                             ");
    JTextField lec_name = new JTextField(10);
    JTextField lec_time = new JTextField(10);

    Pf_RegisterScreen() {
        pf = (professor) management.now_member;
        // TODO Auto-generated constructor stub
        JButton register = new JButton("강의등록");

        add(name);
        add(lec_name);
        add(time);
        add(lec_time);
        add(register);
        add(info);
        register.addActionListener(this);
    }


    public void actionPerformed(ActionEvent ae) {
        String s = ae.getActionCommand();
        lecture temp;
        if (s == "강의등록") {
            pf = (professor) management.now_member;
            temp = new lecture(lec_name.getText(), pf.get_name(), lec_time.getText());
            if (pf.register_lecture(temp))
                info.setText("정상적으로 강의가 등록되었습니다.");
            else
                info.setText("시간이 겹치는 과목이 있습니다. 다시 확인해 주세요.");


        }
    }


}