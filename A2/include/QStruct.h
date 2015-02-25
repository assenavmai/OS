#ifndef Q_STRUCT_H
#define Q_STRUCT_H

#include "Boolean.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef enum{PROCESS_NEW, PROCESS_READY, PROCESS_RUNNING, PROCESS_BLOCKED, PROCESS_TERMINTED}type;

typedef struct Thread_t
{
	int cpu_time[16];
	int io_time[15];
	int thread_number;
	int arrival_time;
	int number_of_cpu;
}Thread;

typedef struct Node_t
{
	Thread info;
	int number_of_processes;
	int number_of_threads;
	int thread_switch;
    int process_switch;
    int process_number;
    int priority;
    type t;
    struct Node_t *next;
}Node;

Node * head;
Node * tail;

Node * initNode(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int number_of_threads, Thread info);
void dequeue();
Boolean isEmpty();

#endif