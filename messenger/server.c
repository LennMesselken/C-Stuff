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
#define MAX_CLIENTS 16
#define USERNAME_LEN 16
#define BUFFER_SIZE 1024

struct client
{
    int socket;
    char username[USERNAME_LEN];
};

int main(){
    int server_fd;
    struct sockaddr_in server_addr;
    struct pollfd pds[MAX_CLIENTS];
    struct client clients[MAX_CLIENTS];
    char buffer[BUFFER_SIZE];

    //Socket Creation
    if((server_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        perror("socket creation error");
        exit(EXIT_FAILURE);
    }

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    //Binding
    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0){
        perror("bind error");
        exit(EXIT_FAILURE);
    }

    //Listening
    if ((listen(server_fd, 10)) < 0) {
        perror("listen error");
        exit(EXIT_FAILURE);
    }

    //poll initialization
    pds[0].fd = server_fd;
    pds[0].events = POLL_IN;
    for (int i = 1; i < MAX_CLIENTS; i++){
        pds[i].fd = -1;
    }

    printf("Server running on Port %d\n", PORT);

    while(1){
        //client info
        int client_fd;
        struct sockaddr_in client_addr;
        socklen_t addr_len;

        int activity = poll(pds, MAX_CLIENTS, -1);
        if (activity < 0){
            perror("poll error");
            exit(EXIT_FAILURE);
        } 
        //check if theres new incoming connections;
        if (pds[0].revents & POLL_IN){
            addr_len = sizeof(client_addr);
            client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &addr_len);

            //find empty slot for client
            for (int i = 1; i < MAX_CLIENTS; i++){
                if (pds[i].fd == -1){
                    pds[i].fd = client_fd;
                    pds[i].events = POLL_IN;
                    clients[i].socket = client_fd;
                
                //ask for username:
                send(client_fd, "Enter username: ", 16, 0);
                int username_len = recv(client_fd, clients[i].username, USERNAME_LEN, 0);
                if(username_len > 0){
                    clients[i].username[username_len - 1] = '\0';
                } else {
                    close(client_fd);
                    pds[i].fd = -1;
                    clients[i].socket = -1;
                }

                printf("New client connected: %s\n", clients[i].username);
                break;
                }
            }
        }
        //Check for activity on each clients connection

        for(int i = 1; i < MAX_CLIENTS; i++){
            if(clients[i].socket != -1 && (pds[i].revents & POLL_IN)){
                memset(buffer, 0, BUFFER_SIZE);
                int bytes_read = read(clients[i].socket, buffer, BUFFER_SIZE);
                if (bytes_read <= 0){
                    printf("Client Disconnected: %s\n", clients[i].username);
                    close(clients[i].socket);
                    pds[i].fd = -1;
                    clients[i].socket = -1; 
                } else {
                    buffer[bytes_read] = '\0';
                    printf("%s : %s", clients[i].username, buffer);

                    //Broadcast to rest of clients
                    for (int j = 1; j < MAX_CLIENTS; j++){
                        if(clients[i].socket != -1 && j != i){
                            char message[BUFFER_SIZE + USERNAME_LEN];
                            snprintf(message, sizeof(message), "[%s]: %s", clients[i].username, buffer);
                            send(clients[j].socket, message, strlen(message), 0);
                        }
                    }
                }
            }
        }
    }
    close(server_fd);
    return 0;

    
    return 0;
}