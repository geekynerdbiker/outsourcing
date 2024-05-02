#ifndef _STACK_H_
#define _STACK_H_

#define MAX_STACK_SIZE 999

/**
 * 사용 용도 :
 * 1. 입력된 중위수식 -> 후위수식 변환 시 연산자 저장 스택
 * 2. 후위수식 계산 시 계산결과 저장 스택
*/

typedef struct Stack {
  int top;                    // 스택의 맨 위 인덱스
  int size;                   // 스택의 크기
  int items[MAX_STACK_SIZE];  // 스택 배열
} Stack;

Stack initStack(); // 스택 초기화
void push(Stack *stack, int element);
int pop(Stack *stack);
int isStackFull(Stack *stack);
int isStackEmpty(Stack *stack);


#endif