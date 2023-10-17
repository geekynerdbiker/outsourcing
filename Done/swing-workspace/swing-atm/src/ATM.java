import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.text.DecimalFormat;
import java.text.NumberFormat;
import java.util.ArrayList;
import java.util.Objects;

public class ATM {
    private JFrame frame;

    private static String s = new String("");
    private static String pin = new String("");
    private static String withdraw = new String("");
    private static String deposit = new String("");
    private static String receiver = new String("");
    private static String transfer = new String("");

    private static ArrayList<BankAccount> accounts;
    private static BankAccount currentUser;
    private static BankAccount receiverAccount;

    private boolean isStart = true, isPin = false, isLogin = false, isReceiver = false, isTransfer = false;
    private boolean isOption1 = false, isOption2 = false, isOption3 = false, isOption4 = false;


    public ATM(ArrayList<BankAccount> bankAccounts) {
        accounts = bankAccounts;
        init();
    }

    private void init() {
        frame = new JFrame();
        frame.setBounds(100, 100, 580, 550);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        JLabel sTrainPlanner = new JLabel("Java ATM");
        sTrainPlanner.setHorizontalAlignment(SwingConstants.CENTER);
        sTrainPlanner.setBounds(120, 60, 280, 20);
        frame.getContentPane().add(sTrainPlanner);

        JLabel topImage = new JLabel("");
        topImage.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/woori.png"))));
        topImage.setBounds(10, 10, 500, 50);
        frame.getContentPane().add(topImage);

        JTextPane tPane = new JTextPane();
        tPane.setText("Please, insert your card and press ENTER...");
        tPane.setEditable(false);
        tPane.setBounds(140, 80, 270, 160);
        frame.getContentPane().add(tPane);


        JButton optionButton1 = new JButton("OPTION 1");
        optionButton1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isLogin) {
                    isOption1 = true;

                    String name = currentUser.getBankUser().getName();
                    NumberFormat nf = new DecimalFormat("0.00");
                    String balance = nf.format(currentUser.getBalance());

                    s = "User: " + name + "\n";
                    s += "Balance: " + balance + "\n";
                    s += "Press ENTER...";
                    tPane.setText(s);
                }
            }
        });

        optionButton1.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/arr.png"))));
        optionButton1.setBackground(UIManager.getColor("Button.background"));
        optionButton1.setBounds(10, 80, 130, 40);
        frame.getContentPane().add(optionButton1);

        JButton optionButton2 = new JButton("OPTION 2");
        optionButton2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isLogin) {
                    isOption2 = true;

                    s = "Enter Withdrawal Amount: ";
                    tPane.setText(s);
                }
            }
        });
        optionButton2.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/arr.png"))));
        optionButton2.setBackground(SystemColor.window);
        optionButton2.setBounds(10, 120, 130, 40);
        frame.getContentPane().add(optionButton2);

        JButton optionButton3 = new JButton("OPTION 3");
        optionButton3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isLogin) {
                    isOption3 = true;

                    s = "Enter Deposit Amount: ";
                    tPane.setText(s);
                }
            }
        });
        optionButton3.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/arr.png"))));
        optionButton3.setBackground(SystemColor.window);
        optionButton3.setBounds(10, 160, 130, 40);
        frame.getContentPane().add(optionButton3);

        JButton optionButton4 = new JButton("OPTION 4");
        optionButton4.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isLogin) {
                    isOption4 = true;
                    isReceiver = true;
                    s = "Enter Account Number (Receiver): ";
                    tPane.setText(s);
                }
            }
        });
        optionButton4.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/arr.png"))));
        optionButton4.setBackground(SystemColor.window);
        optionButton4.setBounds(10, 200, 130, 40);
        frame.getContentPane().add(optionButton4);

        JButton engButton = new JButton("ENGLISH");
        engButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            }
        });
        engButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/eng.png"))));
        engButton.setBackground(SystemColor.window);
        engButton.setBounds(410, 80, 160, 40);
        frame.getContentPane().add(engButton);

        JButton korButton = new JButton("KOREAN");
        korButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            }
        });
        korButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/kor.png"))));
        korButton.setBackground(SystemColor.window);
        korButton.setBounds(410, 120, 160, 40);
        frame.getContentPane().add(korButton);

        JButton cancelButton = new JButton("CANCEL");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {


                s = "Cancelled!\n" + "New plan:\n" + "Choose transport (from left menu): ";
                tPane.setText(s);
            }
        });
        cancelButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/cancel.png"))));
        cancelButton.setBackground(SystemColor.window);
        cancelButton.setBounds(410, 240, 160, 70);
        frame.getContentPane().add(cancelButton);

        JButton clearButton = new JButton("CLEAR");
        clearButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    s = s.substring(0, s.length() - pin.length());
                    tPane.setText(s);
                    pin = "";
                }
            }
        });
        clearButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/clear.png"))));
        clearButton.setBackground(SystemColor.window);
        clearButton.setBounds(410, 310, 160, 70);
        frame.getContentPane().add(clearButton);

        JButton enterButton = new JButton("ENTER");
        enterButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/enter.png"))));
        enterButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isStart) {
                    currentUser = null;
                    s = "PIN: ";
                    tPane.setText(s);

                    isStart = false;
                    isPin = true;
                } else if (isPin) {
                    for (BankAccount acc : accounts) {
                        if (acc.checkPIN(Integer.parseInt(pin))) {
                            currentUser = acc;
                            break;
                        }
                    }

                    if (currentUser != null) {
                        s = "Welcome " + currentUser.getBankUser().getName() + "\n";
                        s += "Please choose options:\n";
                        s += "OPTION 1: Balance Checking\n";
                        s += "OPTION 2: Withdrawing money\n";
                        s += "OPTION 3: Deposit\n";
                        s += "OPTION 4: Transfer\n";
                        tPane.setText(s);

                        pin = "";
                        isPin = false;
                        isLogin = true;
                    } else {
                        pin = "";
                        s = "Wrong pin! Try Again:\n";
                        s += "PIN: ";
                        tPane.setText(s);
                    }
                } else if (isOption1) {
                    s = "Thank you for banking with us!\n";
                    s += "Press ENTER...";
                    tPane.setText(s);

                    isOption1 = false;
                    isStart = true;
                } else if (isOption2 && !withdraw.equals("")) {
                    if (currentUser.withdraw(Double.parseDouble(withdraw))) {
                        String name = currentUser.getBankUser().getName();
                        NumberFormat nf = new DecimalFormat("0.00");
                        String balance = nf.format(currentUser.getBalance());
                        String withdrawString = nf.format(Double.parseDouble(withdraw));

                        s = "Success :)\n";
                        s += "User: " + name + "\n";
                        s += "Withdrawal Amount: " + withdrawString + "\n";
                        s += "Current Balance: " + balance + "\n";

                    } else {
                        s = "Not enough money!\n";
                    }
                    s += "Press ENTER...";
                    tPane.setText(s);

                    withdraw = "";
                    isOption2 = false;
                    isStart = true;
                } else if (isOption3 && !deposit.equals("")) {
                    currentUser.deposit(Double.parseDouble(deposit));
                    String name = currentUser.getBankUser().getName();
                    NumberFormat nf = new DecimalFormat("0.00");
                    String balance = nf.format(currentUser.getBalance());
                    String depositSting = nf.format(Double.parseDouble(deposit));


                    s = "Success :)\n";
                    s += "User: " + name + "\n";
                    s += "Deposit Amount: " + depositSting + "\n";
                    s += "Current Balance: " + balance + "\n";
                    s += "Press ENTER...";
                    tPane.setText(s);

                    deposit = "";
                    isOption3 = false;
                    isStart = true;
                } else if (isOption4 && isReceiver && !receiver.equals("")) {
                    boolean isExist = false;
                    for (BankAccount acc : accounts) {
                        if (acc.getBankNumber().equals(receiver)) {
                            isExist = true;
                            receiverAccount = acc;
                            break;
                        }
                    }

                    if (isExist) {

                        s = "Transfer Account: " + receiverAccount.getBankUser().getName() + "\n";
                        s += "Enter Transfer Amount: ";
                        tPane.setText(s);

                        isReceiver = false;
                        isTransfer = true;
                    } else {
                        s = "You entered the wrong account number!\n";
                        s += "Press ENTER...";
                        tPane.setText(s);

                        receiver = "";
                        isOption4 = false;
                        isReceiver = false;
                        isStart = true;
                    }
                } else if (isOption4 && isTransfer) {
                    if (currentUser.transfer(receiverAccount, Double.parseDouble(transfer))) {
                        NumberFormat nf = new DecimalFormat("0.00");
                        String balance = nf.format(currentUser.getBalance());
                        String transferString = nf.format(Double.parseDouble(transfer));

                        s = "Transfer Amount: " + transferString + "\n";
                        s += "Current Balance: " + balance + "\n";

                    } else {
                        s = "Not enough money!\n";
                    }
                    s += "Press ENTER...";
                    tPane.setText(s);

                    transfer = "";
                    isOption4 = false;
                    isTransfer = false;
                    isStart = true;
                }
            }
        });
        enterButton.setBackground(SystemColor.window);
        enterButton.setBounds(410, 380, 160, 70);
        frame.getContentPane().add(enterButton);

        JButton numberButton_1 = new JButton("");
        numberButton_1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "1";
                    s += "1";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "1";
                    s += "1";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "1";
                    s += "1";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "1";
                    s += "1";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "1";
                    s += "1";
                    tPane.setText(s);
                }

            }
        });
        numberButton_1.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/1.png"))));
        numberButton_1.setBackground(SystemColor.window);
        numberButton_1.setBounds(140, 240, 90, 70);
        frame.getContentPane().add(numberButton_1);

        JButton numberButton_2 = new JButton("");
        numberButton_2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "2";
                    s += "2";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "2";
                    s += "2";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "2";
                    s += "2";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "2";
                    s += "2";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "2";
                    s += "2";
                    tPane.setText(s);
                }
            }
        });
        numberButton_2.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/2.png"))));
        numberButton_2.setBackground(SystemColor.window);
        numberButton_2.setBounds(230, 240, 90, 70);
        frame.getContentPane().add(numberButton_2);

        JButton numberButton_3 = new JButton("");
        numberButton_3.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/3.png"))));
        numberButton_3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "3";
                    s += "3";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "3";
                    s += "3";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "3";
                    s += "3";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "3";
                    s += "3";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "3";
                    s += "3";
                    tPane.setText(s);
                }
            }
        });
        numberButton_3.setBackground(SystemColor.window);
        numberButton_3.setBounds(320, 240, 90, 70);
        frame.getContentPane().add(numberButton_3);

        JButton numberButton_4 = new JButton("");
        numberButton_4.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "4";
                    s += "4";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "4";
                    s += "4";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "4";
                    s += "4";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "4";
                    s += "4";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "4";
                    s += "4";
                    tPane.setText(s);
                }
            }
        });
        numberButton_4.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/4.png"))));
        numberButton_4.setBackground(SystemColor.window);
        numberButton_4.setBounds(140, 310, 90, 70);
        frame.getContentPane().add(numberButton_4);

        JButton numberButton_5 = new JButton("");
        numberButton_5.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "5";
                    s += "5";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "5";
                    s += "5";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "5";
                    s += "5";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "5";
                    s += "5";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "5";
                    s += "5";
                    tPane.setText(s);
                }
            }
        });
        numberButton_5.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/5.png"))));
        numberButton_5.setBackground(SystemColor.window);
        numberButton_5.setBounds(230, 310, 90, 70);
        frame.getContentPane().add(numberButton_5);

        JButton numberButton_6 = new JButton("");
        numberButton_6.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "6";
                    s += "6";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "6";
                    s += "6";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "6";
                    s += "6";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "6";
                    s += "6";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "6";
                    s += "6";
                    tPane.setText(s);
                }
            }
        });
        numberButton_6.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/6.png"))));
        numberButton_6.setBackground(SystemColor.window);
        numberButton_6.setBounds(320, 310, 90, 70);
        frame.getContentPane().add(numberButton_6);


        JButton numberButton_7 = new JButton("");
        numberButton_7.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "7";
                    s += "7";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "7";
                    s += "7";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "7";
                    s += "7";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "7";
                    s += "7";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "7";
                    s += "7";
                    tPane.setText(s);
                }
            }
        });
        numberButton_7.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/7.png"))));
        numberButton_7.setBackground(SystemColor.window);
        numberButton_7.setBounds(140, 380, 90, 70);
        frame.getContentPane().add(numberButton_7);

        JButton numberButton_8 = new JButton("");
        numberButton_8.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "8";
                    s += "8";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "8";
                    s += "8";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "8";
                    s += "8";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "8";
                    s += "8";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "8";
                    s += "8";
                    tPane.setText(s);
                }
            }
        });
        numberButton_8.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/8.png"))));
        numberButton_8.setBackground(SystemColor.window);
        numberButton_8.setBounds(230, 380, 90, 70);
        frame.getContentPane().add(numberButton_8);

        JButton numberButton_9 = new JButton("");
        numberButton_9.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "9";
                    s += "9";
                    tPane.setText(s);
                } else if (isOption2) {
                    withdraw += "9";
                    s += "9";
                    tPane.setText(s);
                } else if (isOption3) {
                    deposit += "9";
                    s += "9";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "9";
                    s += "9";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer) {
                    transfer += "9";
                    s += "9";
                    tPane.setText(s);
                }
            }
        });
        numberButton_9.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/9.png"))));
        numberButton_9.setBackground(SystemColor.window);
        numberButton_9.setBounds(320, 380, 90, 70);
        frame.getContentPane().add(numberButton_9);

        JButton numberButton_0 = new JButton("");
        numberButton_0.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/0.png"))));
        numberButton_0.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                if (isPin) {
                    pin += "0";
                    s += "0";
                    tPane.setText(s);
                } else if (isOption2 && !withdraw.equals("")) {
                    withdraw += "0";
                    s += "0";
                    tPane.setText(s);
                } else if (isOption3 && !deposit.equals("")) {
                    deposit += "0";
                    s += "0";
                    tPane.setText(s);
                } else if (isOption4 && isReceiver) {
                    receiver += "0";
                    s += "0";
                    tPane.setText(s);
                } else if (isOption4 && isTransfer && !transfer.equals("")) {
                    transfer += "0";
                    s += "0";
                    tPane.setText(s);
                }
            }
        });
        numberButton_0.setBackground(SystemColor.window);
        numberButton_0.setBounds(230, 450, 90, 70);
        frame.getContentPane().add(numberButton_0);

    }

    public static void main(String[] args) {
        ArrayList<BankAccount> bankAccounts = new ArrayList<>();
        User user1 = new User("Firuz");
        User user2 = new User("John");
        User user3 = new User("Eldor");

        bankAccounts.add(new BankAccount("200100237898", 1234, 500000.0, user1));
        bankAccounts.add(new BankAccount("110000022033", 4321, 700000.0, user2));
        bankAccounts.add(new BankAccount("111111111111", 2222, 800000.0, user3));
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                ATM atm = new ATM(bankAccounts);
                atm.frame.setVisible(true);
            }
        });
    }
}
