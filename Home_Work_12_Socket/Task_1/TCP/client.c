#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define NAME_FILE_SERVER "/tmp/socket_server"
#define NAME_FILE_CLIENT "/tmp/socket_client"
#define BUFFER_SIZE 128

int main()
{
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, NAME_FILE_SERVER, sizeof(server.sun_path) - 1);

    struct sockaddr_un client;
    client.sun_family = AF_LOCAL;
    strncpy(client.sun_path, NAME_FILE_CLIENT, sizeof(client.sun_path) - 1);

    int socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

    char buffer_1[BUFFER_SIZE] = "Hello!";
    char buffer_2[BUFFER_SIZE];

    if(socket_fd == -1)
    {
        perror("Socket");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success socket!\n");
    }

    if(bind(socket_fd, (struct sockaddr *) &client, sizeof(client)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success bind!\n");
    }
    
    if(connect(socket_fd, (const struct sockaddr *) &server, sizeof(server)) == -1)
    {
        perror("Connect");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success connect!\n");
    }

    if(send(socket_fd, buffer_1, BUFFER_SIZE, 0) == -1)
    {
        perror("Send");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        if(recv(socket_fd, buffer_2, BUFFER_SIZE, 0) == -1)
        {
            perror("Recv");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("%s\n", buffer_2);
            close(socket_fd);
        }
    }

    return 0;
}
