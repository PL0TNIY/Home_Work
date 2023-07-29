#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define NAME_FILE "/tmp/server_socket"
#define BUFFER_SIZE 100

int main()
{
    
    struct sockaddr_un server;
    server.sun_family = AF_LOCAL;
    strncpy(server.sun_path, NAME_FILE, sizeof(server.sun_path) - 1);

    int socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);

    char message_1[BUFFER_SIZE] = "Hello!";
    char message_2[BUFFER_SIZE];

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

    if(bind(socket_fd, (const struct sockaddr *) &server, sizeof(server)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("Success bind!\n");
    }

    struct sockaddr_un client;

    int size_client = sizeof(client);

    if(recvfrom(socket_fd, message_2, BUFFER_SIZE, 0, (struct sockaddr *) &client, &size_client) == -1)
    {
        perror("Recvfrom");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        printf("%s\n", message_2);
    }
    
    if(sendto(socket_fd, message_1, BUFFER_SIZE, 0, (const struct sockaddr *) &client, sizeof(client)) == -1)
    {
        perror("Sendto");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    else
    {
        close(socket_fd);
    }

    return 0;
}
