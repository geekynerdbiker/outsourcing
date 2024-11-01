package Machine;
import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.util.ArrayList;
import java.util.List;

import javax.swing.BorderFactory;
import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JPanel;
import javax.swing.JTextField;

import Action.PutMoney;
import Action.ReturnMoney;
import Action.TakeCan;
import Action.ButtonAction;
import Can.CanArray;

public class MachinePanelLeft extends JPanel {
	JButton getCan, canButton;
	JTextField putMoneytext, takeMoneytext;

	public MachinePanelLeft() {
		setPreferredSize(new Dimension(320, 550));

		List<JButton> blist = new ArrayList<JButton>();

		JPanel moneyPanel = new JPanel();

		JPanel takeMoneyPanel = new JPanel();
		takeMoneytext = new JTextField(6);
		takeMoneytext.setText("0");
		
		JButton takeMoneyButton = new JButton(new ImageIcon("return.png"));
		takeMoneyButton.setBorder(BorderFactory.createEmptyBorder());
		takeMoneyButton.setContentAreaFilled(false);
		takeMoneyButton.addActionListener(new ReturnMoney(takeMoneytext, getCan, blist));

		JPanel putMoneyPanel = new JPanel();
		putMoneytext = new JTextField(6);

		putMoneytext.addActionListener(new PutMoney(putMoneytext, takeMoneytext, blist));
		JButton putMoneyButton = new JButton("돈 넣기");
		putMoneyButton.addActionListener(new PutMoney(putMoneytext, takeMoneytext, blist));
		
		takeMoneytext.setEditable(false);
		takeMoneyPanel.add(takeMoneytext);
		takeMoneyPanel.add(takeMoneyButton);
		putMoneyPanel.add(putMoneytext);
		putMoneyPanel.add(putMoneyButton);
		
		moneyPanel.add(takeMoneyPanel);
		moneyPanel.add(putMoneyPanel);


		JPanel getCanPanel = new JPanel();
		getCan = new JButton("");
		getCan.addActionListener(new TakeCan(getCan));
		getCan.setIcon(new ImageIcon("canreturn.png"));
		getCan.setBorder(BorderFactory.createEmptyBorder());
		getCan.setContentAreaFilled(false);

		getCanPanel.add(getCan);


		JPanel selectCan = new JPanel(new GridLayout(2, 1));
		selectCan.setPreferredSize(new Dimension(310, 330));

		for (int i = 0; i < CanArray.canList.size(); i++) {
			JPanel canEach = new JPanel();
			JLabel canLabel = new JLabel(CanArray.canList.get(i).getCanPrice() + "원");
			canButton = new JButton(CanArray.canList.get(i).getCanName());
			canButton.addActionListener(new ButtonAction(takeMoneytext, getCan, blist));
			canButton.setForeground(new Color(0, 0, 0));
			canButton.setBackground(new Color(255, 255, 255));
			canEach.add(new JLabel(new ImageIcon(i + ".png")));
			canEach.add(canLabel);
			canEach.add(canButton);
			selectCan.add(canEach);

			blist.add(canButton);
		}

		add(selectCan, BorderLayout.NORTH);
		add(moneyPanel, BorderLayout.CENTER);
		add(getCanPanel, BorderLayout.SOUTH);

		moneyPanel.setBackground(new Color(10, 110, 120));
		takeMoneyPanel.setBackground(new Color(10, 110, 120));
		putMoneyPanel.setBackground(new Color(10, 110, 120));
		getCanPanel.setBackground(new Color(10, 110, 120));
		setBackground(new Color(10, 110, 120));

	}
}
