#include <pthread.h>
#include <stdio.h>

void *fun(void *ptr)
{
    int *ptr_1 = ptr;
    printf("thread %d\n", *ptr_1);
}

int main()
{
    pthread_t thread[10];
    int array[10];
    
    for(int i = 0; i <= 9; i++)
    {   
        array[i] = i;
        pthread_create(&thread[i], NULL, fun, &array[i]);
    }

    for(int j = 0; j <= 9; j++)
    {
        pthread_join(thread[j], NULL);
    }

    return 0;
}
