#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main()
{
    char name_file[100]; 
    char content_file[777];
    int choice;

    printf("Menu:\n1.creat file;\n2.write file;\n3.read file;\n4.exit.\n");

    do
    {  
        printf("Choice:\n");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter name file:\n");
                scanf("%s", name_file);
                int creat_file = creat(name_file, 00700);
                break;

            case 2:
                printf("Enter name file:\n");
                scanf("%s", name_file);
                int write_file = open(name_file, O_WRONLY | O_APPEND);
                printf("Enter content file:\n");
                scanf("%s", content_file);
                write(write_file, content_file, strlen(content_file));
                close(write_file);
                break;

            case 3:
                printf("Enter name file:\n");
                scanf("%s", name_file);
                int read_file = open(name_file, O_RDONLY);
                read(read_file, content_file, 777);
                printf("File content:\n%s\n", content_file);
                close(read_file);
                break;
        }

    }while(choice != 5);

    return 0;
}

