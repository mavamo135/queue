The behaviour of a Queue is similar to a First In First Out (FIFO) memory.

The Queue implementation provides APIs to enqueue (push) and dequeue (pop)
values from the queue. It can be used with diferrent data types and doesn´t 
use malloc so it can be used on resource constrained devices.

## Example

The following code example initializes the queue, writes to the queue, and
then gets elements from the queue.

```c
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

#define QUEUESIZE   sizeof(uint16_t) * 10

int main(int argc, char** argv)
{
    uint8_t error, i;
    uint16_t ret;
    const uint16_t data[3] = {0, 1, 2};
    queue_array_t queue_array[QUEUESIZE] = {0};
    queue_t queue;

    queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));

    for (i = 0; i < 3; i++)
    {
        error = queue_enqueue(&queue, (void *) &data[i]);
    }

    for (i = 0; i < 3; i++)
    {
        error = queue_dequeue(&queue, (void *) &ret));
        printf("Value %d: %d", i, ret);
    }
}
```

## Initialize a queue

To initialize a queue structure use the function `queue_init()`.

```c
#define QUEUESIZE   sizeof(uint16_t) * 10

queue_array_t queue_array[QUEUESIZE] = {0};
queue_t queue;

queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
```

## Enqueue elements

To add an element to the queue use the function `queue_enqueue` passing as
parameters the queue and a pointer to the variable with the value to add.

```c
uint16_t data = 10;
uint8_t error = queue_enqueue(&queue, (void *) &data);
```

## Dequeue elements

To get an element from the list use the function `queue_dequeue` passing as
parameters the queue and a pointer to the variable with the correct type.

```c
uint16_t retval;
uint8_t error = queue_dequeue(&queue, (void *) &retval);
```

## Print elements in a queue

To print the elements of a list use the function `queue_print` passing as
parameter the queue, a pointer to the function that correctly prints the data
according to the data type and a pointer to a variable with the correct data
type used to store every data element of the queue which is passed to the print
function.

```c
uint16_t print_data;
queue_print(&queue, printFn, (void *) &print_data);
```

## Build

To build the project use the following command in the root directory
of the project.

    $ make

## Tests

To build the project tests use the following commands in the tests directory
of the project.

    $ git clone https://github.com/ThrowTheSwitch/Unity.git
    $ make

