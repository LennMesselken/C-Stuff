#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <string.h>
#include <netinet/in.h>
#include <pthread.h>

#define PORT 8080 

int main(){
    int server_fd;
    struct sockaddr_in server_addr;

    //Socket Creation
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Listening
    if ((listen(server_fd, 10)) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    printf("Server running on Port %d\n", PORT);

    while(1){

        //client info
        struct sockaddr_in client_addr;
        socklen_t client_addr_len = sizeof(client_addr);
        int* client_fd = malloc(sizeof(int));

        //accept client connections
        if ((*client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_addr_len)) < 0){
            perror("accept failure");
            exit(EXIT_FAILURE);
        }

        //create new thread to handle request
        

    }
    close(server_fd);
    return 0;

    
    return 0;
}