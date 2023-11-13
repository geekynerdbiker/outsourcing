import java.io.BufferedReader;
import java.io.FileReader;
import java.io.IOException;

public class Main {



    public static void main(String[] args) throws IOException {
        BufferedReader br = new BufferedReader(new FileReader("input2.txt"));

        String sLine;

        Tree t = new Tree();
        while( (sLine = br.readLine()) != null ) {
            int index = 0;
            for (int i = 0; i < sLine.length(); i++)
                if (sLine.charAt(i) == ' ') {
                    index = i;
                    break;
                }

            String parent = sLine.substring(0, index);
            String child = sLine.substring(index+1);
            t.addNode(parent, child);
        }
        ArrayQueue result = t.levelOrder();
        if (result == null || !t.validation())
            System.out.println("null");
        else 
            result.print();
    }
}