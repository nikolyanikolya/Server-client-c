#include "errproc.h"
int main(int argc, char * argv[]){
    int ret = EXIT_FAILURE;
    if(argc != 4){
        printf("Illegal arguments: three were expected.\n "
               "Usage: %s <server ip> <server port> <file to send>\n", argv[0]);
        goto resources_closed;
    }
    const char * server_ip = argv[1];
    struct sockaddr_in addr;
    int server_port, socket;
    socklen_t addr_len;
    set_values(argv[2], &addr, &addr_len, &server_port, &socket);
    if(inet_pton_(AF_INET, server_ip, &addr.sin_addr) == -1){
        goto opened_socket;
    }
    if(connect_(socket, (struct sockaddr *) &addr, addr_len) == -1){
        goto opened_socket;
    }
    FILE * client_file = fopen(argv[3], "rb");
    if(!client_file){
        print_error(strcat("Unable to open for reading ", argv[3]), 0);
        goto opened_socket;
    }
    int res = fseek(client_file, 0, SEEK_END);
    error_check(res, "fseek failed: ", 0);
    if(res == -1){
        goto opened_file;
    }
    int file_size = ftell(client_file);
    error_check(file_size, "ftell failed: ", 0);
    if(file_size == -1){
        goto opened_file;
    }
    rewind(client_file);
    char * content_buf = malloc(file_size);
    if(!content_buf){
        print_error(strcat("Unable to allocate memory for the content of ",argv[3]), 0);
        goto opened_file;
    }
    ssize_t nread;
    while((nread = fread(content_buf, sizeof (char), sizeof(content_buf), client_file)) > 0){
        res = send_(socket, content_buf, nread, 0);
        if(res == -1) {
            goto buf_not_freed;
        }
    }
    if(ferror(client_file)){
        print_error(strcat("Error occurred while reading ", argv[3]), 0);
        goto buf_not_freed;
    }
    ret = EXIT_SUCCESS;
buf_not_freed:
    free(content_buf);
opened_file:
    fclose(client_file);
opened_socket:
    close(socket);
resources_closed:
    return ret;
}
