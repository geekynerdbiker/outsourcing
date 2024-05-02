#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <errno.h>

int pipes, numbers;
int indexes[200], commands[200];

int** fds;
pid_t ppid;

void sigusr(int signal) {
    if (ppid != getpid())
        exit(0);
}

void sigchld(int signal) {
    if (ppid == getpid())
        kill(0, SIGUSR1);
}

void sigint(int signal) {
    if (ppid != getpid())
        exit(0);
}

void sigtstp(int signal) {
    if (ppid != getpid())
        exit(0);
}

void error(int num) {
    switch (num) {
        case EACCES:
            fprintf(stderr, "Permission denied\n");
            break;
            
        case EPERM:
            fprintf(stderr, "Permission denied\n");
            break;
        
        case ENOENT:
            fprintf(stderr, "No such file or directory\n");
            break;
            
        case EISDIR:
            fprintf(stderr, "Is a directory\n");
            break;
            
        case ENOTDIR:
            fprintf(stderr, "Not a directory\n");
            break;
        
        default:
            fprintf(stderr, "Error occurred: %d\n", errno);
            break;
    }
}

void run(char* argv[], int input, int idx) {
    if (input && (numbers == 1)) {
        char data;
        
        while (read(0, &data, 1)) {
            write(1, &data, 1);
        }
        
        return;
    }
    
    int num;
    char dept[200] = "", dest[200] = "";
    
    if (commands[idx] == 1) {
        if (strcmp(argv[indexes[idx]], "ls") == 0)
            sprintf(dept, "/bin/%s", argv[indexes[idx]]);
        else
            sprintf(dept, "/usr/bin/%s", argv[indexes[idx]]);
        execv(dept, argv+indexes[idx]);
    } else if (commands[idx] == 2) {
        if (strcmp(argv[indexes[idx]+1], "-n") == 0){
            num = atoi(argv[indexes[idx]+2]);
            sprintf(dept, "%s", argv[indexes[idx]+3]);
        } else {
            num = 10;
            sprintf(dept, "%s", argv[indexes[idx]+1]);
        }
        
        if (strcmp(argv[indexes[idx]], "head") == 0) {
            int fd = open(dept, O_RDONLY, 0666);
            
            char data;
            for (int i = 0; i < num; i++) {
                while (1) {
                    if (read(fd, &data, 1) == 0) {
                        close(fd);
                        return;
                    }
                    
                    write(1, &data, 1);
                    if (data == '\n')
                        break;
                }
            }
            
            close(fd);
        } else if (strcmp(argv[indexes[idx]], "tail") == 0) {
            int fd = open(dept, O_RDONLY, 0666);
            lseek(fd, -1, SEEK_END);
            
            char *tmp = (char*)malloc(sizeof(char)*1024);
            int curr = 0, check = 0;
            
            char data;
            for (int i = 0; i < num+1; i++) {
                while (1) {
                    read(fd, &data, 1);
                    tmp[curr++] = data;
                    
                    if (lseek(fd, -2, SEEK_CUR) == 0) {
                        read(fd, &data, 1);
                        tmp[curr++] = data;
                        check++;
                        close(fd);
                        break;
                    }
                    
                    if (data == '\n')
                        break;
                }
                
                if (check)
                    break;
            }
            
            close(fd);
            if (!check)
                curr--;

            for (int i = curr-1; i >= 0; i--)
                write(1, &tmp[i], 1);

            free(tmp);
        } else if (strcmp(argv[indexes[idx]], "cat") == 0) {
            int fd =open(dept, O_RDONLY, 0666);
            
            char data;
            while (read(fd, &data, 1)) {
                write(1, &data, 1);
            }
            
            close(fd);
        }
    } else if (commands[idx] == 3) {
        sprintf(dept, "%s", argv[indexes[idx]+1]);
        sprintf(dest, "%s", argv[indexes[idx]+2]);
        
        if (strcmp(argv[indexes[idx]], "cd") == 0){
            if (chdir(dept) == -1) {
                fprintf(stderr, "cd: ");
                error(errno);
            }
        } else if (strcmp(argv[indexes[idx]], "cp") == 0){
            int fd1 = open(dept, O_RDONLY);
            int fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC);
            
            printf("%s\n", dept);
            printf("%s\n", dest);
            if (strlen(dept) == 0 || strlen(dest) == 0) {
                fprintf(stderr, "cp: ");
                error(errno);
            } else {
                
                int n;
                char data;
                while ((n = read(fd1, &data, 1024)) >= 0) {
                    write(fd2, &data, n);
                }
                
                close(fd1);
                close(fd2);
            }
        } else if (strcmp(argv[indexes[idx]], "mv") == 0){
            int fd1 = open(dept, O_RDONLY);
            int fd2 = open(dest, O_WRONLY | O_CREAT | O_TRUNC);
            
            if (strlen(dept) == 0 || strlen(dest) == 0) {
                fprintf(stderr, "mv: ");
                error(errno);
            } else {
                if (rename(dept, dest) == -1) {
                    fprintf(stderr, "mv: ");
                    error(errno);
                }
            }
        } else if (strcmp(argv[indexes[idx]], "rm") == 0){
            if (unlink(dept) == -1) {
                fprintf(stderr, "rm: ");
                error(errno);
            }
        }
    } else if (commands[idx] == 4) {
        if (strcmp(argv[indexes[idx]], "pwd") == 0) {
            char *buf;
            size_t len = 1024;
            buf = getcwd(NULL, len);
            write(1, buf, len);
            if(buf != NULL)
                free(buf);
        }
    }
}

int main(void) {
    ppid = getpid();
    
    signal(SIGUSR1, sigusr);
    signal(SIGCHLD, sigchld);
    signal(SIGINT, sigint);
    signal(SIGTSTP, sigtstp);
    
    size_t size = 0;
    
    int f = 0;
    char *cmd = NULL;
    char *argv[200];
    
    while (1) {
        for (int i = 0; i < numbers; i++) {
            if (fds != NULL && fds[i] != NULL) {
                free(fds[i]);
                fds[i] = NULL;
            }
        }
        
        if (fds != NULL) {
            free(fds);
            fds = NULL;
        }
        
        pipes = 0;
        for (int i = 0; i < numbers; i++) {
            indexes[i] = 0;
            commands[i] = 0;
        }
        
        numbers = 0;
        
        int symbol[200] = {0}, symidx[200] = {0};
        int symnum = 0, num = 0, check1 = 0, check2 = 0, interrupt;
        
        getline(&cmd, &size, stdin);
        cmd[strlen(cmd)-1] = '\0';
        
        if (strlen(cmd) == 0)
            continue;
        
        char* tok;
        tok = strtok(cmd, " ");
        
        while (tok) {
            argv[num++] = tok;
            tok = strtok(NULL, " ");
        }
        
        argv[num] = NULL;
        
        if (strcmp(argv[0], "quit") == 0)
            break;
        
        char path[100];
        sprintf(path, "/bin/%s", argv[0]);
        
        indexes[numbers++] = 0;
        for (int i = 0; i < num; i++) {
            if (strcmp(argv[i], "|") == 0) {
                symidx[symnum] = i;
                symbol[symnum++] = 1;
                indexes[numbers++] = i+1;
            } if (strcmp(argv[i], ">") == 0) {
                symidx[symnum] = i;
                symbol[symnum++] = 2;
            } else if (strcmp(argv[i], ">>") == 0) {
                symidx[symnum] = i;
                symbol[symnum++] = 3;
            } else if (strcmp(argv[i], "<") == 0) {
                symidx[symnum] = i;
                symbol[symnum++] = 4;
            }
        }
        
        int comparasion = 1;
        for (int i = 0; i < numbers; i++) {
            if (strcmp(argv[indexes[i]], "ls") == 0 ||
               strcmp(argv[indexes[i]], "man") == 0 || strcmp(argv[indexes[i]], "grep") == 0 ||
               strcmp(argv[indexes[i]], "sort") == 0 || strcmp(argv[indexes[i]], "awk") == 0 || strcmp(argv[indexes[i]], "bc") == 0) {
                commands[i] = 1;
            } else if (strcmp(argv[indexes[i]], "head") == 0 || strcmp(argv[indexes[i]], "tail") == 0 || strcmp(argv[indexes[i]], "cat") == 0) {
                commands[i] = 2;
            } else if (strcmp(argv[indexes[i]], "mv") == 0 || strcmp(argv[indexes[i]], "rm") == 0 ||
                      strcmp(argv[indexes[i]], "cp") == 0 || strcmp(argv[indexes[i]], "cd") == 0) {
                commands[i] = 3;
            } else if (strcmp(argv[indexes[i]], "pwd") == 0 || strcmp(argv[indexes[i]], "exit") == 0) {
                commands[i] = 4;
            } else {
                printf("swsh: Command not found\n");
                comparasion = 0;
                break;
            }
        }
        
        if (comparasion == 0)
            continue;
        
        if (strcmp(argv[indexes[numbers-1]], "cd") == 0) {
            run(argv, 0, numbers-1);
            continue;
        }
        
        if (strcmp(argv[indexes[numbers-1]], "exit") == 0) {
            int num;
            write(2, "exit\n", 6);
            
            if (argv[indexes[numbers-1]+1])
                num = atoi(argv[indexes[numbers-1]+1]);
            else
                num = 0;
            exit(num);
        }
        
        fds = (int**)malloc(sizeof(int*)*(numbers));
        
        for (int i = 0; i < numbers; i++) {
            fds[i] = (int*)malloc(sizeof(int)*2);
            pipe(fds[i]);
        }
        
        for (int i = 0; i < symnum; i++)
            argv[symidx[i]] = NULL;
        
        if (symbol[0] == 4) {
            check1++;
            
            if ((f = open(argv[symidx[0] + 1], O_RDONLY, 0666)) <= 0) {
                printf("swsh: No such file\n");
                continue;
            }
        }
        
        if (fork() == 0) {
            dup2(fds[0][1], 1);
            
            if (check1 != 0)
                dup2(f, 0);
            
            run(argv, 0, 0);
            exit(0);
        }
        
        close(fds[0][1]);
        wait(NULL);
        
        if (check1 != 0) {
            close(f);
            check1 = 0;
        }
        
        for (interrupt = 1; interrupt < numbers-1; interrupt++) {
            if (fork() == 0) {
                dup2(fds[interrupt-1][0], 0);
                dup2(fds[interrupt][1], 1);
                run(argv, 0, interrupt);
                exit(0);
            }
            
            close(fds[interrupt-1][0]);
            close(fds[interrupt][1]);
            wait(NULL);
        }
        
        if (symbol[symnum-1] == 2 || symbol[symnum-1] == 3) {
            check2++;
            f = (symbol[symnum-1] == 2) ?
            
            open(argv[symidx[symnum-1]+1], O_WRONLY | O_CREAT | O_TRUNC, 0666) :
            open(argv[symidx[symnum-1]+1], O_WRONLY | O_CREAT | O_APPEND, 0666);
        }
        
        if (fork() == 0) {
            dup2(fds[interrupt-1][0], 0);
            
            if (check2 != 0)
                dup2(f, 1);
            
            run(argv, 1, numbers-1);
            exit(0);
        }
        
        close(fds[interrupt-1][0]);
        wait(NULL);
        
        if (check2 != 0) {
            close(f);
            check2 = 0;
        }
    }
    
    if (cmd != 0) {
        free(cmd);
        cmd = NULL;
    }
    
    for (int i = 0; i < numbers; i++) {
        if (fds != NULL && fds[i] != NULL) {
            free(fds[i]);
            fds[i] = NULL;
        }
    }
    
    if (fds) {
        free(fds);
        fds = NULL;
    }
    
    pipes = 0;
    for (int i = 0; i < numbers; i++) {
        indexes[i] = 0;
        commands[i] = 0;
    }
    
    numbers = 0;
}
