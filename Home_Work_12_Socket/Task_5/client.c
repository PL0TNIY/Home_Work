#include <arpa/inet.h>
#include <netinet/in.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define SERVER_PORT 9171
#define CLIENT_PORT 7919
#define SIZE_DATA 128

int main()
{
    char *message_send = calloc(SIZE_DATA, sizeof(char));
    strcpy(message_send, "Hello, I'm client!");

    char *packet = calloc(sizeof(struct udphdr) + strlen(message_send), 
            sizeof(char));
    memmove(packet + sizeof(struct udphdr), message_send, strlen(message_send));

    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    struct udphdr *udp_header = (struct udphdr *)packet;
    memset(udp_header, 0, sizeof(struct udphdr));
    udp_header -> source = htons(CLIENT_PORT);
    udp_header -> dest = htons(SERVER_PORT);
    udp_header -> len = htons(sizeof(struct udphdr) + strlen(message_send));
    udp_header -> check = htons(0);

    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

    if(socket_fd == -1)
    {
        perror("Socket");
        free(message_send);
        free(packet);
        exit(EXIT_FAILURE);
    }

    if(sendto(socket_fd, packet, sizeof(struct udphdr) + strlen(message_send), 
                0, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_in)) == -1) 
    {
        perror("Sendto");
        free(message_send);
        free(packet);
        close(socket_fd);
        exit(EXIT_FAILURE);
    }
    
    printf("Client send message to server!\n\n");
    printf("Client waiting message from server...\n");    

    while(1)
    {
        int size_sockaddr_in = sizeof(struct sockaddr_in);

        if(recvfrom(socket_fd, packet, SIZE_DATA, 0, 
                (struct sockaddr *) &server, &size_sockaddr_in) == -1)
        {
            perror("Recvfrom");
            free(message_send);
            free(packet);
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        struct iphdr *ip_header = (struct iphdr *)packet;

        udp_header = (struct udphdr *)(packet + sizeof(struct iphdr));

        if((ntohs(udp_header -> dest) == CLIENT_PORT))
        {
            struct in_addr address;
            memset(&address, 0, sizeof(struct in_addr));
            address.s_addr = ip_header -> saddr;

            printf("Server IP: %s\n", inet_ntoa(address));
            printf("Server port: %d\n", ntohs(udp_header -> source));
            printf("Message: %s\n", packet + sizeof(struct iphdr) + 
                    sizeof(struct udphdr));

            free(message_send);
            free(packet);

            close(socket_fd);

            break;
        }
    }

    exit(EXIT_SUCCESS);
}
