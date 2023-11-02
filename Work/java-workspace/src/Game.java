import java.awt.*;

import javax.swing.*;

public class Game extends Thread {
    // 이미지, 그래픽 등 멤버 변수 선언
    private Image screenImage;
    private Graphics screenGraphic;
    private Image gameInfoImage = new ImageIcon(Main.class.getResource("image/gameInfo.png")).getImage();

    // 생성자에서 받아옴
    private String difficulty;
    private String title;
    private Music gameMusic;

    public Game(String difficulty, String musicTitle, String title) {
        this.difficulty = difficulty;
        this.title = title;

        // 받아온 musicTitle로 Music 객체 생성 후 할당
        gameMusic = new Music(musicTitle, false);
        gameMusic.start();
    }

    // 화면을 그리는 함수
    public void screenDraw(Graphics2D g) {
        g.drawImage(gameInfoImage, 0, 660, null);
        g.setColor(Color.WHITE);
        g.setFont(new Font("Arial", Font.BOLD, 30));
        g.drawString(title, 20, 702);
        g.drawString(difficulty, 1100, 702);
        g.setFont(new Font("Arial", Font.PLAIN, 26));
        g.setColor(Color.DARK_GRAY);
    }

    // Thread 익스텐션 클래스 이므로 생성
    // 다른 동작을 할 필요 없으므로 함수를 비워 둠
    @Override
    public void run() {

    }

    // 지금 실행중인 스레드 종료
    public void close() {
        gameMusic.close();
        this.interrupt();
    }
}