#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/un.h>
#include <unistd.h>

#define PATH_SERVER "/tmp/socket_server"
#define SIZE_DATA 128

int main()
{   
    char message_send[SIZE_DATA] = "Hello, I'm server!";

    struct sockaddr_un server;
    memset(&server, 0, sizeof(struct sockaddr_un));
    server.sun_family = AF_LOCAL;
    strcpy(server.sun_path, PATH_SERVER);

    struct sockaddr_un client;

    int socket_fd = socket(AF_LOCAL, SOCK_STREAM, 0);

    if(socket_fd == - 1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    if(bind(socket_fd, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_un)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(socket_fd, 1) == -1)
    {
        perror("Listen");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Server waiting connect client...\n");

        memset(&client, 0, sizeof(struct sockaddr_un));

        char message_recv[SIZE_DATA] = {0};

        int size_sockaddr_un = sizeof(struct sockaddr_un);
        int new_socket_fd = accept(socket_fd, (struct sockaddr *) &client, 
                &size_sockaddr_un);

        if(new_socket_fd == -1)
        {
            perror("Accept");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        printf("Client connected to server!\n\n");
        printf("Server waiting message from client...\n");

        if(recv(new_socket_fd, message_recv, SIZE_DATA, 0) == -1)
        {
            perror("Recv");
            close(new_socket_fd);
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        
        printf("Path client: %s\n", client.sun_path);
        printf("Message: %s\n\n", message_recv);

        if(send(new_socket_fd, message_send, SIZE_DATA, 0) == -1)
        {
            perror("Send");
            close(new_socket_fd);
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        printf("Server send message to client!\n\n");
    }
}
