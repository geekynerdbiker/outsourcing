//
//  prob3.c
//  enejew
//
//  Created by Jacob An on 2021/12/09.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_BUFFER_SIZE 100

int main() {
    char input[MAX_BUFFER_SIZE];
    
    fgets(input, MAX_BUFFER_SIZE, stdin);
    char *ptr = strtok(input, " ");
    
    ptr = strtok(NULL, " ");
    int time = atoi(ptr);
    ptr = strtok(NULL, " ");
    char* command = ptr;
    
    sleep(time);
    system(command);

}
