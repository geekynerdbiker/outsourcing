package hwkim0413.finaltest;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Calendar;

@SuppressWarnings("serial")
public class FinalTestFrame extends JFrame {
	
	VolunteerManager hwkim = new VolunteerManager("좋은세상만들기"); // 본인이름 이니셜 객체
	JLabel time;
	JButton stop, add;
	JPanel timePanel, inputPanel;
	JOptionPane adder;
	Container contentPane;
	JTextField t1, t2, t3;

	public FinalTestFrame() {
		this("201910065 김혜원"); // 본인 학번 이름
	}
	
	public FinalTestFrame(String title) {
		super(title);
		this.setSize(500,500);
		this.setLocationRelativeTo(null);
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);
		init();
		this.setVisible(true);
	}

	class TimeThread extends Thread {
		public void run(){
			while (true) {
				Calendar cal = Calendar.getInstance();

				String str = cal.get(Calendar.YEAR)+"년 ";
				str += cal.get(Calendar.MONTH)+"월 ";
				str += cal.get(Calendar.DAY_OF_MONTH)+"일 ";
				str += cal.get(Calendar.HOUR_OF_DAY)+"시 ";
				str += cal.get(Calendar.MINUTE)+"분 ";
				str += cal.get(Calendar.SECOND)+"초 ";

				time.setText(str);
				try {
					Thread.sleep(1000);

				} catch (InterruptedException e) {
					e.printStackTrace();
				}
			}
		}
	}

	public void init() {
		contentPane = this.getContentPane();

		timePanel = new JPanel();
		TimeThread tt = new TimeThread();
		tt.start();

		time = new JLabel();
		timePanel.add(time, BorderLayout.NORTH);

		stop = new JButton("STOP");
		timePanel.add(stop);

		stop.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				tt.stop();
			}
		});

		inputPanel = new JPanel();

		t1 = new JTextField(10);
		t2 = new JTextField(5);
		t3 = new JTextField(5);
		inputPanel.add(t1);
		inputPanel.add(t2);
		inputPanel.add(t3);

		add = new JButton("추가");
		inputPanel.add(add);

		add.addActionListener(new ActionListener() {
			@Override
			public void actionPerformed(ActionEvent e) {
				String volName = t1.getText();
				int donationTime = Integer.parseInt(t2.getText());
				int number = Integer.parseInt(t3.getText());

				String result = hwkim.addVolunteer(new Volunteer(volName, donationTime, number));
				adder = new JOptionPane(result);
				adder.show();
			}
		});

		contentPane.add(timePanel, BorderLayout.NORTH);
		contentPane.add(inputPanel, BorderLayout.CENTER);

	}


}




















