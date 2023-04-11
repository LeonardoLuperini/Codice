#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>
#include "pthread_utils.h"

#define ERR_RET(cond, retval) 				\
if ((cond)) return retval;

typedef struct node_t {
    void *data;
    struct node_t *next;
} node_t;

typedef struct {
    node_t *head;
	node_t *tail;
    pthread_mutex_t mtx;
	pthread_cond_t cond;
} queue_t;

/* Initilize a node.
 *
 * Params:
 * pointer to data.
 *
 * Returns: 
 * NULL if there was an error and errno is set 
 * else return a pointer to the queue.
 *
 */
node_t* node_init(void *data);

/* Initilize a queue.
 *
 * Returns: 
 * NULL if there was an error 
 * else return a pointer to the queue.
 *
 */
queue_t* queue_init();

/* Insert data at the end of the queue.
 * 
 * Params:
 * Pointer to a queue that you want to update.
 * Pointer to data the you want to insert.
 *
 * Returns:
 * true if succeeded else false
 *
 */
bool queue_push(queue_t *queue, void *data);

/* Extract data from the head of the queue,
 * if the queue is empty wait.
 * 
 * Params:
 * Pointer to a queue that you want to update.
 *
 * Returns:
 * data of the fist node.
 *
 */
void *queue_pop(queue_t *queue);

/* Destroy a queue
 * 
 * Params:
 * Pointer to a queue that you want to destroy.
 * That pointer now point to an empty queue.
 *
 */
void queue_destroy(queue_t *queue);


#endif
