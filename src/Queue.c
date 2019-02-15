/******************************************************************************
* Title                 :   Queue source file 
* Filename              :   Queue.c
* Author                :   Maximiliano Valencia
* Origin Date           :   13/02/2019
* Version               :   1.0.0
* Compiler              :   gcc
* Target                :   STM32
* Notes                 :   None
******************************************************************************/
/*! @file        Queue.c
 *  @brief       Circular queue implementation
 *
 *  To use the queue implementation, include this header file as follows:
 *  @code
 *      #include "Queue.h"
 *  @endcode
 *
 *  ## Overview ##
 *  The behaviour of a Queue is similar to a First In First Out (FIFO) memory.
 * 
 *  ## Usage ##
 * 
 *  The Queue implementation provides APIs to enqueue (push) and dequeue (pop)
 *  values from the queue.
 * 
 *  The following code example initializes the queue, writes to the queue, and
 *  then gets elements from the queue.
 * 
 *  @code
 *      int ret;
 *      int error;
 *      int queue_array[10] = {0};
 *      queue_t queue;
 * 
 *      queue_init(&queue, queue_array, 10);
 * 
 *      error = queue_enqueue(&queue, 1);
 *      error = queue_enqueue(&queue, 2);
 *      error = queue_enqueue(&queue, 3);
 * 
 *      queue_print(queue);
 * 
 *      error = queue_dequeue(&queue, &ret);
 *      printf("Value 1: %d", ret);
 *      error = queue_dequeue(&queue, &ret);
 *      printf("Value 2: %d", ret);
 *      error = queue_dequeue(&queue, &ret);
 *      printf("Value 3: %d", ret);
 *  @endcode
 */
/******************************************************************************
* Includes
******************************************************************************/
#include "Queue.h"          /* For TODO: WHY ME? */

/******************************************************************************
* Module Preprocessor Constants
******************************************************************************/


/******************************************************************************
* Module Preprocessor Macros
******************************************************************************/


/******************************************************************************
* Module Typedefs
******************************************************************************/


/******************************************************************************
* Module Variable Definitions
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/
static int is_empty(queue_t* queue);
static int is_full(queue_t* queue);

/******************************************************************************
* Function Definitions
******************************************************************************/


/*****************************************************************************/
/*!
 * @addtogroup queue
 * @{
 */
/*****************************************************************************/

/*****************************************************************************/
/*!
 * 
 * @internal
 * 
 * \b Description:
 * 
 * This function is used to check if the queue is empty.
 * 
 * @param queue Queue to be checked.
 * 
 * @return Returns 1 if the queue is empty, 0 otherwise.
 *
 */
/*****************************************************************************/
static int
is_empty(queue_t* queue)
{
    if (queue->count == 0)
            return 1;  

    return 0;
}

/*****************************************************************************/
/*!
 * 
 * @internal
 * 
 * \b Description:
 * 
 * This function is used to check if the queue is full.
 * 
 * @param queue Queue to be checked.
 * 
 * @return Returns 1 if the queue is full, 0 otherwise.
 *
 */
/*****************************************************************************/
static int
is_full(queue_t* queue)
{
    if(queue->count == queue->size)
            return 1;  

    return 0;
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to initialize a queue structure.
 * 
 * @param queue Queue to be initialized.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      int queue_array[10] = {0};
 *      queue_t queue;
 *      queue_init(&queue, queue_array, 10);
 * @endcode
 *
 */
/*****************************************************************************/
void
queue_init(queue_t* queue, int* elementsArray, int size)
{
    // Initialize the structure
    queue->index = 0;
    queue->outdex = 0;
    queue->count = 0;
    queue->elements = elementsArray;
    queue->size = size;
    
    // Initialize R/W semaphore
    sem_init(&(queue->lock), 0, 1);
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to put a element in the queue.
 * 
 * @param queue Queue.
 * @param value Integer value to insert to the queue.
 * 
 * @return -1 if the queue is full (overflow), 0 otherwise.
 * 
 * \b Example:
 * @code
 *      int queue_array[10] = {0};
 *      queue_t queue;
 *      queue_init(&queue, queue_array, 10);
 * 
 *      int error = queue_enqueue(&queue, 1);
 * @endcode
 *
 */
/*****************************************************************************/
int
queue_enqueue(queue_t* queue, int value)
{
    int ret = -1;
    
    sem_wait(&(queue->lock));

    if (!is_full(queue))
      {
          queue->elements[queue->index] = value;
          queue->index = (queue->index+1) % queue->size;
          queue->count++;
          ret = 0;
      }

    sem_post(&(queue->lock));

    return ret;
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to get a element from the queue.
 * 
 * @param queue Queue.
 * @param value Integer variable pointer to write the value of the element.
 * 
 * @return -1 if the queue is empty (underflow), 0 otherwise.
 * 
 * \b Example:
 * @code
 *      int retval;
 *      int queue_array[10] = {0};
 *      queue_t queue;
 *      queue_init(&queue, queue_array, 10);
 * 
 *      int error = queue_enqueue(&queue, 1);
 *      int error = queue_dequeue(&queue, &retval);
 * @endcode
 *
 */
/*****************************************************************************/
int
queue_dequeue(queue_t* queue, int* value)
{
    int ret = -1;

    sem_wait(&(queue->lock));

    if (!is_empty(queue))
      {
          *value = queue->elements[queue->outdex];
          queue->outdex = (queue->outdex+1) % queue->size;
          queue->count--;
          ret = 0;
      }

    sem_post(&(queue->lock));

    return ret;
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to print the values of the queue.
 * 
 * @param queue Queue.
 * 
 * @return None.
 *
 */
/*****************************************************************************/
void 
queue_print(queue_t* queue)
{
    int ix = 0;
    int jx = queue->outdex;

    sem_wait(&(queue->lock));

    for (ix = 0; ix < queue->count; ix++)
      {
          printf("%d :: ", queue->elements[jx]);
          jx = (jx+1) % queue->size;
      }

    printf("\n");

    sem_post(&(queue->lock));
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to get the number of elements in the queue.
 * 
 * @param queue Queue to get the number of elements.
 * 
 * @return Number of elements.
 *
 */
/*****************************************************************************/
int
queue_count(queue_t* queue)
{
    int count = -1;

    sem_wait(&(queue->lock));

    count = queue->count;

    sem_post(&(queue->lock));

    return count;
}

/*****************************************************************************/
/*!
 * Close the Doxygen group.
 * @}
 */
/*****************************************************************************/
