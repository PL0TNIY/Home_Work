#include <stdio.h>

#define n 5

int main()
{
    int array[n]; 
    int count = 0;

    for(int i = 0; i <= n - 1; i++)
    {
        count++;
        array[i] = count;
    }

    for(int j = 0; j <= n - 1; j++)
    {
        count--;
        printf("%-2d", array[count]);
    }

    return 0;
}
