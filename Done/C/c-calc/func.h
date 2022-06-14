//
//  func.h
//  calc
//
//  Created by Jacob An on 2022/05/18.
//

#ifndef func_h
#define func_h

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER '0'
#define MAXOP 100
#define MAXVAL 100
#define BUFSIZE 100

int getch1(void);
void ungetch1(int c);
int getop(char s[]);

void push(double f);
double pop(void);

void run(void);

#endif /* func_h */
