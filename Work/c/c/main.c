//
//  main.c
//  c-stack-eval
//
//  Created by Jacob An on 2022/04/06.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct stackNode
{
    double data;
    struct stackNode* link;
}stackNode;

stackNode* top;

void push(double item);
double pop();
double peek();
void del();
void printStack();
int eval(char* exp);
void postfix_case_bloack(char* postfix, int* p);
void postfix_case_operator_1(char* postfix, char symbol, int* p);
void postfix_case_operator_2(char* postfix, char symbol, int* p);
void postfix_case_default(char* postfix, char symbol, char* exp, int* p, int i);
char* infix_to_postfix(char* exp);
int syntaxsearch(char* exp);


void push(double item)
{
    stackNode* temp = (stackNode*)malloc(sizeof(stackNode));
    temp->data = item;
    temp->link = top;
    top = temp;
}

double pop()
{
    double item;
    stackNode* temp = top;
    
    if (top == NULL)
    {
        printf("\n\n Stack is empty !\n");
        return 0;
    }
    else
    {
        item = temp->data;
        top = temp->link;
        free(temp);
        return item;
    }
}

double peek()
{
    if (top == NULL)
    {
        return -999;
    }
    else
    {
        return top->data;
    }
}

void del()
{
    stackNode* temp;
    
    if (top == NULL)
    {
        printf("\n\n Stack is empty !\n");
    }
    else
    {
        temp = top;
        top = top->link;
        free(temp);
    }
}

void printStack()
{
    stackNode* p = top;
    
    printf("\n STACK [ ");
    
    while (p)
    {
        printf("%d ", p->data);
        p = p->link;
    }
    printf("] ");
}

int eval(char* exp)
{
    if (syntaxsearch(exp) == -1 ) return -999;
    char *postfix = infix_to_postfix(exp);
    
    double opr1, opr2;
    int value, i = 0, count = 0;
    int length = strlen(postfix);
    char symbol;
    
    for (i = 0; i < length; i++)
    {
        symbol = postfix[i];
        
        if (symbol >= '0' && symbol <= '9')
        {
            while (postfix[i + count] != ' ')
            {
                count++;
            }
            value = atoi(&postfix[i]);
            i += count;
            count = 0;
            push(value);
        }
        else
        {
            if (symbol != ' ')
            {
                opr2 = pop();
                opr1 = pop();
                
                switch (symbol)
                {
                    case '+': push(opr1 + opr2); break;
                    case '-': push(opr1 - opr2); break;
                    case '*': push(opr1 * opr2); break;
                    case '/': push(opr1 / opr2);
                        if (opr2 == 0) return -999;
                        break;
                }
            }
        }
    }
    return (int)pop();
}

void postfix_case_bloack(char* postfix, int* p)
{
    char temp;
    
    while (1)
    {
        temp = (char)pop();
        
        if ((temp != '(') && (temp != '{') && (temp != '['))
        {
            postfix[(*p)++] = temp;
            postfix[(*p)++] = ' ';
        }
        else
        {
            break;
        }
    }
}

void postfix_case_operator_1(char* postfix, char symbol, int* p)
{
    char temp;
    
    while (1)
    {
        if (top == NULL)
        {
            break;
        }
        temp = (char)pop();
        
        if (temp == '+' || temp == '-' || temp == '*' || temp == '/')
        {
            postfix[(*p)++] = temp;
            postfix[(*p)++] = ' ';
        }
        else
        {
            push(temp);
            break;
        }
    }
    push(symbol);
}

void postfix_case_operator_2(char* postfix, char symbol, int* p)
{
    char temp;
    
    while (1)
    {
        if (top == NULL)
        {
            break;
        }
        temp = (char)pop();
        
        if (temp == '*' || temp == '/')
        {
            postfix[(*p)++] = temp;
            postfix[(*p)++] = ' ';
        }
        else
        {
            push(temp);
            break;
        }
    }
    push(symbol);
}

void postfix_case_default(char* postfix, char symbol, char* exp, int* p, int i)
{
    postfix[(*p)++] = symbol;
    
    if (exp[i + 1] == '+' || exp[i + 1] == '-' || exp[i + 1] == '*' || exp[i + 1] == '/' ||
        exp[i + 1] == ')' || exp[i + 1] == '}' || exp[i + 1] == ']' || exp[i + 1] == '\0')
    {
        postfix[(*p)++] = ' ';
    }
}

char* infix_to_postfix(char* exp)
{
    int i = 0, p = 0;
    int length = strlen(exp);
    char symbol;
    char* postfix = (char*)malloc(length * 2);
    
    for (i = 0; i < length; i++)
    {
        symbol = exp[i];
        
        switch (symbol)
        {
            case '(':
                push(symbol);
                break;
                
            case ')':
                postfix_case_bloack(postfix, &p);
                break;
                
            case '+':
            case '-':
                postfix_case_operator_1(postfix, symbol, &p);
                break;
                
            case '*':
            case '/':
                postfix_case_operator_2(postfix, symbol, &p);
                break;
                
            default:
                postfix_case_default(postfix, symbol, exp, &p, i);
                break;
        }
    }
    
    while (top)
    {
        postfix[p++] = (char)pop();
        postfix[p++] = ' ';
    }
    postfix[p] = '\0';
    return postfix;
}

int syntaxsearch(char* exp)
{
    int length = strlen(exp);
    int i = 0;
    int ncount = 0;
    char symbol, opr;
    
    for (i = 0; i < length; i++)
    {
        symbol = exp[i];
        
        switch (symbol)
        {
            case '+':
            case '-':
            case '*':
            case '/':
                opr = exp[i + 1];
                if (opr == '+' || opr == '-' || opr == '*' || opr == '/')
                {
                    return -1;
                }
                break;
                
            case '(':
                push(symbol);
                break;
                
            case ')':
                if (top == NULL)
                {
                    return -1;
                }
                else
                {
                    if (pop() != '(')
                    {
                        return -1;
                    }
                }
                break;
                
            default:
                if (symbol < '0' || symbol > '9')
                {
                    return -1;
                }
                else
                {
                    ncount++;
                }
                break;
        }
    }
    if (!ncount || ncount == 1)
    {
        return -1;
    }
    while (top)
    {
        opr = (char)pop();
        if (opr == '(' || opr == '{' || opr == '[' ||
            opr == '+' || opr == '-' || opr == '*' || opr == '/')
        {
            return -1;
        }
    }
    return 0;
}

int main(void)
{
    char* exp[] = {"(78-(4*3*73)", "82*26/6", "78-(91-(16*69)", "(94*69-65+16)", "(95*93+56*98", "5/(10-10)"};
    int result;
    
    for (int i = 0; i < 6; i++){
        result = eval(exp[i]);
        if (result == -999) {
            printf("Error\n");
        }
        else {
            printf("%d\n", result);
        }
    }
    return 0;
}
