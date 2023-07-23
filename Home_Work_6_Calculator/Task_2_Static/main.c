#include "calculator.h"
#include <stdio.h>

int main()
{
    int a;
    int b;
    int chois;

    do
    {
        printf("Menu:\n1 - sum;\n2 - sub;\n3 - mult;\n4 - div;\n5 - exit.\n");
        printf("Chois: ");
        scanf("%d", &chois);

        switch(chois)
        {
            case 1:
                printf("A = ");
                scanf("%d", &a);
                printf("B = ");
                scanf("%d", &b);
                printf("%d + %d = %d\n", a, b, sum(a, b));
                break;

            case 2:
                printf("A = ");
                scanf("%d", &a);
                printf("B = ");
                scanf("%d", &b);
                printf("%d - %d = %d\n", a, b, sub(a, b));
                break;

            case 3:
                printf("A = ");
                scanf("%d", &a);
                printf("B = ");
                scanf("%d", &b);
                printf("%d * %d = %d\n", a, b, mult(a, b));
                break;

            case 4:
                printf("A = ");
                scanf("%d", &a);
                printf("B = ");
                scanf("%d", &b);
                printf("%d / %d = %d\n", a, b, div(a, b));
                break;
        }

    }while(chois != 5);

    return 0;
}
