#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int numPhil;
int maxEat;

/*struct for the philosophers*/
typedef struct Philosopher_t {
    pthread_mutex_t *chopsticksL, *chopstickR;
    pthread_t thread;
    int fail;
    int position;
    int timesEaten;
} Philosopher;


void *philosophers(void *p) {
    Philosopher *phil = (Philosopher*)p;
    int error;
    int tries_left;
    int food = 6;

    while (food != 0) {

        printf ("Philosopher %d is thinking.\n", phil->position);
        sleep(1+rand()%8);

        if(phil->position%2 == 1) /*if an even number, wait*/
        {
            sleep(40);
        }
        if(phil->position == 0)
        {
            sleep(65);
        }

        if(phil->timesEaten < 2)
        {
           printf ("Philosopher %d is eating\n",phil->position);

           error = pthread_mutex_lock(phil->chopsticksL);

           pthread_mutex_lock(phil->chopstickR);
           sleep(1 + rand()%8);

           pthread_mutex_unlock(phil->chopsticksL);
           pthread_mutex_unlock(phil->chopstickR);
           sleep(1 + rand()%8);

           printf ("Philosopher %d finished eating\n",phil->position);
           phil->timesEaten++;
           food--;
       }
       else
       {
            break;
       }

    }
    return NULL;
}


int main(int argc, char const *argv[])
{
    pthread_mutex_t chopsticks[3];
    Philosopher *phil;
    int i;
    int failed;

    if(argc < 3)
    {
        printf("Insufficient amount of arguments.\n");
        exit(1);
    }
    else
    {
        numPhil = atoi(argv[1]);
        maxEat = atoi(argv[2]);
    }

   /* initializeChopsticks(3, chopsticks);*/

    for (i = 0; i < numPhil; i++) {
        failed = pthread_mutex_init(&chopsticks[i], NULL);
        if (failed) {
            printf("Failed to initialize mutexes.");
            exit(1);
        }
    }

    for (i = 0;i < numPhil; i++) {
        phil = malloc(sizeof(Philosopher));
        phil->chopsticksL = &chopsticks[i];
        phil->chopstickR = &chopsticks[(i+1)%numPhil];
        phil->position = i;
        phil->timesEaten = 0;
        phil->fail = pthread_create( &phil->thread, NULL, philosophers, phil);
    }

    for(i = 0; i < numPhil; i++)
    {
        pthread_join(phil->thread, NULL);
    }

    
    return 0;
}