#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include "Queue.h"

#define QUEUESIZE   sizeof(uint16_t) * 10

void 
printUint16(const void *data)
{
    printf("%d :: ", *((const uint16_t *) data));
}

void *
writeThread(void* arg)
{
    uint16_t i, j;
    queue_t* queue = (queue_t*) arg;

    for (i = 0; i <= 10; i++)
    {
        j = i * 100;
        queue_enqueue(queue, (void *) &j);
        sleep(1);
    }

    pthread_exit(NULL);
}

void *
readThread(void* arg)
{
   uint8_t i, error;
   uint16_t ret;
   uint16_t print_data;
   queue_t* queue = (queue_t*) arg;
   
    while(queue_count(queue) == 0)
    {
        sleep(1);
    }

    for(i = 0; i <= 10; i++)
    {
        error = queue_dequeue(queue, (void *) &ret);
        printf("%d <- ", ret);
        queue_print(queue, printUint16, (void *) &print_data);
        printf("\n");
        sleep(2);
    }

    pthread_exit(NULL);
}

int
main(int argc, char** argv)
{
    queue_array_t queue_array[QUEUESIZE] = {0};
    queue_t queue;
    pthread_t writer;
    pthread_t reader;

    queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));

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
