package ajou_service.Student;

import ajou_service.Management;

import javax.swing.*;
import java.awt.*;


public class StudentInfo extends JFrame{
	public StudentInfo() {
		Container c1 = getContentPane();

		GridLayout b1 = new GridLayout(7, 1, 10, 10);
		c1.setLayout(b1);

		setTitle("학생 정보");

		Student member = (Student) Management.currMember;

		setContentPane(c1);
		c1.add(new JLabel("이름: " + member.getName()));
		c1.add(new JLabel("성별: " + member.getGender()));
		c1.add(new JLabel("전화번호: "+ member.getTel()));
		c1.add(new JLabel("이메일: "+member.getEmail()));
		c1.add(new JLabel("소속학과: "+ member.getDepart()));
		c1.add(new JLabel("학기: "+ member.getSemester()));
		c1.add(new JLabel("학번: "+ member.getSid()));
		c1.add(new JLabel("지난 성적: "+ member.getGrade()));

		setSize(300, 400);
		setResizable(false);
		setVisible(true);
	}

	public StudentInfo(Student member) {
		Container c1 = getContentPane();

		GridLayout b1 = new GridLayout(7, 1, 10, 10);
		c1.setLayout(b1);

		setTitle("학생 정보");

		setContentPane(c1);
		c1.add(new JLabel("이름: " + member.getName()));
		c1.add(new JLabel("성별: " + member.getGender()));
		c1.add(new JLabel("전화번호: "+ member.getTel()));
		c1.add(new JLabel("이메일: "+member.getEmail()));
		c1.add(new JLabel("소속학과: "+ member.getDepart()));
		c1.add(new JLabel("학기: "+ member.getSemester()));
		c1.add(new JLabel("학번: "+ member.getSid()));
		c1.add(new JLabel("지난 성적: "+ member.getGrade()));

		setSize(300, 400);
		setResizable(false);
		setVisible(true);
	}

	public StudentInfo(String s) {
		Container c1 = getContentPane();

		GridLayout b1 = new GridLayout(7, 1, 10, 10);
		c1.setLayout(b1);

		setTitle("학생 정보");

		setContentPane(c1);
		c1.add(new JLabel("존재하지 않는 학생입니다."));

		setSize(400, 300);
		setResizable(false);
		setVisible(true);
	}
}
