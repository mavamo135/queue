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
 * 
 *      uint8_t error, i;
 *      uint16_t ret;
 *      const uint16_t data[3] = {0, 1, 2};
 *      queue_array_t queue_array[QUEUESIZE] = {0};
 *      queue_t queue;
 *
 *      queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
 *
 *      for (i = 0; i < 3; i++)
 *      {
 *          error = queue_enqueue(&queue, (void *) &data[i]);
 *      }
 *
 *      for (i = 0; i < 3; i++)
 *      {
 *          error = queue_dequeue(&queue, (void *) &ret));
 *          printf("Value %d: %d", i, ret);
 *      }
 *  @endcode
 */
/******************************************************************************
* Includes
******************************************************************************/
#include "Queue.h"          /* Queue and queue array typedefs */

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
    if (queue->numElements == 0)
    {
        return 1;  
    }

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
    if((queue->numElements * queue->dataSize) == queue->queueSize)
    {
        return 1;  
    }

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
 * @param queueArray Pointer to the array used to store the data.
 * @param queueSize Size of the queue array.
 * @param dataSize Size of every data element.
 * 
 * @return None.
 * 
 * \b Example:
 * @code
 *      #define QUEUESIZE   sizeof(uint16_t) * 10
 *
 *      queue_t queue;
 *      queue_array_t queue_array[QUEUESIZE] = {0};
 *
 *      queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
 * @endcode
 *
 */
/*****************************************************************************/
void
queue_init(queue_t* queue,
           queue_array_t* queueArray,
           uint16_t queueSize,
           uint8_t dataSize)
{
    // Initialize the structure
    queue->index = 0;
    queue->outdex = 0;
    queue->numElements = 0;
    queue->queueArray = queueArray;
    queue->queueSize = queueSize;
    queue->dataSize = dataSize;
    
    // Initialize R/W semaphore
    pthread_mutex_init(&(queue->lock), NULL);
}

/*****************************************************************************/
/*!
 * 
 * \b Description:
 * 
 * This function is used to put a element in the queue.
 * 
 * @param queue Queue.
 * @param value Pointer to variable whose value is going to be inserted to the 
 *              queue.
 * 
 * @return -1 if the queue is full (overflow), 0 otherwise.
 * 
 * \b Example:
 * @code
 *      #define QUEUESIZE   sizeof(uint16_t) * 10
 * 
 *      uint8_t error;
 *      uint16_t data;
 *      queue_t queue;
 *      queue_array_t queue_array[QUEUESIZE] = {0};
 *
 *      queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
 * 
 *      data = 1;
 *      int error = queue_enqueue(&queue, (void *) &data);
 * @endcode
 *
 */
/*****************************************************************************/
uint8_t
queue_enqueue(queue_t* queue, const void* value)
{
    uint8_t ret = 1;
    
    pthread_mutex_lock(&(queue->lock));

    if (!is_full(queue))
    {
        for (uint8_t j = 0; j < queue->dataSize; j++)
        {
            uint8_t offset = queue->index + j;
            *((uint8_t *) (queue->queueArray + offset)) = *((uint8_t *) (value + j));
        }
        queue->index = (queue->index + queue->dataSize) % queue->queueSize;
        queue->numElements++;
        ret = 0;
    }

    pthread_mutex_unlock(&(queue->lock));

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
 * @param value Pointer to variable to which the dequeued data will be copied.
 * 
 * @return -1 if the queue is empty (underflow), 0 otherwise.
 * 
 * \b Example:
 * @code
 *      #define QUEUESIZE   sizeof(uint16_t) * 10
 *
 *      uint8_t error;
 *      uint16_t data, retval;
 *      queue_t queue;
 *      queue_array_t queue_array[QUEUESIZE] = {0};
 *
 *      queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
 * 
 *      data = 1;
 *      int error = queue_enqueue(&queue, (void *) &data);
 *      int error = queue_dequeue(&queue, (void *) &retval);
 * @endcode
 *
 */
/*****************************************************************************/
uint8_t
queue_dequeue(queue_t* queue, void* value)
{
    int ret = 1;

    pthread_mutex_lock(&(queue->lock));

    if (!is_empty(queue))
    {
        for (uint8_t j = 0; j < queue->dataSize; j++)
        {
            uint8_t offset = queue->outdex + j;
            *((uint8_t *) (value + j)) = *((uint8_t *) (queue->queueArray + offset));
        }
        queue->outdex = (queue->outdex + queue->dataSize) % queue->queueSize;
        queue->numElements--;
        ret = 0;
    }

    pthread_mutex_unlock(&(queue->lock));

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
 * @param printFn Pointer to the function used to print the elements.
 * @param data Pointer to a variable with the correct size that will store every
 *             element of the queue and is passed to printFn.
 * 
 * @return None.
 *
 * \b Example:
 * @code
 *      #define QUEUESIZE   sizeof(uint16_t) * 3
 *      
 *      void 
 *      printUint16(const void *data)
 *      {
 *          printf("%d :: ", *((const uint16_t *) data));
 *      }
 * 
 *      int
 *      main(int argc, char** argv)
 *      {
 *          uint8_t error, i;
 *          uint16_t print_data;
 *          const uint16_t data[3] = {0, 1, 2};
 *          queue_t queue;
 *          queue_array_t queue_array[QUEUESIZE] = {0};
 *
 *          queue_init(&queue, queue_array, QUEUESIZE, sizeof(uint16_t));
 * 
 *          for (i = 0; i < 3; i++)
 *          {
 *              int error = queue_enqueue(&queue, (void *) &data[i]);
 *          }
 * 
 *          queue_print(queue, printUint16, (void *) &print_data);
 *      }
 * @endcode
 * 
 */
/*****************************************************************************/
void 
queue_print(queue_t* queue, void (*printFn)(const void* data), void* data)
{
    uint16_t i = 0;
    uint16_t k = 0;

    pthread_mutex_lock(&(queue->lock));

    uint16_t j = queue->outdex;

    for (i = 0; i < queue->numElements; i++)
    {
        for (k = 0; k < queue->dataSize; k++)
        {
            uint8_t offset = j + k;
            *((uint8_t *) (data + k)) = *((uint8_t *) (queue->queueArray + offset));
        }
        printFn(data);
        j = (j + queue->dataSize) % queue->queueSize;
    }

    pthread_mutex_unlock(&(queue->lock));
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
uint16_t
queue_count(queue_t* queue)
{
    int count = -1;

    pthread_mutex_lock(&(queue->lock));

    count = queue->numElements;

    pthread_mutex_unlock(&(queue->lock));

    return count;
}

/*****************************************************************************/
/*!
 * Close the Doxygen group.
 * @}
 */
/*****************************************************************************/
