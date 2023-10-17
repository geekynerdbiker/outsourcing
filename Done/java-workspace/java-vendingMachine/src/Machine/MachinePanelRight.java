package Machine;

import Action.AddCanFrame;
import Action.AddCoinFrame;
import Can.CanArray;
import Coin.CoinArray;
import Person.Admin;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class MachinePanelRight extends JPanel implements ActionListener {
    JPasswordField adminPass;
    JPanel canAdminPanel, moneyAdminPanel, moneyTotalPanel;
    JButton btnAdminIn, btnAddCanStart, btnAddCan;
    JLabel label, labe2;
    String password;
    DefaultTableModel canModel;
    public static JLabel totalMoneyLabel;
    public static JTable canTable, moneyTable;

    public MachinePanelRight(String password) {
        this.password = password;

        setPreferredSize(new Dimension(280, 550));

        label = new JLabel("관리하려면 관리자로 연결해주세요.");
        label.setVisible(true);
		
        canAdminPanel = new JPanel(new BorderLayout());

        String[] canColName = {"이름", "재고", "판매가격"};
        canModel = new DefaultTableModel(canColName, 0);
        canTable = new JTable(canModel);
        JScrollPane canScrollPanel = new JScrollPane(canTable);
        canScrollPanel.setPreferredSize(new Dimension(230, 150));

        btnAddCan = new JButton("음료 추가");
        btnAddCan.addActionListener(new AddCanFrame(canTable));

        canAdminPanel.add(new JLabel("음료 관리"), BorderLayout.WEST);
        canAdminPanel.add(btnAddCan, BorderLayout.EAST);
        canAdminPanel.add(canScrollPanel, BorderLayout.SOUTH);
        canAdminPanel.setVisible(false);

        for (int i = 0; i < CanArray.canList.size(); i++) {
            String arr[] = {CanArray.canList.get(i).getCanName(),
                    Integer.toString(CanArray.canList.get(i).getCanNum()),
                    Integer.toString(CanArray.canList.get(i).getCanPrice())};
            canModel.addRow(arr);
        }
		
        moneyAdminPanel = new JPanel(new BorderLayout());

        String[] moneyColName = {"동전 종류", "남은 갯수",};
        DefaultTableModel moneyModel = new DefaultTableModel(moneyColName, 0);
        moneyTable = new JTable(moneyModel);
        JScrollPane moneyScrollPanel = new JScrollPane(moneyTable);
        moneyScrollPanel.setPreferredSize(new Dimension(230, 150));

        JButton btnAddMoney = new JButton("거스름돈 추가");
        btnAddMoney.addActionListener(new AddCoinFrame(moneyTable));
        moneyAdminPanel.add(new JLabel("거스름돈 관리"), BorderLayout.CENTER);
        moneyAdminPanel.add(btnAddMoney, BorderLayout.EAST);
        moneyAdminPanel.add(moneyScrollPanel, BorderLayout.SOUTH);
        moneyAdminPanel.setVisible(false);

        moneyModel = (DefaultTableModel) moneyTable.getModel();

        for (int i = 0; i < CoinArray.coinList.size(); i++) {
            String arr[] = {CoinArray.coinList.get(i).getCoinName(),
                    Integer.toString(CoinArray.coinList.get(i).getCoinNum())};
            moneyModel.addRow(arr);
        }

        moneyTotalPanel = new JPanel(new BorderLayout());
        totalMoneyLabel = new JLabel("총 매출액 : " + Admin.getTotalMoney());
        moneyTotalPanel.add(totalMoneyLabel);
        moneyTotalPanel.setVisible(false);

        JPanel inAdminPanel = new JPanel();

        adminPass = new JPasswordField(10);
        adminPass.setEchoChar('*');
        btnAdminIn = new JButton("연결");
        adminPass.addActionListener(this);
        btnAdminIn.addActionListener(this);

        inAdminPanel.add(new JLabel("관리자"));
        inAdminPanel.add(adminPass);
        inAdminPanel.add(btnAdminIn);

        add(inAdminPanel);
        add(canAdminPanel);
        add(label);
        add(moneyAdminPanel);
        add(moneyTotalPanel);
    }

    public void actionPerformed(ActionEvent e) {
        if (!canAdminPanel.isVisible()) {
            if (adminPass.getText().equals(password)) {

                label.setVisible(false);
                canAdminPanel.setVisible(true);
                moneyAdminPanel.setVisible(true);
                moneyTotalPanel.setVisible(true);

                btnAdminIn.setText("연결 해제");
                adminPass.setText("");
                adminPass.setVisible(false);

            } else if (adminPass.getText().equals("")) {
                JOptionPane.showMessageDialog(new JFrame(), "비밀번호를 입력해주세요");
            } else {
                JOptionPane.showMessageDialog(new JFrame(), "비밀번호가 틀렸습니다!");
            }
        } else if (canAdminPanel.isVisible()) {

            label.setVisible(true);
            canAdminPanel.setVisible(false);
            moneyAdminPanel.setVisible(false);
            moneyTotalPanel.setVisible(false);

            btnAdminIn.setText("연결");
            adminPass.setVisible(true);
        }
    }

}