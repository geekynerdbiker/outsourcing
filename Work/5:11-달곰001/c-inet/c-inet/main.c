#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <pthread.h>
#include <stdlib.h>
// author: TODO-1-YOUR-NETID-HERE
// Cite all your sources! This is the starting code of the Spring 2022 CS241 Final
// "It's dangerous to go alone, take this!" - Legend of Zelda (1986) pthread_mutex_t duck = PTHREAD_MUTEX_INITIALIZER;
void quit (const char *mesg) {
    perror (mesg);
    exit (1);
    
}

void* handle_client (void *fd_ptr) {
    pthread_detach (pthread_self ()); // pthread_join not needed
    
    int fd = *(int *) fd_ptr;
    free (fd_ptr); fd_ptr = NULL;
    
    struct sockaddr_in address;
    socklen_t addressLength = sizeof (address);
    
    int ok = getpeername (fd, (struct sockaddr *) &address, &addressLength);
    
    // TODO-2: inet_ntoa is not thread-safe! So make this code safe using the duck.
    // inet_ntoa may return a pointer to the same memory location
    // TODO-3: Answer below: If no lock was used to protect this critical section
    // what errors/changes would you expect to see in the program’s behavior or output?
    //
    //
    char *filename = ok == 0 ? inet_ntoa (address.sin_addr) : "unknownip";
    // you do not need to call free on the filename
    
    printf ("Logging data to file %s\n", filename);
    FILE *file = fopen(filename, 'r'); // TODO-4 open filename for append;
    
    char buffer[8 * 1024 + 1];
    size_t numreadtotal = 0;
    // maybe useful later,
    // if (strstr (buffer, "\r\n\r\n")) break // fwrite (buffer, 1, , )
    // time_t, time() and ctime() are great but look out for thread safety.
    // HTTP request and response headers both use \r\n as a line ending.
    // TODO-5 Prevent a race condition when two threads write to the same log file:
    // - Concurrent requests must not have overlapping content in the log file.
    
    fclose(file);
}
