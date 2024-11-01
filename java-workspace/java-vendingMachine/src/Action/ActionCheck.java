package Action;

import Can.CanArray;
import Coin.CoinArray;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ActionCheck implements ActionListener {
    List<JComboBox> selectList;

    public ActionCheck(List<JComboBox> selectList) {
        super();
        this.selectList = selectList;
    }

    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();
        JCheckBox c = (JCheckBox) obj;

        if (selectList.size() >= 6) {
            if (c.isSelected()) {
                for (int i = 0; i < selectList.size(); i++) {
                    if (CanArray.canList.get(i).getCanName().equals(c.getLabel())) {
                        selectList.get(i).setVisible(true);
                    }
                }
            } else {
                for (int i = 0; i < selectList.size(); i++) {
                    if (CanArray.canList.get(i).getCanName().equals(c.getLabel())) {
                        selectList.get(i).setVisible(false);
                    }
                }
            }
        } else {
            if (c.isSelected()) {
                for (int i = 0; i < selectList.size(); i++) {
                    if (CoinArray.coinList.get(i).getCoinName().equals(c.getLabel())) {
                        selectList.get(i).setVisible(true);
                    }
                }
            } else {
                for (int i = 0; i < selectList.size(); i++) {
                    if (CoinArray.coinList.get(i).getCoinName().equals(c.getLabel())) {
                        selectList.get(i).setVisible(false);
                    }
                }
            }
        }

    }
}