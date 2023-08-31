#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>

#define NUMBER_STORE 5
#define NUMBER_BUYER 3
#define START_VOLUME 1000
#define LIMIT_BUYER 10000
#define VOLUME_SUPPLIER 500
#define SPENDING 200

struct buyer
{
    int id;
    int limit;
};

struct supplier
{
    int volume;
};

int store[NUMBER_STORE];

pthread_mutex_t mutex[NUMBER_STORE];

void *buy(void *arg) 
{
    struct buyer *buyer = (struct buyer *)arg;

    int id = buyer -> id;
    int limit = buyer -> limit;

    while (limit > 0) 
    {
        int number_shop = rand() % NUMBER_STORE;

        pthread_mutex_lock(&mutex[number_shop]);

        if (store[number_shop] >= SPENDING)
        {
            store[number_shop] -= SPENDING;

            limit -= SPENDING;

            printf("Buyer №%d bought 200 units from shop %d\n", id + 1, 
                    number_shop + 1);
            printf("Buyer №%d must spend: %d\n\n", id + 1, limit);
        }

        pthread_mutex_unlock(&mutex[number_shop]);

        sleep(1);
    }

    printf("Buyer №%d spent all\n\n", id + 1);
}

void *supply(void *arg) 
{
    struct supplier *supplier = (struct supplier *)arg;

    int volume = supplier -> volume;

    while (1)
    {
        for (int i = 0; i < NUMBER_STORE; i++)
        {
            pthread_mutex_lock(&mutex[i]);

            if (store[i] <= VOLUME_SUPPLIER || store[i] == 0) 
            {
                store[i] += volume;

                printf("Supplier supplied %d units to store №%d\n\n", volume, 
                        i + 1);
            }

            pthread_mutex_unlock(&mutex[i]);
        }

        sleep(2);
    }
}

int main() 
{
    srand(time(NULL));

    struct buyer buyer[NUMBER_BUYER];

    for(int i = 0; i < NUMBER_BUYER; i++) 
    {   
        memset(&buyer[i], 0, sizeof(struct buyer));
        
        buyer[i].id = i;

        buyer[i].limit = LIMIT_BUYER;
    }

    struct supplier supplier;
    memset(&supplier, 0, sizeof(struct supplier));
    supplier.volume = VOLUME_SUPPLIER;

    for(int i = 0; i < NUMBER_STORE; i++)
    {
        store[i] = START_VOLUME;
        printf("Store №%d: %d\n\n", i + 1, store[i]);
    }

    for(int i = 0; i < NUMBER_STORE; i++) 
    {
        pthread_mutex_init(&mutex[i], NULL);
    }

    pthread_t thread_buyer[NUMBER_BUYER];

    for(int i = 0; i < NUMBER_BUYER; i++)
    {
        if(pthread_create(&thread_buyer[i], NULL, buy, &buyer[i]) != 0)
        {
            perror("Pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    pthread_t thread_supplier;

    if(pthread_create(&thread_supplier, NULL, supply, &supplier) != 0)
    {
        perror("Pthread create supplier");
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < NUMBER_BUYER; i++) 
    {
        pthread_join(thread_buyer[i], NULL);
    }

    pthread_cancel(thread_supplier);

    for (int i = 0; i < NUMBER_STORE; i++) 
    {
        pthread_mutex_destroy(&mutex[i]);
    }

    exit(EXIT_SUCCESS);
}
