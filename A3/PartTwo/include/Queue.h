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
	int start;
	int end;
	struct Process_t * next;
}Process;

Process * head;
Process * tail;

Process * memory_head;
Process * memory_tail;

int length;
int memory_length;

Process * Q_create();
Process * initNode(int id, int size, int swapped, int start, int end);
void enqueue(int id, int size, int swapped, int start, int end);
void dequeue();
Boolean isEmpty();
void print();

void memory_enqueue(int id, int size, int swapped, int start, int end);
void memory_dequeue();
void memory_print();
Boolean memory_isEmpty();

void destroy();
void memory_destroy();

Process * traverse();
/*void Q_dequeue();
void Q_insert(Node *);
Boolean Q_isEmpty();*/

#endif