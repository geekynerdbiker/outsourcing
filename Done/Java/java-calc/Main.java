import java.io.BufferedReader;
import java.io.InputStreamReader;
import java.util.*;

public class Main {
    public static void main(String args[]) {
        BufferedReader br = new BufferedReader(new InputStreamReader(System.in));

        while (true) {
            try {
                String input = br.readLine();
                if (input.compareTo("q") == 0)
                    break;

                command(input);
            } catch (Exception e) {
                System.out.println("입력이 잘못되었습니다. 오류 : " + e.toString());
            }
        }
    }

    private static void command(String input) {
        // TODO : 아래 문장을 삭제하고 구현해라.
        String infix = postfixToInfix(input);
        long result = getInfixResult(infix);

        if (result == Long.MIN_VALUE) System.out.println("ERROR");
        else {
            System.out.println(infix);
            System.out.println(result);
        }
    }

    public static Long getInfixResult(String expression) {
        int count = 0;
        long answer = 0;

        String[] op = {"+", "-", "*", "/", "%", "^", "~", " "};
        Stack<Long> stack = new Stack<>();

        char[] e = expression.toCharArray();
        for (int i = 0; i < e.length; i++) {
            if (Arrays.asList(op).contains(e[i] + "")) {
                long op1 = 0, op2 = 0;
                if (e[i] == ' ') continue;
                op2 = stack.pop();
                if (e[i] == '~') {
                    stack.push(op2 * -1);
                    continue;
                } else if (stack.empty())
                    return (Long.MIN_VALUE);
                else
                    op1 = stack.pop();

                switch (e[i]) {
                    case '+':
                        stack.push(op1 + op2);
                        break;
                    case '-':
                        stack.push(op1 - op2);
                        break;
                    case '*':
                        stack.push(op1 * op2);
                        break;
                    case '/':
                        stack.push(op1 / op2);
                        break;
                    case '%':
                        stack.push(op1 % op2);
                        break;
                    case '^':
                        stack.push((long) Math.pow(op1, op2));
                        break;
                }
            } else if (e[i] >= '0' && e[i] <= '9') {
                while (i + count < e.length && e[i + count] != ' ' && e[i + count] >= '0' && e[i + count] <= '9') {
                    count++;
                }
                long value = Long.parseLong(String.valueOf(e[i]));
                for (int k = 1; k < count; k++) {
                    value *= 10;
                    i += 1;
                    value += Long.parseLong(String.valueOf(e[i]));
                }
                stack.push(Long.parseLong(value + ""));
                count = 0;
            }
        }

        answer = stack.pop();
        return answer;
    }

    public static String postfixToInfix(String expression) {
        Queue<String> answer = new LinkedList<>();
        Stack<String> stack = new Stack<>();
        String[] op = {"+", "-", "*", "/", "%", "(", ")", "^", "~", " "};

        int count = 0;
        char[] e = expression.toCharArray();
        for (int i = 0; i < e.length; i++) {
            if (e[i] == '-') {
                boolean result = true;
                for (int j = i - 1; j >= 0; j--) {
                    if (e[j] >= '0' && e[j] <= '9') {
                        result = false;
                        break;
                    } else if (Arrays.asList(op).contains(e[i] + "") && e[j] != ' ') {
                        break;
                    }
                }
                if (result) e[i] = '~';
            }
            if (Arrays.asList(op).contains(e[i] + "")) {
                if (e[i] == ')') {
                    while (!stack.isEmpty() && stack.peek().charAt(0) != '(') {
                        answer.add(Character.toString(stack.pop().charAt(0)));
                        answer.add(" ");
                    }
                    stack.pop();

                } else if (e[i] == ' ') {
                } else {
                    while (!stack.isEmpty() && compareToOperation(e[i], stack.peek().charAt(0))) {
                        answer.add(stack.pop());
                        answer.add(" ");
                    }
                    if (e[i] == '-' && answer.isEmpty() && stack.isEmpty())
                        stack.push("~" + "");
                    else
                        stack.push(e[i] + "");
                }
            } else {
                if (e[i] >= '0' && e[i] <= '9') {
                    while (i + count < e.length && e[i + count] != ' ' && e[i + count] >= '0' && e[i + count] <= '9') {
                        count++;
                    }
                    long value = Long.parseLong(String.valueOf(e[i]));
                    for (int k = 1; k < count; k++) {
                        value *= 10;
                        i += 1;
                        value += Long.parseLong(String.valueOf(e[i]));
                    }
                    answer.add(Long.toString(value));
                    answer.add(" ");
                    count = 0;
                }
            }
        }

        while (!stack.isEmpty()) {
            String c = stack.pop();
            if (c.compareTo("-") == 0 && answer.size() <= 2) {
                answer.add("~");
                answer.add(" ");
            } else {
                answer.add(c);
                answer.add(" ");
            }
        }
        String result = "";
        while (answer.size() > 1)
            result += answer.poll();
        return result;
    }

    public static boolean compareToOperation(char op1, char op2) {
        switch (op1) {
            case '+':
            case '-':
                if (op2 == '+' || op2 == '-' || op2 == '*' || op2 == '/' || op2 == '%' || op2 == '^' || op2 == '~') {
                    return true;
                }

            case '*':
            case '/':
            case '%':
                if (op2 == '*' || op2 == '/' || op2 == '%' || op2 == '^' || op2 == '~') {
                    return true;
                }
            case '^':
            case '~':
                if (op2 == '^' || op2 == '~') {
                    return false;
                }
        }
        return false;
    }
}
