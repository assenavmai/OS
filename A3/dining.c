#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>


pthread_t philosopher[1025];
pthread_mutex_t chopstick[1025];
int timesEaten[1025] = {0};
int chopStickTaken[3] = {0};
int numPhil;
int maxEat;
int eaten = 0;

void initializeChopsticks(int numChopsticks, pthread_mutex_t *chopsticks);
void createPhilosophers(int numPhil, int timesEat, pthread_mutex_t * chopsticks);

void * philosopherFunction(int i){
int j;



    while(eaten < maxEat)
    {

        printf("Philosopher %d wants to eat.\n", i + 1);

        /*Locking the left chopstick*/
        pthread_mutex_lock(&chopstick[i]);

        if(chopStickTaken[i] == 1)/*if the left chopstick is not taken*/
        {
            printf("Philosopher %d has their left chopstick %d \n",i+1, i);

            chopStickTaken[i] = 0;

            pthread_mutex_unlock(&chopstick[i]);
            pthread_mutex_lock(&chopstick[(i+1)%numPhil]);
            printf("%d %d\n", (i+1)%numPhil, chopStickTaken[1]);

            if(chopStickTaken[(i+1)%numPhil] == 1)
            {
                printf("Philosopher %d had their right chopstick.\n", i+1);
                
                chopStickTaken[(i+1)%numPhil] = 0;
                pthread_mutex_unlock(&chopstick[(i+1)%numPhil]);

                printf("Philosopher %d has 2 chopsticks and is now eating.\n", i+1);
                eaten++;
                
                sleep(1+rand()%30000000000);

                pthread_mutex_lock(&chopstick[(i+1)%numPhil]);
                pthread_mutex_lock(&chopstick[i]);

                chopStickTaken[i] = 1;
                chopStickTaken[(i+1)%numPhil] = 1;

                pthread_mutex_unlock(&chopstick[(i+1)%numPhil]);
                pthread_mutex_unlock(&chopstick[i]);

                sleep(1+rand()%30000000000);

            }
            else
            {
                printf("Philosopher %d cannot get right chopstick.\n", i+1);
                chopStickTaken[(i+1)%numPhil] = 0;

                pthread_mutex_unlock(&chopstick[(i+1)%numPhil]);
                pthread_mutex_lock(&chopstick[i]);

                chopStickTaken[i] = 1;

                pthread_mutex_unlock(&chopstick[i]);
                sleep(1+rand()%30000000000);

            }
        }
        else
        {
            printf("Philosopher %d cannot get left chopstick.\n", i+1);
            pthread_mutex_unlock(&chopstick[i]);
                sleep(1+rand()%8);

        }
        pthread_yield();

    }
   
    pthread_exit(0);
    return(NULL);
}

int main(int argc, char const *argv[]){

    int i;

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

    initializeChopsticks(numPhil, chopstick);

    createPhilosophers(numPhil, maxEat, chopstick);

   for(i=0;i<5;i++)
      pthread_mutex_destroy(&chopstick[i]);

   return 0;
   }

void initializeChopsticks(int numChopsticks, pthread_mutex_t *chopsticks)
{
    int i, error;

    for(i = 0; i < numChopsticks; i++)
    {
        error = pthread_mutex_init(&chopsticks[i], NULL);

        if(error)
        {
            printf("Could not initialize chopsticks.\n");
            exit(1);
        }
    }
}

void createPhilosophers(int numPhil, int timesEat, pthread_mutex_t * chopsticks){
    
    int i;

    for(i = 0; i < numPhil; i++)
    {
        pthread_create(&philosopher[i], NULL, (void *)philosopherFunction, (void*)i);
    }

    for(i = 0; i < numPhil; i++)
    {
        pthread_join(philosopher[i], NULL);
    }
}

int foodLeft(int numPhil, int timesEaten)
{
    int food;

    food = numPhil * timesEaten;

    return food;
}