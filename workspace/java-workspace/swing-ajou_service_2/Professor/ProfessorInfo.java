package ajou_service.Professor;

import ajou_service.Management;

import javax.swing.*;
import java.awt.*;


public class ProfessorInfo extends JFrame{
	public ProfessorInfo() {
		Container c1 = getContentPane();

		GridLayout b1 = new GridLayout(7, 1, 10, 10);
		c1.setLayout(b1);

		setTitle("교수 정보");

		Professor member = (Professor) Management.currMember;

		setContentPane(c1);
		c1.add(new JLabel("이름: " + member.getName()));
		c1.add(new JLabel("성별: " + member.getGender()));
		c1.add(new JLabel("전화번호: "+ member.getTel()));
		c1.add(new JLabel("이메일: "+member.getEmail()));
		c1.add(new JLabel("소속학과: "+ member.getDepart()));
		c1.add(new JLabel("학기: "+ member.getSemester()));

		setSize(400, 300);
		setResizable(false);
		setVisible(true);
	}
}
