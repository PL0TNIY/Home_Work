#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 128

int main()
{
    char *data;

    int fd = shm_open("asd", O_RDWR, 00700);

    if(fd == -1)
    {
        perror("Shm_open");
        exit(EXIT_FAILURE);
    }

    data = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

    if (data == MAP_FAILED)
    {
        perror("Mmap");
        exit(EXIT_FAILURE);
    }

    strcpy(data, "Hello, I'm client!");

    while(strcmp(data, "Hello, I'm server!") != 0)
    {
    
    }
    
    printf("Message: %s\n", data);

    munmap(data, SIZE);
    
    close(fd);

    exit(EXIT_SUCCESS);
}

