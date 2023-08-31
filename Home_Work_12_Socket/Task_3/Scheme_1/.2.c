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
#define CLIENT_PORT 7777
#define SIZE_DATA 128

int main()
{
    char message_recv[SIZE_DATA] = {0};
    char message_send[SIZE_DATA] = "Hello, I'm client!";

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);
    
    struct sockaddr_in client;
    memset(&client, 0, sizeof(struct sockaddr_in));
    client.sin_family = AF_INET;
    client.sin_port = htons(CLIENT_PORT);    
    client.sin_addr.s_addr = inet_addr(ADDRESS);

    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_fd == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    if(bind(socket_fd, (const struct sockaddr *) &client, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("Bind");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
    printf("Client port: %d\n\n", ntohs(client.sin_port));
    printf("Client connects to server...\n");

    if(connect(socket_fd, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("Connect");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client connected to server!\n\n");

    if(send(socket_fd, message_send, SIZE_DATA, 0) == -1)
    {
        perror("Send");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    printf("Client send message to server!\n\n");
    printf("Client waiting message from server...\n");

    if(recv(socket_fd, message_recv, SIZE_DATA, 0) == -1)
    {
        perror("Recv");
        close(socket_fd);
        exit(EXIT_FAILURE); 
    }

    printf("Server IP: %s\n", inet_ntoa(server.sin_addr));
    printf("Server port: %d\n", ntohs(server.sin_port));    
    printf("Message: %s\n", message_recv);

    close(socket_fd);

    return 0;
}
