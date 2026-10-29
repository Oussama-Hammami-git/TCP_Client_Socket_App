#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include<fcntl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>


int main()
{
    /*
    NAME
        socket - create an endpoint for communication

    LIBRARY
        Standard C library (libc, -lc)

    SYNOPSIS
        #include <sys/socket.h>

        int socket(int domain, int type, int protocol);
    */
    int sockfd, status;

    sockfd = socket(AF_INET, SOCK_STREAM,0);
    if (sockfd <0)
    {
        perror("socket");
        return sockfd;
    }

    /*
    NAME
     connect - initiate a connection on a socket

    LIBRARY
     Standard C library (libc, -lc)

    SYNOPSIS
     #include <sys/socket.h>

     int connect(int sockfd, const struct sockaddr *addr,
                 socklen_t addrlen);
    */

    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(12345);

    /*
    NAME
     inet_aton,   inet_addr,   inet_network,   inet_ntoa,   inet_makeaddr,
     inet_lnaof, inet_netof - Internet address manipulation routines

LIBRARY
     Standard C library (libc, -lc)

SYNOPSIS
     #include <sys/socket.h>
     #include <netinet/in.h>
     #include <arpa/inet.h>

     int inet_aton(const char *cp, struct in_addr *inp);
    */
    inet_aton("127.0.0.1", &addr.sin_addr);

    status = connect(sockfd, (struct sockaddr *)&addr, sizeof(addr));

    if(status)
    {
        perror("connect");
        close(sockfd);
        return status;
    }

    /*
    NAME
     send, sendto, sendmsg - send a message on a socket

    LIBRARY
     Standard C library (libc, -lc)

    SYNOPSIS
     #include <sys/socket.h>

     ssize_t send(size_t size;
                    int sockfd, const void buf[size], size_t size, int flags);
     ssize_t sendto(size_t size;
                    int sockfd, const void buf[size], size_t size, int flags,
                    const struct sockaddr *dest_addr, socklen_t addrlen);
     ssize_t sendmsg(int sockfd, const struct msghdr *msg, int flags);

    */
    char text[255];
    sprintf(text, "hello from client \r\n");
    send(sockfd, text, strlen(text), 0);

    int ret = 0;
    ret = recv(sockfd, text, sizeof(text),0);
    if(ret > 0) printf("%s", text);


    close(sockfd);
    return 0;

}