#include "box.h"

void add_user(struct user_data *pointer)
{
    char add_name[12];
    char add_surname[12];
    char add_number[12];

    printf("Surname:");
    scanf("%s", add_surname);

    printf("Name:");
    scanf("%s", add_name);

    printf("Number:");
    scanf("%s", add_number);

    for(int i = 0; i < 10; i++)
    {
        if(strcmp(pointer -> name, "") == 0 || (strcmp(pointer -> name, " ") == 
                    0))
        {
            strcpy(pointer -> surname, add_surname);
            strcpy(pointer -> name, add_name);
            strcpy(pointer -> number, add_number);

            break;
        }

        pointer++;
    }
}
