//
//  main.c
//  parser
//
//  Created by Jacob An on 2022/04/01.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER 100

void match(char);
char nexttoken(void);

void expr(void);
void expr_term(void);

void term(void);
void term_factor(void);

void factor(void);
void print(void);

char lookahead;

char result[MAX_BUFFER];
int buff_size = 0;

int main(void) {
    
    lookahead = nexttoken();
    
    expr();
    if (lookahead == '$') {
        result[buff_size++] = '\n';
        print();
    }
    else {
        print();
        printf(" error\n");
    }
    
    return 0;
}

void match(char token) {
    
    if (lookahead == token)
        lookahead = nexttoken();
    else {
        print();
        printf(" error\n");
        exit(1);
    }
}

char nexttoken(void) {
    char c;
    
    while (1) {
        c = getchar();
        if (c == ' ' || c == '\t' || c == '\n' || c == '\0') continue;
        return(c);
    }
}

void expr(void) {
    term();
    result[buff_size++] = '3';
    expr_term();
}

void expr_term(void) {
    if (lookahead == '+') {
        match('+');
        term();
        result[buff_size++] = '1';
        expr_term();
    } else if (lookahead == '-') {
        match('-');
        term();
        result[buff_size++] = '2';
        expr_term();
    }
}

void term(void) {
    factor();
    result[buff_size++] = '6';
    term_factor();
}

void term_factor(void) {
    if (lookahead == '*') {
        match('*');
        factor();
        result[buff_size++] = '4';
        term_factor();
    } else if (lookahead == '/') {
        match('/');
        factor();
        result[buff_size++] = '5';
        term_factor();
    }
}

void factor(void) {
    if (lookahead >= '0' && lookahead <= '9')
        match(lookahead);
    else {
        match('(');
        expr();
        match(')');
        result[buff_size++] = '7';
    }
}


void print(void) {
    for (int i = 0; i < buff_size; i++)
        printf("%c", result[i]);
}
