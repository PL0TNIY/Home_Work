#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>

int main()
{
    char name_file[100]; 
    char content_file[777];

    int choice;

    printf("Menu:\n1.creat file;\n2.write file;\n3.read file;\n4.exit.\n");

    do
    {  
        printf("\n");
        printf("Choice: ");
        scanf("%d", &choice);

        switch(choice)
        {
            case 1:
                printf("Enter name file:\n");
                scanf("%s", name_file);

                int creat_file = creat(name_file, 00700);

                if(creat_file == - 1)
                {
                    perror("Creat_file");
                    exit(EXIT_FAILURE);
                }

                close(creat_file);

                break;

            case 2:
                printf("Enter name file:\n");
                scanf("%s", name_file);

                int write_file = open(name_file, O_WRONLY | O_APPEND);
                
                if(write_file == -1)
                {
                    perror("Write_file");
                    exit(EXIT_FAILURE);
                }

                printf("Enter content file:\n");
                scanf("%s", content_file);

                write(write_file, content_file, strlen(content_file));

                close(write_file);
                
                break;

            case 3:
                printf("Enter name file:\n");
                scanf("%s", name_file);

                int read_file = open(name_file, O_RDONLY);

                if(read_file == -1)
                {
                    perror("Read_file");
                    exit(EXIT_FAILURE);
                }

                read(read_file, content_file, 777);

                printf("File content:\n%s\n", content_file);

                close(read_file);

                break;
        }

    }while(choice != 4);

    exit(EXIT_SUCCESS);
}
