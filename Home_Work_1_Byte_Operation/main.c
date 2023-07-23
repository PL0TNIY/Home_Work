#include <stdio.h>

int main()
{
    unsigned long int digit = 0xaabbccdd;
    int replace_byte;
    unsigned long int new_byte;

    printf("Digit: %lx\n", digit);

    for(int i = 0; i < 4; i++)
    {
        printf("%d Byte: %lx\n", i + 1, (digit >> (8 * i)) & 0xff);
    }

    printf("Replace byte: ");
    scanf("%d", &replace_byte);
    printf("New byte: ");
    scanf("%lx", &new_byte);

    switch(replace_byte)
    {
        case 1: 
            digit &= 0xffffff00; 
            digit |= new_byte;
            break;

        case 2: 
            digit &= 0xffff00ff;
            digit |= (new_byte << 8);
            break;

        case 3: 
            digit &= 0xff00ffff;
            digit |= (new_byte << 16);
            break;

        case 4: 
            digit &= 0x00ffffff;
            digit |= (new_byte << 24);
            break;
    }

    printf("New digit: %lx\n", digit);

    return 0;
}
