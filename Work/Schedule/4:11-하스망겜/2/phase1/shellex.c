/* $begin shellmain */
#include "csapp.h"
#include<errno.h>
#define MAXARGS   128

/* Function prototypes */
void eval(char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);
char** history;
int history_len = 0, start_index;

void history_concat(char* order) {
    history = (char**)realloc(history, sizeof(char*) * (history_len + 1));
    history[history_len++] = strdup(order);
}

int main() 
{
    char cmdline[MAXLINE]; /* Command line */
    
    FILE* fp;
    if ((fp = fopen("history", "r")) == NULL)
	fp = fopen("history", "w");
    int line = 0;
    while (fgets(cmdline, MAXLINE, fp) != NULL)
	history_concat(cmdline);
    start_index = history_len;
    fclose(fp);

    while (1) {
	/* Read */
	printf("CSE4100-MP-P1> ");                   
	fgets(cmdline, MAXLINE, stdin); 
	if (feof(stdin))
	    exit(0);
	if (sscanf(cmdline, "!%d", &line)) {
	    if (line > history_len)
		printf("-bash: %s: event not found\n", cmdline); 
	    else {
		if (strcmp(history[history_len - 1], history[line - 1]))
		    history_concat(history[line - 1]);
		strcpy(cmdline, history[line - 1]);
	    }
	}
	else if (!strcmp("!!\n", cmdline)) {
	    if (history_len == 0)
		printf("-bash: %s: event not found\n", cmdline);
	    else strcpy(cmdline, history[history_len - 1]);
	}
	else if (history_len == 0 || strcmp(history[history_len - 1], cmdline))
	    history_concat(cmdline);
	/* Evaluate */
	eval(cmdline);
    }
}
/* $end shellmain */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    
    strcpy(buf, cmdline);
    bg = parseline(buf, argv); 
    if (argv[0] == NULL)  
	return;   /* Ignore empty lines */
    if (!builtin_command(argv)) { //quit -> exit(0), & -> ignore, other -> run
	if ((pid = Fork()) == 0) {
	    if (execvp(argv[0], argv) < 0) {	//ex) /bin/ls ls -al &
		printf("%s: Command not found.\n", argv[0]);
		exit(0);
	    }
	}
	/* Parent waits for foreground job to terminate */
	if (!bg){ 
	    int status;
	    if (waitpid(pid, &status, 0) < 0)
		unix_error("waitfg: waitpid error\n");
	
	}
	else//when there is backgrount process!
	    printf("%d %s", pid, cmdline);
    }
    return;
}

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit")) { /* quit command */
	FILE* fp = fopen("history", "a");
	for (int i = start_index; i < history_len; i++)
	    fprintf(fp, "%s", history[i]);
	fclose(fp);

	exit(0);
    }
    if (!strcmp(argv[0], "&"))    /* Ignore singleton & */
	return 1;
    if (!strcmp(argv[0], "cd")) {
	if (argv[1] != NULL) {
	    if (chdir(argv[1]))
		perror("cd");
	}
	else chdir(getenv("HOME"));
	
	return 1;
    }
    if (!strcmp(argv[0], "history")) {
	for (int i = 0; i < history_len; i++)
	    printf("%d %s", i + 1, history[i]);
	return 1;
    }
/*    if (!strcmp(argv[0], "!!")) {
	printf("%s", history[history_len - 1]);
	eval(history[history_len - 1]);	
	return 1;
    }
    int num;
    if (sscanf(argv[0], "!%d", &num) == 1) {
	printf("%s", history[num - 1]);
	eval(history[num - 1]);
	return 1;
    }*/
    return 0;                     /* Not a builtin command */
}
/* $end eval */

/* $begin parseline */
/* parseline - Parse the command line and build the argv array */
int parseline(char *buf, char **argv) 
{
    char *delim;         /* Points to first space delimiter */
    int argc;            /* Number of args */
    int bg;              /* Background job? */

    buf[strlen(buf)-1] = ' ';  /* Replace trailing '\n' with space */
    while (*buf && (*buf == ' ')) /* Ignore leading spaces */
	buf++;

    /* Build the argv list */
    argc = 0;
    while ((delim = strchr(buf, ' '))) {
	if (*buf == '\'') {
	    buf++;
	    delim = strchr(buf, '\'');
	}
	else if (*buf == '\"') {
	    buf++;
	    delim = strchr(buf, '\"');
	}
	argv[argc++] = buf;
	*delim = '\0';
	buf = delim + 1;
	while (*buf && (*buf == ' ')) /* Ignore spaces */
            buf++;
    }
    argv[argc] = NULL;
    
    if (argc == 0)  /* Ignore blank line */
	return 1;

    /* Should the job run in the background? */
    if ((bg = (*argv[argc-1] == '&')) != 0)
	argv[--argc] = NULL;

    return bg;
}
/* $end parseline */


