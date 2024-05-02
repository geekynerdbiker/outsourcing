package Action;

import Coin.CoinArray;
import Machine.MachinePanelRight;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ActionAddCoin extends JFrame implements ActionListener {

    JFrame frame;
    DefaultTableModel coinModel;
    List<JCheckBox> checkList;
    List<JComboBox> selectList;
    JButton chechAll;

    public ActionAddCoin(JFrame frame, JButton chechAll, List<JCheckBox> checkList, List<JComboBox> selectList) {
        super();
        this.frame = frame;
        this.checkList = checkList;
        this.selectList = selectList;
        this.chechAll = chechAll;
    }

    public void actionPerformed(ActionEvent e) {
        coinModel = (DefaultTableModel) MachinePanelRight.moneyTable.getModel();
        if (coinModel.getRowCount() != 0) {
            coinModel.setRowCount(0);
        }
        for (int i = 0; i < checkList.size(); i++) {
            if (checkList.get(i).isSelected()) {
                if (selectList.get(i).getSelectedItem().equals("10개")) {
                    CoinArray.coinList.get(i).setCoinNum(CoinArray.coinList.get(i).getCoinNum() + 10);
                } else if (selectList.get(i).getSelectedItem().equals("20개")) {
                    CoinArray.coinList.get(i).setCoinNum(CoinArray.coinList.get(i).getCoinNum() + 20);
                } else if (selectList.get(i).getSelectedItem().equals("50개")) {
                    CoinArray.coinList.get(i).setCoinNum(CoinArray.coinList.get(i).getCoinNum() + 50);
                }
                checkList.get(i).setSelected(false);
            }
        }

        for (JComboBox jComboBox : selectList) {
            jComboBox.setVisible(false);
            chechAll.setLabel("전체 10개 추가");
        }

        for (int i = 0; i < CoinArray.coinList.size(); i++) {
            String arr[] = {CoinArray.coinList.get(i).getCoinName(), Integer.toString(CoinArray.coinList.get(i).getCoinNum())};
            coinModel.addRow(arr);
        }

        frame.dispose();
        this.setVisible(false);
    }
}
