//
//  LexicalAnalyzer.c
//  lexical_analyzer
//
//  Created by Jacob An on 2022/04/30.
//

#include "LexicalAnalyzer.h"

// lexeme에 다음 캐릭터 추가
void add_Char()
{
    if (lexLen < LEXEME_SIZE - 1)
    {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }
    else
        fprintf(stderr, "Error :: Lexeme is too Long.\n");
}

// 입력의 다음 캐릭터를 받고 캐릭터의 형태를 결정
void get_Char()
{
    if ((nextChar = getc(fp)) != EOF)
    {
        if (isalpha(nextChar))
            charClass = LETTER;
        else if (isdigit(nextChar))
            charClass = DIGIT;
        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

// 공백문자가 나올때 까지 get_Char 함수를 호출
void get_Non_Blank()
{
    while (isspace(nextChar))
        get_Char();
}

int Look_Up(char ch)
{
    switch (ch)
    {
    case '(':
        add_Char();
        nextToken = LEFT_PAREN;
        break;

    case ')':
        add_Char();
        nextToken = RIGHT_PAREN;
        break;

    case '=':
        add_Char();
        nextToken = ASSIGN_OP;
        break;

    case ';':
        add_Char();
        nextToken = SEMI_COLON;
        break;

    case '+':
        add_Char();
        nextToken = ADD_OP;
        break;

    case '-':
        add_Char();
        nextToken = SUB_OP;
        break;

    case '*':
        add_Char();
        nextToken = MULT_OP;
        break;

    case '/':
        add_Char();
        nextToken = DIV_OP;
        break;

    default:
        add_Char();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

int Lex()
{
    lexLen = 0;
    get_Non_Blank();

    switch (charClass)
    {
        case LETTER:
        {
            add_Char();
            get_Char();

            while (charClass == LETTER || charClass == DIGIT)
            {
                add_Char();
                get_Char();
            }
            nextToken = IDENT;
            break;
        }
        
        case DIGIT:
        {
            add_Char();
            get_Char();

            while (charClass == DIGIT)
            {
                add_Char();
                get_Char();
            }
            nextToken = IDENT;
            break;
        }
        
        case UNKNOWN:
        {
            Look_Up(nextChar);
            get_Char();
            break;
        }
        
        case EOF:
        {
            nextToken = EOF;
            lexeme[0] = 'E';
            lexeme[1] = 'O';
            lexeme[2] = 'F';
            lexeme[3] = '\0';
            break;
        }
    }
    
    printf("Next token is %d, Next lexeme is %s\n", nextToken, lexeme);
    return nextToken;
}

void Test(const char* file_name)
{
    
    if ((err = fopen_s(&fp, file_name, "r")) != 0)
        printf("Error - cannnot open %s.\n", file_name);
    else
    {
        printf("[%s]: output\n", file_name);
        get_Char();

        do
        {
            Lex();
        } while (nextToken != EOF);
    }
}
