package Action;

import Coin.CoinArray;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;


public class AddCoinFrame extends JFrame implements ActionListener {
    JCheckBox coinCheck;
    JButton coinOk, coinClose;
    JTable coinTable;
    DefaultTableModel coinModel;

    public AddCoinFrame(JTable coinTable) {
        this.coinTable = coinTable;
    }

    public void addCoinFrame(JTable coinTable) {
        this.coinTable = coinTable;

        List<JCheckBox> coinCheckList = new ArrayList<JCheckBox>();
        List<JComboBox> coinSelectList = new ArrayList<JComboBox>();

        setTitle("거스름돈 추가");
        setSize(320, 300);
        setLocation(200, 200);

        JLabel label = new JLabel("어떤 거스름돈이 부족하신가요?");
        JPanel toPanel = new JPanel();
        toPanel.add(label);
        add(toPanel, BorderLayout.NORTH);

        JPanel checkPanel = new JPanel();
        JButton chechAll = new JButton("전체 10개 추가");
        chechAll.setPreferredSize(new Dimension(120, 30));
        chechAll.addActionListener(new ActionSelectAll(coinCheckList));

        String[] coinSelectNum = {"10개", "20개", "50개"};

        for (int i = 0; i < CoinArray.coinList.size(); i++) {
            JPanel checkEach = new JPanel();
            coinCheck = new JCheckBox(CoinArray.coinList.get(i).getCoinName());
            JComboBox<String> coinSelectBox = new JComboBox();
            for (String s : coinSelectNum) {
                coinSelectBox.addItem(s);
            }

            coinCheckList.add(coinCheck);
            coinSelectList.add(coinSelectBox);

            checkEach.add(coinCheck);
            checkEach.add(coinSelectBox);
            coinSelectBox.setVisible(false);

            checkPanel.add(checkEach);
            coinCheck.addActionListener(new ActionCheck(coinSelectList));
            checkEach.setPreferredSize(new Dimension(160, 30));
        }

        add(chechAll, BorderLayout.WEST);
        add(checkPanel, BorderLayout.CENTER);

        coinOk = new JButton("추가");
        coinClose = new JButton("취소");

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(coinOk);
        buttonPanel.add(coinClose);
        add(buttonPanel, BorderLayout.SOUTH);
        coinOk.addActionListener(new ActionAddCoin(this, chechAll, coinCheckList, coinSelectList));
        coinClose.addActionListener(new ActionCancle(this));

        setVisible(true);

    }

    public void actionPerformed(ActionEvent e) {
        addCoinFrame(coinTable);
    }
}
