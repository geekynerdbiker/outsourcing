import java.io.IOException;

public class Main {
    public static void main(String[] args) throws IOException {
        float input = 0;
        float n1 = 0, n2 = 0;
        float op = 0;

        while (true) {
            while (input != '=' && input != EOF) {
                input = System.in.read();

                if (input == 10)
                    continue;
                if (input >= '0' && input <= '9') {
                    input -= '0';
                    System.out.format("%d 0x%x\n", (int) input, (int) (input + '0'));
                } else if (input == '+' || input == '-' || input == '*' || input == '/') {
                    op = input;
                    System.out.format("%c 0x%x\n", (char) input, (int) input);
                    continue;
                }

                if (op == 0) {
                    n1 = n1 * 10 + input;
                } else if (input != '=') {
                    n2 = n2 * 10 + input;
                } else {
                    System.out.format("%c 0x%x\n", (char) input, (int) input);
                }
            }

            if (op == '+')
                System.out.format("%d FLOAT TYPE\n", (int) (n1 + n2));
            else if (op == '-')
                System.out.format("%d FLOAT TYPE\n", (int) (n1 - n2));
            else if (op == '*')
                System.out.format("%d FLOAT TYPE\n", (int) (n1 * n2));
            else if (op == '/') {
                if (n2 == 0)
                    System.out.println("Cannot divide by 0.");
                else
                    System.out.format("%d FLOAT TYPE\n", (int) (n1 / n2));
            }
            input = 0; n1 = 0; n2 = 0; op = 0;
        }
    }
}