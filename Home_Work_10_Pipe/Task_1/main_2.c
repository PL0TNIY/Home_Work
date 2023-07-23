#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define LEN 1000

int main()
{
    int fd;
    char *fifo = "./test";
    char write_message_2[LEN];
    char read_message_2[LEN];

    while(1)
    {
        fd = open(fifo, O_RDONLY);
        read(fd, read_message_2, sizeof(read_message_2));
        puts("User_1:");
        puts(read_message_2);
        close(fd);

        fd = open(fifo, O_WRONLY);
        puts("Message:");
        fgets(write_message_2, LEN, stdin);
        write(fd, write_message_2, strlen(write_message_2) + 1);
        close(fd);   
    }

    return 0; 
}

