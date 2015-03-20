#include "PQueue.h"

/*insert to the EQ and sort by arrival time*/
void insert(Node * data){


	/*data = initNode(priority, process_number, thread_number, cpu_time, io_time, arrival_time, type, index, number_of_cpu);*/

	if(head == NULL)
	{
		head = tail  = data;
	}
	else if(head->priority <= data->priority && head->process_number < data->process_number)
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

	/*else if(data->priority > head->priority)
	{
		tail->next = data;
		tail = data;
		tail->next = head;
	}*/
	/*else if(data->priority < head->priority)
	{
			data->next = head;
			head = data;
	}*/
	/*else
	{
		prev = NULL;

		while(curr == head)
		{
			if(curr->priority > data->priority)
			{
				prev->next = data;
				data->next = curr;
				return;
			}
			else if(curr->priority == data->priority)
			{
				if(curr->process_number > data->process_number)
				{
					prev->next = data;
					data->next = curr;
					return;
				}
			}
			prev = curr;
		}
	}*/

	/*if(head == NULL)
	{
		head = tail = prev = data;
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
	}*/

	len++;
}

/*insert to the EQ if io is complete*/
void IOinsert(Node * readyEvent){

	tail->next = readyEvent;
	tail = readyEvent;
	tail->next= head;
	len++;
	/*if(head == NULL)
	{
		head = readyEvent;
		tail = readyEvent;
	}
	else if(readyEvent->priority < head->priority)
	{
		readyEvent->next = head;
		head = readyEvent;
	}
	else if(readyEvent->priority > tail->priority)
	{
		tail->next = readyEvent;
		tail = readyEvent;
		tail->next = head;
	}
	else
	{
		curr = head;

		while(curr->next != NULL && curr->next->priority < readyEvent->priority)
		{
			curr = curr->next;
		}
		readyEvent->next = curr->next;
		curr->next = readyEvent;
	}*/

	len++;
}

/*check if the queue is empty*/
Boolean isEmpty(){

	if(len == 0 || head == NULL)
	{
		return true;
	}

	return false;
}

/*remove the head of the queue*/
void dequeue(){

	Node * temp;

	if(isEmpty())
	{
		fprintf(stderr, "%s\n", "Deletion Error: dequeue(), line 39.");
		exit(1);
	}

	temp = head;
	head = temp->next;
	len--;
	/*free(temp);*/

	/*temp = temp->next;
	head = temp;*/
	/*head = head->next;
	temp->next = NULL;
	free(temp);*/
}