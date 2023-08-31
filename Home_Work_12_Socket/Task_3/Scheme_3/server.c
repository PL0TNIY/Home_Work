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

int thread_ready[NUMBER_CLIENT] = {0};
int file_descriptor[NUMBER_CLIENT] = {0};

void *thread_function(void *arg)
{
    char message_send[SIZE_DATA] = "Hello, I'm server!";

    int *pointer_thread_id = (int *)arg;
    int thread_id = *pointer_thread_id;

    while(1)
    {
        thread_ready[thread_id] = thread_id;

        if(file_descriptor[thread_id] != 0)
        {
            thread_ready[thread_id] = -1;

            char message_recv[SIZE_DATA] = {0};

            recv(file_descriptor[thread_id], message_recv, SIZE_DATA, 0);

            printf("Message: %s\n\n", message_recv);

            send(file_descriptor[thread_id], message_send, SIZE_DATA, 0);

            printf("Server send message to server!\n\n");

            close(file_descriptor[thread_id]);

            file_descriptor[thread_id] = 0;
        }
    }
}

int main()
{
    struct sockaddr_in server;
    memset(&server, 0, sizeof(struct sockaddr_in));
    server.sin_family = AF_INET;
    server.sin_port = htons(SERVER_PORT);
    server.sin_addr.s_addr = inet_addr(ADDRESS);

    struct sockaddr_in client;

    int index[NUMBER_CLIENT];

    void *pointer_index;

    pthread_t thread_handling[NUMBER_CLIENT];

    for(int a = 0; a < NUMBER_CLIENT; a++)
    {
        index[a] = a;

        pointer_index = &index[a];

        if(pthread_create(&thread_handling[a], NULL, thread_function, 
                    pointer_index) != 0)
        {
                perror("Pthread_create");
                exit(EXIT_FAILURE);
        }
    }

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

    if(listen(socket_fd, NUMBER_CLIENT))
    {
        perror("Listen");
        close(socket_fd);
        exit(EXIT_FAILURE);
    }

    while(1)
    {
        for(int b = 0; b < NUMBER_CLIENT; b++)
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

            int c = 0;

            while(1)
            {
                if(thread_ready[c] == c)
                {
                    file_descriptor[c] = new_socket_fd;
                    break;
                }

                c++;

                if(c == NUMBER_CLIENT)
                {
                    c = 0;
                }
            }
        }
    }
}
