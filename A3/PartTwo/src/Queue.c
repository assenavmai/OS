#include "Queue.h"

/*Create a new node to put into the queue*/
Process * initNode(int id, int size, int swapped){

	Process * newProcess = malloc(sizeof(Process) * 1);

	if(newProcess == NULL)
	{
		fprintf(stderr, "%s\n", "Malloc Error: initNode(), line 18.");
		exit(0);
	}

	newProcess->id = id;
	newProcess->size = size;
	newProcess->swapped = swapped;
	newProcess->next = NULL;

	return newProcess;
}

/*Add to the back of the process queue*/
void enqueue(int id, int size, int swapped){

	Process * data;

	data = initNode(id, size, swapped);

	if(head == NULL)/*if there is not anything in the queue*/
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

/*Remove from the front of the process queue*/
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

/*Checks if the queue is empty*/
Boolean isEmpty(){

	if(length == 0 || head == NULL)
	{
		return true;
	}

	return false;
}

/*Destroys the process queue*/
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

/*Helper function: prints out the process queue*/
void print(){

	Process * temp;

	temp = head;

	while(temp != NULL)
	{
		printf("%c %d %d\n", temp->id, temp->size, temp->swapped);
		temp = temp->next;
	}
}

/*************************************Memory Queue Functions Start Here************************************************/

/*Adds to the back of the memory queue*/
void memory_enqueue(int id, int size, int swapped){

	Process * data;

	data = initNode(id, size, swapped);

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


/*Removes the first element in the memory queue*/
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


/*Destroys the memory queue*/
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


/*Checks if the memory queue is empty*/
Boolean memory_isEmpty(){

	if(memory_length == 0)
	{
		return true;
	}

	return false;
}

/*Prints out the memory queue -> helper function*/
void memory_print(){

	Process * temp;

	temp = memory_head;
	if(isEmpty())
	{
		printf("Nothing to print in memory!\n");
		return;
	}

	while(temp != NULL)
	{
		printf("%c %d %d\n", temp->id, temp->size, temp->swapped);
		temp = temp->next;
	}
}