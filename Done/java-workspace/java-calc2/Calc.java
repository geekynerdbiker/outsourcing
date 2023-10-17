import java.io.IOException;
import java.io.PushbackInputStream;

class Calc {
    int token;
    int value;
    int ch;
    private PushbackInputStream input;
    final int NUMBER = 256;

    Calc(PushbackInputStream is) {
        input = is;
    }

    int getToken() { /* tokens are characters */
        while (true) {
            try {
                ch = input.read();
                if (ch == ' ' || ch == '\t' || ch == '\r') ;
                else {
                    if (Character.isDigit(ch)) {
                        value = number();
                        input.unread(ch);
                        return NUMBER;
                    } else return ch;
                }
            } catch (IOException e) {
                System.err.println(e);
            }
        }
    }

    private int number() {
        /* number -> digit { digit } */
        int result = ch - '0';
        try {
            ch = input.read();
            while (Character.isDigit(ch)) {
                result = 10 * result + ch - '0';
                ch = input.read();
            }
        } catch (IOException e) {
            System.err.println(e);
        }
        return result;
    }

    void error() {
        System.out.printf("parse error : %d\n", ch);
        //System.exit(1);
    }

    void match(int c) {
        if (token == c)
            token = getToken();
        else error();
    }

    void command() {
        /* command -> expr '\n' */
        Object result = expr(); // 부호 우선순위 상 expr() 먼저 호출
        if (token == '\n') /* end the parse and print the result */
            System.out.println("The result is: " + result);
        else error();
    }

    Object expr() {
        Object result = null;
        if (token == '!') { // not 연산
            match('!');
            result = !(boolean) expr(); // 식 결과값 반전
        } else if (token == 't') { // true
            match('t');
            if (token == 'r') {
                match('r');
                if (token == 'u') {
                    match('u');
                    if (token == 'e') {
                        match('e');
                        result = true;
                    }
                }
            }
        } else if (token == 'f') { // false
            match('f');
            if (token == 'a') {
                match('a');
                if (token == 'l') {
                    match('l');
                    if (token == 's') {
                        match('s');
                        if (token == 'e') {
                            match('e');
                            result = false;
                        }
                    }
                }
            }
        } else {
            result = bepx();
            while (token == '&' || token == '|') {
                switch (token) {
                    case '&': // & 부호
                        match('&');
                        result = (boolean) bepx() && (boolean) result;
                        break;
                    case '|': // | 부호
                        match('|');
                        result = (boolean) bepx() || (boolean) result;
                        break;
                }
            }
        }

        return result;
    }

    Object bepx() { // 비교 연산자
        Object result = aepx(); // 부호 연산 후 비교
        switch (relop()) {
            case "==":
                if ((int) result == aepx()) {
                    result = true;
                } else {
                    result = false;
                }
                break;
            case "!=":
                if ((int) result == aepx()) {
                    result = false;
                } else {
                    result = true;
                }
                break;
            case "<":
                if ((int) result < aepx()) {
                    result = true;
                } else {
                    result = false;
                }
                break;
            case ">":
                if ((int) result > aepx()) {
                    result = true;
                } else {
                    result = false;
                }
                break;
            case "<=":
                if ((int) result <= aepx()) {
                    result = true;
                } else {
                    result = false;
                }
                break;
            case ">=":
                if ((int) result >= aepx()) {
                    result = true;
                } else {
                    result = false;
                }
                break;
        }
        return result;
    }

    String relop() {
        String result = "";
        if (token == '=') {
            match('=');
            if (token == '=') {
                match('=');
                result = "==";
            }
        } else if (token == '!') {
            match('!');
            if (token == '=') {
                match('=');
                result = "!=";
            }
        } else if (token == '<') {
            match('<');
            if (token == '=') {
                match('=');
                result = "<=";
            } else {
                result = "<";
            }
        } else if (token == '>') {
            match('>');
            if (token == '=') {
                match('=');
                result = ">=";
            } else {
                result = ">";
            }
        }
        return result;
    }


    int aepx() {
        /* expr -> term { '+' term } */
        int result = term();
        while (token == '+' || token == '-') { // 덧셈, 뺄셈.
            switch (token) {
                case '+':
                    match('+');
                    result += term();
                    break;
                case '-':
                    match('-');
                    result -= term();
                    break;
            }
        }

        return result;
    }

    int term() {
        /* term -> factor { '*' factor } */
        int result = factor();
        while (token == '*' || token == '/') { // 곱셈, 나눗셈.
            switch (token) {
                case '*':
                    match('*');
                    result *= factor();
                    break;
                case '/':
                    match('/');
                    result /= factor();
                    break;
            }
        }
        return result;
    }

    int factor() {
        /* factor -> '(' expr ')' | number */
        int result = 0;
        if (token == '(') { // 괄호 연산. 스택 사용하려 했으나 안배운 것 같아서 괄호 열고 계산 후 닫는 방식 채택.
            match('(');
            result = aepx();
            match(')');
        } else if (token == NUMBER) {
            result = value;
            match(NUMBER); //token = getToken();
        }

        return result;
    }

    void parse() {
        token = getToken(); // get the first token
        command();          // call the parsing command
    }

    public static void main(String args[]) {
        Calc calc = new Calc(new PushbackInputStream(System.in));
        while (true) {
            System.out.print(">> ");
            calc.parse();
        }
    }
}