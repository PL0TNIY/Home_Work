#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

int main()
{
    int counter = 0;

    pid_t process;

    process = fork();

    if(process == -1)
    {
        perror("Process");
        exit(EXIT_FAILURE);
    }

    if(process == 0)
    {
        while (1)
        {
            counter++;
            printf("Counter = %d\n", counter);
        }
    }
    else 
    {   
        sleep(3);

        int kill_process = kill(process, SIGKILL);

        if(kill_process == -1) 
        {
            perror("Kill_process");
            exit(EXIT_FAILURE);
        }

        printf("Parent killed child: %d\n", process);
    }

    exit(EXIT_SUCCESS);
}
