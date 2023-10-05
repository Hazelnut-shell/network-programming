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
    if(argc != 3) {
        error_handling("Usage : " + (std::string)argv[0] + " <IP> <port>\n");
    }
    
    int sock = socket(PF_INET, SOCK_STREAM, 0);
    if(sock == -1) {
        error_handling("socket() error");
    }

    struct sockaddr_in serv_addr;

    memset(&serv_addr, 0, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr(argv[1]);
    serv_addr.sin_port = htons(atoi(argv[2]));

    if(connect(sock, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) == -1) {
        error_handling("connect() error");
    }

    char message[30];
    int msg_len = read(sock, message, sizeof(message) - 1);
    if(msg_len == -1) {
        error_handling("read() error");
    }

    printf("Message from server: %s\n", message);

    close(sock);
    return 0;
}

void error_handling(std::string msg) {
    std::cerr << msg << std::endl;
    exit(1);
}
