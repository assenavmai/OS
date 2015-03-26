#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

/*in MBs*/
#define MEMSIZE 128

char processID[1024];
int processSize[1024];
int memory[129] = {0};

void readFile();
void firstFit();
void bestFit();
void bestTest();
void insertIntoMemory();
void removeFromMemory();


int main(int argc, char const *argv[])
{
	

	/*print();*/
	/*firstFit();*/
	bestTest();
	return 0;
}

void readFile(){

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

}

void bestTest()
{
	int i,j;
	int bestStart = 1;
	int blockSize = 0;
	int currStart = 0;
	int smallestSize = 128;


	readFile();

	while(!isEmpty())
	{
		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				if(blockSize == 0)
				{
					currStart = i;
					printf("                                       curr %d\n", currStart);
				}
				blockSize++;
			}
			else
			{
				if(blockSize > 0)
				{
					if(blockSize < smallestSize && blockSize >= head->size)
					{
						printf("     in for else\n");
						bestStart = currStart;
						smallestSize = blockSize;
					}
				}
			}
		}

		if(blockSize < smallestSize && blockSize >= head->size)
		{
			printf("         outside\n");
			bestStart = currStart;
			smallestSize = blockSize;
		}

		printf("Best Time = %d Smallest = %d\n", bestStart, smallestSize);
		if(head != NULL)
		{
			if(blockSize < head->size)
			{
				printf("remove\n");

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;

					}
				}
				removeFromMemory();


				for(j = 1; j < 129; j++)
				{
					printf("%d ", memory[j]);
				}
				printf("\n");

			}
			else
			{
				printf("insert\n");
				for(j = bestStart; j < bestStart + head->size; j++)
				{
					memory[j] = head->id;
				}
				insertIntoMemory();


				for(j = 1; j < 129; j++)
				{
					printf("%d ", memory[j]);
				}
				printf("\n");
			}

		}

		blockSize = 0;
	}

	
	

	for(j = 1; j < 129; j++)
	{
		printf("%d ", memory[j]);
	}
	printf("\n");
}
void bestFit(){

	int i = 0, j, blockSize = 0, loads = 0;
	int bestStart = 1;
	int currStart = 0;
	int smallestSize = 128;
	int numProcesses = 0, holes = 0;
	Boolean smallestFound = false;
	int memsize = 128;
	
	readFile();

	while(!isEmpty())
	{
		smallestFound = false;
		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
					/*memory[i] =1;*/
				if(blockSize == 0)
				{
					currStart = i;
				}
				blockSize++;
			}
			else 
			{	
				/*printf("     %d\n", blockSize);*/
				if(blockSize > 0)
				{
					printf("jdjd %d < %d && %d >= %d \n", blockSize, smallestSize, blockSize, head->size);
					if(blockSize < smallestSize && blockSize >= head->size)
					{						
						bestStart = currStart;
						smallestSize = blockSize;
						smallestFound = true;
					}

					blockSize = 0;
				}
				
			}
		}
		printf("last %d < %d && %d >= %d \n", blockSize, smallestSize, blockSize, head->size);
		if(blockSize < smallestSize && blockSize >= head->size)
		{
			printf("    last block check\n");
			bestStart = currStart;
			smallestSize = blockSize;
			blockSize = 0;
			smallestFound = true;
		}

		printf("Best Start = %d BlockSize = %d Smallest = %d Head -> %d\n", bestStart, blockSize, smallestSize, head->size);

		print();

		if(head != NULL)
		{
			if(blockSize < head->size && !smallestFound)
			{
				printf("removing\n");
				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;
					}
				}

				for(j = 1; j < 129; j++)
				{
					printf("%d ", memory[j]);
				}
					printf("\n");

				memsize += head->size;
				removeFromMemory();
				
			}
			else
			{
				printf("inseting %d %d\n",bestStart, head->size);

				for(j = 1; j < head->size + 1 ; j++)
				{
					memory[j] = head->id;
				}

				memsize -= head->size;
				insertIntoMemory();

				for(j = 1; j < 129; j++)
				{
					printf("%d ", memory[j]);
				}
					printf("\n");
			}
		}


	}
		
		

		/*for(i = 1; i < 129; i++)
		{
			printf("%d ", memory[i]);
		}
		printf("\n");*/

}

void firstFit(){

	int i = 0, j, blockSize = 0, loads = 0;
	int numProcesses = 0, holes = 0;
	Boolean inserting = false;
	int memsize = 128;
	
	readFile();

	
	while(!isEmpty())
	{
		inserting = false;

		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				blockSize++;
				memory[i] = 1;

				if(head != NULL)
				{
					if(blockSize >= head->size)
					{	

						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
						}

						numProcesses++;
						loads++;
						memsize -= head->size;
						/*printf("              %c start = %d end = %d\n", head->id, head->start, head->end);*/
						printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d\n", head->id, numProcesses, holes);
						insertIntoMemory();
						inserting = true;
						blockSize = 0;

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

		if(head != NULL)
		{
			if(blockSize < head->size && inserting == false)
			{
				memsize += memory_head->size;

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

				numProcesses--;
				blockSize = 0;
							
						
				removeFromMemory();
			}
		}
	}

	printf("Total Loads = %d\n", loads);

	memory_destroy();
	destroy();
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