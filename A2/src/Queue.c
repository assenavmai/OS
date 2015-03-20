#include "Queue.h"

Node * Q_create(){

	Node * q;

	q = NULL;

	return q;
}

/*add to the back of the queue*/
void enqueue(int process_number, int thread_number, int cpu_time, int io_time, int arrival_time, type_t type, int index, int number_of_cpu){

	Node * data;
	
	/*priority is automatically -2*/
	data = initNode(-2, process_number, thread_number, cpu_time, io_time, arrival_time, type, index, number_of_cpu);

	/*if there is no head make a list else add to the back*/
	if(q_head == NULL)
	{
		q_head = q_tail = data;
	}
	else
	{
		q_tail->next = data;
		q_tail = data;
	}

	q_len++;

}

/*insert when it is in IO mode*/
void Q_insert(Node * nextEvent){

	if(q_head == NULL)
	{
		q_head = nextEvent;
		q_tail = nextEvent;
	}
	else
	{
		q_tail->next = nextEvent;
		q_tail = nextEvent;
	}

	q_len++;

	/*printf("%d\n", q_tail->thread_number);*/
}

/*remove the head of the queue*/
void Q_dequeue(){

	Node * temp;

	if(Q_isEmpty())
	{
		fprintf(stderr, "%s\n", "Deletion Error: dequeue(), line 39.");
		exit(1);
	}

	temp = q_head;
	q_head = temp->next;
	q_len--;
	/*free(temp);*/

	/*temp = temp->next;
	head = temp;*/
	/*head = head->next;
	temp->next = NULL;
	free(temp);*/
}

/*check if the queue is empty*/
Boolean Q_isEmpty(){

	if(q_len == 0)
	{
		return true;
	}

	return false;
}

