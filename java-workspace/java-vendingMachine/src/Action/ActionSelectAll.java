package Action;

import javax.swing.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ActionSelectAll implements ActionListener {

    List<JCheckBox> checkList;

    public ActionSelectAll(List<JCheckBox> checkList) {
        this.checkList = checkList;
    }

    public void actionPerformed(ActionEvent e) {
        Object obj = e.getSource();
        JButton b = (JButton) obj;

        if (b.getLabel().equals("전체 10개 추가")) {
            for (int i = 0; i < checkList.size(); i++) {
                checkList.get(i).setSelected(true);
            }
            b.setLabel("전체 해제");
        } else {
            for (JCheckBox jCheckBox : checkList) {
                jCheckBox.setSelected(false);
            }
            b.setLabel("전체 10개 추가");
        }

    }

}
