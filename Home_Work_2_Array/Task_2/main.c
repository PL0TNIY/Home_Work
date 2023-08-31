#include <stdio.h>
#include <stdlib.h>

#define n 5

int main()
{
    int array[n]; 
    int counter = 0;

    for(int i = 0; i <= n - 1; i++)
    {
        counter++;
        array[i] = counter;
    }

    for(int j = 0; j <= n - 1; j++)
    {
        counter--;

        printf("%-2d", array[counter]);
    }

    exit(EXIT_SUCCESS);
}
