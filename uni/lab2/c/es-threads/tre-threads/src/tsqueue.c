#include "tsqueue.h"

queue_t *queue_init() {
    queue_t *q = malloc(sizeof(queue_t));
    ERR_RET(q == NULL, NULL);
    q->head = NULL;
    q->tail = NULL;
    if (mtx_init(&q->mtx, NULL) != 0)
        return NULL;
    if (cond_init(&q->cond, NULL) != 0) {
        mtx_destroy(&q->mtx);
        return NULL;
    }

    return q;
}

bool qpush(queue_t *queue, void *data) {
    node_t *newnode = node_init(data);
    if (newnode != NULL) {
        mtx_lock(&queue->mtx);
        if (queue->head == NULL)
            queue->head = newnode;
        if (queue->tail != NULL)
            queue->tail->next = newnode;
        queue->tail = newnode;
    	cond_signal(&queue->cond);
        mtx_unlock(&queue->mtx);
        return true;
    }
    return false;
}

void *qpop(queue_t *queue) {
    void *data;
    mtx_lock(&queue->mtx);
    while (queue->tail == NULL)
        cond_wait(&queue->cond, &queue->mtx);
    data = queue->head->data;
    if (queue->tail == queue->head)
        queue->tail = NULL;
    queue->head = queue->head->next;
    mtx_unlock(&queue->mtx);
    return data;
}

node_t *node_init(void *data) {
    node_t *newnode = malloc(sizeof(node_t));
    if (newnode != NULL) {
        newnode->data = data;
        newnode->next = NULL;
    }
    return newnode;
}
