import java.awt.Dimension;
import java.awt.GridLayout;

import javax.swing.JFrame;
import javax.swing.JPanel;
import javax.swing.border.TitledBorder;

public class ActivityMonitorGUI extends JFrame {

    public ActivityMonitorGUI() {
        setTitle("Activity Monitor Tracker");
        setLayout(new GridLayout(3,1));

        JPanel  memoryUsagePnl = new JPanel();
        memoryUsagePnl.setBorder(new TitledBorder("Memory Usage Alert"));
        add(memoryUsagePnl);

        setPreferredSize(new Dimension(600,600));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        pack();
    }

    public static void main(String[] args) {
        ActivityMonitor app = new ActivityMonitor();
    }

}
