#include "box.h"

void search_user(struct user_data *pointer)
{
    char search[12];
    
    printf("Enter name or surname or number: ");
    scanf("%s", search);
    printf("\n");

    for(int i = 0; i < 10; i++)
    {
        if((strcmp(pointer -> name, search) == 0) || 
                (strcmp(pointer -> surname, search) == 0) || 
                (strcmp(pointer -> number, search) == 0))
        {
            printf("%d.%s %s %s\n", i + 1, pointer -> surname, pointer -> name, 
                    pointer -> number);
        }

        pointer++;
   }
}
