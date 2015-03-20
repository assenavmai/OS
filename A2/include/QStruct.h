#ifndef Q_STRUCT_H
#define Q_STRUCT_H

#include "Boolean.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{PROCESS_ARRIVES, IO_READY, PROCESS_TERMINATION}type_t;

typedef struct Thread_t
{
	int cpu_time[512];
	int io_time[512];
	int currentBurst;
	int thread_number;
	int arrival_time;
	int time;
	type_t type;
	int number_of_cpu; /*omit*/
}Thread;

typedef struct Node_t
{
	Thread info[51];
	int start;
	int finish;
	int turnaround;
	int waiting;
	int cpuIndex;
	int process_number;
	int priority;
	int threadNum;
	type_t type;
	int number_of_processes;
	int number_of_threads;
	int thread_switch;
    int process_switch;
    struct Node_t *next;
}Node;

Node * head;
Node * tail;
Node * curr;
Node * prev;
Node * sortH;
Node * prev;
Node * q_head;
Node * q_tail;
int len;
int q_len;

Node * initNode(int priority, int process_number, int thread_number, int cpu_time, int io_time, int arrival_time, type_t type, int index, int number_of_cpu);


#endif