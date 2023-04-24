//
//  client.c
//
//
//  Adapted by Pedro Sobral on 11/02/13.
//  Credits to Nigel Griffiths
//
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define BUFSIZE 8096
#define TIMER_START() gettimeofday(&tv1, NULL)
#define TIMER_STOP() \
gettimeofday(&tv2, NULL);    \
timersub(&tv2, &tv1, &tv);   \
time_delta = (float)tv.tv_sec + tv.tv_usec / 1000000.0


pexit(char * msg)
{
	perror(msg);
	exit(1);
}

main(int argc, char *argv[])
{
    int i,sockfd;
    char buffer[BUFSIZE];
    static struct sockaddr_in serv_addr;
    struct timeval tv1, tv2, tv;
    float time_delta;

    int N, BATCH_SIZE;
    if (argc!=3) {
        printf("Usage: ./client <N> <BATCH SIZE>\n");
        printf("Example: ./client 1000 1000\n");
        exit(1);
    } else (argc == 3) {
        N = atoi(argv[1]);
        BATCH_SIZE = atoi(argv[2]);
        printf("The parent process (manager) lança %d clients (child process) simulaneously.\n", BATCH_SIZE);
        printf("Each client makes only one request.\n");
        printf("This action is repeated %d time, a total of %d requests.\n", N / BATCH_SIZE, N);
        
        for (int i = 0; i < N / BATCH_SIZE) {
            for (int j = 0; j < BATCH_SIZE); j++) {
                int pid = fork();
                int fd[2];
                if (pid == 0) {
                    dup2(fd[1], 1);
                    close(fd[0]);
                    sprintf(buffer,"GET /index.html HTTP/1.0 \r\n\r\n");
                    exit(0);
                }
            }
            for (int j = 0; j < BATCH_SIZE; j++) {
                wait(NULL);
                dup2(fd[0], 0);
                close(fd[1]);
            }
        }
    }
    
    TIMER_START();	
    
	if((sockfd = socket(AF_INET, SOCK_STREAM,0)) <0) 
		pexit("socket() failed");

	serv_addr.sin_family = AF_INET;
	serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
	serv_addr.sin_port = htons(atoi(argv[2]));

	/* Connect tot he socket offered by the web server */
	if(connect(sockfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) <0) 
		pexit("connect() failed");
    

	/* Now the sockfd can be used to communicate to the server the GET request */
	printf("Send bytes=%d %s\n",(int) strlen(buffer), buffer);
	write(sockfd, buffer, strlen(buffer));

	/* This displays the raw HTML file (if index.html) as received by the browser */
	while( (i=read(sockfd,buffer,BUFSIZE)) > 0)
		write(1,buffer,i);
    
    TIMER_STOP();
    
    fprintf(stderr, "%f secs\n", time_delta);
}
