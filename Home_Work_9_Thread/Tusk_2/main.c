#include <pthread.h>
#include <stdio.h>

long x = 0;

void *fun(void *ptr)
{
    long sum;

    for(int i = 0; i <= 999999; i++)
    {
        sum = x;
        sum++;
        x = sum;
    }
}

int main()
{
    pthread_t thread[1000];

    for(int i = 0; i <= 999; i++)
    {
        pthread_create(&thread[i], NULL, fun, NULL);
    }

    for(int i = 0; i <= 999; i++)
    {
        pthread_join(thread[i], NULL);
    }

    printf("x =  %ld\n", x);

    return 0;
}
