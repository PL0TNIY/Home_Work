#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define PATH_SERVER "/tmp/socket_server"
#define PATH_CLIENT "/tmp/socket_client"
#define SIZE_DATA 100

int main()
{
    char message_recv[SIZE_DATA] = {0};
    char message_send[SIZE_DATA] = "Hello, I'm client!";

    struct sockaddr_un server;
    memset(&server, 0, sizeof(struct sockaddr_un));
    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, PATH_SERVER);
    
    struct sockaddr_un client;
    memset(&client, 0, sizeof(struct sockaddr_un));
    client.sun_family = AF_LOCAL;
    strcpy(client.sun_path, PATH_CLIENT);

    int socket_fd = socket(AF_LOCAL, SOCK_DGRAM, 0);

    if(socket_fd == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    if(bind(socket_fd, (const struct sockaddr *) &client, 
                sizeof(struct sockaddr_un)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    if(sendto(socket_fd, message_send, SIZE_DATA, 0, 
                (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_un)) == -1)
    {
        perror("Sendto");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client send message to server!\n\n");   

    int size_sockaddr_un = sizeof(struct sockaddr_un);

    printf("Client waiting message from server...\n");

    if(recvfrom(socket_fd, message_recv, SIZE_DATA, 0, 
                (struct sockaddr *) &server, &size_sockaddr_un) == -1)
    {
        perror("Recvfrom");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Path server: %s\n", server.sun_path);
    printf("Message: %s\n", message_recv);

    close(socket_fd);

    exit(EXIT_SUCCESS);
}
