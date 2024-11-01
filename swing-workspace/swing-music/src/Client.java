import java.awt.*;
import java.awt.event.*;
import java.awt.geom.AffineTransform;
import java.awt.image.BufferedImage;
import java.io.*;
import java.net.Socket;
import java.util.Scanner;

import javax.imageio.ImageIO;
import javax.sound.sampled.*;
import javax.swing.*;
import javax.swing.event.ChangeEvent;
import javax.swing.event.ChangeListener;
import javax.xml.crypto.Data;


public class Client {
    final static int FILE_TRANSFER_PORT_NUM = 9000;

    static JFrame frame1 = new JFrame("Music Player");
    static JFrame frame4 = new JFrame("WELCOME");

    static JPanel album_list;
    static JPanel song_list;
    static JPanel fourth_lyrics;
    static JPanel fourth_album_show;
    static JLabel fourth_album_show_label;

    //GUI
    static BufferedReader in = null;
    static PrintWriter out = null;
    static String IP = "127.0.0.1";
    static Socket myClient;

    public static void main(String[] args) {
        try {
            myClient = new Socket(IP, 8189);

            try {
                in = new BufferedReader(new InputStreamReader(
                        myClient.getInputStream()));
            } catch (IOException ioe) {
                ioe.printStackTrace();
            }

            try {
                out = new PrintWriter(myClient.getOutputStream(), true);

            } catch (IOException ioe1) {
                ioe1.printStackTrace();
            }

            frame1.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame1.getContentPane().add(new mainPanel());
            frame1.pack();
            frame1.setVisible(true);

        } catch (IOException io) {
            io.printStackTrace();
        }
    }

    public static void request_song_info(String song_id, BufferedReader in, PrintWriter out) {
        request_music(song_id, in, out);
        request_lyrics(song_id, in, out);
        request_image(song_id, in, out);
        System.out.println("request_song");
    }

    public static void request_music(String song_id, BufferedReader in, PrintWriter out) {
        final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {

            System.out.println(in.readLine());

            String IP = "127.0.0.1";
            Socket socket = new Socket(IP, FILE_TRANSFER_PORT_NUM);
            InputStream is = socket.getInputStream();
            FileOutputStream fos = new FileOutputStream(Database.getSong_dir(Integer.parseInt(song_id)+1));

            out.println(song_id);

            System.out.println(in.readLine());

            out.println("�뷡���� �غ�Ϸ�");

            Thread.sleep(300);
            while ((readBytes = is.read(buffer)) != -1) {
                fos.write(buffer, 0, readBytes);
            }

            fos.close();
            is.close();
            socket.close();
            System.exit(0);
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void request_lyrics(String song_id, BufferedReader in, PrintWriter out) {
        final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {

            System.out.println(in.readLine());

            String IP = "127.0.0.1";
            Socket socket = new Socket(IP, FILE_TRANSFER_PORT_NUM);
            InputStream is = socket.getInputStream();
            FileOutputStream fos = new FileOutputStream(Database.getLyrics_dir(Integer.parseInt(song_id)+1));

            out.println(song_id);

            System.out.println(in.readLine());

            out.println("������� �غ�Ϸ�");

            Thread.sleep(300);
            while ((readBytes = is.read(buffer)) != -1) {
                fos.write(buffer, 0, readBytes);
            }
            fos.close();
            is.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static void request_image(String song_id, BufferedReader in, PrintWriter out) {
        final int DEFAULT_BUFFER_SIZE = 10000;
        byte[] buffer = new byte[DEFAULT_BUFFER_SIZE];
        int readBytes;

        try {

            System.out.println(in.readLine());

            String IP = "127.0.0.1";
            Socket socket = new Socket(IP, FILE_TRANSFER_PORT_NUM);
            InputStream is = socket.getInputStream();
            FileOutputStream fos = new FileOutputStream(Database.getImage_dir(Integer.parseInt(song_id)+1));

            out.println(song_id);

            System.out.println(in.readLine());

            out.println("�ٹ� �̹��� ���� �غ�Ϸ�");

            Thread.sleep(300);
            while ((readBytes = is.read(buffer)) != -1) {
                fos.write(buffer, 0, readBytes);
            }
            fos.close();
            is.close();
            socket.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    //main 화면
    static class mainPanel extends JPanel {
        BufferedImage main_logo;

        mainPanel() {

            try {
                main_logo = ImageIO.read(new File("main.png"));

            } catch (Exception e) {
                e.printStackTrace();
            }
            JButton main_logo_label = new JButton(new ImageIcon(main_logo));
            main_logo_label.setPreferredSize(new Dimension(1280, 1024));
            setPreferredSize(new Dimension(1280, 1024)); //창크기
            setLayout(new BorderLayout());

            add(main_logo_label, BorderLayout.CENTER);
            main_logo_label.addActionListener(new mainPanel_listener());
        }
    }

    static class mainPanel_listener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            frame1.dispose();
            frame4.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
            frame4.getContentPane().add(new playerPanel());
            frame4.pack();
            frame4.setVisible(true);
        }
    }


    static class playerPanel extends JPanel implements ActionListener, LineListener, ChangeListener {
        public static JButton play = new JButton(">");
        public static JButton stop = new JButton("ㅁ");
        public static JButton pause = new JButton("||");
        public static JSlider time = new JSlider();
        public static JSlider volume = new JSlider();
        public static JButton lyrics = new JButton("lyrics");
        public static JLabel label_volume = new JLabel("volume");
        public static JButton playlist = new JButton("playlist");
        public static JButton quit = new JButton("quit");
        public static ScrollPane scroll = new ScrollPane();
        public static JLabel label_song = new JLabel("");
        public static JLabel label_singer = new JLabel("");

        private static Clip clip;

        private boolean isPlay = false;

        private static File wavFile = new File("song.wav");

        private static AudioInputStream ais;
        static Timer t = null;

        playerPanel() {
            this.setPreferredSize(new Dimension(1280, 1024));
            setBackground(new Color(200, 200, 200));
            setLayout(null);
            fourth_album_show = new JPanel();
            fourth_album_show.setPreferredSize(new Dimension(500, 500));
            //fourth_album_show.setBackground(new Color(200, 200, 200));

            stop.setBounds(50, 750, 120, 80);
            play.setBounds(210, 750, 120, 80);
            pause.setBounds(370, 750, 120, 80);
            time.setBounds(50, 700, 450, 30);
            volume.setBounds(150, 900, 250, 30);
            lyrics.setBounds(650, 20, 250, 50);
            label_volume.setBounds(100, 900, 120, 30);
            playlist.setBounds(950, 20, 250, 50);
            quit.setBounds(0, 950, 1280, 30);
            time.setPreferredSize(new Dimension(450, 30));
            scroll.setBounds(650, 100, 600, 950);
            fourth_album_show.setBounds(20, 20, 500, 500);
            label_song.setBounds(50, 550, 190, 50);
            label_singer.setBounds(50, 600, 200, 50);
            scroll.setWheelScrollingEnabled(true);

            label_song.setText("Test TItle");
            label_singer.setText("Me");

            this.add(play);
            this.add(stop);
            this.add(pause);
            this.add(time);
            this.add(volume);
            this.add(lyrics);
            this.add(label_volume);
            this.add(playlist);
            this.add(quit);
            this.add(scroll);
            this.add(fourth_album_show);
            this.add(label_song);
            this.add(label_singer);
            fourth_album_show_label = new JLabel();
            BufferedImage main_logo = null;

            try {
                main_logo = ImageIO.read(new File("main.png"));
            } catch (Exception e) {
                e.printStackTrace();
            }
            fourth_album_show_label.setIcon(new ImageIcon(main_logo));
            fourth_album_show.add(fourth_album_show_label);

            play.addActionListener(this);
            stop.addActionListener(this);
            pause.addActionListener(this);
            volume.addChangeListener(this);
            time.addChangeListener(this);
            playlist.addActionListener(this);
            lyrics.addActionListener(this);
            quit.addActionListener(this);

            t = new Timer(100, new ActionListener() {
                public void actionPerformed(ActionEvent e) {

                    int current = clip.getFramePosition();
                    int length = clip.getFrameLength();

                    time.setValue(100 * current / length);

                }
            });

            try {
                ais = AudioSystem.getAudioInputStream(wavFile);

                clip = AudioSystem.getClip();

                clip.open(ais);

                clip.addLineListener(this);
            } catch (Exception e) {
            }
        }

        public void actionPerformed(ActionEvent ae) {

            if (ae.getSource() == play) {
                isPlay = true;
                clip.start();
                t.start();
            } else if (ae.getSource() == stop) {
                isPlay = false;
                clip.setMicrosecondPosition(0);
                clip.stop();
                t.stop();
            } else if (ae.getSource() == pause) {
                isPlay = false;
                clip.stop();
                t.stop();
            } else if (ae.getSource() == playlist) {
                scroll.removeAll();
                scroll.add(album_list = new panel_fourth_songlist());
            } else if (ae.getSource() == lyrics) {
                scroll.removeAll();
                scroll.add(fourth_lyrics = new panel_fourth_lyrics());

            } else if (ae.getSource() == quit) {
                frame4.dispose();
                try {
                    out.println("quit");
                    in.close();
                    out.close();
                    myClient.close();
                    System.exit(0);
                } catch (Exception e) {

                }

            }
        }

        public void stateChanged(ChangeEvent ce) {

            if (ce.getSource() == volume) {
                FloatControl gainControl = (FloatControl) clip.getControl(FloatControl.Type.MASTER_GAIN);
                float dB = (float) (Math.log(volume.getValue() / 100f) / Math.log(10.0) * 20);
                gainControl.setValue(dB);
                if (isPlay == true) {
                    clip.start();
                    t.start();
                }
            }

            if (ce.getSource() == time) {
                clip.setFramePosition(time.getValue() * clip.getFrameLength() / 100);
                if (isPlay == true) {
                    clip.start();
                    t.start();
                }
            }
        }

        public void update(LineEvent arg0) {
        }
    }

    static class panel_fourth_songlist extends JPanel {
        public panel_fourth_songlist() {
            setPreferredSize(new Dimension(475, 600));
            setBackground(new Color(95, 185, 25));

            int al_len = Database.getMusic_len();
            song_label[] temp = new song_label[al_len];
            setLayout(new GridLayout(100, 1));
            out.println("songlist_album");
            for (int i = 0; i < al_len; i++) {
                try {
                    temp[i] = new song_label();
                    temp[i].setText(Database.getSong_name(i + 1)); // �뷡�̸� ���޹ް�
                    temp[i].setID(i); // id �ְ�
                    temp[i].setText(Database.getSinger(i + 1));

                    temp[i].addMouseListener(new songlistener_fourth());
                    temp[i].setBackground(Color.WHITE);
                    temp[i].setLayout(new GridLayout(100, 1));
                    add(temp[i]);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        }
    }

    static class song_label extends JLabel {
        int id = 0;

        song_label() {
            super();
        }

        public void setID(int i) {
            this.id = i;
        }

        public int getID() {
            return id;
        }
    }

    static class songlistener_fourth implements MouseListener {

        @Override
        public void mouseClicked(MouseEvent arg0) {
            // TODO Auto-generated method stub
            int id = ((song_label) arg0.getSource()).getID();
            System.out.println(id);
            out.println("request_song");

            request_song_info(Integer.toString(id), in, out);


            BufferedImage image = null;

            try {
                image = ImageIO.read(new File(Database.getImage_dir(id + 1)));
            } catch (Exception e) {
                e.printStackTrace();
            }
            try {
                fourth_album_show_label.setIcon(new ImageIcon(image));

                if (playerPanel.clip != null) {
                    playerPanel.clip.setMicrosecondPosition(0);
                    playerPanel.clip.stop();
                }
                playerPanel.wavFile = new File(Database.getSong_dir(id+1));
                playerPanel.ais = AudioSystem.getAudioInputStream(playerPanel.wavFile);
                // clip ������
                playerPanel.clip = AudioSystem.getClip();

                // AudioInputStream �ε�
                playerPanel.clip.open(playerPanel.ais);

                playerPanel.clip.setMicrosecondPosition(0);

                playerPanel.clip.start();

                playerPanel.t.start();

                playerPanel.scroll.removeAll();
                playerPanel.scroll.add(album_list = new panel_fourth_songlist());

            } catch (Exception e) {
                e.printStackTrace();
            }

        }

        @Override
        public void mouseEntered(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void mouseExited(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void mousePressed(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

        @Override
        public void mouseReleased(MouseEvent arg0) {
            // TODO Auto-generated method stub

        }

    }

    static class panel_fourth_lyrics extends JPanel {
        panel_fourth_lyrics() {

            try {
                setLayout(new GridLayout(300, 1));

                Scanner inFile = new Scanner(new FileReader(Database.getLyrics_dir(1)));

                while (inFile.hasNext()) {
                    JLabel temp = new JLabel(inFile.nextLine());
                    add(temp);

                }


            } catch (Exception e) {
                e.printStackTrace();
            }
        }
    }
}