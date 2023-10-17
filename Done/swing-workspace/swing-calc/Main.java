import java.awt.*;
import java.awt.event.*;
import javax.swing.*;

public class Main implements ActionListener {
    private JFrame CalculatorFrame;
    private JPanel CalculatorPanel;
    private JLabel operation, result;

    JButton verticalView, copyExpression;
    String temp;

    boolean isVertical = false;
    public static void main(String[] args) {
        Main main = new Main();
        main.showBasicCalculatorLayout();
    }


    private void showBasicCalculatorLayout() {
        CalculatorFrame = new JFrame("Basic Calculator");
        Dimension dimension = Toolkit.getDefaultToolkit().getScreenSize();
        int x = (int) ((dimension.getWidth() - 760) / 2);
        int y = (int) ((dimension.getHeight() - 660) / 2);
        CalculatorFrame.setBounds(x, y, 760, 660);
        CalculatorFrame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        CalculatorFrame.setResizable(false);
        CalculatorPanel = new JPanel();
        GridBagLayout gridBagLayout = new GridBagLayout();
        CalculatorPanel.setLayout(gridBagLayout);
        GridBagConstraints gridBagConstraints = new GridBagConstraints();

        gridBagConstraints.fill = GridBagConstraints.HORIZONTAL;
        String[] buttonsContent = {"7", "8", "9", "AC", "Del", "4", "5", "6", "+", "(", "1", "2", "3", "-", ")", "0", "*", "/", ".", "="};
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 0;
        gridBagConstraints.gridwidth = 5;
        operation = new JLabel("", SwingConstants.RIGHT);

        operation.setPreferredSize(new Dimension(700, 80));
        CalculatorPanel.add(operation, gridBagConstraints);
        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 1;
        gridBagConstraints.gridwidth = 5;
        result = new JLabel("", SwingConstants.RIGHT);

        result.setPreferredSize(new Dimension(700, 80));
        CalculatorPanel.add(result, gridBagConstraints);
        int gridy = 2;
        int gridx = 0;
        for (int i = 0; i < buttonsContent.length; i += 1) {
            gridBagConstraints.gridx = gridx;
            gridBagConstraints.gridy = gridy;
            gridBagConstraints.gridwidth = 1;
            JButton button = new JButton(buttonsContent[i]);
            button.addActionListener(this);

            button.setPreferredSize(new Dimension(140, 80));
            CalculatorPanel.add(button, gridBagConstraints);
            if ((i + 1) % 5 == 0) {
                gridy++;
                gridx = 0;
            } else
                gridx += 1;
        }


        gridBagConstraints.gridx = 0;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 2;
        verticalView = new JButton("Vertical View");
        verticalView.addActionListener(this);
        verticalView.setPreferredSize(new Dimension(280, 80));
        CalculatorPanel.add(verticalView, gridBagConstraints);


        gridBagConstraints.gridx = 2;
        gridBagConstraints.gridy = 6;
        gridBagConstraints.gridwidth = 3;
        copyExpression = new JButton("Copy Expression");
        copyExpression.addActionListener(this);
        copyExpression.setPreferredSize(new Dimension(420, 80));
        CalculatorPanel.add(copyExpression, gridBagConstraints);


        CalculatorFrame.add(CalculatorPanel);
        CalculatorFrame.setVisible(true);
    }

    @Override
    public void actionPerformed(ActionEvent e) {
        if (((JButton) e.getSource()).getText().equals("=")) {
            if (!operation.getText().isEmpty()) {
                try {
                    if(isVertical) result.setText(String.valueOf((long)Expression.evaluate(temp)));
                    else result.setText(String.valueOf((long)Expression.evaluate(operation.getText())));
                } catch (Exception exception) {
                    result.setText(exception.getMessage());
                }
            } else {
                result.setText("Syntax Error");
            }
        } else if (((JButton) e.getSource()).getText().equals("Vertical View")) {
            isVertical = true;
                temp = operation.getText();

                StringBuilder vertical = new StringBuilder();
                vertical.append("<HTML><p style=\"text-align:right;\">");
                int newLine = 0;
                for (int i = 0; i < operation.getText().length(); i++) {
                    char op = operation.getText().charAt(i);
                    if (op == '+' || op == '-' || op == '*' || op == '/') {
                        vertical.append(operation.getText(), newLine, i);
                        vertical.append("<br>");
                        newLine = i;
                    }
                }
                if (vertical.length() != 0) {
                    vertical.append(operation.getText().substring(newLine));
                    vertical.append("</p></HTML>");
                    operation.setText(vertical.toString());
                }
                verticalView.setText("Normal View");

            } else if (((JButton) e.getSource()).getText().equals("Normal View")) {
            isVertical = false;
                operation.setText(temp);
                verticalView.setText("Vertical View");

        } else if (((JButton) e.getSource()).getText().equals("Copy Expression")) {
            temp = operation.getText();
            operation.setText("Copied!");
            copyExpression.setText("Paste Expression");
        } else if (((JButton) e.getSource()).getText().equals("Paste Expression")) {
            operation.setText(temp);
            copyExpression.setText("Copy Expression");
        } else if (((JButton) e.getSource()).getText().equals("AC")) {
            result.setText("");
            operation.setText("");
        } else if (((JButton) e.getSource()).getText().equals("Del")) {
            operation.setText((operation.getText() == null || operation.getText().length() == 0) ? operation.getText() : operation.getText().substring(0, operation.getText().length() - 1));
        } else {
            if (operation.getText() == "Copied!") operation.setText("");
            JButton jButton = (JButton) e.getSource();
            String buttonText = jButton.getText();
            operation.setText(operation.getText() + buttonText);
        }
    }

}