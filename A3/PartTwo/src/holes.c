#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

/*in MBs*/
#define MEMSIZE 128

char processID[1024];
int processSize[1024];
int memory[129] = {0};

int readFile();
void firstFit();
void bestFit();

void insertIntoMemory();
void removeFromMemory();
void first();

int main(int argc, char const *argv[])
{
	

	/*print();*/
	first();
	return 0;
}

int readFile(){

	FILE * f;
	char id;
	int size;
	int i, lineAmount;
	char line[1024];

	lineAmount = 0;
	if((f = fopen("t1.txt", "r")) == NULL)
	{
		fprintf(stderr, "%s\n", "Could not open file.");
		exit(1);
	}

	while(fgets(line, sizeof(line), f) != NULL)
	{
		lineAmount++;
	}

	rewind(f);

	for (i = 0; i < lineAmount; ++i)
	{
		while(fscanf(f, "%c %d", &id, &size) == 2)
		{
			enqueue(id, size, 0, 0,0);
			/*printf("%c %d\n", processID[i], processSize[i]);*/
		}
	}

	return lineAmount;
}

void firstFit(){

	int memsize = 128;
	int loads = 0;
	int numProcesses = 0;
	int holes = 8;
	int count;
	
	count = readFile();

	while(!isEmpty())
	{

		if(memsize >= head->size)
		{
			memory_enqueue(head->id, head->size, head->swapped, head->start, head->end);
			memsize -= head->size;
			numProcesses++;
			loads++;
			holes--;

			printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d\n", head->id, numProcesses, holes);
			dequeue();
		}

		if(head != NULL)
		{
			if(head->size > memsize)
			{
				memory_head->swapped++;
				memsize += memory_head->size;
				holes++;
				if(memory_head->swapped != 3)
				{
					enqueue(memory_head->id, memory_head->size, memory_head->swapped, head->start, head->end);
					memory_dequeue();
				}
				else
				{
					memory_dequeue();
				}
				numProcesses--;
			/*	printf("%d\n", memsize);*/

			}
		}
		
	}
	
	printf("Total Loads = %d\n", loads);

	destroy();
	memory_destroy();
}


void bestFit(){

	/*Process * smallest;
	int count, i, space = 0, memsize = 128;
	int memory[128] = {0};

	count = readFile();

	smallest = traverse();*/

}

void first(){

	int i = 0, j,k, x,blockSize = 0, prev = -1;
	int numProcesses = 0, holes = 0;
	Boolean inserting = false;
	int memsize = 128;
	int count;
	
	count = readFile();

	
	while(!isEmpty())
	{
		inserting = false;

		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				blockSize++;
				memory[i] = 1;
				/*printf("         block %d %d\n", i, blockSize);*/
				/*printf("   i %d\n", i);*/
				/*printf("At spot %d it is %d\n", i, memory[i]);*/
				if(head != NULL)
				{
						/*printf("no null %d %d\n", head->size, blockSize);*/
					if(blockSize >= head->size)
					{	

						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
						}
						memsize -= head->size;
						/*printf("              %c start = %d end = %d\n", head->id, head->start, head->end);*/
						printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d\n", head->id, head->start, head->end);
						insertIntoMemory();
						prev = i;
						blockSize = 0;

						/*printf("          %d\n", memsize);


							for(k = 1; k < 129; k++)
							{
								printf("%d ", memory[k]);
							}
							printf("\n");
							inserting = true;*/

						break;
					}
				}
				
			}
							else
				{
					while(blockSize != 0)
					{
						memory[blockSize] = 0;
						blockSize--;
					}
				}

		}

		/*printf("bs %d\n", blockSize);*/

		if(head != NULL)
		{
			if(blockSize < head->size && inserting == false)
			{
				memsize += memory_head->size;

				/*printf("   No space for %c  %d %c %d\n", head->id, memsize, memory_head->id, memory_head->size);*/

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;
					}

					if(memory[j] == 1)
					{
						memory[j] = 0;
					}
				}
				blockSize = 0;
			
				removeFromMemory();

					/*for(k = 1; k < 129; k++)
					{
						printf("%d ", memory[k]);
					}
					printf("\n\n");*/

			}
		}
		
		
	}


}


void insertIntoMemory(){

	memory_enqueue(head->id, head->size, head->swapped, head->start, head->end);
	dequeue();
}

void removeFromMemory(){

	memory_head->swapped++;

	if(memory_head->swapped != 3)
	{
		enqueue(memory_head->id, memory_head->size, memory_head->swapped, head->start, head->end);
		memory_dequeue();
	}
	
	else
	{
		memory_dequeue();
	}
}

/*positive
sweet
gentleman*/