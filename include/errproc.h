#ifndef VK_PROJECT_ERRPROC_H
#define VK_PROJECT_ERRPROC_H
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <string.h>
void error_check(int res, const char *message, int is_exit);

void print_error(const char * message, int is_exit);

int socket_(int domain, int type, int protocol);

int bind_(int sockfd, struct sockaddr *my_addr, socklen_t addrlen);

int listen_(int sockfd, int backlog);

int accept_(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

int connect_(int sockfd, struct sockaddr *addr, socklen_t addrlen);

int inet_pton_(int af, const char *src, void *dst);

int recv_(int sockfd, void *buf, size_t len, int flags);

int send_(int sockfd, const void *buf, size_t len, int flags);

void set_values(const char * arg, struct sockaddr_in * addr, socklen_t *addr_len, int * server_port, int *socket);

int getsockname_(int sockfd, struct sockaddr *addr, socklen_t *addrlen);

#endif //VK_PROJECT_ERRPROC_H
