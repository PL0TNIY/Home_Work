#include "box.h"

void add_random_user(struct user_data *pointer)
{
    srand(time(NULL));

    char *random_name[10] = 
    {
        "Ronnie",
        "Alice",
        "Oliver",
        "Viola",
        "Yury",
        "Eva",
        "Arnold",
        "Melissa",
        "Victor",
        "Leona"
    };
    char *random_surname[10] =
    {
        "White",
        "Smith",
        "Reed",
        "Lee",
        "Young",
        "Simpson",
        "Miller",
        "Coleman",
        "Allen",
        "Russell"
    };
    char *random_number[10] =
    {
        "89516666666",
        "89147777777",
        "89033333333",
        "89991111111",
        "89102222222",
        "89674444444",
        "89958888888",
        "89175555555",
        "89699999999",
        "89291234567"
    };

    for(int i = 0; i <= rand() % 10; i++)
    {
        strcpy(pointer -> name, random_name[rand() % 10]);
        strcpy(pointer -> surname, random_surname[rand() % 10]);
        strcpy(pointer -> number, random_number[rand() % 10]);
        
        pointer++;
    }
}
