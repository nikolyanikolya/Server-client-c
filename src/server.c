#include "errproc.h"
#include <netinet/in.h>
const int BUF_SIZE = 256;
int main(int argc, char * argv[]) {
    int ret = EXIT_FAILURE;
    char buf[BUF_SIZE];
    if(argc != 3){
        printf("Illegal arguments: three were expected.\n "
               "Usage: %s <server port> <folder to put files in>\n", argv[0]);
        goto resources_closed;
    }
    struct sockaddr_in addr;
    int server_port, socket;
    socklen_t addr_len;
    set_values(argv[1], &addr, &addr_len, &server_port, &socket);
    if(bind_(socket, (struct sockaddr *)&addr, addr_len) == -1){
        goto opened_socket;
    }
    if(listen_(socket, 5) == -1){
        goto opened_socket;
    }
    while(1) {
        int fd = accept_(socket, (struct sockaddr *) &addr, &addr_len);
        if(fd == -1){
            continue;
        }
        char * filepath = strcat(argv[2], "/client_file.txt");
        FILE *copy_file = fopen(filepath, "wb");
        if (!copy_file) {
            print_error(strcat("Unable to open file for writing file ", filepath), 0);
            goto opened_accept_socket;
        }
        int nread;
        while ((nread = recv_(fd, buf, sizeof(buf), 0)) != 0) {
            if (nread == -1) {
                goto opened_file;
            }
            unsigned written;
            do {
                written = fwrite(buf, sizeof(char), nread, copy_file);
                if (ferror(copy_file)) {
                    print_error(strcat("Error occurred while writing to the file ", filepath), 0);
                    goto opened_file;
                }
                nread -= written;
            } while (nread != 0);
        }
    opened_file:
        fclose(copy_file);
    opened_accept_socket:
        close(fd);
    }
    ret = EXIT_SUCCESS;
opened_socket:
    close(socket);
resources_closed:
    return ret;
}
