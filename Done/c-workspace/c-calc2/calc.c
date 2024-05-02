#include <math.h>
#include <stdio.h>
#include <string.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

// 수식이 유효한 지 검사
int isInvalidExpression(char str[]) {
    int count = 0; // 미완성된 괄호 수

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];

        // 빈 괄호 입력
        if (strcmp(str, "()") == 0) {
            printf("빈 괄호가 입력되었습니다.\n");
            return 1;
        }

        // 숫자 뒤에 바로 괄호가 오는 경우 ex) 12(12)
        if ((ch >= '0' && ch <= '9') && str[i + 1] == '(') {
            printf("올바르지 않은 수식입니다.\n");
            return 1;
        }

        // 숫자, 연산자 외 입력
        if (!((ch >= '0' && ch <= '9') || isOperator(ch) || ch == ' ')) {
            printf("유효하지 않은 값: %c\n", ch);
            return 1;
        }

        // 단항 연산자 입력 ex) +1, 1+(-1)
        if ((str[0] == '+' || str[0] == '-') || ((ch == '+' || ch == '-') && i > 0 && isOperator(str[i - 1]) && str[i - 1] != ')')) {
            printf("단항 연산자가 사용되었습니다.\n");
            return 1;
        }

        // 잘못된 연산자 입력 ex) 1++1, 2**5
        if (isOperator(str[i]) && isOperator(str[i + 1]) && str[i] != '(' && str[i] != ')' && str[i + 1] != '(' && str[i + 1] != ')') {
            printf("연산자가 연속으로 사용되었습니다.\n");
            return 1;
        }

        // 올바르지 않은 괄호 ex) (1+1)), )(1+1)
        if (ch == '(') count++;
        else if (ch == ')') {
            count--;
            if (count < 0) {
                printf("괄호가 올바르지 않습니다.\n");
                return 1;
            }
        }

    }

    // 올바르지 않은 괄호 (위와 같이 사용)
    if (count != 0) {
        printf("괄호가 올바르지 않습니다.\n");
        return 1;
    }

    // 마지막 입력 연산자 ex) 1+2+3+
    if (isOperator(str[strlen(str) - 1]) && str[strlen(str) - 1] != ')') {
        printf("마지막 입력이 연산자입니다.\n");
        return 1;
    }

    return 0;
}


// 연산자 판단
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')';
}

// 입력 연산자 수행
int doOperator(char op, int x, int y) {
    switch (op) {
    case '+': return x + y;
    case '-': return x - y;
    case '*': return x * y;
    case '/': return x / y;
    case '%': return x % y;
    case '^': return (int)(pow(x, y));
    default: return 0;
    }
}

// 입력된 연산자의 우선순위 반환(숫자가 높을 수록 우선순위 높음)
int precedence(char op) {
    switch (op) {
    case '(':
        return 0;
    case '+':
    case '-':
        return 1;
    case '*':
    case '/':
    case '%':
        return 2;
    case '^':
        return 3;
    default:
        return -1;
    }

}

// 입력된 중위수식을 후위수식으로 변환
Queue infixToPostfix(char infix[]) {
    Stack stack = initStack(); // 연산자 저장 스택
    Queue postfix = initQueue(); // 변환된 후위 수식
    int value;
    int infix_len = strlen(infix);

    for (int i = 0; i < infix_len; i++) {
        // 수식에 포함된 공백은 무시
        if (infix[i] == ' ') continue;
        int ch = (int)(infix[i]);

        // 연산자 일 경우
        if (isOperator(ch)) {
            // 괄호 계산
            if (ch == '(') {
                push(&stack, ch);
            }
            else if (ch == ')') { // 닫힌 괄호 나올 시 괄호 내 연산자 모두 삽입
                while (stack.items[stack.top] != '(') {
                    value = pop(&stack);
                    enqueue(&postfix, value, 1);
                }
                pop(&stack);
            }
            // 괄호가 아닌 연산자
            else {
                while (stack.top >= 0 && precedence(stack.items[stack.top]) >= precedence(ch)) {
                    // 연속적인 제곱의 연산순서는 반대방향이므로 나중에 삽입 ex) 4^3^2 = 4^9 (4^3을 먼저 계산하는게 아닌 3^2 먼저 계산)
                    if (ch == '^') break;
                    value = pop(&stack);
                    enqueue(&postfix, value, 1);
                }
                push(&stack, ch);
            }
        }
        // 피연산자일 경우
        else {
            int num = (int)(ch - '0');
            // 1234같은 여러자리 숫자 변환
            while (!isOperator(infix[i + 1]) && i < infix_len - 1 && infix[i + 1] != ' ') {
                num *= 10;
                num += (int)(infix[i + 1] - '0');
                i++;
            }
            enqueue(&postfix, num, 0);
        }
    }

    // 남은 연산자 모두 삽입
    while (!isStackEmpty(&stack)) {
        int value = (int)(pop(&stack));
        enqueue(&postfix, value, 1);
    }

    return postfix;
}

// 수식 평가(계산)
void evaluate(char infix[]) {
    // 수식이 올바른지 확인
    if (isInvalidExpression(infix)) return;

    int result;
    int a, b;
    Stack stack = initStack(); // 중간 계산값 결과들 저장 스택
    Node node;
    Queue postfix = infixToPostfix(infix); // 변환된 후위수식 큐

    // 큐 내 노드 순회
    while (!isQueueEmpty(&postfix)) {
        node = dequeue(&postfix);
        // 노드가 연산자일 시
        if (node.type == 1) {
            b = pop(&stack); // 맨 위 원소
            a = pop(&stack); // 그 다음 원소

            // 0으로 나누는 경우에 대한 예외처리
            if (((char)(node.element) == '/' || (char)(node.element) == '%') && b == 0) {
                printf("0으로 나눌 수 없습니다.\n");
                return;
            }

            result = doOperator((char)(node.element), a, b); // 계산
            push(&stack, result);
        }
        // 노드가 피연산자일 시 스택에 push
        else {
            push(&stack, node.element);
        }
    }

    // 사용한 후위수식 큐 메모리 해제
    destroyQueue(&postfix);

    // 계산결과 출력
    printf("result: %d\n", stack.items[0]);
}