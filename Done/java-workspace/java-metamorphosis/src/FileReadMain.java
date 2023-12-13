import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.*;

public class FileReadMain {
    public static void main(String[] args) throws IOException {
        File file = new File("Metamorphosis.txt");
        HashMap<String, Integer> frequencies = new HashMap<>();

        int length = 0, numWord = 0, numSent = 0, numPara = 0;
        try (Scanner sc = new Scanner(file)) {
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                if (line.compareTo("") == 0) {
                    numPara++;
                    continue;
                }

                length += line.length();
                StringTokenizer st = new StringTokenizer(line);

                while (st.hasMoreTokens()) {
                    String word = st.nextToken();
                    if (word.compareTo("") != 0) {
                        numWord++;
                        if (word.charAt(word.length() - 1) == '”' || word.charAt(word.length() - 1) == '.' || word.charAt(word.length() - 1) == '!' || word.charAt(word.length() - 1) == '?')
                            numSent++;
                        while (word.length() >= 1 && !(word.charAt(0) >= 'a' && word.charAt(0) <= 'z') && !(word.charAt(0) >= 'A' && word.charAt(0) <= 'Z')) {
                            word = word.substring(1);
                        }
                        while (word.length() >= 1 && !(word.charAt(word.length() - 1) >= 'a' && word.charAt(word.length() - 1) <= 'z') && !(word.charAt(word.length() - 1) >= 'A' && word.charAt(word.length() - 1) <= 'Z')) {
                            word = word.substring(0, word.length() - 1);
                        }

                        if (word.length() >= 2 && word.charAt(word.length() - 2) == '’' && word.charAt(word.length() - 1) == 's')
                            word = word.substring(0, word.length() - 2);
                        if (word.length() == 0)
                            continue;

                        word = word.toLowerCase();
                        if (frequencies.get(word) == null)
                            frequencies.put(word, 1);
                        else
                            frequencies.put(word, frequencies.get(word) + 1);
                    } else {
                        break;
                    }
                }
            }
            System.out.printf("Length in characters: %d\n", length);
            System.out.printf("Number of words: %d\n", numWord);
            System.out.printf("Number of sentences: %d\n", numSent);
            System.out.printf("Number of paragraphs: %d\n", numPara / 2 + 1);

            FileWriter fw = new FileWriter("Frequencies.txt", true);

            Iterator<Map.Entry<String, Integer>> entry =
                    frequencies.entrySet().iterator();

            int idx = 0;
            while (entry.hasNext()) {
                Map.Entry<String, Integer> element = entry.next();

                String line = "INDEX " + Integer.toString(idx++) + ": WORD: " + element.getKey() + " FREQ: " + element.getValue();
                fw.write(line + "\n");
            }
            fw.flush();
            fw.close();
        } catch (IOException e) {
            e.printStackTrace();
        }

    }
}
