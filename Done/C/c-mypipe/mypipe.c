//
//  mypipe.c
//  c-workspace
//
//  Created by Jacob An on 2023/04/13.
//
#include <ctype.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char *argv[]) {
    int fd1[2], fd2[2];
    pid_t pid1, pid2;
    
    if (argc == 2) {
        if (pipe(fd1) < 0) {
            printf("Error pipe()\n");
            exit(1);
        } else if ((pid1 = fork()) < 0) {
            printf("Error fork()\n");
            exit(1);
        }
        
        if (pid1 == 0) {
            dup2(fd1[1], STDIN_FILENO);
            close(fd1[0]);
            close(fd1[1]);
            
            char *cmd[2] = { NULL };
            strcpy(cmd[0], argv[2]);
            execvp(cmd[0], cmd);
        }
    } else if (argc == 3) {
        if (pipe(fd1) < 0) {
            printf("Error pipe()\n");
            exit(1);
        } else if ((pid1 = fork()) < 0) {
            printf("Error fork()\n");
            exit(1);
        }
        
        if (pid1 == 0) {
            dup2(fd1[1], STDIN_FILENO);
            close(fd1[0]);
            close(fd1[1]);
            
            char *cmd[2] = { NULL };
            strcpy(cmd[0], argv[2]);
            execvp(cmd[0], cmd);
            
            if (pipe(fd2) < 0) {
                printf("Error pipe()\n");
                exit(1);
            } else if ((pid2 = fork()) < 0) {
                printf("Error fork()\n");
                exit(1);
            }
            
            if (pid2 == 0) {
                dup2(fd2[1], STDIN_FILENO);
                close(fd2[0]);
                close(fd2[1]);
                
                char *cmd[2] = { NULL };
                strcpy(cmd[0], argv[3]);
                execvp(cmd[0], cmd);
            }
        }
    }
    
    return 0;
}

