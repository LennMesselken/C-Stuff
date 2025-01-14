#include <stdlib.h>
#include <sys/socket.h>
#include <sys/stat.h>
#include <unistd.h>
#include <regex.h>
#include <stdio.h>
#include <string.h>

#include "./file_helper.c"
#include "./http_helper.c"

#define BUFFER_SIZE 104857600
#define SRC_DIR "../src/"

void build_http_response(const char* file_name, const char* file_ext, char* response, size_t* response_len){
    printf("Considered Filename: %s \n", file_name);

    //build http header
    const char* mime_type = get_mime_type(file_ext);
    char* header = (char*) malloc(BUFFER_SIZE + sizeof(char));
    snprintf(header, BUFFER_SIZE, "HTTP/1.1 200 OK\r\n" "Content-Type: %s\r\n" "\r\n",mime_type);
    
    //try to open the requested file
    int file_fd = get_file_descriptor(SRC_DIR, file_name);
    if (file_fd == -1){
        snprintf(response, BUFFER_SIZE,"HTTP/1.1 404 Not Found\r\n" "Content-Type: text/plain\r\n" "\r\n" "404 Not Found");
        *response_len = strlen(response);
        return;
    }

    //get file size for content_length
    struct stat file_stat;
    fstat(file_fd, &file_stat);
    off_t file_size = file_stat.st_size;
    printf("FILE_DESC: %d  SIZE: %li \n", file_fd, file_size);

    //copy headers to response buffer
    *response_len = 0;
    memcpy(response, header, strlen(header));
    *response_len += strlen(header);

    //copy files to response buffer
    ssize_t bytes_read;
    while((bytes_read = read(file_fd, response + *response_len, BUFFER_SIZE - *response_len)) > 0){
        *response_len += bytes_read;
    }
    free(header);
    close(file_fd);

