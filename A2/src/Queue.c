#include "Queue.h"

Node * Q_create(){

	Node * q;

	q = NULL;

	return q;
}

void enqueue(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number){

	Node * data;

	data = initNode(priority, number_of_processes, thread_switch, process_switch, process_number, arrival_time, number_of_cpu, cpu_time, io_time, thread_number);

	if(head == NULL)
	{
		head = tail = data;
	}
	else
	{
		tail->next = data;
		tail = data;
	}
}

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