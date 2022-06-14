import java.util.Arrays;
import java.io.FileReader;
import java.io.IOException;
import java.io.BufferedReader;
import java.util.StringTokenizer;

public class Main {
    public static void main(String[] args) throws IOException {
        BufferedReader reader = new BufferedReader(new FileReader("/Users/jacoban/Desktop/SimpleRectangleApplication/src/input.txt"));
        Rectangle[] rectangles = new Rectangle[5];
        int len = 0;

        String str;
        while ((str = reader.readLine()) != null) {
            StringTokenizer st = new StringTokenizer(str);
            int[] arg = new int[4];
            for (int i = 0; st.hasMoreTokens(); i++) {
                arg[i] = Integer.parseInt(st.nextToken());
            }
            rectangles[len++] = new Rectangle(arg[0], arg[1], arg[2], arg[3]);
        }
        reader.close();

        System.out.println("Before Sort");
        for (int i = 0; i < 5; i++)
            System.out.println(rectangles[i].getSize() + " " + rectangles[i].width + " " + rectangles[i].height + " " + rectangles[i].x + " " + rectangles[i].y);

        Arrays.sort(rectangles);

        System.out.println("\nAfter Sort");
        for (int i = 0; i < 5; i++)
            System.out.println(rectangles[i].getSize() + " " + rectangles[i].width + " " + rectangles[i].height + " " + rectangles[i].x + " " + rectangles[i].y);

        System.out.println("\nOverlap Area");
        for (int i = 0; i < 4; i++) {
            for (int j = i + 1; j < 5; j++) {
                int smaller = Math.min(rectangles[i].getSize(), rectangles[j].getSize());
                int bigger = Math.max(rectangles[i].getSize(), rectangles[j].getSize());
                System.out.println(smaller + " " + bigger + " " + rectangles[i].overlapArea(rectangles[j]));
            }
        }
    }
}
