/* 
CSE3027 Computer Network(Project1)
UID : 2018044857
NAME : 이강영
*/
#include <stdio.h>
#include <sys/types.h>   
#include <sys/socket.h>  
#include <netinet/in.h>  
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>
#define BUFFER_SIZE 1024

void error(char *msg) {
  perror(msg);
  exit(1);
}

char *decisionContentType(char *path) {
  char *extent[] = {".html", ".gif", ".jpeg", ".mp3", ".pdf"};
  char *type[] = {"text/html", "image/gif", "image/jpeg", "audio/mp3", "application/pdf"};
  char *result;
  for(int i=0;i<5;i++) {
    if(strstr(path, extent[i]) != NULL) {
      result = (char *)malloc(strlen(type[i]) +1);
      strcpy(result, type[i]);
      break;
    }
  }
  return result;
}

int main(int argc, char *argv[]) {
  int sockfd, newsockfd; //descriptors rturn from socket and accept system calls
  int portno; // port number
  
     
  char buffer[BUFFER_SIZE];
  char response[BUFFER_SIZE];

  /*sockaddr_in: Structure Containing an Internet Address*/
  struct sockaddr_in serv_addr, cli_addr;
  socklen_t clilen = sizeof(cli_addr);
     
  int n; 
  // Port #를 받지 못하면 에러
  if (argc < 2) {
    fprintf(stderr,"ERROR, no port provided\n");
    exit(1);
  }
     
  //TCP 소켓 생성
  if ((sockfd = socket(PF_INET, SOCK_STREAM, 0)) < 0) 
    error("ERROR opening socket");
  
  //bind시에 local 주소를 재사용하기 위해 set함
  int flag = 1;
  setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag));

  //주소를 초기화한 후에 IP ADDRESS, PORT 지정
  memset(&serv_addr, 0, sizeof(serv_addr)); //(char *) &serv_addr 영역을 0으로 채움, sizeof(serv_addr)는 초기화 크기
  portno = atoi(argv[1]); 
  serv_addr.sin_family = PF_INET;   
  serv_addr.sin_addr.s_addr = INADDR_ANY; //for the server the IP address is always the address that the server is running on
  serv_addr.sin_port = htons(portno); //convert from host to network byte order
     
  //socket, server address를 binding함
  if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
    error("ERROR on binding");
     
  // Listen for socket connections. Backlog queue (connections to wait) is 5ㄴ
  listen(sockfd,5); 
     

  /*accept function: 
    1) Block until a new connection is established
    2) the new socket descriptor will be used for subsequent communication with the newly connected client.
  */
  while(1){

    newsockfd = accept(sockfd, (struct sockaddr *) &cli_addr, &clilen);
    if (newsockfd < 0) 
      error("ERROR on accept");
      
    memset(buffer, 0, BUFFER_SIZE);
    memset(response, 0, BUFFER_SIZE);

    if (read(newsockfd,buffer,BUFFER_SIZE) < 0) 
      error("ERROR reading from socket");
    
    printf("\n<Request Message>\n%s",buffer);
    char *startline = strtok(buffer, " "); //GET /test.html HTTP/1.1 [startline : GET]
    
    if(startline !=NULL) {
      
      char *req_path = strtok(NULL, " ");
      char *path;
      if(strcmp(req_path, "/") == 0) {
        path = (char *)malloc(strlen("./test.html") + 1);
        strcpy(path, "./test.html");
      }
      else {
        path = (char *)malloc(strlen(req_path) + 1);
        sprintf(path, ".%s", req_path);
      }

      char *content_type = decisionContentType(path);
      /*
      printf("startline:%s\n", startline);
      printf("req_path:%s\n", req_path);
      printf("path:%s\n", path);
      printf("contentType : %s\n\n", content_type);
      */
      int file = open(path, O_RDONLY);
      if(file < 0) {
        file = open("./404.html", O_RDONLY);
        content_type = (char *)malloc(strlen("text/html") +1);
        strcpy(content_type, "text/html");
      }
      int content_size = lseek(file, 0, SEEK_END);
      lseek(file, 0, SEEK_SET);

      sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", content_type, content_size);
      //printf("\n<Response Message>\n%s\n",response);
      n = write(newsockfd, response, strlen(response));
      if (n < 0) error("ERROR writing to socket");
      memset(buffer, 0, BUFFER_SIZE);
      while ((content_size = read(file, buffer, BUFFER_SIZE)) > 0){
        n = write(newsockfd, buffer, BUFFER_SIZE);
        if (n < 0) error("ERROR writing to socket");
      }
    }
  }
  close(newsockfd);
  close(sockfd);
  
  return 0; 
}