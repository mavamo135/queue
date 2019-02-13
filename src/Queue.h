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
#include <pthread.h>
#include <semaphore.h>

/******************************************************************************
* Preprocessor Constants
******************************************************************************/


/******************************************************************************
* Configuration Constants
******************************************************************************/
/*!
 * Maximum number of elements in the queue array
 */
#define MAXSIZE     10

/******************************************************************************
* Macros
******************************************************************************/


/******************************************************************************
* Typedefs
******************************************************************************/
/*! @brief Queue typedef */
typedef struct queue_t queue_t;

/*! @brief Queue structure */
struct queue_t
{
    int index;              /**< Index used for input elements */
    int outdex;             /**< Index used for output elements */
    int count;              /**< Number of elements in the queue */
    int elements[MAXSIZE];  /**< Queue array */
    sem_t lock;             /**< Semaphore used to lock the queue */
};

/******************************************************************************
* Variables
******************************************************************************/


/******************************************************************************
* Function Prototypes
******************************************************************************/
void queue_init(queue_t* queue);
int queue_enqueue(queue_t* queue, int value);
int queue_dequeue(queue_t* queue, int* value);
void queue_print(queue_t* queue);
int queue_count(queue_t* queue);

#endif /* QUEUE_H */