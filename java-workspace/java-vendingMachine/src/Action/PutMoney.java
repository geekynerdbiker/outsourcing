package Action;

import Can.CanArray;
import Machine.MachinePanelRight;
import Person.Admin;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;
import java.util.regex.Pattern;

public class PutMoney implements ActionListener {

    JTextField putMoneytext, takeMoneytext;
    List<JButton> blist;


    public PutMoney(JTextField putMoneytext, JTextField takeMoneytext, List<JButton> blist) {
        super();
        this.putMoneytext = putMoneytext;
        this.takeMoneytext = takeMoneytext;
        this.blist = blist;
    }

    public void actionPerformed(ActionEvent e) {

        if (putMoneytext.getText().equals("")) {
            JOptionPane.showMessageDialog(new JFrame(), "돈을 투입해주세요.");
        } else if (Pattern.matches("^[0-9]*$", putMoneytext.getText())) {

            boolean pattern;

            if (Integer.parseInt(putMoneytext.getText()) < 100) {
                pattern = Pattern.matches("[0,5]?0$", putMoneytext.getText());
            } else if (Integer.parseInt(putMoneytext.getText()) <= 3000) {
                pattern = Pattern.matches("[1-9]((\\d){0,2}[0,5])?0$", putMoneytext.getText());
            } else {
                pattern = false;
            }

            if (!pattern) {
                JOptionPane.showMessageDialog(new JFrame(), "지폐는 3천원 이하의 돈으로, 동전은 50원 단위로 넣어주세요.");
            } else {
                takeMoneytext.setText(String.valueOf(Integer.parseInt(takeMoneytext.getText()) + Integer.parseInt(putMoneytext.getText())));

                if (Integer.parseInt(takeMoneytext.getText()) > 5000) {
                    takeMoneytext.setText(String.valueOf(Integer.parseInt(takeMoneytext.getText()) - Integer.parseInt(putMoneytext.getText())));
                    JOptionPane.showMessageDialog(new JFrame(), "5천원 이상 입력하실 수 없습니다.");
                }
                for (int i = 0; i < blist.size(); i++) {
                    if (blist.get(i).getLabel().equals(CanArray.canList.get(i).getCanName())) {
                        if (CanArray.canList.get(i).getCanPrice() <= Integer.parseInt(takeMoneytext.getText())) {
                            blist.get(i).setForeground(new Color(255, 255, 255));

                            blist.get(i).setBackground(new Color(50, 100, 250));
                        }
                    }
                }

                Admin.setTotalMoney(Admin.getTotalMoney() + Integer.parseInt(putMoneytext.getText()));
                MachinePanelRight.totalMoneyLabel.setText("총 매출액 : " + Admin.getTotalMoney());

                putMoneytext.setText("");
            }
        } else {
            JOptionPane.showMessageDialog(new JFrame(), "숫자 형식으로 입력해주세요.");
        }
    }
}
