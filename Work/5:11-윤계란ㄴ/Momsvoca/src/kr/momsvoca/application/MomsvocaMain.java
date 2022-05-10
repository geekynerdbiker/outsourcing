package kr.momsvoca.application;

import kr.momsvoca.application.controllers.MomsvocaController;
import kr.momsvoca.application.models.MomsvocaModel;

import java.awt.Font;
import java.awt.FontFormatException;
import java.awt.GraphicsEnvironment;
import java.io.File;
import java.io.IOException;

public class MomsvocaMain {
    public static void main(String[] args) {
        GraphicsEnvironment ge = GraphicsEnvironment.getLocalGraphicsEnvironment();
        try {
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("resources/fonts/a뉴굴림1.ttf")));
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("resources/fonts/a뉴굴림2.ttf")));
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("resources/fonts/a뉴굴림3.ttf")));
            ge.registerFont(Font.createFont(Font.TRUETYPE_FONT, new File("resources/fonts/a뉴굴림4.ttf")));

            for(Font font : ge.getAllFonts()) {
                System.out.println(font.getName());
            }
            //System.out.println(ge.getAllFonts());
        } catch (FontFormatException e) {
            e.printStackTrace();
        } catch (IOException e) {
            e.printStackTrace();
        }

        MomsvocaModel model = new MomsvocaModel();
        MomsvocaView view = new MomsvocaView(model);
        MomsvocaController controller = new MomsvocaController(model, view);
        model.initialize();
        view.initialize();
        controller.initialize();

        view.start();
    }
}
