import java.util.Scanner;


public class Main {
    public static void main(String[] args) {
        cal("2-3+11");
        cal("+");
        cal("2+3*2");
        cal("(2+3)*2");
        cal("(2+3))*2");
        cal("2+3<=10");
        cal("2<=4<2");
        cal("-5+2");
        cal("-2-(-1)");
    }

    // 노드 클래스
    // Node class
    public static class Node {
        private String data;
        private Node nextNode;

        // 생성자
        // Constructor
        public Node(String data) {
            this.data = data;
        }

        // 데이터 반환 함수
        // Data getter
        public String getData() {
            return data;
        }

        // 다음 리스트 노드 지정
        // Next node setter
        public void setNextNode(Node nextNode) {
            this.nextNode = nextNode;
        }

        // 다음 리스트 노드 반환 함수
        // Next node getter
        public Node getNextNode() {
            return nextNode;
        }
    }

    // 연결 리스트 스택 클래스
    // Linked list stack class
    public static class LinkedListStack {
        private Node head, tail;

        // 노드 추가
        // push
        public void push(Node newNode) {
            if (isEmpty())
                head = newNode;
            else {
                Node currentTop = head;

                // 꼬리를 찾아서 연결
                // look for tail and link
                while (currentTop.getNextNode() != null)
                    currentTop = currentTop.getNextNode();
                currentTop.setNextNode(newNode);
            }
            tail = newNode;
        }

        // 노드 제거
        // pop
        public Node pop() {
            Node node = tail;

            if (head == tail) {
                head = null;
                tail = null;
            } else {
                Node currentTop = head;


                while (currentTop.getNextNode() != node)
                    currentTop = currentTop.getNextNode();
                tail = currentTop;
                tail.setNextNode(null);
            }
            return node;
        }

        // 최상위 노드 반환
        // peek
        public Node peek() {
            return tail;
        }

        // 빈 스택인지 체크하는 함수
        // check stack is empty
        public boolean isEmpty() {
            return head == null;
        }
    }

    // 계산기 클래스
    // Calculator class
    public static class Calculator {
        // 연산자 선언
        // Operators

        private final char[] NUMBER = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.'};
        private final char OPERAND = 'O';
        private final char LEFT = '(';
        private final char MULTIPLY = '*';
        private final char DIVIDE = '/';
        private final char PLUS = '+';
        private final char MINUS = '-';
        private final char SMALLER = '<';
        private final char BIGGER = '>';
        private final char EQUAL = '=';

        private final char POINT = '.';
        private char[] token;
        private int tokenType;
        private int equal = 0;
        private int relational = 0;

        private LinkedListStack stack;

        public Calculator() {
            stack = new LinkedListStack();
        }

        // 연산자 우선순위를 매기는 함수
        // prioritize operators
        public int getPriority(char operator, boolean inStack) {
            int priority = -1;

            // 소숫점 < 괄호 < 곱셈 나눗셈 < 덧셈 뺄셈 < 비교연산
            switch (operator) {
                case LEFT:
                    // 왼쪽 괄호의 경우 항상 예외로 스택에 넣어준다.
                    // always push in case of left parenthesis
                    if (inStack) priority = 4;
                    else priority = 1;
                    break;
                case MULTIPLY:
                case DIVIDE:
                    priority = 2;
                    break;
                case PLUS:
                case MINUS:
                    priority = 3;
                    break;
                case BIGGER:
                case SMALLER:
                    priority = 6;
                    relational++;
                    break;
                case EQUAL:
                    priority = 5;
                    equal++;
                    break;
                case POINT:
                    priority = 0;
                    break;
            }

            return priority;
        }

        // 토큰과 우선순위 비교하는 함수
        public boolean isPrior(char operatorInToken, char operatorInStack) {
            return (getPriority(operatorInToken, false) < getPriority(operatorInStack, true));
        }

        // 해당 토큰이 숫자인지 판별하는 함수
        public boolean isNumber(char token) {
            for (char c : NUMBER) if (token == c) return true;
            return false;
        }

        // 중위표기식 토크나이징
        // Tokenizing from infix expression
        public int getNextToken(String infixExpression, char[] chrArray) {
            int i = 0;
            infixExpression += ' ';

            // null이 나올때까지 반복
            // repeat until null comes out
            for (i = 0; infixExpression.charAt(i) != 0; i++) {
                // 문자를 하나씩 추출
                // Extract characters one by one
                chrArray[i] = infixExpression.charAt(i);

                // 피연산자이면 타입을 표시
                // if number
                if (isNumber(chrArray[i])) {
                    tokenType = OPERAND;

                    // 만약 피연산자 다음의 문자가 피연산자가 아니라면 중지
                    // Stop if the letter after the operand is not the operand
                    if (!isNumber(infixExpression.charAt(i + 1)))
                        break;
                } else {
                    // 연산자이면 대입
                    // operate
                    tokenType = infixExpression.charAt(i);
                    break;
                }
            }

            // 추출된 토큰을 복사한다.
            // copy tokens
            token = new char[++i];
            System.arraycopy(chrArray, 0, token, 0, i);
            return i;
        }

        // 중위 -> 후위
        // infix -> postfix
        public String getPostfix(String infixExpression) {
            StringBuffer postfixExpression = new StringBuffer();
            int position = 0;
            int length = infixExpression.length();
            char[] chArr = new char[length];
            Node popped;

            while (position < length) {
                // position 위치부터 토큰을 하나씩 가져온다.
                // get token from position
                position += getNextToken(infixExpression.substring(position), chArr);

                 if (tokenType == OPERAND) {
                    postfixExpression.append(token);
                    postfixExpression.append(' ');
                } else {
                     // 연산자가 오른쪽 괄호 ')' 라면 스택에서 '('가 나올때까지 제거연산 수행
                     // repeat pop until ')' comes out
                    if (tokenType == ')') {
                        if (stack.isEmpty()) {
                            return " ";
                        }
                        while (!stack.isEmpty()) {
                            popped = stack.pop();

                            // 제거한 노드가 '(' 라면 중지
                            // stop if popped '('
                            if (popped.getData().charAt(0) == LEFT)
                                break;
                            else
                                postfixExpression.append(popped.getData());
                        }
                    }
                    // 나머지 연산자의 경우 토큰의 우선순위가 스택의 top보다 낮을 경우 제거연산 수행.
                    // 제거연산은 토큰의 우선순위보다 낮은 노드가 나올때까지 수행(같은 거라도 수행)
                    // For the remaining operators, perform the remove operation if the priority of the token is lower than the top of the stack.
                    // The removal operation is performed until a node below the priority of the token comes out (even if it is the same)
                    else {
                        // 스택이 비어있지 않고 토큰의 우선순위가 스택의 top보다 낮다면
                        // If the stack is not empty and the token has a lower priority than the top of the stack
                        while (!stack.isEmpty()
                                && !isPrior(token[0], stack.peek().getData()
                                .charAt(0))) {
                            // 제거연산 수행
                            // pop
                            popped = stack.pop();

                            // '(' 빼고 모두 출력
                            // append without '('
                            if (popped.getData().charAt(0) != LEFT)
                                postfixExpression.append(popped.getData());
                        }
                        // 토큰의 우선순위가 스택의 top보다 높다면 삽입연산 수행
                        // If the priority of the token is higher than the top of the stack, perform the insert operation
                        stack.push(new Node(String.valueOf(token)));
                    }
                }
            }
            // 스택에 남아 있는 노드들을 제거
            // remove nodes in stack
            while (!stack.isEmpty()) {
                popped = stack.pop();

                if (popped.getData().charAt(0) != LEFT)
                    postfixExpression.append(popped.getData());
            }

            // 등호가 2개 이상, 부등호가 2개 이상, 등호가 부등호보다 많으면 고려하지 않는 경우
            // not considered case
            if (equal > 2 || relational > 2 || (equal > relational))
                return null;
            return postfixExpression.toString();
        }

        // 계산
        // calculate
        String calculate(String postfixExpression) {
            int position = 0;
            int length = postfixExpression.length();
            char[] chrArr = new char[length];
            String result = null;

            double operand1, operand2;
            LinkedListStack stack = new LinkedListStack();

            while (position < length) {
                position += getNextToken(postfixExpression.substring(position),
                        chrArr);
                // 공백은 무시
                // ignore whitespace
                if (tokenType == ' ')
                    continue;
                // 피연산자이면 스택에 삽입
                // push if operand
                if (tokenType == OPERAND) {
                    stack.push(new Node(String.valueOf(token)));
                } else {
                    if (stack.isEmpty())
                        return null;
                    // 연산자이면 스택에서 제거
                    // pop from stack if operator
                    operand2 = Double.parseDouble(stack.pop().getData());

                    // 다음 연산자가 '-'이면 음수화
                    // negative if next operator is '-'
                    if (position < length && postfixExpression.charAt(position) == '-') {
                        operand2 = operand2 * -1;
                        position++;
                    }
                    if (stack.isEmpty()) {
                        // 피연산자가 1개이고, 연산자가 '-'이면 음수화
                        // negative if there is one operand
                        if (tokenType == MINUS)
                            result = String.valueOf(operand2 * -1);
                    } else {
                        operand1 = Double.parseDouble(stack.pop().getData());

                        // 연산
                        // operate
                        switch (tokenType) {
                            case MULTIPLY:
                                result = String.valueOf(operand1 * operand2);
                                break;
                            case DIVIDE:
                                result = String.valueOf(operand1 / operand2);
                                break;
                            case PLUS:
                                result = String.valueOf(operand1 + operand2);
                                break;
                            case MINUS:
                                result = String.valueOf(operand1 - operand2);
                                break;
                            case EQUAL:
                                // 등호이면 다음 연산자가 어떤 비교연산자인지 확인
                                // check next relational operator
                                position += getNextToken(postfixExpression.substring(position),
                                        chrArr);
                                if (tokenType == BIGGER)
                                    result = String.valueOf(operand1 >= operand2);
                                else if (tokenType == SMALLER)
                                    result = String.valueOf(operand1 <= operand2);
                                break;
                            case BIGGER:
                                result = String.valueOf(operand1 > operand2);
                            case SMALLER:
                                result = String.valueOf(operand1 < operand2);
                        }
                    }
                    stack.push(new Node(String.valueOf(result)));
                }
            }
            return result;
        }
    }

    public static void cal(String s) {
        Calculator c = new Calculator();
        Scanner sc = new Scanner(System.in);

        String infixExpression, postfixExpression;
        double result = 0.0;

        System.out.println("Input: " + s);
        postfixExpression = c.getPostfix(s);

        // 비교 연산 여러개
        // not considered case
        if (postfixExpression == null) {
            System.out.println("The above examples are not considered.");
            return;
        }

        // 올바르지 않은 식 또는 비교 연산
        // not normal expression or comparison
        String rst = c.calculate(postfixExpression);
        if (rst == null) {
            System.out.println("Output: studentID pa1 p3 null");
            return;
        } else if (rst.equals("true")) {
            System.out.println("Output: studentID pa1 p3 true");
            return;
        } else if (rst.equals("false")) {
            System.out.println("Output: studentID pa1 p3 false");
            return;
        }
        result = Double.parseDouble(rst);

        // 정수일 경우
        // case of integer result
        if (result % 1 == 0.0)
            System.out.println("Output: studentID pa1 p3 " + (int) result);
        else
            System.out.println("Output: studentID pa1 p3 " + result);
    }
}
