#ifndef _CALC_H_
#define _CALC_H_

#include "stack.h"
#include "queue.h"


int precedence(char op);                // 연산자의 우선순위   char op: 연산자
int isOperator(char ch);                // 연산자인지 구분   char ch: 구분할 문자
Queue infixToPostfix(char infix[]);     // 중위수식 -> 후위수식 변환    char infix[]: 입력된 중위수식
void evaluate(char infix[]);            // 입력된 수식 계산    char infix[]: 입력된 중위수식
int doOperator(char op, int x, int y);  // op에 해당하는 연산 수행   char op: 연산자, int x, y: 피연산자
int isInvalidExpression(char str[]);    // 유효한 수식인지 검사    char str[]: 입력 수식


#endif