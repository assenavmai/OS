#include "PQueue.h"

/*Node * create(){

	Node * l;

	l = NULL;
	head = NULL;
	tail = NULL;

	return l;
}


void insert(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int number_of_threads, Thread * info){

	Node * data, *curr;

	data = initNode(priority, number_of_processes, thread_switch, process_switch, process_number, number_of_threads, info);

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
	}
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
*/