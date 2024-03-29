#include "pthread_utils.h"

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
    ERR_TEXIT(pthread_mutex_init(mutex, NULL) != 0,
              "Error pthread_mutex_init\n");
}

/* Like pthread_mutex_destroy(mutex) but exit the thread when get an error */
inline void mtx_destroy(pthread_mutex_t *mutex) {
    ERR_TEXIT(pthread_mutex_destroy(mutex) != 0,
              "Error pthread_mutex_destroy\n");
}

/* Like pthread_cond_init(cond, NULL) but exit the thread when get an error */
inline void cond_init(pthread_cond_t *cond) {
    ERR_TEXIT(pthread_cond_init(cond, NULL) != 0, "Error pthread_cond_init\n");
}

/* Like pthread_cond_destroy(cond) but exit the thread when get an error */
inline void cond_destroy(pthread_cond_t *cond) {
    ERR_TEXIT(pthread_cond_destroy(cond) != 0, "Error pthread_cond_destroy\n");
}

/* Like pthread_cond_signal(cond) but exit the thread when get an error */
inline void cond_signal(pthread_cond_t *cond) {
    ERR_TEXIT(pthread_cond_signal(cond) != 0, "Error pthread_cond_signal\n");
}

/* Like pthread_cond_wait(cond, mtx) but exit the thread when get an error */
inline void cond_wait(pthread_cond_t *cond, pthread_mutex_t *mtx) {
    ERR_TEXIT(pthread_cond_wait(cond, mtx) != 0, "Error pthread_cond_wait\n");
}

/* Like pthread_cond_broadcast(cond) but exit the thread when get an error */
inline void cond_broadcast(pthread_cond_t *cond) {
    ERR_TEXIT(pthread_cond_broadcast(cond) != 0,
              "Error pthread_cond_broadcast\n");
}
