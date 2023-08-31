#include "box.h"

void delete_user(struct user_data *pointer)
{
    char delete_name[12];
    char delete_surname[12];
    char delete_number[12];
    
    printf("Surname:");
    scanf("%s", delete_surname);

    printf("Name:");
    scanf("%s", delete_name);

    printf("Number:");
    scanf("%s", delete_number);

    for(int i = 0; i < 10; i++)
    {
        if((strcmp(pointer -> surname, delete_surname) == 0) & 
                (strcmp(pointer -> name, delete_name) == 0) & 
                (strcmp(pointer -> number, delete_number) == 0))
        {
            strcpy(pointer -> surname, " ");
            strcpy(pointer -> name, " ");
            strcpy(pointer -> number, " ");
        }
        else
        {
            pointer++;
        }
    }
}
