#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"

typedef struct Process_t
{
	char id;
	int size;
	int swapped;
	struct Process_t * next;
}Process;

/*Process Queue*/
Process * head;
Process * tail;

/*Memory Queue*/
Process * memory_head;
Process * memory_tail;

/*Length of Process Queue*/
int length;

/*Length of Memory Queue*/
int memory_length;

/*process memory functions*/
Process * initNode(int id, int size, int swapped);
void enqueue(int id, int size, int swapped);
void dequeue();
Boolean isEmpty();
void print();
void destroy();


/*memory queue functions*/
void memory_enqueue(int id, int size, int swapped);
void memory_dequeue();
void memory_print();
Boolean memory_isEmpty();
void memory_destroy();

#endif