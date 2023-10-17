import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.ArrayList;
import java.util.Objects;

public class TripPlanner {
    private JFrame frame;

    private static String s = new String("");
    private static String fare = new String("");
    private static String baseFare = new String("");
    private static String farePerDistance = new String("");
    private static String numStations = new String("");
    private static final ArrayList<PublicTransport> transport = new ArrayList<>();

    private boolean isBaseFare = false, isDistanceFare = false, isNStations = false;

    private boolean isTrain = false;
    private boolean isBus = false;
    private boolean isTaxi = false;

    private static void printFare(JTextPane tPane) {
        int count = 1;
        double transportFare = 0, totalTripFare = 0;
        s = "";

        for (PublicTransport transport : transport) {
            s += "Transport " + count + ": ";

            if (transport.getModel().equals("KORAIL")) {
                transportFare = ((Train) transport).calculatePayment();
                totalTripFare += transportFare;
                s += "KORAIL\n";
                s += "Fare: " + transportFare + "\n";
            } else if (transport.getModel().equals("KORBUS")) {
                transportFare = ((Bus) transport).calculatePayment();
                totalTripFare += transportFare;
                s += "KORBUS\n";
                s += "Fare: " + transportFare + "\n";
            } else if (transport.getModel().equals("KAKAO TAXI")) {
                transportFare = ((Taxi) transport).calculatePayment();
                totalTripFare += transportFare;
                s += "KAKAO TAXI\n";
                s += "Fare: " + transportFare + "\n";
            }

            count += 1;
        }

        s += "=====================\n" + "Total Trip Fare: " + totalTripFare + "\n";
        tPane.setText(s);
    }

    public TripPlanner() {
        init();
    }

    private void init() {
        frame = new JFrame();
        frame.setBounds(100, 100, 600, 700);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel sTrainPlanner = new JLabel("TRIP PLANNER");
        sTrainPlanner.setHorizontalAlignment(SwingConstants.CENTER);
        sTrainPlanner.setBounds(120, 100, 280, 20);
        frame.getContentPane().add(sTrainPlanner);

        JLabel topImage = new JLabel("");
        topImage.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/planner_logo.png"))));
        topImage.setBounds(90, 20, 500, 80);
        frame.getContentPane().add(topImage);

        JTextPane tPane = new JTextPane();
        tPane.setText("Choose transport (from left menu):");
        tPane.setEditable(false);
        tPane.setBounds(140, 120, 270, 230);
        frame.getContentPane().add(tPane);


        JButton trainButton = new JButton("TRAIN");
        trainButton.addActionListener(new ActionListener() {
            // behavior if train button pushed
            public void actionPerformed(ActionEvent e) {
                isTrain = true;
                isBaseFare = true;
                s = "You choose TRAIN\nEnter base fare: ";
                tPane.setText(s);
            }
        });

        trainButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/train.png"))));
        trainButton.setBackground(UIManager.getColor("Button.background"));
        trainButton.setBounds(40, 120, 100, 40);
        frame.getContentPane().add(trainButton);

        JButton busButton = new JButton("BUS");
        busButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                isBus = true;
                isBaseFare = true;
                s = "You choose BUS\nEnter base fare: ";
                tPane.setText(s);
            }
        });
        busButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/bus.png"))));
        busButton.setBackground(SystemColor.window);
        busButton.setBounds(40, 160, 100, 40);
        frame.getContentPane().add(busButton);

        JButton taxiButton = new JButton("TAXI");
        taxiButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                isTaxi = true;
                isBaseFare = true;
                s = "You choose TAXI\nEnter base fare: ";
                tPane.setText(s);
            }
        });
        taxiButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/taxi.png"))));
        taxiButton.setBackground(SystemColor.window);
        taxiButton.setBounds(40, 200, 100, 40);
        frame.getContentPane().add(taxiButton);

        JButton yesButton = new JButton("Yes");
        yesButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                isBaseFare = false;
                isDistanceFare = false;
                isNStations = false;
                isBus = false;
                isTrain = false;
                isTaxi = false;

                tPane.setText("Choose transport (from left menu): ");
            }
        });
        yesButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/enterSmall.png"))));
        yesButton.setBackground(SystemColor.window);
        yesButton.setBounds(410, 120, 160, 40);
        frame.getContentPane().add(yesButton);

        JButton noButton = new JButton("No");
        noButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                printFare(tPane);
            }
        });
        noButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/cancelSmall.png"))));
        noButton.setBackground(SystemColor.window);
        noButton.setBounds(410, 160, 160, 40);
        frame.getContentPane().add(noButton);

        JButton cancelButton = new JButton("CANCEL");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = "";

                isBaseFare = false;
                isDistanceFare = false;
                isNStations = false;
                isBus = false;
                isTrain = false;
                isTaxi = false;

                transport.clear();

                s = "Cancelled!\n" + "New plan:\n" + "Choose transport (from left menu):";
                tPane.setText(s);
            }
        });
        cancelButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/cancel.png"))));
        cancelButton.setBackground(SystemColor.window);
        cancelButton.setBounds(410, 350, 150, 70);
        frame.getContentPane().add(cancelButton);

        JButton clearButton = new JButton("CLEAR");
        clearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                s = s.substring(0, s.length() - fare.length());
                tPane.setText(s);

                fare = "";
            }
        });
        clearButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/clear.png"))));
        clearButton.setBackground(SystemColor.window);
        clearButton.setBounds(410, 420, 150, 70);
        frame.getContentPane().add(clearButton);

        JButton enterButton = new JButton("ENTER");
        enterButton.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/enter.png"))));
        enterButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isBaseFare) {
                    isBaseFare = false;
                    isDistanceFare = true;

                    baseFare = fare;
                    fare = "";

                    if (isTaxi) {
                        s = "Enter fare per km: ";
                        tPane.setText(s);
                    } else {
                        s = "Enter fare per station (for extra stations): ";
                        tPane.setText(s);
                    }
                    isNStations = true;
                } else if (isDistanceFare) {
                    isDistanceFare = false;
                    isNStations = true;
                    farePerDistance = fare;
                    fare = "";

                    if (isTaxi) {
                        s = "Enter distance (in km): ";
                        tPane.setText(s);
                    } else {
                        s = "Enter number of stations: ";
                        tPane.setText(s);
                    }
                } else if (isNStations) {
                    isNStations = false;
                    numStations = fare;
                    fare = "";

                    if (isTrain) {
                        isTrain = false;
                        transport.add(new Train(Double.parseDouble(baseFare), Double.parseDouble(farePerDistance),
                                Integer.parseInt(numStations)));
                    } else if (isBus) {
                        isBus = false;
                        transport.add(new Bus(Double.parseDouble(baseFare), Double.parseDouble(farePerDistance),
                                Integer.parseInt(numStations)));
                    } else if (isTaxi) {
                        isTaxi = false;
                        transport.add(new Taxi(Double.parseDouble(baseFare), Double.parseDouble(farePerDistance),
                                Double.parseDouble(numStations)));
                    }

                    s = "Add more transport (from right menu)?";
                    tPane.setText(s);
                }
            }
        });
        enterButton.setBackground(SystemColor.window);
        enterButton.setBounds(410, 490, 150, 70);
        frame.getContentPane().add(enterButton);

        JButton numberButton_1 = new JButton("");
        numberButton_1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "1";
                s += "1";
                tPane.setText(s);
            }
        });
        numberButton_1.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/1.png"))));
        numberButton_1.setBackground(SystemColor.window);
        numberButton_1.setBounds(140, 350, 90, 70);
        frame.getContentPane().add(numberButton_1);

        JButton numberButton_2 = new JButton("");
        numberButton_2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "2";
                s += "2";
                tPane.setText(s);
            }
        });
        numberButton_2.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/2.png"))));
        numberButton_2.setBackground(SystemColor.window);
        numberButton_2.setBounds(230, 350, 90, 70);
        frame.getContentPane().add(numberButton_2);

        JButton numberButton_3 = new JButton("");
        numberButton_3.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/3.png"))));
        numberButton_3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "3";
                s += "3";
                tPane.setText(s);
            }
        });
        numberButton_3.setBackground(SystemColor.window);
        numberButton_3.setBounds(320, 350, 90, 70);
        frame.getContentPane().add(numberButton_3);

        JButton numberButton_4 = new JButton("");
        numberButton_4.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "4";
                s += "4";
                tPane.setText(s);
            }
        });
        numberButton_4.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/4.png"))));
        numberButton_4.setBackground(SystemColor.window);
        numberButton_4.setBounds(140, 420, 90, 70);
        frame.getContentPane().add(numberButton_4);

        JButton numberButton_5 = new JButton("");
        numberButton_5.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "5";
                s += "5";
                tPane.setText(s);
            }
        });
        numberButton_5.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/5.png"))));
        numberButton_5.setBackground(SystemColor.window);
        numberButton_5.setBounds(230, 420, 90, 70);
        frame.getContentPane().add(numberButton_5);

        JButton numberButton_6 = new JButton("");
        numberButton_6.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "6";
                s += "6";
                tPane.setText(s);
            }
        });
        numberButton_6.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/6.png"))));
        numberButton_6.setBackground(SystemColor.window);
        numberButton_6.setBounds(320, 420, 90, 70);
        frame.getContentPane().add(numberButton_6);


        JButton numberButton_7 = new JButton("");
        numberButton_7.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "7";
                s += "7";
                tPane.setText(s);
            }
        });
        numberButton_7.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/7.png"))));
        numberButton_7.setBackground(SystemColor.window);
        numberButton_7.setBounds(140, 490, 90, 70);
        frame.getContentPane().add(numberButton_7);

        JButton numberButton_8 = new JButton("");
        numberButton_8.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "8";
                s += "8";
                tPane.setText(s);
            }
        });
        numberButton_8.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/8.png"))));
        numberButton_8.setBackground(SystemColor.window);
        numberButton_8.setBounds(230, 490, 90, 70);
        frame.getContentPane().add(numberButton_8);

        JButton numberButton_9 = new JButton("");
        numberButton_9.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "9";
                s += "9";
                tPane.setText(s);
            }
        });
        numberButton_9.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/9.png"))));
        numberButton_9.setBackground(SystemColor.window);
        numberButton_9.setBounds(320, 490, 90, 70);
        frame.getContentPane().add(numberButton_9);

        JButton numberButton_0 = new JButton("");
        numberButton_0.setIcon(new ImageIcon(Objects.requireNonNull(TripPlanner.class.getResource("/assets/0.png"))));
        numberButton_0.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                fare = fare + "0";
                s += "0";
                tPane.setText(s);
            }
        });
        numberButton_0.setBackground(SystemColor.window);
        numberButton_0.setBounds(240, 560, 90, 70);
        frame.getContentPane().add(numberButton_0);

    }

    public static void main(String[] args) {
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                try {
                    TripPlanner window = new TripPlanner();
                    window.frame.setVisible(true);
                } catch (Exception e) {
                    e.printStackTrace();
                }
            }
        });
    }
}
