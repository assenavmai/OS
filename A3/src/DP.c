#include <stdio.h>
#include <stdlib.h>
#include <semaphore.h>
#include <pthread.h>
#include <unistd.h>
#include <stdarg.h>
#include <time.h>

/*floor(num phil / 2)*/
typedef struct info{
	int position;
	pthread_mutex_t *lChopstick;
	pthread_mutex_t *rChopstick;
	pthread_t thread;
	int max;
	int failure;
	int timesEaten;
}Philosopher;

void grab(Philosopher p, int n);
void putdown(Philosopher p, int n, int m);

void * philF(void * data){

	Philosopher * p;

	p = (Philosopher*)data;

	while(1)
	{
		printf("Philosopher %d is thinking.\n", p[1].position);
	}

	return NULL;
}

void * philosopher(int numPhilo, int freq, Philosopher p){

	int position;
	int fail;
	pthread_mutex_t *left , *right, *temp;
	while(1)
	{
		position = (int)numPhilo;
		printf("Philosopher %d is thinking.\n", position);
		sleep(1 + rand()%8);

		if(p.timesEaten == freq)
		{
			break;
		}
		else
		{
			printf("Philosopher %d is eating.\n", numPhilo);
			p.timesEaten++;
			sleep(1 + rand()%8);

		}
	}

	return NULL;
}

void think(){
	
}

int main(int argc, char const *argv[])
{
	int i, err;
	Philosopher * p;
	Philosopher phil[5];
	pthread_mutex_t * chopsticks;
	
	/*p = malloc(sizeof(Philosopher) * 1000);*/
	chopsticks = malloc(sizeof(Philosopher) * 1000);

	for(i = 1; i <= 5; i++)
	{
		err = pthread_mutex_init(&chopsticks[i], NULL);

		if(err)
		{
			printf("Error init\n");
			exit(1);
		}
	}
	for(i = 1; i <= 5; i++)
	{
		p = &phil[i];
		p->position = i;
		p->lChopstick = &chopsticks[i];
		p->rChopstick = &chopsticks[(i+1)%5];
		p->max = 2;
		pthread_create(&p->thread, NULL, philF, p);
		/*philosopher(i, 1, p[i]);*/
	}

	return 0;
}
