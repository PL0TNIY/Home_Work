#include <stdio.h>
#include <string.h> 
#include <stdlib.h>
#include <time.h>

struct user_data
{
    char name[11];
    char surname[11];
    char number[12];
};

void random_user(struct user_data *t)
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
        strcpy(t -> name, random_name[rand() % 10]);
        strcpy(t -> surname, random_surname[rand() % 10]);
        strcpy(t -> number, random_number[rand() % 10]);
        t++;
    }
}

void show_user(struct user_data *z)
{
    printf("____________PHONE BOOK____________\n");

    for(int i = 0; i <= 9; i++)
    {
        printf("%d.%s %s %s\n", i + 1, z -> surname, z -> name, z -> number);
        printf("__________________________________\n");       
        z++;
    }
}

void search_user(struct user_data *x)
{
    char search[12];

    printf("Enter name or surname or number: ");
    scanf("%s", search);

    for(int i = 0; i <= 9; i++)
    {
        if((strcmp(x -> name, search) == 0) || (strcmp(x -> surname, search) == 0) || (strcmp(x -> number, search) == 0))
        {
            printf("%d.%s %s %s\n", i + 1, x -> surname, x -> name, x -> number);
        }
        x++;
    }

}

void delete_user(struct user_data *q)
{
    char delete_name[11];
    char delete_surname[11];
    char delete_number[12];
    
    printf("Surname:");
    scanf("%s", delete_surname);
    printf("Name:");
    scanf("%s", delete_name);
    printf("Number:");
    scanf("%s", delete_number);

    for(int i = 0; i <= 9; i++)
    {
        if((strcmp(q -> surname, delete_surname) == 0) & (strcmp(q -> name, delete_name) == 0) & (strcmp(q -> number, delete_number) == 0))
        {
            strcpy(q -> surname, " ");
            strcpy(q -> name, " ");
            strcpy(q -> number, " ");
        }
        else
        {
            q++;
        }
    }
}

void add_user(struct user_data *y)
{
    char add_name[11];
    char add_surname[11];
    char add_number[12];

    printf("Surname:");
    scanf("%s", add_surname);
    printf("Name:");
    scanf("%s", add_name);
    printf("Number:");
    scanf("%s", add_number);

    for(int i = 0; i <= 9; i++)
    {
        if(strcmp(y -> name, "") == 0 ||  (strcmp(y -> name, " ") == 0))
        {
            strcpy(y -> surname, add_surname);
            strcpy(y -> name, add_name);
            strcpy(y -> number, add_number);
            break;
        }
        y++;
    }
}

int main()
{
    int menu;
    struct user_data search[10] = {};
    struct user_data *ptr = &search[0];
    random_user(ptr);

    printf("Menu:\n1.show list;\n2.search user;\n3.delete user;\n4.add user;\n5.exit.\n");
    
    do
    {
        printf("Choise: ");
        scanf("%d", &menu);

        switch(menu)
        {
            case 1: show_user(ptr);
                    break;

            case 2: search_user(ptr);
                    break;

            case 3: delete_user(ptr);
                    break;

            case 4: add_user(ptr);
                    break;
        }

    }while(menu != 5);
    
    return 0;
}
