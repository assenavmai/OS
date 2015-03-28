#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

pthread_t philosopher[6];
pthread_mutex_t chopstick[6];
int timesEaten[50] = {0};
int numPhil;
int maxEat;

void initializeChopsticks(int numChopsticks, pthread_mutex_t *chopsticks);
void createPhilosophers(int numPhil, int timesEat, pthread_mutex_t * chopsticks);

void * philosopherFunction(int i){

    int food;
   printf ("Philosopher %d is thinking.\n",i + 1);

   pthread_mutex_lock(&chopstick[i]);
   pthread_mutex_lock(&chopstick[(i+1)%numPhil]);

   food = numPhil * maxEat;

   while(food != 0)
   {
        if(philosopher[i] == numPhil)
        {
            sleep(1 + rand() %8);
        }
        if(timesEaten[i] < maxEat)
       {
           printf ("Philosopher %d is eating\n",i);
           sleep(1 + rand()%8);

           pthread_mutex_unlock(&chopstick[i]);
           pthread_mutex_unlock(&chopstick[(i+1)%numPhil]);
           sleep(1 + rand()%8);

           printf ("Philosopher %d finished eating\n",i + 1);
           timesEaten[i] += 1;
           food--;
       }
       else
       {
            pthread_mutex_unlock(&chopstick[i]);
            pthread_mutex_unlock(&chopstick[(i+1)%numPhil]);
            break;
       }   
   }
   

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

    pthread_mutex_t chopstick[numPhil];
   
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