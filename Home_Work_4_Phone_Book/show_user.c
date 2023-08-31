#include "box.h"

void show_user(struct user_data *pointer)
{
    for(int i = 0; i < 10; i++)
    {
        printf("%d.%s %s %s\n", i + 1, pointer -> surname, pointer -> name, 
                pointer -> number);

        pointer++;
    }
}
