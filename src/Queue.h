/******************************************************************************
* Title                 :   Queue header file  
* Filename              :   Queue.h
* Author                :   Maximiliano Valencia
* Origin Date           :   13/02/2019
* Version               :   1.0.0
* Compiler              :   gcc
* Target                :   STM32
* Notes                 :   None
******************************************************************************/
/** @file Queue.h
 *  @brief Defines the function prototypes and structures of the linked list.
 * 
 *  This is the header file for the definition of the queue structure and 
 *  typedef as well as the function prototypes of the methods of the queue.
 */
#ifndef QUEUE_H
#define QUEUE_H

/******************************************************************************
* Includes
******************************************************************************/
#include <stdio.h>
#include <stdint.h>
#include <pthread.h>

/******************************************************************************
* Preprocessor Constants
******************************************************************************/


/******************************************************************************
* Configuration Constants
******************************************************************************/


/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Typedefs
******************************************************************************/
/*! @brief Queue array typedef */
typedef uint8_t queue_array_t;

/*! @brief Queue typedef */
typedef struct queue_t queue_t;

/*! @brief Queue structure */
struct queue_t
{
    uint16_t index;             /**< Index used for input elements */
    uint16_t outdex;            /**< Index used for output elements */
    uint16_t numElements;       /**< Number of elements in the queue */
    queue_array_t* queueArray;  /**< Queue array pointer to user array */
    uint16_t queueSize;         /**< Size of queue array */
    uint8_t dataSize;           /**< Size of every data element */
    pthread_mutex_t lock;       /**< Mutex used to lock the queue */
};

/******************************************************************************
* Variables
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/
void queue_init(queue_t* queue,
                queue_array_t* queueArray, 
                uint16_t queueSize, 
                uint8_t dataSize);
uint8_t queue_enqueue(queue_t* queue, const void* value);
uint8_t queue_dequeue(queue_t* queue, void* value);
void queue_print(queue_t* queue, void (*printFn)(const void* data), void* data);
uint16_t queue_count(queue_t* queue);

#endif /* QUEUE_H */
