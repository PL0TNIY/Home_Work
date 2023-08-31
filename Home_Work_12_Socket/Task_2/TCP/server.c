#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define SERVER_PORT 9171
#define SIZE_DATA 100

int main()
{
    char message_send[SIZE_DATA] = "Hello, I'm server!";

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT); 
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    struct sockaddr_in client;

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    if(bind(socket_fd, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Server IP: %s\n", inet_ntoa(server.sin_addr));
    printf("Server port: %d\n\n", ntohs(server.sin_port));

    if(listen(socket_fd, 1) == -1)
    {
        perror("Listen");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        printf("Server waiting connect client...\n");

        memset(&client, 0, sizeof(struct sockaddr_in));
        
        char message_recv[SIZE_DATA] = {0};

        int size_sockaddr_in = sizeof(struct sockaddr_in);
        int new_socket_fd = accept(socket_fd, (struct sockaddr *) &client, 
                &size_sockaddr_in);

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

        printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
        printf("Client port: %d\n", ntohs(client.sin_port));
        printf("Message: %s\n\n", message_recv);

        if(send(new_socket_fd, message_send, SIZE_DATA, 0) == -1)
        {
            perror("Send");
            close(new_socket_fd);
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        printf("Server send message to server!\n\n");
    }
}
