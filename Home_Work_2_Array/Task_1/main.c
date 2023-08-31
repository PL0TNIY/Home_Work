#include <stdio.h>
#include <stdlib.h>

#define n 3

int main()
{
    int array[n][n];
    int counter = 0;

    for(int i = 0; i <= n - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            counter++;
            array[i][j] = counter;

            printf("%d\t", array[i][j]);
        }

        printf("\n");
    }

    exit(EXIT_SUCCESS);
}
