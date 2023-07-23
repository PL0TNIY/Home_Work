#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t process;

    switch(process = fork())
    {
        case -1:
            perror("Process");
            exit(1);

        case 0:
            printf("Process child\n");
            printf("PDI: %d\n", getpid());
            printf("Parent PDI: %d\n", getppid());
            exit(0);

        default:
            printf("Process parent\n");
            printf("PID: %d\n", getpid());
            printf("Child PDI: %d\n", process);
    }

    return 0;
}
