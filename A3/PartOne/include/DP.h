#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

typedef struct philData {
    pthread_mutex_t *fork_lft, *fork_rgt;
    int pos;
    pthread_t thread;
    int fail;
} Philosopher;

void * philosopher(void * num);