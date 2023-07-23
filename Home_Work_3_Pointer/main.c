#include <stdio.h>

int main()
{
    unsigned int digit = 917;
    int byte;
    unsigned char *ptr;
    ptr = &digit;

    printf("Digit: %u\n", digit);

    for(int i = 0; i <= sizeof(digit) - 1; i++)
    {
        printf("%d Byte: %u\t Address: %p\n", i + 1, *(ptr + i), ptr + i);
    }

    printf("Replace byte: ");
    scanf("%d", &byte);

    switch(byte)
    {
        case 1:
            *ptr += 7;
            break;

        case 2:
            ptr++;
            *ptr = *ptr + 9;
            break;

        case 3:
            ptr += 2;
            *ptr += 11;
            break;

        case 4:
            ptr += 3;
            *ptr += 13;
            break;
    }

    printf("Result digit: %u\n", digit);

    return 0;
}
