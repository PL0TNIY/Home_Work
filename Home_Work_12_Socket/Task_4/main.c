#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 6666
#define SIZE_DATA 128

int main()
{
    struct sockaddr_in sniffer;
    memset(&sniffer, 0, sizeof(struct sockaddr_in));
    sniffer.sin_family = AF_INET;
    sniffer.sin_port = htons(PORT);
    sniffer.sin_addr.s_addr = inet_addr(ADDRESS);
    
    struct sockaddr_in packet;

    int socket_fd = socket(AF_INET, SOCK_RAW, IPPROTO_UDP);

    if(socket_fd == -1)
    {
        perror("Socket");
        exit(EXIT_FAILURE);
    }
    
    while(1)
    {   
        memset(&packet, 0, sizeof(struct sockaddr_in));

        char message[SIZE_DATA] = {0};
        
        int size_sockaddr_in = sizeof(struct sockaddr_in);

        if(recvfrom(socket_fd, message, SIZE_DATA, 0, 
                    (struct sockaddr *) &packet, &size_sockaddr_in) == -1)
        {
            perror("Recvfrom");
            close(socket_fd);
            exit(EXIT_FAILURE);
        }

        printf("IP: %s\n", inet_ntoa(packet.sin_addr));
        printf("Port: %d\n", ntohs(packet.sin_port));
    }
}
