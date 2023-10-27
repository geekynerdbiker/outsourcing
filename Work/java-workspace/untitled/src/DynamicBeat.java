import javax.swing.*;
import java.awt.*;
import java.awt.event.MouseAdapter;
import java.awt.event.MouseEvent;
import java.awt.event.MouseMotionAdapter;
import java.util.ArrayList;


public class DynamicBeat extends JFrame {

    private Image screenImage;
    private Graphics screenGraphic;


    private Image background = new ImageIcon(Main.class.getResource("image/game_title.jpg")).getImage();

    private JLabel menuBar = new JLabel(new ImageIcon(Main.class.getResource("image/menuBar.png")));


    private ImageIcon exitButtonEnteredImage = new ImageIcon(Main.class.getResource("image/exitButtonEntered.png"));
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

    private ImageIcon leftItemImage = new ImageIcon(Main.class.getResource("image/exitButtonEntered.png"));
    private ImageIcon rightItemImage = new ImageIcon(Main.class.getResource("image/exitButtonBasic.png"));



    // 이미지들 아이콘에 저장
    private JButton exitButton = new JButton(exitButtonBasicImage);
    private JButton startButton = new JButton(startButtonBasicImage);
    private JButton quitButton = new JButton(quitButtonBasicImage);
    private JButton leftButton = new JButton(leftButtonBasicImage);
    private JButton rightButton = new JButton(rightButtonBasicImage);
    private JButton normalButton = new JButton(normalButtonBasicImage);
    private JButton hardButton = new JButton(hardButtonBasicImage);
    private JButton backButton = new JButton(backButtonBasicImage);
    private JButton leftItemButton = new JButton(leftItemImage);
    private JButton rightItemButton = new JButton(rightItemImage);


    // 이미지 변수 설정 초기화
    private int mouseX, mouseY;

    private boolean isMainScreen = false; //메인화면 이동시 트루
    private boolean isGameScreen = false; //게임 화면 넘어왔는지 변수


    ArrayList<Track> trackList = new ArrayList<Track>(); //트랙 클래스이용 변수들을 담을 배열


    private Image titleImage;
    private Image selectedImage;
    private int nowSelected = 0;

    public static Game game; // 게임변수는 프로젝트 전체에 가능

    public DynamicBeat() {
        setUndecorated(true);
        setTitle("Dynamic Beat");
        setSize(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT);
        setResizable(false);
        setLocationRelativeTo(null);
        setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
        setVisible(true);
        setBackground(new Color(0, 0, 0, 0));
        setLayout(null);

        trackList.add(new Track("Star Title Image.png", "Star Start Image.png",
                "Star Game Image.png", "Terranteam Selected.mp3", "Terranteam.mp3", "Terranteam"));
        trackList.add(new Track("Wwe Title Image.png", "Wwe Start Image.png",
                "Wwe Game Image.png", "AcrosstheNation Selected.mp3", "AcrosstheNation.mp3", "AcrosstheNation"));
        trackList.add(new Track("Kof Title Image.png", "Kof Start Image.png",
                "Kof Game Image.png", "Esaka Selected.mp3", "Esaka.mp3", "Esaka"));
        //파일 순서대로 넣기 변수 초기화 트랙리스트에 넣어줌
        exitButton.setBounds(1245, 0, 30, 30);
        exitButton.setBorderPainted(false);
        exitButton.setContentAreaFilled(false);
        exitButton.setFocusPainted(false);
        exitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                exitButton.setIcon(exitButtonEnteredImage);
                exitButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
            }

            @Override
            public void mouseExited(MouseEvent e) {
                exitButton.setIcon(exitButtonBasicImage);
                exitButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                try {
                    Thread.sleep(1000);

                } catch (InterruptedException ex) {
                    ex.printStackTrace();
                }
                System.exit(0);
            }
        });
        add(exitButton);

        startButton.setBounds(40, 200, 400, 100);
        startButton.setBorderPainted(false);
        startButton.setContentAreaFilled(false);
        startButton.setFocusPainted(false);
        startButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                startButton.setIcon(startButtonEnteredImage);
                startButton.setCursor(new Cursor(Cursor.HAND_CURSOR));

            }

            @Override
            public void mouseExited(MouseEvent e) {
                startButton.setIcon(startButtonBasicImage);
                startButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                enterMain(); //메인 함수로 들어간다
            }
        });
        add(startButton);


        quitButton.setBounds(40, 330, 400, 100);
        quitButton.setBorderPainted(false);
        quitButton.setContentAreaFilled(false);
        quitButton.setFocusPainted(false);
        quitButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                quitButton.setIcon(quitButtonEnteredImage);
                quitButton.setCursor(new Cursor(Cursor.HAND_CURSOR));

            }

            @Override
            public void mouseExited(MouseEvent e) {
                quitButton.setIcon(quitButtonBasicImage);
                quitButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                System.exit(0);
            }
        });
        add(quitButton);

        leftButton.setVisible(false); //맨처음엔 보이지 않토록 시작하기 버튼누루고
        // 메인화면 넘어왔을떄 is 메인스크린 에 들어와서 각각의 곡정보를 출력하고 레프트 라이트
        // 버튼이고 곡들이보이고  완전하게 메인화면이 보인다
        leftButton.setBounds(140, 310, 60, 60);
        leftButton.setBorderPainted(false);
        leftButton.setContentAreaFilled(false);
        leftButton.setFocusPainted(false);
        leftButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                leftButton.setIcon(leftButtonEnteredImage);
                leftButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
            }

            @Override
            public void mouseExited(MouseEvent e) {
                leftButton.setIcon(leftButtonBasicImage);
                leftButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {
                selectLeft();
                //왼쪽 버튼 이벤트
            }
        });
        add(leftButton);

        rightButton.setVisible(false); //맨처음엔 보이지 않토록
        rightButton.setBounds(1080, 310, 60, 60);
        rightButton.setBorderPainted(false);
        rightButton.setContentAreaFilled(false);
        rightButton.setFocusPainted(false);
        rightButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                rightButton.setIcon(rightButtonEnteredImage);
                rightButton.setCursor(new Cursor(Cursor.HAND_CURSOR));


            }

            @Override
            public void mouseExited(MouseEvent e) {
                rightButton.setIcon(rightButtonBasicImage);
                rightButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {


                selectRight();
                //오른쪽 버튼 이벤트
            }
        });
        add(rightButton);

        normalButton.setVisible(false); //맨처음엔 보이지 않토록
        normalButton.setBounds(375, 580, 250, 67);
        normalButton.setBorderPainted(false);
        normalButton.setContentAreaFilled(false);
        normalButton.setFocusPainted(false);
        normalButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                normalButton.setIcon(normalButtonEnteredImage);
                normalButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
            }

            @Override
            public void mouseExited(MouseEvent e) {
                normalButton.setIcon(normalButtonBasicImage);
                normalButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                gameStart("Normal");
                //난이도 노말 버튼 이벤트
            }
        });
        add(normalButton);

        hardButton.setVisible(false); //맨처음엔 보이지 않토록
        hardButton.setBounds(655, 580, 250, 67);
        hardButton.setBorderPainted(false);
        hardButton.setContentAreaFilled(false);
        hardButton.setFocusPainted(false);
        hardButton.addMouseListener(new MouseAdapter() {
            @Override
            public void mouseEntered(MouseEvent e) {
                hardButton.setIcon(hardButtonEnteredImage);
                hardButton.setCursor(new Cursor(Cursor.HAND_CURSOR));
            }

            @Override
            public void mouseExited(MouseEvent e) {
                hardButton.setIcon(hardButtonBasicImage);
                hardButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));

            }

            @Override
            public void mousePressed(MouseEvent e) {


                gameStart("Hard");
                //난이도 어려움 버튼 이벤트
            }
        });
        add(hardButton);

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


            }

            @Override
            public void mouseExited(MouseEvent e) {
                backButton.setIcon(backButtonBasicImage);
                backButton.setCursor(new Cursor(Cursor.DEFAULT_CURSOR));
            }

            @Override
            public void mousePressed(MouseEvent e) {
                backMain();
                //메인화면으로 돌아가는 이벤트
            }
        });
        add(backButton);


        menuBar.setBounds(0, 0, 1280, 30);
        menuBar.addMouseListener(new MouseAdapter() {
            @Override
            public void mousePressed(MouseEvent e) {
                mouseX = e.getX();
                mouseY = e.getY();

            }
        });
        menuBar.addMouseMotionListener(new MouseMotionAdapter() {
            @Override
            public void mouseDragged(MouseEvent e) {
                int x = e.getXOnScreen();
                int y = e.getYOnScreen();
                setLocation(x - mouseX, y - mouseY);
            }

        });
        add(menuBar);

    }

    public void paint(Graphics g) {
        screenImage = createImage(Main.SCREEN_WIDTH, Main.SCREEN_HEIGHT);
        screenGraphic = screenImage.getGraphics();
        screenDraw((Graphics2D) screenGraphic);
        g.drawImage(screenImage, 0, 0, null);
    }

    public void screenDraw(Graphics2D g) {
        g.drawImage(background, 0, 0, null); // 변화하는 이미지
        if (isMainScreen) { //그림을 그려줄떄 트루값일떄 특정한이미지 그리기
            g.drawImage(selectedImage, 340, 100, null);
            g.drawImage(titleImage, 340, 70, null);
        } //g.드로우 이미지는 단순히 이미지를 출력하는거
        //이미지나 역동적인 움직임을 보여주는건 드로우 이미지 함수 로 그려줌
        if (isGameScreen) {
            game.screenDraw(g); //게임 클래스 이동
        }
        super.paintComponents(g); // 고정된 이미지 이기떄문에 페인트 컴퍼먼트 사용
        this.repaint(); //메인 프로그램에 추가된요소 보여줌 add 페인트 컴퍼먼트에서 그려지는거

    }

    public void selectTrack(int nowSelected)
    // 선택한 것에 대한 곡 이미지 및 음악 삽입 함수

    {
        titleImage = new ImageIcon(Main.class.getResource("image/" + trackList.get(nowSelected).getTitleImage())).getImage();
        // 타이틀 이미지 값을 trackList에서 nowSelected에 있는 곳에서 불러오겠다.
        selectedImage = new ImageIcon(Main.class.getResource("image/" + trackList.get(nowSelected).getStartImage())).getImage();
        // 선택된 이미지 값을 trackList에서 nowSelected에 있는 곳에서 불러오겠다.
    }

    public void selectLeft() {
        if (nowSelected == 0)
            nowSelected = trackList.size() - 1;
        else
            nowSelected--;
        selectTrack(nowSelected);
    }

    public void selectRight() {
        if (nowSelected == trackList.size() - 1)
            nowSelected = 0;
        else
            nowSelected++;
        selectTrack(nowSelected);
    }

    public void gameStart(String difficulty) {
        isMainScreen = false;
        leftButton.setVisible(false);
        rightButton.setVisible(false);
        normalButton.setVisible(false);
        hardButton.setVisible(false);
        background = new ImageIcon(Main.class.getResource("image/" + trackList.get(nowSelected).getGameImage())).getImage();
        backButton.setVisible(true);
        // 난이도 정보 디피컬트 음악이 실행중이라면 닫아줌 메인화면이아니라서 스크린드로우 부분 실행안됨
        isGameScreen = true;
        // 게임이 시작하는 부분
        setFocusable(true);
        game = new Game(difficulty);
        requestFocus();
        // 메인창 키보드 포커서 맞쳐짐
    }

    public void backMain() {
        isMainScreen = true;
        leftButton.setVisible(true);
        rightButton.setVisible(true);
        normalButton.setVisible(true);
        hardButton.setVisible(true);
        background = new ImageIcon(Main.class.getResource("image/mainBackground.png"))
                .getImage();
        backButton.setVisible(false);
        selectTrack(nowSelected);
        //현재의 선택된부분을 보여주고 하이라이트 재생
        isGameScreen = false;
        // 게임이 끝나는 부분
        game.close();
        // 현재 실행되고있는 게임종료 음악도 종료 다른곡 선택할수있도록

    }

    public void enterMain() {
        startButton.setVisible(false);
        quitButton.setVisible(false);
        leftButton.setVisible(true);
        rightButton.setVisible(true);
        normalButton.setVisible(true);
        hardButton.setVisible(true);
        background = new ImageIcon(Main.class.getResource("image/mainBackground.png")).getImage();
        isMainScreen = true; //메인 스크린 트루값해서 보이게
        selectTrack(0);
        // 메인 화면 으로 넘어 가는부분
    }
}

