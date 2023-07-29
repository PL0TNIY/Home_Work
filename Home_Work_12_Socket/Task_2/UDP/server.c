#include <arpa/inet.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 9719
#define ADDRESS "127.0.0.1"
#define BUFFER_SIZE 100

int main()
{
    struct sockaddr_in server;
    server.sin_family = AF_INET;
    server.sin_addr.s_addr = inet_addr(ADDRESS);
    server.sin_port = htons(PORT);

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

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

    struct sockaddr_in client;
    
    int size_client = sizeof(client);

    char message_1[BUFFER_SIZE] = "Hello!";
    char message_2[BUFFER_SIZE];
    
    if(recvfrom(socket_fd, message_2, BUFFER_SIZE, 0, (struct sockaddr *) &client, &size_client) == -1)
    {
        perror("Recvfrom");
        close(socket_fd);
        exit(EXIT_FAILURE); 
    }
    else
    {
        if(sendto(socket_fd, message_1, BUFFER_SIZE, 0, (const struct sockaddr *) &client, size_client) == -1)
        {
            perror("Sendto");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }
        else
        {
            printf("%s\n", message_1);
            close(socket_fd);
        }
    }

    return 0;
}
