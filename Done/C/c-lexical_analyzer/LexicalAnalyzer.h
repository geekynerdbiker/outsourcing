//
//  LexicalAnalyzer.h
//  lexical_analyzer
//
//  Created by Jacob An on 2022/04/30.
//

#ifndef LexicalAnalyzer_h
#define LexicalAnalyzer_h

#include <stdio.h>
#pragma once
#include <stdio.h>
#include <ctype.h>

#define LEXEME_SIZE 100

// 문자, 숫자, 알수없는 기타 기호
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

// 정수값, identifier, 등호, 연산기호, 좌우괄호, 세미콜론
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 20
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define SEMI_COLON 27

// 테스트 함수 이름 최대 길이 지정
#define FILE_NAME_SIZE 100

// 변수 선언
int charClass;
char lexeme[LEXEME_SIZE];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE* fp;
errno_t err;

// 함수 선언
void add_Char();
void get_Char();
void get_Non_Blank();
int Look_Up(char ch);
int Lex();

void Test(const char* file_name);



#endif /* LexicalAnalyzer_h */
