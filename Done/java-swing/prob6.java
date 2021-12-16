import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.KeyEvent;
import java.awt.event.KeyListener;
import javax.swing.*;

class prob6 extends JFrame {
    JLabel mainL;
    GridLayout grid;
    Container c;

    int num = 0;
    int op1, op2 = 0;
    char op = ' ';

    /*


    6-1


    */
    public prob6() {
        mainL.setFont(new Font("고딕", Font.BOLD, 40)); // 1
        mainL.setHorizontalAlignment(JLabel.RIGHT); // 2
        mainL.setOpaque(true); // 3
        mainL.setBackground(Color.ORANGE); // 4

        Panel p = new Panel();
        grid = new GridLayout(); // 5
        grid.setVgap(5); // 6
        p.setLayout(grid); // 7

        c.add(p, BorderLayout.CENTER); // 8
    }

    /*


    6-2


    */
    class NumActionListener implements ActionListener { // 1
        @Override
        public void actionPerformed(ActionEvent e) {  // 2
            JButton b = (JButton) e.getSource(); // 3
            int btnNum = Integer.parseInt(b.getText()); // 4
            if (b.getText().compareTo("00") == 0) // 5
                num = num * 100; // 6
            else
                num = num * 10 + btnNum; // 7
            mainL.setText(Integer.toString(btnNum)); // 8
        }
    }

    /*


    6-3


    */
    class OpActionListener implements ActionListener {
        @Override
        public void actionPerformed(ActionEvent e) {
            JButton b = (JButton) e.getSource(); // 1
            char opChar = b.getText().charAt(0);

            if (op == ' ') // 2
                op1 = num; // 3
            else {
                int result = 0;
                op2 = num; // 4
                switch (op) {
                    case '+':
                        result = op1 + op2; // 5
                    case '-':
                }
                mainL.setText(Integer.toString(result)); // 6
                op1 = result; // 7
            }
            op = opChar; // 8
            num = 0; // 9
        }
    }

    /*


    6-4


    */
    class MyKeyListener implements KeyListener { // 1
        @Override
        public void keyPressed(KeyEvent e) { //2
            char keyChar = e.getKeyChar(); // 3
            if( keyChar >= '0' && keyChar <= '9') // 4
                ;

        }

        @Override
        public void keyTyped(KeyEvent e) {

        }


        @Override
        public void keyReleased(KeyEvent e) {

        }
    }
}



