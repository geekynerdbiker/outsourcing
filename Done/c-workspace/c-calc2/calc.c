#include <math.h>
#include <stdio.h>
#include <string.h>
#include "calc.h"
#include "queue.h"
#include "stack.h"

// ������ ��ȿ�� �� �˻�
int isInvalidExpression(char str[]) {
    int count = 0; // �̿ϼ��� ��ȣ ��

    for (int i = 0; i < strlen(str); i++) {
        char ch = str[i];

        // �� ��ȣ �Է�
        if (strcmp(str, "()") == 0) {
            printf("�� ��ȣ�� �ԷµǾ����ϴ�.\n");
            return 1;
        }

        // ���� �ڿ� �ٷ� ��ȣ�� ���� ��� ex) 12(12)
        if ((ch >= '0' && ch <= '9') && str[i + 1] == '(') {
            printf("�ùٸ��� ���� �����Դϴ�.\n");
            return 1;
        }

        // ����, ������ �� �Է�
        if (!((ch >= '0' && ch <= '9') || isOperator(ch) || ch == ' ')) {
            printf("��ȿ���� ���� ��: %c\n", ch);
            return 1;
        }

        // ���� ������ �Է� ex) +1, 1+(-1)
        if ((str[0] == '+' || str[0] == '-') || ((ch == '+' || ch == '-') && i > 0 && isOperator(str[i - 1]) && str[i - 1] != ')')) {
            printf("���� �����ڰ� ���Ǿ����ϴ�.\n");
            return 1;
        }

        // �߸��� ������ �Է� ex) 1++1, 2**5
        if (isOperator(str[i]) && isOperator(str[i + 1]) && str[i] != '(' && str[i] != ')' && str[i + 1] != '(' && str[i + 1] != ')') {
            printf("�����ڰ� �������� ���Ǿ����ϴ�.\n");
            return 1;
        }

        // �ùٸ��� ���� ��ȣ ex) (1+1)), )(1+1)
        if (ch == '(') count++;
        else if (ch == ')') {
            count--;
            if (count < 0) {
                printf("��ȣ�� �ùٸ��� �ʽ��ϴ�.\n");
                return 1;
            }
        }

    }

    // �ùٸ��� ���� ��ȣ (���� ���� ���)
    if (count != 0) {
        printf("��ȣ�� �ùٸ��� �ʽ��ϴ�.\n");
        return 1;
    }

    // ������ �Է� ������ ex) 1+2+3+
    if (isOperator(str[strlen(str) - 1]) && str[strlen(str) - 1] != ')') {
        printf("������ �Է��� �������Դϴ�.\n");
        return 1;
    }

    return 0;
}


// ������ �Ǵ�
int isOperator(char ch) {
    return ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '%' || ch == '^' || ch == '(' || ch == ')';
}

// �Է� ������ ����
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

// �Էµ� �������� �켱���� ��ȯ(���ڰ� ���� ���� �켱���� ����)
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

// �Էµ� ���������� ������������ ��ȯ
Queue infixToPostfix(char infix[]) {
    Stack stack = initStack(); // ������ ���� ����
    Queue postfix = initQueue(); // ��ȯ�� ���� ����
    int value;
    int infix_len = strlen(infix);

    for (int i = 0; i < infix_len; i++) {
        // ���Ŀ� ���Ե� ������ ����
        if (infix[i] == ' ') continue;
        int ch = (int)(infix[i]);

        // ������ �� ���
        if (isOperator(ch)) {
            // ��ȣ ���
            if (ch == '(') {
                push(&stack, ch);
            }
            else if (ch == ')') { // ���� ��ȣ ���� �� ��ȣ �� ������ ��� ����
                while (stack.items[stack.top] != '(') {
                    value = pop(&stack);
                    enqueue(&postfix, value, 1);
                }
                pop(&stack);
            }
            // ��ȣ�� �ƴ� ������
            else {
                while (stack.top >= 0 && precedence(stack.items[stack.top]) >= precedence(ch)) {
                    // �������� ������ ��������� �ݴ�����̹Ƿ� ���߿� ���� ex) 4^3^2 = 4^9 (4^3�� ���� ����ϴ°� �ƴ� 3^2 ���� ���)
                    if (ch == '^') break;
                    value = pop(&stack);
                    enqueue(&postfix, value, 1);
                }
                push(&stack, ch);
            }
        }
        // �ǿ������� ���
        else {
            int num = (int)(ch - '0');
            // 1234���� �����ڸ� ���� ��ȯ
            while (!isOperator(infix[i + 1]) && i < infix_len - 1 && infix[i + 1] != ' ') {
                num *= 10;
                num += (int)(infix[i + 1] - '0');
                i++;
            }
            enqueue(&postfix, num, 0);
        }
    }

    // ���� ������ ��� ����
    while (!isStackEmpty(&stack)) {
        int value = (int)(pop(&stack));
        enqueue(&postfix, value, 1);
    }

    return postfix;
}

// ���� ��(���)
void evaluate(char infix[]) {
    // ������ �ùٸ��� Ȯ��
    if (isInvalidExpression(infix)) return;

    int result;
    int a, b;
    Stack stack = initStack(); // �߰� ��갪 ����� ���� ����
    Node node;
    Queue postfix = infixToPostfix(infix); // ��ȯ�� �������� ť

    // ť �� ��� ��ȸ
    while (!isQueueEmpty(&postfix)) {
        node = dequeue(&postfix);
        // ��尡 �������� ��
        if (node.type == 1) {
            b = pop(&stack); // �� �� ����
            a = pop(&stack); // �� ���� ����

            // 0���� ������ ��쿡 ���� ����ó��
            if (((char)(node.element) == '/' || (char)(node.element) == '%') && b == 0) {
                printf("0���� ���� �� �����ϴ�.\n");
                return;
            }

            result = doOperator((char)(node.element), a, b); // ���
            push(&stack, result);
        }
        // ��尡 �ǿ������� �� ���ÿ� push
        else {
            push(&stack, node.element);
        }
    }

    // ����� �������� ť �޸� ����
    destroyQueue(&postfix);

    // ����� ���
    printf("result: %d\n", stack.items[0]);
}