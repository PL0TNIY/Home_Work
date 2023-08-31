#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/msg.h>
#include <sys/wait.h>

#define SIZE 128

struct message
{
  long type;

  char message[SIZE];
};

int main()
{
    struct message send;
    memset(&send, 0, sizeof(struct message));
    send.type = 1;
    strcpy(send.message, "Hello, I'm client!");

    struct message recv;
    memset(&recv, 0, sizeof(struct message));
    
    key_t key;
    
    key = ftok("server", 1);

    if(key == -1)
    {
        perror("Key");
        exit(EXIT_FAILURE);
    }

    int queue_id = msgget(key, IPC_CREAT | 00700);

    if(msgsnd(queue_id, &send, sizeof(send.message), 0) == -1)
    {
        perror("Msgrcv");
        exit(EXIT_FAILURE);
    }

    if(msgrcv(queue_id, &recv, SIZE, 2, 0) == -1)
    {
        perror("Msgrcv");
        exit(EXIT_FAILURE);
    }

    printf("Message: %s\n", recv.message);
}
