# Queue

The behaviour of a Queue is similar to a First In First Out (FIFO) memory.

The Queue implementation provides APIs to enqueue (push) and dequeue (pop)
values from the queue.

## Example

The following code example initializes the queue, writes to the queue, and
then gets elements from the queue.

```c
#include <stdio.h>
#include <stdlib.h>
#include "queue.h"

int main(int argc, char** argv)
{
    int ret;
    int error;
    int queue_array[10] = {0};
    queue_t queue;

    queue_init(&queue, queue_array, 10);

    error = queue_enqueue(&queue, 1);
    error = queue_enqueue(&queue, 2);
    error = queue_enqueue(&queue, 3);

    queue_print(&queue);

    error = queue_dequeue(&queue, &ret);
    printf("Value 1: %d", ret);
    error = queue_dequeue(&queue, &ret);
    printf("Value 2: %d", ret);
    error = queue_dequeue(&queue, &ret);
    printf("Value 3: %d", ret);
}
```

## Initialize a queue

To initialize a queue structure use the function `queue_init()`.

```c
int queue_array[10] = {0};
queue_t queue;
queue_init(&queue, queue_array, 10);
```

## Enqueue elements

To add an element to the queue use the function `queue_enqueue` passing as
parameters the queue and the value to add.

```c
queue_enqueue(&queue, 10);
```

## Dequeue elements

To get an element from the list use the function `queue_dequeue` passing as
parameters the queue and a pointer to the integer variable.

```c
int retval;

int error = queue_dequeue(&queue, &retval);
```

## Print elements in a queue

To print the elements of a list use the function `queue_print` passing as
parameter the queue.

```c
queue_print(&queue);
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

