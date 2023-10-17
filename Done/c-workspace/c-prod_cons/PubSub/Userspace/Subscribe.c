#include <linux/netlink.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <pthread.h>

#define NETLINK_USER 31

#define MAX_PAYLOAD 1024 /* maximum payload size*/
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;
int rec = 1;

void subscriber() {
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    
    memset(&src_addr, 0, sizeof(src_addr));
    
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid =getpid();
    
    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;
    
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;
    
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    
    
    printf("[ Consumer ]\n");
    strcpy(NLMSG_DATA(nlh), "subs");
    
    sendmsg(sock_fd, &msg, 0);
    
    while(1) {
        recvmsg(sock_fd, &msg, 0);
        printf("Received message payload: %s\n", NLMSG_DATA(nlh));
    }
}



void publisher() {
    sock_fd = socket(PF_NETLINK, SOCK_RAW, NETLINK_USER);
    
    memset(&src_addr, 0, sizeof(src_addr));
    
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = 1;
    
    bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
    
    memset(&dest_addr, 0, sizeof(dest_addr));
    
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0;
    dest_addr.nl_groups = 0;
    
    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid =  1;
    nlh->nlmsg_flags = 0;
    
    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    
    printf("[ Producer ]\n");
    
    char buffer[100];
    
    while (fgets(buffer, sizeof(buffer), stdin)) {
        printf("Input a message to publish:");
        strcpy(NLMSG_DATA(nlh), cwd);
        sendmsg(sock_fd, &msg, 0);
        
    }
    
}


int main() {
    printf("1 for publisher, 0 for otherwise\n");
    
    int id;
    scanf("%d",&id);
    
    if (id == 1)
        publisher();
    else
        subscriber();
    
    close(sock_fd);
}
