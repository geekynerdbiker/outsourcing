package Action;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class TakeCan implements ActionListener {

    JButton getCan;

    public TakeCan(JButton getCan) {
        super();
        this.getCan = getCan;
    }

    public void actionPerformed(ActionEvent e) {
        getCan.setIcon(new ImageIcon("canreturn.png"));
        JOptionPane.showMessageDialog(new JFrame(), "감사합니다");
    }

}
