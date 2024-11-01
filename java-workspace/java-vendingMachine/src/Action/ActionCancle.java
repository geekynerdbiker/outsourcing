package Action;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

public class ActionCancle implements ActionListener {
    JFrame frame;

    public ActionCancle(JFrame frame) {
        this.frame = frame;
    }

    public void actionPerformed(ActionEvent e) {
        frame.dispose();
    }

}
