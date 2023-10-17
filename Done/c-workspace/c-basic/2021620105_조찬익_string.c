#include <stdio.h>

int main(int argc, const char * argv[]) {
    char study[] = "C 언어를 배우고 있습니다.";
    printf("%s\n", study);
    
    char word[100], i;
    printf("영문 단어를 하나 입력하시오.: ");
    
    scanf(" %s", word);
    i = 0;
    while ( word[i] != '\0'){
        i++;
    }
    printf("문자열의 길이: %d \n", i);
    
    return 0;
}
