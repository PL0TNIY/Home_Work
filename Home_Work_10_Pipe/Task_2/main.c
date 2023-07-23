#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

#define LEN 7

int main()
{
    int fildes[2];
    char w_buffer[LEN] = "Hello!";
    char c_buffer[LEN];
    pid_t process;
    pipe(fildes);

    if(pipe(fildes) < 0)
    {
        printf("Error pipe");
        exit(1);
    }

    process = fork();

    if(process < 0)
    {
        printf("Error process");
        exit(1);
    }

    if(process == 0)
    {
        close(fildes[1]);
        read(fildes[0], c_buffer, sizeof(c_buffer));
        printf("Process child got: %s\n", c_buffer);
        close(fildes[0]);
        exit(0);
    }
    else
    {
        close(fildes[0]);
        write(fildes[1], w_buffer, LEN);
        close(fildes[1]);
        wait(NULL);
    }

    return 0;
}

