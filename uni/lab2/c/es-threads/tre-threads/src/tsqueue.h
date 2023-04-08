#ifndef THREAD_SAFE_QUEUE
#define THREAD_SAFE_QUEUE

#define _GNU_SOURCE
#include <pthread.h>
#include <stdlib.h>
#include <stdbool.h>

#define ERR_RET(cond, retval) 				\
if ((cond)) return retval;

#define ERR_TEXIT(cond, msg) 				\
if ((cond)) {								\
	fprintf(stderr, msg);					\
	pthread_exit(EXIT_FAILURE);				\
}

/* Like pthread_mutex_lock but exit the thread when get an error */
inline void mtx_lock(pthread_mutex_t *mutex) {
	ERR_TEXIT(pthread_mutex_lock(mutex) != 0, "Error pthread_mutex_lock\n");
}

/* Like pthread_mutex_unlock but exit the thread when get an error */
inline void mtx_unlock(pthread_mutex_t *mutex) {
	ERR_TEXIT(pthread_mutex_unlock(mutex) != 0, "Error pthread_mutex_unlock\n");
}

/* Like pthread_mutex_init(mutex, NULL) but exit the thread when get an error */
inline void mtx_init(pthread_mutex_t *mutex) {
	ERR_TEXIT(pthread_mutex_init(mutex, NULL) != 0, "Error pthread_mutex_init\n");
}

/* Like pthread_mutex_destroy(mutex) but exit the thread when get an error */
inline void mtx_destroy(pthread_mutex_t *mutex) {
	ERR_TEXIT(pthread_mutex_destroy(mutex) != 0, "Error pthread_mutex_destroy\n");
}

/* Like pthread_cond_init(cond, NULL) but exit the thread when get an error */
inline void cond_init(pthread_cond_t *cond) {
	ERR_TEXIT(pthread_cond_init(cond, NULL), "Error pthread_cond_init\n");
}

/* Like pthread_cond_destroy(cond) but exit the thread when get an error */
inline void cond_destroy(pthread_cond_t *cond) {
	ERR_TEXIT(pthread_cond_destroy(cond), "Error pthread_cond_destroy\n");
}

/* Like pthread_cond_signal(cond) but exit the thread when get an error */
inline void cond_signal(pthread_cond_t *cond) {
	ERR_TEXIT(pthread_cond_signal(cond), "Error pthread_cond_signal\n");
}

/* Like pthread_cond_wait(cond, mtx) but exit the thread when get an error */
inline void cond_wait(pthread_cond_t *cond, pthread_mutex_t *mtx) {
	ERR_TEXIT(pthread_cond_wait(cond, mtx), "Error pthread_cond_wait\n");
}

/* Like pthread_cond_broadcast(cond) but exit the thread when get an error */
inline void cond_broadcast(pthread_cond_t *cond) {
	ERR_TEXIT(pthread_cond_broadcast(cond), "Error pthread_cond_broadcast\n");
}

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
bool qpush(queue_t *queue, void *data);

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
void *qpop(queue_t *queue);

#endif
