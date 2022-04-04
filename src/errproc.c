#include "errproc.h"
void error_check(int res, const char *message, int is_exit){
    if(res == -1) {
        print_error(message, is_exit);
    }
}
void print_error(const char * message, int is_exit){
    perror(message);
    if(is_exit) {
        exit(EXIT_FAILURE);
    }
}
int socket_(int domain, int type, int protocol){
    int res = socket(domain, type, protocol);
    error_check(res, "socket failed: ", 1);
    return res;
}
int bind_(int sockfd, struct sockaddr *my_addr, socklen_t addrlen){
    int res = bind(sockfd, my_addr,  addrlen);
    error_check(res, "bind failed: ", 1);
    return res;
}
int listen_(int sockfd, int backlog){
    int res = listen(sockfd, backlog);
    error_check(res, "listen failed: ", 1);
    return res;
}
int accept_(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int res = accept(sockfd, addr, addrlen);
    error_check(res, "accept failed: ", 0);
    return res;
}
int connect_(int sockfd, struct sockaddr *addr, socklen_t addrlen){
    int res = connect(sockfd, addr, addrlen);
    error_check(res, "connect failed: ", 1);
    return res;
}
int inet_pton_(int af, const char *src, void *dst){
    int res = inet_pton(af, src, dst);
    error_check(res, "inet_pton failed: ", 1);
    if (res == 0){
        printf("inet_pton failed: src does not\n"
               "       contain a character string representing a valid network "
               "address in the specified address family");
        exit(EXIT_FAILURE);
    }
    return res;
}
int recv_(int sockfd, void *buf, size_t len, int flags){
    int res = recv(sockfd, buf, len, flags);
    error_check(res, "Error occurred while receiving content from the client: ", 0);
    return res;
}

int send_(int sockfd, const void *buf, size_t len, int flags){
    int res = send(sockfd, buf, len, flags);
    error_check(res, "Error occurred while sending content to the server: ", 0);
    return res;
}
void set_values(const char * arg, struct sockaddr_in * addr, socklen_t *addr_len, int * server_port, int *socket){
    *server_port = atoi(arg);
    *socket = socket_(AF_INET, SOCK_STREAM, 0);
    *addr = (struct sockaddr_in){0};
    (*addr).sin_family = AF_INET;
    (*addr).sin_port = htons(*server_port);
    *addr_len = sizeof (*addr);
}

int getsockname_(int sockfd, struct sockaddr *addr, socklen_t *addrlen){
    int res = getsockname(sockfd, addr, addrlen);
    error_check(res, "Error occurred while getting the socket name", 0);
    return res;
}