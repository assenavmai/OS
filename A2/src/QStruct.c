#include "QStruct.h"

Node * initNode(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int number_of_threads, Thread  info){

	Node * newNode = malloc(sizeof(Node) * 1);

	if(newNode == NULL)
	{
		fprintf(stderr, "%s\n", "Malloc Error: initNode(), line 14.");
		exit(0);
	}

	newNode->info = info;
	newNode->priority = priority;
	newNode->number_of_processes = number_of_processes;
	newNode->thread_switch = thread_switch;
	newNode->process_switch = process_switch;
	newNode->process_number = process_number;
	newNode->number_of_threads = number_of_threads;
	newNode->next = NULL;

	return newNode;
}

void dequeue(){

	Node * temp;

	if(head == NULL)
	{
		fprintf(stderr, "%s\n", "Deletion Error: removeHighest(), line 39.");
		exit(1);
	}

	if(head == tail)
	{
		tail = NULL;
	}

	temp = head;
	head = head->next;
	temp->next = NULL;
	free(temp);
}