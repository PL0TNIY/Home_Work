#include <arpa/inet.h>
#include <netinet/in.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define ADDRESS "127.0.0.1"
#define SERVER_PORT 9171
#define NUMBER_CLIENT 5
#define SIZE_DATA 128

struct variable
{
    int thread_id;
    int new_socket_fd;
};

pthread_t thread_handling[NUMBER_CLIENT];

void *thread_function(void *arg)
{
    char message_send[SIZE_DATA] = "Hello, I'm server!";
    char message_recv[SIZE_DATA] = {0};

    struct variable *pointer  = (struct variable *)arg;
    
    int thread_id = pointer -> thread_id;
    int new_socket_fd = pointer -> new_socket_fd;

    recv(new_socket_fd, message_recv, SIZE_DATA, 0);

    printf("Message: %s\n\n", message_recv);

    send(new_socket_fd, message_send, SIZE_DATA, 0);

    printf("Server send message to server!\n\n");

    close(new_socket_fd);    
    close(thread_handling[thread_id]);
}

int main()
{   
    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    struct sockaddr_in client;
    
    struct variable info[NUMBER_CLIENT];

    struct variable *pointer = &info[0];

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

    if(listen(socket_fd, NUMBER_CLIENT) == -1)
    {
        perror("Listen");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        for(int i = 0; i < NUMBER_CLIENT; i++)
        {
            memset(&client, 0, sizeof(struct sockaddr_in));

            int size_sockaddr_in = sizeof(struct sockaddr_in);
            int new_socket_fd = accept(socket_fd, 
                    (struct sockaddr *) &client, &size_sockaddr_in);

            if(new_socket_fd == -1)
            {
                perror("Accept");
                close(socket_fd);
                exit(EXIT_FAILURE);
            }

            info[i].thread_id = i;
            info[i].new_socket_fd = new_socket_fd;

            if(pthread_create(&thread_handling[i], NULL, thread_function, 
                        pointer + i) != 0)
            {
                    perror("Pthread_create");
                    close(thread_handling[i]);
                    close(new_socket_fd);
                    close(socket_fd);
                    exit(EXIT_FAILURE);
            }
        }
    }
}
