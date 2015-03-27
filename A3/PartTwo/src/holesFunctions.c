#include "holesFunctions.h"
#include "Queue.h"

int memory[129] = {0}; /*size is 129 because I count from 1 instead of 0*/
float cumulativeMemory[256] = {0.0};

/*reads the file and adds it into the process queue*/
void readFile(const char *str){

	FILE * f;
	char id;
	int size;
	int i, lineAmount;
	char line[1024];

	lineAmount = 0;
	if((f = fopen(str, "r")) == NULL)
	{
		fprintf(stderr, "%s\n", "Could not open file.");
		exit(1);
	}

	/*get how much lines there are*/
	while(fgets(line, sizeof(line), f) != NULL)
	{
		lineAmount++;
	}

	rewind(f);

	for (i = 0; i < lineAmount; ++i)
	{
		while(fscanf(f, "%c %d", &id, &size) == 2)
		{
			enqueue(id, size, 0);
		}
	}
}


/*First Fit Memory Allocation
     Finds the first spot that can fit the process*/
void firstFit(const char *str){

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
	readFile(str);

	
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
				/*if we hit a non zero then remove all the 1's in the array so nothing is visited*/
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
			/*removing a process from memory*/
			if(blockSize < head->size && inserting == false)
			{
				memsize += memory_head->size;

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;
					}

					if(memory[j] == 1)/*mark all visited spots as empty*/
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

	percentCumulative = getCumulative(loads); /*calculate %mem cumulative*/

	printf("\nTotal Loads = %d Average # of Processes = %.2f Average Holes = %.2f Cumulative memory = %.2f%%\n", loads, ((float)ttlProcesses/loads), ((float)ttlHoles/loads), percentCumulative);

	memory_destroy();
	destroy();
	clearMemory(); /*set the array back to 0*/
}

/*Best Fit Memory Allocation
     Finds the smallest hole amongst all the holes that can fit the process that wants to be added into memory*/
void bestFit(const char *str){

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

	readFile(str);

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
				/*if we are at a zero, make the current starting point that spot*/
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
					/*change the starting point and the smallest size if we find something smaller than is greater than the
						size of the process that wants to be added*/
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

		/*This checks for the last hole in the array*/
		if(blockSize < smallestSize && blockSize >= head->size)
		{
			bestStart = currStart;
			smallestSize = blockSize;
			found = true;
		}

		if(head != NULL)
		{
			/*remove from the oldest process from memory if we did not find a size to fit the process*/
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
				numProcesses--;

				removeFromMemory();

				bestStart = 1;
			}
			else /*inserting to memory*/
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

/*Worst Fit Memory Allocation
	Finds the biggest hole amongst all the holes that can fit the process that wants to be added into memory*/
void worstFit(const char *str){

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

	readFile(str);

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
				/*if we hit a 0, make the current starting point for that hole i*/
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
					/*if we find a bigger hole that can fit the process, make that the biggest found and the start position to the currStart*/
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

		/*This accounts for if there is a hole at the end of the array*/
		if(blockSize > biggestSize && blockSize >= head->size)
		{
			bestStart = currStart;
			biggestSize = blockSize;
			found = true;
		}

		if(head != NULL)
		{
			/*remove from memory if a spot isn't found*/
			if(blockSize < head->size && !found)
			{

				for(j = 1; j < 129; j++)
				{
					if(memory[j] == memory_head->id)
					{
						memory[j] = 0;

					}
				}

				numProcesses--;
				memsize += memory_head->size;
				removeFromMemory();

				bestStart = 1;

			}
			else
			{
				/*add to the memory file*/
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

void nextFit(const char *str){

	int i, j, k,blockSize, numProcesses, ttlProcesses, loads, holes, ttlHoles, lastIndex, memsize;
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
	
	readFile(str);
	
	while(!isEmpty())
	{
		inserting = false;
		blockSize = 0;

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
						/*Inserting into the memory queue*/
						for(j = 1; j < 129; j++)
						{
							if(memory[j] == 1)
							{
								memory[j] = head->id;
							}
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
						inserting = true;
						lastIndex = i; /*last index is set to i, keep track where last inserted*/
						break;
					}
					if(i >= 128)/*if we reach the last index, go back to the start and remove anywhere we marked as visited*/
					{
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
				/*if it is not 0, remove everything that is marked as visited*/
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
				/*remove from the memory queue*/
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

	percentCumulative = getCumulative(loads);

	printf("\nTotal Loads = %d Average # of Processes = %.2f Average Holes = %.2f Cumulative memory = %.2f%%\n", loads, ((float)ttlProcesses/loads), ((float)ttlHoles/loads), percentCumulative);


	memory_destroy();
	destroy();
	clearMemory();
}

/*Inserts the process into memory queue*/
void insertIntoMemory(){

	memory_enqueue(head->id, head->size, head->swapped);
	dequeue();
}

/*remove process from memory queue*/
void removeFromMemory(){

	memory_head->swapped++;

	if(memory_head->swapped != 3)
	{
		enqueue(memory_head->id, memory_head->size, memory_head->swapped);
		memory_dequeue();
	}
	
	else/*if it was swapped 3 times, just remove it from the queue*/
	{
		memory_dequeue();
	}
}

/*count the amount of holes in memory*/
int countHoles(){

	int i, holes;

	holes = 0;

	for(i = 1; i < 129; i++)
	{
		/*check if it is 0, if the next spot isn't a 0 or is at the last index*/
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

/*gets the %mem cumulative*/
float getCumulative(int currLoads){

	int i;
	float percentCumulative, currCumulative;

	percentCumulative = 0.0;
	currCumulative = 0.0;

	for(i = 0; i < currLoads; i++)
	{
		currCumulative += cumulativeMemory[i]; /*the mem usage is added to an array so add all the values together*/
	}

	percentCumulative = (currCumulative / (float)currLoads);

	return percentCumulative;
}

/*calculates %memusage*/
float calculateMemUsage(int memsize){

	int usedMemory;
	float memusage;

	memusage = 0.0;
	usedMemory = 0;

	usedMemory = 128 - memsize;
	memusage = ((float)usedMemory / 128) * 100;

	return memusage;
}

/*clears the memory array back to 0 and the cumulativeMemory array also*/
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