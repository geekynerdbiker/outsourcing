#include "stack.h"
#include <stdio.h>


// 스택 초기화
Stack initStack() {
  Stack newStack;
  newStack.top = -1;
  newStack.size = 0;

  return newStack;
}

int isStackFull(Stack *stack) {
  return (stack->size >= MAX_STACK_SIZE);
}
int isStackEmpty(Stack *stack) {
  return (stack->size <= 0);
}

void push(Stack *stack, int element) {
  // 큐가 꽉찼을 시 예외처리
  if (isStackFull(stack)) {
    printf("Stack is Full\n");
    return;
  }
  stack->top++;
  stack->size++;
  stack->items[stack->top] = element;
}

int pop(Stack *stack) {
  // 큐가 비었을 시 예외처리
  if (isStackEmpty(stack)) {
    printf("Stack is Empty\n");
    return -1;
  }

  int value = stack->items[stack->top];
  stack->top--;
  stack->size--;

  return value;
}