#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main()
{
    pid_t process;
    int count_parent = 1;
    int count_child = 0;

    printf("PDI parent №%d: %d\n\n", count_parent, getpid());

    for(int i = 0; i <= 1; i++)
    {
        count_parent++;
        count_child++;

        process = fork();

        if(process < 0)
        {
            printf("Error");
        }

        if(process == 0)
        {   
            printf("Process child №%d(parent №%d)\n", count_child, count_parent);
            printf("PDI child: %d\n", getpid());
            printf("PDI parent: %d\n\n", getppid());
            
            for(int j = 0; j <= 1; j++)
            {   
                process = fork();

                if(process < 0)
                {
                    printf("Error");
                }

                if(process == 0)
                {
                    printf("Process child\n");
                    printf("PDI child: %d\n", getpid());
                    printf("PDI parent: %d\n\n", getppid());
                    exit(0);
                }
                else
                {
                    wait(NULL);
                }
            }
            exit(0);
        }
        else
        {
            wait(NULL);
        }
    }

    return 0; 
}

