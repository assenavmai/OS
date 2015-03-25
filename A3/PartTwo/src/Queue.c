#include "Queue.h"

Process * Q_create(){

	Process * q;

	q = NULL;

	return q;
}

Process * initNode(int id, int size, int swapped, int start, int end){

	Process * newProcess = malloc(sizeof(Process) * 1);

	if(newProcess == NULL)
	{
		fprintf(stderr, "%s\n", "Malloc Error: initNode(), line 18.");
		exit(0);
	}

	newProcess->id = id;
	newProcess->size = size;
	newProcess->swapped = swapped;
	newProcess->start = start;
	newProcess->end = end;
	newProcess->next = NULL;

	return newProcess;
}

void enqueue(int id, int size, int swapped, int start, int end){

	Process * data;

	data = initNode(id, size, swapped, start, end);

	if(head == NULL)
	{
		head = tail = data;
	}
	else
	{
		tail->next = data;
		tail = data;
	}

	length++;
}

void memory_enqueue(int id, int size, int swapped, int start, int end){

	Process * data;

	data = initNode(id, size, swapped, start, end);

	if(memory_head == NULL)
	{
		memory_head = memory_tail = data;
	}
	else
	{
		memory_tail->next = data;
		memory_tail = data;
	}

	memory_length++;
}

void dequeue(){

	Process * temp;

	if(isEmpty())
	{
		fprintf(stderr, "%s\n", "Deletion error(), dequeue() line 52.");
		exit(1);
	}

	temp = head;
	head = temp->next;
	length--;

	/*free(temp);*/
}

void memory_dequeue(){

	Process * temp;

	if(memory_isEmpty())
	{
		fprintf(stderr, "%s\n", "Deletion error(), memory_dequeue() line 91.");
		exit(1);
	}

	temp = memory_head;
	memory_head = temp->next;
	memory_length--;

	free(temp);
}

void destroy(){

	if(head == NULL)
	{
		return;
	}

	while(head != NULL)
	{
		dequeue();
	}

	tail = NULL;
}

void memory_destroy(){

	if(memory_head == NULL)
	{
		return;
	}

	while(memory_head != NULL)
	{
		memory_dequeue();
	}

	memory_tail = NULL;

}

Boolean isEmpty(){

	if(length == 0 || head == NULL)
	{
		return true;
	}

	return false;
}

Boolean memory_isEmpty(){

	if(memory_length == 0)
	{
		return true;
	}

	return false;
}

Process * traverse(){

	Process * curr, *smallest;

	curr = head;

	while(curr->next != NULL)
	{

		if(curr->size <= curr->next->size)
		{
			smallest = curr;
			
		}

		curr = curr->next;
	}
	printf("%c %d\n", smallest->id, smallest->size);
	return smallest;
}

void print(){

	Process * temp;

	temp = head;

	while(temp != NULL)
	{
		printf("%c %d %d\n", temp->id, temp->size, temp->swapped);
		temp = temp->next;
	}
}

void memory_print(){

	Process * temp;

	temp = memory_head;

	while(temp != NULL)
	{
		printf("%c %d %d\n", temp->id, temp->size, temp->swapped);
		temp = temp->next;
	}
}