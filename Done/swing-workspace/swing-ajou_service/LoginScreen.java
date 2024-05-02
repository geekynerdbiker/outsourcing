package ajou_service;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class LoginScreen extends JFrame implements ActionListener {

    JTextField ID = new JTextField(20);
    JTextField PW = new JTextField(20);
    JLabel icon = new JLabel();
    JLabel text1 = new JLabel();
    JLabel text2 = new JLabel();
    JButton button1 = new JButton("Login");
    JButton button2 = new JButton("New");

    public LoginScreen() {
        Container c1 = getContentPane();
        ImageIcon ajou = new ImageIcon("ajou2.png");
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

        GridLayout b1 = new GridLayout(7, 1, 10, 10);
        c1.setLayout(b1);


        icon.setIcon(ajou);
        icon.setText("아주대학교 수강신청 프로그램 입니다.");

        text1.setText("ID를 입력해 주세요");
        text2.setText("PW를 입력해 주세요");

        button1.setText("Login");
        button2.setText("회원가입");

        c1.add(icon);
        c1.add(text1);
        c1.add(ID);
        c1.add(text2);
        c1.add(PW);
        c1.add(button1);
        c1.add(button2);

        button1.addActionListener(this);
        button2.addActionListener(this);

        ID.addActionListener(this);
        PW.addActionListener(this);

        setTitle("수강신청 프로그램");
        setSize(500, 400);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        member Member;
        int flag;
        String id = ID.getText();
        String pw = PW.getText();

        if (ae.getActionCommand() == "Login") {

            id = ID.getText();
            pw = PW.getText();

            Member = login.check_id_pw(id, pw);

            if (Member == null) {
                flag = 0;
                new New_Window(flag);

            } else {
                dispose();
                management.now_member = Member;
                if (management.now_member instanceof student)
                    new StudentScreen();
                else if (management.now_member instanceof professor)
                    new ProfessorScreen();

            }

        } else if (ae.getActionCommand() == "회원가입") {
            new MakeNewScreen();
        }
    }

}

class New_Window extends JFrame {
    New_Window(int flag) {
        JLabel NewLabel;
        setTitle("New Window");

        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);

        if (flag == 0) {
            NewWindowContainer.add(new JLabel("입력한 정보와 일치하는 아이디는 존재하지 않습니다"));
            NewWindowContainer.add(new JLabel("다시한번 입력해 주세요"));
        } else if (flag == 1) {
            NewWindowContainer.add(new JLabel("중복된 id가 존재합니다"));
            NewWindowContainer.add(new JLabel("다른 아이디를 사용해 주세요"));
        } else if (flag == 2) {
            NewWindowContainer.add(new JLabel("회원가입이 완료 되었습니다!"));
        }
        setSize(300, 100);
        setResizable(false);
        setVisible(true);
    }
}

class MakeNewScreen extends JFrame implements ActionListener {

    JLabel jl1 = new JLabel("당신은 신분은? ");
    ButtonGroup bgp = new ButtonGroup();
    JRadioButton jrb1 = new JRadioButton("학생", true);
    JRadioButton jrb2 = new JRadioButton("교수");

    JTextField NAME = new JTextField(5);
    JTextField ID = new JTextField(20);
    JTextField PW = new JTextField(20);
    JButton BTN = new JButton("회원가입");

    public MakeNewScreen() {

        Container c1 = getContentPane();
        GridLayout g1 = new GridLayout(9, 2, 10, 10);
        c1.setLayout(g1);

        JLabel NewLabel;
        setTitle("회원가입");

        bgp.add(jrb1);
        bgp.add(jrb2);

        c1.add(jl1);
        c1.add(new JLabel(" "));
        c1.add(jrb1);
        c1.add(jrb2);
        c1.add(new JLabel("이름을 입력해 주세요"));
        c1.add(NAME);
        c1.add(new JLabel("ID 를 입력해 주세요"));
        c1.add(ID);
        c1.add(new JLabel("PW 를 입력해 주세요"));
        c1.add(PW);
        c1.add(new JLabel(" "));
        c1.add(BTN);

        BTN.setText("회원가입");
        BTN.addActionListener(this);

        setSize(300, 400);
        setResizable(false);
        setVisible(true);

    }

    public void actionPerformed(ActionEvent ae) {
        member Member;
        int flag;
        String id = ID.getText();
        String pw = PW.getText();
        System.out.println(ae.getActionCommand());
        if (ae.getActionCommand() == "회원가입") {
            if (!login.check_duplicate_id(ID.getText())) {
                new New_Window(1);
                ID.setText("");
            } else {
                new New_Window(2);
                if (jrb1.isSelected() == true) {
                    Member = new student(NAME.getText(), ID.getText(), PW.getText());
                    management.students.add((student) Member);
                } else {
                    Member = new professor(NAME.getText(), ID.getText(), PW.getText());
                    management.professors.add((professor) Member);
                }

                this.dispose();

            }

        }
    }

}


