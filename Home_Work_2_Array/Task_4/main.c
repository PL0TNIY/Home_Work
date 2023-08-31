#include <stdio.h>
#include <stdlib.h>

#define n 5

int main()
{
    int array[n][n];
    int counter = 1;

    for(int move = 0; move <= n - 2; move++)
    {
        for(int q = 0 + move; q <= n - 1 - move; q++)
        {
            array[n - n + move][q] = counter;
            counter++;
        }

        counter--;

        for(int w = 0 + move; w <= n - 1 - move; w++)
        {   
            array[w][n - 1 - move] = counter;
            counter++;
        }

        counter--;

        for(int e = n - 1 - move; e >= 0 + move; e--)
        {
            array[n - 1 - move][e] = counter;
            counter++;
        }

        counter--;

        for(int r = n - 1 - move; r >= n - (n - 1) + move; r--)
        {
            array[r][n - n + move] = counter;
            counter++;
        }
    }

    for(int i = 0; i <= n - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            printf("%d\t", array[i][j]);
        }

        printf("\n");
    }

    exit(EXIT_SUCCESS);
}
