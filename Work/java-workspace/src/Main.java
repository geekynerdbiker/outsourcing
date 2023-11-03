import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import java.awt.BorderLayout;
import java.awt.Point;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;

public class Main {
    private static Point point = new Point();

    public static void main(String[] args) {
        final JFrame frame = new JFrame();

        frame.setUndecorated(true);
        JButton button = new JButton("Close Me");
        button.addActionListener(e -> System.exit(0));
        frame.addMouseListener(new MouseAdapter() {
            public void mousePressed(MouseEvent e) {
                point.x = e.getX();
                point.y = e.getY();
            }
        });

        frame.addMouseMotionListener(new MouseMotionAdapter() {
            public void mouseDragged(MouseEvent e) {
                Point p = frame.getLocation();
                frame.setLocation(p.x + e.getX() - point.x, p.y + e.getY() - point.y);
            }
        });

        frame.setSize(500, 500);
        frame.setLocation(200, 200);
        frame.setLayout(new BorderLayout());

        frame.getContentPane().add(button, BorderLayout.NORTH);
        frame.getContentPane().add(new JLabel("Drag Me", JLabel.CENTER),
                BorderLayout.CENTER);
        frame.setVisible(true);
    }
}