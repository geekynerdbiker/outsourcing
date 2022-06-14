import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.image.BufferedImage;
import java.io.File;
import java.io.IOException;
import java.util.Random;
import javax.imageio.ImageIO;
import javax.swing.*;

public class MyImageFrame extends JFrame implements ActionListener {
    private int pieces = 4;
    private int totalPieces = pieces * pieces;
    private int[] pieceNumber;
    private BufferedImage img;

    Thread p_display;
    JLabel w1, w2, w3;
    int mm, ss, ms, t = 0;
    int count = 0;

    boolean isSel = false;
    int selBtn1;
    int selBtn2;

    JPanel gamePanel = new JPanel();
    JButton button = new JButton("Divide");
    JButton changeImg = new JButton("Image Change");
    JComboBox<String> cbPieces = new JComboBox<String>();
    int onePiecesSize = 600 / pieces;

    public MyImageFrame() {
        setTitle("Image Draw Test");
        try {
            img = ImageIO.read(new File("hubble.jpg"));
        } catch (IOException e) {
            System.out.println(e.getMessage());
            System.exit(0);
        }
        pieceNumber = new int[totalPieces];
        for (int i = 0; i < totalPieces; i++) {
            pieceNumber[i] = i;
        }

        JPanel wp = new JPanel(new FlowLayout(FlowLayout.CENTER));
        JLabel c1 = new JLabel(" : ");
        JLabel c2 = new JLabel(" : ");
        w1 = new JLabel("00");
        w2 = new JLabel("00");
        w3 = new JLabel("00");

        wp.add(w1);
        wp.add(c1);
        wp.add(w2);
        wp.add(c2);
        wp.add(w3);

        add(wp, BorderLayout.NORTH);

        add(new MyPanel(), BorderLayout.CENTER);
        cbPieces.addItem("3");
        cbPieces.addItem("4");
        cbPieces.addItem("5");
        cbPieces.addItem("6");
        cbPieces.addItem("7");
        changeImg.addActionListener(this);
        button.addActionListener(this);
        gamePanel.add(button);
        gamePanel.add(cbPieces);
        gamePanel.add(changeImg);
        add(gamePanel, BorderLayout.SOUTH);
        setSize(900, 700);
        setVisible(true);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
    }

    void divide() {
        Random rand = new Random();
        int ri;
        for (int i = 0; i < totalPieces; i++) {
            ri = rand.nextInt(totalPieces);
            int tmp = pieceNumber[i];
            pieceNumber[i] = pieceNumber[ri];
            pieceNumber[ri] = tmp;
        }

        p_display = new Thread(new Runnable() {
            @Override
            public void run() {
                mm = Integer.parseInt(w1.getText());
                ss = Integer.parseInt(w2.getText());
                ms = Integer.parseInt(w3.getText());

                while (p_display == Thread.currentThread()) {
                    mm = t % (1000 * 60) / 100 / 60;
                    ss = t % (1000 * 60) / 100 % 60;
                    ms = t % 100;

                    try {
                        Thread.sleep(10);

                        w1.setText(String.format("%02d", mm));
                        w2.setText(String.format("%02d", ss));
                        w3.setText(String.format("%02d", ms));
                        t++;
                    } catch (InterruptedException ignored) {
                    }
                }
            }
        });

        p_display.start();
    }

    boolean isGameOver() {
        for (int i = 0; i < totalPieces; i++) {
            if (pieceNumber[i] != i) {
                return false;
            }
        }
        return true;
    }

    class MyPanel extends JPanel {
        public MyPanel() {
            addMouseListener(new MouseAdapter() {
                @Override
                public void mousePressed(MouseEvent e) {
                    Point p = e.getPoint();
                    if (600 < p.x || 600 < p.y) {
                        return;
                    }
                    int pieceWidth = img.getWidth(null) / pieces;
                    int pieceHeight = img.getHeight(null) / pieces;
                    int selx = p.x / onePiecesSize;
                    int sely = p.y / onePiecesSize;
                    if (!isSel) {
                        selBtn1 = sely * pieces + selx;

                        isSel = true;
                    } else {
                        selBtn2 = sely * pieces + selx;
                        isSel = false;
                        int tmp = pieceNumber[selBtn1];
                        pieceNumber[selBtn1] = pieceNumber[selBtn2];
                        pieceNumber[selBtn2] = tmp;
                        count++;
                        repaint();
                        if (isGameOver()) {
                            p_display = null;
                            JOptionPane.showMessageDialog(null, "Game Over!\nTime: " + mm+":"+ss+":"+ms+"\nClick: "+count);
                            MyImageFrame.this.add(gamePanel, BorderLayout.SOUTH);
                            MyImageFrame.this.repaint();
                        }
                    }
                }
            });
        }

        public void paintComponent(Graphics g) {
            super.paintComponent(g);
            int pieceWidth = img.getWidth(null) / pieces;
            int pieceHeight = img.getHeight(null) / pieces;
            for (int x = 0; x < pieces; x++) {
                int sy = x * onePiecesSize;
                for (int y = 0; y < pieces; y++) {
                    int sx = y * onePiecesSize;
                    int number = pieceNumber[x * pieces + y];

                    int dx = (number % pieces) * pieceWidth;
                    int dy = (number / pieces) * pieceHeight;
                    g.drawImage(img, sx, sy, sx + onePiecesSize, sy + onePiecesSize,
                            dx, dy, dx + pieceWidth, dy + pieceHeight, null);
                }
            }
            g.drawImage(img, 650, 50, 850, 250,
                    0, 0, img.getWidth(null), img.getHeight(null), null);
        }
    }

    public static void main(String[] args) {
        new MyImageFrame();
    }

    public void actionPerformed(ActionEvent e) {
        if (e.getSource() == button) {
            pieces = Integer.parseInt((String) cbPieces.getSelectedItem());
            onePiecesSize = 600 / pieces;
            totalPieces = pieces * pieces;
            pieceNumber = new int[totalPieces];
            for (int i = 0; i < totalPieces; i++) {
                pieceNumber[i] = i;
            }
            remove(gamePanel);
            divide();
            repaint();
        }

        if (e.getSource() == changeImg) {
            JFileChooser fc = new JFileChooser();
            if (fc.showOpenDialog(this) == JFileChooser.OPEN_DIALOG) {
                String filename = fc.getSelectedFile().getPath();
                try {
                    img = ImageIO.read(new File(filename));
                    repaint();
                } catch (IOException ex) {

                }
            }
        }
    }
}