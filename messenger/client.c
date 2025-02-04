#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <poll.h>
#include <arpa/inet.h>
#include <unistd.h>

#define PORT 8081
#define BUFFER_SIZE 1024
int main (){
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];

    sock = socket(AF_INET, SOCK_STREAM, 0);
    
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");

    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("error while connecting to server");
        exit(EXIT_FAILURE);
    }

    //Handle Username prompt
    recv(sock, buffer, BUFFER_SIZE, 0);
    printf("%s\n", buffer);
    fgets(buffer, BUFFER_SIZE, stdin);
    send(sock, buffer, strlen(buffer), 0);

    struct pollfd pds[2];
    pds[0].fd = sock;
    pds[0].events = POLL_IN;
    pds[1].fd = STDIN_FILENO;
    pds[1].events = POLL_IN;

    printf("Connected to Server\n");

    while(1){
        poll(pds, 2, -1);

        if (pds[0].revents & POLL_IN){
            memset(buffer, 0, BUFFER_SIZE);
            int bytes_read = recv(sock, buffer, BUFFER_SIZE, 0);
            if (bytes_read <= 0){
                printf("Server has closed the connection\n");
                close(sock);
                exit(0);
            }
            printf("%s", buffer);
        }
        if (pds[1].revents & POLL_IN){
            memset(buffer, 0, BUFFER_SIZE);
            fgets(buffer, BUFFER_SIZE, stdin);
            send(sock, buffer, strlen(buffer), 0);
        }
    }
    close(sock);
    return 0;
}