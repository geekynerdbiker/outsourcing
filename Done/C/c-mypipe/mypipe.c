//
//  mypipe.c
//  c-workspace
//
//  Created by Jacob An on 2023/04/13.
//

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2];
    pid_t pid1, pid2;
    
    char c;
    char *args[4] = { NULL };
    
    while ((c = getchar()) != EOF ) {
        if (argc == 1) {
            printf("%c", c);
        } else if (argc == 2) {
            args[0] = (char *)malloc(sizeof(strlen(argv[1])));
            args[1] = (char *)malloc(sizeof(char));
            
            strcpy(args[0], argv[1]);
            args[1][0] = c;
            
            if (pipe(fd1) < 0) {
                printf("Error pipe()\n");
                exit(1);
            } else if ((pid1 = fork()) < 0) {
                printf("Error fork()\n");
                exit(1);
            }
            
            if (pid1 == 0) {
                close(fd1[0]);
                dup2(fd1[1], STDIN_FILENO);
                close(fd1[1]);
                
                if (execvp(argv[1], args) < 0) {
                    printf("Error execvp()\n");
                    exit(1);
                }
            }
            
            char result;
            
            close(fd1[1]);
            while (read(fd1[0], &result, 1) > 0)
                write(STDOUT_FILENO, &result, 1);
            close(fd1[0]);
            wait(NULL);
            
        } else if (argc == 3) {
            args[0] = (char *)malloc(sizeof(strlen(argv[1])));
            args[1] = (char *)malloc(sizeof(strlen(argv[1])));
            args[2] = (char *)malloc(sizeof(char));
            
            strcpy(args[0], argv[1]);
            strcpy(args[1], argv[2]);
            args[2][0] = c;
            
            if (pipe(fd1) < 0) {
                printf("Error pipe()\n");
                exit(1);
            } else if ((pid1 = fork()) < 0) {
                printf("Error fork()\n");
                exit(1);
            }
            
            if (pid1 == 0) {
                close(fd1[0]);
                dup2(fd1[1], STDIN_FILENO);
                close(fd1[1]);
                
                argv++;
                
                if (execvp(argv[1], args) < 0) {
                    printf("Error execvp()\n");
                    exit(1);
                }
            }
            
            char result;
            
            close(fd1[1]);
            while (read(fd1[0], &result, 1) > 0)
                write(STDOUT_FILENO, &result, 1);
            close(fd1[0]);
            wait(NULL);
        }
    }
    return 0;
}

