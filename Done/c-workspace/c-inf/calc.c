#include "calc.h"

int main(int argc, char* argv[]){
	// 파일 입력받아서 연결리스트 저장받기
	char ch;
	pList expr = makeList();
	FILE *pFile = NULL;
	pFile = fopen(argv[1], "r");
	
    if(pFile != NULL)
	{
		ch = fgetc(pFile);
		insertBack(expr,makeNode(ch));
		while(EOF != (ch = fgetc(pFile)) && ch != 10) {
			insertBack(expr,makeNode(ch));
		}
	}
	fclose(pFile);
	
	printf("====== Welcome to infinite calculator! ======\n");
	printf("Enter the expression in infix notation.\n");
	printf("Input : ");
	printList(expr);
	
	if (check(expr))
	{
		// 중위표기식 다듬기
		change(expr);
		// 중위표기식을 후위표기식으로 변환
		pList pos = postfix(expr);
		
		// 후위표기식을 계산
		pList answer = seccalc(pos);
		
		printf("Result : ");
		printList(answer);
	}
	else {
		printf("wrong expression\n");
	}
	
    return 0;
}

// 입력이 올바른지 확인
int check(pList expr){
    int dot = 0;
    int space = 0;
    int operator = 0;
    int left = 0;
    int right = 0;
    int count = 0;
    pNode curr = expr->head;
    
    if (curr->data == '.' || curr->data == ' ' || curr->data == '*') return 0;
    while(curr != NULL) {
        count++;
        if (!(isdigit(curr->data) || curr->data == ' ' || curr->data == '.' || curr->data == '(' || curr->data == ')' || curr->data == '+' || curr->data == '-' || curr->data == '*')) return 0;
        if (curr->data == '.') {
            dot++;
            if (curr->next == NULL || !isdigit(curr->next->data)) return 0;
            if (dot >= 2) return 0;
        }
        if (curr->data == ' ') {
            dot = 0;
            space++;
            if ((curr->next->data == ')' || curr->next->data == '.' ) && curr->next != NULL) return 0;
            if (space >= 2) return 0;
        }
        if (isdigit(curr->data)) {
            if (curr->next != NULL && curr->next->data == ' '){
                if ((curr->next->next->data == '(' || curr->next->next->data == ')' || isdigit(curr->next->next->data)) && curr->next->next != NULL) return 0;
            }
        }
        if (curr->data == '0') {
            if (curr->next != NULL && curr->next->data == '.'){
                if (curr->next->next != NULL && (!isdigit(curr->next->next->data))) return 0;
            }
        }
        if (curr->data == '(') {
            dot = 0;
            left++;
        }
        if (curr->data == ')') {
            dot = 0;
            right++;
            if (right >left) return 0;
        }
        if (curr->data == '+' || curr->data == '-' || curr->data == '*'){
            operator++;
            dot = 0;
            if (operator >= 2) return 0;
            if (curr->next != NULL && curr->next->data == ' '){
                if ((curr->next->next->data == '+' || curr->next->next->data == '-' || curr->next->next->data == '*') && curr->next->next != NULL) return 0;
            }
        }
        if (curr->data == '(')
            if (curr->next != NULL && curr->next->data == '*') return 0;
        if (curr->data != ' ') space = 0;
        if (!(curr->data == '+' || curr->data == '-' || curr->data == '*')) operator = 0;
        curr = curr->next;
   }
    if (left != right) return 0;
    else return 1;
}

// 중위표기식을 후위표기식으로 바꾸기 위한 전처리
void change(pList expr) {
    pNode curr = expr->head;
    int count = 1;
    while (curr != NULL) {
        if(curr == expr->head && ( curr->data == '-' || curr->data == '+')) {
            insertFront(expr,makeNode('0'));
        }
        else if(curr->next != NULL && curr->data=='(' && (curr->next->data=='-' || curr->next->data == '+')) {
            insertMid(expr,count,makeNode('0'));
        }
        curr = curr->next;
        count++;
    }
}

// 후위표기식으로 변환
pList postfix(pList infix)
{
    pList list = makeList();
    struct node* head = NULL;
    char temp;
    pNode start = infix->head;

    while (start != NULL) {
        if (isdigit(start->data) || start->data == '.') {
            insertBack(list,makeNode(start->data));
        }
        else if (start->data == '+' || start->data == '-' || start->data == '*'
                || start->data == '(' || start->data == ')' )
        {
            insertBack(list,makeNode(' '));
            if (start->data == '+' || start->data == '-') {
                if (top(head) == '+' || empty(head) || top(head) == '(') push(&head, start->data);
                else if (top(head) == '-') {
                    temp = top(head);
                    pop(&head);
                    insertBack(list,makeNode(temp));
                    insertBack(list,makeNode(' '));
                    push(&head, start->data);
                }
                else if (top(head) == '*') {
                    while (top(head) == '*') {
                        temp = top(head);
                        pop(&head);
                        insertBack(list,makeNode(temp));
                        insertBack(list,makeNode(' '));
                    }
                    push(&head, start->data);
                }
            }
            else if (start->data == '*') push(&head, start->data);
            else if (start->data == '(') push(&head, start->data);
            else if (start->data == ')') {
                while (top(head) != '(') {
                    temp = top(head);
                    pop(&head);
                    insertBack(list,makeNode(temp));
                    insertBack(list,makeNode(' '));

                }
                pop(&head);
            }
        }
        start = start->next;
    }
    insertBack(list,makeNode(' '));
    while (!empty(head)) {
        temp = top(head);
        pop(&head);
        insertBack(list,makeNode(temp));
        insertBack(list,makeNode(' '));
    }
    removeSpace(list);
    return list;
}
