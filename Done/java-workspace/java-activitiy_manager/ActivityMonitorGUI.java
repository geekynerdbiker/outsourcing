import java.awt.*;
import java.text.DecimalFormat;

import javax.swing.*;
import javax.swing.border.TitledBorder;

public class ActivityMonitorGUI extends JFrame {

    public ActivityMonitorGUI() {
        setTitle("Activity Monitor Tracker");
        setLayout(new GridLayout(3, 1));

        JPanel memoryUsagePnl = new JPanel();
        memoryUsagePnl.setBorder(new TitledBorder("Memory Usage Alert"));
        add(memoryUsagePnl);

        setPreferredSize(new Dimension(600, 600));
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        pack();
    }

    public static void main(String[] args) {
        JFrame frame = new JFrame();
        frame.setTitle("Activity Monitor Tracker");
        frame.setLayout(new GridLayout(3, 1));

        ActivityMonitor app = new ActivityMonitor(new CpuUtilizationSensor(),
                new DeskUsageSensor(),
                new MemoryUsageSensor());

        frame.setPreferredSize(new Dimension(600, 600));
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.pack();

        frame.add(newPanel(app.cpuValue()));
        frame.add(newPanel(app.memoryValue()));
        frame.add(newPanel(app.deskValue()));

        frame.setVisible(true);
    }

    public static JPanel newPanel(ActivityMonitor.Value value) {
        JPanel panel = new JPanel();
        panel.setBorder(new TitledBorder(value.alertName()));
        BoxLayout layout = new BoxLayout(panel, BoxLayout.Y_AXIS);
        panel.setLayout(layout);
        panel.setAlignmentX(Component.LEFT_ALIGNMENT);

        JPanel emptySpace0 = new JPanel();
        emptySpace0.setMaximumSize(new Dimension(0, 20));
        panel.add(emptySpace0);

        JPanel color = new JPanel();
        color.setMaximumSize(new Dimension((int) (value.ratio() * 300) + 5, 50));
        color.setBackground(value.color);
        color.setAlignmentX(Component.LEFT_ALIGNMENT);
        panel.add(color);

        JPanel emptySpace1 = new JPanel();
        emptySpace1.setMaximumSize(new Dimension(0, 10));
        panel.add(emptySpace1);

        JLabel text = new JLabel();
        DecimalFormat format = new DecimalFormat("#.0");
        text.setText(value.alertText() + " --> " + format.format(value.value));
        text.setAlignmentX(Component.LEFT_ALIGNMENT);
        text.setBorder(BorderFactory.createEmptyBorder(0, 60, 0, 0));
        panel.add(text);

        return panel;
    }

}
