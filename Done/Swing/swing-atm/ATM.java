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

    private static String s = new String(""); // 모든 문자열 출력시 활용되는 변수
    private static String pin = new String(""); // 핀 입력 모드에서 활용
    private static String withdraw = new String(""); // 출금 모드에서 황룔
    private static String deposit = new String(""); // 입금 모드에서 활용
    private static String receiver = new String(""); // 송금 모드에서 송금 계좌 입력시 활용
    private static String transfer = new String(""); // 송금 모드에서 솜금 금액 입력시 활용

    private static ArrayList<BankAccount> accounts; // 매개변수로 넘겨받은 계좌 정보를 저장할 리스트
    private static BankAccount currentUser; // 로그인한 현재 유저의 정보를 담을 객체
    private static BankAccount receiverAccount; // 송금받을 유저의 정보를 담을 객체

    // 각각의 스테이지 모드에 대한 boolean 변수들
    private boolean isStart = true, isPin = false, isLogin = false, isReceiver = false, isTransfer = false, isDone = false;
    private boolean isOption1 = false, isOption2 = false, isOption3 = false, isOption4 = false;

    // 생성자
    public ATM(ArrayList<BankAccount> bankAccounts) {
        accounts = bankAccounts;
        init();
    }

    private void init() {
        //  J 프레임 생성
        frame = new JFrame();
        frame.setBounds(100, 100, 580, 550);
        frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        frame.getContentPane().setLayout(null);

        // 레이블
        JLabel skkuATM = new JLabel("SKKU ATM");
        skkuATM.setHorizontalAlignment(SwingConstants.CENTER);
        skkuATM.setBounds(120, 60, 280, 20);
        frame.getContentPane().add(skkuATM);

        // 은행 이미지
        JLabel topImage = new JLabel("");
        topImage.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/woori.png"))));
        topImage.setBounds(10, 10, 500, 50);
        frame.getContentPane().add(topImage);

        // 텍스트 페인 -> 기능별 텍스트 출력에 사용
        JTextPane tPane = new JTextPane();
        tPane.setText("Please, insert your card and press ENTER...");
        tPane.setEditable(false);
        tPane.setBounds(140, 80, 270, 160);
        frame.getContentPane().add(tPane);

        // 옵션 1 버튼
        JButton optionButton1 = new JButton("OPTION 1");
        optionButton1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 로그인 이후 옵션 1 버튼을 한번 누르면 이후에 다른 옵션 버튼을 눌러도 동작하지 않도록 조건 분기
                if (isLogin && !isOption1 && !isOption2 && !isOption3 && !isOption4) {
                    isOption1 = true;

                    String name = currentUser.getBankUser().getName();
                    // 자바 넘버 포맷 클래스 활용하여 어떠한 숫자도 소숫점 둘째자리까지 출력하도록 포맷팅 해주는 클래스
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

        // 옵션 2 버튼
        JButton optionButton2 = new JButton("OPTION 2");
        optionButton2.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 로그인 이후 옵션 2 버튼을 한번 누르면 이후에 다른 옵션 버튼을 눌러도 동작하지 않도록 조건 분기
                if (isLogin && !isOption1 && !isOption2 && !isOption3 && !isOption4) {
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

        // 옵션 3 버튼
        JButton optionButton3 = new JButton("OPTION 3");
        optionButton3.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 로그인 이후 옵션 3 버튼을 한번 누르면 이후에 다른 옵션 버튼을 눌러도 동작하지 않도록 조건 분기
                if (isLogin && !isOption1 && !isOption2 && !isOption3 && !isOption4) {
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

        // 옵션 4 버튼
        JButton optionButton4 = new JButton("OPTION 4");
        optionButton4.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 로그인 이후 옵션 4 버튼을 한번 누르면 이후에 다른 옵션 버튼을 눌러도 동작하지 않도록 조건 분기
                if (isLogin && !isOption1 && !isOption2 && !isOption3 && !isOption4) {
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

        // ENGLISH 버튼. 기능 없음
        JButton engButton = new JButton("ENGLISH");
        engButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            }
        });
        engButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/eng.png"))));
        engButton.setBackground(SystemColor.window);
        engButton.setBounds(410, 80, 160, 40);
        frame.getContentPane().add(engButton);

        // KOREAN 버튼. 기능 없음
        JButton korButton = new JButton("KOREAN");
        korButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
            }
        });
        korButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/kor.png"))));
        korButton.setBackground(SystemColor.window);
        korButton.setBounds(410, 120, 160, 40);
        frame.getContentPane().add(korButton);

        // CANCEL 버튼. 어떠한 상황에서도 취소
        JButton cancelButton = new JButton("CANCEL");
        cancelButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                s = "Process is canceled by user! Please press ENTER...\n";
                tPane.setText(s);

                // 모든 변수 초기화 후 최초 실행 상태로 돌아감.
                pin = "";
                withdraw = "";
                deposit = "";
                transfer = "";

                isLogin = false;
                isOption1 = false;
                isOption2 = false;
                isOption3 = false;
                isOption4 = false;
                isReceiver = false;
                isTransfer = false;
                isStart = true;
            }
        });
        cancelButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/cancel.png"))));
        cancelButton.setBackground(SystemColor.window);
        cancelButton.setBounds(410, 240, 160, 70);
        frame.getContentPane().add(cancelButton);

        // CLEAR 버튼. 비밀번호를 입력할 때만 누를 수 있음
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

        // ENTER 버튼
        JButton enterButton = new JButton("ENTER");
        enterButton.setIcon(new ImageIcon(Objects.requireNonNull(ATM.class.getResource("/assets/enter.png"))));
        enterButton.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 최초 실행 후 엔터
                if (isStart) {
                    s = "PIN: ";
                    tPane.setText(s);

                    // 시작 모드 종료
                    isStart = false;
                    // 핀 입력 모드 시작
                    isPin = true;
                } else if (isPin) { // 핀 입력 모드
                    // 모든 계좌에서 핀번호와 일치하는 유저가 있는지 검사
                    for (BankAccount acc : accounts) {
                        // 있으면 현재 유저를 해당 유저로 갱신하고 반복문 탈출
                        if (acc.checkPIN(Integer.parseInt(pin))) {
                            currentUser = acc;
                            break;
                        }
                    }

                    // 핀 번호가 일치하는 유저가 있을 때
                    if (currentUser != null) {
                        s = "Welcome " + currentUser.getBankUser().getName() + "\n";
                        s += "Please choose options:\n";
                        s += "OPTION 1: Balance Checking\n";
                        s += "OPTION 2: Withdrawing money\n";
                        s += "OPTION 3: Deposit\n";
                        s += "OPTION 4: Transfer\n";
                        tPane.setText(s);

                        // 핀 입력 모드 종료
                        isPin = false;
                        // 로그인 모드 시작
                        isLogin = true;
                    } else { // 입력한 핀과 일치하는 계좌가 없을 때
                        pin = "";
                        s = "Wrong pin! Try Again:\n";
                        s += "PIN: ";
                        tPane.setText(s);
                    }
                } else if (isOption1) { // 옵션 1 버튼이 눌러진 상태에서 엔터를 눌렀을 때
                    // 완료 모드 시작
                    isDone = true;
                } else if (isOption2 && !withdraw.equals("")) { // 옵션 2 버튼이 눌러진 상태 + 출금할 금액이 입력된 경우
                    if (currentUser.withdraw(Double.parseDouble(withdraw))) { // 잔액이 충분한지 확인 후, 충분하다면 즉시 출금 진행
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

                    // 출금 모드 종료
                    isOption2 = false;
                    // 완료 모드 시작
                    isDone = true;
                } else if (isOption3 && !deposit.equals("")) { // 옵션 3 버튼이 눌러진 상태 + 입금할 금액이 입력된 경우
                    currentUser.deposit(Double.parseDouble(deposit)); // 즉시 입금 진행
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

                    // 입금 모드 종료
                    isOption3 = false;
                    // 완료 모드 시작
                    isDone = true;
                } else if (isOption4 && isReceiver && !receiver.equals("")) { // 옵션 4 버튼이 눌러진 상태 + 송금할 계좌가 입력된 경우
                    // 송금할 계좌가 존재하는지 체크할 변수
                    boolean isExist = false;
                    // 모든 계좌를 탐색
                    for (BankAccount acc : accounts) {
                        // 송금할 계좌가 존재하면
                        if (acc.getBankNumber().equals(receiver)) {
                            // 존재함으로 표시하고, 송금 받을 계좌 갱신 및 반복문 탈출
                            isExist = true;
                            receiverAccount = acc;
                            break;
                        }
                    }

                    // 송금받을 계좌가 존재하면 금앱을 입력받음.
                    if (isExist) {
                        s = "Transfer Account: " + receiverAccount.getBankUser().getName() + "\n";
                        s += "Enter Transfer Amount: ";
                        tPane.setText(s);

                        // 송금 계좌 모드 종료
                        isReceiver = false;
                        // 송금 금액 모드 시작
                        isTransfer = true;
                    } else { // 계좌가 존재하지 않을 때
                        s = "You entered the wrong account number!\n";
                        s += "Press ENTER...";
                        tPane.setText(s);

                        // 송금 모드 전체 종료
                        isOption4 = false;
                        // 완료 모드 시작
                        isDone = true;
                    }
                } else if (isOption4 && isTransfer) { // 옵션 4 버튼이 눌러진 상태 + 송금 금액이 입력된 경우
                    if (currentUser.transfer(receiverAccount, Double.parseDouble(transfer))) { // 송금 가능한지 잔액 조회 후 이상 없으면 즉시 송금 실행
                        NumberFormat nf = new DecimalFormat("0.00");
                        String balance = nf.format(currentUser.getBalance());
                        String transferString = nf.format(Double.parseDouble(transfer));

                        s = "Transfer Amount: " + transferString + "\n";
                        s += "Current Balance: " + balance + "\n";

                    } else { // 잔액이 부족할 때
                        s = "Not enough money!\n";
                    }
                    s += "Press ENTER...";
                    tPane.setText(s);

                    // 송금 모드 전체 종료
                    isOption4 = false;
                    // 완료 모드 시작
                    isDone = true;
                } else if (isDone) { // 완료 모드
                    s = "Thank you for banking with us!\n";
                    s += "Press ENTER...";
                    tPane.setText(s);

                    // 모든 변수 최초 실행시와 같은 상태로 초기화
                    pin = "";
                    withdraw = "";
                    deposit = "";
                    transfer = "";

                    isLogin = false;
                    isOption1 = false;
                    isOption2 = false;
                    isOption3 = false;
                    isOption4 = false;
                    isReceiver = false;
                    isTransfer = false;
                    isDone = false;
                    // 시작 모드 시작
                    isStart = true;
                }
            }
        });
        enterButton.setBackground(SystemColor.window);
        enterButton.setBounds(410, 380, 160, 70);
        frame.getContentPane().add(enterButton);

        // 숫자 버튼
        JButton numberButton_1 = new JButton("");
        numberButton_1.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                // 각 모드에 맞는 변수에 핀 입력.
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

    // 메인 함수
    public static void main(String[] args) {
        ArrayList<BankAccount> bankAccounts = new ArrayList<>();
        User user1 = new User("Firuz");
        User user2 = new User("John");
        User user3 = new User("Eldor");

        bankAccounts.add(new BankAccount("200100237898", 1234, 500000.0, user1));
        bankAccounts.add(new BankAccount("110000022033", 4321, 700000.0, user2));
        bankAccounts.add(new BankAccount("111111111111", 2222, 900000.0, user3));
        EventQueue.invokeLater(new Runnable() {
            public void run() {
                // 생성한 계좌 리스트를 매개변수로 ATM 클래스 생성
                ATM atm = new ATM(bankAccounts);
                atm.frame.setVisible(true);
            }
        });
    }
}
