import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;

import javazoom.jl.player.Player;

public class Music extends Thread {
	// 음악 실행을 위한 클래스 변수들
    // jLayer 라이브러리 필요
    private Player player;
    private boolean isLoop;
    private File file;
    private FileInputStream fis;
    private BufferedInputStream bis;

    public Music(String name, boolean isLoop) {
        // try-catch문으로 예외 컨트롤
        try {
            // 음악 파일을 열어서 파일, 버퍼, 뮤직 플레이어 클래스 초기화
            this.isLoop = isLoop;
            file = new File(Main.class.getResource("music/" + name).toURI());
            fis = new FileInputStream(file);
            bis = new BufferedInputStream(fis);
            player = new Player(bis);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }

    // 현재 재생중인 시간 반환
    public int getTime() {
        if (player == null)
            return 0;
        return player.getPosition();
    }

    // 현재 실행중인 스레드 종료
    public void close() {
        isLoop = false;
        player.close();
        this.interrupt();
    }

    // 스레드 실행 함수
    @Override
    public void run() {
        try {
            do {
                // 초기화된 정보로 음악 재생
                player.play();
                fis = new FileInputStream(file);
                bis = new BufferedInputStream(fis);
                player = new Player(bis);
            } while (isLoop);
        } catch (Exception e) {
            System.out.println(e.getMessage());
        }
    }
}

