#pragma warning(disable:4996)

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char binaryops[7] = { '+', '-', '*', '/', '&', '|', '^' };
char unaryops[1] = { '-' };
int numofunaryop = 2;

int complexity = 0;
int is_arithmetic = 0;
typedef struct node
{
    char* op;
    struct node* lefthand;
    struct node* righthand;
} Node;

Node* newNode(char* op, Node* lefthand, Node* righthand)
{
    Node* n = (Node*)malloc(sizeof(Node));
    n->op = (char*)malloc(sizeof(char) * 11);

    strcpy(n->op, op);
    n->lefthand = lefthand;
    n->righthand = righthand;

    return n;
}

Node* base_parser(char* prefix_expr)
{
    if (!prefix_expr || *prefix_expr == '\0')
        return NULL;

    char* op = strtok(prefix_expr, " ");
    char* op1 = strtok(NULL, " ");
    char* op2 = strtok(NULL, " ");

    if (!op2) {
        return newNode(op, NULL, newNode(op1, NULL, NULL));
    }

    return newNode(op, newNode(op1, NULL, NULL), newNode(op2, NULL, NULL));
}

int is_operator(char c) {
    for (int i = 0; i < sizeof(binaryops); ++i) {
        if (c == binaryops[i])
            return 1;
    }
    return 0;
}

Node* parser(char* prefix_expr)
{
    if (!prefix_expr || *prefix_expr == '\0')
        return NULL;

    // 토큰을 저장할 버퍼 (연산자 또는 피연산자)
    char token[11];
    int i = 0;

    // 전위 표기법 수식에서 첫 번째 토큰 읽기
    sscanf(prefix_expr, "%s", token);

    // 여는 괄호일 경우 무시하고 다음 칸 파싱
    if (token[0] == '(') {
        return parser(prefix_expr + strlen(token) + 1);
    }

    // 괄호가 닫히면 항 종료.
    if (token[0] == ')')
        return NULL;

    // 토큰이 연산자인지 확인
    int is_op = is_operator(token[0]);

    // 연산자인 경우
    if (is_op) {
        // 왼쪽과 오른쪽 피연산자의 위치 포인터를 각각 저장.
        char* left_expr = prefix_expr + strlen(token) + 1;
        char* right_expr = prefix_expr + strlen(token) + strlen(token) + 2;

        // 왼쪽 피연산자 파싱
        Node* left = parser(prefix_expr + strlen(token) + 1);

        // 파싱한 왼쪽 피연산자가 괄호 열림 기호이면
        if ((*left_expr) == '(') {
            int paren = 0;
            // 오른쪽 피연산자 다음 괄호 닫힘 기호까지 이동 
            while (*right_expr) {
                if ((*right_expr) == '(')
                    paren++;
                else if ((*right_expr) == ')' && paren != 0)
                    paren--;
                else if ((*right_expr) == ')' && paren == 0)
                    break;
                right_expr++;
            }
            right_expr++;
        }

        // 오른쪽 피연산자가 공백이 아닐 때 까지 이동
        while (*right_expr && (*right_expr) == ' ')
            right_expr++;
        // 찾은 오른쪽 피연산자 파싱
        Node* right = parser(right_expr);

        // 파싱한 오른쪽 피연산자가 없으면 (단항)
        if (!right)
            // 왼쪽 피연산자를 오른쪽 자식에 저장하고, 왼쪽 자식은 NULL 할당
            return newNode(token, NULL, left);
        // 피연산자가 2개이면 왼쪽 오른쪽 자식 저장
        return newNode(token, left, right);
    }
    else {
        // 연산자가 아니라면 피연산자일 것이므로 노드를 생성하고 반환
        // 단항 연산자의 경우 왼쪽 자식은 NULL이어야 한다
        return newNode(token, NULL, NULL);;
    }
}



void pre2in(Node* root)
{
    if (root != NULL)
    {
        pre2in(root->lefthand);
        printf("%s ", root->op);
        pre2in(root->righthand);
    }
}


int is_booleanOp(char* str)
{
    if (strcmp(str, "&") == 0 || strcmp(str, "|") == 0 || strcmp(str, "^") == 0) {
        return 1; // Boolean Operator인 경우
    }
    return 0;
}

int is_arithmeticOp(char* str)
{
    if (strcmp(str, "+") == 0 || strcmp(str, "-") == 0 ||
        strcmp(str, "*") == 0 || strcmp(str, "/") == 0) {
        return 1; // Arithmetic Operator인 경우
    }
    return 0; // 아닌 경우
}

void calc_complexity(struct node* root)
{
    if (root == NULL)
        return;

    if (is_arithmetic == 0) {
        if (is_arithmeticOp(root->op))
            is_arithmetic = 1;
        else if (is_booleanOp(root->op))
            is_arithmetic = -1;
        complexity++;
    }

    // 왼쪽 서브트리 처리
    calc_complexity(root->lefthand);

    // 현재 노드 연산자 처리
    if (is_arithmeticOp(root->op) && is_arithmetic == -1) {
        complexity += 1; // Arithmetic Operator
        is_arithmetic = 1;
    }
    else if (is_booleanOp(root->op) && is_arithmetic == 1) {
        complexity += 1; // Boolean Operator
        is_arithmetic = -1;
    }

    // 오른쪽 서브트리 처리
    calc_complexity(root->righthand);
}

// Hexadecimal to Integer 변환 함수
int hex_to_int(char* hex)
{
    // 0x 제거 후 16진수 문자열을 10진수로 변환
    return (int)strtol(hex + 2, NULL, 16);
}

// 변수 값 입력 함수
int get_variable_value(char var)
{
    int value;
    printf("Enter the value of '%c': ", var);
    scanf("%d", &value);
    return value;
}

int calc_MBA(struct node* root)
{
    if (root == NULL)
        return 0;

    // 연산자인 경우
    if (is_arithmeticOp(root->op) || is_booleanOp(root->op)) {
        int left_val = calc_MBA(root->lefthand);
        int right_val = calc_MBA(root->righthand);

        if (strcmp(root->op, "+") == 0)
            return left_val + right_val;
        else if (strcmp(root->op, "-") == 0) {
            // Unary '-' 처리
            if (root->lefthand == NULL)
                return -right_val;
            else
                return left_val - right_val;
        }
        else if (strcmp(root->op, "*") == 0)
            return left_val * right_val;
        else if (strcmp(root->op, "/") == 0) {
            // Division by zero 오류 확인
            if (right_val == 0) {
                printf("Error: Division by zero!\n");
                exit(EXIT_FAILURE);
            }
            return left_val / right_val;
        }
        else if (strcmp(root->op, "&") == 0)
            return left_val & right_val;
        else if (strcmp(root->op, "|") == 0)
            return left_val | right_val;
        else if (strcmp(root->op, "^") == 0)
            return left_val ^ right_val;
    }
    // 피연산자인 경우
    else {
        // 16진수인 경우 변환
        if (strncmp(root->op, "0x", 2) == 0)
            return hex_to_int(root->op);
        // 미지수 x, y, z 입력 받기
        else if (strcmp(root->op, "x") == 0 || strcmp(root->op, "y") == 0 || strcmp(root->op, "z") == 0)
            return get_variable_value(root->op[0]); // 변수명의 첫 번째 문자
        // 일반 상수인 경우
        else
            return atoi(root->op); // 문자열을 정수로 변환
    }

    return 0; // 예외 처리
}

// 메모리 해제 함수 정의
void free_tree(Node* root)
{
    if (root == NULL)
        return;

    free_tree(root->lefthand);
    free_tree(root->righthand);
    free(root->op);
    free(root);
}

int main()
{
    //char prefix_expr[] = "+ ( - 1 ) ( + 1 1 )";
    //char prefix_expr[] = "+ 1 ( - ( + 1 2 ) x )";
    char prefix_expr[] = "+ ( & ( - x y ) ( - 0 ) ) ( | 1 2 )";

    // 수식 파싱
    Node* root = parser(prefix_expr);

    // 중위 순회 출력
    printf("Inorder traversal: ");
    pre2in(root);
    printf("\n");

    // 복잡도 계산
    calc_complexity(root);
    printf("Complexity: %d\n", complexity);

    // MBA 수식 계산
    int result = calc_MBA(root);
    printf("Result: %d\n", result);

    free_tree(root);
    return 0;
}
