#include "stack_array.h"

// --------------------------------------------------------------------
// 변경 금지
// --------------------------------------------------------------------

// 스택 초기화
void stack_init_as(Array_Stack* stack)
{
    stack->top = 0;
    
    return;
}

// --------------------------------------------------------------------


/*
 * 구현시 유의사항
 * 1. 함수명과 매개변수는 수정하시지 마세요.
 * 2. 반환값 정확하게 구현해주세요. (bool, int)
 */

// --------------------------------------------------------------------
// 기초 스택 구현 - 모두 구현 B
// --------------------------------------------------------------------

// 스택이 비어있는지 확인, true/false 반환
bool is_empty_as(Array_Stack* stack)
{
    return (stack->top == 0);
}
/*
 * 스택이 가득찼는지 확인, true/false 반환
 * 스택의 최대 원소의 개수는 MAX_STACK_SIZE
 */
bool is_full_as(Array_Stack* stack)
{
    return (stack->top == MAX_STACK_SIZE);
}

// 스택에 원소 삽입
void push_as(Array_Stack* stack, int data)
{
    stack->array[(stack->top)++] = data;
    
    return;
}

// 스택의 최상위 원소(top)를 삭제하고 반환
int pop_as(Array_Stack* stack)
{
    int data = stack->array[(stack->top - 1)];
    stack->top--;
    
    return data;
    
}


// --------------------------------------------------------------------
// 심화 스택 구현
// --------------------------------------------------------------------

// 현재 스택 원소 개수 반환
int get_stack_size_as(Array_Stack* stack)
{
    return stack->top;
}

// 스택의 최상위 원소(top) 값 반환
int get_top_as(Array_Stack* stack)
{
    return stack->array[stack->top - 1];
}


/*
 * 스택의 최상위 원소부터 순서대로 출력 (pop X)
 * top ... bottom
 * ex) 5 10 12 4 3
 */
void print_stack_as(Array_Stack* stack)
{
    for (int i = stack->top - 1; i >= 0 ; i--)
        printf("%d ", stack->array[i]);
    printf("\n");
    
    return;
}
