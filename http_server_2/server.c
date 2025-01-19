#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>

#include <util.h>
#include "./lib/utility_functions.c"

#define PORT 8080

int main(int argc, char* argv[]){
    int server_fd;
    struct sockaddr_in server_addr;

    //create a server socket
    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket creation failure");
        exit(EXIT_FAILURE);
    }

    //config socket
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //bind socket to port
    if(bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)) << 0){
        perror("bind failure");
        exit(EXIT_FAILURE);
    }

    //listen for connections
    if(listen(server_fd, 10) < 0){
        perror("listen failure");
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
        pthread_t thread_id;
        pthread_create(&thread_id, NULL, handle_client,(void*) client_fd);
        pthread_detach(thread_id);

    }
    close(server_fd);
    return 0;


}