package ajou_service;

import javax.swing.*;


public class Program_info extends JFrame{
	JButton BTN = new JButton();
	public Program_info() {
		JPanel NewPanel = new JPanel();
		setTitle("프로그램 정보");

		setContentPane(NewPanel);
		NewPanel.add(new JLabel("이름: 홍길동"));
		NewPanel.add(new JLabel("학번: 202012345"));

		setSize(300, 400);
		setResizable(false);
		setVisible(true);

	}
}
