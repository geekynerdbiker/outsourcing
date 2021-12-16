import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.*;
import java.util.*;
import javax.swing.*;


class prob8 extends JFrame {

    /*


     8-1


     */
    Map<String, String> nations = new Map<String, String>() { // 1
        @Override
        public int size() {
            return 0;
        }

        @Override
        public boolean isEmpty() {
            return false;
        }

        @Override
        public boolean containsKey(Object key) {
            return false;
        }

        @Override
        public boolean containsValue(Object value) {
            return false;
        }

        @Override
        public String get(Object key) {
            return null;
        }

        @Override
        public String put(String key, String value) {
            return null;
        }

        @Override
        public String remove(Object key) {
            return null;
        }

        @Override
        public void putAll(Map<? extends String, ? extends String> m) {

        }

        @Override
        public void clear() {

        }

        @Override
        public Set<String> keySet() {
            return null;
        }

        @Override
        public Collection<String> values() {
            return null;
        }

        @Override
        public Set<Entry<String, String>> entrySet() {
            return null;
        }
    };
    JFrame jf;

    void readNations() throws IOException {
        BufferedReader br;
        InputStreamReader isr = null;
        FileInputStream fis = null;
        String input;

        br = new BufferedReader(new InputStreamReader(new FileInputStream("nation.txt"))); // 2
        while ((input = br.readLine()) != null) { // 2
            StringTokenizer st = new StringTokenizer(input); // 2
            nations.put(st.nextToken(), st.nextToken()); // 2
        }
    }

    /*


     8-2


     */
    void createMenu() {
        JMenuBar mb = new JMenuBar();
        JMenu gameMenu = new JMenu("게임");

        mb.add(gameMenu); // 1
        JMenu newGame = new JMenu("새게임"); // 2
        JMenuItem cappital = new JMenuItem("수도"); // 3
        newGame.add(cappital); // 4

        gameMenu.add(newGame); // 5
        setJMenuBar(mb); // 6
    }

    /*


     8-3


     */
    class MenuActionListener implements ActionListener {
        public void actionPerformed(ActionEvent e) {
            int type = 0;
            String cmd = e.getActionCommand(); // 1
            if (cmd == "수도")  // 2
                type = 1; // 3
            setQuestions(type); // 4
        }
    }

    /*


     8-4


     */
    void rightAnswer() {
        // 1                          2                            3             4                 5
        JOptionPane.showMessageDialog(jf, "축하합니다. 정답입니다!!", "축하", JOptionPane.INFORMATION_MESSAGE);
    }

    /*


     8-5


     */
    void wrongAnser() {
        //                        1                                                                                                     2
        int result = JOptionPane.showConfirmDialog(null, "틀렸습니다. 다른 게임을 하시겠습니까?", "Confirm", JOptionPane.YES_NO_OPTION);
        if (result == JOptionPane.YES_OPTION) {
        } // 3

    }

    /*


     8-6


     */
    void setQuestions(int type) {
        String n;
        if (type == 1) { // 1
            n = getNation(); // 2
            String userAnswer = JOptionPane.showInputDialog(n + "의 수도는?"); // 3

            if (checkAnswer(n, userAnswer)) // 4
                rightAnswer(); // 5
            else
                wrongAnser(); // 6
        }
    }

    /*


     8-7


     */
    // 1
    boolean checkAnswer(String national, String capital) {
        String n = nations.get(national); // 2
        if (n.compareTo(capital) == 0) // 3
            return true;
        else
            return false;
    }

    String getNation() {
        return "";
    }

}