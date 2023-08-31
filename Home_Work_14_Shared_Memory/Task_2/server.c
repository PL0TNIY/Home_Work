#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/mman.h>
#include <unistd.h>

#define SIZE 128

int main() 
{
  char *data;
  char *message = "Hello, I'm server!";

  int fd = shm_open("asd", O_CREAT | O_RDWR, 00700);

  if(fd == -1)
  {
      perror("Shm_open");
      exit(EXIT_FAILURE);
  }

  if(ftruncate(fd, SIZE) == -1)
  {
      perror("Ftruncate");
      exit(EXIT_FAILURE);
  }

  data = mmap(NULL, SIZE, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);

  if(data == MAP_FAILED)
  {
      perror("Mmap");
      exit(EXIT_FAILURE);
  }

  while(1)
  {
      if(strcmp(data, "Hello, I'm client!") == 0) 
      {
          printf("Client: %s\n", data);
          strcpy(data, message);
      }
  }
}

