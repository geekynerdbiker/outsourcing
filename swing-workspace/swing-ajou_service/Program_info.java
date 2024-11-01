package ajou_service;

import javax.swing.*;


public class Program_info extends JFrame{
	JButton BTN = new JButton();
	public Program_info() {
		JPanel NewPanel = new JPanel();
		setTitle("프로그램 정보");

		setContentPane(NewPanel);
		NewPanel.add(new JLabel("이름: 이준명"));
		NewPanel.add(new JLabel("학번: 202020968"));
		NewPanel.add(new JLabel("업데이트 날짜: 2023/06/25"));

		setSize(300, 400);
		setResizable(false);
		setVisible(true);

	}
}
