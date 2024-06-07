package ajou_service;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.IOException;

public class StudentScreen extends JFrame implements ActionListener {
    private St_RegisterScreen rsc;
    private JTabbedPane jtp;


    public StudentScreen() {

        jtp = new JTabbedPane();
        rsc = new St_RegisterScreen();
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

        jtp.addTab("수강신청", rsc);
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

class St_RegisterScreen extends JPanel implements ActionListener {

    int num_of_lectures = 6;
    ButtonGroup gb = new ButtonGroup();
    JCheckBox[] jc = new JCheckBox[num_of_lectures + 1];
    private student st;

    St_RegisterScreen() {
        st = (student) management.now_member;
        num_of_lectures = management.lectures.size();
        JLabel temp;
        GridLayout b1 = new GridLayout(num_of_lectures + 2, 4, 10, 10);
        setLayout(b1);


        String[] content = {"선택", "과목명", "시간", "교수명"};


        JButton btn = new JButton("수강신청");

        for (int i = 0; i < 4; i++)
            add(new JLabel(content[i]));

        for (int i = 0; i < num_of_lectures; i++) {
            jc[i] = new JCheckBox("");
            add(jc[i]);
            add(new JLabel(management.lectures.get(i).get_name()));
            add(new JLabel(management.lectures.get(i).get_time()));
            add(new JLabel(management.lectures.get(i).get_prof()));
            gb.add(jc[i]);
            jc[i].addActionListener(this);

        }
        add(new JLabel(""));
        add(new JLabel(""));
        add(new JLabel(""));
        add(btn);

        btn.addActionListener(this);

        // TODO Auto-generated constructor stub
    }

    public void actionPerformed(ActionEvent ae) {
        String s = ae.getActionCommand();
        lecture temp;
        if (s == "수강신청") {
            st = (student) management.now_member;
            for (int i = 0; i < num_of_lectures; i++) {
                if (jc[i].isSelected()) {
                    temp = management.lectures.get(i);

                    if (st.register_lecture(temp)) {
                        new New_Window2(0);

                    } else {
                        new New_Window2(1);
                    }

                }
            }
        }

    }


}

class New_Window2 extends JFrame {
    New_Window2(int flag) {
        JLabel NewLabel;
        setTitle("New Window");

        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);

        if (flag == 0) {
            NewWindowContainer.add(new JLabel("선택하신 강의가 정상적으로 신청되었습니다."));

        } else if (flag == 1) {
            NewWindowContainer.add(new JLabel("선택하신 강의를 신청할 수 없습니다"));
            NewWindowContainer.add(new JLabel("시간 및 강의를 다시 확인해 주세요"));

        }

        setSize(300, 100);
        setResizable(false);
        setVisible(true);
    }
}
