package Action;

import Can.CanArray;

import javax.swing.*;
import javax.swing.table.DefaultTableModel;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.List;

public class AddCanFrame extends JFrame implements ActionListener {

    JCheckBox canCheck;
    JTable canTable;
    DefaultTableModel canModel;

    public AddCanFrame(JTable canTable) {
        this.canTable = canTable;
    }

    public void addCanFrame(JTable canTable) {
        this.canTable = canTable;

        List<JCheckBox> canCheckList = new ArrayList<JCheckBox>();
        List<JComboBox> canSelectList = new ArrayList<JComboBox>();

        setTitle("음료 추가");
        setSize(320, 300);
        setLocation(200, 200);

        JLabel label = new JLabel("어떤 음료가 필요하신가요?");
        JPanel toPanel = new JPanel();
        toPanel.add(label);
        add(toPanel, BorderLayout.NORTH);

        JPanel checkPanel = new JPanel();
        JButton chechAll = new JButton("전체 10개 추가");
        chechAll.setPreferredSize(new Dimension(120, 10));
        chechAll.addActionListener(new ActionSelectAll(canCheckList));

        String[] canSelectNum = {"10개", "20개", "50개"};

        for (int i = 0; i < CanArray.canList.size(); i++) {
            JPanel checkEach = new JPanel();
            canCheck = new JCheckBox(CanArray.canList.get(i).getCanName());
            JComboBox<String> canSelectBox = new JComboBox();

            for (String s : canSelectNum) {
                canSelectBox.addItem(s);
            }

            canCheckList.add(canCheck);
            canSelectList.add(canSelectBox);

            checkEach.add(canCheck);
            checkEach.add(canSelectBox);
            canSelectBox.setVisible(false);

            checkPanel.add(checkEach);
            canCheck.addActionListener(new ActionCheck(canSelectList));
            checkEach.setPreferredSize(new Dimension(160, 30));
        }


        add(chechAll, BorderLayout.WEST);
        add(checkPanel, BorderLayout.CENTER);

        JButton btnAdd = new JButton("추가");
        JButton btnCancle = new JButton("취소");

        JPanel buttonPanel = new JPanel();
        buttonPanel.add(btnAdd);
        buttonPanel.add(btnCancle);
        add(buttonPanel, BorderLayout.SOUTH);
        btnAdd.addActionListener(new ActionAddCan(this, chechAll, canCheckList, canSelectList));
        btnCancle.addActionListener(new ActionCancle(this));
        setVisible(true);
    }

    public void actionPerformed(ActionEvent e) {
        addCanFrame(canTable);
    }
}
