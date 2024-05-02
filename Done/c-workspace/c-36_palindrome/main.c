#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TRUE 1
#define FALSE 0
#define MAX_SIZE 500

int isPalindrome(char *s) {
    for (int i = 0; i < strlen(s) / 2; i++)
        if (s[i] != s[strlen(s) - i - 1])
            return FALSE;
    return TRUE;
}

int getDigit(char c) {
    if (c >= '0' && c <= '9')
        return (int)c - 48;
    else if (c >= 'A' && c <= 'Z')
        return (int)c - 55;
    else
        return 0;
}

int getOctal(int k) {
    if (k >= 0 && k <= 9)
        return k + 48;
    else if (k >= 10 && k <= 35)
        return k + 55;
    else
        return 0;
}

int main(void) {
    int N;
    scanf("%d", &N);
    
    char buffer[MAX_SIZE];
    
    for (int i = 0; i < N; i++) {
        scanf("%s", buffer);
        
        char *input, *reverse;
        input = (char *)malloc(sizeof(char) * strlen(buffer));
        
        strcpy(input, buffer);
        int len = (int)strlen(input);
        
        do {
            reverse = (char *)malloc(sizeof(char) * len);
            for (int i = 0; i < len; i++)
                reverse[i] = input[len - i - 1];
            
            int *digit = (int *)malloc(sizeof(int) * (len + 1));
            for (int i = 0; i < len + 1; i++)
                digit[i] = 0;
            
            int flag = FALSE;
            for (int i = 0; i < len; i++)
                digit[i] += getDigit(reverse[i]) + getDigit(input[i]);
            
            for (int i = 0; i < len + 1; i++) {
                if (digit[i] >= 36) {
                    digit[i] %= 36;
                    digit[i+1]++;
                }
            }
            
            if (digit[len])
                flag = TRUE;
            
            input = (char *)malloc(sizeof(char) * (len + flag));
            for (int i = 0; i < len + flag; i++)
                input[i] = getOctal(digit[len + flag - i - 1]);
            len += flag;
        } while (!isPalindrome(input) && len <= MAX_SIZE);
        
        if (len > MAX_SIZE)
            printf("No\n");
        else
            printf("%s\n", input);
    }
    
    return 0;
}

/*
 
 TEST INPUT:
 
1
WWW
 
 
 INPUT:
 
9
1
999999
WWWWWWWWWWWW
123456789ABCDEDCBA987654321
123456789ABCDEFGHIJIHGFEDCBA987654321
ZZZZ
ZWYZWYW
FJKWEKLFJKLEJKLW
YP3IJK
*/
