#include <stdio.h>
#include <stdlib.h>
#include <string.h> 
#include <time.h>

struct user_data
{
    char name[12];
    char surname[12];
    char number[12];
};

void add_random_user(struct user_data *pointer);

void show_user(struct user_data *pointer);

void search_user(struct user_data *pointer);

void add_user(struct user_data *pointer);

void delete_user(struct user_data *pointer);
