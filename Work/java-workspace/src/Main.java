import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {



    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("src/input.txt"));

        String sLine = null;

        Tree t = new Tree();
        while( (sLine = br.readLine()) != null ) {
            String parent = String.valueOf(sLine.charAt(0));
            String child = String.valueOf(sLine.charAt(2));
            t.addNode(parent, child);
        }
        ArrayQueue result = t.levelOrder();
        result.print();
    }
}