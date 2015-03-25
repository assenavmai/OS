#include "DP.h"

void * philosopher(void * num){

    Philosopher * p = (Philosopher*)num;
    while(1)
    {
        printf("Philosopher %d is thinking.\n", p->pos);
    }
}

