import javax.swing.*;
import javax.swing.border.EmptyBorder;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyChangeEvent;
import java.beans.PropertyChangeListener;
import java.io.FileWriter;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;

public class Main extends JFrame {

    private JPanel contentPane;
    private JLabel topLabel, lblStatus;
    private JPanel bottom, top, middle;
    private JTextArea middleText;
    private JScrollPane middleScroll;
    private JButton cancelButton, okButton;
    private JTextField input;
    private JProgressBar progressBar;


    Thread workThread;
    WorkerClass worker;

    public static void main(String[] args) {
        SwingUtilities.invokeLater(new Runnable() {
            @Override
            public void run() {
                try {
                    Main lucasSeries = new Main();
                    lucasSeries.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }


    public Main() {
        // JFrame attribute setting
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setBounds(100, 100, 900, 400);
        setTitle("Finding Lucas series sum");

        // content pane setting
        contentPane = new JPanel();
        contentPane.setBorder(new EmptyBorder(5, 5, 5, 5));
        contentPane.setLayout(new BorderLayout(0, 0));
        setContentPane(contentPane);

        // top panel setting
        top = new JPanel();
        top.setLayout(new GridLayout(0, 4, 0, 0));
        contentPane.add(top, BorderLayout.NORTH);

        // 1. top label
        topLabel = new JLabel();
        topLabel.setText("Number of row in Lucas series: ");
        top.add(topLabel);

        // 2. top input
        input = new JTextField();
        input.setColumns(10);
        top.add(input);

        // 3. top start button
        okButton = new JButton("Get Sum of Lucas Series");
        okButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {

                // reset all views, JProgressBar, JTextArea, JLabel
                progressBar.setValue(0);
                middleText.setText("");
                lblStatus.setText("Sum = 0");

                // catch number format error using try ~ catch
                int integer;
                try {
                    integer = Integer.parseInt(input.getText());
                    if (integer < 3 || integer > 20) {
                        // show invalid message
                        int response = JOptionPane.showOptionDialog(null, "Enter Valid input!",
                                "Warning", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, null, null);
                    } else {
                        // create and start a thread
                        worker = new WorkerClass(integer);
                        worker.addPropertyChangeListener(new PropertyChangeListener() {
                            @Override
                            public void propertyChange(PropertyChangeEvent evt) {
                                // if the changed property is progress, update the progress bar
                                if (evt.getPropertyName().equals("progress")) {
                                    int newValue = (Integer) evt.getNewValue();
                                    progressBar.setValue(newValue);
                                }
                            }
                        });
                        worker.execute();
                    }
                } catch (NumberFormatException exception) {
                    // show invalid message
                    int response = JOptionPane.showOptionDialog(null, "Enter Valid input!",
                            "Warning", JOptionPane.DEFAULT_OPTION, JOptionPane.INFORMATION_MESSAGE, null, null, null);
                    return ;
                }
            }
        });
        top.add(okButton);

        // 4. top cancel button
        cancelButton = new JButton("Cancel");
        cancelButton.addActionListener(new ActionListener() {
            @Override
            public void actionPerformed(ActionEvent e) {
                worker.stopWork();
            }
        });
        cancelButton.setEnabled(false);
        top.add(cancelButton);

        // middle panel setting
        middle = new JPanel();
        contentPane.add(middle, BorderLayout.CENTER);
        SpringLayout springLayout = new SpringLayout();
        middle.setLayout(springLayout);

        // 1. set textarea in middle
        middleText = new JTextArea();
        middleText.setEditable(false);

        // 2. middle scroll pane
        middleScroll = new JScrollPane(middleText, ScrollPaneConstants.VERTICAL_SCROLLBAR_ALWAYS, ScrollPaneConstants.HORIZONTAL_SCROLLBAR_NEVER);
        springLayout.putConstraint(SpringLayout.NORTH, middleScroll, 5, SpringLayout.NORTH, middle);
        springLayout.putConstraint(SpringLayout.WEST, middleScroll, 0, SpringLayout.WEST, middle);
        springLayout.putConstraint(SpringLayout.SOUTH, middleScroll, -5, SpringLayout.SOUTH, middle);
        springLayout.putConstraint(SpringLayout.EAST, middleScroll, 0, SpringLayout.EAST, middle);

        middle.add(middleScroll);

        // bottom panel setting
        bottom = new JPanel();
        contentPane.add(bottom, BorderLayout.SOUTH);
        bottom.setLayout(new GridLayout(0, 2, 10, 0));

        // 1. progress bar setting
        progressBar = new JProgressBar();
        progressBar.setStringPainted(true);
        bottom.add(progressBar);

        // 2. lbl status setting
        lblStatus = new JLabel();
        bottom.add(lblStatus);
    }

    // function for calculating lucas number
    public int lucas(int N) {
        if (N == 0) return 2;
        if (N == 1) return 1;
        return lucas(N - 1) + lucas(N - 2);
    }

    // declare WorkerClass based on SwingWorker
    public class WorkerClass extends SwingWorker<Integer, String> {
        int num;
        boolean canceled;

        public WorkerClass(int number) {
            num = number;
            canceled = false;
        }

        @Override
        protected Integer doInBackground() throws Exception {
            // Disable Start Button and Enable Cancel Button
            okButton.setEnabled(false);
            cancelButton.setEnabled(true);
            lblStatus.setText("Sum = 0");

            int sum = 0;
            List<String> lucas_list = new ArrayList<>();
            try {
                for (int i = 0; i < num; i++) {
                    if (canceled) {
                        break;
                    }

                    // calculate lucas series
                    Thread.sleep(100);
                    int lucas_num = lucas(i);

                    // calculate sum and show total num
                    sum += lucas_num;
                    lblStatus.setText("Sum = " + Integer.toString(sum));

                    // show progree lucas number
                    middleText.append(Integer.toString(lucas_num) + "\n");
                    middleText.setCaretPosition(middleText.getDocument().getLength());

                    // store lucas number for data file
                    lucas_list.add(Integer.toString(lucas_num));

                    // update the view
                    setProgress((i+1)*100 / num);
                    publish(Integer.toString(lucas_num));
                }
            } catch (InterruptedException e) {
                // update the status
                lblStatus.setText("");
            }

            // write data.txt
            try {
                PrintWriter printWriter = new PrintWriter(new FileWriter("data.txt"));
                printWriter.append("[");
                for (int i = 0; i < lucas_list.size(); i++) {
                    if (i == lucas_list.size() - 1) {
                        printWriter.append(lucas_list.get(i));
                    }
                    else {
                        printWriter.append(lucas_list.get(i) + ",");
                    }
                }
                printWriter.append("]");
                printWriter.flush();
            } catch (Exception e) {
                e.printStackTrace();
            }
            return sum;
        }

        // displays published values
        protected void progress(List<String> publishedVal) {
            for (int i = 0; i < publishedVal.size(); i++) {
                middleText.append(publishedVal.get(i) + "\n");
                middleText.setCaretPosition(middleText.getDocument().getLength());
            }
        }

        // execute when doInBackground completes
        protected void done() {
            // Enable Start Button and disable Cancel Button
            okButton.setEnabled(true);
            cancelButton.setEnabled(false);
        }

        // stop work
        public void stopWork() {
            canceled = true;
        }
    }
}
