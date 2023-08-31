#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    pid_t process;

    switch(process = fork())
    {
        case -1:
            perror("Process");
            exit(EXIT_FAILURE);

        case 0:
            printf("Process child\n");
            printf("PDI: %d\n", getpid());
            printf("Parent PDI: %d\n", getppid());
            exit(EXIT_SUCCESS);

        default:
            printf("Process parent\n");
            printf("PID: %d\n", getpid());
            printf("Child PDI: %d\n\n", process);
    }
}
