#ifndef LIST_H
#define LIST_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Boolean.h"

typedef struct Node_t
{
	int number_of_processes;
	int thread_switch;
    int process_switch;
    int process_number;
    int arrival_time;
    int number_of_cpu;
    int cpu_time;
    int io_time;
    int thread_number;
    int priority;
    struct Node_t *next;
}Node;

Node * head;
Node * tail;

Node * create();
void insert(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number);
void removeHighest();
void display();
void makeEmpty();
Node * initNode(int priority, int number_of_processes, int thread_switch, int process_switch, int process_number, int arrival_time, int number_of_cpu, int cpu_time, int io_time, int thread_number);
Boolean isEmpty();



#endif