package ajou_service.Student;

import javax.swing.*;

public class StudentPopUp extends JFrame {
    StudentPopUp(int flag) {
        JLabel NewLabel;
        setTitle("New Window");

        JPanel NewWindowContainer = new JPanel();
        setContentPane(NewWindowContainer);

        if (flag == 0) {
            NewWindowContainer.add(new JLabel("선택하신 강의가 정상적으로 신청되었습니다."));

        } else if (flag == 1) {
            NewWindowContainer.add(new JLabel("선택하신 강의를 신청할 수 없습니다"));
            NewWindowContainer.add(new JLabel("시간 및 강의를 다시 확인해 주세요"));

        } else if (flag == 2) {
            NewWindowContainer.add(new JLabel("선택하신 강의가 정상적으로 취소되었습니다."));
        } else if (flag == 3) {
            NewWindowContainer.add(new JLabel("선택하신 강의를 취소할 수 없습니다"));
            NewWindowContainer.add(new JLabel("시간 및 강의를 다시 확인해 주세요"));
        }

        setSize(300, 100);
        setResizable(false);
        setVisible(true);
    }
}
