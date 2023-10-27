import java.awt.Dimension;
import java.awt.Font;
import java.awt.Image;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.ImageIcon;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JPanel;

public class Worldcub {
    static JPanel panelNorth;
    static JPanel panelCenter;
    static JLabel lavelMessage;
    static JLabel labelVs ;
    static JButton buttonLeft;
    static JButton buttonRight;
    static String[] images = {
            "sc/sc1.png", "sc/sc2.png", "sc/sc3.png", "sc/sc4.png", "sc/sc5.png", "sc/sc6.png", "sc/sc7.png", "sc/sc8.png", "sc/sc9.png"
            , "sc/sc10.png", "sc/sc11.png", "sc/sc12.png", "sc/sc13.png", "sc/sc14.png", "sc/sc15.png", "sc/sc16.png",
    };
    static int imageIndex = 2; //th image index initialized

    // 펑션
    static ImageIcon changeImage(String filname) {
        ImageIcon icon = new ImageIcon("./" + filname);
        Image originImage = icon.getImage();
        Image changedImage = originImage.getScaledInstance(200, 200, Image.SCALE_SMOOTH);
        ImageIcon icon_new = new ImageIcon(changedImage);
        return icon_new;
    }


    static class MyFrame extends JFrame implements ActionListener {
        public MyFrame(String title) {
            super(title);
            //ui 초기화
            this.setSize(450, 250);
            this.setVisible(true);
            this.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);

            panelNorth = new JPanel();
            lavelMessage = new JLabel("Find Your Win!");
            lavelMessage.setFont(new Font("Arial", Font.BOLD, 20));
            panelNorth.add(lavelMessage);
            this.add(panelNorth);
            
            panelCenter = new JPanel();
            labelVs = new JLabel("VS");
            labelVs .setFont(new Font("Arial", Font.BOLD, 20));
            buttonLeft = new JButton("LeftButton");
            buttonLeft.setIcon(changeImage("sc/sc1.png"));
            buttonLeft.setPreferredSize(new Dimension(200,200));
            buttonRight = new JButton("RightButton");
            buttonRight.setIcon(changeImage("sc/sc2.png"));
            buttonRight.setPreferredSize(new Dimension(200,200));
            //클릭 이벤트
            buttonLeft.addActionListener(this);
            buttonRight.addActionListener(this);
            panelCenter.add(buttonLeft);
            panelCenter.add(labelVs );
            panelCenter.add(buttonRight);
            this.add("Center",panelCenter);

            this.pack(); //빈공간을 없애주고 딱맞게 해줌
        }

        // 버튼 클릭 이벤트
        @Override
        public void actionPerformed(ActionEvent e) {
        	if (imageIndex==16) {
				//last win
        		lavelMessage.setText("WIN");
        		if (e.getActionCommand().equals("LeftButton")) {
        			buttonRight.hide();
        			labelVs.hide();
        			}else {
        				buttonRight.hide();
            			labelVs.hide();
					}
        		
			}
            if( e.getActionCommand().equals("LeftButton")){
            	buttonRight.setIcon(changeImage(images[imageIndex]));
            	imageIndex++;
            }else {
            	buttonLeft.setIcon(changeImage(images[imageIndex]));
            	imageIndex++;
            }

        }

        public static void main(String[] args) {
            new MyFrame("World Cup");
        }
    }
}