#include "List.h"

Node * create(){

	Node * l;

	l = NULL;
	head = NULL;
	tail = NULL;

	return l;
}

/*sorted*/
void insert(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number){

	Node * data, *curr;

	data = initNode(priority, number_of_processes, thread_switch, process_switch, process_number, arrival_time, number_of_cpu, cpu_time, io_time, thread_number);

	if(head == NULL)
	{
		head = tail = data;
	}
	if(data->priority < head->priority)
	{
		data->next = head;
		head = data;
	}
	else if(data->priority > tail->priority)
	{
		tail->next = data;
		tail = data;
		tail->next = head;
	}
	else
	{
		curr = head;

		while(curr->next != NULL && curr->next->priority < data->priority)
		{
			curr = curr->next;
		}
		data->next = curr->next;
		curr->next = data;
		
		/*tail->next = data;
		tail = data;
		printf("Added to end of queue.\n");*/
	}
}

void removeHighest(){

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

void display(){

	Node * temp;

	if(head == NULL)
	{
		printf("Priority Queue is empty.\n");
	}
	else
	{
		temp = head;

		while(temp != NULL)
		{
			printf("[%d]->", temp->priority);
			temp = temp->next;
		}
		printf("\n");
	}
}
Node * initNode(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number){

	Node * newNode = malloc(sizeof(Node) * 1);

	if(newNode == NULL)
	{
		fprintf(stderr, "%s\n", "Malloc Error: initNode(), line 14.");
		exit(0);
	}

	newNode->priority = priority;
	newNode->number_of_processes = number_of_processes;
	newNode->thread_switch = thread_switch;
	newNode->process_switch = process_switch;
	newNode->process_number = process_number;
	newNode->arrival_time = arrival_time;
	newNode->number_of_cpu = number_of_cpu;
	newNode->cpu_time = cpu_time;
	newNode->io_time = io_time;
	newNode->thread_number = thread_number;
	newNode->next = NULL;

	return newNode;
}