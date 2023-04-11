/* $begin shellmain */
#include "csapp.h"
#include <errno.h>
#define MAXARGS 128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

void writeHistory(char *cmdline);
int readHistory(int status);
void getHistory(int index, char *argv);


int main() {
    FILE *file = fopen("history", "a");
    fclose(file);
    
    char cmdline[MAXLINE]; /* Command line */
    
    int num = 0;
    while (1) {
        /* Read */
        printf("CSE4100-MP-P1> ");
        fgets(cmdline, MAXLINE, stdin);
        writeHistory(cmdline);
        
        if (feof(stdin))
            exit(0);
        if (sscanf(cmdline, "!%d", &num)) {
            if (num > readHistory(0))
                printf("-bash: %s: event not found\n", cmdline);
            else {
                getHistory(num, cmdline);
            }
        }
        else if (!strcmp("!!\n", cmdline)) {
            if (readHistory(0) == 0)
                printf("-bash: %s: event not found\n", cmdline);
            else
                getHistory(-1, cmdline);
        }
        /* Evaluate */
        eval(cmdline);
    }
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) {
    char *argv[10][MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];       /* Holds modified command line */
    char cmd[10][100];
    int bg, status; /* Should the job run in bg or fg? */
    pid_t pid;      /* Process id */

    strcpy(buf, cmdline);
    writeHistory(cmdline);
    char *ptr = strtok(buf, "|");
    
    int count = 0;
    for (int i = 0; ptr != NULL; i++) {
        strcpy(cmd[i], ptr);
        ptr = strtok(NULL, "|");
        count = i;
    }
    
    for (int i = 0; i <= count; i++) {
        while (cmd[i][0] == ' ')
            strcpy(cmd[i], cmd[i] + 1);


    for (int i = 0; i <= count; i++)
        parseline(cmd[i], argv[i]);

    if (argv[0] == NULL)
        return; /* Ignore empty lines */

    //make pipe
    int *pipes;
    pipes = malloc(sizeof(int) * (count) * 2);

    for (int i = 0; i < count; i++)
    {
        pipe(pipes + i * 2);
    }

    //fork all process
    for (int i = 0; i <= count; i++)
    {

        if (!builtin_command(argv[i]))
        { //quit -> exit(0), & -> ignore, other -> run

            if ((pid = Fork()) == 0)
            { //child

                if (count == 0)
                { //no pipe
                    for (int t = 0; t < 2 * (count); t++)
                    {
                        close(pipes[t]);
                    }

                    execvp(argv[0][0], argv[0]);
                }
                else if (i == 0)
                { //first pipe
                    dup2(pipes[1], 1);

                    for (int t = 0; t < 2 * (count); t++)
                    {
                        close(pipes[t]);
                    }

                    execvp(argv[0][0], argv[0]);
                }
                else if (i == count)
                { //last pipe
                    dup2(pipes[i * 2 - 2], 0);

                    for (int t = 0; t < 2 * (count); t++)
                    {
                        close(pipes[t]);
                    }

                    execvp(argv[i][0], argv[i]);
                }
                else
                { //middle pipe
                    dup2(pipes[i * 2 - 2], 0);
                    dup2(pipes[i * 2 + 1], 1);

                    for (int t = 0; t < 2 * (count); t++)
                    {
                        close(pipes[t]);
                    }

                    execvp(argv[i][0], argv[i]);
                }
                exit(0);
            }
        }
    }

    for (int t = 0; t < 2 * (count); t++)
    {
        close(pipes[t]);
    }
    for (int i = 0; i <= count; i++)
    {
        wait(&status);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv)
{
    char cwd[1024];
    if (!strcmp(argv[0], "exit"))
    { /* exit command */
        exit(0);
    }
    else if (!strcmp(argv[0], "cd"))
    {
        if (argv[1] == NULL)
        {
            chdir(environ[20] + 5);
        }
        else if (chdir(argv[1]) == -1)
        {
            if (!strcmp(argv[1], "~"))
            {
                chdir(environ[20] + 5);
            }
            else
                printf("invalid dir\n");
        }
        return 1;
    }
    else if (!strcmp(argv[0], "&")) /* Ignore singleton & */
        return 1;
    else
        return 0; /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv)
{
    char *delim; /* Points to first space delimiter */
    int argc;    /* Number of args */
    int bg;      /* Background job? */

    buf[strlen(buf) - 1] = ' ';   /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
        buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' ')))
    {
        argv[argc++] = buf;
        *delim = '\0';
        buf = delim + 1;
        while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;

    if (argc == 0) /* Ignore blank line */
        return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc - 1] == '&')) != 0)
        argv[--argc] = NULL;

    return bg;
}
