#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <fcntl.h>
#include <unistd.h>

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define BUFFER_SIZE 1024
#define TRUE 1
#define FALSE 0

void error(char *msg) {
    perror(msg);
    exit(1);
}

char *contentType(char *path) {
    char *extent[] = {".html", ".gif", ".jpeg", ".mp3", ".pdf"};
    char *type[] = {"text/html", "image/gif", "image/jpeg", "audio/mp3", "application/pdf"};
    char *result;
    
    for (int i = 0; i < 5; i++) {
        if (strstr(path, extent[i]) != NULL) {
            result = (char *)malloc(strlen(type[i]) +1);
            strcpy(result, type[i]);
            break;
        }
    }
    return result;
}

int main(int argc, char *argv[]) {
    int port_no, sock_fd, newsock_fd;
    char buffer[BUFFER_SIZE], response[BUFFER_SIZE];
    struct sockaddr_in server_addr, client_addr;
    
    socklen_t clilent = sizeof(client_addr);
    
    int n;
    if (argc < 2) {
        fprintf(stderr,"ERROR, no port provided\n");
        exit(1);
    }
    
    if ((sock_fd = socket(PF_INET, SOCK_STREAM, 0)) < 0)
        error("ERROR opening socket");
    
    int flag = TRUE;
    setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag));
    
    memset(&server_addr, 0, sizeof(server_addr));
    port_no = atoi(argv[1]);
    server_addr.sin_family = PF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(port_no);
    
    if (bind(sock_fd, (struct sockaddr *) &server_addr, sizeof(server_addr)) < 0)
        error("ERROR on binding");
    listen(sock_fd,5);
    
    
    while (TRUE) {
        newsock_fd = accept(sock_fd, (struct sockaddr *) &client_addr, &clilent);
        if (newsock_fd < 0)
            error("ERROR on accept");
        
        memset(buffer, 0, BUFFER_SIZE);
        memset(response, 0, BUFFER_SIZE);
        
        if (read(newsock_fd, buffer, BUFFER_SIZE) < 0)
            error("ERROR reading from socket");
        
        printf("\n<Request Message>\n%s",buffer);
        char *startline = strtok(buffer, " ");
        
        if (startline != NULL) {
            
            char *req_path = strtok(NULL, " ");
            char *path;
            
            if (!strcmp(req_path, "/")) {
                path = (char *)malloc(strlen("./test.html") + 1);
                strcpy(path, "./test.html");
            }
            else {
                path = (char *)malloc(strlen(req_path) + 1);
                sprintf(path, ".%s", req_path);
            }
            
            int file = open(path, O_RDONLY);
            char *content_type = contentType(path);
            
            if (file < 0) {
                file = open("./404.html", O_RDONLY);
                content_type = (char *)malloc(strlen("text/html") +1);
                strcpy(content_type, "text/html");
            }
            
            int content_size = lseek(file, 0, SEEK_END);
            lseek(file, 0, SEEK_SET);
            
            sprintf(response, "HTTP/1.1 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n", content_type, content_size);
            n = write(newsock_fd, response, strlen(response));
            
            if (n < 0)
                error("ERROR writing to socket");
            memset(buffer, 0, BUFFER_SIZE);
            
            while ((content_size = read(file, buffer, BUFFER_SIZE)) > 0) {
                n = write(newsock_fd, buffer, BUFFER_SIZE);
                
                if (n < 0)
                    error("ERROR writing to socket");
            }
        }
    }
    
    close(newsock_fd);
    close(sock_fd);
    
    return 0;
}
