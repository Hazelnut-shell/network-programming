#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/socket.h>

#include <string> 
#include <iostream>

void error_handling(std::string msg);

int main(int argc, char *argv[]) {
    if(argc != 2) {
        error_handling("Usage : " + (std::string)argv[0] + " <port>\n");
    }
    
    int serv_sock;
    int clnt_sock;

    serv_sock = socket(PF_INET, SOCK_STREAM, 0);
    if(serv_sock == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in serv_addr;
    
    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    serv_addr.sin_port = htons(atoi(argv[1]));

    if(bind(serv_sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("bind() error");
    }

    if(listen(serv_sock, 5) == -1) {
        error_handling("listen() error");
    }


    struct sockaddr_in clnt_addr;
    socklen_t clnt_addr_size = sizeof(clnt_addr);
    clnt_sock = accept(serv_sock, (struct sockaddr*) &clnt_addr, &clnt_addr_size);
    if(clnt_sock == -1) {
        error_handling("accept() error");
    }

    char message[] = "hello world";     
    write(clnt_sock, message, sizeof(message));

    close(clnt_sock);
    close(serv_sock);

    return 0;
}

void error_handling(std::string msg) {
    std::cerr << msg << std::endl;
    // fputs(msg, stderr);
    // fputc('\n', stderr);
    exit(1);
}
