#include "box.h"

int main()
{
    int menu;

    struct user_data *ptr = calloc(10 * sizeof(struct user_data), sizeof(char));

    add_random_user(ptr);

    printf("Menu:\n1.show list;\n2.search user;\n3.add user;\n4.delete user;\n5.exit.\n");

    do
    {
        printf("\n");
        printf("Choise: ");
        scanf("%d", &menu);
        printf("\n");

        switch(menu)
        {
            case 1: show_user(ptr);
                    break;

            case 2: search_user(ptr);
                    break;

            case 3: add_user(ptr);
                    break;

            case 4: delete_user(ptr);
                    break;
        }

    }while(menu != 5);

    exit(EXIT_SUCCESS);
}
