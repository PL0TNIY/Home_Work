#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define PORT 9171
#define SIZE_DATA 128
 
int main()
{
    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    struct sockaddr_in client;

    int socket_tcp_fd = socket(AF_INET, SOCK_STREAM, 0);

    if(socket_tcp_fd == -1)
    {
        perror("Socket TCP");
        exit(EXIT_FAILURE);
    }

    if(bind(socket_tcp_fd, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("Bind TCP");
        close(socket_tcp_fd);
        exit(EXIT_FAILURE);
    }

    int socket_udp_fd = socket(AF_INET, SOCK_DGRAM, 0);

    if(socket_udp_fd == -1)
    {
        perror("Socket UDP");
        close(socket_tcp_fd);
        exit(EXIT_FAILURE);
    }

    if(bind(socket_udp_fd, (const struct sockaddr *) &server, 
                sizeof(struct sockaddr_in)) == -1)
    {
        perror("Socket UDP");
        close(socket_tcp_fd);
        close(socket_udp_fd);
        exit(EXIT_FAILURE);
    }

    if(listen(socket_tcp_fd, 5) == -1)
    {
        perror("Listen");
        close(socket_tcp_fd);
        close(socket_udp_fd);
        exit(EXIT_FAILURE);
    }
    
    fd_set fd;
    FD_ZERO(&fd);
    FD_SET(socket_tcp_fd, &fd);
    FD_SET(socket_udp_fd, &fd);

    while(1)
    {
        printf("Server waiting TCP or UDP packet...\n\n");

        time_t current_time = time(NULL);

        fd_set copy = fd;

        if(select(FD_SETSIZE, &copy, NULL, NULL, NULL) == -1)
        {
            perror("Select");
            close(socket_tcp_fd);
            close(socket_udp_fd);
            exit(EXIT_FAILURE);
        }

        if(FD_ISSET(socket_tcp_fd, &copy))
        {
            printf("Server waiting connect client...\n");

            memset(&client, 0, sizeof(struct sockaddr_in));

            char message_recv[SIZE_DATA] = {0};
            char message_send[SIZE_DATA] = {0};

            int size_sockaddr_in = sizeof(struct sockaddr_in);
            int new_socket_tcp_fd = accept(socket_tcp_fd, 
                    (struct sockaddr *) &client, &size_sockaddr_in);

            if(new_socket_tcp_fd == -1)
            {
                perror("Accept");
                close(socket_tcp_fd);
                close(socket_udp_fd);
                exit(EXIT_FAILURE);
            }

            printf("Client connected to server!\n\n");
            printf("Server waiting message from client...\n");

            if(recv(new_socket_tcp_fd, message_recv, SIZE_DATA, 0) == -1)
            {
                perror("Recv");
                close(new_socket_tcp_fd);
                close(socket_tcp_fd);
                close(socket_udp_fd);
                exit(EXIT_FAILURE);
            }

            printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
            printf("Client port: %d\n", ntohs(client.sin_port));
            printf("Message: %s\n\n", message_recv);

            strcpy(message_send, ctime(&current_time));

            if(send(new_socket_tcp_fd, message_send, SIZE_DATA, 0) == -1)
            {
                perror("Recv");
                close(new_socket_tcp_fd);
                close(socket_tcp_fd);
                close(socket_udp_fd);
                exit(EXIT_FAILURE);
            }

            printf("Server send message to client!\n\n");

            close(new_socket_tcp_fd);
        }

        if(FD_ISSET(socket_udp_fd, &copy))
        {
            memset(&client, 0, sizeof(struct sockaddr_in));

            char message_recv[SIZE_DATA] = {0};
            char message_send[SIZE_DATA] = {0}; 

            int size_sockaddr_in = sizeof(struct sockaddr_in);

            printf("Server waiting message from client...\n");

            if(recvfrom(socket_udp_fd, message_recv, SIZE_DATA, 0, 
                        (struct sockaddr *) &client, &size_sockaddr_in) == -1)
            {
                perror("Recvfrom");
                close(socket_tcp_fd);
                close(socket_udp_fd);
                exit(EXIT_FAILURE);
            }

            printf("Client IP: %s\n", inet_ntoa(client.sin_addr));
            printf("Client port: %d\n", ntohs(client.sin_port));
            printf("Message: %s\n\n", message_recv);

            strcpy(message_send, ctime(&current_time));

            if(sendto(socket_udp_fd, message_send, SIZE_DATA, 0, 
                        (const struct sockaddr *) &client, size_sockaddr_in) == 
                    -1)
            {
                perror("Recvfrom");
                close(socket_tcp_fd);
                close(socket_udp_fd);
                exit(EXIT_FAILURE);        
            }

            printf("Server send message to client!\n\n");
        }
    }
}
