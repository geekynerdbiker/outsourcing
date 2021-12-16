//
//  prob2.c
//  enejew
//
//  Created by Jacob An on 2021/12/09.
//

#include <stdio.h>
#include <stdlib.h>

#define MAX_BUFFER_SIZE 100

int main() {
    char env[MAX_BUFFER_SIZE], envVal[MAX_BUFFER_SIZE];
    
    printf("Input environment variable: ");
    fgets(env, MAX_BUFFER_SIZE, stdin);
    printf("Input environment variable value: ");
    fgets(envVal, MAX_BUFFER_SIZE, stdin);
    
    const char* s = getenv(env);
    if(s == NULL)
        setenv(env, envVal, 0);
    else {
        printf("Already defined. Do you want to overwrite? (Y or N): ");
        char answer;
        scanf("%c", &answer);
        
        if (answer == 'Y') setenv(env, envVal, 1);
    }
}
