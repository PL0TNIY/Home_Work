#include <stdio.h>

#define n 3

int main()
{
    int array[n][n];
    int count = 0;

    for(int i = 0; i <= n - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            count++;
            array[i][j] = count;
            printf("%d\t", array[i][j]);
        }
        printf("\n");
    }

    return 0;
}
