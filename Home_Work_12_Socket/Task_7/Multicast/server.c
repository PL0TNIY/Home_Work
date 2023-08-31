#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "224.0.0.1"
#define PORT 9171
#define SIZE_DATA 128

int main()
{
    char message_send[SIZE_DATA] = "Hello, I'm multicast!";

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_fd == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }

    int size_sockaddr_in = sizeof(struct sockaddr_in);

    while(1)
    {
        if(sendto(socket_fd, message_send, SIZE_DATA, 0,
                    (const struct sockaddr *) &server, size_sockaddr_in) == -1)
        {
            perror("Sendto");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        sleep(5);
    }
}
