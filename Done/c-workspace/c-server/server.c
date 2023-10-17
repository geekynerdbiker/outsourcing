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

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "ERROR: NO PORT PROVIDED!\n");
        exit(1);
    }
    
    int _socket;
    if ((_socket = socket(PF_INET, SOCK_STREAM, 0)) < 0) {
        fprintf(stderr, "ERROR: OPENING SOCKET!\n");
        exit(1);
    } else {
        int port_no = atoi(argv[1]);
        
        int flag = TRUE;
        setsockopt(_socket, SOL_SOCKET, SO_REUSEADDR, (const char*)&flag, sizeof(flag));
        
        char buffer[BUFFER_SIZE];
        char response[BUFFER_SIZE];
        
        struct sockaddr_in server;
        struct sockaddr_in client;
        
        memset(&server, 0, sizeof(server));
        socklen_t _client = sizeof(client);
        
        server.sin_family = PF_INET;
        server.sin_port = htons(port_no);
        server.sin_addr.s_addr = INADDR_ANY;
        
        if (bind(_socket, (struct sockaddr *) &server, sizeof(server)) < 0) {
            fprintf(stderr, "ERROR: ON BINDING!\n");
            exit(1);
        }
        
        listen(_socket,5);
        while (TRUE) {
            int _socket_ = accept(_socket, (struct sockaddr *) &client, &_client);
            if (_socket_ < 0) {
                fprintf(stderr, "ERROR: ON ACCEPT!\n");
                exit(1);
            }
            
            memset(buffer, 0, BUFFER_SIZE);
            memset(response, 0, BUFFER_SIZE);
            
            if (read(_socket_, buffer, BUFFER_SIZE) < 0) {
                fprintf(stderr, "ERROR: READING FROM SOCKET!\n");
                exit(1);
            }
            
            printf("\n<Request Messages>\n%s",buffer);
            char *line = strtok(buffer, " ");
            
            if (line != NULL) {
                char *path = "\0";
                char *request = strtok(NULL, " ");
                
                if (!strcmp(request, "/")) {
                    path = (char *)malloc(strlen("./test.html") + 1);
                    strcpy(path, "./test.html");
                } else {
                    path = (char *)malloc(strlen(request) + 1);
                    sprintf(path, ".%s", request);
                }
                
                char *extention[] = {".html", ".gif", ".jpeg", ".mp3", ".pdf"};
                char *filetype[] = {"text/html", "image/gif", "image/jpeg", "audio/mp3", "application/pdf"};
                
                char *type = "\0";
                for (int i = 0; i < 5; i++) {
                    if (strstr(path, extention[i]) != NULL) {
                        type = (char *)malloc(strlen(filetype[i]) +1);
                        strcpy(type, filetype[i]);
                        break;
                    }
                }
                
                int file = open(path, O_RDONLY);
                if (file < 0) {
                    file = open("./404.html", O_RDONLY);
                    type = (char *)malloc(strlen("text/html") +1);
                    strcpy(type, "text/html");
                }
                
                long long size = lseek(file, 0, SEEK_END);
                lseek(file, 0, SEEK_SET);
                
                sprintf(response, "HTTP/1.1 200 OK\r\n");
                sprintf(response, "Type: %s\r\n", type);
                sprintf(response, "Length: %lld\r\n\r\n", size);
                
                long n = write(_socket_, response, strlen(response));
                if (n < 0) {
                    fprintf(stderr, "ERROR: WRITING TO SOCKET!\n");
                    exit(1);
                }
                
                memset(buffer, 0, BUFFER_SIZE);
                while ((size = read(file, buffer, BUFFER_SIZE)) > 0) {
                    n = write(_socket_, buffer, BUFFER_SIZE);
                    
                    if (n < 0) {
                        fprintf(stderr, "ERROR: WRITING TO SOCKET!\n");
                        exit(1);
                    }
                }
            }
            close(_socket_);
        }
    }
    close(_socket);
    
    return 0;
}
