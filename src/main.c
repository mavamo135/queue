#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Queue.h"

void *writeThread(void* arg)
{
    int i;
    queue_t* queue = (queue_t*) arg;

    for (i = 0; i <= 10; i++)
      {
          printf("Write: %d\n", i);
          queue_enqueue(queue, i);
          sleep(1);
      }

    pthread_exit(NULL);
}

void *readThread(void* arg)
{
   int i, ret;
   queue_t* queue = (queue_t*) arg;
   
    while(queue_count(queue) == 0)
            sleep(1);

    for(i = 0; i <= 10; i++)
      {
          queue_dequeue(queue, &ret);
          printf("Read: %d\n", ret);
          sleep(2);
      }

    pthread_exit(NULL);
}

int
main(int argc, char** argv)
{
    queue_t queue;
    pthread_t writer;
    pthread_t reader;

    queue_init(&queue);

    if (pthread_create(&writer, NULL, writeThread, (void*) &queue))
      {
          printf("Error creating write thread.\n");
          exit(EXIT_FAILURE);
      }

    if (pthread_create(&reader, NULL, readThread, (void*) &queue))
      {
          printf("Error creating read thread.\n");
          exit(EXIT_FAILURE);
      }

    pthread_join(writer, NULL);
    pthread_join(reader, NULL);

    exit(EXIT_SUCCESS);
}
