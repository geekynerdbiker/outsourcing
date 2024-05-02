package Machine;

import Can.Can;
import Can.CanArray;
import Coin.Coin;
import Coin.CoinArray;

import javax.swing.*;
import java.awt.*;
import java.awt.event.WindowAdapter;
import java.awt.event.WindowEvent;
import java.awt.event.WindowListener;

public class MachineFrame extends JFrame {
    String password;

    public MachineFrame(String password) {
        this.password = password;

        CanArray.canList.add(new Can("생수", 3, 450));
        CanArray.canList.add(new Can("커피", 3, 500));
        CanArray.canList.add(new Can("이온음료", 3, 550));
        CanArray.canList.add(new Can("아메리카노", 3, 700));
        CanArray.canList.add(new Can("탄산음료", 3, 750));

        CoinArray.coinList.add(new Coin("10", 5));
        CoinArray.coinList.add(new Coin("50", 5));
        CoinArray.coinList.add(new Coin("100", 5));
        CoinArray.coinList.add(new Coin("500", 5));
        CoinArray.coinList.add(new Coin("1000", 5));

        setTitle("자판기 관리 프로그렘 - 네트워크");
        setPreferredSize(new Dimension(650, 550));
        setLocation(400, 150);

        WindowListener win = new WindowAdapter() {
            //window �� ������ x �� ��연결 성공
            public void windowClosing(WindowEvent e) {
                super.windowClosing(e);
                System.exit(0);
            }
        };

        addWindowListener(win);

        Container contentPanel = getContentPane();

        JPanel panelRight = new MachinePanelRight(password);
        JPanel panelLeft = new MachinePanelLeft();

        contentPanel.add(panelRight, BorderLayout.EAST);
        contentPanel.add(panelLeft, BorderLayout.CENTER);

        pack();
        setVisible(true);

    }
}
