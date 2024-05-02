package Action;

import Can.CanArray;
import Coin.CoinArray;
import Machine.MachinePanelRight;
import Person.Admin;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ReturnMoney implements ActionListener {

    JTextField takeMoneytext;
    JButton getCan;
    List<JButton> blist;

    public ReturnMoney(JTextField takeMoneytext, JButton getCan, List<JButton> blist) {
        super();
        this.takeMoneytext = takeMoneytext;
        this.getCan = getCan;
        this.blist = blist;
    }

    public void actionPerformed(ActionEvent e) {
        int returnMoney = Integer.parseInt(takeMoneytext.getText());

        int return1000 = 0;
        int return500 = 0;
        int return100 = 0;
        int return50 = 0;
        int return10 = 0;

        if (returnMoney > 0) {
            return1000 = returnMoney / 1000;
            return500 = (returnMoney % 1000) / 500;
            return100 = ((returnMoney % 1000) % 500) / 100;
            return50 = (((returnMoney % 1000) % 500) % 100) / 50;
            return10 = ((((returnMoney % 1000) % 500) % 100) % 50) / 10;

            Admin.setTotalMoney(Admin.getTotalMoney() - returnMoney);
            MachinePanelRight.totalMoneyLabel.setText("총 매출액 : " + Admin.getTotalMoney());

            for (int i = 0; i < return1000; i++) {
                if (CoinArray.coinList.get(4).getCoinNum() == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "1000원 지폐 부족");
                    return500 = returnMoney / 500;
                    break;
                } else {
                    CoinArray.coinList.get(4).setCoinNum(CoinArray.coinList.get(4).getCoinNum() - 1);
                    returnMoney -= 1000;
                    takeMoneytext.setText(Integer.toString(returnMoney));
                }
            }

            for (int i = 0; i < return500; i++) {
                if (CoinArray.coinList.get(3).getCoinNum() == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "500원 동전 부족");
                    return100 = returnMoney / 100;
                    break;
                } else {
                    CoinArray.coinList.get(3).setCoinNum(CoinArray.coinList.get(3).getCoinNum() - 1);
                    returnMoney -= 500;
                    takeMoneytext.setText(Integer.toString(returnMoney));
                }
            }

            for (int i = 0; i < return100; i++) {
                if (CoinArray.coinList.get(2).getCoinNum() == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "100원 동전 부족");
                    return50 = returnMoney / 50;
                    break;
                } else {
                    CoinArray.coinList.get(2).setCoinNum(CoinArray.coinList.get(2).getCoinNum() - 1);
                    returnMoney -= 100;
                    takeMoneytext.setText(Integer.toString(returnMoney));
                }
            }

            for (int i = 0; i < return50; i++) {
                if (CoinArray.coinList.get(1).getCoinNum() == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "50원 동전 부족");
                    return10 = returnMoney / 10;
                    break;
                } else {
                    CoinArray.coinList.get(1).setCoinNum(CoinArray.coinList.get(1).getCoinNum() - 1);
                    returnMoney -= 50;
                    takeMoneytext.setText(Integer.toString(returnMoney));
                }
            }

            for (int i = 0; i < return10; i++) {
                if (CoinArray.coinList.get(0).getCoinNum() == 0) {
                    JOptionPane.showMessageDialog(new JFrame(), "10원 동전 부족");
                    takeMoneytext.setText(Integer.toString(returnMoney));
                    break;
                } else {
                    CoinArray.coinList.get(0).setCoinNum(CoinArray.coinList.get(0).getCoinNum() - 1);
                    returnMoney -= 10;
                    takeMoneytext.setText(Integer.toString(returnMoney));
                }
            }

            DefaultTableModel moneyModel = (DefaultTableModel) MachinePanelRight.moneyTable.getModel();
            moneyModel.setRowCount(0);

            for (int j = 0; j < CoinArray.coinList.size(); j++) {
                String arr[] = {CoinArray.coinList.get(j).getCoinName(),
                        Integer.toString(CoinArray.coinList.get(j).getCoinNum())};
                moneyModel.addRow(arr);
            }

            for (int k = 0; k < blist.size(); k++) {
                if (blist.get(k).getLabel().equals(CanArray.canList.get(k).getCanName())) {
                    blist.get(k).setForeground(new Color(0, 0, 0));
                    blist.get(k).setBackground(new Color(255, 255, 255));
                }
            }
        } else {
            JOptionPane.showMessageDialog(new JFrame(), "반환할 거스름돈이 없습니다.");
        }

    }

}
