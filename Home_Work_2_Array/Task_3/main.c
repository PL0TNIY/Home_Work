#include <stdio.h>

#define n 9

int main()
{
    int array[n][n];
    int digit = 0b00000001;
    int revers_count = n;

    for(int i = 0; i <= n - 1; i++)
    {
        for(int j = 0; j <= n - 1; j++)
        {
            if(j < (revers_count - 1))
            {
                array[i][j] = digit >> 1;
                printf("%d", array[i][j]);
            }
            else
            {
                array[i][j] = digit;
                printf("%d", array[i][j]);
            }
        }
        revers_count--;
        printf("\n");
    }

    return 0;
}
