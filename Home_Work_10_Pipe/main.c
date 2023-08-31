#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>

#define SIZE 128

int main() 
{
    char buffer_1[SIZE];
    char buffer_2[SIZE];
    char message_1[SIZE] = "Hello_1!";
    char message_2[SIZE] = "Hello_2!";

    int fd_1[2]; 
    int fd_2[2];

    pid_t process;

    if(pipe(fd_1) == -1)
    {
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    if(pipe(fd_2) == -1)
    {
        perror("Pipe");
        exit(EXIT_FAILURE);
    }

    if((process = fork()) == -1) 
    {
        perror("Fork");
        exit(EXIT_FAILURE);
    }

    if (process > 0) 
    {
        close(fd_1[0]);

        if(write(fd_1[1], message_1, strlen(message_1)) == -1)
        {
            perror("Write");
            exit(EXIT_FAILURE);
        }

        printf("Parent write message in pipe №1\n");

        close(fd_2[1]);
    }
    else
    {
        close(fd_2[0]);
        close(fd_1[1]);

        printf("Child read message in pipe №1\n");

        if(read(fd_1[0], buffer_2, SIZE) == -1)
        {
            perror("Read");
            exit(EXIT_FAILURE);
        }

        printf("Message: %s\n", buffer_2);

        close(fd_1[0]);

        printf("Child write message in pipe №2\n");

        if(write(fd_2[1], message_2, strlen(message_2)) == -1)
        {
            perror("Write");
            exit(EXIT_FAILURE);
        }
        
        close(fd_2[1]);
    }

    sleep(5);

    if(process > 0)
    {
        close(fd_2[1]);
        
        printf("Parent read message in pipe №2\n");

        if(read(fd_2[0], buffer_1, SIZE) == -1)
        {
            perror("Read");
            exit(EXIT_FAILURE);
        }

        printf("Message: %s\n", buffer_1);
        
        close(fd_2[0]);
    }

    exit(EXIT_SUCCESS);
}
