//
//  main.c
//  lexical_analyzer
//
//  Created by Jacob An on 2022/04/30.
//

#include "LexicalAnalyzer.h"

// 파일을 받아서 함수 실행
int main(int args, char[] argv)
{
    char file[FILE_NAME_SIZE];
    
    fputs("INPUT: ", stdout);
    scanf_s("%s",file, FILE_NAME_SIZE);
    Test(file);
    
    return 0;
}
