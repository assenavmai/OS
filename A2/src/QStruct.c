#include "QStruct.h"

/*Creates a Node and initializes all of the values*/
Node * initNode(int priority, int process_number, int thread_number, int cpu_time, int io_time, int arrival_time, type_t type, int index, int number_of_cpu){

	Node * newNode = malloc(sizeof(Node) * 1);

	if(newNode == NULL)
	{
		fprintf(stderr, "%s\n", "Malloc Error: initNode(), line 14.");
		exit(0);
	}

	newNode->info[thread_number].number_of_cpu = number_of_cpu;
	newNode->priority = priority;
	newNode->cpuIndex = index;
	newNode->info[thread_number].currentBurst = index;
	newNode->threadNum = thread_number;
	newNode->info[thread_number].cpu_time[index] = cpu_time;
	newNode->info[thread_number].io_time[index] = io_time;
	newNode->info[thread_number].arrival_time = arrival_time;
	newNode->process_number = process_number;
	newNode->type = type;
	newNode->next = NULL;

	return newNode;
}


/*get the head of the list priority*/
int peek(){

	int peekRt = 0;

	if(head == NULL)
	{
		fprintf(stderr, "%s\n", "Peek Error: peek(), line 33.");
		exit(1);
	}

	peekRt = head->priority;

	return peekRt;

}