import java.io.*;

public class CalculatorTest {
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
        System.out.println("<< command 함수에서 " + input + " 명령을 처리할 예정입니다 >>");

        String prefix, *postfix;
        double result;

        printf("중위식을 입력하세요: ");
        scanf("%s", buf);
        fflush(stdin);

        if (syntaxsearch(buf) != -1) {
            prefix = infix_to_prefix(buf);
            prefix = reverse(prefix);
            postfix = infix_to_postfix(buf);
            result = eval(postfix);

            printf("전위식: %s\n", prefix);
            printf("후위식 : %s\n", postfix);
            printf("계산결과: %.8lf\n", result);
        }
        return 0;
    }

    double eval(char*exp) {
        double opr1, opr2;
        double value;
        int i = 0, count = 0;
        unsigned long length = strlen(exp);
        char symbol;

        for (i = 0; i < length; i++) {
            symbol = exp[i];

            if ((symbol >= '0' && symbol <= '9') || symbol == '.') {
                while (exp[i + count] != ' ') {
                    count++;
                }
                value = atof( & exp[i]);
                i += count;
                count = 0;
                push(value);
            } else {
                if (symbol != ' ') {
                    opr2 = pop();
                    opr1 = pop();

                    switch (symbol) {
                        case '+':
                            push(opr1 + opr2);
                            break;
                        case '-':
                            push(opr1 - opr2);
                            break;
                        case '*':
                            push(opr1 * opr2);
                            break;
                        case '/':
                            push(opr1 / opr2);
                            if (opr2 == 0) return -999;
                            break;
                    }
                }
            }
        }
        return pop();
    }

    void postfix_case_bloack(char*postfix, int*p) {
        char temp;

        while (1) {
            temp = (char) pop();

            if ((temp != '(')) {
                postfix[( * p)++] =temp;
                postfix[( * p)++] =' ';
            } else {
                break;
            }
        }
    }

    void postfix_case_operator_1(char*postfix, char symbol, int*p) {
        char temp;

        while (1) {
            if (top == NULL) {
                break;
            }
            temp = (char) pop();

            if (temp == '+' || temp == '-' || temp == '*' || temp == '/') {
                postfix[( * p)++] =temp;
                postfix[( * p)++] =' ';
            } else {
                push(temp);
                break;
            }
        }
        push(symbol);
    }

    void postfix_case_operator_2(char*postfix, char symbol, int*p) {
        char temp;

        while (1) {
            if (top == NULL) {
                break;
            }
            temp = (char) pop();

            if (temp == '*' || temp == '/') {
                postfix[( * p)++] =temp;
                postfix[( * p)++] =' ';
            } else {
                push(temp);
                break;
            }
        }
        push(symbol);
    }

    void postfix_case_default(char*postfix, char symbol, char*exp, int*p, int i) {
        postfix[( * p)++] =symbol;

        if (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '*' || exp[i + 1] == '/' ||
                exp[i + 1] == ')' || exp[i + 1] == '\0') {
            postfix[( * p)++] =' ';
        }
    }

    char*

    infix_to_postfix(char*exp) {
        int i = 0, p = 0;
        unsigned long length = strlen(exp);
        char symbol;
        char*postfix = ( char*)malloc(length * 2);

        for (i = 0; i < length; i++) {
            symbol = exp[i];

            switch (symbol) {
                case '(':
                    push(symbol);
                    break;

                case ')':
                    postfix_case_bloack(postfix, & p);
                    break;

                case '+':
                case '-':
                    postfix_case_operator_1(postfix, symbol, & p);
                    break;

                case '*':
                case '/':
                    postfix_case_operator_2(postfix, symbol, & p);
                    break;

                default:
                    postfix_case_default(postfix, symbol, exp, & p, i);
                    break;
            }
        }

        while (top) {
            postfix[p++] = (char) pop();
            postfix[p++] = ' ';
        }
        postfix[p] = '\0';
        return postfix;
    }

    int syntaxsearch(char*exp) {
        unsigned long length = strlen(exp);
        int i = 0;
        int ncount = 0;
        char symbol, opr;

        for (i = 0; i < length; i++) {
            symbol = exp[i];

            switch (symbol) {
                case '+':
                case '-':
                case '*':
                case '/':
                    opr = exp[i + 1];
                    if (opr == '+' || opr == '-' || opr == '*' || opr == '/') {
                        return -1;
                    }
                    break;

                case '(':
                    push(symbol);
                    break;

                case ')':
                    if (top == NULL) {
                        return -1;
                    } else {
                        if (pop() != '(') {
                            return -1;
                        }
                    }
                    break;

                default:
                    if ((symbol >= '0' && symbol <= '9') || symbol == '.') {
                        ncount++;
                    } else {
                        return -1;
                    }
                    break;
            }
        }
        if (!ncount || ncount == 1) {
            return -1;
        }
        while (top) {
            opr = (char) pop();
            if (opr == '(' || opr == '+' || opr == '-' || opr == '*' || opr == '/') {
                return -1;
            }
        }
        return 0;
    }
}
