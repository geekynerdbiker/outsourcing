import java.awt.Color;
import java.awt.Font;
import java.awt.Graphics2D;
import java.awt.Image;
import java.awt.RenderingHints;

import javax.swing.ImageIcon;

public class Game extends Thread {

    private Image noteBasicImage=new ImageIcon(Main.class.getResource("../image/noteBasic.png")).getImage();;
    private Image noteRouteLineImage=new ImageIcon(Main.class.getResource("../image/noteRouteLine.png")).getImage();;

    private Image gameInfoImage=new ImageIcon(Main.class.getResource("../image/gameInfo.png")).getImage();;
    private Image judgementLineImage=new ImageIcon(Main.class.getResource("../image/judgementLine.png")).getImage();;

    private Image noteRouteSImage = new ImageIcon(Main.class.getResource("../image/noteRoute.png")).getImage();
    private Image noteRouteDImage = new ImageIcon(Main.class.getResource("../image/noteRoute.png")).getImage();
    private Image noteRouteSpaceImage = new ImageIcon(Main.class.getResource("../image/noteRoute.png")).getImage();
    private Image noteRouteKImage = new ImageIcon(Main.class.getResource("../image/noteRoute.png")).getImage();
    private Image noteRouteLImage = new ImageIcon(Main.class.getResource("../image/noteRoute.png")).getImage();

    private String difficulty;

    public Game(String difficulty) {
        this.difficulty = difficulty;
    }


    public void screenDraw(Graphics2D g) {
        g.drawImage(noteRouteSImage, 272, 30, null);
        g.drawImage(noteRouteDImage, 424, 30, null);
        g.drawImage(noteRouteSpaceImage, 574, 30, null);
        g.drawImage(noteRouteKImage, 724, 30, null);
        g.drawImage(noteRouteLImage, 874, 30, null);

        g.drawImage(noteBasicImage, 272, 30, null);
        g.drawImage(noteBasicImage, 424, 30, null);
        g.drawImage(noteBasicImage, 574, 30, null);
        g.drawImage(noteBasicImage, 724, 30, null);
        g.drawImage(noteBasicImage, 874, 30, null);

        g.drawImage(noteRouteLineImage, 266, 30, null);
        g.drawImage(noteRouteLineImage, 424, 30, null);
        g.drawImage(noteRouteLineImage, 574, 30, null);
        g.drawImage(noteRouteLineImage, 724, 30, null);
        g.drawImage(noteRouteLineImage, 874, 30, null);
        g.drawImage(noteRouteLineImage, 1020, 30, null);


        g.drawImage(gameInfoImage, 0, 660, null);
        g.drawImage(judgementLineImage, 0, 580, null);
        g.setRenderingHint( RenderingHints.KEY_TEXT_ANTIALIASING, RenderingHints.VALUE_TEXT_ANTIALIAS_ON);
    }

    @Override
    public void run() {

    }

    public void close() {
        this.interrupt();
        // 지금 실행 하고있는 스레드 종료
    }

}