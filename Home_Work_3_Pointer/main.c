#include <stdio.h>
#include <stdlib.h>

int main()
{
    unsigned char *pointer;

    int byte;
    unsigned int digit = 917;

    pointer = &digit;

    printf("Digit: %u\n", digit);

    for(int i = 0; i <= sizeof(digit) - 1; i++)
    {
        printf("%d Byte: %u\t Address: %p\n", i + 1, *(pointer + i), 
                pointer + i);
    }

    printf("Replace byte: ");
    scanf("%d", &byte);

    switch(byte)
    {
        case 1:
            *pointer += 7;
            break;

        case 2:
            pointer++;
            *pointer += 9;
            break;

        case 3:
            pointer += 2;
            *pointer += 11;
            break;

        case 4:
            pointer += 3;
            *pointer += 13;
            break;
    }

    printf("Result digit: %u\n", digit);

    exit(EXIT_SUCCESS);
}
