#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "224.0.0.1"
#define SERVER 9171
#define SIZE_DATA 128

int main()
{
    char message_recv[SIZE_DATA] = {0};

    struct sockaddr_in client;
    memset(&client, 0, sizeof(struct sockaddr_in));
    client.sin_family = AF_INET;
    client.sin_port = htons(SERVER);    
    client.sin_addr.s_addr = inet_addr(ADDRESS);

    struct ip_mreq multicast;
    memset(&multicast, 0, sizeof(struct ip_mreq));
    multicast.imr_multiaddr.s_addr = inet_addr(ADDRESS);
    multicast.imr_interface.s_addr = htonl(INADDR_ANY);

    int socket_fd = socket(AF_INET, SOCK_DGRAM, 0);

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

    if(setsockopt(socket_fd, IPPROTO_IP, IP_ADD_MEMBERSHIP, &multicast, 
                sizeof(struct ip_mreq)) == -1)
    {
        perror("Setsockopt");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    int size_sockaddr_in = sizeof(struct sockaddr_in);

    if(recvfrom(socket_fd, message_recv, SIZE_DATA, 0, 
                (struct sockaddr *) &client, &size_sockaddr_in) == -1)
    {
        perror("Recvfrom");
        close(socket_fd);
        exit(EXIT_FAILURE); 
    }

    printf("Message: %s\n", message_recv);

    close(socket_fd);

    exit(EXIT_SUCCESS);
}
