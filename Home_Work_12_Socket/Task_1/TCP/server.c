#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define NAME_FILE_SOCKET "/tmp/socket_server"
#define BUFFER_SIZE 100

int main()
{   
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, NAME_FILE_SOCKET, sizeof(server.sun_path) - 1);

    int socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);
    int new_socket_fd;
    int size_server = sizeof(server);

    char buffer_1[BUFFER_SIZE] = "Hello!";
    char buffer_2[BUFFER_SIZE];

    if(socket_fd == - 1)
    {
        perror("Socket!\n");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Socket creat!\n");
    }

    if(bind(socket_fd, (const struct sockaddr *) &server, size_server) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success bind!\n");
    }
    
    if(listen(socket_fd, 1) == -1)
    {
        perror("Listen");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success listen!\n");
    }
    
    new_socket_fd = accept(socket_fd, NULL, NULL);

    if(new_socket_fd == -1)
    {
        perror("Accept");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success accept!\n");
    }

    if(recv(new_socket_fd, buffer_2, BUFFER_SIZE, 0) == -1)
    {
        perror("Recv");
        close(new_socket_fd);
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("%s\n", buffer_2);

        if(send(new_socket_fd, buffer_1, BUFFER_SIZE, 0) == -1)
        {
            perror("Send");
            close(socket_fd);
            close(new_socket_fd);
            exit(EXIT_FAILURE);
        }
        else
        {
            close(socket_fd);
            close(new_socket_fd);
        }
    }

    return 0;
}
