#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Queue.h"

/*in MBs*/
#define MEMSIZE 128

char processID[1024];
int processSize[1024];
int memory[129] = {0}; /*size is 129 because I count from 1 instead of 0*/
float cumulativeMemory[256] = {0.0};

void readFile();
void firstFit();
void bestFit();
void worstFit();
void nextFit();
void nextTest();
/*void bestTest();*/
void insertIntoMemory();
void removeFromMemory();
int countHoles();
float getCumulative(int currLoads);
float calculateMemUsage(int memsize);
void clearMemory();


int main(int argc, char const *argv[])
{

	/*if(argc < 2)
	{
		printf("error\n");
		exit(1);
	}
	else
	{
		printf("ysysy\n");
		printf("%s\n", argv[1]);
	}*/

	/*printf("-------------------------------------FIRST FIT---------------------------------\n");
	firstFit();

	printf("-------------------------------------BEST FIT-----------------------------------\n");
	bestFit();

	printf("-------------------------------------WORST FIT-----------------------------------\n");
	worstFit();*/

	printf("-------------------------------------NEXT FIT------------------------------------\n");
	nextTest();
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



void firstFit(){

	int i, j, k, blockSize, loads, numProcesses, holes, memsize, ttlProcesses, ttlHoles;
	float memusage, percentCumulative;
	Boolean inserting;
	
	blockSize = 0;
	loads = 0;
	numProcesses = 0;
	holes = 0;
	inserting = false;
	memsize = 128;
	memusage = 0;
	k = 0;
	percentCumulative = 0.0;
	ttlProcesses = 0;
	ttlHoles = 0;
	readFile();

	
	while(!isEmpty())
	{
		inserting = false;
		holes = 0;

		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				blockSize++;
				memory[i] = 1;/*this marks the array as visited*/

				if(head != NULL)
				{
					if(blockSize >= head->size)
					{	

						/*adds the pid to the array to indicate where the process takes up memory*/
						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
						}
						printf("                            inserting\n");
						for(j = 1; j < 129; j++)
						{
							printf("%d ", memory[j]);
						}
						printf("\n");

						numProcesses++;
						ttlProcesses += numProcesses;
						loads++;
						memsize -= head->size;

						holes = countHoles();
						ttlHoles += holes;

						memusage = calculateMemUsage(memsize);
						cumulativeMemory[k] = memusage; /*adds the %memusage so that the cumulative can be calculated each time*/
						k++;
						percentCumulative = getCumulative(loads);

						printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d Memory Usage: %.2f%% Cumulative Memory %.2f%%\n", head->id, numProcesses, holes, memusage, percentCumulative);
						
						insertIntoMemory();
						inserting = true;
						blockSize = 0;

						break;
					}
				}	
			}
			else
			{
				for(j = 1; j < 129; j++)
				{
					if(memory[j] == 1)
					{
						memory[j] = 0;
					}
				}
				blockSize = 0;
			}
		}

		if(head != NULL)
		{
			if(blockSize < head->size && inserting == false)
			{
				/*printf("                                      removing %c no space for %c\n", memory_head->id, head->id);*/
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

	percentCumulative = getCumulative(loads);

	printf("\nTotal Loads = %d Average # of Processes = %.2f Average Holes = %.2f Cumulative memory = %.2f%%\n", loads, ((float)ttlProcesses/loads), ((float)ttlHoles/loads), percentCumulative);

	/*for(j = 0; j < 256; j++)
	{
		printf("%f ", cumulativeMemory[j]);
	}
	printf("\n");*/

	memory_destroy();
	destroy();
	clearMemory();
}

void bestFit(){

	int i, j, k, holes, bestStart, blockSize, currStart, smallestSize, numProcesses, ttlProcesses, loads, memsize, ttlHoles;
	float memusage, percentCumulative;
	Boolean found;

	numProcesses = 0;
	ttlProcesses = 0;
	loads = 0;
	memsize = 128;
	ttlHoles = 0;
	memusage = 0.0;
	percentCumulative = 0.0;
	k = 0;

	readFile();

	while(!isEmpty())
	{
		blockSize = 0;
		bestStart = 1;
		currStart =0;
		smallestSize = 128;
		found = false;

		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				if(blockSize == 0)
				{
					currStart = i;
				}

				blockSize++;
			}
			else
			{
				if(blockSize > 0)
				{
					if(blockSize < smallestSize && blockSize >= head->size)
					{
						bestStart = currStart;
						smallestSize = blockSize;
						found = true;
					}
					blockSize = 0;

				}
			}
		}

		if(blockSize < smallestSize && blockSize >= head->size)
		{
			bestStart = currStart;
			smallestSize = blockSize;
			found = true;
		}

		if(head != NULL)
		{
			if(blockSize < head->size && !found)
			{

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;

					}
				}

				memsize += memory_head->size;

				removeFromMemory();

				bestStart = 1;
			}
			else
			{
				for(j = bestStart; j < bestStart + head->size; j++)
				{
					memory[j] = head->id;
				}

				numProcesses++;
				ttlProcesses += numProcesses;
				loads++;
				memsize -= head->size;

				holes = countHoles();
				ttlHoles += holes;

				memusage = calculateMemUsage(memsize);
				cumulativeMemory[k] = memusage; /*adds the %memusage so that the cumulative can be calculated each time*/
				k++;
				percentCumulative = getCumulative(loads);

				printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d Memory Usage: %.2f%% Cumulative Memory %.2f%%\n", head->id, numProcesses, holes, memusage, percentCumulative);
				
				insertIntoMemory();
			}

		}

	}

	percentCumulative = getCumulative(loads);

	printf("\nTotal Loads = %d Average # of Processes = %.2f Average Holes = %.2f Cumulative memory = %.2f%%\n", loads, ((float)ttlProcesses/loads), ((float)ttlHoles/loads), percentCumulative);

	memory_destroy();
	destroy();
	clearMemory();

}

void worstFit(){

	int i, j, k, bestStart, blockSize, currStart, biggestSize, numProcesses, ttlProcesses, ttlHoles, loads, memsize, holes;
	float memusage, percentCumulative;
	Boolean found;

	k = 0;
	ttlHoles = 0;
	ttlProcesses = 0;
	loads = 0;
	memsize = 128;
	memusage = 0.0;
	percentCumulative = 0.0;

	readFile();

	while(!isEmpty())
	{
		holes = 0;
		blockSize = 0;
		bestStart = 1;
		currStart =0;
		biggestSize = 0;
		found = false;

		for(i = 1; i < 129; i++)
		{
			if(memory[i] == 0)
			{
				if(blockSize == 0)
				{
					currStart = i;
				}
				blockSize++;
			}
			else
			{
				
				if(blockSize > 0)
				{
					if(blockSize > biggestSize && blockSize >= head->size)
					{
						bestStart = currStart;
						biggestSize = blockSize;
						found = true;
					}
					blockSize = 0;
				}
			}
		}

		if(blockSize > biggestSize && blockSize >= head->size)
		{
			bestStart = currStart;
			biggestSize = blockSize;
			found = true;
		}

		if(head != NULL)
		{
			if(blockSize < head->size && !found)
			{

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;

					}
				}

				memsize += memory_head->size;
				removeFromMemory();

				bestStart = 1;

			}
			else
			{
				for(j = bestStart; j < bestStart + head->size; j++)
				{
					memory[j] = head->id;
				}

				numProcesses++;
				ttlProcesses += numProcesses;
				loads++;
				memsize -= head->size;

				holes = countHoles();
				ttlHoles += holes;

				memusage = calculateMemUsage(memsize);
				cumulativeMemory[k] = memusage; /*adds the %memusage so that the cumulative can be calculated each time*/
				k++;
				percentCumulative = getCumulative(loads);

				printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d Memory Usage: %.2f%% Cumulative Memory %.2f%%\n", head->id, numProcesses, holes, memusage, percentCumulative);
				insertIntoMemory();
			}
		}
	}

	percentCumulative = getCumulative(loads);

	printf("\nTotal Loads = %d Average # of Processes = %.2f Average Holes = %.2f Cumulative memory = %.2f%%\n", loads, ((float)ttlProcesses/loads), ((float)ttlHoles/loads), percentCumulative);

	memory_destroy();
	destroy();
	clearMemory();
}

void nextFit(){

	int i = 0, j, k,blockSize, numProcesses, ttlProcesses, loads, holes, ttlHoles, lastIndex, memsize;
	float memusage, percentCumulative;
	Boolean inserting;

	k = 0;
	loads = 0;
	blockSize = 0;
	memsize = 128;
	lastIndex = 1;
	memusage = 0.0;
	percentCumulative = 0.0;
	
	readFile();
	
	while(!isEmpty())
	{
		inserting = false;
		blockSize = 0;
		printf("                            last %d %d\n", lastIndex, blockSize);
		for(i = lastIndex; i < 129; i++)
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
							printf("%d ", memory[j]);

						}
						printf("\n");
						printf("  b %d\n", blockSize);
						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
						}

						printf("\n");
						for(j = 1; j < 129; j++)
						{
							printf("%d ", memory[j]);

						}
						printf("\n");

						numProcesses++;
						ttlProcesses += numProcesses;
						loads++;
						memsize -= head->size;

						printf("                %d %c\n", memsize, head->id);

						holes = countHoles();
						ttlHoles += holes;

						memusage = calculateMemUsage(memsize);
						cumulativeMemory[k] = memusage; /*adds the %memusage so that the cumulative can be calculated each time*/
						k++;
						percentCumulative = getCumulative(loads);

						printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d Memory Usage: %.2f%% Cumulative Memory %.2f%%\n", head->id, numProcesses, holes, memusage, percentCumulative);
				
						insertIntoMemory();
						inserting = true;
						lastIndex = i;
						break;
					}
					if(i >= 128)
					{
						lastIndex = 1;
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
				printf("\n\n\nhahah\n");

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

				memsize += memory_head->size;

				printf("                              remove %d %c\n", memsize, memory_head->id);

				numProcesses--;
							
				removeFromMemory();
			}
		}
	}

	printf("Total Loads = %d\n", loads);

	memory_destroy();
	destroy();
	clearMemory();
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

int countHoles(){

	int i, holes;

	holes = 0;

	for(i = 1; i < 129; i++)
	{
		if(memory[i] == 0)
		{
			if(memory[i + 1] != 0 || i == 128)
			{
				holes++;
			}
		}
	}

	return holes;
}

float getCumulative(int currLoads){

	int i;
	float percentCumulative, currCumulative;

	percentCumulative = 0.0;
	currCumulative = 0.0;

	for(i = 0; i < currLoads; i++)
	{
		currCumulative += cumulativeMemory[i];
	}

	percentCumulative = (currCumulative / (float)currLoads);

	return percentCumulative;
}

float calculateMemUsage(int memsize){

	int usedMemory;
	float memusage;

	memusage = 0.0;
	usedMemory = 0;

	usedMemory = 128 - memsize;
	printf("used %d %d\n", usedMemory, memsize);
	memusage = ((float)usedMemory / 128) * 100;

	return memusage;
}

void clearMemory(){

	int i;

	for(i = 1; i < 129; i++)
	{
		memory[i] = 0;
	}

	for(i = 0; i < 256; i++)
	{
		cumulativeMemory[i] = 0;
	}

}


void nextTest(){

	int i, j, k,blockSize, numProcesses, ttlProcesses, loads, holes, ttlHoles, lastIndex, memsize, currStart;
	float memusage, percentCumulative;
	Boolean inserting;

	k = 0;
	loads = 0;
	blockSize = 0;
	memsize = 128;
	lastIndex = 1;
	memusage = 0.0;
	percentCumulative = 0.0;
	numProcesses = 0;
	ttlProcesses = 0;
	holes = 0;
	ttlHoles = 0;
	
	readFile();
	
	while(!isEmpty())
	{
		inserting = false;
		blockSize = 0;
		currStart = 0;
		printf("                            last %d %d\n", lastIndex, blockSize);
		for(i = lastIndex; i < 129; i++)
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
							printf("%d ", memory[j]);

						}
						printf("\n");
						printf("  b %d\n", blockSize);
						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
						}

						printf("\n");
						for(j = 1; j < 129; j++)
						{
							printf("%d ", memory[j]);

						}
						printf("\n");

						numProcesses++;
						ttlProcesses += numProcesses;
						loads++;
						memsize -= head->size;

						printf("                %d %c\n", memsize, head->id);

						holes = countHoles();
						ttlHoles += holes;

						memusage = calculateMemUsage(memsize);
						cumulativeMemory[k] = memusage; /*adds the %memusage so that the cumulative can be calculated each time*/
						k++;
						percentCumulative = getCumulative(loads);

						printf("PID Loaded: %c Number of Processes: %d Number of Holes: %d Memory Usage: %.2f%% Cumulative Memory %.2f%%\n", head->id, numProcesses, holes, memusage, percentCumulative);
				
						insertIntoMemory();
						inserting = true;
						lastIndex = i;
						break;
					}
					if(i >= 128)
					{
						printf("ya\n");
						lastIndex = 1;

						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = 0;
							}
						}
					}
				}
				
			}
			else
			{
				for(j = 1; j < 129; j++)
				{
					if(memory[j] == 1)
					{
						memory[j] = 0;
					}
				}
				blockSize = 0;
			}
		}

		if(head != NULL)
		{
			if(blockSize < head->size && inserting == false && memory_head != NULL)
			{
				printf("\n\n\nhahah %d \n", blockSize);

				memory_print();

					printf("\n");
						for(j = 1; j < 129; j++)
						{
							printf("%d ", memory[j]);

						}
						printf("\n");

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

				memsize += memory_head->size;


				numProcesses--;
							
				removeFromMemory();
			}
		}
	}

	printf("Total Loads = %d\n", loads);

	memory_destroy();
	destroy();
	clearMemory();
}