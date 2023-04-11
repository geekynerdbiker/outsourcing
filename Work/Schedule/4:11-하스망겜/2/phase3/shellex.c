/* $begin shellmain */
#include "csapp.h"
#include<errno.h>
#define MAXARGS   128

#define Default 0
#define Running 1
#define Suspended 2
#define Front 3

typedef struct job {
    pid_t pid;
    int state;
    int num;
    char *cmdline;
    struct job *next;
} job;

typedef struct list {
    job *front;
    job *rear;
    int job_count;
} list;

/* Function prototypes */
void eval(char *cmdline, sigset_t mask_prev);
void eval_pipe(char *cmd, char *cmdline);
int parseline(char *buf, char **argv);
int builtin_command(char **argv);

void sigchld_handler(int sig);
void sigtstp_handler(int sig);
void sigint_handler(int sig);
job* get_fg(list *job_list);
char** history;
int history_len = 0, start_index;
int job_num = 1;
list *job_list;

void initList(void) {
    job_list->front = job_list->rear = NULL;
    job_list->job_count = 0;
}

int isEmpty(void) {
    return job_list->job_count == 0;
}

void add_job(pid_t pid, int state, char *cmdline) {
    job *newjob = (job*)malloc(sizeof(job));
    newjob->pid = pid;
    newjob->num = job_num++;
    newjob->state = state;
    newjob->cmdline = strdup(cmdline);
    newjob->next = NULL;

    if (isEmpty())
	job_list->front = newjob;
    else job_list->rear->next = newjob;
    job_list->rear = newjob;
    job_list->job_count++;
}

int delete_job(pid_t pid) {
    job *cur, *prev;
    if (isEmpty())
	return -1;
    cur = job_list->front;
    prev = NULL;
    while (cur) {
	if (cur->pid == pid) {
	    if (prev != NULL)
		prev->next = cur->next;
	    else job_list->front = cur->next;
	    free(cur);
	    job_list->job_count--;
	    return 1;
	}
	prev = cur;
	cur = cur->next;
    }
    return -1;	    
}

pid_t delete_job_num(int num) {
    job *cur, *prev;
    if (isEmpty())
        return -1;
    cur = job_list->front;
    prev = NULL;
    while (cur) {
        if (cur->num == num) {
            if (prev != NULL)
                prev->next = cur->next;
            else job_list->front = cur->next;
	    free(cur);
	    job_list->job_count--;
            return cur->pid;
        }
        prev = cur;
        cur = cur->next;
    }
    return -1;
}

job* get_fg(list *job_list) {
    job *cur = job_list->front;
    while (cur) {
        if (cur->state == Front)
            return cur->pid;
        cur = cur->next;
    }
    return NULL;
}

job* get_job(int num) {
    job* cur = job_list->front;
    while (cur) {
	if (cur->num == num)
	    return cur;
	cur = cur->next;
    }
    return NULL;
}

void history_concat(char* order) {
    history = (char**)realloc(history, sizeof(char*) * (history_len + 1));
    history[history_len++] = strdup(order);
}

int main() 
{
    job_list = (list*)malloc(sizeof(list));
    char cmdline[MAXLINE]; /* Command line */
    sigset_t mask_all, mask_one, mask_prev;
    Sigfillset(&mask_all);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);

    Signal(SIGCHLD, sigchld_handler);
    Signal(SIGTSTP, sigtstp_handler);
    Signal(SIGINT, sigint_handler);

    FILE* fp;
    if ((fp = fopen("history", "r")) == NULL)
	fp = fopen("history", "w");
    int line = 0;
    while (fgets(cmdline, MAXLINE, fp) != NULL)
	history_concat(cmdline);
    start_index = history_len;
    fclose(fp);
    int original_stdin;
    initList();    

    while (1) {
	Sigprocmask(SIG_BLOCK, &mask_one, &mask_prev);
        original_stdin = dup(STDIN_FILENO);
	
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
	if (strchr(cmdline, '|')) {
	    char *cmd = strdup(cmdline);
	    eval_pipe(cmd, cmdline);
	    free(cmd);
	}
	else eval(cmdline, mask_prev);
	
	Dup2(original_stdin, STDIN_FILENO);
	Close(original_stdin);
	Sigprocmask(SIG_SETMASK, &mask_prev, NULL);
    }
}
/* $end shellmain */

/* $begin signal handlers */
void sigchld_handler(int sig) {
    pid_t pid;
    int olderrno = errno;
    sigset_t mask_all, prev_all;
    int status;

    Sigfillset(&mask_all);
    while ((pid = waitpid(-1, &status, WNOHANG | WUNTRACED)) > 0) {
	if (WIFSIGNALED(status) || WIFEXITED(status)) {
	    Sigprocmask(SIG_BLOCK, &mask_all, &prev_all);
	    delete_job(pid);
	    Sigprocmask(SIG_SETMASK, &prev_all, NULL);
	}
    }
    if (errno != ECHILD)
	sio_error("waitpid error\n");
    errno = olderrno;	    
}

void sigtstp_handler(int sig) {
    pid_t pid;
    job* foreground = get_fg(job_list);
    if (foreground != NULL) {
	foreground->state = Suspended;
	kill(-foreground->pid, SIGSTOP);
    }
    return;
}

void sigint_handler(int sig) {
    pid_t pid;
    job* foreground = get_fg(job_list);
    if (foreground != NULL) {
	delete_job(pid);
	kill(-foreground->pid, SIGINT);
    }
    else exit(0);
    return;	
}
/* $end signal handlers */

/* $begin eval */
/* eval - Evaluate a command line */
void eval(char *cmdline, sigset_t mask_prev) 
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    sigset_t mask_all, mask_one;    
    Sigfillset(&mask_all);
    Sigemptyset(&mask_one);
    Sigaddset(&mask_one, SIGCHLD);

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
	    Sigprocmask(SIG_BLOCK, &mask_all, NULL);
	    add_job(pid, Front, cmdline);
	    Sigprocmask(SIG_SETMASK, &mask_prev, NULL);
	    if (waitpid(pid, &status, 0) < 0)
		unix_error("waitfg: waitpid error\n");
	    else {
		Sigprocmask(SIG_BLOCK, &mask_all, NULL);
		delete_job(pid);
		Sigprocmask(SIG_SETMASK, &mask_prev, NULL);
	    }
	}
	else { //when there is backgrount process!
	    printf("%d %s", pid, cmdline);
	    Sigprocmask(SIG_BLOCK, &mask_all, NULL);
	    add_job(pid, Running, cmdline);
	    Sigprocmask(SIG_SETMASK, &mask_prev, NULL);
	}
    }
    return;
}

/* $begin eval_pipe */
/* eval_pipe - Evaluate a command line when there is pipe */
void eval_pipe(char *cmd, char *cmdline)
{
    char *argv[MAXARGS]; /* Argument list execve() */
    char buf[MAXLINE];   /* Holds modified command line */
    int bg;              /* Should the job run in bg or fg? */
    pid_t pid;           /* Process id */
    char path1[MAXLINE] = "/bin/";
    char path2[MAXLINE] = "/usr/bin/";
    int fd[MAXARGS][2];
    int pipe_num = 0;

    for(int i = 0; i < strlen(cmdline); i++) {
	if(cmdline[i] == '|')
	    pipe_num++;
    }
    
    for (int i = 0; i <= pipe_num; i++) {
	pipe(fd[i]);

	char *tmp = cmd;
	if (i != pipe_num) {
	    cmd = strchr(cmd, '|');
	    *cmd = '\0';
	}

	strcpy(buf, tmp);
	if (buf[strlen(buf) - 1] != '\n')
	    strcat(buf, " ");
	bg = parseline(buf, argv);
	if (argv[0] == NULL)  
	    return;   /* Ignore empty lines */
	if (!builtin_command(argv)) { //quit -> exit(0), & -> ignore, other -> run
	    /* Child */
	    if((pid = Fork()) == 0) {
		if(i != pipe_num) {
		    Dup2(fd[i][1], STDOUT_FILENO);
		    Close(fd[i][1]);
		    Close(fd[i][0]);
		}

		if((execvp(strcat(path1, argv[0]), argv) < 0) && (execvp(strcat(path2, argv[0]), argv) < 0)) {	//ex) /bin/ls ls -al &
		    printf("%s: Command not found.\n", argv[0]);
		    exit(0);
		}
	    }
	    /* Parent waits for foreground job to terminate */
	    if(!bg) {
		int status;
		if(waitpid(pid, &status, 0) < 0)
		    unix_error("waitfg: waitpid error");

		if(index != pipe_num) {
		    Dup2(fd[i][0], STDIN_FILENO);
		    Close(fd[i][0]);
		    Close(fd[i][1]);
		    cmd++;
		}
		else return;
	    }
	    else //when there is backgrount process!
		printf("%d %s", pid, cmdline);
	}
    }
    return;
}
/* $end eval_pipe */	

/* If first arg is a builtin command, run it and return true */
int builtin_command(char **argv) 
{
    if (!strcmp(argv[0], "quit") || !strcmp(argv[0], "exit")) { /* quit command */
	FILE* fp = fopen("history", "a");
	for (int i = start_index; i < history_len; i++) {
	    fprintf(fp, "%s", history[i]);
	    free(history[i]);
	}
	free(history);
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
    if (!strcmp(argv[0], "jobs")) {
	job* cur = job_list->front;
	while (cur) {
	    switch (cur->state)
	    {
	    case 1: printf("[%d] %d  running %s", cur->num, cur->pid, cur->cmdline); break;
	    case 2: printf("[%d] suspended %s", cur->num, cur->cmdline); break;
	    default: break;
	    }
	    cur = cur->next;
	}
	return 1;	
    }
    int num = 0;
    job* cur;
    if (!strcmp(argv[0], "kill") || !strcmp(argv[0], "bg") || !strcmp(argv[0], "fg")) {
	sscanf(argv[1], "%%%d", &num);
	cur = get_job(num);
	if (cur == NULL) {
	    printf("No Such Job\n");
 	    return 1;
	}
    }
    if (!strcmp(argv[0], "kill")) {
	delete_job(cur->pid);
	kill(cur->pid, SIGINT);
	printf("[%d] killed %s", cur->num, cur->cmdline);
	return 1;
    }
    if (!strcmp(argv[0], "bg")) {
	if (cur->state == Suspended) {
	    cur->state = Running;
	    Kill(cur->pid, SIGCONT);
	    printf("[%d] running %s", cur->num, cur->cmdline);
	}
	return 1;
    }
    if (!strcmp(argv[0], "fg")) {
	if ((cur->state == Suspended) || (cur->state == Running)) {
	    cur->state = Front;
	    Kill(cur->pid, SIGCONT);
	    printf("[%d] running %s", cur->num, cur->cmdline);
	}
	return 1;
    }
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

    if (buf[strlen(buf)-1] == '\n')
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


