#include <stdio.h>
#include <semaphore.h>
#include <pthread.h>
#include <stdlib.h>


#define THINKING 0
#define HUNGRY 1
#define EATING 2
 
 
sem_t me; /*mutual exclusion*/
sem_t S[1025];/*semaphore at 0 intially*/
int numPhil; /*number of philosophers*/
int maxEat; /*max times to eat*/
int timesEaten[1025]; /*times eatedn*/
int pflag[1025];
 
void * philospher(void *num);
void pickup(int pos);
void putdown(int pos);
void test(int);/*check if surround forks are taken*/
 
 
int main(int argc, char const *argv[]){
    int i;
    pthread_t threads[1025];
    int phil[1025];

    if(argc < 3)/*get command line arguements*/
    {
        printf("Insufficient amount of arguments.\n");
        exit(1);
    }
    else
    {
        numPhil = atoi(argv[1]);
        maxEat = atoi(argv[2]);
    }

    for(i = 0; i < numPhil; i++)/*intialize philosoher number arrays*/
    {
        phil[i] = i;
    }


    sem_init(&me,0,1);/*initialize mutex*/
 
    for(i = 0; i < numPhil; i++)
    {
        sem_init(&S[i],0,0);/*initialize semaphore to 0*/
    }
    for(i = 0; i < numPhil; i++)/*create the threads of philosophers*/
    {
        pthread_create(&threads[i],NULL,philospher,&phil[i]);
        printf("Philosopher %d is thinking\n",i+1);
    }
    for(i = 0; i < numPhil; i++)
    {
        pthread_join(threads[i],NULL);
    }

    return 0;
}
 
 
void * philospher(void* num){

    int food = numPhil * maxEat;/*amount of food on the table*/
    
    while(food > 0)
    {
        int *i = num;/*get the address of the philosophers number*/

        if(*i == 0)/*if it is the first positon, let them not be there for a while*/
        {
            sleep(20);
        }
        if(timesEaten[*i] < maxEat)
        {
            sleep(1);
            pickup(*i); /*get chopstick*/
            sleep(0);
            putdown(*i);/*putdown chopstick*/
            food--;
            timesEaten[*i] += 1; /*keeps track of how many time each philosopher eats*/
        }
        else
        {
            break;
        }
    }

    return NULL;
}

 
 /*pick up adjacent forks*/
void pickup(int pos)
{
    sem_wait(&me);  /*critical section*/
    pflag[pos] = HUNGRY;
    
    printf("Philosopher %d is thinking.\n",pos+1);
    test(pos);
    sem_post(&me);/*end critical section*/
    sem_wait(&S[pos]);/*eat if possible*/
    sleep(2);
}
 
 /*check if adjacent forks are being used*/
void test(int pos)
{
    int left = 0, right = 0, diff = 0;

    diff = numPhil - 1;

    left = (pos + diff)%numPhil;
    right = (pos + 1)%numPhil;


    if (pflag[pos] == HUNGRY && pflag[left] != EATING && pflag[right] != EATING)/*check if the chopstick is being used*/
    {
        pflag[pos] = EATING;
        sleep(2);
        printf("Philosopher %d is eating.\n",pos+1);
        sem_post(&S[pos]);/*allow the philosopher to eat*/
    }
}
 
 /*put forks down*/
void putdown(int pos)
{
    int left, right,diff;

    diff = numPhil - 1;

    left = (1 + diff)%numPhil;
    right = (pos + 1)%numPhil;

    sem_wait(&me);/*critical section*/
    pflag[pos] = THINKING;
    sleep(2);
    printf("Philosopher %d is thinking.\n",pos+1);
    test(left); /*let the philosopher to the left eat if possible*/
    test(right);/*let the philospoher to the right eat if possible*/
    sem_post(&me);/*end critical section*/
}