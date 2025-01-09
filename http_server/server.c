#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080

int server_fd;
struct sockaddr_in server_addr;

int main(){
    //create server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){ //TCP
        perror("socket failure");
        exit(EXIT_FAILURE);
    } 
    
    //socket config
    server_addr.sin_family = AF_INET; //IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY; //Accept Connections from any network interface
    server_addr.sin_port = htons(PORT);

    //bind socket 
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    //listen for connections
    if (listen(server_fd, 10) < 0){
        perror("listen failure");
        exit(EXIT_FAILURE);
    }
}