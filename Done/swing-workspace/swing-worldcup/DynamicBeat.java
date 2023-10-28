import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.*;
import java.util.List;

import javax.swing.*;


public class DynamicBeat extends JFrame {
    // 변수 선언 부분
    private Image screenImage;
    private Graphics screenGraphic;

    // swing 컴포넌트 이미지 아이콘 및 이미지 초기화
    private Image background = new ImageIcon(Main.class.getResource("image/game_title.jpg")).getImage();
    private JLabel menuBar = new JLabel(new ImageIcon(Main.class.getResource("image/menuBar.png")));

    private Icon exitButtonEnteredImage = new ImageIcon(Main.class.getResource("image/exitButtonEntered.png"));
    private ImageIcon exitButtonBasicImage = new ImageIcon(Main.class.getResource("image/exitButtonBasic.png"));
    private ImageIcon startButtonEnteredImage = new ImageIcon(Main.class.getResource("image/startButtonEntered.png"));
    private ImageIcon startButtonBasicImage = new ImageIcon(Main.class.getResource("image/startButtonBasic.png"));
    private ImageIcon quitButtonEnteredImage = new ImageIcon(Main.class.getResource("image/quitButtonEntered.png"));
    private ImageIcon quitButtonBasicImage = new ImageIcon(Main.class.getResource("image/quitButtonBasic.png"));
    private ImageIcon leftButtonEnteredImage = new ImageIcon(Main.class.getResource("image/leftButtonEntered.png"));
    private ImageIcon leftButtonBasicImage = new ImageIcon(Main.class.getResource("image/leftButtonBasic.png"));
    private ImageIcon rightButtonEnteredImage = new ImageIcon(Main.class.getResource("image/rightButtonEntered.png"));
    private ImageIcon rightButtonBasicImage = new ImageIcon(Main.class.getResource("image/rightButtonBasic.png"));
    private ImageIcon normalButtonBasicImage = new ImageIcon(Main.class.getResource("image/normalButtonBasic.png"));
    private ImageIcon normalButtonEnteredImage = new ImageIcon(Main.class.getResource("image/normalButtonEntered.png"));
    private ImageIcon hardButtonBasicImage = new ImageIcon(Main.class.getResource("image/hardButtonBasic.png"));
    private ImageIcon hardButtonEnteredImage = new ImageIcon(Main.class.getResource("image/hardButtonEntered.png"));
    private ImageIcon backButtonBasicImage = new ImageIcon(Main.class.getResource("image/backButtonBasic.png"));
    private ImageIcon backButtonEnteredImage = new ImageIcon(Main.class.getResource("image/backButtonEntered.png"));


    // 이미지들 아이콘에 저장
    private JButton exitButton = new JButton(exitButtonBasicImage);
    private JButton startButton = new JButton(startButtonBasicImage);
    private JButton quitButton = new JButton(quitButtonBasicImage);
    private JButton leftButton = new JButton(leftButtonBasicImage);
    private JButton rightButton = new JButton(rightButtonBasicImage);
    private JButton normalButton = new JButton(normalButtonBasicImage);
    private JButton hardButton = new JButton(hardButtonBasicImage);
    private JButton backButton = new JButton(backButtonBasicImage);

    // 이미지 변수 설정 초기화
    private int mouseX, mouseY;

    // 메인화면 이동시 트루
    private boolean isMainScreen = false;
    // 게임 화면 넘어왔는지 변수
    private boolean isGameScreen = false;

    //트랙 클래스이용 변수들을 담을 배열
    ArrayList<Track> trackList = new ArrayList<Track>();

    private Image selectedImage;
    private int nowSelected = 0;

    // 게임변수는 프로젝트 전체에 가능
    public static Game game;


    private JButton leftItemButton = new JButton("Left");
    private JButton rightItemButton = new JButton("right");
    private JLabel winner = new JLabel();
    private JLabel statusText = new JLabel("");

    // 이상형 월드컵 전용 변수. 난이도, 이미지파일 경로 및 버튼 등
    private String difficulty;
    private List<String> sc;
    private List<String> wwe;
    private List<String> kof;

    /*
    여기 부분 수정시 16강, 32강, 64강 ... 진행 가능
    ROUND -> 몇강인지 나타내는 정적 변수

    scImages, wweImages, kofImages 는 이미지 파일 이름들. ROUND 변경시 최소 ROUND개 이상의 이미지가 있어야 함.
     */
    private static final int ROUND = 16;
    private String[] scImages = {"sc1.png", "sc2.png", "sc3.png", "sc4.png", "sc5.png", "sc6.png", "sc7.png", "sc8.png", "sc9.png"
            , "sc10.png", "sc11.png", "sc12.png", "sc13.png", "sc14.png", "sc15.png", "sc16.png", "sc17.png", "sc18.png", "sc19.png", "sc20.png", "sc21.png", "sc22.png", "sc23.png", "sc24.png", "sc25.png"
            , "sc26.png", "sc27.png", "sc28.png", "sc29.png", "sc30.png", "sc31.png", "sc32.png"};
    private String[] wweImages = {"wwe1.png", "wwe2.png", "wwe3.png", "wwe4.png", "wwe5.png", "wwe6.png", "wwe7.png", "wwe8.png", "wwe9.png"
            , "wwe10.png", "wwe11.png", "wwe12.png", "wwe13.png", "wwe14.png", "wwe15.png", "wwe16.png"};
    private String[] kofImages = {"kof1.png", "kof2.png", "kof3.png", "kof4.png", "kof5.png", "kof6.png", "kof7.png", "kof8.png", "kof9.png"
            , "kof10.png", "kof11.png", "kof12.png", "kof13.png", "kof14.png", "kof15.png", "kof16.png"};

    // 생존한 항목 관리용 큐
    private Queue<Icon> items = new LinkedList<>();

    private Music selectedMusic; //함수화를 통해서 코드가 간결하게 만듬
    private Music flowerdance = new Music("flowerdance.mp3", true);

    public DynamicBeat() {
        // JFrame 초기화 및 세팅
        setUndecorated(true);
        setTitle("Dynamic Beat");
        setSize(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT);
        setResizable(false);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setBackground(new Color(0, 0, 0, 0));
        setLayout(null);

        flowerdance.start();

        // 파일 순서대로 넣기 변수 초기화 트랙리스트에 넣어줌
        trackList.add(new Track("Star Start Image.png",
                "Star Game Image.png", "sc", "Terranteam Selected.mp3", "Terranteam.mp3"));
        trackList.add(new Track("Wwe Start Image.png",
                "Wwe Game Image.png", "wwe", "AcrosstheNation Selected.mp3", "AcrosstheNation.mp3"));
        trackList.add(new Track("Kof Start Image.png",
                "Kof Game Image.png", "kof", "Esaka Selected.mp3", "Esaka.mp3"));

        // 종료 버튼
        exitButton.setBounds(1245, 0, 30, 30);
        exitButton.setBorderPainted(false);
        exitButton.setContentAreaFilled(false);
        exitButton.setFocusPainted(false);
        exitButton.addMouseListener(new MouseAdapter() {
            // 마우스 올렸을 때
            @Override
            public void mouseEntered(MouseEvent e) {
                // 이미지 변경, 효과음 재생 및 커서 색상 변경
                exitButton.setIcon(exitButtonEnteredImage);
                exitButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            // 마우스 올렸다 치웠을 때
            @Override
            public void mouseExited(MouseEvent e) {
                // 이미지 변경 및 커서 색상 변경
                exitButton.setIcon(exitButtonBasicImage);
                exitButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            // 마우스 클릭시
            @Override
            public void mousePressed(MouseEvent e) {
                // 효과음 재생 및 스레드 1초간 멈춤
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                try {
                    Thread.sleep(1000);

                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });
        // 종료 버튼을 JFrame에 추가
        add(exitButton);

        // 시작 버튼
        startButton.setBounds(40, 200, 400, 100);
        startButton.setBorderPainted(false);
        startButton.setContentAreaFilled(false);
        startButton.setFocusPainted(false);
        startButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                startButton.setIcon(startButtonEnteredImage);
                startButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                startButton.setIcon(startButtonBasicImage);
                startButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 메인 함수로 들어간다
                enterMain();
            }
        });
        add(startButton);


        // 프로그램 종료 버튼
        quitButton.setBounds(40, 330, 400, 100);
        quitButton.setBorderPainted(false);
        quitButton.setContentAreaFilled(false);
        quitButton.setFocusPainted(false);
        quitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                quitButton.setIcon(quitButtonEnteredImage);
                quitButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                quitButton.setIcon(quitButtonBasicImage);
                quitButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                try {
                    Thread.sleep(1000);

                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });
        add(quitButton);

        // 왼쪽 버튼
        // 처음엔 보이지 않도록 설정
        leftButton.setVisible(false);
        leftButton.setBounds(140, 310, 60, 60);
        leftButton.setBorderPainted(false);
        leftButton.setContentAreaFilled(false);
        leftButton.setFocusPainted(false);
        leftButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                leftButton.setIcon(leftButtonEnteredImage);
                leftButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                leftButton.setIcon(leftButtonBasicImage);
                leftButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 왼쪽 버튼 클릭 이벤트
                selectLeft();
            }
        });
        add(leftButton);

        // 오른쪽 버튼
        rightButton.setVisible(false);
        rightButton.setBounds(1080, 310, 60, 60);
        rightButton.setBorderPainted(false);
        rightButton.setContentAreaFilled(false);
        rightButton.setFocusPainted(false);
        rightButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                rightButton.setIcon(rightButtonEnteredImage);
                rightButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                rightButton.setIcon(rightButtonBasicImage);
                rightButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 오른쪽 버튼 클릭 이벤트
                selectRight();
            }
        });
        add(rightButton);

        // 노멀 난이도 버튼
        // 처음엔 보이지 않도록 설정
        normalButton.setVisible(false);
        normalButton.setBounds(375, 580, 250, 67);
        normalButton.setBorderPainted(false);
        normalButton.setContentAreaFilled(false);
        normalButton.setFocusPainted(false);
        normalButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                normalButton.setIcon(normalButtonEnteredImage);
                normalButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                normalButton.setIcon(normalButtonBasicImage);
                normalButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 노멀 난이도 버튼 이벤트
                gameStart("Normal");

            }
        });
        add(normalButton);

        // 하드 난이도 버튼
        hardButton.setVisible(false);
        hardButton.setBounds(655, 580, 250, 67);
        hardButton.setBorderPainted(false);
        hardButton.setContentAreaFilled(false);
        hardButton.setFocusPainted(false);
        hardButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                hardButton.setIcon(hardButtonEnteredImage);
                hardButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                hardButton.setIcon(hardButtonBasicImage);
                hardButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 하드 난이도 버튼 이벤트
                gameStart("Hard");
            }
        });
        add(hardButton);

        // 뒤로가기 버튼
        backButton.setVisible(false);
        backButton.setBounds(20, 50, 60, 60);
        backButton.setBorderPainted(false);
        backButton.setContentAreaFilled(false);
        backButton.setFocusPainted(false);
        backButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                backButton.setIcon(backButtonEnteredImage);
                backButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
                Music buttonEnteredMusic = new Music("buttonEnteredMusic.mp3", false);
                buttonEnteredMusic.start();
            }

            @Override
            public void mouseExited(MouseEvent e) {
                backButton.setIcon(backButtonBasicImage);
                backButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                leftItemButton.setVisible(false);
                rightItemButton.setVisible(false);
                winner.setVisible(false);
                statusText.setVisible(false);
                Music buttonEnteredMusic = new Music("buttonPressedMusic.mp3", false);
                buttonEnteredMusic.start();
                // 뒤로가기 버튼 이벤트
                backMain();
            }
        });
        add(backButton);

        // 메뉴바
        menuBar.setBounds(0, 0, 1280, 30);
        // 람다 리스너 이벤트
        menuBar.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouseX = e.getX();
                mouseY = e.getY();

            }
        });
        // 람다 모션 리스너 이벤트
        menuBar.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                int x = e.getXOnScreen();
                int y = e.getYOnScreen();
                setLocation(x - mouseX, y - mouseY);
            }

        });
        add(menuBar);


        // 왼쪽 아이템 버튼
        leftItemButton.setVisible(false);
        leftItemButton.setBounds(70, 100, 500, 500);
        leftItemButton.setBorderPainted(false);
        leftItemButton.setContentAreaFilled(false);
        leftItemButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                //왼쪽 아이템 버튼 이벤트
                selectLeftItem();
            }
        });
        add(leftItemButton);

        // 오른쪽 아이템 버튼
        rightItemButton.setVisible(false);
        rightItemButton.setBounds(710, 100, 500, 500);
        rightItemButton.setBorderPainted(false);
        rightItemButton.setContentAreaFilled(false);
        rightItemButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                // 오른쪽 아이템 버튼 이벤트
                selectRightItem();

            }
        });
        add(rightItemButton);

        // 우승 이미지 레이블
        winner.setVisible(false);
        winner.setBounds(390, 100, 500, 500);
        add(winner);

        // 상태 텍스트 레이블
        statusText.setVisible(false);
        statusText.setBounds(390, 30, 500, 50);
        statusText.setVerticalAlignment(SwingConstants.CENTER);
        statusText.setHorizontalAlignment(SwingConstants.CENTER);
        statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
        statusText.setForeground(Color.white);
        add(statusText);
    }

    // 왼쪽 아이템 골랐을 때
    private void selectLeftItem() {
        // 큐의 사이즈를 확인
        switch (items.size()) {
            // 큐에 아이템이 1개이면 우슨
            case 1:
                statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                // 우승 상태 텍스트 전환 후
                statusText.setText("WINNER is");
                // 우승한 항목 Visible
                winner.setIcon(leftItemButton.getIcon());
                getWinner();
                return;
            // 큐에 아이템이 2개이면 결승
            case 2:
                statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                // 결승 상태 텍스트 전환
                statusText.setText("Final");
                break;
            // 큐에 아이템이 4개이면 준결승
            case 4:
                // 노멀 난이도일 때만
                if (difficulty.compareTo("Normal") == 0) {
                    statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                    // 준결승 상태 이미지 전환
                    statusText.setText("Semi Final");
                }
                break;
            // 그 외 8강, 16강, 32강 ... 128강
            case 8:
            case 16:
            case 32:
            case 64:
            case 128:
                if (difficulty.compareTo("Normal") == 0) {
                    statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                    statusText.setText(items.size() + "강");
                }
        }

        // 노멀 난이도일 경우
        if (difficulty.compareTo("Normal") == 0) {
            // 큐에서 두 개를 뽑아
            Icon item1 = items.poll();
            Icon item2 = items.poll();

            // 널인지 확인 후
            assert item1 != null;
            assert item2 != null;

            // 전에 선택된 아이템을 큐의 맨뒤에 삽입 후
            items.add(leftItemButton.getIcon());
            // 양쪽에 뽑은 두개의 아이템 표시
            leftItemButton.setIcon(item1);
            rightItemButton.setIcon(item2);
            // 하드 난이도일 경우
        } else if (difficulty.compareTo("Hard") == 0) {
            // 큐에서 아이템을 하나만 뽑아
            Icon item = items.poll();

            // 널인지 확인 후
            assert item != null;

            // 선택한 반대쪽에만 아이템 표시
            rightItemButton.setIcon(item);
        }

    }

    // 오른쪽 아이템 골랐을 때
    private void selectRightItem() {
        switch (items.size()) {
            case 1:
                statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                statusText.setText("WINNER is");
                winner.setIcon(rightItemButton.getIcon());
                getWinner();
                return;
            case 2:
                statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                statusText.setText("Final");
                break;
            case 4:
                if (difficulty.compareTo("Normal") == 0) {
                    statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                    statusText.setText("Semi Final");
                }
                break;
            case 8:
            case 16:
            case 32:
            case 64:
            case 128:
                if (difficulty.compareTo("Normal") == 0) {
                    statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
                    statusText.setText(items.size() + "강");
                }
        }
        if (difficulty.compareTo("Normal") == 0) {
            Icon item1 = items.poll();
            Icon item2 = items.poll();

            assert item1 != null;
            assert item2 != null;

            items.add(rightItemButton.getIcon());
            leftItemButton.setIcon(item1);
            rightItemButton.setIcon(item2);
        } else if (difficulty.compareTo("Hard") == 0) {
            Icon item = items.poll();

            assert item != null;

            leftItemButton.setIcon(item);
        }
    }

    private void getWinner() {
        leftItemButton.setVisible(false);
        rightItemButton.setVisible(false);
        winner.setVisible(true);
    }

    // 배경이미지 그리는 그래픽 함수
    public void paint(Graphics g) {
        screenImage = createImage(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT);
        screenGraphic = screenImage.getGraphics();
        screenDraw((Graphics2D) screenGraphic);
        g.drawImage(screenImage, 0, 0, null);
    }

    public void screenDraw(Graphics2D g) {
        // 변화하는 이미지
        g.drawImage(background, 0, 0, null);
        // 메인화면일 때 특정 이미지 그리기
        if (isMainScreen) {
            // 이미지 출력
            g.drawImage(selectedImage, 340, 100, null);
        }
        // 게임화면일 때
        if (isGameScreen) {
            // 게임 클래스 이동하여 이미지 출력
            game.screenDraw(g);
        }
        // 고정된 이미지는 페인트 컴퍼먼트 사용
        paintComponents(g);
        // 메인 프로그램에 추가된 요소 보여줌
        this.repaint();

    }

    // 선택한 것에 대한 곡 이미지 및 음악 삽입 함수
    public void selectTrack(int nowSelected) {
        // 선택한 음악의 값이 null 이 아니라면
        if (selectedMusic != null)
            // 실행 중인 음악을 종료
            selectedMusic.close();

        // 선택된 이미지 값을 trackList에서 selectedMusic에 Music 객체로 할당
        selectedImage = new ImageIcon(Main.class.getResource("image/" + trackList.get(nowSelected).getStartImage())).getImage();
        selectedMusic = new Music(trackList.get(nowSelected).getStartMusic(), true);
        selectedMusic.start();
    }

    // 왼쪽 버튼 누를 시
    public void selectLeft() {
        // 인덱스는 음수이면 안되기에 처리
        if (nowSelected == 0)
            nowSelected = trackList.size() - 1;
        else
            nowSelected--;
        // 트랙 선택 함수 호출
        selectTrack(nowSelected);
    }

    public void selectRight() {
        if (nowSelected == trackList.size() - 1)
            nowSelected = 0;
        else
            nowSelected++;
        selectTrack(nowSelected);
    }

    // 게임 시작 함수
    public void gameStart(String difficulty) {
        if (selectedMusic != null)
            selectedMusic.close();

        isMainScreen = false;
        leftButton.setVisible(false);
        rightButton.setVisible(false);
        normalButton.setVisible(false);
        hardButton.setVisible(false);

        // 백그라운드 이미지 지정
        background = new ImageIcon(Main.class.getResource("image/" + trackList.get(nowSelected).getGameImage())).getImage();
        backButton.setVisible(true);

        // 난이도 정보 디피컬트 음악이 실행중이라면 닫아줌
        isGameScreen = true;
        setFocusable(true);
        leftItemButton.setVisible(true);
        rightItemButton.setVisible(true);

        this.difficulty = difficulty;
        // 게임 시작 시 마다 큐를 새로 할당
        items = new LinkedList<>();
        // 순회용 인덱스
        int index = 0;

        // 선택한 트랙에 따라서 분기
        switch (trackList.get(nowSelected).getTitleName()) {
            // 스타크래프트
            case "sc":
                // 새로운 게임 객체 생성
                game = new Game(difficulty, trackList.get(nowSelected).getGameMusic(), "Star Craft");
                // 스타크래프트 경로 배열을 List로 치환
                sc = Arrays.asList(scImages);
                // 순서 무작위로 섞음
                Collections.shuffle(sc);

                // 리스트 내 모든 아이템에 대해서
                for (String s : sc) {
                    // ROUND만큼 순회했으면 종료
                    // 이 때 라운드는 기본 16강이며, 이미지 추가 후 정적변수 ROUND 바꾸어주면 32강, 64강 ... 진행가능
                    if (index == ROUND)
                        break;
                    // 이미지 아이콘 생성 후
                    ImageIcon icon = new ImageIcon(Main.class.getResource("image/sc/" + s));
                    // 크기를 500 x 500으로 리사이즈하여 통일
                    icon = imageSetsize(icon, 500, 500);

                    // 큐에 추가
                    items.add(icon);
                    // 인덱스 증가
                    index++;
                }
                break;
            // WWE
            case "wwe":
                game = new Game(difficulty, trackList.get(nowSelected).getGameMusic(), "WWE");
                wwe = Arrays.asList(wweImages);
                Collections.shuffle(wwe);
                for (String s : wwe) {
                    if (index == ROUND)
                        break;

                    ImageIcon icon = new ImageIcon(Main.class.getResource("image/wwe/" + s));
                    icon = imageSetsize(icon, 500, 500);

                    items.add(icon);
                    index++;
                }
                break;
            // 더 킹 오브 파이터즈
            case "kof":
                game = new Game(difficulty, trackList.get(nowSelected).getGameMusic(), "The King of Fighters");
                kof = Arrays.asList(kofImages);
                Collections.shuffle(kof);
                for (String s : kof) {
                    if (index == ROUND)
                        break;

                    ImageIcon icon = new ImageIcon(Main.class.getResource("image/kof/" + s));
                    icon = imageSetsize(icon, 500, 500);

                    items.add(icon);
                    index++;
                }
                break;
        }

        // 처음에 큐에서 2개의 아이템을 큐에서 뽑아서
        Icon item1 = items.poll();
        Icon item2 = items.poll();

        // 널인지 확인 후
        assert item1 != null;
        assert item2 != null;

        // 양 버튼에 이미지 지정
        leftItemButton.setIcon(item1);
        rightItemButton.setIcon(item2);
        statusText.setVisible(true);

        // 노멀 난이도인 경우에만 몇강인지 표시
        if (difficulty.compareTo("Normal") == 0) {
            statusText.setFont(new Font("맑은 고딕", Font.PLAIN, 50));
            statusText.setText(ROUND + "강");
        } else
            statusText.setText("");
    }

    // 메인 화면으로 돌아가는 함수
    public void backMain() {
        isMainScreen = true;
        leftButton.setVisible(true);
        rightButton.setVisible(true);
        normalButton.setVisible(true);
        hardButton.setVisible(true);
        background = new ImageIcon(Main.class.getResource("image/mainBackground.png"))
                .getImage();
        backButton.setVisible(false);
        // 현재의 선택된부분을 보여주고 하이라이트 재생
        selectTrack(nowSelected);
        // 게임이 끝나는 부분
        isGameScreen = false;
        // 현재 실행되고 있는 게임 및 음악 종료
        game.close();
    }

    // 메인으로 들어가는 함수
    public void enterMain() {
        startButton.setVisible(false);
        quitButton.setVisible(false);
        leftButton.setVisible(true);
        rightButton.setVisible(true);
        normalButton.setVisible(true);
        hardButton.setVisible(true);
        background = new ImageIcon(Main.class.getResource("image/mainBackground.png")).getImage();
        // 메인 스크린 트루값해서 보이게
        isMainScreen = true;
        flowerdance.close();
        // 메인 화면 으로 넘어 가는부분
         selectTrack(0);
    }

    // 이미지 아이콘 이미지 리사이즈 함수
    private ImageIcon imageSetsize(ImageIcon icon, int i, int j) {
        // ImageIcon을 Image로 변환.
        Image ximg = icon.getImage();
        Image yimg = ximg.getScaledInstance(i, j, java.awt.Image.SCALE_SMOOTH);
        ImageIcon xyimg = new ImageIcon(yimg);

        return xyimg;
    }
}

