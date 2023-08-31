#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>

#define NUMBER_THREAD 1000

long int digit = 0;

void *fun(void *arg)
{
    int *pthread = (int *)arg;

    digit += 100000;

    printf("Digit[%d] = %ld\n", *pthread, digit);
}

int main()
{
    pthread_t thread[NUMBER_THREAD];
    
    int index[NUMBER_THREAD];
    
    for(int i = 0; i < NUMBER_THREAD; i++)
    {   
        index[i] = i;

        pthread_create(&thread[i], NULL, fun, &index[i]);
    }

    for(int j = 0; j < NUMBER_THREAD; j++)
    {
        pthread_join(thread[j], NULL);
    }

    exit(EXIT_SUCCESS);
}
