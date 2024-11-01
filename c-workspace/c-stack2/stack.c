#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

typedef struct stack {
    int top;
    int capacity;
    char *array;
} Stack;

FILE* fin;
FILE* fout;

Stack* createStack(int capacity) {
    Stack* stack = (Stack*)malloc(sizeof(Stack));
    
    if (!stack)
        return NULL;

    stack->top = -1;
    stack->capacity = capacity;
    stack->array = (char*)malloc(stack->capacity * sizeof(char));

    if (!stack->array)
        return NULL;

    return stack;
}

int isFull(Stack* stack) {
    return stack->top == stack->capacity -1;
}

int isEmpty(Stack* stack) {
    return stack->top == -1;
}

char peek(Stack* stack) {
    return stack->array[stack->top];
}

char pop(Stack* stack) {
    if (!isEmpty(stack))
        return stack->array[stack->top--];
    fprintf(fout, "Underflow\n");
    return 0;
}

void push(Stack* stack, char new_element) {
    if (!isFull(stack))
        stack->array[++stack->top] = new_element;
    else
        fprintf(fout, "Overflow\n");
}

void printStack(Stack* stack) {
    for (int i = 0; i <= stack->top; i++)
        fprintf(fout, "%d ", stack->array[i]);
    fprintf(fout, "\n");
}

char* palindromeFix(char* buf, char* str) {
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
        if (buf[i] >= 'A' && buf[i] <= 'Z')
            str[index++] = buf[i] + 32;
        else if (buf[i] >= 'a' && buf[i] <= 'z')
            str[index++] = buf[i];
    str[index] = '\0';

    return str;
}

int isPalindrome(Stack* stack, char word[], int length) {
    int i;
    for (i = 0; i < length / 2; i++)
        push(stack, word[i]);

    if (length % 2 != 0)
        i++;

    while (i < length) {
        char character = pop(stack);

        if (character != word[i] && abs(character - word[i]) != 32)
            return 0;
        i++;
    }
    return 1;
}

int isMatched(char character1, char character2) {
    if (character1 == '(' && character2 == ')')
        return 1;
    else if (character1 == '{' && character2 == '}')
        return 1;
    else if (character1 == '[' && character2 == ']')
        return 1;
    else
    return 0;
}

char* balancedFix(char* buf, char* str) {
    int index = 0;
    for (int i = 0; i < strlen(buf); i++)
        if (buf[i] == '(' || buf[i] == '{' || buf[i] == '[' || buf[i] == ')' || buf[i] == '}' || buf[i] == ']')
            str[index++] = buf[i];
    str[index] = '\0';

    return str;
}

int isBalanced(Stack *stack, char exp[], int length) {
    for (int i = 0; i < length; i++) {
        if (exp[i] == '(' || exp[i] == '{' || exp[i] == '[')
            push(stack, exp[i]);
        else if (exp[i] == ')' || exp[i] == '}' || exp[i] == ']') {
            if (isEmpty(stack))
                return 0;
            else if (!isMatched(pop(stack), exp[i]))
                return 0;
        }
    }

    if (isEmpty(stack))
        return 1;
    else
        return 0;
}


int main (int argc, char *argv[]) {
    if (argc < 3) {
        printf("Too few arguments.\n");
        return -1;
    }

    fin = fopen(argv[1], "r");
    fout = fopen(argv[2], "w");

    char command;
    
    int arg, result;
    char buf[MAX_BUFFER_SIZE], str[MAX_BUFFER_SIZE];

    Stack* stack = createStack(5);
    Stack* palindrome;
    Stack* balanced;

    while ((fscanf(fin, " %c", &command) != EOF)) {
        switch (command) {
        case 'H':
            fscanf(fin, " %d", &arg);
            push(stack, arg);
            printStack(stack);
            break;
        
        case 'T':
            fprintf(fout, "%d\n", peek(stack));
            break;

        case 'O':
            pop(stack);
            printStack(stack);
            break;

        case 'P':
            palindrome = createStack(20);
            
            fgets(buf, MAX_BUFFER_SIZE, fin);
            palindromeFix(buf, str);
            
            result = isPalindrome(palindrome, str, strlen(str));
            if (result)
                fprintf(fout, "T\n");
            else
                fprintf(fout, "F\n");
            break;

        case 'B':
            balanced = createStack(20);
            
            fgets(buf, MAX_BUFFER_SIZE, fin);
            balancedFix(buf, str);

            result = isBalanced(balanced, str, strlen(str));
            if (result)
                fprintf(fout, "T\n");
            else
                fprintf(fout, "F\n");
            break;
        }
    }

    fclose(fin);
    fclose(fout);

    return 0;
}