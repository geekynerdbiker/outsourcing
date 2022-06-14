//
//  prob1.c
//  enejew
//
//  Created by Jacob An on 2021/12/09.
//

#include <stdio.h>
#include <string.h>

#define MAX_BUFFER_SIZE 100

int main(int argc, const char * argv[]) {
    char path[MAX_BUFFER_SIZE];
    int numChar, answer = 0;
    
    printf("Input file name: ");
    fgets(path, MAX_BUFFER_SIZE, stdin);
    printf("Input number of char: ");
    scanf("%d", &numChar);
    
    FILE* fp = fopen(path, "r");
    
    if (fp == NULL) {
        printf("No file exist.\n");
        return -1;
    }
    while (feof(fp) == 0) {
        char str[MAX_BUFFER_SIZE];
        fgets(str, MAX_BUFFER_SIZE, fp);
            
        int len = 0;
        for (int i = 0; i < MAX_BUFFER_SIZE; i++){
            if(str[i] != '\0') len++;
            else break;
        }
        if (len > numChar) answer++;
    }
    printf("%d\n", answer);
    return 0;
}
